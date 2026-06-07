#include "graph.h"

GameGraph graph;

void graph_init(int code)
{
    graph.last_vsync = 0;
    graph.delta = 1;

    if (code == 0)
    {
        graph.ResW = 256;
        graph.ResH = 256;
        graph.pal_mode = TRUE;
    }
    else
    {
        graph.ResW = 256;
        graph.ResH = 240;
        graph.pal_mode = FALSE;
    }

    graph.db = 0;

    graph.camPos.vx = 0;
    graph.camPos.vy = 0;
    graph.camPos.vz = 0;
    graph.camRot.vx = 0;
    graph.camRot.vy = 0;
    graph.camRot.vz = 0;

    graph.scr_fade = 128;

    ResetGraph(0);
    SetDispMask(0);

    InitGeom();
    SetGeomOffset(graph.ResW / 2, graph.ResH / 2);
    SetGeomScreen(graph.ResW / 2);

    SetDefDispEnv(&graph.disp[0], 0, 0, graph.ResW, graph.ResH);
    SetDefDispEnv(&graph.disp[1], 0, (graph.ResH > 256 ? 0 : graph.ResH), graph.ResW, graph.ResH);
    SetDefDrawEnv(&graph.draw[0], 0, 0, graph.ResW, graph.ResH);
    SetDefDrawEnv(&graph.draw[1], 0, (graph.ResH > 256 ? 0 : graph.ResH), graph.ResW, graph.ResH);

    if (graph.pal_mode)
    {
        graph.disp[0].screen.y = 24;
        graph.disp[1].screen.y = 24;
    }
    else
    {
        graph.disp[0].screen.y = 0;
        graph.disp[1].screen.y = 0;
    }

    if (graph.ResH > 256)
    {
        graph.disp[0].isinter = 1;
        graph.disp[1].isinter = 1;
    }
    else
    {
        graph.disp[0].isinter = 0;
        graph.disp[1].isinter = 0;
    }

    SetVideoMode(graph.pal_mode ? MODE_PAL : MODE_NTSC);

    setRGB0(&graph.draw[0], 0, 0, 0);
    graph.draw[0].isbg = 1;
    setRGB0(&graph.draw[1], 0, 0, 0);
    graph.draw[1].isbg = 1;

    ClearOTagR(graph.ot[0], OTLEN);
    ClearOTagR(graph.ot[1], OTLEN);

    PutDispEnv(&graph.disp[0]);
    PutDrawEnv(&graph.draw[0]);

    graph.nextpri = graph.pribuff[0];

    graph_clearvram();
}

void graph_disp()
{
    DrawSync(0);

    while (!graph_vsync())
    {
        VSync(0);
    }

    PutDispEnv(&graph.disp[graph.db]);
    PutDrawEnv(&graph.draw[graph.db]);

    SetDispMask(1);

    DrawOTag(graph.ot[graph.db] + OTLEN - 1);

    graph.db = !graph.db;
    graph.nextpri = graph.pribuff[graph.db];
}

void graph_clearvram()
{
    for (int x = 0; x < 1024; x += 64)
    {
        for (int y = 0; y < 512; y += 64)
        {
            RECT rect;
            setRECT(&rect, x, y, 64, 64);
            ClearImage2(&rect, 0, 0, 0);
        }
    }
}

CCLUT *graph_loadtexture(u_long *tim, int max_clut)
{
    TIM_IMAGE tparam;
    CCLUT *cluting = NULL;

    OpenTIM(tim);
    ReadTIM(&tparam);

    LoadImage(tparam.prect, (u_long *)tparam.paddr);
    DrawSync(0);

    if (tparam.mode & 0x8)
    {
        if (max_clut > 0)
        {
            u_short *cluter = (u_short *)tparam.caddr;
            cluting = (CCLUT *)malloc(max_clut * sizeof(CCLUT));

            for (int i = 0; i < max_clut; i++)
            {
                cluting[i].r = (cluter[i] >> 0) & 31;
                cluting[i].g = (cluter[i] >> 5) & 31;
                cluting[i].b = (cluter[i] >> 10) & 31;

                cluting[i].r *= 8;
                cluting[i].g *= 8;
                cluting[i].b *= 8;
                cluting[i].stp = (cluter[i] >> 15) & 1;
            }
        }

        LoadImage(tparam.crect, (u_long *)tparam.caddr);
        DrawSync(0);
    }

    return cluting;
}

