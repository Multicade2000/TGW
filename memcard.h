#pragma once

#include <sys/file.h>
#include <sys/types.h>
#include <kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libmcrd.h>
#include <libpad.h>
#include <string.h>

#define SAVENAME_EU "BEMAIN-EXE02TGW00000"
#define SAVENAME_US "BAMAIN-EXE02TGW00000"
#define SAVENAME_JP "BIMAIN-EXE02TGW00000"

typedef struct {
    char id[2];
    char type;
    char size;
    char title[64];
    char pad[28];
    char clut[32];
} SAVEHDR;

typedef struct {
    char sprt[128];
} SAVEIMG;

typedef struct {
    u_char glvl;
    u_int hp;
    u_int mp;
    u_char armor;
    u_int armor_hp;
    u_char shd;
    u_int shd_hp;
    u_char spell[10];
    u_char spell_rank[10];
    u_char pot[3];
    u_int lvl;
    u_char dump[82];
} SAVEDATA;

typedef struct {
    SAVEDATA data;
    u_char load;
} DATALOAD;

typedef struct
{
    long cardCmd;
    long slotResult[1];

    SAVEHDR mem_header;

    SAVEIMG icon1;
    SAVEIMG icon2;
} GameSave;

void memcard_init();
void memcard_prepareheader(u_long *icon1, u_long *icon2, int region);
void memcard_clearheader();
void memcard_save(u_char port, DATALOAD *data, int region, int mp);
DATALOAD memcard_load(u_char port, int region, int mp);