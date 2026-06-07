#include "cdrom.h"
#include "region.h"
#include "graph.h"

GameCD disc;

void cdrom_init()
{
    CdInit();
}

u_long *cdrom_readfile(const char *filename)
{
    cdrom_xastop();

    CdlFILE file;
    u_long *buffer;

    disc.cd_standby = FALSE;
    disc.cd_tick = 0;

    if (!CdSearchFile(&file, (char *)filename))
    {
        return NULL;
    }

    buffer = (u_long *)malloc(2048 * ((file.size + 2047) / 2048));

    if (!buffer)
    {
        return NULL;
    }

    CdControl(CdlSetloc, (u_char *)&file.pos, 0);

    CdRead((file.size + 2047) / 2048, buffer, CdlModeSpeed);

    CdReadSync(0, 0);

    u_char param = CdlModeSpeed;

    CdControlB(CdlSetmode, &param, 0);
    CdControlF(CdlPause, 0);

    return buffer;
}

void cdrom_standby()
{
    if (disc.cd_standby)
    {
        if (disc.cd_tick != 0)
        {
            u_char param = 0x00;
            CdControlB(CdlSetmode, &param, 0);
            CdControlF(CdlStandby, 0);
            disc.cd_tick = 0;
        }
    }
    else if (!disc.xa_playing)
    {
        disc.cd_tick++;
        if (disc.cd_tick >= 1000)
        {
            disc.cd_standby = TRUE;
        }
    }
}

void cdrom_xaplay(const char *XAload, u_char channel, int dS)
{
    if (CdDiskReady(1) == CdlStatShellOpen)
    {
        return;
    }

    if (!disc.xa_playing)
    {
        disc.cd_standby = FALSE;
        disc.cd_tick = 0;

        CdlFILE XAPos;
        if (!CdSearchFile(&XAPos, (char *)XAload))
        {
            ((void (*)())0xBFC00000)();
            return;
        }
        disc.pos_start = CdPosToInt(&XAPos.pos);
        disc.pos_end = (disc.pos_start + ((XAPos.size / CD_SECTOR_SIZE)));

        u_char param = CdlModeRT | CdlModeSF | CdlModeSize1;
        if (dS)
        {
            param |= CdlModeSpeed;
        }

        disc.doubleSpeed = dS;

        CdControlB(CdlSetmode, &param, 0);
        CdControlF(CdlPause, 0);

        CdlFILTER filter;

        filter.file = 1;
        filter.chan = channel;

        CdControlF(CdlSetfilter, (u_char *)&filter);

        CdlLOC loc;
        disc.cur_pos = disc.pos_start;

        CdIntToPos(disc.pos_start, &loc);
        CdControlF(CdlReadS, (u_char *)&loc);

        disc.xa_playing = TRUE;
    }
}

void cdrom_xaupdate()
{
    if (disc.xa_playing)
    {
        if (REGION_CODE != 0)
        {
            disc.cur_pos += (disc.doubleSpeed ? 8 : 4) * graph.delta;
        }
        else
        {
            disc.cur_pos += (disc.doubleSpeed ? 10 : 5) * graph.delta;
        }
        if (disc.cur_pos >= disc.pos_end)
        {
            cdrom_xastop();
        }
    }
}

void cdrom_xastop()
{
    if (disc.xa_playing)
    {
        u_char param = disc.doubleSpeed ? CdlModeSpeed : 0x00;

        CdControlF(CdlPause, 0);
        CdControlB(CdlSetmode, &param, 0);
        disc.xa_playing = FALSE;
        disc.pos_start = 0;
        disc.pos_end = 0;
        disc.cur_pos = 0;
    }
}

void cdrom_playmovie(const char *filename, int frames, int eu, int dS)
{
    PlayStr(filename, frames, eu, dS);
}