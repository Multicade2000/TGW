#include "movie.h"
#include "controller.h"

GameMovie movie;

void PlayStr(const char *filename, int frames, int eu, int doubleSpeed)
{
    movie.doubleSpeed = doubleSpeed;
    movie.pal = eu;

    movie.strNumFrames = frames;
    movie.strScreenWidth = 320;
    movie.strScreenHeight = (movie.pal ? 256 : 240);
    movie.strFrameX = 0;
    movie.strFrameY = (movie.pal ? 8 : 0);

    movie.strPlayDone = 0;
    strDoPlayback(filename);
}

static void strDoPlayback(const char *filename)
{
    int id;
    DISPENV disp;
    CdlFILE file;

    u_long RingBuff[32 * SECTOR_SIZE];
    u_long VlcBuff[2][320 / 2 * (movie.pal ? 256 : 240)];
    u_short ImgBuff[2][16 * 1 * (movie.pal ? 256 : 240)];

    SetDispMask(0);

    if (CdSearchFile(&file, (char *)filename) == 0)
    {
        return;
    }

    movie.strEnv.VlcBuff_ptr[0] = &VlcBuff[0][0];
    movie.strEnv.VlcBuff_ptr[1] = &VlcBuff[1][0];
    movie.strEnv.VlcID = 0;
    movie.strEnv.ImgBuff_ptr[0] = &ImgBuff[0][0];
    movie.strEnv.ImgBuff_ptr[1] = &ImgBuff[1][0];
    movie.strEnv.ImgID = 0;

    movie.strEnv.rect[0].x = movie.strFrameX;
    movie.strEnv.rect[0].y = movie.strFrameY;
    movie.strEnv.rect[1].x = movie.strFrameX;
    movie.strEnv.rect[1].y = movie.strFrameY + movie.strScreenHeight;
    movie.strEnv.RectID = 0;

    movie.strEnv.slice.x = movie.strFrameX;
    movie.strEnv.slice.y = movie.strFrameY;
    movie.strEnv.slice.w = 16 * 1;
    movie.strEnv.FrameDone = 0;

    DecDCTReset(0);
    DecDCToutCallback(strCallback);
    StSetRing(RingBuff, 32);
    StSetStream(0, 1, 0xffffffff, 0, 0);
    strKickCD(&file.pos);

    strNextVlc(&movie.strEnv);

    while (1)
    {
        DecDCTin(movie.strEnv.VlcBuff_ptr[movie.strEnv.VlcID], 2);
        DecDCTout((u_long *)movie.strEnv.ImgBuff_ptr[movie.strEnv.ImgID], movie.strEnv.slice.w * movie.strEnv.slice.h / 2);

        strNextVlc(&movie.strEnv);

        id = movie.strEnv.RectID ? 0 : 1;
        SetDefDispEnv(&disp, 0, movie.strScreenHeight * id, movie.strScreenWidth * 1, movie.strScreenHeight);

        if (movie.pal)
        {
            disp.screen.y = 24;
        }

        disp.isinter = 0;

        // if (movie.bpp24)
        // {
        // 	disp.isrgb24 = 1;
        // 	disp.disp.w = disp.disp.w * 2 / 3;
        // }

        VSync(0);
        PutDispEnv(&disp);
        SetDispMask(1);

        if (movie.strPlayDone == 1)
        {
            break;
        }

        int stop = FALSE;

        for (int pidx = 0; pidx < 8; pidx++)
        {
            PlayerCtrl plr_ctrl = controller_getplayer(pidx);

            if (plr_ctrl.connected == TRUE)
            {
                if (!(plr_ctrl.btn & PAD_CROSS) || !(plr_ctrl.btn & PAD_START))
                {
                    stop = TRUE;
                    break;
                }
            }
        }

        if (stop == TRUE)
        {
            break;
        }
    }

    DecDCToutCallback(0);
    StUnSetRing();
    CdControlB(CdlPause, 0, 0);
}

