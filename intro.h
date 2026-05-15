#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include "graph.h"
#include "sprite.h"

typedef struct
{
    Sprite spr[3];

    VECTOR mov;
    SVECTOR rot;
    VECTOR scl;
    u_char active;
    u_int tick;
} IntroModel;

typedef struct
{
    Sprite edge;
    Sprite diama;
    Sprite map1; // The Cave
    Sprite map2; // The Jungle Land
    Sprite map3; // The Village
    Sprite map4; // The Stoney Bar
    Sprite map5; // The Golden House
    Sprite map6; // The Iron Throne
    Sprite map7; // The Diamond Lodge
    Sprite map8; // The Loving Emerald
    Sprite map9; // The Redstone Castle

    Sprite number[4];

    Sprite king;
    Sprite redorn_head;
    Sprite king_text[4];

    Sprite legend;
    Sprite secret;
    Sprite witness;

    u_int scenario;
    u_int num_s;
    u_int king_s;
    u_char active;
    u_int tick;
} IntroCircus;

typedef struct
{
    Sprite spr[4];

    VECTOR mov;
    SVECTOR rot;
    VECTOR scl;

    u_int title_s;
    u_int tick;
    u_char active;

    u_char hor_pressed;
    u_char ver_pressed;
    u_char accept_pressed;
    u_char decline_pressed;
    u_char lockin_pressed;

    u_char opt;
    u_char menu;
    u_char mus_track;
    u_char camMode;
    u_char camLock;

    u_char plr2;
    u_char plr3;
    u_char plr4;

    TextChar *opt1;
    TextChar *opt2;
    TextChar *opt3;

    TextChar *mp1;
    TextChar *mp2;
    TextChar *mp3;
    TextChar *mp4;
    TextChar *mp5;

    TextChar *lodm;
    TextChar *lodm2;
    TextChar *lod1;
    TextChar *lod2;
    
    TextChar *mus1;
    TextChar *mus2;
    TextChar *mus3;

    u_int tsize01;
    u_int tsize02;
    u_int tsize03;

    u_int tsize21;
    u_int tsize22;
    u_int tsize23;
    u_int tsize24;
    u_int tsize25;

    u_int tsize31;
    u_int tsize32;
    u_int tsize33;
    u_int tsize34;

    u_int tsize2531;
    u_int tsize2532;
    u_int tsize2533;
} IntroTitle;

void intro_init(IntroModel *intro);
void intro_update(IntroModel *intro);

void circus_init(IntroCircus *circ);
void circus_update(IntroCircus *circ);

void title_init(IntroTitle *title);
void title_update(IntroTitle *title);