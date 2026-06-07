#include "intro.h"
#include "game.h"

void intro_init(IntroModel *intro)
{
    graph.last_vsync = VSync(-1);
    graph.scr_fade = 128;

    intro->mov.vx = 0;
    intro->mov.vy = 512;
    intro->mov.vz = 1280;
    intro->rot.vx = 0;
    intro->rot.vy = 0;
    intro->rot.vz = 0;
    intro->scl.vx = ONE / 2;
    intro->scl.vy = ONE / 2;
    intro->scl.vz = ONE / 2;

    if (LNG == 1)
    {
        intro->spr[0].alpha = 0;
        intro->spr[0].clut = getClut(256, 449);
        intro->spr[0].tpage = getTPage(0, 1, 256, 256);
        intro->spr[0].MovVector.vx = 0;
        intro->spr[0].MovVector.vy = -224 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[0].MovVector.vz = 256;
        intro->spr[0].RotVector.vx = 0;
        intro->spr[0].RotVector.vy = 0;
        intro->spr[0].RotVector.vz = 0;
        intro->spr[0].ScaleVector.vx = ONE * 2;
        intro->spr[0].ScaleVector.vy = ONE * 2;
        intro->spr[0].ScaleVector.vz = ONE * 2;
        intro->spr[0].u = 0;
        intro->spr[0].v = 0;
        intro->spr[0].w = 32;
        intro->spr[0].h = 16;
        intro->spr[0].r = 128;
        intro->spr[0].g = 128;
        intro->spr[0].b = 128;

        intro->spr[1].alpha = 0;
        intro->spr[1].clut = getClut(256, 449);
        intro->spr[1].tpage = getTPage(0, 1, 256, 256);
        intro->spr[1].MovVector.vx = -64;
        intro->spr[1].MovVector.vy = -160 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[1].MovVector.vz = 256;
        intro->spr[1].RotVector.vx = 0;
        intro->spr[1].RotVector.vy = 0;
        intro->spr[1].RotVector.vz = 0;
        intro->spr[1].ScaleVector.vx = ONE * 2;
        intro->spr[1].ScaleVector.vy = ONE * 2;
        intro->spr[1].ScaleVector.vz = ONE * 2;
        intro->spr[1].u = 32;
        intro->spr[1].v = 0;
        intro->spr[1].w = 64;
        intro->spr[1].h = 32;
        intro->spr[1].r = 128;
        intro->spr[1].g = 128;
        intro->spr[1].b = 128;

        intro->spr[2].alpha = 0;
        intro->spr[2].clut = getClut(256, 449);
        intro->spr[2].tpage = getTPage(0, 1, 256, 256);
        intro->spr[2].MovVector.vx = 64;
        intro->spr[2].MovVector.vy = -160 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[2].MovVector.vz = 256;
        intro->spr[2].RotVector.vx = 0;
        intro->spr[2].RotVector.vy = 0;
        intro->spr[2].RotVector.vz = 0;
        intro->spr[2].ScaleVector.vx = ONE * 2;
        intro->spr[2].ScaleVector.vy = ONE * 2;
        intro->spr[2].ScaleVector.vz = ONE * 2;
        intro->spr[2].u = 96;
        intro->spr[2].v = 0;
        intro->spr[2].w = 64;
        intro->spr[2].h = 32;
        intro->spr[2].r = 128;
        intro->spr[2].g = 128;
        intro->spr[2].b = 128;
    }
    else if (LNG == 0)
    {
        intro->spr[0].alpha = 0;
        intro->spr[0].clut = getClut(256, 449);
        intro->spr[0].tpage = getTPage(0, 1, 256, 256);
        intro->spr[0].MovVector.vx = 0;
        intro->spr[0].MovVector.vy = -224 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[0].MovVector.vz = 256;
        intro->spr[0].RotVector.vx = 0;
        intro->spr[0].RotVector.vy = 0;
        intro->spr[0].RotVector.vz = 0;
        intro->spr[0].ScaleVector.vx = 0;
        intro->spr[0].ScaleVector.vy = 0;
        intro->spr[0].ScaleVector.vz = 0;
        intro->spr[0].u = 0;
        intro->spr[0].v = 0;
        intro->spr[0].w = 32;
        intro->spr[0].h = 16;
        intro->spr[0].r = 128;
        intro->spr[0].g = 128;
        intro->spr[0].b = 128;

        intro->spr[1].alpha = 0;
        intro->spr[1].clut = getClut(256, 449);
        intro->spr[1].tpage = getTPage(0, 1, 256, 256);
        intro->spr[1].MovVector.vx = -80;
        intro->spr[1].MovVector.vy = -224 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[1].MovVector.vz = 256;
        intro->spr[1].RotVector.vx = 0;
        intro->spr[1].RotVector.vy = 0;
        intro->spr[1].RotVector.vz = 0;
        intro->spr[1].ScaleVector.vx = ONE * 2;
        intro->spr[1].ScaleVector.vy = ONE * 2;
        intro->spr[1].ScaleVector.vz = ONE * 2;
        intro->spr[1].u = 0;
        intro->spr[1].v = 48;
        intro->spr[1].w = 80;
        intro->spr[1].h = 32;
        intro->spr[1].r = 128;
        intro->spr[1].g = 128;
        intro->spr[1].b = 128;

        intro->spr[2].alpha = 0;
        intro->spr[2].clut = getClut(256, 449);
        intro->spr[2].tpage = getTPage(0, 1, 256, 256);
        intro->spr[2].MovVector.vx = 80;
        intro->spr[2].MovVector.vy = -224 + (REGION_CODE != 0 ? 24 : 0);
        intro->spr[2].MovVector.vz = 256;
        intro->spr[2].RotVector.vx = 0;
        intro->spr[2].RotVector.vy = 0;
        intro->spr[2].RotVector.vz = 0;
        intro->spr[2].ScaleVector.vx = ONE * 2;
        intro->spr[2].ScaleVector.vy = ONE * 2;
        intro->spr[2].ScaleVector.vz = ONE * 2;
        intro->spr[2].u = 80;
        intro->spr[2].v = 48;
        intro->spr[2].w = 80;
        intro->spr[2].h = 32;
        intro->spr[2].r = 128;
        intro->spr[2].g = 128;
        intro->spr[2].b = 128;
    }

    intro->active = TRUE;
    intro->tick = 0;
}

void intro_update(IntroModel *intro)
{
    if (intro->rot.vy > -ONE)
    {
        intro->rot.vy -= (REGION_CODE != 0 ? 16 : 20) * graph.delta;
    }
    else
    {
        intro->rot.vy = -ONE;
    }

    if (intro->mov.vz > 512)
    {
        intro->mov.vz -= (REGION_CODE != 0 ? 3 : 4) * graph.delta;
    }
    else
    {
        intro->mov.vz = 512;
    }

    game_drawmodel(0, intro->mov, intro->rot, intro->scl, 0, 0, getTPage(0, 0, 256, 0), getClut(256, 448));

    for (int i = 0; i < 3; i++)
    {
        if (intro->rot.vy == -4096)
        {
            if (intro->spr[i].alpha < 128)
            {
                intro->spr[i].alpha += graph.delta;
            }
            else
            {
                intro->spr[i].alpha = 128;
                intro->spr[i].tpage = getTPage(0, 0, 256, 256);
            }
        }

        graph_drawsprite(intro->spr[i], OTLEN - 1);
    }

    int fps = REGION_CODE == 0 ? 50 : 60;

    if (intro->tick < (fps * 9) - (fps / 2))
    {
        intro->tick += graph.delta;
    }
    else
    {
        intro->active = FALSE;
    }
}

void circus_init(IntroCircus *circ)
{
    graph.last_vsync = VSync(-1);
    graph.scr_fade = 128;

    circ->edge.alpha = 0;
    circ->edge.clut = getClut(256, 450);
    circ->edge.tpage = getTPage(0, 1, 320, 0);
    circ->edge.MovVector.vx = 128;
    circ->edge.MovVector.vy = 0;
    circ->edge.MovVector.vz = 256;
    circ->edge.RotVector.vx = 0;
    circ->edge.RotVector.vy = 0;
    circ->edge.RotVector.vz = 0;
    circ->edge.ScaleVector.vx = -(ONE * 2);
    circ->edge.ScaleVector.vy = ONE * 2;
    circ->edge.ScaleVector.vz = ONE * 2;
    circ->edge.u = 0;
    circ->edge.v = 0;
    circ->edge.w = 32;
    circ->edge.h = 32;
    circ->edge.r = 128;
    circ->edge.g = 128;
    circ->edge.b = 128;

    circ->diama.alpha = 0;
    circ->diama.clut = getClut(256, 450);
    circ->diama.tpage = getTPage(0, 1, 320, 0);
    circ->diama.MovVector.vx = 128;
    circ->diama.MovVector.vy = 64;
    circ->diama.MovVector.vz = 256;
    circ->diama.RotVector.vx = 0;
    circ->diama.RotVector.vy = 0;
    circ->diama.RotVector.vz = 0;
    circ->diama.ScaleVector.vx = -(ONE * 2);
    circ->diama.ScaleVector.vy = ONE * 2;
    circ->diama.ScaleVector.vz = ONE * 2;
    circ->diama.u = 32;
    circ->diama.v = 0;
    circ->diama.w = 32;
    circ->diama.h = 32;
    circ->diama.r = 128;
    circ->diama.g = 128;
    circ->diama.b = 128;

    circ->map1.alpha = 128;
    circ->map1.clut = getClut(256, 451);
    circ->map1.tpage = getTPage(0, 0, 384, 0);
    circ->map1.MovVector.vx = -192;
    circ->map1.MovVector.vy = 128;
    circ->map1.MovVector.vz = 256;
    circ->map1.RotVector.vx = 0;
    circ->map1.RotVector.vy = 0;
    circ->map1.RotVector.vz = 0;
    circ->map1.ScaleVector.vx = ONE * 2;
    circ->map1.ScaleVector.vy = ONE * 2;
    circ->map1.ScaleVector.vz = ONE * 2;
    circ->map1.u = 0;
    circ->map1.v = 0;
    circ->map1.w = 64;
    circ->map1.h = 64;
    circ->map1.r = 128;
    circ->map1.g = 128;
    circ->map1.b = 128;

    circ->map2.alpha = 128;
    circ->map2.clut = getClut(256, 451);
    circ->map2.tpage = getTPage(0, 0, 384, 0);
    circ->map2.MovVector.vx = -128;
    circ->map2.MovVector.vy = 64;
    circ->map2.MovVector.vz = 256;
    circ->map2.RotVector.vx = 0;
    circ->map2.RotVector.vy = 0;
    circ->map2.RotVector.vz = 0;
    circ->map2.ScaleVector.vx = ONE * 2;
    circ->map2.ScaleVector.vy = ONE * 2;
    circ->map2.ScaleVector.vz = ONE * 2;
    circ->map2.u = 64;
    circ->map2.v = 0;
    circ->map2.w = 64;
    circ->map2.h = 64;
    circ->map2.r = 128;
    circ->map2.g = 128;
    circ->map2.b = 128;

    circ->map3.alpha = 128;
    circ->map3.clut = getClut(256, 451);
    circ->map3.tpage = getTPage(0, 0, 384, 0);
    circ->map3.MovVector.vx = -128;
    circ->map3.MovVector.vy = -64;
    circ->map3.MovVector.vz = 256;
    circ->map3.RotVector.vx = 0;
    circ->map3.RotVector.vy = 0;
    circ->map3.RotVector.vz = 0;
    circ->map3.ScaleVector.vx = ONE * 2;
    circ->map3.ScaleVector.vy = ONE * 2;
    circ->map3.ScaleVector.vz = ONE * 2;
    circ->map3.u = 128;
    circ->map3.v = 0;
    circ->map3.w = 64;
    circ->map3.h = 64;
    circ->map3.r = 128;
    circ->map3.g = 128;
    circ->map3.b = 128;

    circ->map4.alpha = 128;
    circ->map4.clut = getClut(256, 451);
    circ->map4.tpage = getTPage(0, 0, 384, 0);
    circ->map4.MovVector.vx = -64;
    circ->map4.MovVector.vy = -128;
    circ->map4.MovVector.vz = 256;
    circ->map4.RotVector.vx = 0;
    circ->map4.RotVector.vy = 0;
    circ->map4.RotVector.vz = 0;
    circ->map4.ScaleVector.vx = ONE * 2;
    circ->map4.ScaleVector.vy = ONE * 2;
    circ->map4.ScaleVector.vz = ONE * 2;
    circ->map4.u = 192;
    circ->map4.v = 0;
    circ->map4.w = 64;
    circ->map4.h = 64;
    circ->map4.r = 128;
    circ->map4.g = 128;
    circ->map4.b = 128;

    circ->map5.alpha = 128;
    circ->map5.clut = getClut(256, 451);
    circ->map5.tpage = getTPage(0, 0, 384, 0);
    circ->map5.MovVector.vx = 64;
    circ->map5.MovVector.vy = -128;
    circ->map5.MovVector.vz = 256;
    circ->map5.RotVector.vx = 0;
    circ->map5.RotVector.vy = 0;
    circ->map5.RotVector.vz = 0;
    circ->map5.ScaleVector.vx = ONE * 2;
    circ->map5.ScaleVector.vy = ONE * 2;
    circ->map5.ScaleVector.vz = ONE * 2;
    circ->map5.u = 0;
    circ->map5.v = 64;
    circ->map5.w = 64;
    circ->map5.h = 64;
    circ->map5.r = 128;
    circ->map5.g = 128;
    circ->map5.b = 128;

    circ->map6.alpha = 128;
    circ->map6.clut = getClut(256, 451);
    circ->map6.tpage = getTPage(0, 0, 384, 0);
    circ->map6.MovVector.vx = 128;
    circ->map6.MovVector.vy = -64;
    circ->map6.MovVector.vz = 256;
    circ->map6.RotVector.vx = 0;
    circ->map6.RotVector.vy = 0;
    circ->map6.RotVector.vz = 0;
    circ->map6.ScaleVector.vx = ONE * 2;
    circ->map6.ScaleVector.vy = ONE * 2;
    circ->map6.ScaleVector.vz = ONE * 2;
    circ->map6.u = 64;
    circ->map6.v = 64;
    circ->map6.w = 64;
    circ->map6.h = 64;
    circ->map6.r = 128;
    circ->map6.g = 128;
    circ->map6.b = 128;

    circ->map7.alpha = 128;
    circ->map7.clut = getClut(256, 451);
    circ->map7.tpage = getTPage(0, 0, 384, 0);
    circ->map7.MovVector.vx = 128;
    circ->map7.MovVector.vy = 64;
    circ->map7.MovVector.vz = 256;
    circ->map7.RotVector.vx = 0;
    circ->map7.RotVector.vy = 0;
    circ->map7.RotVector.vz = 0;
    circ->map7.ScaleVector.vx = ONE * 2;
    circ->map7.ScaleVector.vy = ONE * 2;
    circ->map7.ScaleVector.vz = ONE * 2;
    circ->map7.u = 128;
    circ->map7.v = 64;
    circ->map7.w = 64;
    circ->map7.h = 64;
    circ->map7.r = 128;
    circ->map7.g = 128;
    circ->map7.b = 128;

    circ->map8.alpha = 128;
    circ->map8.clut = getClut(256, 451);
    circ->map8.tpage = getTPage(0, 0, 384, 0);
    circ->map8.MovVector.vx = 0;
    circ->map8.MovVector.vy = 128;
    circ->map8.MovVector.vz = 256;
    circ->map8.RotVector.vx = 0;
    circ->map8.RotVector.vy = 0;
    circ->map8.RotVector.vz = 0;
    circ->map8.ScaleVector.vx = ONE * 2;
    circ->map8.ScaleVector.vy = ONE * 2;
    circ->map8.ScaleVector.vz = ONE * 2;
    circ->map8.u = 192;
    circ->map8.v = 64;
    circ->map8.w = 64;
    circ->map8.h = 64;
    circ->map8.r = 128;
    circ->map8.g = 128;
    circ->map8.b = 128;

    circ->map9.alpha = 128;
    circ->map9.clut = getClut(256, 451);
    circ->map9.tpage = getTPage(0, 0, 384, 0);
    circ->map9.MovVector.vx = 0;
    circ->map9.MovVector.vy = 0;
    circ->map9.MovVector.vz = 256;
    circ->map9.RotVector.vx = 0;
    circ->map9.RotVector.vy = 0;
    circ->map9.RotVector.vz = 0;
    circ->map9.ScaleVector.vx = ONE * 2;
    circ->map9.ScaleVector.vy = ONE * 2;
    circ->map9.ScaleVector.vz = ONE * 2;
    circ->map9.u = 0;
    circ->map9.v = 128;
    circ->map9.w = 128;
    circ->map9.h = 128;
    circ->map9.r = 128;
    circ->map9.g = 128;
    circ->map9.b = 128;

    circ->number[0].alpha = 128;
    circ->number[0].clut = getClut(256, 450);
    circ->number[0].tpage = getTPage(0, 0, 320, 0);
    circ->number[0].MovVector.vx = 0;
    circ->number[0].MovVector.vy = 256;
    circ->number[0].MovVector.vz = 256;
    circ->number[0].RotVector.vx = 0;
    circ->number[0].RotVector.vy = 0;
    circ->number[0].RotVector.vz = 0;
    circ->number[0].ScaleVector.vx = ONE * 2;
    circ->number[0].ScaleVector.vy = ONE * 2;
    circ->number[0].ScaleVector.vz = ONE * 2;
    circ->number[0].u = 0;
    circ->number[0].v = 32;
    circ->number[0].w = 32;
    circ->number[0].h = 32;
    circ->number[0].r = 0;
    circ->number[0].g = 0;
    circ->number[0].b = 128;

    circ->number[1].alpha = 128;
    circ->number[1].clut = getClut(256, 450);
    circ->number[1].tpage = getTPage(0, 0, 320, 0);
    circ->number[1].MovVector.vx = 0;
    circ->number[1].MovVector.vy = 256;
    circ->number[1].MovVector.vz = 256;
    circ->number[1].RotVector.vx = 0;
    circ->number[1].RotVector.vy = 0;
    circ->number[1].RotVector.vz = 0;
    circ->number[1].ScaleVector.vx = ONE * 2;
    circ->number[1].ScaleVector.vy = ONE * 2;
    circ->number[1].ScaleVector.vz = ONE * 2;
    circ->number[1].u = 32;
    circ->number[1].v = 32;
    circ->number[1].w = 32;
    circ->number[1].h = 32;
    circ->number[1].r = 0;
    circ->number[1].g = 0;
    circ->number[1].b = 128;

    circ->number[2].alpha = 128;
    circ->number[2].clut = getClut(256, 450);
    circ->number[2].tpage = getTPage(0, 0, 320, 0);
    circ->number[2].MovVector.vx = 0;
    circ->number[2].MovVector.vy = 256;
    circ->number[2].MovVector.vz = 256;
    circ->number[2].RotVector.vx = 0;
    circ->number[2].RotVector.vy = 0;
    circ->number[2].RotVector.vz = 0;
    circ->number[2].ScaleVector.vx = ONE * 2;
    circ->number[2].ScaleVector.vy = ONE * 2;
    circ->number[2].ScaleVector.vz = ONE * 2;
    circ->number[2].u = 64;
    circ->number[2].v = 32;
    circ->number[2].w = 32;
    circ->number[2].h = 32;
    circ->number[2].r = 0;
    circ->number[2].g = 0;
    circ->number[2].b = 128;

    circ->number[3].alpha = 128;
    circ->number[3].clut = getClut(256, 450);
    circ->number[3].tpage = getTPage(0, 0, 320, 0);
    circ->number[3].MovVector.vx = 0;
    circ->number[3].MovVector.vy = 256;
    circ->number[3].MovVector.vz = 256;
    circ->number[3].RotVector.vx = 0;
    circ->number[3].RotVector.vy = 0;
    circ->number[3].RotVector.vz = 0;
    circ->number[3].ScaleVector.vx = ONE * 2;
    circ->number[3].ScaleVector.vy = ONE * 2;
    circ->number[3].ScaleVector.vz = ONE * 2;
    circ->number[3].u = 64;
    circ->number[3].v = 32;
    circ->number[3].w = 32;
    circ->number[3].h = 32;
    circ->number[3].r = 0;
    circ->number[3].g = 0;
    circ->number[3].b = 128;

    circ->king.alpha = 128;
    circ->king.clut = getClut(256, 450);
    circ->king.tpage = getTPage(0, 0, 320, 0);
    circ->king.MovVector.vx = 0;
    circ->king.MovVector.vy = 256;
    circ->king.MovVector.vz = 258;
    circ->king.RotVector.vx = 0;
    circ->king.RotVector.vy = 0;
    circ->king.RotVector.vz = 0;
    circ->king.ScaleVector.vx = ONE * 2;
    circ->king.ScaleVector.vy = 0;
    circ->king.ScaleVector.vz = ONE * 2;
    circ->king.u = 0;
    circ->king.v = 64;
    circ->king.w = 128;
    circ->king.h = 128;
    circ->king.r = 128;
    circ->king.g = 128;
    circ->king.b = 0;

    if (LNG == 1)
    {
        circ->king_text[0].alpha = 128;
        circ->king_text[0].clut = getClut(256, 450);
        circ->king_text[0].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[0].MovVector.vx = -128;
        circ->king_text[0].MovVector.vy = -128;
        circ->king_text[0].MovVector.vz = 256;
        circ->king_text[0].RotVector.vx = 0;
        circ->king_text[0].RotVector.vy = 0;
        circ->king_text[0].RotVector.vz = 0;
        circ->king_text[0].ScaleVector.vx = 0;
        circ->king_text[0].ScaleVector.vy = 0;
        circ->king_text[0].ScaleVector.vz = ONE * 2;
        circ->king_text[0].u = 128;
        circ->king_text[0].v = 0;
        circ->king_text[0].w = 32;
        circ->king_text[0].h = 16;
        circ->king_text[0].r = 128;
        circ->king_text[0].g = 128;
        circ->king_text[0].b = 0;

        circ->king_text[1].alpha = 128;
        circ->king_text[1].clut = getClut(256, 450);
        circ->king_text[1].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[1].MovVector.vx = -64;
        circ->king_text[1].MovVector.vy = -128;
        circ->king_text[1].MovVector.vz = 256;
        circ->king_text[1].RotVector.vx = 0;
        circ->king_text[1].RotVector.vy = 0;
        circ->king_text[1].RotVector.vz = 0;
        circ->king_text[1].ScaleVector.vx = 0;
        circ->king_text[1].ScaleVector.vy = 0;
        circ->king_text[1].ScaleVector.vz = ONE * 2;
        circ->king_text[1].u = 160;
        circ->king_text[1].v = 0;
        circ->king_text[1].w = 32;
        circ->king_text[1].h = 16;
        circ->king_text[1].r = 128;
        circ->king_text[1].g = 128;
        circ->king_text[1].b = 0;

        circ->king_text[2].alpha = 128;
        circ->king_text[2].clut = getClut(256, 450);
        circ->king_text[2].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[2].MovVector.vx = 64;
        circ->king_text[2].MovVector.vy = -128;
        circ->king_text[2].MovVector.vz = 256;
        circ->king_text[2].RotVector.vx = 0;
        circ->king_text[2].RotVector.vy = 0;
        circ->king_text[2].RotVector.vz = 0;
        circ->king_text[2].ScaleVector.vx = 0;
        circ->king_text[2].ScaleVector.vy = 0;
        circ->king_text[2].ScaleVector.vz = ONE * 2;
        circ->king_text[2].u = 192;
        circ->king_text[2].v = REGION_CODE == 2 ? 16 : 0;
        circ->king_text[2].w = 32;
        circ->king_text[2].h = 16;
        circ->king_text[2].r = 128;
        circ->king_text[2].g = 128;
        circ->king_text[2].b = 0;

        circ->king_text[3].alpha = 128;
        circ->king_text[3].clut = getClut(256, 450);
        circ->king_text[3].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[3].MovVector.vx = 128;
        circ->king_text[3].MovVector.vy = -128;
        circ->king_text[3].MovVector.vz = 256;
        circ->king_text[3].RotVector.vx = 0;
        circ->king_text[3].RotVector.vy = 0;
        circ->king_text[3].RotVector.vz = 0;
        circ->king_text[3].ScaleVector.vx = 0;
        circ->king_text[3].ScaleVector.vy = 0;
        circ->king_text[3].ScaleVector.vz = ONE * 2;
        circ->king_text[3].u = 224;
        circ->king_text[3].v = REGION_CODE == 2 ? 16 : 0;
        circ->king_text[3].w = 32;
        circ->king_text[3].h = 16;
        circ->king_text[3].r = 128;
        circ->king_text[3].g = 128;
        circ->king_text[3].b = 0;
    }
    else if (LNG == 0)
    {
        circ->king_text[0].alpha = 128;
        circ->king_text[0].clut = getClut(256, 450);
        circ->king_text[0].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[0].MovVector.vx = -128;
        circ->king_text[0].MovVector.vy = -128;
        circ->king_text[0].MovVector.vz = 256;
        circ->king_text[0].RotVector.vx = 0;
        circ->king_text[0].RotVector.vy = 0;
        circ->king_text[0].RotVector.vz = 0;
        circ->king_text[0].ScaleVector.vx = 0;
        circ->king_text[0].ScaleVector.vy = 0;
        circ->king_text[0].ScaleVector.vz = ONE * 2;
        circ->king_text[0].u = 132;
        circ->king_text[0].v = 16;
        circ->king_text[0].w = 52;
        circ->king_text[0].h = 16;
        circ->king_text[0].r = 128;
        circ->king_text[0].g = 128;
        circ->king_text[0].b = 0;

        circ->king_text[1].alpha = 128;
        circ->king_text[1].clut = getClut(256, 450);
        circ->king_text[1].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[1].MovVector.vx = 128;
        circ->king_text[1].MovVector.vy = -128;
        circ->king_text[1].MovVector.vz = 256;
        circ->king_text[1].RotVector.vx = 0;
        circ->king_text[1].RotVector.vy = 0;
        circ->king_text[1].RotVector.vz = 0;
        circ->king_text[1].ScaleVector.vx = 0;
        circ->king_text[1].ScaleVector.vy = 0;
        circ->king_text[1].ScaleVector.vz = ONE * 2;
        circ->king_text[1].u = 190;
        circ->king_text[1].v = 16;
        circ->king_text[1].w = 64;
        circ->king_text[1].h = 16;
        circ->king_text[1].r = 128;
        circ->king_text[1].g = 128;
        circ->king_text[1].b = 0;

        circ->king_text[2].alpha = 0;
        circ->king_text[2].clut = getClut(256, 450);
        circ->king_text[2].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[2].MovVector.vx = 64;
        circ->king_text[2].MovVector.vy = -128;
        circ->king_text[2].MovVector.vz = 256;
        circ->king_text[2].RotVector.vx = 0;
        circ->king_text[2].RotVector.vy = 0;
        circ->king_text[2].RotVector.vz = 0;
        circ->king_text[2].ScaleVector.vx = 0;
        circ->king_text[2].ScaleVector.vy = 0;
        circ->king_text[2].ScaleVector.vz = ONE * 2;
        circ->king_text[2].u = 192;
        circ->king_text[2].v = REGION_CODE == 2 ? 16 : 0;
        circ->king_text[2].w = 32;
        circ->king_text[2].h = 16;
        circ->king_text[2].r = 128;
        circ->king_text[2].g = 128;
        circ->king_text[2].b = 0;

        circ->king_text[3].alpha = 0;
        circ->king_text[3].clut = getClut(256, 450);
        circ->king_text[3].tpage = getTPage(0, 0, 320, 0);
        circ->king_text[3].MovVector.vx = 128;
        circ->king_text[3].MovVector.vy = -128;
        circ->king_text[3].MovVector.vz = 256;
        circ->king_text[3].RotVector.vx = 0;
        circ->king_text[3].RotVector.vy = 0;
        circ->king_text[3].RotVector.vz = 0;
        circ->king_text[3].ScaleVector.vx = 0;
        circ->king_text[3].ScaleVector.vy = 0;
        circ->king_text[3].ScaleVector.vz = ONE * 2;
        circ->king_text[3].u = 224;
        circ->king_text[3].v = REGION_CODE == 2 ? 16 : 0;
        circ->king_text[3].w = 32;
        circ->king_text[3].h = 16;
        circ->king_text[3].r = 128;
        circ->king_text[3].g = 128;
        circ->king_text[3].b = 0;
    }

    circ->redorn_head.alpha = 0;
    circ->redorn_head.clut = getClut(256, 450);
    circ->redorn_head.tpage = getTPage(0, 1, 320, 0);
    circ->redorn_head.MovVector.vx = -192;
    circ->redorn_head.MovVector.vy = -192;
    circ->redorn_head.MovVector.vz = 256;
    circ->redorn_head.RotVector.vx = 0;
    circ->redorn_head.RotVector.vy = 0;
    circ->redorn_head.RotVector.vz = 0;
    circ->redorn_head.ScaleVector.vx = ONE * 4;
    circ->redorn_head.ScaleVector.vy = ONE * 4;
    circ->redorn_head.ScaleVector.vz = ONE * 4;
    circ->redorn_head.u = 64;
    circ->redorn_head.v = 0;
    circ->redorn_head.w = 32;
    circ->redorn_head.h = 32;
    circ->redorn_head.r = 128;
    circ->redorn_head.g = 128;
    circ->redorn_head.b = 128;

    circ->legend.alpha = 128;
    circ->legend.clut = getClut(256, 450);
    circ->legend.tpage = getTPage(0, 0, 320, 0);
    circ->legend.MovVector.vx = 0;
    circ->legend.MovVector.vy = 0;
    circ->legend.MovVector.vz = 256;
    circ->legend.RotVector.vx = 0;
    circ->legend.RotVector.vy = 0;
    circ->legend.RotVector.vz = 0;
    circ->legend.ScaleVector.vx = 0;
    circ->legend.ScaleVector.vy = 0;
    circ->legend.ScaleVector.vz = ONE * 2;
    circ->legend.u = 128;
    circ->legend.v = 32;
    circ->legend.w = 128;
    circ->legend.h = 128;
    circ->legend.r = 128;
    circ->legend.g = 128;
    circ->legend.b = 128;

    circ->secret.alpha = 128;
    circ->secret.clut = getClut(256, 450);
    circ->secret.tpage = getTPage(0, 0, 320, 0);
    circ->secret.MovVector.vx = -128;
    circ->secret.MovVector.vy = -64;
    circ->secret.MovVector.vz = 256;
    circ->secret.RotVector.vx = 0;
    circ->secret.RotVector.vy = 0;
    circ->secret.RotVector.vz = 0;
    circ->secret.ScaleVector.vx = ONE * 2;
    circ->secret.ScaleVector.vy = ONE * 2;
    circ->secret.ScaleVector.vz = ONE * 2;
    circ->secret.u = 128;
    circ->secret.v = 160;
    circ->secret.w = 32;
    circ->secret.h = 32;
    circ->secret.r = 64;
    circ->secret.g = 0;
    circ->secret.b = 128;

    circ->witness.alpha = 0;
    circ->witness.clut = getClut(256, 450);
    circ->witness.tpage = getTPage(0, 1, 320, 0);
    circ->witness.MovVector.vx = 128;
    circ->witness.MovVector.vy = 0;
    circ->witness.MovVector.vz = 256;
    circ->witness.RotVector.vx = 0;
    circ->witness.RotVector.vy = 0;
    circ->witness.RotVector.vz = 0;
    circ->witness.ScaleVector.vx = (ONE * 8) - 1;
    circ->witness.ScaleVector.vy = (ONE * 8) - 1;
    circ->witness.ScaleVector.vz = (ONE * 8) - 1;
    circ->witness.u = 160;
    circ->witness.v = 160;
    circ->witness.w = 32;
    circ->witness.h = 32;
    circ->witness.r = 0;
    circ->witness.g = 64;
    circ->witness.b = 128;

    circ->scenario = 0;
    circ->active = TRUE;
    circ->tick = 0;
    circ->num_s = 0;
    circ->king_s = 0;
}

