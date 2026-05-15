#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct
{
    u_char u;
    u_char v;
    u_short tpage;
    u_short clut;
    TMD_PRIM *mdl;
    int n_prim;
} Model;
