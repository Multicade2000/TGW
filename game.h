#pragma once

#include "region.h"
#include "graph.h"
#include "cdrom.h"
#include "sound.h"
#include "controller.h"
#include "memcard.h"
#include "intro.h"
#include "battle.h"

#define MAX_SNDS 30

extern int LNG;
extern int lvl;
extern VAGsound sfx[MAX_SNDS];
extern IntroTitle *title;
extern SceneBattle *btl;
extern u_char plr[3];
extern u_char memlod;

void game_init();
void game_update();
void game_loadstuff();
void game_drawmodel(int idx, VECTOR Trans, SVECTOR Rotate, VECTOR Scale, u_char u, u_char v, u_short tpage, u_short clut);
void game_reset();