void circus_update(IntroCircus *circ)
{
    int fps = REGION_CODE == 0 ? 50 : 60;

    switch (circ->scenario)
    {
    case 0:
    {
        if (circ->edge.alpha < 128)
        {
            circ->edge.alpha += 2 * graph.delta;
        }
        else
        {
            circ->edge.alpha = 128;
            circ->edge.tpage = getTPage(0, 0, 320, 0);
        }

        graph_drawsprite(circ->edge, -1);

        graph_drawback(getTPage(0, 0, 960, 0), getClut(256, 510));

        if (circ->tick < fps * 2)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->tick = 0;
            circ->scenario++;
            circ->edge.ScaleVector.vx = ONE * 2;
            circ->edge.MovVector.vx = -128;
            circ->edge.MovVector.vy = 64;
        }

        break;
    }
    case 1:
    {
        if (circ->diama.alpha < 128)
        {
            circ->diama.alpha += 2 * graph.delta;
        }
        else
        {
            circ->diama.alpha = 128;
            circ->diama.tpage = getTPage(0, 0, 320, 0);
        }

        graph_drawsprite(circ->edge, -1);
        graph_drawsprite(circ->diama, -1);

        graph_drawsprite(circ->map1, -1);
        graph_drawsprite(circ->map2, -1);
        graph_drawsprite(circ->map3, -1);
        graph_drawsprite(circ->map4, -1);
        graph_drawsprite(circ->map5, -1);
        graph_drawsprite(circ->map6, -1);
        graph_drawsprite(circ->map7, -1);
        graph_drawsprite(circ->map8, -1);
        graph_drawsprite(circ->map9, -1);

        graph_drawback(getTPage(0, 0, 960, 256), getClut(256, 511));

        if (circ->tick < fps * 3)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->tick = 0;
            circ->scenario++;
            circ->edge.alpha = 0;
            circ->edge.tpage = getTPage(0, 1, 320, 0);
            circ->edge.MovVector.vx = -128;
            circ->edge.MovVector.vy = 0;
            circ->edge.ScaleVector.vx = ONE * 2;
            circ->diama.alpha = 0;
            circ->diama.tpage = getTPage(0, 1, 320, 0);
            circ->diama.MovVector.vx = 128;
            circ->diama.MovVector.vy = 0;
            circ->diama.ScaleVector.vx = -(ONE * 2);
        }

        break;
    }
    case 2:
    {
        switch (circ->num_s)
        {
        case 0:
        {
            circ->number[0].MovVector.vy -= 16 * graph.delta;
            circ->number[1].MovVector.vy -= 16 * graph.delta;
            circ->number[2].MovVector.vy -= 16 * graph.delta;
            circ->number[3].MovVector.vy -= 16 * graph.delta;

            if (circ->number[0].MovVector.vy <= 0 && circ->number[1].MovVector.vy <= 0 && circ->number[2].MovVector.vy <= 0 && circ->number[3].MovVector.vy <= 0)
            {
                circ->number[0].MovVector.vy = 0;
                circ->number[1].MovVector.vy = 0;
                circ->number[2].MovVector.vy = 0;
                circ->number[3].MovVector.vy = 0;

                circ->num_s++;
            }

            break;
        }
        case 1:
        {
            circ->number[0].MovVector.vx -= 16 * graph.delta;
            circ->number[1].MovVector.vx -= 16 * graph.delta;
            circ->number[2].MovVector.vx += 16 * graph.delta;
            circ->number[3].MovVector.vx += 16 * graph.delta;

            if (circ->number[0].MovVector.vx <= -128)
            {
                circ->number[0].MovVector.vx = -128;
            }
            if (circ->number[1].MovVector.vx <= -48)
            {
                circ->number[1].MovVector.vx = -48;
            }
            if (circ->number[2].MovVector.vx >= 48)
            {
                circ->number[2].MovVector.vx = 48;
            }
            if (circ->number[3].MovVector.vx >= 128)
            {
                circ->number[3].MovVector.vx = 128;
            }

            if (circ->number[0].MovVector.vx == -128 && circ->number[1].MovVector.vx == -48 && circ->number[2].MovVector.vx == 48 && circ->number[3].MovVector.vx == 128)
            {
                circ->num_s++;
            }

            break;
        }
        case 2:
        {
            if (circ->number[0].alpha > 0)
            {
                circ->number[0].alpha -= 4 * graph.delta;
                circ->number[0].tpage = getTPage(0, 0, 320, 0);
            }

            if (circ->number[3].alpha > 0)
            {
                circ->number[3].alpha -= 4 * graph.delta;
                circ->number[3].tpage = getTPage(0, 0, 320, 0);
            }

            if (circ->edge.alpha < 128)
            {
                circ->edge.alpha += 4 * graph.delta;
            }
            else
            {
                circ->edge.alpha = 128;
                circ->edge.tpage = getTPage(0, 0, 320, 0);
            }

            if (circ->diama.alpha < 128)
            {
                circ->diama.alpha += 4 * graph.delta;
            }
            else
            {
                circ->diama.alpha = 128;
                circ->diama.tpage = getTPage(0, 0, 320, 0);
            }

            break;
        }
        }

        graph_drawsprite(circ->edge, -1);
        graph_drawsprite(circ->diama, -1);

        for (int i = 0; i < 4; i++)
        {
            graph_drawsprite(circ->number[i], -1);
        }

        if (circ->tick < fps * 2)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->tick = 0;
            circ->scenario++;
        }

        break;
    }
    case 3:
    {
        switch (circ->king_s)
        {
        case 0:
        {
            circ->king.ScaleVector.vy += 256 * graph.delta;
            circ->king.MovVector.vy -= 8 * graph.delta;

            if (circ->king.MovVector.vy < 0)
            {
                circ->king.MovVector.vy = 0;
            }

            if (circ->king.ScaleVector.vy > ONE * 2)
            {
                circ->king.ScaleVector.vy = ONE * 2;
            }

            if (circ->king.MovVector.vy == 0 && circ->king.ScaleVector.vy == ONE * 2)
            {
                circ->king_s++;
            }

            break;
        }
        case 1:
        {
            if (LNG == 1)
            {
                circ->king_text[0].ScaleVector.vx += 512 * graph.delta;
                circ->king_text[0].ScaleVector.vy += 512 * graph.delta;

                if (circ->king_text[0].ScaleVector.vx > ONE * 2)
                {
                    circ->king_text[0].ScaleVector.vx = ONE * 2;
                }

                if (circ->king_text[0].ScaleVector.vy > ONE * 2)
                {
                    circ->king_text[0].ScaleVector.vy = ONE * 2;
                }

                if (circ->king_text[0].ScaleVector.vx == ONE * 2 && circ->king_text[0].ScaleVector.vy == ONE * 2)
                {
                    circ->king_s++;
                }
            }
            else if (LNG == 0)
            {
                circ->king_text[0].ScaleVector.vx += 512 * graph.delta;
                circ->king_text[0].ScaleVector.vy += 512 * graph.delta;

                if (circ->king_text[0].ScaleVector.vx > ONE * 4)
                {
                    circ->king_text[0].ScaleVector.vx = ONE * 4;
                }

                if (circ->king_text[0].ScaleVector.vy > ONE * 4)
                {
                    circ->king_text[0].ScaleVector.vy = ONE * 4;
                }

                if (circ->king_text[0].ScaleVector.vx == ONE * 4 && circ->king_text[0].ScaleVector.vy == ONE * 4)
                {
                    circ->king_s++;
                }
            }

            break;
        }
        case 2:
        {
            if (LNG == 1)
            {
                circ->king_text[1].ScaleVector.vx += 1024 * graph.delta;
                circ->king_text[1].ScaleVector.vy += 1024 * graph.delta;

                if (circ->king_text[1].ScaleVector.vx > ONE * 4)
                {
                    circ->king_text[1].ScaleVector.vx = ONE * 4;
                }

                if (circ->king_text[1].ScaleVector.vy > ONE * 4)
                {
                    circ->king_text[1].ScaleVector.vy = ONE * 4;
                }

                if (circ->king_text[1].ScaleVector.vx == ONE * 4 && circ->king_text[1].ScaleVector.vy == ONE * 4)
                {
                    circ->king_s++;
                }
            }
            else if (LNG == 0)
            {
                circ->king_text[1].ScaleVector.vx += 512 * graph.delta;
                circ->king_text[1].ScaleVector.vy += 512 * graph.delta;

                if (circ->king_text[1].ScaleVector.vx > ONE * 4)
                {
                    circ->king_text[1].ScaleVector.vx = ONE * 4;
                }

                if (circ->king_text[1].ScaleVector.vy > ONE * 4)
                {
                    circ->king_text[1].ScaleVector.vy = ONE * 4;
                }

                if (circ->king_text[1].ScaleVector.vx == ONE * 4 && circ->king_text[1].ScaleVector.vy == ONE * 4)
                {
                    circ->king_s = 5;
                }
            }

            break;
        }
        case 3:
        {
            circ->king_text[2].ScaleVector.vx += 512 * graph.delta;
            circ->king_text[2].ScaleVector.vy += 512 * graph.delta;

            if (circ->king_text[2].ScaleVector.vx > ONE * 2)
            {
                circ->king_text[2].ScaleVector.vx = ONE * 2;
            }

            if (circ->king_text[2].ScaleVector.vy > ONE * 2)
            {
                circ->king_text[2].ScaleVector.vy = ONE * 2;
            }

            if (circ->king_text[2].ScaleVector.vx == ONE * 2 && circ->king_text[2].ScaleVector.vy == ONE * 2)
            {
                circ->king_s++;
            }

            break;
        }
        case 4:
        {
            circ->king_text[3].ScaleVector.vx += 1024 * graph.delta;
            circ->king_text[3].ScaleVector.vy += 1024 * graph.delta;

            if (circ->king_text[3].ScaleVector.vx > ONE * 4)
            {
                circ->king_text[3].ScaleVector.vx = ONE * 4;
            }

            if (circ->king_text[3].ScaleVector.vy > ONE * 4)
            {
                circ->king_text[3].ScaleVector.vy = ONE * 4;
            }

            if (circ->king_text[3].ScaleVector.vx == ONE * 4 && circ->king_text[3].ScaleVector.vy == ONE * 4)
            {
                circ->king_s++;
            }

            break;
        }
        case 5:
        {
            for (int i = 0; i < (LNG == 0 ? 2 : 4); i++)
            {
                if (circ->king_text[i].alpha > 0)
                {
                    circ->king_text[i].alpha -= 2 * graph.delta;
                    circ->king_text[i].tpage = getTPage(0, 1, 320, 0);
                }
                else
                {
                    circ->king_text[i].alpha = 0;
                }
            }

            if (circ->king.r > 63)
            {
                circ->king.r -= 2 * graph.delta;
            }
            else
            {
                circ->king.r = 63;
            }

            if (circ->king.g > 63)
            {
                circ->king.g -= 2 * graph.delta;
            }
            else
            {
                circ->king.g = 63;
            }

            if (circ->king.b < 63)
            {
                circ->king.b += 2 * graph.delta;
            }
            else
            {
                circ->king.b = 63;
            }

            if ((circ->king_text[0].alpha == 0 && circ->king_text[1].alpha == 0 && circ->king_text[2].alpha == 0 && circ->king_text[3].alpha == 0) && (circ->king.r == 63 && circ->king.g == 63 && circ->king.b == 63))
            {
                circ->king_s++;
            }

            break;
        }
        case 6:
        {
            if (circ->tick >= fps * 6)
            {
                circ->redorn_head.MovVector.vx += 2 * graph.delta;
                circ->redorn_head.MovVector.vy += 2 * graph.delta;

                if (circ->redorn_head.alpha < 128)
                {
                    circ->redorn_head.alpha += 2 * graph.delta;
                }
                else
                {
                    circ->redorn_head.alpha = 128;
                    circ->redorn_head.tpage = getTPage(0, 0, 320, 0);
                }

                if (circ->redorn_head.MovVector.vx > -128)
                {
                    circ->redorn_head.MovVector.vx = -128;
                }

                if (circ->redorn_head.MovVector.vy > -128)
                {
                    circ->redorn_head.MovVector.vy = -128;
                }
            }

            break;
        }
        }

        graph_drawsprite(circ->king, -1);

        for (int i = 0; i < 4; i++)
        {
            graph_drawsprite(circ->king_text[i], -1);
        }

        graph_drawsprite(circ->redorn_head, -1);

        if (circ->tick < fps * 9)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->tick = 0;
            circ->scenario++;
        }

        break;
    }
    case 4:
    {
        circ->legend.ScaleVector.vx += 512 * graph.delta;
        circ->legend.ScaleVector.vy += 512 * graph.delta;

        if (circ->legend.ScaleVector.vx > ONE * 2)
        {
            circ->legend.ScaleVector.vx = ONE * 2;
        }
        if (circ->legend.ScaleVector.vy > ONE * 2)
        {
            circ->legend.ScaleVector.vy = ONE * 2;
        }

        graph_drawsprite(circ->legend, -1);

        if (circ->tick < fps * 2)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->tick = 0;
            circ->scenario++;
        }

        break;
    }
    case 5:
    {
        if (circ->tick >= fps * 3 && circ->tick < fps * 5)
        {
            if (circ->witness.alpha < 128)
            {
                circ->witness.alpha += 4 * graph.delta;
            }
            else
            {
                circ->witness.alpha = 128;
                circ->witness.tpage = getTPage(0, 0, 320, 0);
            }
        }

        if (circ->tick < fps * 3)
        {
            graph_drawback(getTPage(0, 0, 960, 0), getClut(256, 510));
        }

        if (circ->tick >= fps * 5)
        {
            if (circ->witness.alpha > 0)
            {
                circ->witness.alpha -= 4 * graph.delta;
                circ->witness.tpage = getTPage(0, 1, 320, 0);
            }
            else
            {
                circ->witness.alpha = 0;
            }

            if (circ->secret.alpha > 0)
            {
                circ->secret.alpha -= 4 * graph.delta;
                circ->secret.tpage = getTPage(0, 1, 320, 0);
            }
            else
            {
                circ->secret.alpha = 0;
            }
        }

        if (circ->tick < fps * 6)
        {
            circ->tick += graph.delta;
        }
        else
        {
            circ->active = FALSE;
        }

        graph_drawsprite(circ->secret, -1);
        graph_drawsprite(circ->witness, -1);

        break;
    }
    }
}