static void strCallback()
{
    RECT TransferRect;
    int id;

    // if (movie.bpp24)
    // {
    // 	extern u_long StCdIntrFlag;
    // 	if (StCdIntrFlag)
    // 	{
    // 		StCdInterrupt();
    // 		StCdIntrFlag = 0;
    // 	}
    // }

    id = movie.strEnv.ImgID;
    TransferRect = movie.strEnv.slice;

    movie.strEnv.ImgID = movie.strEnv.ImgID ? 0 : 1;

    movie.strEnv.slice.x += movie.strEnv.slice.w;

    if (movie.strEnv.slice.x < movie.strEnv.rect[movie.strEnv.RectID].x + movie.strEnv.rect[movie.strEnv.RectID].w)
    {
        DecDCTout((u_long *)movie.strEnv.ImgBuff_ptr[movie.strEnv.ImgID], movie.strEnv.slice.w * movie.strEnv.slice.h / 2);
    }
    else
    {
        movie.strEnv.FrameDone = 1;

        movie.strEnv.RectID = movie.strEnv.RectID ? 0 : 1;
        movie.strEnv.slice.x = movie.strEnv.rect[movie.strEnv.RectID].x;
        movie.strEnv.slice.y = movie.strEnv.rect[movie.strEnv.RectID].y;
    }

    LoadImage(&TransferRect, (u_long *)movie.strEnv.ImgBuff_ptr[id]);
}

static void strNextVlc(STRENV *strEnv)
{
    int cnt = 4096;
    u_long *next = NULL;
    u_long *strNext();

    while ((next = strNext(strEnv)) == NULL)
    {
        int cdr = CdDiskReady(1);
        if (--cnt == 0 || cdr == CdlStatShellOpen)
        {
            movie.strPlayDone = 1;
            return;
        }
    }

    strEnv->VlcID = strEnv->VlcID ? 0 : 1;

    DecDCTvlc(next, strEnv->VlcBuff_ptr[strEnv->VlcID]);

    StFreeRing(next);
}

static u_long *strNext(STRENV *strEnv)
{
    u_long *addr;
    StHEADER *sector;
    int cnt = 4096;

    while (StGetNext((u_long **)&addr, (u_long **)&sector))
    {
        int cdr = CdDiskReady(1);
        if (--cnt == 0 || cdr == CdlStatShellOpen)
            return (0);
    }

    if (sector->frameCount >= movie.strNumFrames)
        movie.strPlayDone = 1;

    if (movie.strFrameWidth != sector->width || movie.strFrameHeight != sector->height)
    {

        RECT rect;
        setRECT(&rect, 0, 0, movie.strScreenWidth * 1, movie.strScreenHeight * 2);
        ClearImage(&rect, 0, 0, 0);

        movie.strFrameWidth = sector->width;
        movie.strFrameHeight = sector->height;
    }

    strEnv->rect[0].w = strEnv->rect[1].w = movie.strFrameWidth * 1;
    strEnv->rect[0].h = strEnv->rect[1].h = movie.strFrameHeight;
    strEnv->slice.h = movie.strFrameHeight;

    return (addr);
}

static void strKickCD(CdlLOC *loc)
{
    if (movie.doubleSpeed)
    {
        u_char param = CdlModeSpeed;

        int loop = TRUE;

        while (loop)
        {
            while (CdControl(CdlSetloc, (u_char *)loc, 0) == 0)
                ;
            while (CdControl(CdlSetmode, &param, 0) == 0)
                ;

            VSync(3);

            if (CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT) != 0)
                loop = FALSE;
        }
    }
    else
    {
        u_char param = 0x00;

        int loop = TRUE;

        while (loop == TRUE)
        {
            while (CdControl(CdlSetloc, (u_char *)loc, 0) == 0)
                ;
            while (CdControl(CdlSetmode, &param, 0) == 0)
                ;

            VSync(3);

            if (CdRead2(CdlModeStream | CdlModeRT) != 0)
                loop = FALSE;
        }
    }
}