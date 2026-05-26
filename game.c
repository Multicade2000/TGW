#include "game.h"

#define MAX_MDLS 2

int LNG = 0;
int lvl = 0;

int reseter = FALSE;

u_int gticker = 0;

static unsigned char ramAddr[0x40000];
Model mdls[MAX_MDLS];

IntroModel *intro = NULL;
IntroCircus *circ = NULL;
IntroTitle *title = NULL;
SceneBattle *btl = NULL;

VAGsound sfx[MAX_SNDS];

u_char plr[3];
u_char memlod = FALSE;

// ((void (*)())0xBFC00000)(); Reset console

void game_init()
{
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));
    region_init();
    graph_init(REGION_CODE);
    sound_init();
    cdrom_init();
    memcard_init();
    controller_init();

    mdls[0].mdl = NULL;
    mdls[1].mdl = NULL;

    for (u_int i = 0; i < MAX_SNDS; i++)
    {
        sfx[i].spu_address = NULL;
    }

    switch (REGION_CODE)
    {
    case 0:
    {
        u_char vert_pressed = FALSE;

        u_long *file;

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FLAGS.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FONT.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU1A.VAG;1")))
        {
            sfx[0].spu_address = sound_settransfer(&sfx[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU2.VAG;1")))
        {
            sfx[2].spu_address = sound_settransfer(&sfx[2], file);

            free(file);
        }

        TextChar *ro_t = (TextChar *)malloc(6 * sizeof(TextChar));

        ro_t[0].char_id = 50;
        ro_t[0].clut = getClut(256, 509);
        ro_t[0].tpage_x = 896;
        ro_t[0].tpage_y = 0;
        ro_t[0].w = 12;
        ro_t[0].h = 12;
        ro_t[0].u = 0;
        ro_t[0].v = 0;
        ro_t[0].mw = 252;
        ro_t[0].mh = 144;
        ro_t[0].r = 128;
        ro_t[0].g = 128;
        ro_t[0].b = 128;
        ro_t[1].char_id = 79;
        ro_t[1].clut = getClut(256, 509);
        ro_t[1].tpage_x = 896;
        ro_t[1].tpage_y = 0;
        ro_t[1].w = 12;
        ro_t[1].h = 12;
        ro_t[1].u = 0;
        ro_t[1].v = 0;
        ro_t[1].mw = 252;
        ro_t[1].mh = 144;
        ro_t[1].r = 128;
        ro_t[1].g = 128;
        ro_t[1].b = 128;
        ro_t[2].char_id = 77;
        ro_t[2].clut = getClut(256, 509);
        ro_t[2].tpage_x = 896;
        ro_t[2].tpage_y = 0;
        ro_t[2].w = 12;
        ro_t[2].h = 12;
        ro_t[2].u = 0;
        ro_t[2].v = 0;
        ro_t[2].mw = 252;
        ro_t[2].mh = 144;
        ro_t[2].r = 128;
        ro_t[2].g = 128;
        ro_t[2].b = 128;
        ro_t[3].char_id = 230;
        ro_t[3].clut = getClut(256, 509);
        ro_t[3].tpage_x = 896;
        ro_t[3].tpage_y = 0;
        ro_t[3].w = 12;
        ro_t[3].h = 12;
        ro_t[3].u = 0;
        ro_t[3].v = 0;
        ro_t[3].mw = 252;
        ro_t[3].mh = 144;
        ro_t[3].r = 128;
        ro_t[3].g = 128;
        ro_t[3].b = 128;
        ro_t[4].char_id = 78;
        ro_t[4].clut = getClut(256, 509);
        ro_t[4].tpage_x = 896;
        ro_t[4].tpage_y = 0;
        ro_t[4].w = 12;
        ro_t[4].h = 12;
        ro_t[4].u = 0;
        ro_t[4].v = 0;
        ro_t[4].mw = 252;
        ro_t[4].mh = 144;
        ro_t[4].r = 128;
        ro_t[4].g = 128;
        ro_t[4].b = 128;
        ro_t[5].char_id = 229;
        ro_t[5].clut = getClut(256, 509);
        ro_t[5].tpage_x = 896;
        ro_t[5].tpage_y = 0;
        ro_t[5].w = 12;
        ro_t[5].h = 12;
        ro_t[5].u = 0;
        ro_t[5].v = 0;
        ro_t[5].mw = 252;
        ro_t[5].mh = 144;
        ro_t[5].r = 128;
        ro_t[5].g = 128;
        ro_t[5].b = 128;

        TextChar *en_t = (TextChar *)malloc(7 * sizeof(TextChar));

        en_t[0].char_id = 37;
        en_t[0].clut = getClut(256, 509);
        en_t[0].tpage_x = 896;
        en_t[0].tpage_y = 0;
        en_t[0].w = 12;
        en_t[0].h = 12;
        en_t[0].u = 0;
        en_t[0].v = 0;
        en_t[0].mw = 252;
        en_t[0].mh = 144;
        en_t[0].r = 128;
        en_t[0].g = 128;
        en_t[0].b = 128;
        en_t[1].char_id = 78;
        en_t[1].clut = getClut(256, 509);
        en_t[1].tpage_x = 896;
        en_t[1].tpage_y = 0;
        en_t[1].w = 12;
        en_t[1].h = 12;
        en_t[1].u = 0;
        en_t[1].v = 0;
        en_t[1].mw = 252;
        en_t[1].mh = 144;
        en_t[1].r = 128;
        en_t[1].g = 128;
        en_t[1].b = 128;
        en_t[2].char_id = 71;
        en_t[2].clut = getClut(256, 509);
        en_t[2].tpage_x = 896;
        en_t[2].tpage_y = 0;
        en_t[2].w = 12;
        en_t[2].h = 12;
        en_t[2].u = 0;
        en_t[2].v = 0;
        en_t[2].mw = 252;
        en_t[2].mh = 144;
        en_t[2].r = 128;
        en_t[2].g = 128;
        en_t[2].b = 128;
        en_t[3].char_id = 76;
        en_t[3].clut = getClut(256, 509);
        en_t[3].tpage_x = 896;
        en_t[3].tpage_y = 0;
        en_t[3].w = 12;
        en_t[3].h = 12;
        en_t[3].u = 0;
        en_t[3].v = 0;
        en_t[3].mw = 252;
        en_t[3].mh = 144;
        en_t[3].r = 128;
        en_t[3].g = 128;
        en_t[3].b = 128;
        en_t[4].char_id = 73;
        en_t[4].clut = getClut(256, 509);
        en_t[4].tpage_x = 896;
        en_t[4].tpage_y = 0;
        en_t[4].w = 12;
        en_t[4].h = 12;
        en_t[4].u = 0;
        en_t[4].v = 0;
        en_t[4].mw = 252;
        en_t[4].mh = 144;
        en_t[4].r = 128;
        en_t[4].g = 128;
        en_t[4].b = 128;
        en_t[5].char_id = 83;
        en_t[5].clut = getClut(256, 509);
        en_t[5].tpage_x = 896;
        en_t[5].tpage_y = 0;
        en_t[5].w = 12;
        en_t[5].h = 12;
        en_t[5].u = 0;
        en_t[5].v = 0;
        en_t[5].mw = 252;
        en_t[5].mh = 144;
        en_t[5].r = 128;
        en_t[5].g = 128;
        en_t[5].b = 128;
        en_t[6].char_id = 72;
        en_t[6].clut = getClut(256, 509);
        en_t[6].tpage_x = 896;
        en_t[6].tpage_y = 0;
        en_t[6].w = 12;
        en_t[6].h = 12;
        en_t[6].u = 0;
        en_t[6].v = 0;
        en_t[6].mw = 252;
        en_t[6].mh = 144;
        en_t[6].r = 128;
        en_t[6].g = 128;
        en_t[6].b = 128;

        while (1)
        {
            ClearOTagR(graph.ot[graph.db], OTLEN);

            graph_updateCam();

            Sprite ro;
            ro.clut = getClut(256, 448);
            ro.MovVector.vx = -64;
            ro.MovVector.vy = -64;
            ro.MovVector.vz = 128;
            ro.RotVector.vx = 0;
            ro.RotVector.vy = 0;
            ro.RotVector.vz = 0;
            ro.ScaleVector.vx = ONE * 2;
            ro.ScaleVector.vy = ONE * 2;
            ro.ScaleVector.vz = ONE * 2;
            ro.u = 0;
            ro.v = 0;
            ro.w = 32;
            ro.h = 24;
            ro.r = 128;
            ro.g = 128;
            ro.b = 128;

            Sprite en;
            en.clut = getClut(256, 448);
            en.MovVector.vx = -64;
            en.MovVector.vy = 64;
            en.MovVector.vz = 128;
            en.RotVector.vx = 0;
            en.RotVector.vy = 0;
            en.RotVector.vz = 0;
            en.ScaleVector.vx = ONE * 2;
            en.ScaleVector.vy = ONE * 2;
            en.ScaleVector.vz = ONE * 2;
            en.u = 32;
            en.v = 0;
            en.w = 32;
            en.h = 24;
            en.r = 128;
            en.g = 128;
            en.b = 128;

            if (LNG == 0)
            {
                ro.alpha = 128;
                ro.tpage = getTPage(0, 0, 256, 0);
                en.alpha = 63;
                en.tpage = getTPage(0, 1, 256, 0);
            }
            else if (LNG == 1)
            {
                ro.alpha = 63;
                ro.tpage = getTPage(0, 1, 256, 0);
                en.alpha = 128;
                en.tpage = getTPage(0, 0, 256, 0);
            }

            graph_drawsprite(ro, -1);
            graph_drawsprite(en, -1);

            graph_drawtext(224, 64, LNG == 0 ? 128 : 64, 6, 2, ro_t, 1);
            graph_drawtext(224, 256 - 64, LNG == 1 ? 128 : 64, 7, 2, en_t, 1);

            PlayerCtrl ctrl = controller_getplayer(0);

            if (ctrl.connected)
            {
                if (!(ctrl.btn & PAD_UP) || !(ctrl.btn & PAD_DOWN) || ctrl.ls_y >= 63 || ctrl.ls_y <= -63)
                {
                    if (vert_pressed == FALSE)
                    {
                        LNG = LNG == 1 ? 0 : 1;
                        sound_playsfx(&sfx[0], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                        vert_pressed = TRUE;
                    }
                }
                else
                {
                    vert_pressed = FALSE;
                }

                if (!(ctrl.btn & PAD_CROSS) || !(ctrl.btn & PAD_START))
                {
                    sound_playsfx(&sfx[2], 12, 0xA1BA, FALSE, 0xFF, 0xFF);
                    graph_clearvram();
                    break;
                }
            }

            graph_disp();
        }

        free(ro_t);
        free(en_t);
        break;
    }
    case 1:
    {
        LNG = 1;
        break;
    }
        // case 2:
        // {
        //     LNG = 2;
        //     break;
        // }
    }

    ClearOTagR(graph.ot[0], OTLEN);
    ClearOTagR(graph.ot[1], OTLEN);

    graph.db = 0;
    graph.nextpri = graph.pribuff[graph.db];

    game_loadstuff();
}

void game_update()
{
    ClearOTagR(graph.ot[graph.db], OTLEN);

    graph_updateCam();

    switch (lvl)
    {
    case 0:
    {
        PlayerCtrl ctrl = controller_getplayer(0);

        if (ctrl.connected == TRUE)
        {
            controller_vibrate(ctrl.porter);

            if (!(ctrl.btn & PAD_CROSS) || !(ctrl.btn & PAD_START))
            {
                SetDispMask(0);

                if (intro)
                {
                    free(intro);
                    intro = NULL;
                }

                if (circ)
                {
                    free(circ);
                    circ = NULL;
                }

                sound_stopmusic();
                sound_clearmusic();
                cdrom_xastop();

                lvl = 1;

                u_long *file;

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU1A.VAG;1")))
                {
                    sfx[0].spu_address = sound_settransfer(&sfx[0], file);

                    free(file);
                }

                // if ((file = cdrom_readfile("\\DATA\\SND\\MENU1B.VAG;1")))
                // {
                //     sfx[1].spu_address = sound_settransfer(&sfx[1], file);

                //     free(file);
                // }

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU2.VAG;1")))
                {
                    sfx[2].spu_address = sound_settransfer(&sfx[2], file);

                    free(file);
                }

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU3.VAG;1")))
                {
                    sfx[3].spu_address = sound_settransfer(&sfx[3], file);

                    free(file);
                }

                if ((file = cdrom_readfile("\\DATA\\MUS\\TITLE.MUS;1")))
                {
                    sound_setbpm(120);
                    sound_loadmusic(file, 44, 5);
                    free(file);
                }

                title = (IntroTitle *)malloc(sizeof(IntroTitle));
                title_init(title);

                sound_playmusic();
            }
        }

        if (intro)
        {
            intro_update(intro);

            if (intro->active == FALSE)
            {
                free(intro);
                intro = NULL;

                sound_stopmusic();
                sound_clearmusic();
                cdrom_xastop();

                u_long *file;

                if ((file = cdrom_readfile("\\DATA\\MUS\\INTRO2.MUS;1")))
                {
                    sound_setbpm(145);
                    sound_loadmusic(file, 225, 4);
                    free(file);
                }

                circ = (IntroCircus *)malloc(sizeof(IntroCircus));
                circus_init(circ);

                cdrom_xaplay("\\DATA\\XA\\SPCH2.XA;1", LNG, FALSE);
                sound_playmusic();
            }
        }
        else if (circ)
        {
            circus_update(circ);

            if (circ->active == FALSE)
            {
                free(circ);
                circ = NULL;

                SetDispMask(0);

                sound_stopmusic();
                sound_clearmusic();
                cdrom_xastop();

                lvl = 1;

                u_long *file;

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU1A.VAG;1")))
                {
                    sfx[0].spu_address = sound_settransfer(&sfx[0], file);

                    free(file);
                }

                // if ((file = cdrom_readfile("\\DATA\\SND\\MENU1B.VAG;1")))
                // {
                //     sfx[1].spu_address = sound_settransfer(&sfx[1], file);

                //     free(file);
                // }

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU2.VAG;1")))
                {
                    sfx[2].spu_address = sound_settransfer(&sfx[2], file);

                    free(file);
                }

                if ((file = cdrom_readfile("\\DATA\\SND\\MENU3.VAG;1")))
                {
                    sfx[3].spu_address = sound_settransfer(&sfx[3], file);

                    free(file);
                }

                if ((file = cdrom_readfile("\\DATA\\MUS\\TITLE.MUS;1")))
                {
                    sound_setbpm(120);
                    sound_loadmusic(file, 44, 5);
                    free(file);
                }

                title = (IntroTitle *)malloc(sizeof(IntroTitle));
                title_init(title);

                sound_playmusic();
            }
        }

        break;
    }
    case 1:
    {
        if (title)
        {
            title_update(title);

            if (title->active == FALSE)
            {
                free(title);
                title = NULL;

                SetDispMask(0);

                game_reset();
            }
        }
        break;
    }
    case 2:
    {
        if (btl)
        {
            battle_update(btl);

            if (btl->active == FALSE)
            {
                free(btl);
                btl = NULL;

                SetDispMask(0);

                game_reset();
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }

    if (reseter == TRUE)
    {
        reseter = FALSE;
        gticker = 0;
        return;
    }

    if (gticker < 1000000)
    {
        gticker++;
    }
    else
    {
        gticker = 0;
    }

    srand(gticker);

    control.pcon[0] = FALSE;
    control.pcon[1] = FALSE;
    control.pcon[2] = FALSE;
    control.pcon[3] = FALSE;
    control.pcon[4] = FALSE;
    control.pcon[5] = FALSE;
    control.pcon[6] = FALSE;
    control.pcon[7] = FALSE;

    graph_disp();

    cdrom_xaupdate();
    cdrom_standby();
}

void game_loadstuff()
{
    if (lvl == 0)
    {
        cdrom_playmovie("\\DATA\\MOV\\LOGO.STR;1", 150, REGION_CODE == 0, TRUE);

        graph_clearvram();

        SetDispMask(0);

        sound_stopsfx(12);
        sound_musicsync();

        for (int i = 0; i < MAX_SNDS; i++)
        {
            if (sfx[i].spu_address != NULL)
            {
                SpuFree(sfx[i].spu_address);
                sfx[i].spu_address = NULL;
            }
        }

        SpuWrite0(0);

        u_long *file;

        if ((file = cdrom_readfile("\\DATA\\SPRT\\TITLE.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\CIRCUS.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\MAP.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FONT.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\BACK\\COJUN.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\BACK\\COWO.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MDL\\KING.TIM;1")))
        {
            graph_loadtexture(file, 0);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MDL\\KING.TMD;1")))
        {
            mdls[0] = graph_loadmodel(file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\BASS.VAG;1")))
        {
            sound.mus[0].spu_address = sound_settransfer(&sound.mus[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\HORN.VAG;1")))
        {
            sound.mus[1].spu_address = sound_settransfer(&sound.mus[1], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\TRUMPET.VAG;1")))
        {
            sound.mus[2].spu_address = sound_settransfer(&sound.mus[2], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\HORN2.VAG;1")))
        {
            sound.mus[3].spu_address = sound_settransfer(&sound.mus[3], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INTRO1.MUS;1")))
        {
            sound_setbpm(115);
            sound_loadmusic(file, 49, 5);
            free(file);
        }

        u_long *mem1;
        u_long *mem2;

        if ((mem1 = cdrom_readfile("\\ICON1.TIM;1")))
        {
            if ((mem2 = cdrom_readfile("\\ICON2.TIM;1")))
            {
                memcard_prepareheader(mem1, mem2, REGION_CODE);
                free(mem1);
                free(mem2);
            }
        }

        intro = (IntroModel *)malloc(sizeof(IntroModel));
        intro_init(intro);

        cdrom_xaplay("\\DATA\\XA\\SPCH1.XA;1", LNG, FALSE);

        sound_playmusic();
    }
    else if (lvl == 1)
    {
        u_long *file;

        if ((file = cdrom_readfile("\\DATA\\SPRT\\TITLE.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FONT.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MDL\\KING.TIM;1")))
        {
            graph_loadtexture(file, 0);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MDL\\KING.TMD;1")))
        {
            mdls[0] = graph_loadmodel(file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\BASS.VAG;1")))
        {
            sound.mus[0].spu_address = sound_settransfer(&sound.mus[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\HORN.VAG;1")))
        {
            sound.mus[1].spu_address = sound_settransfer(&sound.mus[1], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\TRUMPET.VAG;1")))
        {
            sound.mus[2].spu_address = sound_settransfer(&sound.mus[2], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\HORN2.VAG;1")))
        {
            sound.mus[3].spu_address = sound_settransfer(&sound.mus[3], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU1A.VAG;1")))
        {
            sfx[0].spu_address = sound_settransfer(&sfx[0], file);

            free(file);
        }

        // if ((file = cdrom_readfile("\\DATA\\SND\\MENU1B.VAG;1")))
        // {
        //     sfx[1].spu_address = sound_settransfer(&sfx[1], file);

        //     free(file);
        // }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU2.VAG;1")))
        {
            sfx[2].spu_address = sound_settransfer(&sfx[2], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU3.VAG;1")))
        {
            sfx[3].spu_address = sound_settransfer(&sfx[3], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\TITLE.MUS;1")))
        {
            sound_setbpm(120);
            sound_loadmusic(file, 44, 5);
            free(file);
        }

        u_long *mem1;
        u_long *mem2;

        if ((mem1 = cdrom_readfile("\\ICON1.TIM;1")))
        {
            if ((mem2 = cdrom_readfile("\\ICON2.TIM;1")))
            {
                memcard_prepareheader(mem1, mem2, REGION_CODE);
                free(mem1);
                free(mem2);
            }
        }

        title = (IntroTitle *)malloc(sizeof(IntroTitle));
        title_init(title);

        sound_playmusic();
    }
    else if (lvl == 2)
    {
        u_long *file;

        if (LNG == 1)
        {
            if ((file = cdrom_readfile("\\DATA\\BACK\\JUNLD.TIM;1")))
            {
                graph_loadback(file);
                free(file);
            }
        }
        else
        {
            if ((file = cdrom_readfile("\\DATA\\BACK\\JUNLD2.TIM;1")))
            {
                graph_loadback(file);
                free(file);
            }
        }

        SetDispMask(1);

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FONT.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\BACK\\COJUN.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\EDGE.TIM;1")))
        {
            CCLUT *cluted = graph_loadtexture(file, 16);
            free(file);

            cluted[4].r = 63;
            cluted[4].g = 31;
            cluted[4].b = 0;
            cluted[5].r = 127;
            cluted[5].g = 63;
            cluted[5].b = 0;
            graph_loadclut(cluted, 256, 451, 16); // Wooden Armor

            cluted[4].r = 63;
            cluted[4].g = 63;
            cluted[4].b = 63;
            cluted[5].r = 127;
            cluted[5].g = 127;
            cluted[5].b = 127;
            graph_loadclut(cluted, 256, 452, 16); // Stone Armor

            cluted[4].r = 127;
            cluted[4].g = 127;
            cluted[4].b = 0;
            cluted[5].r = 255;
            cluted[5].g = 255;
            cluted[5].b = 0;
            graph_loadclut(cluted, 256, 453, 16); // Golden Armor

            cluted[4].r = 127;
            cluted[4].g = 127;
            cluted[4].b = 127;
            cluted[5].r = 255;
            cluted[5].g = 255;
            cluted[5].b = 255;
            graph_loadclut(cluted, 256, 454, 16); // Iron Armor

            cluted[4].r = 0;
            cluted[4].g = 127;
            cluted[4].b = 127;
            cluted[5].r = 0;
            cluted[5].g = 255;
            cluted[5].b = 255;
            graph_loadclut(cluted, 256, 455, 16); // Diamond Armor

            cluted[4].r = 0;
            cluted[4].g = 127;
            cluted[4].b = 0;
            cluted[5].r = 0;
            cluted[5].g = 255;
            cluted[5].b = 0;
            graph_loadclut(cluted, 256, 456, 16); // Emerald Armor

            cluted[4].r = 127;
            cluted[4].g = 0;
            cluted[4].b = 0;
            cluted[5].r = 255;
            cluted[5].g = 0;
            cluted[5].b = 0;
            graph_loadclut(cluted, 256, 457, 16); // Redstone Armor

            cluted[4].r = 63;
            cluted[4].g = 0;
            cluted[4].b = 127;
            cluted[5].r = 127;
            cluted[5].g = 0;
            cluted[5].b = 255;
            graph_loadclut(cluted, 256, 458, 16); // Ender Armor

            cluted[1].r = 0;
            cluted[1].g = 127;
            cluted[1].b = 127;
            cluted[2].r = 0;
            cluted[2].g = 255;
            cluted[2].b = 255;
            cluted[3].r = 0;
            cluted[3].g = 127;
            cluted[3].b = 127;
            cluted[4].r = 0;
            cluted[4].g = 127;
            cluted[4].b = 127;
            cluted[5].r = 0;
            cluted[5].g = 255;
            cluted[5].b = 255;
            graph_loadclut(cluted, 256, 459, 16); // Frozen

            free(cluted);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\FX.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SPRT\\ACTION.TIM;1")))
        {
            graph_loadtexture(file, 0);
            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\BASS.VAG;1")))
        {
            sound.mus[0].spu_address = sound_settransfer(&sound.mus[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\GUITAR.VAG;1")))
        {
            sound.mus[1].spu_address = sound_settransfer(&sound.mus[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\GUITAR2.VAG;1")))
        {
            sound.mus[2].spu_address = sound_settransfer(&sound.mus[2], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\GUITAR3.VAG;1")))
        {
            sound.mus[3].spu_address = sound_settransfer(&sound.mus[3], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\GUITAR4.VAG;1")))
        {
            sound.mus[4].spu_address = sound_settransfer(&sound.mus[4], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING.VAG;1")))
        {
            sound.mus[5].spu_address = sound_settransfer(&sound.mus[5], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING2.VAG;1")))
        {
            sound.mus[6].spu_address = sound_settransfer(&sound.mus[6], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING3.VAG;1")))
        {
            sound.mus[7].spu_address = sound_settransfer(&sound.mus[7], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING4.VAG;1")))
        {
            sound.mus[8].spu_address = sound_settransfer(&sound.mus[8], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING5.VAG;1")))
        {
            sound.mus[9].spu_address = sound_settransfer(&sound.mus[9], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\STRING6.VAG;1")))
        {
            sound.mus[10].spu_address = sound_settransfer(&sound.mus[10], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\DRUM.VAG;1")))
        {
            sound.mus[11].spu_address = sound_settransfer(&sound.mus[11], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\DRUM2.VAG;1")))
        {
            sound.mus[12].spu_address = sound_settransfer(&sound.mus[12], file);

            free(file);
        }
        
        if ((file = cdrom_readfile("\\DATA\\MUS\\INST\\DRUM3.VAG;1")))
        {
            sound.mus[13].spu_address = sound_settransfer(&sound.mus[13], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU1A.VAG;1")))
        {
            sfx[0].spu_address = sound_settransfer(&sfx[0], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU1B.VAG;1")))
        {
            sfx[1].spu_address = sound_settransfer(&sfx[1], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU2.VAG;1")))
        {
            sfx[2].spu_address = sound_settransfer(&sfx[2], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\MENU3.VAG;1")))
        {
            sfx[3].spu_address = sound_settransfer(&sfx[3], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\CODMG.VAG;1")))
        {
            sfx[4].spu_address = sound_settransfer(&sfx[4], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\COAM1.VAG;1")))
        {
            sfx[5].spu_address = sound_settransfer(&sfx[5], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\COAM2.VAG;1")))
        {
            sfx[6].spu_address = sound_settransfer(&sfx[6], file);

            free(file);
        }

        if ((file = cdrom_readfile("\\DATA\\SND\\COPOT.VAG;1")))
        {
            sfx[7].spu_address = sound_settransfer(&sfx[7], file);

            free(file);
        }

        u_int mag = 0;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG11.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG12.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG13.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG21.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG22.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG31.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG32.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG41.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG42.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG51.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG52.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG61.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG62.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG71.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG72.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG81.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG82.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG91.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG92.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG101.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\COMAG102.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag++;

        if ((file = cdrom_readfile("\\DATA\\SND\\CODTH.VAG;1")))
        {
            sfx[8 + mag].spu_address = sound_settransfer(&sfx[8 + mag], file);

            free(file);
        }

        mag = 0;

        if ((file = cdrom_readfile("\\DATA\\MUS\\EDGECAST.MUS;1")))
        {
            sound_setbpm(150);
            sound_loadmusic(file, 924, 8);
            free(file);
        }

        u_long *mem1;
        u_long *mem2;

        if ((mem1 = cdrom_readfile("\\ICON1.TIM;1")))
        {
            if ((mem2 = cdrom_readfile("\\ICON2.TIM;1")))
            {
                memcard_prepareheader(mem1, mem2, REGION_CODE);
                free(mem1);
                free(mem2);
            }
        }

        btl = (SceneBattle *)malloc(sizeof(SceneBattle));
        battle_init(btl);

        sound_playmusic();
    }
}

void game_drawmodel(int idx, VECTOR Trans, SVECTOR Rotate, VECTOR Scale, u_char u, u_char v, u_short tpage, u_short clut)
{
    if (idx < MAX_MDLS && idx >= 0)
    {
        mdls[idx].u = u;
        mdls[idx].v = v;
        mdls[idx].tpage = tpage;
        mdls[idx].clut = clut;
        graph_drawmodel(mdls[idx], Trans, Rotate, Scale);
    }
}

void game_reset()
{
    cdrom_xastop();
    sound_stopmusic();
    sound_clearmusic();
    graph_clearvram();
    memcard_clearheader();

    ClearOTagR(graph.ot[0], OTLEN);
    ClearOTagR(graph.ot[1], OTLEN);

    graph.nextpri = graph.pribuff[0];
    graph.db = 0;

    if (mdls[0].mdl)
    {
        free(mdls[0].mdl);
    }

    if (mdls[1].mdl)
    {
        free(mdls[1].mdl);
    }

    u_char cnt = 0;

    while (cnt < (lvl != 255 ? 63 : 255))
    {
        VSync(0);
        cnt++;
    }

    for (int i = 0; i < 24; i++)
    {
        sound_stopsfx(i);

#if SPU_REVERBING == SPU_ON
        SpuSetReverb(SPU_OFF);
        SpuSetReverbVoice(SPU_OFF, (0x1L << i));
#endif
        sound_musicsync();
    }

    for (int i = 0; i < MAX_SNDS; i++)
    {
        if (sfx[i].spu_address != NULL)
        {
            SpuFree(sfx[i].spu_address);
            sfx[i].spu_address = NULL;

            sound_musicsync();
        }
    }

    for (int i = 0; i < 254; i++)
    {
        if (sound.mus[i].spu_address != NULL)
        {
            SpuFree(sound.mus[i].spu_address);
            sound.mus[i].spu_address = NULL;

            sound_musicsync();
        }
    }

    SpuWrite0(0);

#if SPU_REVERBING == SPU_ON
    SpuClearReverbWorkArea(SPU_REV_MODE_STUDIO_C);
#endif

    control.pcon[0] = FALSE;
    control.pcon[1] = FALSE;
    control.pcon[2] = FALSE;
    control.pcon[3] = FALSE;
    control.pcon[4] = FALSE;
    control.pcon[5] = FALSE;
    control.pcon[6] = FALSE;
    control.pcon[7] = FALSE;

    control.motor[0][0] = 0;
    control.motor[0][1] = 0;
    control.vib_sync[0] = TRUE;
    control.motor[1][0] = 0;
    control.motor[1][1] = 0;
    control.vib_sync[1] = TRUE;
    control.motor[2][0] = 0;
    control.motor[2][1] = 0;
    control.vib_sync[2] = TRUE;
    control.motor[3][0] = 0;
    control.motor[3][1] = 0;
    control.vib_sync[3] = TRUE;
    control.motor[4][0] = 0;
    control.motor[4][1] = 0;
    control.vib_sync[4] = TRUE;
    control.motor[5][0] = 0;
    control.motor[5][1] = 0;
    control.vib_sync[5] = TRUE;
    control.motor[6][0] = 0;
    control.motor[6][1] = 0;
    control.vib_sync[6] = TRUE;
    control.motor[7][0] = 0;
    control.motor[7][1] = 0;
    control.vib_sync[7] = TRUE;

    controller_vibrate(0x00);
    controller_vibrate(0x01);
    controller_vibrate(0x02);
    controller_vibrate(0x03);
    controller_vibrate(0x10);
    controller_vibrate(0x11);
    controller_vibrate(0x12);
    controller_vibrate(0x13);

    reseter = TRUE;

    game_loadstuff();
}