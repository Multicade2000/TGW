#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include "graph.h"
#include "controller.h"
#include "sprite.h"

typedef struct
{
    u_char type;
    u_char plr;
    u_char alive;

    u_char anim;

    u_int hp;
    u_int mp;
    u_int lvl;
    u_int max_hp;
    u_int max_mp;
    u_char shd;
    u_char shd_mode;
    u_int shd_hp;
    u_char shd_mana;
    u_char regen;
    u_char poison;
    u_char freeze;
    u_char turn_start;
    u_char armor;
    u_int armor_hp;
    u_char spell[10];
    u_char spell_rank[10];
    u_char spell_used[10];
    u_char pot[3];
    u_int dmg;

    u_char act;
    u_int act_tick;
    u_char act_count;

    u_int tick;
    u_int max_tick;
    u_char walk;
    u_char turn;

    u_char dodge;
    u_char parry;

    u_char b_load;

    u_char action[3];

    u_char hor_pressed;
    u_char ver_pressed;
    u_char accept_pressed;
    u_char decline_pressed;
    u_char quit_pressed;

    PlayerCtrl ctrl;

    Sprite spr;

    VECTOR def_loc;
    VECTOR pivot;
    VECTOR target;
} Person;

typedef struct FX
{
    Sprite spr;
    u_char type;
    u_char tick;

    u_char reverse;

    u_char active;

    Person *owner;

    Person *target;
    struct FX *next;
} FX;


typedef struct
{
    Person *people;
    FX *fx;

    u_char max_people;
    u_char turn;

    u_int spell_cost[10];

    u_int lvl_max;

    u_char menu;

    u_char active;
    u_char retry;
    u_char reverse;

    u_char b_save;
} SceneBattle;

void battle_init(SceneBattle *battle);
void battle_update(SceneBattle *battle);
FX *battle_spawnfx(SceneBattle *battle);

void person_init(Person *person);
void person_update(Person *person);
void person_damage(Person *victim, Person *attacker, u_int dmg, u_char allow_dodge);

void fx_init(FX *fx);
void fx_update(FX *fx);