void graph_loadback(u_long *tim)
{
    TIM_IMAGE tparam;

    OpenTIM(tim);
    ReadTIM(&tparam);

    RECT bg0, bg1;

    bg0.x = 0;
    bg0.y = 0;
    bg0.w = 256;
    bg0.h = graph.pal_mode == TRUE ? 256 : 240;

    bg1.x = 0;
    bg1.y = graph.pal_mode == TRUE ? 256 : 240;
    bg1.w = 256;
    bg1.h = graph.pal_mode == TRUE ? 256 : 240;

    LoadImage(&bg0, (u_long *)tparam.paddr);
    DrawSync(0);
    LoadImage(&bg1, (u_long *)tparam.paddr);
    DrawSync(0);
}

Model graph_loadmodel(u_long *mdl)
{
    Model dump = {0};
    dump.n_prim = OpenTMD(mdl, 0);
    dump.mdl = (TMD_PRIM *)malloc(dump.n_prim * sizeof(TMD_PRIM));
    TMD_PRIM tmd;
    for (int i = 0; i < dump.n_prim && ReadTMD(&tmd) != 0; i++)
    {
        dump.mdl[i] = tmd;
    }

    return dump;
}

void graph_drawsprite(Sprite spr, long OTx)
{
    long polydepth;
    long polyflag;

    short vert_w = spr.w / 2;
    short vert_h = spr.h / 2;
    int uv_w = spr.w - 1;
    int uv_h = spr.h - 1;

    SVECTOR VertPos[4] = {
        {-vert_w, -vert_h, 0},
        {-vert_w, vert_h, 0},
        {vert_w, -vert_h, 0},
        {vert_w, vert_h, 0}};
    MATRIX PolyMatrix = {0};

    long OTz;

    RotMatrix(&spr.RotVector, &PolyMatrix);
    TransMatrix(&PolyMatrix, &spr.MovVector);
    ScaleMatrix(&PolyMatrix, &spr.ScaleVector);

    CompMatrixLV(&graph.camMat, &PolyMatrix, &PolyMatrix);
    SetRotMatrix(&PolyMatrix);
    SetTransMatrix(&PolyMatrix);

    POLY_FT4 *poly = (POLY_FT4 *)graph.nextpri;
    setPolyFT4(poly);

    poly->tpage = spr.tpage;
    poly->clut = spr.clut;

    if (graph.scr_fade > 0)
    {
        if (spr.alpha >= 127)
        {
            setSemiTrans(poly, 0);
            setRGB0(poly, (u_char)(((unsigned short)spr.r * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)spr.g * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)spr.b * (unsigned short)graph.scr_fade + 64) >> 7));
        }
        else
        {
            setSemiTrans(poly, 1);

            if (spr.alpha > 0)
            {
                setRGB0(poly, (u_char)(((((unsigned short)spr.r * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)spr.alpha + 64) >> 7), (u_char)(((((unsigned short)spr.g * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)spr.alpha + 64) >> 7), (u_char)(((((unsigned short)spr.b * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)spr.alpha + 64) >> 7));
            }
            else
            {
                setRGB0(poly, 0, 0, 0);
            }
        }
    }
    else
    {
        setRGB0(poly, 0, 0, 0);
    }

    OTz = RotTransPers(&VertPos[0], (long *)&poly->x0, &polydepth, &polyflag);
    OTz += RotTransPers(&VertPos[1], (long *)&poly->x1, &polydepth, &polyflag);
    OTz += RotTransPers(&VertPos[2], (long *)&poly->x2, &polydepth, &polyflag);
    OTz += RotTransPers(&VertPos[3], (long *)&poly->x3, &polydepth, &polyflag);

    OTz /= 4;

    setUV4(poly, spr.u, spr.v, spr.u, spr.v + uv_h, spr.u + uv_w, spr.v, spr.u + uv_w, spr.v + uv_h);

    if ((OTz > 0) && (OTz < OTLEN))
    {
        AddPrim(&graph.ot[graph.db][(OTx == -1 ? OTz : OTx)], poly);
        graph.nextpri += sizeof(POLY_FT4);
    }
}

void graph_drawmodel(Model mdl, VECTOR Trans, SVECTOR Rotate, VECTOR Scale)
{
    long p, OTz, Flag;
    int nclip;
    MATRIX Matrix = {0};

    RotMatrix(&Rotate, &Matrix);
    TransMatrix(&Matrix, &Trans);
    ScaleMatrix(&Matrix, &Scale);
    // SetRotMatrix(&Matrix);
    // SetTransMatrix(&Matrix);

    CompMatrixLV(&graph.camMat, &Matrix, &Matrix);
    SetRotMatrix(&Matrix);
    SetTransMatrix(&Matrix);

    for (int i = 0; i < mdl.n_prim; i++)
    {
        if (mdl.mdl[i].r3 != 0 || mdl.mdl[i].g3 != 0 || mdl.mdl[i].b3 != 0 || mdl.mdl[i].p3 != 0 || mdl.mdl[i].u3 != 0 || mdl.mdl[i].v3 != 0 || mdl.mdl[i].vert3 != 0 || mdl.mdl[i].norm3 != 0)
        {
            if ((mdl.mdl[i].r0 == 0 && mdl.mdl[i].r1 == 0 && mdl.mdl[i].r2 == 0 && mdl.mdl[i].r3 == 0) && (mdl.mdl[i].g0 == 0 && mdl.mdl[i].g1 == 0 && mdl.mdl[i].g2 == 0 && mdl.mdl[i].g3 == 0) && (mdl.mdl[i].b0 == 0 && mdl.mdl[i].b1 == 0 && mdl.mdl[i].b2 == 0 && mdl.mdl[i].b3 == 0))
            {
                POLY_GT4 *poly = (POLY_GT4 *)graph.nextpri;

                SetPolyGT4(poly);

                poly->tpage = mdl.tpage;
                poly->clut = mdl.clut;

                if (graph.scr_fade > 0)
                {
                    setRGB0(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB1(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB2(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB3(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(poly, 0, 0, 0);
                    setRGB1(poly, 0, 0, 0);
                    setRGB2(poly, 0, 0, 0);
                    setRGB3(poly, 0, 0, 0);
                }
                setUV4(poly, mdl.mdl[i].u0 + mdl.u, mdl.mdl[i].v0 + mdl.v, mdl.mdl[i].u1 + mdl.u, mdl.mdl[i].v1 + mdl.v, mdl.mdl[i].u2 + mdl.u, mdl.mdl[i].v2 + mdl.v, mdl.mdl[i].u3 + mdl.u, mdl.mdl[i].v3 + mdl.v);

                // OTz = RotTransPers(&mdl.mdl[i].x0, (long *)&poly->x0, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x1, (long *)&poly->x1, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x2, (long *)&poly->x2, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x3, (long *)&poly->x3, &p, &Flag);

                // OTz /= 4;

                nclip = RotAverageNclip4(&mdl.mdl[i].x0, &mdl.mdl[i].x1, &mdl.mdl[i].x2, &mdl.mdl[i].x3, (long *)&poly->x0, (long *)&poly->x1, (long *)&poly->x2, (long *)&poly->x3, &p, &OTz, &Flag);

                if (nclip <= 0)
                    continue;

                if ((OTz > 0) && (OTz < OTLEN))
                {
                    AddPrim(&graph.ot[graph.db][OTz], poly);
                    graph.nextpri += sizeof(POLY_GT4);
                }
            }
            else
            {
                POLY_G4 *poly = (POLY_G4 *)graph.nextpri;

                SetPolyG4(poly);

                if (graph.scr_fade > 0)
                {
                    setRGB0(poly, (u_char)(((unsigned short)mdl.mdl[i].r0 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g0 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b0 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB1(poly, (u_char)(((unsigned short)mdl.mdl[i].r1 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g1 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b1 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB2(poly, (u_char)(((unsigned short)mdl.mdl[i].r2 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g2 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b2 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB3(poly, (u_char)(((unsigned short)mdl.mdl[i].r3 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g3 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b3 * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(poly, 0, 0, 0);
                    setRGB1(poly, 0, 0, 0);
                    setRGB2(poly, 0, 0, 0);
                    setRGB3(poly, 0, 0, 0);
                }

                // OTz = RotTransPers(&mdl.mdl[i].x0, (long *)&poly->x0, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x1, (long *)&poly->x1, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x2, (long *)&poly->x2, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x3, (long *)&poly->x3, &p, &Flag);

                // OTz /= 4;

                nclip = RotAverageNclip4(&mdl.mdl[i].x0, &mdl.mdl[i].x1, &mdl.mdl[i].x2, &mdl.mdl[i].x3, (long *)&poly->x0, (long *)&poly->x1, (long *)&poly->x2, (long *)&poly->x3, &p, &OTz, &Flag);

                if (nclip <= 0)
                    continue;

                if ((OTz > 0) && (OTz < OTLEN))
                {
                    AddPrim(&graph.ot[graph.db][OTz], poly);
                    graph.nextpri += sizeof(POLY_G4);
                }
            }
        }
        else
        {
            if ((mdl.mdl[i].r0 == 0 && mdl.mdl[i].r1 == 0 && mdl.mdl[i].r2 == 0) && (mdl.mdl[i].g0 == 0 && mdl.mdl[i].g1 == 0 && mdl.mdl[i].g2 == 0) && (mdl.mdl[i].b0 == 0 && mdl.mdl[i].b1 == 0 && mdl.mdl[i].b2 == 0))
            {
                POLY_GT3 *poly = (POLY_GT3 *)graph.nextpri;

                SetPolyGT3(poly);

                poly->tpage = mdl.tpage;
                poly->clut = mdl.clut;

                if (graph.scr_fade > 0)
                {
                    setRGB0(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB1(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB2(poly, (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(poly, 0, 0, 0);
                    setRGB1(poly, 0, 0, 0);
                    setRGB2(poly, 0, 0, 0);
                }

                setUV3(poly, mdl.mdl[i].u0 + mdl.u, mdl.mdl[i].v0 + mdl.v, mdl.mdl[i].u1 + mdl.u, mdl.mdl[i].v1 + mdl.v, mdl.mdl[i].u2 + mdl.u, mdl.mdl[i].v2 + mdl.v);

                // OTz = RotTransPers(&mdl.mdl[i].x0, (long *)&poly->x0, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x1, (long *)&poly->x1, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x2, (long *)&poly->x2, &p, &Flag);

                // OTz /= 3;

                nclip = RotAverageNclip3(&mdl.mdl[i].x0, &mdl.mdl[i].x1, &mdl.mdl[i].x2, (long *)&poly->x0, (long *)&poly->x1, (long *)&poly->x2, &p, &OTz, &Flag);

                if (nclip <= 0)
                    continue;

                if ((OTz > 0) && (OTz < OTLEN))
                {
                    AddPrim(&graph.ot[graph.db][OTz], poly);
                    graph.nextpri += sizeof(POLY_GT3);
                }
            }
            else
            {
                POLY_G3 *poly = (POLY_G3 *)graph.nextpri;

                SetPolyG3(poly);

                if (graph.scr_fade > 0)
                {
                    setRGB0(poly, (u_char)(((unsigned short)mdl.mdl[i].r0 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g0 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b0 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB1(poly, (u_char)(((unsigned short)mdl.mdl[i].r1 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g1 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b1 * (unsigned short)graph.scr_fade + 64) >> 7));
                    setRGB2(poly, (u_char)(((unsigned short)mdl.mdl[i].r2 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].g2 * (unsigned short)graph.scr_fade + 64) >> 7), (u_char)(((unsigned short)mdl.mdl[i].b2 * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(poly, 0, 0, 0);
                    setRGB1(poly, 0, 0, 0);
                    setRGB2(poly, 0, 0, 0);
                }

                // OTz = RotTransPers(&mdl.mdl[i].x0, (long *)&poly->x0, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x1, (long *)&poly->x1, &p, &Flag);
                // OTz += RotTransPers(&mdl.mdl[i].x2, (long *)&poly->x2, &p, &Flag);

                // OTz /= 3;

                nclip = RotAverageNclip3(&mdl.mdl[i].x0, &mdl.mdl[i].x1, &mdl.mdl[i].x2, (long *)&poly->x0, (long *)&poly->x1, (long *)&poly->x2, &p, &OTz, &Flag);

                if (nclip <= 0)
                    continue;

                if ((OTz > 0) && (OTz < OTLEN))
                {
                    AddPrim(&graph.ot[graph.db][OTz], poly);
                    graph.nextpri += sizeof(POLY_G3);
                }
            }
        }
    }
}

void graph_loadclut(CCLUT *clut, short x, short y, int max_clut)
{
    u_short *cluter = (u_short *)malloc(max_clut * sizeof(u_short));

    for (int i = 0; i < max_clut; i++)
    {
        cluter[i] = (((clut[i].r / 8) & 31) | (((clut[i].g / 8) & 31) << 5) | (((clut[i].b / 8) & 31) << 10) | (clut[i].stp << 15));
    }

    RECT rect = {x, y, max_clut, 1};
    LoadImage(&rect, (u_long *)cluter);
    DrawSync(0);

    free(cluter);
}

void graph_drawback(u_short tp, u_short cl)
{
    int w = 256;
    int h = graph.pal_mode ? 256 : 240;

    SPRT *sprt;
    DR_TPAGE *tpage;

    sprt = (SPRT *)graph.nextpri;
    setSprt(sprt);

    setXY0(sprt, 0, 0);
    setWH(sprt, w, h);
    setUV0(sprt, 0, 0);

    if (graph.scr_fade > 0)
    {
        setRGB0(sprt,
                (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7),
                (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7),
                (u_char)(((unsigned short)127 * (unsigned short)graph.scr_fade + 64) >> 7));
    }
    else
    {
        setRGB0(sprt, 0, 0, 0);
    }
    sprt->clut = cl;

    addPrim(graph.ot[graph.db][OTLEN - 1], sprt);
    graph.nextpri += sizeof(SPRT);

    tpage = (DR_TPAGE *)graph.nextpri;
    setDrawTPage(tpage, 0, 1, tp);
    addPrim(graph.ot[graph.db][OTLEN - 1], tpage);

    graph.nextpri += sizeof(DR_TPAGE);
}

void graph_drawtext(int x, int y, u_char alpha, u_int size, u_char align, TextChar *text, long OTz)
{
    if (size <= 0)
        return;

    if (!text)
        return;

    int len = 0;

    for (int g = 0; g < size; g++)
    {
        len += text[g].w;
    }

    int i = 0;

    int a = x - (len / 2);

    if (align == 1)
    {
        a = x;
    }
    else if (align == 2)
    {
        a = x - len;
    }

    if (align == 0)
    {
        while (a < len + x - (len / 2))
        {
            SPRT *sprt;
            DR_TPAGE *tpage;

            sprt = (SPRT *)graph.nextpri;
            setSprt(sprt);

            int u = text[i].u;
            int v = text[i].v;

            for (int b = 0; b < text[i].char_id; b++)
            {
                u += text[i].w;

                if (u >= text[i].mw)
                {
                    u = 0;
                    v += text[i].h;
                }

                if (v >= text[i].mh)
                {
                    return;
                }
            }

            setXY0(sprt, a, y - (text[i].h / 2));
            setWH(sprt, text[i].w, text[i].h);
            setUV0(sprt, u, v);

            if (graph.scr_fade > 0)
            {
                if (alpha >= 128)
                {
                    setRGB0(sprt,
                            (u_char)(((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(sprt, (u_char)(((((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7));
                }
            }
            else
            {
                setRGB0(sprt, 0, 0, 0);
            }

            sprt->clut = text[i].clut;

            addPrim(graph.ot[graph.db][OTz], sprt);
            setSemiTrans(sprt, alpha >= 128 ? 0 : 1);
            graph.nextpri += sizeof(SPRT);

            tpage = (DR_TPAGE *)graph.nextpri;
            setDrawTPage(tpage, 0, 1, getTPage(0, alpha >= 128 ? 0 : 1, text[i].tpage_x, text[i].tpage_y));
            addPrim(graph.ot[graph.db][OTz], tpage);

            graph.nextpri += sizeof(DR_TPAGE);

            a += text[i].w;

            if (i < size - 1)
            {
                i++;
            }
        }
    }
    else if (align == 1)
    {
        while (a < len + x)
        {
            SPRT *sprt;
            DR_TPAGE *tpage;

            sprt = (SPRT *)graph.nextpri;
            setSprt(sprt);

            int u = text[i].u;
            int v = text[i].v;

            for (int b = 0; b < text[i].char_id; b++)
            {
                u += text[i].w;

                if (u >= text[i].mw)
                {
                    u = 0;
                    v += text[i].h;
                }

                if (v >= text[i].mh)
                {
                    return;
                }
            }

            setXY0(sprt, a, y - (text[i].h / 2));
            setWH(sprt, text[i].w, text[i].h);
            setUV0(sprt, u, v);

            if (graph.scr_fade > 0)
            {
                if (alpha >= 128)
                {
                    setRGB0(sprt,
                            (u_char)(((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(sprt, (u_char)(((((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7));
                }
            }
            else
            {
                setRGB0(sprt, 0, 0, 0);
            }

            sprt->clut = text[i].clut;

            addPrim(graph.ot[graph.db][OTz], sprt);
            setSemiTrans(sprt, alpha >= 128 ? 0 : 1);
            graph.nextpri += sizeof(SPRT);

            tpage = (DR_TPAGE *)graph.nextpri;
            setDrawTPage(tpage, 0, 1, getTPage(0, alpha >= 128 ? 0 : 1, text[i].tpage_x, text[i].tpage_y));
            addPrim(graph.ot[graph.db][OTz], tpage);

            graph.nextpri += sizeof(DR_TPAGE);

            a += text[i].w;

            if (i < size - 1)
            {
                i++;
            }
        }
    }
    else if (align == 2)
    {
        while (a < x)
        {
            SPRT *sprt;
            DR_TPAGE *tpage;

            sprt = (SPRT *)graph.nextpri;
            setSprt(sprt);

            int u = text[i].u;
            int v = text[i].v;

            for (int b = 0; b < text[i].char_id; b++)
            {
                u += text[i].w;

                if (u >= text[i].mw)
                {
                    u = 0;
                    v += text[i].h;
                }

                if (v >= text[i].mh)
                {
                    return;
                }
            }

            setXY0(sprt, a, y - (text[i].h / 2));
            setWH(sprt, text[i].w, text[i].h);
            setUV0(sprt, u, v);

            if (graph.scr_fade > 0)
            {
                if (alpha >= 128)
                {
                    setRGB0(sprt,
                            (u_char)(((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7),
                            (u_char)(((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7));
                }
                else
                {
                    setRGB0(sprt, (u_char)(((((unsigned short)text[i].r * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].g * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7), (u_char)(((((unsigned short)text[i].b * (unsigned short)graph.scr_fade + 64) >> 7) * (unsigned short)alpha + 64) >> 7));
                }
            }
            else
            {
                setRGB0(sprt, 0, 0, 0);
            }

            sprt->clut = text[i].clut;

            addPrim(graph.ot[graph.db][OTz], sprt);
            setSemiTrans(sprt, alpha >= 128 ? 0 : 1);
            graph.nextpri += sizeof(SPRT);

            tpage = (DR_TPAGE *)graph.nextpri;
            setDrawTPage(tpage, 0, 1, getTPage(0, alpha >= 128 ? 0 : 1, text[i].tpage_x, text[i].tpage_y));
            addPrim(graph.ot[graph.db][OTz], tpage);

            graph.nextpri += sizeof(DR_TPAGE);

            a += text[i].w;

            if (i < size - 1)
            {
                i++;
            }
        }
    }
}

void graph_inittext(TextChar *charer)
{
    charer->char_id = 0;
    charer->clut = getClut(256, 509);
    charer->tpage_x = 896;
    charer->tpage_y = 0;
    charer->w = 12;
    charer->h = 12;
    charer->u = 0;
    charer->v = 0;
    charer->mw = 252;
    charer->mh = 144;
    charer->r = 128;
    charer->g = 128;
    charer->b = 128;
}

void graph_settext(const u_char *text, TextChar *charer, u_int size)
{
    for (u_int i = 0; i < size; i++)
    {
        charer[i].char_id = text[i];
    }
}

void graph_drawtile(int x, int y, int w, int h)
{
    TILE *tile;

    tile = (TILE *)graph.nextpri;

    setTile(tile);
    setXY0(tile, x, y);
    setWH(tile, w, h);
    setRGB0(tile, 0, 0, 0);
    addPrim(graph.ot[graph.db][1], tile);

    graph.nextpri += sizeof(TILE);
}

void graph_updateCam()
{
    RotMatrix(&graph.camRot, &graph.camMat);
    ApplyMatrixLV(&graph.camMat, &graph.camPos, &graph.appl);

    TransMatrix(&graph.camMat, &graph.appl);

    // SetRotMatrix(&graph.camMat);
    // SetTransMatrix(&graph.camMat);
}

u_char graph_vsync()
{
    int current_vsync = VSync(-1);

    if (current_vsync - graph.last_vsync >= 1)
    {
        graph.delta = current_vsync - graph.last_vsync;
        graph.last_vsync = current_vsync;

        return 1;
    }

    return 0;
}