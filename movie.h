#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include <libpress.h>

typedef struct {
	u_long	*VlcBuff_ptr[2];
	u_short	*ImgBuff_ptr[2];
	RECT	rect[2];
	RECT	slice;
	int		VlcID;
	int		ImgID;
	int 	RectID;
	int		FrameDone;
} STRENV;

typedef struct
{
    STRENV strEnv;

    int	strScreenWidth,strScreenHeight;
    int	strFrameX,strFrameY;
    int	strNumFrames;

    int strFrameWidth,strFrameHeight;
    int strPlayDone;

    int pal;
    int doubleSpeed;
    int bpp24;
} GameMovie;

void PlayStr(const char *filename, int frames, int eu, int doubleSpeed);

static void strDoPlayback(const char *filename);
static void strCallback();
static void strNextVlc(STRENV *strEnv);
static u_long *strNext(STRENV *strEnv);
static void strKickCD(CdlLOC *loc);