#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>

typedef struct
{
    SVECTOR RotVector;
    VECTOR MovVector;
    VECTOR ScaleVector;
    u_char w;
    u_char h;
    u_char u;
    u_char v;
    u_char r;
    u_char g;
    u_char b;
    u_char alpha;
    u_short tpage;
    u_short clut;
} Sprite;