void title_init(IntroTitle *title)
{
    graph.last_vsync = VSync(-1);
    graph.scr_fade = 128;
    
    title->mov.vx = 0;
    title->mov.vy = 4352;
    title->mov.vz = 512;
    title->rot.vx = 0;
    title->rot.vy = 0;
    title->rot.vz = 0;
    title->scl.vx = ONE / 2;
    title->scl.vy = ONE / 2;
    title->scl.vz = ONE / 2;

    title->spr[0].alpha = 128;
    title->spr[0].clut = getClut(256, 449);
    title->spr[0].tpage = getTPage(0, 0, 256, 256);
    title->spr[0].MovVector.vx = 384;
    title->spr[0].MovVector.vy = -224 + (REGION_CODE != 0 ? 24 : 0);
    title->spr[0].MovVector.vz = 256;
    title->spr[0].RotVector.vx = 0;
    title->spr[0].RotVector.vy = 0;
    title->spr[0].RotVector.vz = 0;
    title->spr[0].ScaleVector.vx = ONE * 2;
    title->spr[0].ScaleVector.vy = ONE * 2;
    title->spr[0].ScaleVector.vz = ONE * 2;
    title->spr[0].u = 0;
    title->spr[0].v = 32;
    title->spr[0].w = 80;
    title->spr[0].h = 16;
    title->spr[0].r = 128;
    title->spr[0].g = 128;
    title->spr[0].b = 128;

    if (LNG == 1)
    {
        title->spr[1].alpha = 128;
        title->spr[1].clut = getClut(256, 449);
        title->spr[1].tpage = getTPage(0, 0, 256, 256);
        title->spr[1].MovVector.vx = 0;
        title->spr[1].MovVector.vy = -192 + (REGION_CODE != 0 ? 24 : 0);
        title->spr[1].MovVector.vz = 256;
        title->spr[1].RotVector.vx = 0;
        title->spr[1].RotVector.vy = 0;
        title->spr[1].RotVector.vz = 0;
        title->spr[1].ScaleVector.vx = 0;
        title->spr[1].ScaleVector.vy = 0;
        title->spr[1].ScaleVector.vz = ONE * 2;
        title->spr[1].u = 0;
        title->spr[1].v = 0;
        title->spr[1].w = 32;
        title->spr[1].h = 16;
        title->spr[1].r = 128;
        title->spr[1].g = 128;
        title->spr[1].b = 128;

        title->spr[2].alpha = 128;
        title->spr[2].clut = getClut(256, 449);
        title->spr[2].tpage = getTPage(0, 0, 256, 256);
        title->spr[2].MovVector.vx = -64;
        title->spr[2].MovVector.vy = -128 + (REGION_CODE != 0 ? 24 : 0);
        title->spr[2].MovVector.vz = 256;
        title->spr[2].RotVector.vx = 0;
        title->spr[2].RotVector.vy = 0;
        title->spr[2].RotVector.vz = 0;
        title->spr[2].ScaleVector.vx = 0;
        title->spr[2].ScaleVector.vy = 0;
        title->spr[2].ScaleVector.vz = ONE * 2;
        title->spr[2].u = 32;
        title->spr[2].v = 0;
        title->spr[2].w = 64;
        title->spr[2].h = 32;
        title->spr[2].r = 128;
        title->spr[2].g = 128;
        title->spr[2].b = 128;
    }
    else if (LNG == 0)
    {
        title->spr[1].alpha = 128;
        title->spr[1].clut = getClut(256, 449);
        title->spr[1].tpage = getTPage(0, 0, 256, 256);
        title->spr[1].MovVector.vx = -384;
        title->spr[1].MovVector.vy = -192 + (REGION_CODE != 0 ? 24 : 0);
        title->spr[1].MovVector.vz = 256;
        title->spr[1].RotVector.vx = 0;
        title->spr[1].RotVector.vy = 0;
        title->spr[1].RotVector.vz = 0;
        title->spr[1].ScaleVector.vx = ONE * 2;
        title->spr[1].ScaleVector.vy = ONE * 2;
        title->spr[1].ScaleVector.vz = ONE * 2;
        title->spr[1].u = 0;
        title->spr[1].v = 48;
        title->spr[1].w = 80;
        title->spr[1].h = 32;
        title->spr[1].r = 128;
        title->spr[1].g = 128;
        title->spr[1].b = 128;

        title->spr[2].alpha = 128;
        title->spr[2].clut = getClut(256, 449);
        title->spr[2].tpage = getTPage(0, 0, 256, 256);
        title->spr[2].MovVector.vx = 384;
        title->spr[2].MovVector.vy = -192 + (REGION_CODE != 0 ? 24 : 0);
        title->spr[2].MovVector.vz = 256;
        title->spr[2].RotVector.vx = 0;
        title->spr[2].RotVector.vy = 0;
        title->spr[2].RotVector.vz = 0;
        title->spr[2].ScaleVector.vx = ONE * 2;
        title->spr[2].ScaleVector.vy = ONE * 2;
        title->spr[2].ScaleVector.vz = ONE * 2;
        title->spr[2].u = 80;
        title->spr[2].v = 48;
        title->spr[2].w = 80;
        title->spr[2].h = 32;
        title->spr[2].r = 128;
        title->spr[2].g = 128;
        title->spr[2].b = 128;
    }

    title->spr[3].alpha = 128;
    title->spr[3].clut = getClut(256, 449);
    title->spr[3].tpage = getTPage(0, 0, 256, 256);
    title->spr[3].MovVector.vx = 64;
    title->spr[3].MovVector.vy = -128 + (REGION_CODE != 0 ? 24 : 0);
    title->spr[3].MovVector.vz = 256;
    title->spr[3].RotVector.vx = 0;
    title->spr[3].RotVector.vy = 0;
    title->spr[3].RotVector.vz = 0;
    title->spr[3].ScaleVector.vx = 0;
    title->spr[3].ScaleVector.vy = 0;
    title->spr[3].ScaleVector.vz = ONE * 2;
    title->spr[3].u = 96;
    title->spr[3].v = 0;
    title->spr[3].w = 64;
    title->spr[3].h = 32;
    title->spr[3].r = 128;
    title->spr[3].g = 128;
    title->spr[3].b = 128;

    title->tick = 0;
    title->active = TRUE;
    title->title_s = 0;

    title->opt = 0;
    title->menu = 0;
    title->mus_track = 0;

    title->hor_pressed = FALSE;
    title->ver_pressed = FALSE;
    title->accept_pressed = FALSE;
    title->decline_pressed = FALSE;
    title->lockin_pressed = FALSE;

    title->camMode = FALSE;
    title->camLock = FALSE;

    title->plr2 = 1;
    title->plr3 = 0;
    title->plr4 = 0;

    if (LNG == 0)
    {
        // title->debug = NULL;

        title->opt1 = (TextChar *)malloc(7 * sizeof(TextChar));

        title->opt1[0].char_id = 42;
        title->opt1[0].clut = getClut(256, 509);
        title->opt1[0].tpage_x = 896;
        title->opt1[0].tpage_y = 0;
        title->opt1[0].w = 12;
        title->opt1[0].h = 12;
        title->opt1[0].u = 0;
        title->opt1[0].v = 0;
        title->opt1[0].mw = 252;
        title->opt1[0].mh = 144;
        title->opt1[0].r = 128;
        title->opt1[0].g = 128;
        title->opt1[0].b = 128;
        title->opt1[1].char_id = 79;
        title->opt1[1].clut = getClut(256, 509);
        title->opt1[1].tpage_x = 896;
        title->opt1[1].tpage_y = 0;
        title->opt1[1].w = 12;
        title->opt1[1].h = 12;
        title->opt1[1].u = 0;
        title->opt1[1].v = 0;
        title->opt1[1].mw = 252;
        title->opt1[1].mh = 144;
        title->opt1[1].r = 128;
        title->opt1[1].g = 128;
        title->opt1[1].b = 128;
        title->opt1[2].char_id = 67;
        title->opt1[2].clut = getClut(256, 509);
        title->opt1[2].tpage_x = 896;
        title->opt1[2].tpage_y = 0;
        title->opt1[2].w = 12;
        title->opt1[2].h = 12;
        title->opt1[2].u = 0;
        title->opt1[2].v = 0;
        title->opt1[2].mw = 252;
        title->opt1[2].mh = 144;
        title->opt1[2].r = 128;
        title->opt1[2].g = 128;
        title->opt1[2].b = 128;
        title->opt1[3].char_id = 0;
        title->opt1[3].clut = getClut(256, 509);
        title->opt1[3].tpage_x = 896;
        title->opt1[3].tpage_y = 0;
        title->opt1[3].w = 12;
        title->opt1[3].h = 12;
        title->opt1[3].u = 0;
        title->opt1[3].v = 0;
        title->opt1[3].mw = 252;
        title->opt1[3].mh = 144;
        title->opt1[3].r = 128;
        title->opt1[3].g = 128;
        title->opt1[3].b = 128;
        title->opt1[4].char_id = 46;
        title->opt1[4].clut = getClut(256, 509);
        title->opt1[4].tpage_x = 896;
        title->opt1[4].tpage_y = 0;
        title->opt1[4].w = 12;
        title->opt1[4].h = 12;
        title->opt1[4].u = 0;
        title->opt1[4].v = 0;
        title->opt1[4].mw = 252;
        title->opt1[4].mh = 144;
        title->opt1[4].r = 128;
        title->opt1[4].g = 128;
        title->opt1[4].b = 128;
        title->opt1[5].char_id = 79;
        title->opt1[5].clut = getClut(256, 509);
        title->opt1[5].tpage_x = 896;
        title->opt1[5].tpage_y = 0;
        title->opt1[5].w = 12;
        title->opt1[5].h = 12;
        title->opt1[5].u = 0;
        title->opt1[5].v = 0;
        title->opt1[5].mw = 252;
        title->opt1[5].mh = 144;
        title->opt1[5].r = 128;
        title->opt1[5].g = 128;
        title->opt1[5].b = 128;
        title->opt1[6].char_id = 85;
        title->opt1[6].clut = getClut(256, 509);
        title->opt1[6].tpage_x = 896;
        title->opt1[6].tpage_y = 0;
        title->opt1[6].w = 12;
        title->opt1[6].h = 12;
        title->opt1[6].u = 0;
        title->opt1[6].v = 0;
        title->opt1[6].mw = 252;
        title->opt1[6].mh = 144;
        title->opt1[6].r = 128;
        title->opt1[6].g = 128;
        title->opt1[6].b = 128;

        title->opt2 = (TextChar *)malloc(13 * sizeof(TextChar));

        title->opt2[0].char_id = 226;
        title->opt2[0].clut = getClut(256, 509);
        title->opt2[0].tpage_x = 896;
        title->opt2[0].tpage_y = 0;
        title->opt2[0].w = 12;
        title->opt2[0].h = 12;
        title->opt2[0].u = 0;
        title->opt2[0].v = 0;
        title->opt2[0].mw = 252;
        title->opt2[0].mh = 144;
        title->opt2[0].r = 128;
        title->opt2[0].g = 128;
        title->opt2[0].b = 128;
        title->opt2[1].char_id = 78;
        title->opt2[1].clut = getClut(256, 509);
        title->opt2[1].tpage_x = 896;
        title->opt2[1].tpage_y = 0;
        title->opt2[1].w = 12;
        title->opt2[1].h = 12;
        title->opt2[1].u = 0;
        title->opt2[1].v = 0;
        title->opt2[1].mw = 252;
        title->opt2[1].mh = 144;
        title->opt2[1].r = 128;
        title->opt2[1].g = 128;
        title->opt2[1].b = 128;
        title->opt2[2].char_id = 67;
        title->opt2[2].clut = getClut(256, 509);
        title->opt2[2].tpage_x = 896;
        title->opt2[2].tpage_y = 0;
        title->opt2[2].w = 12;
        title->opt2[2].h = 12;
        title->opt2[2].u = 0;
        title->opt2[2].v = 0;
        title->opt2[2].mw = 252;
        title->opt2[2].mh = 144;
        title->opt2[2].r = 128;
        title->opt2[2].g = 128;
        title->opt2[2].b = 128;
        title->opt2[3].char_id = 65;
        title->opt2[3].clut = getClut(256, 509);
        title->opt2[3].tpage_x = 896;
        title->opt2[3].tpage_y = 0;
        title->opt2[3].w = 12;
        title->opt2[3].h = 12;
        title->opt2[3].u = 0;
        title->opt2[3].v = 0;
        title->opt2[3].mw = 252;
        title->opt2[3].mh = 144;
        title->opt2[3].r = 128;
        title->opt2[3].g = 128;
        title->opt2[3].b = 128;
        title->opt2[4].char_id = 82;
        title->opt2[4].clut = getClut(256, 509);
        title->opt2[4].tpage_x = 896;
        title->opt2[4].tpage_y = 0;
        title->opt2[4].w = 12;
        title->opt2[4].h = 12;
        title->opt2[4].u = 0;
        title->opt2[4].v = 0;
        title->opt2[4].mw = 252;
        title->opt2[4].mh = 144;
        title->opt2[4].r = 128;
        title->opt2[4].g = 128;
        title->opt2[4].b = 128;
        title->opt2[5].char_id = 67;
        title->opt2[5].clut = getClut(256, 509);
        title->opt2[5].tpage_x = 896;
        title->opt2[5].tpage_y = 0;
        title->opt2[5].w = 12;
        title->opt2[5].h = 12;
        title->opt2[5].u = 0;
        title->opt2[5].v = 0;
        title->opt2[5].mw = 252;
        title->opt2[5].mh = 144;
        title->opt2[5].r = 128;
        title->opt2[5].g = 128;
        title->opt2[5].b = 128;
        title->opt2[6].char_id = 229;
        title->opt2[6].clut = getClut(256, 509);
        title->opt2[6].tpage_x = 896;
        title->opt2[6].tpage_y = 0;
        title->opt2[6].w = 12;
        title->opt2[6].h = 12;
        title->opt2[6].u = 0;
        title->opt2[6].v = 0;
        title->opt2[6].mw = 252;
        title->opt2[6].mh = 144;
        title->opt2[6].r = 128;
        title->opt2[6].g = 128;
        title->opt2[6].b = 128;
        title->opt2[7].char_id = 0;
        title->opt2[7].clut = getClut(256, 509);
        title->opt2[7].tpage_x = 896;
        title->opt2[7].tpage_y = 0;
        title->opt2[7].w = 12;
        title->opt2[7].h = 12;
        title->opt2[7].u = 0;
        title->opt2[7].v = 0;
        title->opt2[7].mw = 252;
        title->opt2[7].mh = 144;
        title->opt2[7].r = 128;
        title->opt2[7].g = 128;
        title->opt2[7].b = 128;
        title->opt2[8].char_id = 42;
        title->opt2[8].clut = getClut(256, 509);
        title->opt2[8].tpage_x = 896;
        title->opt2[8].tpage_y = 0;
        title->opt2[8].w = 12;
        title->opt2[8].h = 12;
        title->opt2[8].u = 0;
        title->opt2[8].v = 0;
        title->opt2[8].mw = 252;
        title->opt2[8].mh = 144;
        title->opt2[8].r = 128;
        title->opt2[8].g = 128;
        title->opt2[8].b = 128;
        title->opt2[9].char_id = 79;
        title->opt2[9].clut = getClut(256, 509);
        title->opt2[9].tpage_x = 896;
        title->opt2[9].tpage_y = 0;
        title->opt2[9].w = 12;
        title->opt2[9].h = 12;
        title->opt2[9].u = 0;
        title->opt2[9].v = 0;
        title->opt2[9].mw = 252;
        title->opt2[9].mh = 144;
        title->opt2[9].r = 128;
        title->opt2[9].g = 128;
        title->opt2[9].b = 128;
        title->opt2[10].char_id = 67;
        title->opt2[10].clut = getClut(256, 509);
        title->opt2[10].tpage_x = 896;
        title->opt2[10].tpage_y = 0;
        title->opt2[10].w = 12;
        title->opt2[10].h = 12;
        title->opt2[10].u = 0;
        title->opt2[10].v = 0;
        title->opt2[10].mw = 252;
        title->opt2[10].mh = 144;
        title->opt2[10].r = 128;
        title->opt2[10].g = 128;
        title->opt2[10].b = 128;
        title->opt2[11].char_id = 85;
        title->opt2[11].clut = getClut(256, 509);
        title->opt2[11].tpage_x = 896;
        title->opt2[11].tpage_y = 0;
        title->opt2[11].w = 12;
        title->opt2[11].h = 12;
        title->opt2[11].u = 0;
        title->opt2[11].v = 0;
        title->opt2[11].mw = 252;
        title->opt2[11].mh = 144;
        title->opt2[11].r = 128;
        title->opt2[11].g = 128;
        title->opt2[11].b = 128;
        title->opt2[12].char_id = 76;
        title->opt2[12].clut = getClut(256, 509);
        title->opt2[12].tpage_x = 896;
        title->opt2[12].tpage_y = 0;
        title->opt2[12].w = 12;
        title->opt2[12].h = 12;
        title->opt2[12].u = 0;
        title->opt2[12].v = 0;
        title->opt2[12].mw = 252;
        title->opt2[12].mh = 144;
        title->opt2[12].r = 128;
        title->opt2[12].g = 128;
        title->opt2[12].b = 128;

        title->opt3 = (TextChar *)malloc(13 * sizeof(TextChar));

        title->opt3[0].char_id = 45;
        title->opt3[0].clut = getClut(256, 509);
        title->opt3[0].tpage_x = 896;
        title->opt3[0].tpage_y = 0;
        title->opt3[0].w = 12;
        title->opt3[0].h = 12;
        title->opt3[0].u = 0;
        title->opt3[0].v = 0;
        title->opt3[0].mw = 252;
        title->opt3[0].mh = 144;
        title->opt3[0].r = 128;
        title->opt3[0].g = 128;
        title->opt3[0].b = 128;
        title->opt3[1].char_id = 85;
        title->opt3[1].clut = getClut(256, 509);
        title->opt3[1].tpage_x = 896;
        title->opt3[1].tpage_y = 0;
        title->opt3[1].w = 12;
        title->opt3[1].h = 12;
        title->opt3[1].u = 0;
        title->opt3[1].v = 0;
        title->opt3[1].mw = 252;
        title->opt3[1].mh = 144;
        title->opt3[1].r = 128;
        title->opt3[1].g = 128;
        title->opt3[1].b = 128;
        title->opt3[2].char_id = 76;
        title->opt3[2].clut = getClut(256, 509);
        title->opt3[2].tpage_x = 896;
        title->opt3[2].tpage_y = 0;
        title->opt3[2].w = 12;
        title->opt3[2].h = 12;
        title->opt3[2].u = 0;
        title->opt3[2].v = 0;
        title->opt3[2].mw = 252;
        title->opt3[2].mh = 144;
        title->opt3[2].r = 128;
        title->opt3[2].g = 128;
        title->opt3[2].b = 128;
        title->opt3[3].char_id = 84;
        title->opt3[3].clut = getClut(256, 509);
        title->opt3[3].tpage_x = 896;
        title->opt3[3].tpage_y = 0;
        title->opt3[3].w = 12;
        title->opt3[3].h = 12;
        title->opt3[3].u = 0;
        title->opt3[3].v = 0;
        title->opt3[3].mw = 252;
        title->opt3[3].mh = 144;
        title->opt3[3].r = 128;
        title->opt3[3].g = 128;
        title->opt3[3].b = 128;
        title->opt3[4].char_id = 73;
        title->opt3[4].clut = getClut(256, 509);
        title->opt3[4].tpage_x = 896;
        title->opt3[4].tpage_y = 0;
        title->opt3[4].w = 12;
        title->opt3[4].h = 12;
        title->opt3[4].u = 0;
        title->opt3[4].v = 0;
        title->opt3[4].mw = 252;
        title->opt3[4].mh = 144;
        title->opt3[4].r = 128;
        title->opt3[4].g = 128;
        title->opt3[4].b = 128;
        title->opt3[5].char_id = 74;
        title->opt3[5].clut = getClut(256, 509);
        title->opt3[5].tpage_x = 896;
        title->opt3[5].tpage_y = 0;
        title->opt3[5].w = 12;
        title->opt3[5].h = 12;
        title->opt3[5].u = 0;
        title->opt3[5].v = 0;
        title->opt3[5].mw = 252;
        title->opt3[5].mh = 144;
        title->opt3[5].r = 128;
        title->opt3[5].g = 128;
        title->opt3[5].b = 128;
        title->opt3[6].char_id = 85;
        title->opt3[6].clut = getClut(256, 509);
        title->opt3[6].tpage_x = 896;
        title->opt3[6].tpage_y = 0;
        title->opt3[6].w = 12;
        title->opt3[6].h = 12;
        title->opt3[6].u = 0;
        title->opt3[6].v = 0;
        title->opt3[6].mw = 252;
        title->opt3[6].mh = 144;
        title->opt3[6].r = 128;
        title->opt3[6].g = 128;
        title->opt3[6].b = 128;
        title->opt3[7].char_id = 67;
        title->opt3[7].clut = getClut(256, 509);
        title->opt3[7].tpage_x = 896;
        title->opt3[7].tpage_y = 0;
        title->opt3[7].w = 12;
        title->opt3[7].h = 12;
        title->opt3[7].u = 0;
        title->opt3[7].v = 0;
        title->opt3[7].mw = 252;
        title->opt3[7].mh = 144;
        title->opt3[7].r = 128;
        title->opt3[7].g = 128;
        title->opt3[7].b = 128;
        title->opt3[8].char_id = 229;
        title->opt3[8].clut = getClut(256, 509);
        title->opt3[8].tpage_x = 896;
        title->opt3[8].tpage_y = 0;
        title->opt3[8].w = 12;
        title->opt3[8].h = 12;
        title->opt3[8].u = 0;
        title->opt3[8].v = 0;
        title->opt3[8].mw = 252;
        title->opt3[8].mh = 144;
        title->opt3[8].r = 128;
        title->opt3[8].g = 128;
        title->opt3[8].b = 128;
        title->opt3[9].char_id = 84;
        title->opt3[9].clut = getClut(256, 509);
        title->opt3[9].tpage_x = 896;
        title->opt3[9].tpage_y = 0;
        title->opt3[9].w = 12;
        title->opt3[9].h = 12;
        title->opt3[9].u = 0;
        title->opt3[9].v = 0;
        title->opt3[9].mw = 252;
        title->opt3[9].mh = 144;
        title->opt3[9].r = 128;
        title->opt3[9].g = 128;
        title->opt3[9].b = 128;
        title->opt3[10].char_id = 79;
        title->opt3[10].clut = getClut(256, 509);
        title->opt3[10].tpage_x = 896;
        title->opt3[10].tpage_y = 0;
        title->opt3[10].w = 12;
        title->opt3[10].h = 12;
        title->opt3[10].u = 0;
        title->opt3[10].v = 0;
        title->opt3[10].mw = 252;
        title->opt3[10].mh = 144;
        title->opt3[10].r = 128;
        title->opt3[10].g = 128;
        title->opt3[10].b = 128;
        title->opt3[11].char_id = 82;
        title->opt3[11].clut = getClut(256, 509);
        title->opt3[11].tpage_x = 896;
        title->opt3[11].tpage_y = 0;
        title->opt3[11].w = 12;
        title->opt3[11].h = 12;
        title->opt3[11].u = 0;
        title->opt3[11].v = 0;
        title->opt3[11].mw = 252;
        title->opt3[11].mh = 144;
        title->opt3[11].r = 128;
        title->opt3[11].g = 128;
        title->opt3[11].b = 128;
        title->opt3[12].char_id = 73;
        title->opt3[12].clut = getClut(256, 509);
        title->opt3[12].tpage_x = 896;
        title->opt3[12].tpage_y = 0;
        title->opt3[12].w = 12;
        title->opt3[12].h = 12;
        title->opt3[12].u = 0;
        title->opt3[12].v = 0;
        title->opt3[12].mw = 252;
        title->opt3[12].mh = 144;
        title->opt3[12].r = 128;
        title->opt3[12].g = 128;
        title->opt3[12].b = 128;

        title->tsize01 = 7;
        title->tsize02 = 13;
        title->tsize03 = 13;

        title->mp1 = (TextChar *)malloc(15 * sizeof(TextChar));

        title->mp1[0].char_id = 42;
        title->mp1[0].clut = getClut(256, 509);
        title->mp1[0].tpage_x = 896;
        title->mp1[0].tpage_y = 0;
        title->mp1[0].w = 12;
        title->mp1[0].h = 12;
        title->mp1[0].u = 0;
        title->mp1[0].v = 0;
        title->mp1[0].mw = 252;
        title->mp1[0].mh = 144;
        title->mp1[0].r = 128;
        title->mp1[0].g = 128;
        title->mp1[0].b = 128;
        title->mp1[1].char_id = 85;
        title->mp1[1].clut = getClut(256, 509);
        title->mp1[1].tpage_x = 896;
        title->mp1[1].tpage_y = 0;
        title->mp1[1].w = 12;
        title->mp1[1].h = 12;
        title->mp1[1].u = 0;
        title->mp1[1].v = 0;
        title->mp1[1].mw = 252;
        title->mp1[1].mh = 144;
        title->mp1[1].r = 128;
        title->mp1[1].g = 128;
        title->mp1[1].b = 128;
        title->mp1[2].char_id = 67;
        title->mp1[2].clut = getClut(256, 509);
        title->mp1[2].tpage_x = 896;
        title->mp1[2].tpage_y = 0;
        title->mp1[2].w = 12;
        title->mp1[2].h = 12;
        title->mp1[2].u = 0;
        title->mp1[2].v = 0;
        title->mp1[2].mw = 252;
        title->mp1[2].mh = 144;
        title->mp1[2].r = 128;
        title->mp1[2].g = 128;
        title->mp1[2].b = 128;
        title->mp1[3].char_id = 229;
        title->mp1[3].clut = getClut(256, 509);
        title->mp1[3].tpage_x = 896;
        title->mp1[3].tpage_y = 0;
        title->mp1[3].w = 12;
        title->mp1[3].h = 12;
        title->mp1[3].u = 0;
        title->mp1[3].v = 0;
        title->mp1[3].mw = 252;
        title->mp1[3].mh = 144;
        title->mp1[3].r = 128;
        title->mp1[3].g = 128;
        title->mp1[3].b = 128;
        title->mp1[4].char_id = 84;
        title->mp1[4].clut = getClut(256, 509);
        title->mp1[4].tpage_x = 896;
        title->mp1[4].tpage_y = 0;
        title->mp1[4].w = 12;
        title->mp1[4].h = 12;
        title->mp1[4].u = 0;
        title->mp1[4].v = 0;
        title->mp1[4].mw = 252;
        title->mp1[4].mh = 144;
        title->mp1[4].r = 128;
        title->mp1[4].g = 128;
        title->mp1[4].b = 128;
        title->mp1[5].char_id = 79;
        title->mp1[5].clut = getClut(256, 509);
        title->mp1[5].tpage_x = 896;
        title->mp1[5].tpage_y = 0;
        title->mp1[5].w = 12;
        title->mp1[5].h = 12;
        title->mp1[5].u = 0;
        title->mp1[5].v = 0;
        title->mp1[5].mw = 252;
        title->mp1[5].mh = 144;
        title->mp1[5].r = 128;
        title->mp1[5].g = 128;
        title->mp1[5].b = 128;
        title->mp1[6].char_id = 82;
        title->mp1[6].clut = getClut(256, 509);
        title->mp1[6].tpage_x = 896;
        title->mp1[6].tpage_y = 0;
        title->mp1[6].w = 12;
        title->mp1[6].h = 12;
        title->mp1[6].u = 0;
        title->mp1[6].v = 0;
        title->mp1[6].mw = 252;
        title->mp1[6].mh = 144;
        title->mp1[6].r = 128;
        title->mp1[6].g = 128;
        title->mp1[6].b = 128;
        title->mp1[7].char_id = 0;
        title->mp1[7].clut = getClut(256, 509);
        title->mp1[7].tpage_x = 896;
        title->mp1[7].tpage_y = 0;
        title->mp1[7].w = 12;
        title->mp1[7].h = 12;
        title->mp1[7].u = 0;
        title->mp1[7].v = 0;
        title->mp1[7].mw = 252;
        title->mp1[7].mh = 144;
        title->mp1[7].r = 128;
        title->mp1[7].g = 128;
        title->mp1[7].b = 128;
        title->mp1[8].char_id = 17;
        title->mp1[8].clut = getClut(256, 509);
        title->mp1[8].tpage_x = 896;
        title->mp1[8].tpage_y = 0;
        title->mp1[8].w = 12;
        title->mp1[8].h = 12;
        title->mp1[8].u = 0;
        title->mp1[8].v = 0;
        title->mp1[8].mw = 252;
        title->mp1[8].mh = 144;
        title->mp1[8].r = 128;
        title->mp1[8].g = 128;
        title->mp1[8].b = 128;
        title->mp1[9].char_id = 26;
        title->mp1[9].clut = getClut(256, 509);
        title->mp1[9].tpage_x = 896;
        title->mp1[9].tpage_y = 0;
        title->mp1[9].w = 12;
        title->mp1[9].h = 12;
        title->mp1[9].u = 0;
        title->mp1[9].v = 0;
        title->mp1[9].mw = 252;
        title->mp1[9].mh = 144;
        title->mp1[9].r = 128;
        title->mp1[9].g = 128;
        title->mp1[9].b = 128;
        title->mp1[10].char_id = 47;
        title->mp1[10].clut = getClut(256, 509);
        title->mp1[10].tpage_x = 896;
        title->mp1[10].tpage_y = 0;
        title->mp1[10].w = 12;
        title->mp1[10].h = 12;
        title->mp1[10].u = 0;
        title->mp1[10].v = 0;
        title->mp1[10].mw = 252;
        title->mp1[10].mh = 144;
        title->mp1[10].r = 128;
        title->mp1[10].g = 128;
        title->mp1[10].b = 128;
        title->mp1[11].char_id = 77;
        title->mp1[11].clut = getClut(256, 509);
        title->mp1[11].tpage_x = 896;
        title->mp1[11].tpage_y = 0;
        title->mp1[11].w = 12;
        title->mp1[11].h = 12;
        title->mp1[11].u = 0;
        title->mp1[11].v = 0;
        title->mp1[11].mw = 252;
        title->mp1[11].mh = 144;
        title->mp1[11].r = 128;
        title->mp1[11].g = 128;
        title->mp1[11].b = 128;
        title->mp1[12].char_id = 0;
        title->mp1[12].clut = getClut(256, 509);
        title->mp1[12].tpage_x = 896;
        title->mp1[12].tpage_y = 0;
        title->mp1[12].w = 12;
        title->mp1[12].h = 12;
        title->mp1[12].u = 0;
        title->mp1[12].v = 0;
        title->mp1[12].mw = 252;
        title->mp1[12].mh = 144;
        title->mp1[12].r = 128;
        title->mp1[12].g = 128;
        title->mp1[12].b = 128;
        title->mp1[13].char_id = 0;
        title->mp1[13].clut = getClut(256, 509);
        title->mp1[13].tpage_x = 896;
        title->mp1[13].tpage_y = 0;
        title->mp1[13].w = 12;
        title->mp1[13].h = 12;
        title->mp1[13].u = 0;
        title->mp1[13].v = 0;
        title->mp1[13].mw = 252;
        title->mp1[13].mh = 144;
        title->mp1[13].r = 128;
        title->mp1[13].g = 128;
        title->mp1[13].b = 128;
        title->mp1[14].char_id = 0;
        title->mp1[14].clut = getClut(256, 509);
        title->mp1[14].tpage_x = 896;
        title->mp1[14].tpage_y = 0;
        title->mp1[14].w = 12;
        title->mp1[14].h = 12;
        title->mp1[14].u = 0;
        title->mp1[14].v = 0;
        title->mp1[14].mw = 252;
        title->mp1[14].mh = 144;
        title->mp1[14].r = 128;
        title->mp1[14].g = 128;
        title->mp1[14].b = 128;

        title->mp2 = (TextChar *)malloc(15 * sizeof(TextChar));

        title->mp2[0].char_id = 42;
        title->mp2[0].clut = getClut(256, 509);
        title->mp2[0].tpage_x = 896;
        title->mp2[0].tpage_y = 0;
        title->mp2[0].w = 12;
        title->mp2[0].h = 12;
        title->mp2[0].u = 0;
        title->mp2[0].v = 0;
        title->mp2[0].mw = 252;
        title->mp2[0].mh = 144;
        title->mp2[0].r = 128;
        title->mp2[0].g = 128;
        title->mp2[0].b = 128;
        title->mp2[1].char_id = 85;
        title->mp2[1].clut = getClut(256, 509);
        title->mp2[1].tpage_x = 896;
        title->mp2[1].tpage_y = 0;
        title->mp2[1].w = 12;
        title->mp2[1].h = 12;
        title->mp2[1].u = 0;
        title->mp2[1].v = 0;
        title->mp2[1].mw = 252;
        title->mp2[1].mh = 144;
        title->mp2[1].r = 128;
        title->mp2[1].g = 128;
        title->mp2[1].b = 128;
        title->mp2[2].char_id = 67;
        title->mp2[2].clut = getClut(256, 509);
        title->mp2[2].tpage_x = 896;
        title->mp2[2].tpage_y = 0;
        title->mp2[2].w = 12;
        title->mp2[2].h = 12;
        title->mp2[2].u = 0;
        title->mp2[2].v = 0;
        title->mp2[2].mw = 252;
        title->mp2[2].mh = 144;
        title->mp2[2].r = 128;
        title->mp2[2].g = 128;
        title->mp2[2].b = 128;
        title->mp2[3].char_id = 229;
        title->mp2[3].clut = getClut(256, 509);
        title->mp2[3].tpage_x = 896;
        title->mp2[3].tpage_y = 0;
        title->mp2[3].w = 12;
        title->mp2[3].h = 12;
        title->mp2[3].u = 0;
        title->mp2[3].v = 0;
        title->mp2[3].mw = 252;
        title->mp2[3].mh = 144;
        title->mp2[3].r = 128;
        title->mp2[3].g = 128;
        title->mp2[3].b = 128;
        title->mp2[4].char_id = 84;
        title->mp2[4].clut = getClut(256, 509);
        title->mp2[4].tpage_x = 896;
        title->mp2[4].tpage_y = 0;
        title->mp2[4].w = 12;
        title->mp2[4].h = 12;
        title->mp2[4].u = 0;
        title->mp2[4].v = 0;
        title->mp2[4].mw = 252;
        title->mp2[4].mh = 144;
        title->mp2[4].r = 128;
        title->mp2[4].g = 128;
        title->mp2[4].b = 128;
        title->mp2[5].char_id = 79;
        title->mp2[5].clut = getClut(256, 509);
        title->mp2[5].tpage_x = 896;
        title->mp2[5].tpage_y = 0;
        title->mp2[5].w = 12;
        title->mp2[5].h = 12;
        title->mp2[5].u = 0;
        title->mp2[5].v = 0;
        title->mp2[5].mw = 252;
        title->mp2[5].mh = 144;
        title->mp2[5].r = 128;
        title->mp2[5].g = 128;
        title->mp2[5].b = 128;
        title->mp2[6].char_id = 82;
        title->mp2[6].clut = getClut(256, 509);
        title->mp2[6].tpage_x = 896;
        title->mp2[6].tpage_y = 0;
        title->mp2[6].w = 12;
        title->mp2[6].h = 12;
        title->mp2[6].u = 0;
        title->mp2[6].v = 0;
        title->mp2[6].mw = 252;
        title->mp2[6].mh = 144;
        title->mp2[6].r = 128;
        title->mp2[6].g = 128;
        title->mp2[6].b = 128;
        title->mp2[7].char_id = 0;
        title->mp2[7].clut = getClut(256, 509);
        title->mp2[7].tpage_x = 896;
        title->mp2[7].tpage_y = 0;
        title->mp2[7].w = 12;
        title->mp2[7].h = 12;
        title->mp2[7].u = 0;
        title->mp2[7].v = 0;
        title->mp2[7].mw = 252;
        title->mp2[7].mh = 144;
        title->mp2[7].r = 128;
        title->mp2[7].g = 128;
        title->mp2[7].b = 128;
        title->mp2[8].char_id = 18;
        title->mp2[8].clut = getClut(256, 509);
        title->mp2[8].tpage_x = 896;
        title->mp2[8].tpage_y = 0;
        title->mp2[8].w = 12;
        title->mp2[8].h = 12;
        title->mp2[8].u = 0;
        title->mp2[8].v = 0;
        title->mp2[8].mw = 252;
        title->mp2[8].mh = 144;
        title->mp2[8].r = 128;
        title->mp2[8].g = 128;
        title->mp2[8].b = 128;
        title->mp2[9].char_id = 26;
        title->mp2[9].clut = getClut(256, 509);
        title->mp2[9].tpage_x = 896;
        title->mp2[9].tpage_y = 0;
        title->mp2[9].w = 12;
        title->mp2[9].h = 12;
        title->mp2[9].u = 0;
        title->mp2[9].v = 0;
        title->mp2[9].mw = 252;
        title->mp2[9].mh = 144;
        title->mp2[9].r = 128;
        title->mp2[9].g = 128;
        title->mp2[9].b = 128;
        title->mp2[10].char_id = 46;
        title->mp2[10].clut = getClut(256, 509);
        title->mp2[10].tpage_x = 896;
        title->mp2[10].tpage_y = 0;
        title->mp2[10].w = 12;
        title->mp2[10].h = 12;
        title->mp2[10].u = 0;
        title->mp2[10].v = 0;
        title->mp2[10].mw = 252;
        title->mp2[10].mh = 144;
        title->mp2[10].r = 128;
        title->mp2[10].g = 128;
        title->mp2[10].b = 128;
        title->mp2[11].char_id = 73;
        title->mp2[11].clut = getClut(256, 509);
        title->mp2[11].tpage_x = 896;
        title->mp2[11].tpage_y = 0;
        title->mp2[11].w = 12;
        title->mp2[11].h = 12;
        title->mp2[11].u = 0;
        title->mp2[11].v = 0;
        title->mp2[11].mw = 252;
        title->mp2[11].mh = 144;
        title->mp2[11].r = 128;
        title->mp2[11].g = 128;
        title->mp2[11].b = 128;
        title->mp2[12].char_id = 77;
        title->mp2[12].clut = getClut(256, 509);
        title->mp2[12].tpage_x = 896;
        title->mp2[12].tpage_y = 0;
        title->mp2[12].w = 12;
        title->mp2[12].h = 12;
        title->mp2[12].u = 0;
        title->mp2[12].v = 0;
        title->mp2[12].mw = 252;
        title->mp2[12].mh = 144;
        title->mp2[12].r = 128;
        title->mp2[12].g = 128;
        title->mp2[12].b = 128;
        title->mp2[13].char_id = 73;
        title->mp2[13].clut = getClut(256, 509);
        title->mp2[13].tpage_x = 896;
        title->mp2[13].tpage_y = 0;
        title->mp2[13].w = 12;
        title->mp2[13].h = 12;
        title->mp2[13].u = 0;
        title->mp2[13].v = 0;
        title->mp2[13].mw = 252;
        title->mp2[13].mh = 144;
        title->mp2[13].r = 128;
        title->mp2[13].g = 128;
        title->mp2[13].b = 128;
        title->mp2[14].char_id = 67;
        title->mp2[14].clut = getClut(256, 509);
        title->mp2[14].tpage_x = 896;
        title->mp2[14].tpage_y = 0;
        title->mp2[14].w = 12;
        title->mp2[14].h = 12;
        title->mp2[14].u = 0;
        title->mp2[14].v = 0;
        title->mp2[14].mw = 252;
        title->mp2[14].mh = 144;
        title->mp2[14].r = 128;
        title->mp2[14].g = 128;
        title->mp2[14].b = 128;

        title->mp3 = (TextChar *)malloc(15 * sizeof(TextChar));

        title->mp3[0].char_id = 42;
        title->mp3[0].clut = getClut(256, 509);
        title->mp3[0].tpage_x = 896;
        title->mp3[0].tpage_y = 0;
        title->mp3[0].w = 12;
        title->mp3[0].h = 12;
        title->mp3[0].u = 0;
        title->mp3[0].v = 0;
        title->mp3[0].mw = 252;
        title->mp3[0].mh = 144;
        title->mp3[0].r = 128;
        title->mp3[0].g = 128;
        title->mp3[0].b = 128;
        title->mp3[1].char_id = 85;
        title->mp3[1].clut = getClut(256, 509);
        title->mp3[1].tpage_x = 896;
        title->mp3[1].tpage_y = 0;
        title->mp3[1].w = 12;
        title->mp3[1].h = 12;
        title->mp3[1].u = 0;
        title->mp3[1].v = 0;
        title->mp3[1].mw = 252;
        title->mp3[1].mh = 144;
        title->mp3[1].r = 128;
        title->mp3[1].g = 128;
        title->mp3[1].b = 128;
        title->mp3[2].char_id = 67;
        title->mp3[2].clut = getClut(256, 509);
        title->mp3[2].tpage_x = 896;
        title->mp3[2].tpage_y = 0;
        title->mp3[2].w = 12;
        title->mp3[2].h = 12;
        title->mp3[2].u = 0;
        title->mp3[2].v = 0;
        title->mp3[2].mw = 252;
        title->mp3[2].mh = 144;
        title->mp3[2].r = 128;
        title->mp3[2].g = 128;
        title->mp3[2].b = 128;
        title->mp3[3].char_id = 229;
        title->mp3[3].clut = getClut(256, 509);
        title->mp3[3].tpage_x = 896;
        title->mp3[3].tpage_y = 0;
        title->mp3[3].w = 12;
        title->mp3[3].h = 12;
        title->mp3[3].u = 0;
        title->mp3[3].v = 0;
        title->mp3[3].mw = 252;
        title->mp3[3].mh = 144;
        title->mp3[3].r = 128;
        title->mp3[3].g = 128;
        title->mp3[3].b = 128;
        title->mp3[4].char_id = 84;
        title->mp3[4].clut = getClut(256, 509);
        title->mp3[4].tpage_x = 896;
        title->mp3[4].tpage_y = 0;
        title->mp3[4].w = 12;
        title->mp3[4].h = 12;
        title->mp3[4].u = 0;
        title->mp3[4].v = 0;
        title->mp3[4].mw = 252;
        title->mp3[4].mh = 144;
        title->mp3[4].r = 128;
        title->mp3[4].g = 128;
        title->mp3[4].b = 128;
        title->mp3[5].char_id = 79;
        title->mp3[5].clut = getClut(256, 509);
        title->mp3[5].tpage_x = 896;
        title->mp3[5].tpage_y = 0;
        title->mp3[5].w = 12;
        title->mp3[5].h = 12;
        title->mp3[5].u = 0;
        title->mp3[5].v = 0;
        title->mp3[5].mw = 252;
        title->mp3[5].mh = 144;
        title->mp3[5].r = 128;
        title->mp3[5].g = 128;
        title->mp3[5].b = 128;
        title->mp3[6].char_id = 82;
        title->mp3[6].clut = getClut(256, 509);
        title->mp3[6].tpage_x = 896;
        title->mp3[6].tpage_y = 0;
        title->mp3[6].w = 12;
        title->mp3[6].h = 12;
        title->mp3[6].u = 0;
        title->mp3[6].v = 0;
        title->mp3[6].mw = 252;
        title->mp3[6].mh = 144;
        title->mp3[6].r = 128;
        title->mp3[6].g = 128;
        title->mp3[6].b = 128;
        title->mp3[7].char_id = 0;
        title->mp3[7].clut = getClut(256, 509);
        title->mp3[7].tpage_x = 896;
        title->mp3[7].tpage_y = 0;
        title->mp3[7].w = 12;
        title->mp3[7].h = 12;
        title->mp3[7].u = 0;
        title->mp3[7].v = 0;
        title->mp3[7].mw = 252;
        title->mp3[7].mh = 144;
        title->mp3[7].r = 128;
        title->mp3[7].g = 128;
        title->mp3[7].b = 128;
        title->mp3[8].char_id = 19;
        title->mp3[8].clut = getClut(256, 509);
        title->mp3[8].tpage_x = 896;
        title->mp3[8].tpage_y = 0;
        title->mp3[8].w = 12;
        title->mp3[8].h = 12;
        title->mp3[8].u = 0;
        title->mp3[8].v = 0;
        title->mp3[8].mw = 252;
        title->mp3[8].mh = 144;
        title->mp3[8].r = 128;
        title->mp3[8].g = 128;
        title->mp3[8].b = 128;
        title->mp3[9].char_id = 26;
        title->mp3[9].clut = getClut(256, 509);
        title->mp3[9].tpage_x = 896;
        title->mp3[9].tpage_y = 0;
        title->mp3[9].w = 12;
        title->mp3[9].h = 12;
        title->mp3[9].u = 0;
        title->mp3[9].v = 0;
        title->mp3[9].mw = 252;
        title->mp3[9].mh = 144;
        title->mp3[9].r = 128;
        title->mp3[9].g = 128;
        title->mp3[9].b = 128;
        title->mp3[10].char_id = 46;
        title->mp3[10].clut = getClut(256, 509);
        title->mp3[10].tpage_x = 896;
        title->mp3[10].tpage_y = 0;
        title->mp3[10].w = 12;
        title->mp3[10].h = 12;
        title->mp3[10].u = 0;
        title->mp3[10].v = 0;
        title->mp3[10].mw = 252;
        title->mp3[10].mh = 144;
        title->mp3[10].r = 128;
        title->mp3[10].g = 128;
        title->mp3[10].b = 128;
        title->mp3[11].char_id = 73;
        title->mp3[11].clut = getClut(256, 509);
        title->mp3[11].tpage_x = 896;
        title->mp3[11].tpage_y = 0;
        title->mp3[11].w = 12;
        title->mp3[11].h = 12;
        title->mp3[11].u = 0;
        title->mp3[11].v = 0;
        title->mp3[11].mw = 252;
        title->mp3[11].mh = 144;
        title->mp3[11].r = 128;
        title->mp3[11].g = 128;
        title->mp3[11].b = 128;
        title->mp3[12].char_id = 77;
        title->mp3[12].clut = getClut(256, 509);
        title->mp3[12].tpage_x = 896;
        title->mp3[12].tpage_y = 0;
        title->mp3[12].w = 12;
        title->mp3[12].h = 12;
        title->mp3[12].u = 0;
        title->mp3[12].v = 0;
        title->mp3[12].mw = 252;
        title->mp3[12].mh = 144;
        title->mp3[12].r = 128;
        title->mp3[12].g = 128;
        title->mp3[12].b = 128;
        title->mp3[13].char_id = 73;
        title->mp3[13].clut = getClut(256, 509);
        title->mp3[13].tpage_x = 896;
        title->mp3[13].tpage_y = 0;
        title->mp3[13].w = 12;
        title->mp3[13].h = 12;
        title->mp3[13].u = 0;
        title->mp3[13].v = 0;
        title->mp3[13].mw = 252;
        title->mp3[13].mh = 144;
        title->mp3[13].r = 128;
        title->mp3[13].g = 128;
        title->mp3[13].b = 128;
        title->mp3[14].char_id = 67;
        title->mp3[14].clut = getClut(256, 509);
        title->mp3[14].tpage_x = 896;
        title->mp3[14].tpage_y = 0;
        title->mp3[14].w = 12;
        title->mp3[14].h = 12;
        title->mp3[14].u = 0;
        title->mp3[14].v = 0;
        title->mp3[14].mw = 252;
        title->mp3[14].mh = 144;
        title->mp3[14].r = 128;
        title->mp3[14].g = 128;
        title->mp3[14].b = 128;

        title->mp4 = (TextChar *)malloc(15 * sizeof(TextChar));

        title->mp4[0].char_id = 42;
        title->mp4[0].clut = getClut(256, 509);
        title->mp4[0].tpage_x = 896;
        title->mp4[0].tpage_y = 0;
        title->mp4[0].w = 12;
        title->mp4[0].h = 12;
        title->mp4[0].u = 0;
        title->mp4[0].v = 0;
        title->mp4[0].mw = 252;
        title->mp4[0].mh = 144;
        title->mp4[0].r = 128;
        title->mp4[0].g = 128;
        title->mp4[0].b = 128;
        title->mp4[1].char_id = 85;
        title->mp4[1].clut = getClut(256, 509);
        title->mp4[1].tpage_x = 896;
        title->mp4[1].tpage_y = 0;
        title->mp4[1].w = 12;
        title->mp4[1].h = 12;
        title->mp4[1].u = 0;
        title->mp4[1].v = 0;
        title->mp4[1].mw = 252;
        title->mp4[1].mh = 144;
        title->mp4[1].r = 128;
        title->mp4[1].g = 128;
        title->mp4[1].b = 128;
        title->mp4[2].char_id = 67;
        title->mp4[2].clut = getClut(256, 509);
        title->mp4[2].tpage_x = 896;
        title->mp4[2].tpage_y = 0;
        title->mp4[2].w = 12;
        title->mp4[2].h = 12;
        title->mp4[2].u = 0;
        title->mp4[2].v = 0;
        title->mp4[2].mw = 252;
        title->mp4[2].mh = 144;
        title->mp4[2].r = 128;
        title->mp4[2].g = 128;
        title->mp4[2].b = 128;
        title->mp4[3].char_id = 229;
        title->mp4[3].clut = getClut(256, 509);
        title->mp4[3].tpage_x = 896;
        title->mp4[3].tpage_y = 0;
        title->mp4[3].w = 12;
        title->mp4[3].h = 12;
        title->mp4[3].u = 0;
        title->mp4[3].v = 0;
        title->mp4[3].mw = 252;
        title->mp4[3].mh = 144;
        title->mp4[3].r = 128;
        title->mp4[3].g = 128;
        title->mp4[3].b = 128;
        title->mp4[4].char_id = 84;
        title->mp4[4].clut = getClut(256, 509);
        title->mp4[4].tpage_x = 896;
        title->mp4[4].tpage_y = 0;
        title->mp4[4].w = 12;
        title->mp4[4].h = 12;
        title->mp4[4].u = 0;
        title->mp4[4].v = 0;
        title->mp4[4].mw = 252;
        title->mp4[4].mh = 144;
        title->mp4[4].r = 128;
        title->mp4[4].g = 128;
        title->mp4[4].b = 128;
        title->mp4[5].char_id = 79;
        title->mp4[5].clut = getClut(256, 509);
        title->mp4[5].tpage_x = 896;
        title->mp4[5].tpage_y = 0;
        title->mp4[5].w = 12;
        title->mp4[5].h = 12;
        title->mp4[5].u = 0;
        title->mp4[5].v = 0;
        title->mp4[5].mw = 252;
        title->mp4[5].mh = 144;
        title->mp4[5].r = 128;
        title->mp4[5].g = 128;
        title->mp4[5].b = 128;
        title->mp4[6].char_id = 82;
        title->mp4[6].clut = getClut(256, 509);
        title->mp4[6].tpage_x = 896;
        title->mp4[6].tpage_y = 0;
        title->mp4[6].w = 12;
        title->mp4[6].h = 12;
        title->mp4[6].u = 0;
        title->mp4[6].v = 0;
        title->mp4[6].mw = 252;
        title->mp4[6].mh = 144;
        title->mp4[6].r = 128;
        title->mp4[6].g = 128;
        title->mp4[6].b = 128;
        title->mp4[7].char_id = 0;
        title->mp4[7].clut = getClut(256, 509);
        title->mp4[7].tpage_x = 896;
        title->mp4[7].tpage_y = 0;
        title->mp4[7].w = 12;
        title->mp4[7].h = 12;
        title->mp4[7].u = 0;
        title->mp4[7].v = 0;
        title->mp4[7].mw = 252;
        title->mp4[7].mh = 144;
        title->mp4[7].r = 128;
        title->mp4[7].g = 128;
        title->mp4[7].b = 128;
        title->mp4[8].char_id = 20;
        title->mp4[8].clut = getClut(256, 509);
        title->mp4[8].tpage_x = 896;
        title->mp4[8].tpage_y = 0;
        title->mp4[8].w = 12;
        title->mp4[8].h = 12;
        title->mp4[8].u = 0;
        title->mp4[8].v = 0;
        title->mp4[8].mw = 252;
        title->mp4[8].mh = 144;
        title->mp4[8].r = 128;
        title->mp4[8].g = 128;
        title->mp4[8].b = 128;
        title->mp4[9].char_id = 26;
        title->mp4[9].clut = getClut(256, 509);
        title->mp4[9].tpage_x = 896;
        title->mp4[9].tpage_y = 0;
        title->mp4[9].w = 12;
        title->mp4[9].h = 12;
        title->mp4[9].u = 0;
        title->mp4[9].v = 0;
        title->mp4[9].mw = 252;
        title->mp4[9].mh = 144;
        title->mp4[9].r = 128;
        title->mp4[9].g = 128;
        title->mp4[9].b = 128;
        title->mp4[10].char_id = 46;
        title->mp4[10].clut = getClut(256, 509);
        title->mp4[10].tpage_x = 896;
        title->mp4[10].tpage_y = 0;
        title->mp4[10].w = 12;
        title->mp4[10].h = 12;
        title->mp4[10].u = 0;
        title->mp4[10].v = 0;
        title->mp4[10].mw = 252;
        title->mp4[10].mh = 144;
        title->mp4[10].r = 128;
        title->mp4[10].g = 128;
        title->mp4[10].b = 128;
        title->mp4[11].char_id = 73;
        title->mp4[11].clut = getClut(256, 509);
        title->mp4[11].tpage_x = 896;
        title->mp4[11].tpage_y = 0;
        title->mp4[11].w = 12;
        title->mp4[11].h = 12;
        title->mp4[11].u = 0;
        title->mp4[11].v = 0;
        title->mp4[11].mw = 252;
        title->mp4[11].mh = 144;
        title->mp4[11].r = 128;
        title->mp4[11].g = 128;
        title->mp4[11].b = 128;
        title->mp4[12].char_id = 77;
        title->mp4[12].clut = getClut(256, 509);
        title->mp4[12].tpage_x = 896;
        title->mp4[12].tpage_y = 0;
        title->mp4[12].w = 12;
        title->mp4[12].h = 12;
        title->mp4[12].u = 0;
        title->mp4[12].v = 0;
        title->mp4[12].mw = 252;
        title->mp4[12].mh = 144;
        title->mp4[12].r = 128;
        title->mp4[12].g = 128;
        title->mp4[12].b = 128;
        title->mp4[13].char_id = 73;
        title->mp4[13].clut = getClut(256, 509);
        title->mp4[13].tpage_x = 896;
        title->mp4[13].tpage_y = 0;
        title->mp4[13].w = 12;
        title->mp4[13].h = 12;
        title->mp4[13].u = 0;
        title->mp4[13].v = 0;
        title->mp4[13].mw = 252;
        title->mp4[13].mh = 144;
        title->mp4[13].r = 128;
        title->mp4[13].g = 128;
        title->mp4[13].b = 128;
        title->mp4[14].char_id = 67;
        title->mp4[14].clut = getClut(256, 509);
        title->mp4[14].tpage_x = 896;
        title->mp4[14].tpage_y = 0;
        title->mp4[14].w = 12;
        title->mp4[14].h = 12;
        title->mp4[14].u = 0;
        title->mp4[14].v = 0;
        title->mp4[14].mw = 252;
        title->mp4[14].mh = 144;
        title->mp4[14].r = 128;
        title->mp4[14].g = 128;
        title->mp4[14].b = 128;

        title->mp5 = (TextChar *)malloc(5 * sizeof(TextChar));

        title->mp5[0].char_id = 42;
        title->mp5[0].clut = getClut(256, 509);
        title->mp5[0].tpage_x = 896;
        title->mp5[0].tpage_y = 0;
        title->mp5[0].w = 12;
        title->mp5[0].h = 12;
        title->mp5[0].u = 0;
        title->mp5[0].v = 0;
        title->mp5[0].mw = 252;
        title->mp5[0].mh = 144;
        title->mp5[0].r = 128;
        title->mp5[0].g = 128;
        title->mp5[0].b = 128;
        title->mp5[1].char_id = 79;
        title->mp5[1].clut = getClut(256, 509);
        title->mp5[1].tpage_x = 896;
        title->mp5[1].tpage_y = 0;
        title->mp5[1].w = 12;
        title->mp5[1].h = 12;
        title->mp5[1].u = 0;
        title->mp5[1].v = 0;
        title->mp5[1].mw = 252;
        title->mp5[1].mh = 144;
        title->mp5[1].r = 128;
        title->mp5[1].g = 128;
        title->mp5[1].b = 128;
        title->mp5[2].char_id = 65;
        title->mp5[2].clut = getClut(256, 509);
        title->mp5[2].tpage_x = 896;
        title->mp5[2].tpage_y = 0;
        title->mp5[2].w = 12;
        title->mp5[2].h = 12;
        title->mp5[2].u = 0;
        title->mp5[2].v = 0;
        title->mp5[2].mw = 252;
        title->mp5[2].mh = 144;
        title->mp5[2].r = 128;
        title->mp5[2].g = 128;
        title->mp5[2].b = 128;
        title->mp5[3].char_id = 67;
        title->mp5[3].clut = getClut(256, 509);
        title->mp5[3].tpage_x = 896;
        title->mp5[3].tpage_y = 0;
        title->mp5[3].w = 12;
        title->mp5[3].h = 12;
        title->mp5[3].u = 0;
        title->mp5[3].v = 0;
        title->mp5[3].mw = 252;
        title->mp5[3].mh = 144;
        title->mp5[3].r = 128;
        title->mp5[3].g = 128;
        title->mp5[3].b = 128;
        title->mp5[4].char_id = 229;
        title->mp5[4].clut = getClut(256, 509);
        title->mp5[4].tpage_x = 896;
        title->mp5[4].tpage_y = 0;
        title->mp5[4].w = 12;
        title->mp5[4].h = 12;
        title->mp5[4].u = 0;
        title->mp5[4].v = 0;
        title->mp5[4].mw = 252;
        title->mp5[4].mh = 144;
        title->mp5[4].r = 128;
        title->mp5[4].g = 128;
        title->mp5[4].b = 128;

        title->tsize21 = 15;
        title->tsize22 = 15;
        title->tsize23 = 15;
        title->tsize24 = 15;
        title->tsize25 = 5;

        title->lodm = (TextChar *)malloc(15 * sizeof(TextChar));

        for (u_char i = 0; i < 15; i++)
        {
            graph_inittext(&title->lodm[i]);
        }

        u_char lodmt[] = {54, 82, 69, 73, 0, 83, 229, 0, 231, 78, 67, 65, 82, 67, 73};

        graph_settext(lodmt, title->lodm, 15);

        title->lodm2 = (TextChar *)malloc(19 * sizeof(TextChar));

        for (u_char i = 0; i < 19; i++)
        {
            graph_inittext(&title->lodm2[i]);
        }

        u_char lodmt2[] = {68, 69, 0, 76, 65, 0, 45, 69, 77, 79, 82, 73, 73, 0, 35, 65, 82, 68, 31};

        graph_settext(lodmt2, title->lodm2, 19);

        title->lod1 = (TextChar *)malloc(2 * sizeof(TextChar));

        for (u_char i = 0; i < 2; i++)
        {
            graph_inittext(&title->lod1[i]);
        }

        u_char lodt1[] = {36, 65};

        graph_settext(lodt1, title->lod1, 2);

        title->lod2 = (TextChar *)malloc(2 * sizeof(TextChar));

        for (u_char i = 0; i < 2; i++)
        {
            graph_inittext(&title->lod2[i]);
        }

        u_char lodt2[] = {46, 85};

        graph_settext(lodt2, title->lod2, 2);

        title->tsize31 = 15;
        title->tsize32 = 19;
        title->tsize33 = 3;
        title->tsize34 = 2;

        title->mus1 = (TextChar *)malloc(11 * sizeof(TextChar));

        title->mus1[0].char_id = 45;
        title->mus1[0].clut = getClut(256, 509);
        title->mus1[0].tpage_x = 896;
        title->mus1[0].tpage_y = 0;
        title->mus1[0].w = 12;
        title->mus1[0].h = 12;
        title->mus1[0].u = 0;
        title->mus1[0].v = 0;
        title->mus1[0].mw = 252;
        title->mus1[0].mh = 144;
        title->mus1[0].r = 128;
        title->mus1[0].g = 128;
        title->mus1[0].b = 128;
        title->mus1[1].char_id = 85;
        title->mus1[1].clut = getClut(256, 509);
        title->mus1[1].tpage_x = 896;
        title->mus1[1].tpage_y = 0;
        title->mus1[1].w = 12;
        title->mus1[1].h = 12;
        title->mus1[1].u = 0;
        title->mus1[1].v = 0;
        title->mus1[1].mw = 252;
        title->mus1[1].mh = 144;
        title->mus1[1].r = 128;
        title->mus1[1].g = 128;
        title->mus1[1].b = 128;
        title->mus1[2].char_id = 90;
        title->mus1[2].clut = getClut(256, 509);
        title->mus1[2].tpage_x = 896;
        title->mus1[2].tpage_y = 0;
        title->mus1[2].w = 12;
        title->mus1[2].h = 12;
        title->mus1[2].u = 0;
        title->mus1[2].v = 0;
        title->mus1[2].mw = 252;
        title->mus1[2].mh = 144;
        title->mus1[2].r = 128;
        title->mus1[2].g = 128;
        title->mus1[2].b = 128;
        title->mus1[3].char_id = 73;
        title->mus1[3].clut = getClut(256, 509);
        title->mus1[3].tpage_x = 896;
        title->mus1[3].tpage_y = 0;
        title->mus1[3].w = 12;
        title->mus1[3].h = 12;
        title->mus1[3].u = 0;
        title->mus1[3].v = 0;
        title->mus1[3].mw = 252;
        title->mus1[3].mh = 144;
        title->mus1[3].r = 128;
        title->mus1[3].g = 128;
        title->mus1[3].b = 128;
        title->mus1[4].char_id = 67;
        title->mus1[4].clut = getClut(256, 509);
        title->mus1[4].tpage_x = 896;
        title->mus1[4].tpage_y = 0;
        title->mus1[4].w = 12;
        title->mus1[4].h = 12;
        title->mus1[4].u = 0;
        title->mus1[4].v = 0;
        title->mus1[4].mw = 252;
        title->mus1[4].mh = 144;
        title->mus1[4].r = 128;
        title->mus1[4].g = 128;
        title->mus1[4].b = 128;
        title->mus1[5].char_id = 229;
        title->mus1[5].clut = getClut(256, 509);
        title->mus1[5].tpage_x = 896;
        title->mus1[5].tpage_y = 0;
        title->mus1[5].w = 12;
        title->mus1[5].h = 12;
        title->mus1[5].u = 0;
        title->mus1[5].v = 0;
        title->mus1[5].mw = 252;
        title->mus1[5].mh = 144;
        title->mus1[5].r = 128;
        title->mus1[5].g = 128;
        title->mus1[5].b = 128;
        title->mus1[6].char_id = 26;
        title->mus1[6].clut = getClut(256, 509);
        title->mus1[6].tpage_x = 896;
        title->mus1[6].tpage_y = 0;
        title->mus1[6].w = 12;
        title->mus1[6].h = 12;
        title->mus1[6].u = 0;
        title->mus1[6].v = 0;
        title->mus1[6].mw = 252;
        title->mus1[6].mh = 144;
        title->mus1[6].r = 128;
        title->mus1[6].g = 128;
        title->mus1[6].b = 128;
        title->mus1[7].char_id = 0;
        title->mus1[7].clut = getClut(256, 509);
        title->mus1[7].tpage_x = 896;
        title->mus1[7].tpage_y = 0;
        title->mus1[7].w = 12;
        title->mus1[7].h = 12;
        title->mus1[7].u = 0;
        title->mus1[7].v = 0;
        title->mus1[7].mw = 252;
        title->mus1[7].mh = 144;
        title->mus1[7].r = 128;
        title->mus1[7].g = 128;
        title->mus1[7].b = 128;
        title->mus1[8].char_id = 16;
        title->mus1[8].clut = getClut(256, 509);
        title->mus1[8].tpage_x = 896;
        title->mus1[8].tpage_y = 0;
        title->mus1[8].w = 12;
        title->mus1[8].h = 12;
        title->mus1[8].u = 0;
        title->mus1[8].v = 0;
        title->mus1[8].mw = 252;
        title->mus1[8].mh = 144;
        title->mus1[8].r = 128;
        title->mus1[8].g = 128;
        title->mus1[8].b = 128;
        title->mus1[9].char_id = 16;
        title->mus1[9].clut = getClut(256, 509);
        title->mus1[9].tpage_x = 896;
        title->mus1[9].tpage_y = 0;
        title->mus1[9].w = 12;
        title->mus1[9].h = 12;
        title->mus1[9].u = 0;
        title->mus1[9].v = 0;
        title->mus1[9].mw = 252;
        title->mus1[9].mh = 144;
        title->mus1[9].r = 128;
        title->mus1[9].g = 128;
        title->mus1[9].b = 128;
        title->mus1[10].char_id = 16;
        title->mus1[10].clut = getClut(256, 509);
        title->mus1[10].tpage_x = 896;
        title->mus1[10].tpage_y = 0;
        title->mus1[10].w = 12;
        title->mus1[10].h = 12;
        title->mus1[10].u = 0;
        title->mus1[10].v = 0;
        title->mus1[10].mw = 252;
        title->mus1[10].mh = 144;
        title->mus1[10].r = 128;
        title->mus1[10].g = 128;
        title->mus1[10].b = 128;

        title->mus2 = (TextChar *)malloc(8 * sizeof(TextChar));

        title->mus2[0].char_id = 48;
        title->mus2[0].clut = getClut(256, 509);
        title->mus2[0].tpage_x = 896;
        title->mus2[0].tpage_y = 0;
        title->mus2[0].w = 12;
        title->mus2[0].h = 12;
        title->mus2[0].u = 0;
        title->mus2[0].v = 0;
        title->mus2[0].mw = 252;
        title->mus2[0].mh = 144;
        title->mus2[0].r = 128;
        title->mus2[0].g = 128;
        title->mus2[0].b = 128;
        title->mus2[1].char_id = 79;
        title->mus2[1].clut = getClut(256, 509);
        title->mus2[1].tpage_x = 896;
        title->mus2[1].tpage_y = 0;
        title->mus2[1].w = 12;
        title->mus2[1].h = 12;
        title->mus2[1].u = 0;
        title->mus2[1].v = 0;
        title->mus2[1].mw = 252;
        title->mus2[1].mh = 144;
        title->mus2[1].r = 128;
        title->mus2[1].g = 128;
        title->mus2[1].b = 128;
        title->mus2[2].char_id = 82;
        title->mus2[2].clut = getClut(256, 509);
        title->mus2[2].tpage_x = 896;
        title->mus2[2].tpage_y = 0;
        title->mus2[2].w = 12;
        title->mus2[2].h = 12;
        title->mus2[2].u = 0;
        title->mus2[2].v = 0;
        title->mus2[2].mw = 252;
        title->mus2[2].mh = 144;
        title->mus2[2].r = 128;
        title->mus2[2].g = 128;
        title->mus2[2].b = 128;
        title->mus2[3].char_id = 78;
        title->mus2[3].clut = getClut(256, 509);
        title->mus2[3].tpage_x = 896;
        title->mus2[3].tpage_y = 0;
        title->mus2[3].w = 12;
        title->mus2[3].h = 12;
        title->mus2[3].u = 0;
        title->mus2[3].v = 0;
        title->mus2[3].mw = 252;
        title->mus2[3].mh = 144;
        title->mus2[3].r = 128;
        title->mus2[3].g = 128;
        title->mus2[3].b = 128;
        title->mus2[4].char_id = 69;
        title->mus2[4].clut = getClut(256, 509);
        title->mus2[4].tpage_x = 896;
        title->mus2[4].tpage_y = 0;
        title->mus2[4].w = 12;
        title->mus2[4].h = 12;
        title->mus2[4].u = 0;
        title->mus2[4].v = 0;
        title->mus2[4].mw = 252;
        title->mus2[4].mh = 144;
        title->mus2[4].r = 128;
        title->mus2[4].g = 128;
        title->mus2[4].b = 128;
        title->mus2[5].char_id = 232;
        title->mus2[5].clut = getClut(256, 509);
        title->mus2[5].tpage_x = 896;
        title->mus2[5].tpage_y = 0;
        title->mus2[5].w = 12;
        title->mus2[5].h = 12;
        title->mus2[5].u = 0;
        title->mus2[5].v = 0;
        title->mus2[5].mw = 252;
        title->mus2[5].mh = 144;
        title->mus2[5].r = 128;
        title->mus2[5].g = 128;
        title->mus2[5].b = 128;
        title->mus2[6].char_id = 84;
        title->mus2[6].clut = getClut(256, 509);
        title->mus2[6].tpage_x = 896;
        title->mus2[6].tpage_y = 0;
        title->mus2[6].w = 12;
        title->mus2[6].h = 12;
        title->mus2[6].u = 0;
        title->mus2[6].v = 0;
        title->mus2[6].mw = 252;
        title->mus2[6].mh = 144;
        title->mus2[6].r = 128;
        title->mus2[6].g = 128;
        title->mus2[6].b = 128;
        title->mus2[7].char_id = 69;
        title->mus2[7].clut = getClut(256, 509);
        title->mus2[7].tpage_x = 896;
        title->mus2[7].tpage_y = 0;
        title->mus2[7].w = 12;
        title->mus2[7].h = 12;
        title->mus2[7].u = 0;
        title->mus2[7].v = 0;
        title->mus2[7].mw = 252;
        title->mus2[7].mh = 144;
        title->mus2[7].r = 128;
        title->mus2[7].g = 128;
        title->mus2[7].b = 128;

        title->mus3 = (TextChar *)malloc(6 * sizeof(TextChar));

        title->mus3[0].char_id = 226;
        title->mus3[0].clut = getClut(256, 509);
        title->mus3[0].tpage_x = 896;
        title->mus3[0].tpage_y = 0;
        title->mus3[0].w = 12;
        title->mus3[0].h = 12;
        title->mus3[0].u = 0;
        title->mus3[0].v = 0;
        title->mus3[0].mw = 252;
        title->mus3[0].mh = 144;
        title->mus3[0].r = 128;
        title->mus3[0].g = 128;
        title->mus3[0].b = 128;
        title->mus3[1].char_id = 78;
        title->mus3[1].clut = getClut(256, 509);
        title->mus3[1].tpage_x = 896;
        title->mus3[1].tpage_y = 0;
        title->mus3[1].w = 12;
        title->mus3[1].h = 12;
        title->mus3[1].u = 0;
        title->mus3[1].v = 0;
        title->mus3[1].mw = 252;
        title->mus3[1].mh = 144;
        title->mus3[1].r = 128;
        title->mus3[1].g = 128;
        title->mus3[1].b = 128;
        title->mus3[2].char_id = 65;
        title->mus3[2].clut = getClut(256, 509);
        title->mus3[2].tpage_x = 896;
        title->mus3[2].tpage_y = 0;
        title->mus3[2].w = 12;
        title->mus3[2].h = 12;
        title->mus3[2].u = 0;
        title->mus3[2].v = 0;
        title->mus3[2].mw = 252;
        title->mus3[2].mh = 144;
        title->mus3[2].r = 128;
        title->mus3[2].g = 128;
        title->mus3[2].b = 128;
        title->mus3[3].char_id = 80;
        title->mus3[3].clut = getClut(256, 509);
        title->mus3[3].tpage_x = 896;
        title->mus3[3].tpage_y = 0;
        title->mus3[3].w = 12;
        title->mus3[3].h = 12;
        title->mus3[3].u = 0;
        title->mus3[3].v = 0;
        title->mus3[3].mw = 252;
        title->mus3[3].mh = 144;
        title->mus3[3].r = 128;
        title->mus3[3].g = 128;
        title->mus3[3].b = 128;
        title->mus3[4].char_id = 79;
        title->mus3[4].clut = getClut(256, 509);
        title->mus3[4].tpage_x = 896;
        title->mus3[4].tpage_y = 0;
        title->mus3[4].w = 12;
        title->mus3[4].h = 12;
        title->mus3[4].u = 0;
        title->mus3[4].v = 0;
        title->mus3[4].mw = 252;
        title->mus3[4].mh = 144;
        title->mus3[4].r = 128;
        title->mus3[4].g = 128;
        title->mus3[4].b = 128;
        title->mus3[5].char_id = 73;
        title->mus3[5].clut = getClut(256, 509);
        title->mus3[5].tpage_x = 896;
        title->mus3[5].tpage_y = 0;
        title->mus3[5].w = 12;
        title->mus3[5].h = 12;
        title->mus3[5].u = 0;
        title->mus3[5].v = 0;
        title->mus3[5].mw = 252;
        title->mus3[5].mh = 144;
        title->mus3[5].r = 128;
        title->mus3[5].g = 128;
        title->mus3[5].b = 128;

        title->tsize2531 = 11;
        title->tsize2532 = 8;
        title->tsize2533 = 6;
    }
    else if (LNG == 1)
    {
        // title->debug = NULL;

        title->opt1 = (TextChar *)malloc(8 * sizeof(TextChar));

        title->opt1[0].char_id = 46;
        title->opt1[0].clut = getClut(256, 509);
        title->opt1[0].tpage_x = 896;
        title->opt1[0].tpage_y = 0;
        title->opt1[0].w = 12;
        title->opt1[0].h = 12;
        title->opt1[0].u = 0;
        title->opt1[0].v = 0;
        title->opt1[0].mw = 252;
        title->opt1[0].mh = 144;
        title->opt1[0].r = 128;
        title->opt1[0].g = 128;
        title->opt1[0].b = 128;
        title->opt1[1].char_id = 69;
        title->opt1[1].clut = getClut(256, 509);
        title->opt1[1].tpage_x = 896;
        title->opt1[1].tpage_y = 0;
        title->opt1[1].w = 12;
        title->opt1[1].h = 12;
        title->opt1[1].u = 0;
        title->opt1[1].v = 0;
        title->opt1[1].mw = 252;
        title->opt1[1].mh = 144;
        title->opt1[1].r = 128;
        title->opt1[1].g = 128;
        title->opt1[1].b = 128;
        title->opt1[2].char_id = 87;
        title->opt1[2].clut = getClut(256, 509);
        title->opt1[2].tpage_x = 896;
        title->opt1[2].tpage_y = 0;
        title->opt1[2].w = 12;
        title->opt1[2].h = 12;
        title->opt1[2].u = 0;
        title->opt1[2].v = 0;
        title->opt1[2].mw = 252;
        title->opt1[2].mh = 144;
        title->opt1[2].r = 128;
        title->opt1[2].g = 128;
        title->opt1[2].b = 128;
        title->opt1[3].char_id = 0;
        title->opt1[3].clut = getClut(256, 509);
        title->opt1[3].tpage_x = 896;
        title->opt1[3].tpage_y = 0;
        title->opt1[3].w = 12;
        title->opt1[3].h = 12;
        title->opt1[3].u = 0;
        title->opt1[3].v = 0;
        title->opt1[3].mw = 252;
        title->opt1[3].mh = 144;
        title->opt1[3].r = 128;
        title->opt1[3].g = 128;
        title->opt1[3].b = 128;
        title->opt1[4].char_id = 39;
        title->opt1[4].clut = getClut(256, 509);
        title->opt1[4].tpage_x = 896;
        title->opt1[4].tpage_y = 0;
        title->opt1[4].w = 12;
        title->opt1[4].h = 12;
        title->opt1[4].u = 0;
        title->opt1[4].v = 0;
        title->opt1[4].mw = 252;
        title->opt1[4].mh = 144;
        title->opt1[4].r = 128;
        title->opt1[4].g = 128;
        title->opt1[4].b = 128;
        title->opt1[5].char_id = 65;
        title->opt1[5].clut = getClut(256, 509);
        title->opt1[5].tpage_x = 896;
        title->opt1[5].tpage_y = 0;
        title->opt1[5].w = 12;
        title->opt1[5].h = 12;
        title->opt1[5].u = 0;
        title->opt1[5].v = 0;
        title->opt1[5].mw = 252;
        title->opt1[5].mh = 144;
        title->opt1[5].r = 128;
        title->opt1[5].g = 128;
        title->opt1[5].b = 128;
        title->opt1[6].char_id = 77;
        title->opt1[6].clut = getClut(256, 509);
        title->opt1[6].tpage_x = 896;
        title->opt1[6].tpage_y = 0;
        title->opt1[6].w = 12;
        title->opt1[6].h = 12;
        title->opt1[6].u = 0;
        title->opt1[6].v = 0;
        title->opt1[6].mw = 252;
        title->opt1[6].mh = 144;
        title->opt1[6].r = 128;
        title->opt1[6].g = 128;
        title->opt1[6].b = 128;
        title->opt1[7].char_id = 69;
        title->opt1[7].clut = getClut(256, 509);
        title->opt1[7].tpage_x = 896;
        title->opt1[7].tpage_y = 0;
        title->opt1[7].w = 12;
        title->opt1[7].h = 12;
        title->opt1[7].u = 0;
        title->opt1[7].v = 0;
        title->opt1[7].mw = 252;
        title->opt1[7].mh = 144;
        title->opt1[7].r = 128;
        title->opt1[7].g = 128;
        title->opt1[7].b = 128;

        title->opt2 = (TextChar *)malloc(9 * sizeof(TextChar));

        title->opt2[0].char_id = 44;
        title->opt2[0].clut = getClut(256, 509);
        title->opt2[0].tpage_x = 896;
        title->opt2[0].tpage_y = 0;
        title->opt2[0].w = 12;
        title->opt2[0].h = 12;
        title->opt2[0].u = 0;
        title->opt2[0].v = 0;
        title->opt2[0].mw = 252;
        title->opt2[0].mh = 144;
        title->opt2[0].r = 128;
        title->opt2[0].g = 128;
        title->opt2[0].b = 128;
        title->opt2[1].char_id = 79;
        title->opt2[1].clut = getClut(256, 509);
        title->opt2[1].tpage_x = 896;
        title->opt2[1].tpage_y = 0;
        title->opt2[1].w = 12;
        title->opt2[1].h = 12;
        title->opt2[1].u = 0;
        title->opt2[1].v = 0;
        title->opt2[1].mw = 252;
        title->opt2[1].mh = 144;
        title->opt2[1].r = 128;
        title->opt2[1].g = 128;
        title->opt2[1].b = 128;
        title->opt2[2].char_id = 65;
        title->opt2[2].clut = getClut(256, 509);
        title->opt2[2].tpage_x = 896;
        title->opt2[2].tpage_y = 0;
        title->opt2[2].w = 12;
        title->opt2[2].h = 12;
        title->opt2[2].u = 0;
        title->opt2[2].v = 0;
        title->opt2[2].mw = 252;
        title->opt2[2].mh = 144;
        title->opt2[2].r = 128;
        title->opt2[2].g = 128;
        title->opt2[2].b = 128;
        title->opt2[3].char_id = 68;
        title->opt2[3].clut = getClut(256, 509);
        title->opt2[3].tpage_x = 896;
        title->opt2[3].tpage_y = 0;
        title->opt2[3].w = 12;
        title->opt2[3].h = 12;
        title->opt2[3].u = 0;
        title->opt2[3].v = 0;
        title->opt2[3].mw = 252;
        title->opt2[3].mh = 144;
        title->opt2[3].r = 128;
        title->opt2[3].g = 128;
        title->opt2[3].b = 128;
        title->opt2[4].char_id = 0;
        title->opt2[4].clut = getClut(256, 509);
        title->opt2[4].tpage_x = 896;
        title->opt2[4].tpage_y = 0;
        title->opt2[4].w = 12;
        title->opt2[4].h = 12;
        title->opt2[4].u = 0;
        title->opt2[4].v = 0;
        title->opt2[4].mw = 252;
        title->opt2[4].mh = 144;
        title->opt2[4].r = 128;
        title->opt2[4].g = 128;
        title->opt2[4].b = 128;
        title->opt2[5].char_id = 39;
        title->opt2[5].clut = getClut(256, 509);
        title->opt2[5].tpage_x = 896;
        title->opt2[5].tpage_y = 0;
        title->opt2[5].w = 12;
        title->opt2[5].h = 12;
        title->opt2[5].u = 0;
        title->opt2[5].v = 0;
        title->opt2[5].mw = 252;
        title->opt2[5].mh = 144;
        title->opt2[5].r = 128;
        title->opt2[5].g = 128;
        title->opt2[5].b = 128;
        title->opt2[6].char_id = 65;
        title->opt2[6].clut = getClut(256, 509);
        title->opt2[6].tpage_x = 896;
        title->opt2[6].tpage_y = 0;
        title->opt2[6].w = 12;
        title->opt2[6].h = 12;
        title->opt2[6].u = 0;
        title->opt2[6].v = 0;
        title->opt2[6].mw = 252;
        title->opt2[6].mh = 144;
        title->opt2[6].r = 128;
        title->opt2[6].g = 128;
        title->opt2[6].b = 128;
        title->opt2[7].char_id = 77;
        title->opt2[7].clut = getClut(256, 509);
        title->opt2[7].tpage_x = 896;
        title->opt2[7].tpage_y = 0;
        title->opt2[7].w = 12;
        title->opt2[7].h = 12;
        title->opt2[7].u = 0;
        title->opt2[7].v = 0;
        title->opt2[7].mw = 252;
        title->opt2[7].mh = 144;
        title->opt2[7].r = 128;
        title->opt2[7].g = 128;
        title->opt2[7].b = 128;
        title->opt2[8].char_id = 69;
        title->opt2[8].clut = getClut(256, 509);
        title->opt2[8].tpage_x = 896;
        title->opt2[8].tpage_y = 0;
        title->opt2[8].w = 12;
        title->opt2[8].h = 12;
        title->opt2[8].u = 0;
        title->opt2[8].v = 0;
        title->opt2[8].mw = 252;
        title->opt2[8].mh = 144;
        title->opt2[8].r = 128;
        title->opt2[8].g = 128;
        title->opt2[8].b = 128;

        title->opt3 = (TextChar *)malloc(11 * sizeof(TextChar));

        title->opt3[0].char_id = 45;
        title->opt3[0].clut = getClut(256, 509);
        title->opt3[0].tpage_x = 896;
        title->opt3[0].tpage_y = 0;
        title->opt3[0].w = 12;
        title->opt3[0].h = 12;
        title->opt3[0].u = 0;
        title->opt3[0].v = 0;
        title->opt3[0].mw = 252;
        title->opt3[0].mh = 144;
        title->opt3[0].r = 128;
        title->opt3[0].g = 128;
        title->opt3[0].b = 128;
        title->opt3[1].char_id = 85;
        title->opt3[1].clut = getClut(256, 509);
        title->opt3[1].tpage_x = 896;
        title->opt3[1].tpage_y = 0;
        title->opt3[1].w = 12;
        title->opt3[1].h = 12;
        title->opt3[1].u = 0;
        title->opt3[1].v = 0;
        title->opt3[1].mw = 252;
        title->opt3[1].mh = 144;
        title->opt3[1].r = 128;
        title->opt3[1].g = 128;
        title->opt3[1].b = 128;
        title->opt3[2].char_id = 76;
        title->opt3[2].clut = getClut(256, 509);
        title->opt3[2].tpage_x = 896;
        title->opt3[2].tpage_y = 0;
        title->opt3[2].w = 12;
        title->opt3[2].h = 12;
        title->opt3[2].u = 0;
        title->opt3[2].v = 0;
        title->opt3[2].mw = 252;
        title->opt3[2].mh = 144;
        title->opt3[2].r = 128;
        title->opt3[2].g = 128;
        title->opt3[2].b = 128;
        title->opt3[3].char_id = 84;
        title->opt3[3].clut = getClut(256, 509);
        title->opt3[3].tpage_x = 896;
        title->opt3[3].tpage_y = 0;
        title->opt3[3].w = 12;
        title->opt3[3].h = 12;
        title->opt3[3].u = 0;
        title->opt3[3].v = 0;
        title->opt3[3].mw = 252;
        title->opt3[3].mh = 144;
        title->opt3[3].r = 128;
        title->opt3[3].g = 128;
        title->opt3[3].b = 128;
        title->opt3[4].char_id = 73;
        title->opt3[4].clut = getClut(256, 509);
        title->opt3[4].tpage_x = 896;
        title->opt3[4].tpage_y = 0;
        title->opt3[4].w = 12;
        title->opt3[4].h = 12;
        title->opt3[4].u = 0;
        title->opt3[4].v = 0;
        title->opt3[4].mw = 252;
        title->opt3[4].mh = 144;
        title->opt3[4].r = 128;
        title->opt3[4].g = 128;
        title->opt3[4].b = 128;
        title->opt3[5].char_id = 80;
        title->opt3[5].clut = getClut(256, 509);
        title->opt3[5].tpage_x = 896;
        title->opt3[5].tpage_y = 0;
        title->opt3[5].w = 12;
        title->opt3[5].h = 12;
        title->opt3[5].u = 0;
        title->opt3[5].v = 0;
        title->opt3[5].mw = 252;
        title->opt3[5].mh = 144;
        title->opt3[5].r = 128;
        title->opt3[5].g = 128;
        title->opt3[5].b = 128;
        title->opt3[6].char_id = 76;
        title->opt3[6].clut = getClut(256, 509);
        title->opt3[6].tpage_x = 896;
        title->opt3[6].tpage_y = 0;
        title->opt3[6].w = 12;
        title->opt3[6].h = 12;
        title->opt3[6].u = 0;
        title->opt3[6].v = 0;
        title->opt3[6].mw = 252;
        title->opt3[6].mh = 144;
        title->opt3[6].r = 128;
        title->opt3[6].g = 128;
        title->opt3[6].b = 128;
        title->opt3[7].char_id = 65;
        title->opt3[7].clut = getClut(256, 509);
        title->opt3[7].tpage_x = 896;
        title->opt3[7].tpage_y = 0;
        title->opt3[7].w = 12;
        title->opt3[7].h = 12;
        title->opt3[7].u = 0;
        title->opt3[7].v = 0;
        title->opt3[7].mw = 252;
        title->opt3[7].mh = 144;
        title->opt3[7].r = 128;
        title->opt3[7].g = 128;
        title->opt3[7].b = 128;
        title->opt3[8].char_id = 89;
        title->opt3[8].clut = getClut(256, 509);
        title->opt3[8].tpage_x = 896;
        title->opt3[8].tpage_y = 0;
        title->opt3[8].w = 12;
        title->opt3[8].h = 12;
        title->opt3[8].u = 0;
        title->opt3[8].v = 0;
        title->opt3[8].mw = 252;
        title->opt3[8].mh = 144;
        title->opt3[8].r = 128;
        title->opt3[8].g = 128;
        title->opt3[8].b = 128;
        title->opt3[9].char_id = 69;
        title->opt3[9].clut = getClut(256, 509);
        title->opt3[9].tpage_x = 896;
        title->opt3[9].tpage_y = 0;
        title->opt3[9].w = 12;
        title->opt3[9].h = 12;
        title->opt3[9].u = 0;
        title->opt3[9].v = 0;
        title->opt3[9].mw = 252;
        title->opt3[9].mh = 144;
        title->opt3[9].r = 128;
        title->opt3[9].g = 128;
        title->opt3[9].b = 128;
        title->opt3[10].char_id = 82;
        title->opt3[10].clut = getClut(256, 509);
        title->opt3[10].tpage_x = 896;
        title->opt3[10].tpage_y = 0;
        title->opt3[10].w = 12;
        title->opt3[10].h = 12;
        title->opt3[10].u = 0;
        title->opt3[10].v = 0;
        title->opt3[10].mw = 252;
        title->opt3[10].mh = 144;
        title->opt3[10].r = 128;
        title->opt3[10].g = 128;
        title->opt3[10].b = 128;

        title->tsize01 = 8;
        title->tsize02 = 9;
        title->tsize03 = 11;

        title->mp1 = (TextChar *)malloc(14 * sizeof(TextChar));

        title->mp1[0].char_id = 48;
        title->mp1[0].clut = getClut(256, 509);
        title->mp1[0].tpage_x = 896;
        title->mp1[0].tpage_y = 0;
        title->mp1[0].w = 12;
        title->mp1[0].h = 12;
        title->mp1[0].u = 0;
        title->mp1[0].v = 0;
        title->mp1[0].mw = 252;
        title->mp1[0].mh = 144;
        title->mp1[0].r = 128;
        title->mp1[0].g = 128;
        title->mp1[0].b = 128;
        title->mp1[1].char_id = 76;
        title->mp1[1].clut = getClut(256, 509);
        title->mp1[1].tpage_x = 896;
        title->mp1[1].tpage_y = 0;
        title->mp1[1].w = 12;
        title->mp1[1].h = 12;
        title->mp1[1].u = 0;
        title->mp1[1].v = 0;
        title->mp1[1].mw = 252;
        title->mp1[1].mh = 144;
        title->mp1[1].r = 128;
        title->mp1[1].g = 128;
        title->mp1[1].b = 128;
        title->mp1[2].char_id = 65;
        title->mp1[2].clut = getClut(256, 509);
        title->mp1[2].tpage_x = 896;
        title->mp1[2].tpage_y = 0;
        title->mp1[2].w = 12;
        title->mp1[2].h = 12;
        title->mp1[2].u = 0;
        title->mp1[2].v = 0;
        title->mp1[2].mw = 252;
        title->mp1[2].mh = 144;
        title->mp1[2].r = 128;
        title->mp1[2].g = 128;
        title->mp1[2].b = 128;
        title->mp1[3].char_id = 89;
        title->mp1[3].clut = getClut(256, 509);
        title->mp1[3].tpage_x = 896;
        title->mp1[3].tpage_y = 0;
        title->mp1[3].w = 12;
        title->mp1[3].h = 12;
        title->mp1[3].u = 0;
        title->mp1[3].v = 0;
        title->mp1[3].mw = 252;
        title->mp1[3].mh = 144;
        title->mp1[3].r = 128;
        title->mp1[3].g = 128;
        title->mp1[3].b = 128;
        title->mp1[4].char_id = 69;
        title->mp1[4].clut = getClut(256, 509);
        title->mp1[4].tpage_x = 896;
        title->mp1[4].tpage_y = 0;
        title->mp1[4].w = 12;
        title->mp1[4].h = 12;
        title->mp1[4].u = 0;
        title->mp1[4].v = 0;
        title->mp1[4].mw = 252;
        title->mp1[4].mh = 144;
        title->mp1[4].r = 128;
        title->mp1[4].g = 128;
        title->mp1[4].b = 128;
        title->mp1[5].char_id = 82;
        title->mp1[5].clut = getClut(256, 509);
        title->mp1[5].tpage_x = 896;
        title->mp1[5].tpage_y = 0;
        title->mp1[5].w = 12;
        title->mp1[5].h = 12;
        title->mp1[5].u = 0;
        title->mp1[5].v = 0;
        title->mp1[5].mw = 252;
        title->mp1[5].mh = 144;
        title->mp1[5].r = 128;
        title->mp1[5].g = 128;
        title->mp1[5].b = 128;
        title->mp1[6].char_id = 0;
        title->mp1[6].clut = getClut(256, 509);
        title->mp1[6].tpage_x = 896;
        title->mp1[6].tpage_y = 0;
        title->mp1[6].w = 12;
        title->mp1[6].h = 12;
        title->mp1[6].u = 0;
        title->mp1[6].v = 0;
        title->mp1[6].mw = 252;
        title->mp1[6].mh = 144;
        title->mp1[6].r = 128;
        title->mp1[6].g = 128;
        title->mp1[6].b = 128;
        title->mp1[7].char_id = 17;
        title->mp1[7].clut = getClut(256, 509);
        title->mp1[7].tpage_x = 896;
        title->mp1[7].tpage_y = 0;
        title->mp1[7].w = 12;
        title->mp1[7].h = 12;
        title->mp1[7].u = 0;
        title->mp1[7].v = 0;
        title->mp1[7].mw = 252;
        title->mp1[7].mh = 144;
        title->mp1[7].r = 128;
        title->mp1[7].g = 128;
        title->mp1[7].b = 128;
        title->mp1[8].char_id = 26;
        title->mp1[8].clut = getClut(256, 509);
        title->mp1[8].tpage_x = 896;
        title->mp1[8].tpage_y = 0;
        title->mp1[8].w = 12;
        title->mp1[8].h = 12;
        title->mp1[8].u = 0;
        title->mp1[8].v = 0;
        title->mp1[8].mw = 252;
        title->mp1[8].mh = 144;
        title->mp1[8].r = 128;
        title->mp1[8].g = 128;
        title->mp1[8].b = 128;
        title->mp1[9].char_id = 40;
        title->mp1[9].clut = getClut(256, 509);
        title->mp1[9].tpage_x = 896;
        title->mp1[9].tpage_y = 0;
        title->mp1[9].w = 12;
        title->mp1[9].h = 12;
        title->mp1[9].u = 0;
        title->mp1[9].v = 0;
        title->mp1[9].mw = 252;
        title->mp1[9].mh = 144;
        title->mp1[9].r = 128;
        title->mp1[9].g = 128;
        title->mp1[9].b = 128;
        title->mp1[10].char_id = 85;
        title->mp1[10].clut = getClut(256, 509);
        title->mp1[10].tpage_x = 896;
        title->mp1[10].tpage_y = 0;
        title->mp1[10].w = 12;
        title->mp1[10].h = 12;
        title->mp1[10].u = 0;
        title->mp1[10].v = 0;
        title->mp1[10].mw = 252;
        title->mp1[10].mh = 144;
        title->mp1[10].r = 128;
        title->mp1[10].g = 128;
        title->mp1[10].b = 128;
        title->mp1[11].char_id = 77;
        title->mp1[11].clut = getClut(256, 509);
        title->mp1[11].tpage_x = 896;
        title->mp1[11].tpage_y = 0;
        title->mp1[11].w = 12;
        title->mp1[11].h = 12;
        title->mp1[11].u = 0;
        title->mp1[11].v = 0;
        title->mp1[11].mw = 252;
        title->mp1[11].mh = 144;
        title->mp1[11].r = 128;
        title->mp1[11].g = 128;
        title->mp1[11].b = 128;
        title->mp1[12].char_id = 65;
        title->mp1[12].clut = getClut(256, 509);
        title->mp1[12].tpage_x = 896;
        title->mp1[12].tpage_y = 0;
        title->mp1[12].w = 12;
        title->mp1[12].h = 12;
        title->mp1[12].u = 0;
        title->mp1[12].v = 0;
        title->mp1[12].mw = 252;
        title->mp1[12].mh = 144;
        title->mp1[12].r = 128;
        title->mp1[12].g = 128;
        title->mp1[12].b = 128;
        title->mp1[13].char_id = 78;
        title->mp1[13].clut = getClut(256, 509);
        title->mp1[13].tpage_x = 896;
        title->mp1[13].tpage_y = 0;
        title->mp1[13].w = 12;
        title->mp1[13].h = 12;
        title->mp1[13].u = 0;
        title->mp1[13].v = 0;
        title->mp1[13].mw = 252;
        title->mp1[13].mh = 144;
        title->mp1[13].r = 128;
        title->mp1[13].g = 128;
        title->mp1[13].b = 128;

        title->mp2 = (TextChar *)malloc(14 * sizeof(TextChar));

        title->mp2[0].char_id = 48;
        title->mp2[0].clut = getClut(256, 509);
        title->mp2[0].tpage_x = 896;
        title->mp2[0].tpage_y = 0;
        title->mp2[0].w = 12;
        title->mp2[0].h = 12;
        title->mp2[0].u = 0;
        title->mp2[0].v = 0;
        title->mp2[0].mw = 252;
        title->mp2[0].mh = 144;
        title->mp2[0].r = 128;
        title->mp2[0].g = 128;
        title->mp2[0].b = 128;
        title->mp2[1].char_id = 76;
        title->mp2[1].clut = getClut(256, 509);
        title->mp2[1].tpage_x = 896;
        title->mp2[1].tpage_y = 0;
        title->mp2[1].w = 12;
        title->mp2[1].h = 12;
        title->mp2[1].u = 0;
        title->mp2[1].v = 0;
        title->mp2[1].mw = 252;
        title->mp2[1].mh = 144;
        title->mp2[1].r = 128;
        title->mp2[1].g = 128;
        title->mp2[1].b = 128;
        title->mp2[2].char_id = 65;
        title->mp2[2].clut = getClut(256, 509);
        title->mp2[2].tpage_x = 896;
        title->mp2[2].tpage_y = 0;
        title->mp2[2].w = 12;
        title->mp2[2].h = 12;
        title->mp2[2].u = 0;
        title->mp2[2].v = 0;
        title->mp2[2].mw = 252;
        title->mp2[2].mh = 144;
        title->mp2[2].r = 128;
        title->mp2[2].g = 128;
        title->mp2[2].b = 128;
        title->mp2[3].char_id = 89;
        title->mp2[3].clut = getClut(256, 509);
        title->mp2[3].tpage_x = 896;
        title->mp2[3].tpage_y = 0;
        title->mp2[3].w = 12;
        title->mp2[3].h = 12;
        title->mp2[3].u = 0;
        title->mp2[3].v = 0;
        title->mp2[3].mw = 252;
        title->mp2[3].mh = 144;
        title->mp2[3].r = 128;
        title->mp2[3].g = 128;
        title->mp2[3].b = 128;
        title->mp2[4].char_id = 69;
        title->mp2[4].clut = getClut(256, 509);
        title->mp2[4].tpage_x = 896;
        title->mp2[4].tpage_y = 0;
        title->mp2[4].w = 12;
        title->mp2[4].h = 12;
        title->mp2[4].u = 0;
        title->mp2[4].v = 0;
        title->mp2[4].mw = 252;
        title->mp2[4].mh = 144;
        title->mp2[4].r = 128;
        title->mp2[4].g = 128;
        title->mp2[4].b = 128;
        title->mp2[5].char_id = 82;
        title->mp2[5].clut = getClut(256, 509);
        title->mp2[5].tpage_x = 896;
        title->mp2[5].tpage_y = 0;
        title->mp2[5].w = 12;
        title->mp2[5].h = 12;
        title->mp2[5].u = 0;
        title->mp2[5].v = 0;
        title->mp2[5].mw = 252;
        title->mp2[5].mh = 144;
        title->mp2[5].r = 128;
        title->mp2[5].g = 128;
        title->mp2[5].b = 128;
        title->mp2[6].char_id = 0;
        title->mp2[6].clut = getClut(256, 509);
        title->mp2[6].tpage_x = 896;
        title->mp2[6].tpage_y = 0;
        title->mp2[6].w = 12;
        title->mp2[6].h = 12;
        title->mp2[6].u = 0;
        title->mp2[6].v = 0;
        title->mp2[6].mw = 252;
        title->mp2[6].mh = 144;
        title->mp2[6].r = 128;
        title->mp2[6].g = 128;
        title->mp2[6].b = 128;
        title->mp2[7].char_id = 18;
        title->mp2[7].clut = getClut(256, 509);
        title->mp2[7].tpage_x = 896;
        title->mp2[7].tpage_y = 0;
        title->mp2[7].w = 12;
        title->mp2[7].h = 12;
        title->mp2[7].u = 0;
        title->mp2[7].v = 0;
        title->mp2[7].mw = 252;
        title->mp2[7].mh = 144;
        title->mp2[7].r = 128;
        title->mp2[7].g = 128;
        title->mp2[7].b = 128;
        title->mp2[8].char_id = 26;
        title->mp2[8].clut = getClut(256, 509);
        title->mp2[8].tpage_x = 896;
        title->mp2[8].tpage_y = 0;
        title->mp2[8].w = 12;
        title->mp2[8].h = 12;
        title->mp2[8].u = 0;
        title->mp2[8].v = 0;
        title->mp2[8].mw = 252;
        title->mp2[8].mh = 144;
        title->mp2[8].r = 128;
        title->mp2[8].g = 128;
        title->mp2[8].b = 128;
        title->mp2[9].char_id = 40;
        title->mp2[9].clut = getClut(256, 509);
        title->mp2[9].tpage_x = 896;
        title->mp2[9].tpage_y = 0;
        title->mp2[9].w = 12;
        title->mp2[9].h = 12;
        title->mp2[9].u = 0;
        title->mp2[9].v = 0;
        title->mp2[9].mw = 252;
        title->mp2[9].mh = 144;
        title->mp2[9].r = 128;
        title->mp2[9].g = 128;
        title->mp2[9].b = 128;
        title->mp2[10].char_id = 85;
        title->mp2[10].clut = getClut(256, 509);
        title->mp2[10].tpage_x = 896;
        title->mp2[10].tpage_y = 0;
        title->mp2[10].w = 12;
        title->mp2[10].h = 12;
        title->mp2[10].u = 0;
        title->mp2[10].v = 0;
        title->mp2[10].mw = 252;
        title->mp2[10].mh = 144;
        title->mp2[10].r = 128;
        title->mp2[10].g = 128;
        title->mp2[10].b = 128;
        title->mp2[11].char_id = 77;
        title->mp2[11].clut = getClut(256, 509);
        title->mp2[11].tpage_x = 896;
        title->mp2[11].tpage_y = 0;
        title->mp2[11].w = 12;
        title->mp2[11].h = 12;
        title->mp2[11].u = 0;
        title->mp2[11].v = 0;
        title->mp2[11].mw = 252;
        title->mp2[11].mh = 144;
        title->mp2[11].r = 128;
        title->mp2[11].g = 128;
        title->mp2[11].b = 128;
        title->mp2[12].char_id = 65;
        title->mp2[12].clut = getClut(256, 509);
        title->mp2[12].tpage_x = 896;
        title->mp2[12].tpage_y = 0;
        title->mp2[12].w = 12;
        title->mp2[12].h = 12;
        title->mp2[12].u = 0;
        title->mp2[12].v = 0;
        title->mp2[12].mw = 252;
        title->mp2[12].mh = 144;
        title->mp2[12].r = 128;
        title->mp2[12].g = 128;
        title->mp2[12].b = 128;
        title->mp2[13].char_id = 78;
        title->mp2[13].clut = getClut(256, 509);
        title->mp2[13].tpage_x = 896;
        title->mp2[13].tpage_y = 0;
        title->mp2[13].w = 12;
        title->mp2[13].h = 12;
        title->mp2[13].u = 0;
        title->mp2[13].v = 0;
        title->mp2[13].mw = 252;
        title->mp2[13].mh = 144;
        title->mp2[13].r = 128;
        title->mp2[13].g = 128;
        title->mp2[13].b = 128;

        title->mp3 = (TextChar *)malloc(14 * sizeof(TextChar));

        title->mp3[0].char_id = 48;
        title->mp3[0].clut = getClut(256, 509);
        title->mp3[0].tpage_x = 896;
        title->mp3[0].tpage_y = 0;
        title->mp3[0].w = 12;
        title->mp3[0].h = 12;
        title->mp3[0].u = 0;
        title->mp3[0].v = 0;
        title->mp3[0].mw = 252;
        title->mp3[0].mh = 144;
        title->mp3[0].r = 128;
        title->mp3[0].g = 128;
        title->mp3[0].b = 128;
        title->mp3[1].char_id = 76;
        title->mp3[1].clut = getClut(256, 509);
        title->mp3[1].tpage_x = 896;
        title->mp3[1].tpage_y = 0;
        title->mp3[1].w = 12;
        title->mp3[1].h = 12;
        title->mp3[1].u = 0;
        title->mp3[1].v = 0;
        title->mp3[1].mw = 252;
        title->mp3[1].mh = 144;
        title->mp3[1].r = 128;
        title->mp3[1].g = 128;
        title->mp3[1].b = 128;
        title->mp3[2].char_id = 65;
        title->mp3[2].clut = getClut(256, 509);
        title->mp3[2].tpage_x = 896;
        title->mp3[2].tpage_y = 0;
        title->mp3[2].w = 12;
        title->mp3[2].h = 12;
        title->mp3[2].u = 0;
        title->mp3[2].v = 0;
        title->mp3[2].mw = 252;
        title->mp3[2].mh = 144;
        title->mp3[2].r = 128;
        title->mp3[2].g = 128;
        title->mp3[2].b = 128;
        title->mp3[3].char_id = 89;
        title->mp3[3].clut = getClut(256, 509);
        title->mp3[3].tpage_x = 896;
        title->mp3[3].tpage_y = 0;
        title->mp3[3].w = 12;
        title->mp3[3].h = 12;
        title->mp3[3].u = 0;
        title->mp3[3].v = 0;
        title->mp3[3].mw = 252;
        title->mp3[3].mh = 144;
        title->mp3[3].r = 128;
        title->mp3[3].g = 128;
        title->mp3[3].b = 128;
        title->mp3[4].char_id = 69;
        title->mp3[4].clut = getClut(256, 509);
        title->mp3[4].tpage_x = 896;
        title->mp3[4].tpage_y = 0;
        title->mp3[4].w = 12;
        title->mp3[4].h = 12;
        title->mp3[4].u = 0;
        title->mp3[4].v = 0;
        title->mp3[4].mw = 252;
        title->mp3[4].mh = 144;
        title->mp3[4].r = 128;
        title->mp3[4].g = 128;
        title->mp3[4].b = 128;
        title->mp3[5].char_id = 82;
        title->mp3[5].clut = getClut(256, 509);
        title->mp3[5].tpage_x = 896;
        title->mp3[5].tpage_y = 0;
        title->mp3[5].w = 12;
        title->mp3[5].h = 12;
        title->mp3[5].u = 0;
        title->mp3[5].v = 0;
        title->mp3[5].mw = 252;
        title->mp3[5].mh = 144;
        title->mp3[5].r = 128;
        title->mp3[5].g = 128;
        title->mp3[5].b = 128;
        title->mp3[6].char_id = 0;
        title->mp3[6].clut = getClut(256, 509);
        title->mp3[6].tpage_x = 896;
        title->mp3[6].tpage_y = 0;
        title->mp3[6].w = 12;
        title->mp3[6].h = 12;
        title->mp3[6].u = 0;
        title->mp3[6].v = 0;
        title->mp3[6].mw = 252;
        title->mp3[6].mh = 144;
        title->mp3[6].r = 128;
        title->mp3[6].g = 128;
        title->mp3[6].b = 128;
        title->mp3[7].char_id = 19;
        title->mp3[7].clut = getClut(256, 509);
        title->mp3[7].tpage_x = 896;
        title->mp3[7].tpage_y = 0;
        title->mp3[7].w = 12;
        title->mp3[7].h = 12;
        title->mp3[7].u = 0;
        title->mp3[7].v = 0;
        title->mp3[7].mw = 252;
        title->mp3[7].mh = 144;
        title->mp3[7].r = 128;
        title->mp3[7].g = 128;
        title->mp3[7].b = 128;
        title->mp3[8].char_id = 26;
        title->mp3[8].clut = getClut(256, 509);
        title->mp3[8].tpage_x = 896;
        title->mp3[8].tpage_y = 0;
        title->mp3[8].w = 12;
        title->mp3[8].h = 12;
        title->mp3[8].u = 0;
        title->mp3[8].v = 0;
        title->mp3[8].mw = 252;
        title->mp3[8].mh = 144;
        title->mp3[8].r = 128;
        title->mp3[8].g = 128;
        title->mp3[8].b = 128;
        title->mp3[9].char_id = 40;
        title->mp3[9].clut = getClut(256, 509);
        title->mp3[9].tpage_x = 896;
        title->mp3[9].tpage_y = 0;
        title->mp3[9].w = 12;
        title->mp3[9].h = 12;
        title->mp3[9].u = 0;
        title->mp3[9].v = 0;
        title->mp3[9].mw = 252;
        title->mp3[9].mh = 144;
        title->mp3[9].r = 128;
        title->mp3[9].g = 128;
        title->mp3[9].b = 128;
        title->mp3[10].char_id = 85;
        title->mp3[10].clut = getClut(256, 509);
        title->mp3[10].tpage_x = 896;
        title->mp3[10].tpage_y = 0;
        title->mp3[10].w = 12;
        title->mp3[10].h = 12;
        title->mp3[10].u = 0;
        title->mp3[10].v = 0;
        title->mp3[10].mw = 252;
        title->mp3[10].mh = 144;
        title->mp3[10].r = 128;
        title->mp3[10].g = 128;
        title->mp3[10].b = 128;
        title->mp3[11].char_id = 77;
        title->mp3[11].clut = getClut(256, 509);
        title->mp3[11].tpage_x = 896;
        title->mp3[11].tpage_y = 0;
        title->mp3[11].w = 12;
        title->mp3[11].h = 12;
        title->mp3[11].u = 0;
        title->mp3[11].v = 0;
        title->mp3[11].mw = 252;
        title->mp3[11].mh = 144;
        title->mp3[11].r = 128;
        title->mp3[11].g = 128;
        title->mp3[11].b = 128;
        title->mp3[12].char_id = 65;
        title->mp3[12].clut = getClut(256, 509);
        title->mp3[12].tpage_x = 896;
        title->mp3[12].tpage_y = 0;
        title->mp3[12].w = 12;
        title->mp3[12].h = 12;
        title->mp3[12].u = 0;
        title->mp3[12].v = 0;
        title->mp3[12].mw = 252;
        title->mp3[12].mh = 144;
        title->mp3[12].r = 128;
        title->mp3[12].g = 128;
        title->mp3[12].b = 128;
        title->mp3[13].char_id = 78;
        title->mp3[13].clut = getClut(256, 509);
        title->mp3[13].tpage_x = 896;
        title->mp3[13].tpage_y = 0;
        title->mp3[13].w = 12;
        title->mp3[13].h = 12;
        title->mp3[13].u = 0;
        title->mp3[13].v = 0;
        title->mp3[13].mw = 252;
        title->mp3[13].mh = 144;
        title->mp3[13].r = 128;
        title->mp3[13].g = 128;
        title->mp3[13].b = 128;

        title->mp4 = (TextChar *)malloc(14 * sizeof(TextChar));

        title->mp4[0].char_id = 48;
        title->mp4[0].clut = getClut(256, 509);
        title->mp4[0].tpage_x = 896;
        title->mp4[0].tpage_y = 0;
        title->mp4[0].w = 12;
        title->mp4[0].h = 12;
        title->mp4[0].u = 0;
        title->mp4[0].v = 0;
        title->mp4[0].mw = 252;
        title->mp4[0].mh = 144;
        title->mp4[0].r = 128;
        title->mp4[0].g = 128;
        title->mp4[0].b = 128;
        title->mp4[1].char_id = 76;
        title->mp4[1].clut = getClut(256, 509);
        title->mp4[1].tpage_x = 896;
        title->mp4[1].tpage_y = 0;
        title->mp4[1].w = 12;
        title->mp4[1].h = 12;
        title->mp4[1].u = 0;
        title->mp4[1].v = 0;
        title->mp4[1].mw = 252;
        title->mp4[1].mh = 144;
        title->mp4[1].r = 128;
        title->mp4[1].g = 128;
        title->mp4[1].b = 128;
        title->mp4[2].char_id = 65;
        title->mp4[2].clut = getClut(256, 509);
        title->mp4[2].tpage_x = 896;
        title->mp4[2].tpage_y = 0;
        title->mp4[2].w = 12;
        title->mp4[2].h = 12;
        title->mp4[2].u = 0;
        title->mp4[2].v = 0;
        title->mp4[2].mw = 252;
        title->mp4[2].mh = 144;
        title->mp4[2].r = 128;
        title->mp4[2].g = 128;
        title->mp4[2].b = 128;
        title->mp4[3].char_id = 89;
        title->mp4[3].clut = getClut(256, 509);
        title->mp4[3].tpage_x = 896;
        title->mp4[3].tpage_y = 0;
        title->mp4[3].w = 12;
        title->mp4[3].h = 12;
        title->mp4[3].u = 0;
        title->mp4[3].v = 0;
        title->mp4[3].mw = 252;
        title->mp4[3].mh = 144;
        title->mp4[3].r = 128;
        title->mp4[3].g = 128;
        title->mp4[3].b = 128;
        title->mp4[4].char_id = 69;
        title->mp4[4].clut = getClut(256, 509);
        title->mp4[4].tpage_x = 896;
        title->mp4[4].tpage_y = 0;
        title->mp4[4].w = 12;
        title->mp4[4].h = 12;
        title->mp4[4].u = 0;
        title->mp4[4].v = 0;
        title->mp4[4].mw = 252;
        title->mp4[4].mh = 144;
        title->mp4[4].r = 128;
        title->mp4[4].g = 128;
        title->mp4[4].b = 128;
        title->mp4[5].char_id = 82;
        title->mp4[5].clut = getClut(256, 509);
        title->mp4[5].tpage_x = 896;
        title->mp4[5].tpage_y = 0;
        title->mp4[5].w = 12;
        title->mp4[5].h = 12;
        title->mp4[5].u = 0;
        title->mp4[5].v = 0;
        title->mp4[5].mw = 252;
        title->mp4[5].mh = 144;
        title->mp4[5].r = 128;
        title->mp4[5].g = 128;
        title->mp4[5].b = 128;
        title->mp4[6].char_id = 0;
        title->mp4[6].clut = getClut(256, 509);
        title->mp4[6].tpage_x = 896;
        title->mp4[6].tpage_y = 0;
        title->mp4[6].w = 12;
        title->mp4[6].h = 12;
        title->mp4[6].u = 0;
        title->mp4[6].v = 0;
        title->mp4[6].mw = 252;
        title->mp4[6].mh = 144;
        title->mp4[6].r = 128;
        title->mp4[6].g = 128;
        title->mp4[6].b = 128;
        title->mp4[7].char_id = 20;
        title->mp4[7].clut = getClut(256, 509);
        title->mp4[7].tpage_x = 896;
        title->mp4[7].tpage_y = 0;
        title->mp4[7].w = 12;
        title->mp4[7].h = 12;
        title->mp4[7].u = 0;
        title->mp4[7].v = 0;
        title->mp4[7].mw = 252;
        title->mp4[7].mh = 144;
        title->mp4[7].r = 128;
        title->mp4[7].g = 128;
        title->mp4[7].b = 128;
        title->mp4[8].char_id = 26;
        title->mp4[8].clut = getClut(256, 509);
        title->mp4[8].tpage_x = 896;
        title->mp4[8].tpage_y = 0;
        title->mp4[8].w = 12;
        title->mp4[8].h = 12;
        title->mp4[8].u = 0;
        title->mp4[8].v = 0;
        title->mp4[8].mw = 252;
        title->mp4[8].mh = 144;
        title->mp4[8].r = 128;
        title->mp4[8].g = 128;
        title->mp4[8].b = 128;
        title->mp4[9].char_id = 40;
        title->mp4[9].clut = getClut(256, 509);
        title->mp4[9].tpage_x = 896;
        title->mp4[9].tpage_y = 0;
        title->mp4[9].w = 12;
        title->mp4[9].h = 12;
        title->mp4[9].u = 0;
        title->mp4[9].v = 0;
        title->mp4[9].mw = 252;
        title->mp4[9].mh = 144;
        title->mp4[9].r = 128;
        title->mp4[9].g = 128;
        title->mp4[9].b = 128;
        title->mp4[10].char_id = 85;
        title->mp4[10].clut = getClut(256, 509);
        title->mp4[10].tpage_x = 896;
        title->mp4[10].tpage_y = 0;
        title->mp4[10].w = 12;
        title->mp4[10].h = 12;
        title->mp4[10].u = 0;
        title->mp4[10].v = 0;
        title->mp4[10].mw = 252;
        title->mp4[10].mh = 144;
        title->mp4[10].r = 128;
        title->mp4[10].g = 128;
        title->mp4[10].b = 128;
        title->mp4[11].char_id = 77;
        title->mp4[11].clut = getClut(256, 509);
        title->mp4[11].tpage_x = 896;
        title->mp4[11].tpage_y = 0;
        title->mp4[11].w = 12;
        title->mp4[11].h = 12;
        title->mp4[11].u = 0;
        title->mp4[11].v = 0;
        title->mp4[11].mw = 252;
        title->mp4[11].mh = 144;
        title->mp4[11].r = 128;
        title->mp4[11].g = 128;
        title->mp4[11].b = 128;
        title->mp4[12].char_id = 65;
        title->mp4[12].clut = getClut(256, 509);
        title->mp4[12].tpage_x = 896;
        title->mp4[12].tpage_y = 0;
        title->mp4[12].w = 12;
        title->mp4[12].h = 12;
        title->mp4[12].u = 0;
        title->mp4[12].v = 0;
        title->mp4[12].mw = 252;
        title->mp4[12].mh = 144;
        title->mp4[12].r = 128;
        title->mp4[12].g = 128;
        title->mp4[12].b = 128;
        title->mp4[13].char_id = 78;
        title->mp4[13].clut = getClut(256, 509);
        title->mp4[13].tpage_x = 896;
        title->mp4[13].tpage_y = 0;
        title->mp4[13].w = 12;
        title->mp4[13].h = 12;
        title->mp4[13].u = 0;
        title->mp4[13].v = 0;
        title->mp4[13].mw = 252;
        title->mp4[13].mh = 144;
        title->mp4[13].r = 128;
        title->mp4[13].g = 128;
        title->mp4[13].b = 128;

        title->mp5 = (TextChar *)malloc(5 * sizeof(TextChar));

        title->mp5[0].char_id = 51;
        title->mp5[0].clut = getClut(256, 509);
        title->mp5[0].tpage_x = 896;
        title->mp5[0].tpage_y = 0;
        title->mp5[0].w = 12;
        title->mp5[0].h = 12;
        title->mp5[0].u = 0;
        title->mp5[0].v = 0;
        title->mp5[0].mw = 252;
        title->mp5[0].mh = 144;
        title->mp5[0].r = 128;
        title->mp5[0].g = 128;
        title->mp5[0].b = 128;
        title->mp5[1].char_id = 84;
        title->mp5[1].clut = getClut(256, 509);
        title->mp5[1].tpage_x = 896;
        title->mp5[1].tpage_y = 0;
        title->mp5[1].w = 12;
        title->mp5[1].h = 12;
        title->mp5[1].u = 0;
        title->mp5[1].v = 0;
        title->mp5[1].mw = 252;
        title->mp5[1].mh = 144;
        title->mp5[1].r = 128;
        title->mp5[1].g = 128;
        title->mp5[1].b = 128;
        title->mp5[2].char_id = 65;
        title->mp5[2].clut = getClut(256, 509);
        title->mp5[2].tpage_x = 896;
        title->mp5[2].tpage_y = 0;
        title->mp5[2].w = 12;
        title->mp5[2].h = 12;
        title->mp5[2].u = 0;
        title->mp5[2].v = 0;
        title->mp5[2].mw = 252;
        title->mp5[2].mh = 144;
        title->mp5[2].r = 128;
        title->mp5[2].g = 128;
        title->mp5[2].b = 128;
        title->mp5[3].char_id = 82;
        title->mp5[3].clut = getClut(256, 509);
        title->mp5[3].tpage_x = 896;
        title->mp5[3].tpage_y = 0;
        title->mp5[3].w = 12;
        title->mp5[3].h = 12;
        title->mp5[3].u = 0;
        title->mp5[3].v = 0;
        title->mp5[3].mw = 252;
        title->mp5[3].mh = 144;
        title->mp5[3].r = 128;
        title->mp5[3].g = 128;
        title->mp5[3].b = 128;
        title->mp5[4].char_id = 84;
        title->mp5[4].clut = getClut(256, 509);
        title->mp5[4].tpage_x = 896;
        title->mp5[4].tpage_y = 0;
        title->mp5[4].w = 12;
        title->mp5[4].h = 12;
        title->mp5[4].u = 0;
        title->mp5[4].v = 0;
        title->mp5[4].mw = 252;
        title->mp5[4].mh = 144;
        title->mp5[4].r = 128;
        title->mp5[4].g = 128;
        title->mp5[4].b = 128;

        title->tsize21 = 14;
        title->tsize22 = 14;
        title->tsize23 = 14;
        title->tsize24 = 14;
        title->tsize25 = 5;

        title->lodm = (TextChar *)malloc(19 * sizeof(TextChar));

        for (u_char i = 0; i < 19; i++)
        {
            graph_inittext(&title->lodm[i]);
        }

        u_char lodmt[] = {36, 79, 0, 89, 79, 85, 0, 87, 65, 78, 84, 0, 84, 79, 0, 76, 79, 65, 68};

        graph_settext(lodmt, title->lodm, 19);

        title->lodm2 = (TextChar *)malloc(17 * sizeof(TextChar));

        for (u_char i = 0; i < 17; i++)
        {
            graph_inittext(&title->lodm2[i]);
        }

        u_char lodmt2[] = {70, 82, 79, 77, 0, 45, 69, 77, 79, 82, 89, 0, 35, 65, 82, 68, 31};

        graph_settext(lodmt2, title->lodm2, 17);

        title->lod1 = (TextChar *)malloc(3 * sizeof(TextChar));

        for (u_char i = 0; i < 3; i++)
        {
            graph_inittext(&title->lod1[i]);
        }

        u_char lodt1[] = {57, 69, 83};

        graph_settext(lodt1, title->lod1, 3);

        title->lod2 = (TextChar *)malloc(2 * sizeof(TextChar));

        for (u_char i = 0; i < 2; i++)
        {
            graph_inittext(&title->lod2[i]);
        }

        u_char lodt2[] = {46, 79};

        graph_settext(lodt2, title->lod2, 2);

        title->tsize31 = 19;
        title->tsize32 = 17;
        title->tsize33 = 3;
        title->tsize34 = 2;

        title->mus1 = (TextChar *)malloc(10 * sizeof(TextChar));

        title->mus1[0].char_id = 45;
        title->mus1[0].clut = getClut(256, 509);
        title->mus1[0].tpage_x = 896;
        title->mus1[0].tpage_y = 0;
        title->mus1[0].w = 12;
        title->mus1[0].h = 12;
        title->mus1[0].u = 0;
        title->mus1[0].v = 0;
        title->mus1[0].mw = 252;
        title->mus1[0].mh = 144;
        title->mus1[0].r = 128;
        title->mus1[0].g = 128;
        title->mus1[0].b = 128;
        title->mus1[1].char_id = 85;
        title->mus1[1].clut = getClut(256, 509);
        title->mus1[1].tpage_x = 896;
        title->mus1[1].tpage_y = 0;
        title->mus1[1].w = 12;
        title->mus1[1].h = 12;
        title->mus1[1].u = 0;
        title->mus1[1].v = 0;
        title->mus1[1].mw = 252;
        title->mus1[1].mh = 144;
        title->mus1[1].r = 128;
        title->mus1[1].g = 128;
        title->mus1[1].b = 128;
        title->mus1[2].char_id = 83;
        title->mus1[2].clut = getClut(256, 509);
        title->mus1[2].tpage_x = 896;
        title->mus1[2].tpage_y = 0;
        title->mus1[2].w = 12;
        title->mus1[2].h = 12;
        title->mus1[2].u = 0;
        title->mus1[2].v = 0;
        title->mus1[2].mw = 252;
        title->mus1[2].mh = 144;
        title->mus1[2].r = 128;
        title->mus1[2].g = 128;
        title->mus1[2].b = 128;
        title->mus1[3].char_id = 73;
        title->mus1[3].clut = getClut(256, 509);
        title->mus1[3].tpage_x = 896;
        title->mus1[3].tpage_y = 0;
        title->mus1[3].w = 12;
        title->mus1[3].h = 12;
        title->mus1[3].u = 0;
        title->mus1[3].v = 0;
        title->mus1[3].mw = 252;
        title->mus1[3].mh = 144;
        title->mus1[3].r = 128;
        title->mus1[3].g = 128;
        title->mus1[3].b = 128;
        title->mus1[4].char_id = 67;
        title->mus1[4].clut = getClut(256, 509);
        title->mus1[4].tpage_x = 896;
        title->mus1[4].tpage_y = 0;
        title->mus1[4].w = 12;
        title->mus1[4].h = 12;
        title->mus1[4].u = 0;
        title->mus1[4].v = 0;
        title->mus1[4].mw = 252;
        title->mus1[4].mh = 144;
        title->mus1[4].r = 128;
        title->mus1[4].g = 128;
        title->mus1[4].b = 128;
        title->mus1[5].char_id = 26;
        title->mus1[5].clut = getClut(256, 509);
        title->mus1[5].tpage_x = 896;
        title->mus1[5].tpage_y = 0;
        title->mus1[5].w = 12;
        title->mus1[5].h = 12;
        title->mus1[5].u = 0;
        title->mus1[5].v = 0;
        title->mus1[5].mw = 252;
        title->mus1[5].mh = 144;
        title->mus1[5].r = 128;
        title->mus1[5].g = 128;
        title->mus1[5].b = 128;
        title->mus1[6].char_id = 0;
        title->mus1[6].clut = getClut(256, 509);
        title->mus1[6].tpage_x = 896;
        title->mus1[6].tpage_y = 0;
        title->mus1[6].w = 12;
        title->mus1[6].h = 12;
        title->mus1[6].u = 0;
        title->mus1[6].v = 0;
        title->mus1[6].mw = 252;
        title->mus1[6].mh = 144;
        title->mus1[6].r = 128;
        title->mus1[6].g = 128;
        title->mus1[6].b = 128;
        title->mus1[7].char_id = 16;
        title->mus1[7].clut = getClut(256, 509);
        title->mus1[7].tpage_x = 896;
        title->mus1[7].tpage_y = 0;
        title->mus1[7].w = 12;
        title->mus1[7].h = 12;
        title->mus1[7].u = 0;
        title->mus1[7].v = 0;
        title->mus1[7].mw = 252;
        title->mus1[7].mh = 144;
        title->mus1[7].r = 128;
        title->mus1[7].g = 128;
        title->mus1[7].b = 128;
        title->mus1[8].char_id = 16;
        title->mus1[8].clut = getClut(256, 509);
        title->mus1[8].tpage_x = 896;
        title->mus1[8].tpage_y = 0;
        title->mus1[8].w = 12;
        title->mus1[8].h = 12;
        title->mus1[8].u = 0;
        title->mus1[8].v = 0;
        title->mus1[8].mw = 252;
        title->mus1[8].mh = 144;
        title->mus1[8].r = 128;
        title->mus1[8].g = 128;
        title->mus1[8].b = 128;
        title->mus1[9].char_id = 16;
        title->mus1[9].clut = getClut(256, 509);
        title->mus1[9].tpage_x = 896;
        title->mus1[9].tpage_y = 0;
        title->mus1[9].w = 12;
        title->mus1[9].h = 12;
        title->mus1[9].u = 0;
        title->mus1[9].v = 0;
        title->mus1[9].mw = 252;
        title->mus1[9].mh = 144;
        title->mus1[9].r = 128;
        title->mus1[9].g = 128;
        title->mus1[9].b = 128;

        title->mus2 = (TextChar *)malloc(4 * sizeof(TextChar));

        title->mus2[0].char_id = 48;
        title->mus2[0].clut = getClut(256, 509);
        title->mus2[0].tpage_x = 896;
        title->mus2[0].tpage_y = 0;
        title->mus2[0].w = 12;
        title->mus2[0].h = 12;
        title->mus2[0].u = 0;
        title->mus2[0].v = 0;
        title->mus2[0].mw = 252;
        title->mus2[0].mh = 144;
        title->mus2[0].r = 128;
        title->mus2[0].g = 128;
        title->mus2[0].b = 128;
        title->mus2[1].char_id = 76;
        title->mus2[1].clut = getClut(256, 509);
        title->mus2[1].tpage_x = 896;
        title->mus2[1].tpage_y = 0;
        title->mus2[1].w = 12;
        title->mus2[1].h = 12;
        title->mus2[1].u = 0;
        title->mus2[1].v = 0;
        title->mus2[1].mw = 252;
        title->mus2[1].mh = 144;
        title->mus2[1].r = 128;
        title->mus2[1].g = 128;
        title->mus2[1].b = 128;
        title->mus2[2].char_id = 65;
        title->mus2[2].clut = getClut(256, 509);
        title->mus2[2].tpage_x = 896;
        title->mus2[2].tpage_y = 0;
        title->mus2[2].w = 12;
        title->mus2[2].h = 12;
        title->mus2[2].u = 0;
        title->mus2[2].v = 0;
        title->mus2[2].mw = 252;
        title->mus2[2].mh = 144;
        title->mus2[2].r = 128;
        title->mus2[2].g = 128;
        title->mus2[2].b = 128;
        title->mus2[3].char_id = 89;
        title->mus2[3].clut = getClut(256, 509);
        title->mus2[3].tpage_x = 896;
        title->mus2[3].tpage_y = 0;
        title->mus2[3].w = 12;
        title->mus2[3].h = 12;
        title->mus2[3].u = 0;
        title->mus2[3].v = 0;
        title->mus2[3].mw = 252;
        title->mus2[3].mh = 144;
        title->mus2[3].r = 128;
        title->mus2[3].g = 128;
        title->mus2[3].b = 128;

        title->mus3 = (TextChar *)malloc(4 * sizeof(TextChar));

        title->mus3[0].char_id = 34;
        title->mus3[0].clut = getClut(256, 509);
        title->mus3[0].tpage_x = 896;
        title->mus3[0].tpage_y = 0;
        title->mus3[0].w = 12;
        title->mus3[0].h = 12;
        title->mus3[0].u = 0;
        title->mus3[0].v = 0;
        title->mus3[0].mw = 252;
        title->mus3[0].mh = 144;
        title->mus3[0].r = 128;
        title->mus3[0].g = 128;
        title->mus3[0].b = 128;
        title->mus3[1].char_id = 65;
        title->mus3[1].clut = getClut(256, 509);
        title->mus3[1].tpage_x = 896;
        title->mus3[1].tpage_y = 0;
        title->mus3[1].w = 12;
        title->mus3[1].h = 12;
        title->mus3[1].u = 0;
        title->mus3[1].v = 0;
        title->mus3[1].mw = 252;
        title->mus3[1].mh = 144;
        title->mus3[1].r = 128;
        title->mus3[1].g = 128;
        title->mus3[1].b = 128;
        title->mus3[2].char_id = 67;
        title->mus3[2].clut = getClut(256, 509);
        title->mus3[2].tpage_x = 896;
        title->mus3[2].tpage_y = 0;
        title->mus3[2].w = 12;
        title->mus3[2].h = 12;
        title->mus3[2].u = 0;
        title->mus3[2].v = 0;
        title->mus3[2].mw = 252;
        title->mus3[2].mh = 144;
        title->mus3[2].r = 128;
        title->mus3[2].g = 128;
        title->mus3[2].b = 128;
        title->mus3[3].char_id = 75;
        title->mus3[3].clut = getClut(256, 509);
        title->mus3[3].tpage_x = 896;
        title->mus3[3].tpage_y = 0;
        title->mus3[3].w = 12;
        title->mus3[3].h = 12;
        title->mus3[3].u = 0;
        title->mus3[3].v = 0;
        title->mus3[3].mw = 252;
        title->mus3[3].mh = 144;
        title->mus3[3].r = 128;
        title->mus3[3].g = 128;
        title->mus3[3].b = 128;

        title->tsize2531 = 10;
        title->tsize2532 = 4;
        title->tsize2533 = 4;
    }
}

