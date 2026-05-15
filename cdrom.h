#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libcd.h>
#include <libpad.h>
#include "movie.h"

#define CD_SECTOR_SIZE 650

typedef struct
{
    int cd_tick;
    int cd_standby;

    int pos_start;
    int pos_end;
    int cur_pos;

    int doubleSpeed;

    int xa_playing;
} GameCD;

void cdrom_init();
u_long *cdrom_readfile(const char *filename);
void cdrom_standby();

void cdrom_xaplay(const char *XAload, u_char channel, int dS);
void cdrom_xaupdate();
void cdrom_xastop();

void cdrom_playmovie(const char *filename, int frames, int eu, int dS);