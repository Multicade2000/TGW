#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <libapi.h>
#include <libetc.h>
#include <libpad.h>

#define PAD_SELECT      1
#define PAD_L3          2
#define PAD_R3          4
#define PAD_START       8
#define PAD_UP          16
#define PAD_RIGHT       32
#define PAD_DOWN        64
#define PAD_LEFT        128
#define PAD_L2          256
#define PAD_R2          512
#define PAD_L1          1024
#define PAD_R1          2048
#define PAD_TRIANGLE    4096
#define PAD_CIRCLE      8192
#define PAD_CROSS       16384
#define PAD_SQUARE      32768

typedef struct
{
    u_char padbuff[2][34];
    u_char align[6];
    u_char motor[8][2];
    int vib_sync[8];
    int pcon[8];
} GameController;

typedef struct
{
    int connected;
    u_short btn;
    u_char type;
    int ls_x,ls_y,rs_x,rs_y;
    int porter;
} PlayerCtrl;

extern GameController control;

void controller_init();
int controller_connected(int port);
u_char controller_type(int port);
u_short controller_btn(int port);
u_char controller_stick(int port, int stick);

void controller_vibrate(int port);
PlayerCtrl controller_getplayer(int pidx);