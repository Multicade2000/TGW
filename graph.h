#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpad.h>
#include "sprite.h"
#include "model.h"

#define OTLEN 4096

typedef struct {
    u_short r;
    u_short g;
    u_short b;
    u_short stp;
}CCLUT;

typedef struct
{
    int ResW, ResH;
    int pal_mode;
    DISPENV disp[2];
    DRAWENV draw[2];
    int db;
    u_long ot[2][OTLEN];
    char pribuff[2][32768];
    char *nextpri;
    VECTOR camPos;
    VECTOR appl;
    SVECTOR camRot;
    MATRIX camMat;
    u_char scr_fade;

    int last_vsync;
} GameGraph;

typedef struct
{
    u_short char_id;
    u_short tpage_x;
    u_short tpage_y;
    u_short clut;

    int w;
    int h;
    int u;
    int v;
    int mw;
    int mh;

    u_char r;
    u_char g;
    u_char b;
} TextChar;

extern GameGraph graph;

void graph_init(int code);
void graph_disp();
void graph_clearvram();
CCLUT *graph_loadtexture(u_long *tim, int max_clut);
void graph_loadback(u_long *tim);
Model graph_loadmodel(u_long *tmd);
void graph_drawsprite(Sprite spr, long OTx);
void graph_drawmodel(Model mdl, VECTOR Trans, SVECTOR Rotate, VECTOR Scale);
void graph_loadclut(CCLUT *clut, short x, short y, int max_clut);
void graph_drawback(u_short tp, u_short cl);
void graph_drawtext(int x, int y, u_char alpha, u_int size, TextChar *text, long OTz);
void graph_inittext(TextChar* charer);
void graph_settext(const u_char *text, TextChar *charer, u_int size);
void graph_drawtile(int x, int y, int w, int h);
void graph_updateCam();
u_char graph_vsync();