void title_update(IntroTitle *title)
{
    int fps = REGION_CODE == 0 ? 50 : 60;

    PlayerCtrl ctrl1 = controller_getplayer(0);
    PlayerCtrl ctrl2 = controller_getplayer(1);
    PlayerCtrl ctrl3 = controller_getplayer(2);
    PlayerCtrl ctrl4 = controller_getplayer(3);

    int porting1 = 0;
    int porting2 = 0;
    int porting3 = 0;
    int porting4 = 0;

    if (ctrl1.connected == TRUE)
    {
        controller_vibrate(ctrl1.porter);

        if (ctrl1.porter == 0x00)
        {
            porting1 = 0;
        }
        else if (ctrl1.porter == 0x01)
        {
            porting1 = 1;
        }
        else if (ctrl1.porter == 0x02)
        {
            porting1 = 2;
        }
        else if (ctrl1.porter == 0x03)
        {
            porting1 = 3;
        }
        else if (ctrl1.porter == 0x10)
        {
            porting1 = 4;
        }
        else if (ctrl1.porter == 0x11)
        {
            porting1 = 5;
        }
        else if (ctrl1.porter == 0x12)
        {
            porting1 = 6;
        }
        else if (ctrl1.porter == 0x13)
        {
            porting1 = 7;
        }

        if (title->tick >= fps * 11)
        {
            if (title->camMode == FALSE)
            {
                int max_opt = 0;

                switch (title->menu)
                {
                case 0:
                {
                    max_opt = 3;
                    break;
                }
                case 2:
                {
                    max_opt = 4;
                    break;
                }
                case 3:
                {
                    max_opt = 0;
                }
                case 253:
                {
                    max_opt = 3;
                    break;
                }
                default:
                {
                    break;
                }
                }

                if (!(ctrl1.btn & PAD_UP) || ctrl1.ls_y <= -63)
                {
                    if (!title->ver_pressed && title->menu != 3)
                    {
                        if (title->opt > 0)
                        {
                            title->opt--;
                        }
                        else
                        {
                            title->opt = max_opt - 1;
                        }

                        if (title->menu == 2)
                        {
                            while (1)
                            {
                                if (title->plr4 == 2 && title->opt == 2)
                                {
                                    title->opt--;
                                }
                                else if (title->plr3 == 2 && title->opt == 1)
                                {
                                    title->opt--;
                                }
                                else if (title->plr2 == 2 && title->opt == 0)
                                {
                                    title->opt = max_opt - 1;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }

                        sound_playsfx(&sfx[0], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        title->ver_pressed = TRUE;
                    }
                }
                else if (!(ctrl1.btn & PAD_DOWN) || ctrl1.ls_y >= 63)
                {
                    if (!title->ver_pressed && title->menu != 3)
                    {
                        if (title->opt < max_opt - 1)
                        {
                            title->opt++;
                        }
                        else
                        {
                            title->opt = 0;
                        }

                        if (title->menu == 2)
                        {
                            while (1)
                            {
                                if (title->plr2 == 2 && title->opt == 0)
                                {
                                    title->opt++;
                                }
                                else if (title->plr3 == 2 && title->opt == 1)
                                {
                                    title->opt++;
                                }
                                else if (title->plr4 == 2 && title->opt == 2)
                                {
                                    title->opt++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }

                        sound_playsfx(&sfx[0], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        title->ver_pressed = TRUE;
                    }
                }
                else
                {
                    title->ver_pressed = FALSE;
                }

                if (!(ctrl1.btn & PAD_LEFT) || ctrl1.ls_x <= -63)
                {
                    if (!title->hor_pressed)
                    {
                        int playsfx = FALSE;

                        if (title->menu == 253 && title->opt == 0)
                        {
                            playsfx = TRUE;

                            if (title->mus_track > 0)
                            {
                                title->mus_track--;
                            }
                            else
                            {
                                title->mus_track = 255;
                            }
                        }
                        else if (title->menu == 2 && title->opt >= 0 && title->opt < 3)
                        {
                            playsfx = TRUE;

                            if (title->opt == 0 && (title->plr3 >= 1 || title->plr4 >= 1))
                            {
                                title->plr2 = !title->plr2;
                            }
                            else if (title->opt == 1 && (title->plr2 >= 1 || title->plr4 >= 1))
                            {
                                title->plr3 = !title->plr3;
                            }
                            else if (title->opt == 2 && (title->plr2 >= 1 || title->plr3 >= 1))
                            {
                                title->plr4 = !title->plr4;
                            }
                        }
                        else if (title->menu == 3)
                        {
                            playsfx = TRUE;

                            title->opt = !title->opt;
                        }

                        if (playsfx)
                        {
                            sound_playsfx(&sfx[0], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        }

                        title->hor_pressed = TRUE;
                    }
                }
                else if (!(ctrl1.btn & PAD_RIGHT) || ctrl1.ls_x >= 63)
                {
                    if (!title->hor_pressed)
                    {
                        int playsfx = FALSE;

                        if (title->menu == 253 && title->opt == 0)
                        {
                            playsfx = TRUE;

                            if (title->mus_track < 255)
                            {
                                title->mus_track++;
                            }
                            else
                            {
                                title->mus_track = 0;
                            }
                        }
                        else if (title->menu == 2 && title->opt >= 0 && title->opt < 3)
                        {
                            playsfx = TRUE;

                            if (title->opt == 0 && (title->plr3 >= 1 || title->plr4 >= 1))
                            {
                                title->plr2 = !title->plr2;
                            }
                            else if (title->opt == 1 && (title->plr2 >= 1 || title->plr4 >= 1))
                            {
                                title->plr3 = !title->plr3;
                            }
                            else if (title->opt == 2 && (title->plr2 >= 1 || title->plr3 >= 1))
                            {
                                title->plr4 = !title->plr4;
                            }
                        }
                        else if (title->menu == 3)
                        {
                            playsfx = TRUE;

                            title->opt = !title->opt;
                        }

                        if (playsfx)
                        {
                            sound_playsfx(&sfx[0], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        }
                        title->hor_pressed = TRUE;
                    }
                }
                else
                {
                    title->hor_pressed = FALSE;
                }

                if (!(ctrl1.btn & PAD_CROSS) || !(ctrl1.btn & PAD_START))
                {
                    if (!title->accept_pressed)
                    {
                        title->accept_pressed = TRUE;

                        if (title->menu == 0 && title->opt == 0)
                        {
                            if (!(ctrl1.btn & PAD_L1) && !(ctrl1.btn & PAD_R1))
                            {
                                title->menu = 253;
                                title->opt = 0;
                                sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);

                                // DATALOAD memdata = memcard_load(ctrl1.porter, REGION_CODE);

                                // if (memdata.load)
                                // {
                                //     title->mus_track = memdata.data.mus;
                                // }
                            }
                            else if ((!(ctrl1.btn & PAD_L3) && !(ctrl1.btn & PAD_R3)) && ctrl1.type == 0x7)
                            {
                                title->camMode = TRUE;
                                title->lockin_pressed = TRUE;
                                sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            }
                            else
                            {
                                // Does nothing for now...
                            }
                        }
                        else if (title->menu == 0 && title->opt == 1)
                        {
                            // Does nothing for now...
                        }
                        else if (title->menu == 0 && title->opt == 2)
                        {
                            title->menu = 2;
                            title->opt = 0;
                            sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        }
                        else if (title->menu == 2)
                        {
                            title->menu = 3;
                            title->opt = 0;
                            sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        }
                        else if (title->menu == 3)
                        {
                            sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            lvl = 2;

                            plr[0] = title->plr2;
                            plr[1] = title->plr3;
                            plr[2] = title->plr4;
                            memlod = title->opt == 0 ? FALSE : TRUE;
                            
                            free(title->opt1);
                            free(title->opt2);
                            free(title->opt3);
                            free(title->mp1);
                            free(title->mp2);
                            free(title->mp3);
                            free(title->mp4);
                            free(title->mp5);
                            free(title->lodm);
                            free(title->lodm2);
                            free(title->lod1);
                            free(title->lod2);
                            free(title->mus1);
                            free(title->mus2);
                            free(title->mus3);
                            
                            title->active = FALSE;
                            return;
                        }
                        else if (title->menu == 253 && title->opt == 1)
                        {
                            sound_stopmusic();
                            sound_clearmusic();

                            switch (title->mus_track)
                            {
                            case 0:
                            {
                                u_long *file;

                                if ((file = cdrom_readfile("\\DATA\\MUS\\INTRO1.MUS;1")))
                                {
                                    sound_setbpm(115);
                                    sound_loadmusic(file, 49, 5);
                                    free(file);

                                    sound_playmusic();
                                }
                                break;
                            }
                            case 1:
                            {
                                u_long *file;

                                if ((file = cdrom_readfile("\\DATA\\MUS\\INTRO2.MUS;1")))
                                {
                                    sound_setbpm(145);
                                    sound_loadmusic(file, 225, 4);
                                    free(file);

                                    sound_playmusic();
                                }
                                break;
                            }
                            case 2:
                            {
                                u_long *file;

                                if ((file = cdrom_readfile("\\DATA\\MUS\\TITLE.MUS;1")))
                                {
                                    sound_setbpm(120);
                                    sound_loadmusic(file, 44, 5);
                                    free(file);

                                    sound_playmusic();
                                }
                                break;
                            }
                            }
                        }
                        else if (title->menu == 253 && title->opt == 2)
                        {
                            title->menu = 0;
                            title->opt = 0;
                            sound_playsfx(&sfx[3], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            sound_stopmusic();

                            // DATALOAD memsave;

                            // memsave.data.mus = title->mus_track;
                            // memcard_save(ctrl1.porter, &memsave, REGION_CODE);

                            title->mus_track = 0;
                        }
                    }
                }
                else
                {
                    title->accept_pressed = FALSE;
                }

                if (!(ctrl1.btn & PAD_CIRCLE))
                {
                    if (!title->decline_pressed)
                    {
                        title->decline_pressed = TRUE;

                        if (title->menu == 2)
                        {
                            sound_playsfx(&sfx[3], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            title->menu = 0;
                            title->opt = 0;
                            title->plr2 = 1;
                            title->plr3 = 0;
                            title->plr4 = 0;
                        }
                        else if (title->menu == 3)
                        {
                            sound_playsfx(&sfx[3], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            title->menu = 2;
                            title->opt = 0;

                            while (1)
                            {
                                if (title->plr2 == 2 && title->opt == 0)
                                {
                                    title->opt++;
                                }
                                else if (title->plr3 == 2 && title->opt == 1)
                                {
                                    title->opt++;
                                }
                                else if (title->plr4 == 2 && title->opt == 2)
                                {
                                    title->opt++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else if (title->menu == 253)
                        {
                            sound_playsfx(&sfx[3], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                            title->menu = 0;
                            title->opt = 0;
                            title->mus_track = 0;
                            sound_stopmusic();
                        }
                    }
                }
                else
                {
                    title->decline_pressed = FALSE;
                }
            }
            else
            {
                int deadzone = 32;

                graph.camRot.vy -= (ctrl1.rs_x > deadzone || ctrl1.rs_x < -deadzone ? (ctrl1.rs_x / 4) : 0) * graph.delta;
                graph.camRot.vx += (ctrl1.rs_y > deadzone || ctrl1.rs_y < -deadzone ? (ctrl1.rs_y / 4) : 0) * graph.delta;

                if (graph.camRot.vx > 1000)
                {
                    graph.camRot.vx = 1000;
                }
                else if (graph.camRot.vx < -1000)
                {
                    graph.camRot.vx = -1000;
                }

                long yaw = graph.camRot.vy;
                long pitch = graph.camRot.vx;

                VECTOR forward, right, up;

                forward.vx = csin(yaw) * ccos(pitch) >> 12;
                forward.vy = -csin(pitch);
                forward.vz = ccos(yaw) * ccos(pitch) >> 12;

                right.vx = csin(yaw + 1024);
                right.vy = 0;
                right.vz = ccos(yaw + 1024);

                up.vx = csin(yaw) * csin(pitch) >> 12;
                up.vy = ccos(pitch);
                up.vz = ccos(yaw) * csin(pitch) >> 12;

                graph.camPos.vx -= ((forward.vx * (ctrl1.ls_y > deadzone || ctrl1.ls_y < -deadzone ? (ctrl1.ls_y / 4) : 0)) * graph.delta) >> 12;
                graph.camPos.vy -= ((forward.vy * (ctrl1.ls_y > deadzone || ctrl1.ls_y < -deadzone ? (ctrl1.ls_y / 4) : 0)) * graph.delta) >> 12;
                graph.camPos.vz += ((forward.vz * (ctrl1.ls_y > deadzone || ctrl1.ls_y < -deadzone ? (ctrl1.ls_y / 4) : 0)) * graph.delta) >> 12;

                graph.camPos.vx -= ((right.vx * (ctrl1.ls_x > deadzone || ctrl1.ls_x < -deadzone ? (ctrl1.ls_x / 4) : 0)) * graph.delta) >> 12;
                graph.camPos.vz += ((right.vz * (ctrl1.ls_x > deadzone || ctrl1.ls_x < -deadzone ? (ctrl1.ls_x / 4) : 0)) * graph.delta) >> 12;

                if (!(ctrl1.btn & PAD_L1) || !(ctrl1.btn & PAD_R1))
                {
                    graph.camPos.vx -= ((up.vx * 32) * graph.delta) >> 12;
                    graph.camPos.vy -= ((up.vy * 32) * graph.delta) >> 12;
                    graph.camPos.vz += ((up.vz * 32) * graph.delta) >> 12;
                }
                else if (!(ctrl1.btn & PAD_L2) || !(ctrl1.btn & PAD_R2))
                {
                    graph.camPos.vx += ((up.vx * 32) * graph.delta) >> 12;
                    graph.camPos.vy += ((up.vy * 32) * graph.delta) >> 12;
                    graph.camPos.vz -= ((up.vz * 32) * graph.delta) >> 12;
                }

                if (!(ctrl1.btn & PAD_L3) && !(ctrl1.btn & PAD_R3))
                {
                    if (!title->lockin_pressed)
                    {
                        title->lockin_pressed = TRUE;

                        title->camLock = !title->camLock;
                    }
                }
                else
                {
                    title->lockin_pressed = FALSE;
                }

                if ((!(ctrl1.btn & PAD_CIRCLE)) || ctrl1.type != 0x7)
                {
                    if (!title->decline_pressed)
                    {
                        title->decline_pressed = TRUE;

                        graph.camPos.vx = 0;
                        graph.camPos.vy = 0;
                        graph.camPos.vz = 0;
                        graph.camRot.vx = 0;
                        graph.camRot.vy = 0;
                        graph.camRot.vz = 0;

                        title->camLock = FALSE;

                        sound_playsfx(&sfx[3], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        title->camMode = FALSE;
                    }
                }
                else
                {
                    title->decline_pressed = FALSE;
                }
            }
        }
    }

    if (ctrl2.connected == TRUE)
    {
        controller_vibrate(ctrl2.porter);

        if (ctrl2.porter == 0x00)
        {
            porting2 = 0;
        }
        else if (ctrl2.porter == 0x01)
        {
            porting2 = 1;
        }
        else if (ctrl2.porter == 0x02)
        {
            porting2 = 2;
        }
        else if (ctrl2.porter == 0x03)
        {
            porting2 = 3;
        }
        else if (ctrl2.porter == 0x10)
        {
            porting2 = 4;
        }
        else if (ctrl2.porter == 0x11)
        {
            porting2 = 5;
        }
        else if (ctrl2.porter == 0x12)
        {
            porting2 = 6;
        }
        else if (ctrl2.porter == 0x13)
        {
            porting2 = 7;
        }

        if (title->tick >= fps * 11)
        {
            if (title->menu == 2)
            {
                if ((!(ctrl2.btn & PAD_CROSS) || !(ctrl2.btn & PAD_START)) && title->plr2 != 2)
                {
                    title->plr2 = 2;
                    sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);

                    while (1)
                    {
                        if (title->plr2 == 2 && title->opt == 0)
                        {
                            title->opt++;
                        }
                        else if (title->plr3 == 2 && title->opt == 1)
                        {
                            title->opt++;
                        }
                        else if (title->plr4 == 2 && title->opt == 2)
                        {
                            title->opt++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    if (ctrl3.connected == TRUE)
    {
        controller_vibrate(ctrl3.porter);

        if (ctrl3.porter == 0x00)
        {
            porting3 = 0;
        }
        else if (ctrl3.porter == 0x01)
        {
            porting3 = 1;
        }
        else if (ctrl3.porter == 0x02)
        {
            porting3 = 2;
        }
        else if (ctrl3.porter == 0x03)
        {
            porting3 = 3;
        }
        else if (ctrl3.porter == 0x10)
        {
            porting3 = 4;
        }
        else if (ctrl3.porter == 0x11)
        {
            porting3 = 5;
        }
        else if (ctrl3.porter == 0x12)
        {
            porting3 = 6;
        }
        else if (ctrl3.porter == 0x13)
        {
            porting3 = 7;
        }

        if (title->tick >= fps * 11)
        {
            if (title->menu == 2)
            {
                if ((!(ctrl3.btn & PAD_CROSS) || !(ctrl3.btn & PAD_START)) && title->plr3 != 2)
                {
                    title->plr3 = 2;
                    sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);

                    while (1)
                    {
                        if (title->plr2 == 2 && title->opt == 0)
                        {
                            title->opt++;
                        }
                        else if (title->plr3 == 2 && title->opt == 1)
                        {
                            title->opt++;
                        }
                        else if (title->plr4 == 2 && title->opt == 2)
                        {
                            title->opt++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    if (ctrl4.connected == TRUE)
    {
        controller_vibrate(ctrl4.porter);

        if (ctrl4.porter == 0x00)
        {
            porting4 = 0;
        }
        else if (ctrl4.porter == 0x01)
        {
            porting4 = 1;
        }
        else if (ctrl4.porter == 0x02)
        {
            porting4 = 2;
        }
        else if (ctrl4.porter == 0x03)
        {
            porting4 = 3;
        }
        else if (ctrl4.porter == 0x10)
        {
            porting4 = 4;
        }
        else if (ctrl4.porter == 0x11)
        {
            porting4 = 5;
        }
        else if (ctrl4.porter == 0x12)
        {
            porting4 = 6;
        }
        else if (ctrl4.porter == 0x13)
        {
            porting4 = 7;
        }

        if (title->tick >= fps * 11)
        {
            if (title->menu == 2)
            {
                if ((!(ctrl4.btn & PAD_CROSS) || !(ctrl4.btn & PAD_START)) && title->plr4 != 2)
                {
                    title->plr4 = 2;
                    sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);

                    while (1)
                    {
                        if (title->plr2 == 2 && title->opt == 0)
                        {
                            title->opt++;
                        }
                        else if (title->plr3 == 2 && title->opt == 1)
                        {
                            title->opt++;
                        }
                        else if (title->plr4 == 2 && title->opt == 2)
                        {
                            title->opt++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    switch (title->title_s)
    {
    case 0:
    {
        title->spr[0].ScaleVector.vx -= 256 * graph.delta;
        title->spr[0].MovVector.vx -= 8 * graph.delta;

        if (title->spr[0].MovVector.vx < -64)
        {
            title->spr[0].MovVector.vx = -64;
        }

        if (title->spr[0].ScaleVector.vx < 1024)
        {
            title->spr[0].ScaleVector.vx = 1024;
        }

        if (title->spr[0].MovVector.vx == -64 && title->spr[0].ScaleVector.vx == 1024)
        {
            title->title_s++;
        }

        break;
    }
    case 1:
    {
        title->spr[0].ScaleVector.vx += 512 * graph.delta;
        title->spr[0].MovVector.vx += 4 * graph.delta;

        if (title->spr[0].MovVector.vx > 0)
        {
            title->spr[0].MovVector.vx = 0;
        }

        if (title->spr[0].ScaleVector.vx > ONE * 2)
        {
            title->spr[0].ScaleVector.vx = ONE * 2;
        }

        if (title->spr[0].MovVector.vx == 0 && title->spr[0].ScaleVector.vx == ONE * 2)
        {
            title->title_s++;
        }

        break;
    }
    case 2:
    {
        if (LNG == 1)
        {
            if (title->tick >= (fps * 2) + (fps / 2))
            {
                if (title->tick == (fps * 2) + (fps / 2))
                {
                    control.motor[porting1][0] = 1;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 1;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 1;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 1;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                }

                title->spr[1].ScaleVector.vx += 512 * graph.delta;
                title->spr[1].ScaleVector.vy += 512 * graph.delta;

                if (title->spr[1].ScaleVector.vx > ONE * 2)
                {
                    title->spr[1].ScaleVector.vx = ONE * 2;
                }

                if (title->spr[1].ScaleVector.vy > ONE * 2)
                {
                    title->spr[1].ScaleVector.vy = ONE * 2;
                }

                if (title->spr[1].ScaleVector.vx == ONE * 2 && title->spr[1].ScaleVector.vy == ONE * 2)
                {
                    control.motor[porting1][0] = 0;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 0;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 0;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 0;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                    title->title_s++;
                }
            }
        }
        else if (LNG == 0)
        {
            if (title->tick >= (fps * 2) + (fps / 2))
            {
                if (title->tick == (fps * 2) + (fps / 2))
                {
                    control.motor[porting1][0] = 1;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 1;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 1;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 1;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                }

                title->spr[1].ScaleVector.vx -= 256 * graph.delta;
                title->spr[1].MovVector.vx += 8 * graph.delta;

                if (title->spr[1].MovVector.vx > -20)
                {
                    title->spr[1].MovVector.vx = -20;
                }

                if (title->spr[1].ScaleVector.vx < 1024)
                {
                    title->spr[1].ScaleVector.vx = 1024;
                }

                title->spr[2].ScaleVector.vx -= 256 * graph.delta;
                title->spr[2].MovVector.vx -= 8 * graph.delta;

                if (title->spr[2].MovVector.vx < 20)
                {
                    title->spr[2].MovVector.vx = 20;
                }

                if (title->spr[2].ScaleVector.vx < 1024)
                {
                    title->spr[2].ScaleVector.vx = 1024;
                }

                if (title->spr[1].MovVector.vx == -20 && title->spr[1].ScaleVector.vx == 1024 && title->spr[2].MovVector.vx == 20 && title->spr[2].ScaleVector.vx == 1024)
                {
                    control.motor[porting1][0] = 0;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 0;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 0;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 0;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                    title->title_s++;
                }
            }
        }

        break;
    }
    case 3:
    {
        if (LNG == 1)
        {
            if (title->tick >= (fps * 3) + (fps / 4))
            {
                if (title->tick == (fps * 3) + (fps / 4))
                {
                    control.motor[porting1][0] = 1;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 1;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 1;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 1;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                }

                title->spr[2].ScaleVector.vx += 512 * graph.delta;
                title->spr[2].ScaleVector.vy += 512 * graph.delta;

                if (title->spr[2].ScaleVector.vx > ONE * 2)
                {
                    title->spr[2].ScaleVector.vx = ONE * 2;
                }

                if (title->spr[2].ScaleVector.vy > ONE * 2)
                {
                    title->spr[2].ScaleVector.vy = ONE * 2;
                }

                if (title->spr[2].ScaleVector.vx == ONE * 2 && title->spr[2].ScaleVector.vy == ONE * 2)
                {
                    control.motor[porting1][0] = 0;
                    control.motor[porting1][1] = 0;
                    control.vib_sync[porting1] = TRUE;
                    control.motor[porting2][0] = 0;
                    control.motor[porting2][1] = 0;
                    control.vib_sync[porting2] = TRUE;
                    control.motor[porting3][0] = 0;
                    control.motor[porting3][1] = 0;
                    control.vib_sync[porting3] = TRUE;
                    control.motor[porting4][0] = 0;
                    control.motor[porting4][1] = 0;
                    control.vib_sync[porting4] = TRUE;
                    title->title_s++;
                }
            }
        }
        else if (LNG == 0)
        {
            title->spr[1].ScaleVector.vx += 512 * graph.delta;
            title->spr[1].MovVector.vx -= 4 * graph.delta;

            if (title->spr[1].MovVector.vx < -80)
            {
                title->spr[1].MovVector.vx = -80;
            }

            if (title->spr[1].ScaleVector.vx > ONE * 2)
            {
                title->spr[1].ScaleVector.vx = ONE * 2;
            }

            title->spr[2].ScaleVector.vx += 512 * graph.delta;
            title->spr[2].MovVector.vx += 4 * graph.delta;

            if (title->spr[2].MovVector.vx > 80)
            {
                title->spr[2].MovVector.vx = 80;
            }

            if (title->spr[2].ScaleVector.vx > ONE * 2)
            {
                title->spr[2].ScaleVector.vx = ONE * 2;
            }

            if (title->spr[1].MovVector.vx == -80 && title->spr[1].ScaleVector.vx == ONE * 2 && title->spr[2].MovVector.vx == 80 && title->spr[2].ScaleVector.vx == ONE * 2)
            {
                title->title_s = 5;
            }
        }

        break;
    }
    case 4:
    {
        if (title->tick >= fps * 4)
        {
            if (title->tick == fps * 4)
            {
                control.motor[porting1][0] = 1;
                control.motor[porting1][1] = 0;
                control.vib_sync[porting1] = TRUE;
                control.motor[porting2][0] = 1;
                control.motor[porting2][1] = 0;
                control.vib_sync[porting2] = TRUE;
                control.motor[porting3][0] = 1;
                control.motor[porting3][1] = 0;
                control.vib_sync[porting3] = TRUE;
                control.motor[porting4][0] = 1;
                control.motor[porting4][1] = 0;
                control.vib_sync[porting4] = TRUE;
            }
            title->spr[3].ScaleVector.vx += 512 * graph.delta;
            title->spr[3].ScaleVector.vy += 512 * graph.delta;

            if (title->spr[3].ScaleVector.vx > ONE * 2)
            {
                title->spr[3].ScaleVector.vx = ONE * 2;
            }

            if (title->spr[3].ScaleVector.vy > ONE * 2)
            {
                title->spr[3].ScaleVector.vy = ONE * 2;
            }

            if (title->spr[3].ScaleVector.vx == ONE * 2 && title->spr[3].ScaleVector.vy == ONE * 2)
            {
                control.motor[porting1][0] = 0;
                control.motor[porting1][1] = 0;
                control.vib_sync[porting1] = TRUE;
                control.motor[porting2][0] = 0;
                control.motor[porting2][1] = 0;
                control.vib_sync[porting2] = TRUE;
                control.motor[porting3][0] = 0;
                control.motor[porting3][1] = 0;
                control.vib_sync[porting3] = TRUE;
                control.motor[porting4][0] = 0;
                control.motor[porting4][1] = 0;
                control.vib_sync[porting4] = TRUE;
                title->title_s++;
            }
        }

        break;
    }
    case 5:
    {
        if (title->tick >= fps * 5)
        {
            if (title->rot.vy < ONE)
            {
                title->rot.vy += (REGION_CODE != 0 ? 16 : 20) * graph.delta;
            }
            else
            {
                title->rot.vy = ONE;
            }

            if (title->mov.vy > 512)
            {
                title->mov.vy -= (REGION_CODE != 0 ? 16 : 20) * graph.delta;
            }
            else
            {
                title->mov.vy = 512;
            }

            if (title->rot.vy == ONE && title->mov.vy == 512)
            {
                title->title_s++;
            }
        }

        break;
    }
    default:
    {
        break;
    }
    }

    if (title->camMode == FALSE)
    {
        if (title->tick < fps * 11)
        {
            // VECTOR dir;

            // dir.vx = title->mov.vx + graph.camPos.vx;
            // dir.vy = (title->mov.vy - 512) + graph.camPos.vy;
            // dir.vz = title->mov.vz + graph.camPos.vz;

            // graph.camRot.vy = ratan2(dir.vz, dir.vx) + (-1024);

            // long distXZ = SquareRoot0(
            //     (dir.vx * dir.vx) +
            //     (dir.vz * dir.vz));

            // graph.camRot.vx = ratan2(dir.vy, distXZ);

            title->tick += graph.delta;
        }
        else
        {
            // title->mov.vz = 512;

            switch (title->menu)
            {
            case 0:
            {
                graph_drawtext(128, 224 - 48, title->opt == 0 ? 128 : 63, title->tsize01, 0, title->opt1, 1);
                graph_drawtext(128, 224 - 24, title->opt == 1 ? 128 : 63, title->tsize02, 0, title->opt2, 1);
                graph_drawtext(128, 224, title->opt == 2 ? 128 : 63, title->tsize03, 0, title->opt3, 1);

                graph_drawtile(32, 160, 192, 96);
                break;
            }
            case 2:
            {
                switch (title->plr2)
                {
                case 0:
                {
                    title->mp2[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 46 : 46;
                    title->mp2[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 79 : 73;
                    title->mp2[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 77;
                    title->mp2[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 69 : 73;
                    title->mp2[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 67;
                    break;
                }
                case 1:
                {
                    title->mp2[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 33 : 50;
                    title->mp2[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 41 : 79;
                    title->mp2[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 66;
                    title->mp2[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 79;
                    title->mp2[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 84;
                    break;
                }
                case 2:
                {
                    title->mp2[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 40 : 47;
                    title->mp2[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 85 : 77;
                    title->mp2[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 77 : 0;
                    title->mp2[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 65 : 0;
                    title->mp2[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 0;
                    break;
                }
                default:
                {
                    break;
                }
                }

                switch (title->plr3)
                {
                case 0:
                {
                    title->mp3[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 46 : 46;
                    title->mp3[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 79 : 73;
                    title->mp3[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 77;
                    title->mp3[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 69 : 73;
                    title->mp3[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 67;
                    break;
                }
                case 1:
                {
                    title->mp3[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 33 : 50;
                    title->mp3[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 41 : 79;
                    title->mp3[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 66;
                    title->mp3[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 79;
                    title->mp3[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 84;
                    break;
                }
                case 2:
                {
                    title->mp3[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 40 : 47;
                    title->mp3[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 85 : 77;
                    title->mp3[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 77 : 0;
                    title->mp3[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 65 : 0;
                    title->mp3[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 0;
                    break;
                }
                default:
                {
                    break;
                }
                }

                switch (title->plr4)
                {
                case 0:
                {
                    title->mp4[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 46 : 46;
                    title->mp4[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 79 : 73;
                    title->mp4[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 77;
                    title->mp4[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 69 : 73;
                    title->mp4[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 67;
                    break;
                }
                case 1:
                {
                    title->mp4[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 33 : 50;
                    title->mp4[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 41 : 79;
                    title->mp4[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 66;
                    title->mp4[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 79;
                    title->mp4[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 0 : 84;
                    break;
                }
                case 2:
                {
                    title->mp4[9 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 40 : 47;
                    title->mp4[10 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 85 : 77;
                    title->mp4[11 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 77 : 0;
                    title->mp4[12 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 65 : 0;
                    title->mp4[13 + (LNG == 0 ? 1 : 0)].char_id = LNG == 1 ? 78 : 0;
                    break;
                }
                default:
                {
                    break;
                }
                }

                graph_drawtext(32, 48, 128, title->tsize21, 1, title->mp1, 1);
                graph_drawtext(32, 72, title->opt == 0 || title->plr2 == 2 ? 128 : 63, title->tsize22, 1, title->mp2, 1);
                graph_drawtext(32, 96, title->opt == 1 || title->plr3 == 2 ? 128 : 63, title->tsize23, 1, title->mp3, 1);
                graph_drawtext(32, 120, title->opt == 2 || title->plr4 == 2 ? 128 : 63, title->tsize24, 1, title->mp4, 1);
                graph_drawtext(128, 224, title->opt == 3 ? 128 : 63, title->tsize25, 0, title->mp5, 1);

                // graph_drawtile(32, 160, 192, 96);
                break;
            }
            case 3:
            {
                graph_drawtext(128, 128 - 28, 128, title->tsize31, 0, title->lodm, 1);
                graph_drawtext(128, 128 - 16, 128, title->tsize32, 0, title->lodm2, 1);
                graph_drawtext(64, 128 + 16, title->opt == 1 ? 128 : 63, title->tsize33, 0, title->lod1, 1);
                graph_drawtext(192, 128 + 16, title->opt == 0 ? 128 : 63, title->tsize34, 0, title->lod2, 1);

                break;
            }
            case 253:
            {
                if (LNG == 0)
                {
                    title->mus1[10].char_id = 16 + (title->mus_track == 0 ? 0 : title->mus_track % 10);
                    title->mus1[9].char_id = 16 + ((title->mus_track == 0 ? 0 : title->mus_track / 10) % 10);
                    title->mus1[8].char_id = 16 + (title->mus_track == 0 ? 0 : title->mus_track / 100);
                }
                else
                {
                    title->mus1[9].char_id = 16 + (title->mus_track == 0 ? 0 : title->mus_track % 10);
                    title->mus1[8].char_id = 16 + ((title->mus_track == 0 ? 0 : title->mus_track / 10) % 10);
                    title->mus1[7].char_id = 16 + (title->mus_track == 0 ? 0 : title->mus_track / 100);
                }

                graph_drawtext(128, 224 - 48, title->opt == 0 ? 128 : 63, title->tsize2531, 0, title->mus1, 1);
                graph_drawtext(128, 224 - 24, title->opt == 1 ? 128 : 63, title->tsize2532, 0, title->mus2, 1);
                graph_drawtext(128, 224, title->opt == 2 ? 128 : 63, title->tsize2533, 0, title->mus3, 1);

                graph_drawtile(32, 160, 192, 96);
                break;
            }
            default:
            {
                break;
            }
            }

            // if (LNG == 2)
            // {
            //     u_short num1 = title->opt1[0].char_id % 10;
            //     u_short num2 = (title->opt1[0].char_id == 0 ? 0 : title->opt1[0].char_id/10) % 10;
            //     u_short num3 = (title->opt1[0].char_id == 0 ? 0 : title->opt1[0].char_id/100);

            //     title->debug[2].char_id = 3 + num1;
            //     title->debug[1].char_id = 3 + num2;
            //     title->debug[0].char_id = 3 + num3;

            //     graph_drawtext(128, 32, 128, col, 3, title->debug);
            // }
        }

        if (title->menu != 1 && title->menu != 2 && title->menu != 3)
        {
            for (int i = 0; i < 4; i++)
            {
                graph_drawsprite(title->spr[i], OTLEN - 1);
            }
        }
    }
    else
    {
        // title->mov.vy += 8;

        if (title->camLock)
        {
            VECTOR dir;

            dir.vx = title->mov.vx + graph.camPos.vx;
            dir.vy = (title->mov.vy - 512) + graph.camPos.vy;
            dir.vz = title->mov.vz + graph.camPos.vz;

            graph.camRot.vy = ratan2(dir.vz, dir.vx) + (-1024);

            long distXZ = SquareRoot0(
                (dir.vx * dir.vx) +
                (dir.vz * dir.vz));

            graph.camRot.vx = ratan2(dir.vy, distXZ);
        }
    }

    if (title->menu != 1 && title->menu != 2 && title->menu != 3)
    {
        game_drawmodel(0, title->mov, title->rot, title->scl, 0, 0, getTPage(0, 0, 256, 0), getClut(256, 448));
    }
}