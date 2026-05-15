#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libspu.h>
#include <libpad.h>

#define MALLOC_MAX 256
#define SWAP_ENDIAN32(x) (((x)>>24) | (((x)>>8) & 0xFF00) | (((x)<<8) & 0x00FF0000) | ((x)<<24))

typedef struct VAGsound {
    u_long spu_address;
    u_int pitch;
} VAGsound;

typedef struct VAGheader{
    char id[4];
    unsigned int version;
    unsigned int reserved;
    unsigned int dataSize;
    unsigned int samplingFrequency;
    char reserved2[12];
    char name[16];

} VAGhdr;

typedef struct MUSheader {
    u_char sampleid;
    u_char channel;
    u_short note_key;
    u_int timer;
    u_char loopStart;
    u_char loopEnd;
    u_char volR;
    u_char volL;
} MusHdr;

typedef struct
{
    u_int mus_tick[12];

    VAGsound mus[254];
    MusHdr *muser;

    int chan_ofs[12];
    int chan_loop[12];
    int chan_start[12];
    int chan_stop[12];

    int mus_playing;

    int stopper;

    int max_channels;

    int curPos[12];

    long musicEvent;
    long mus_bpm;

    char spu_malloc_rec[SPU_MALLOC_RECSIZ * (MALLOC_MAX+1)];
} GameSound;

#define SPU_REVERBING SPU_OFF

extern GameSound sound;

void sound_init();
u_long sound_vagtospu(unsigned int VAG_data_size, u_char *VAG_data);
void sound_setvoiceattr(unsigned int pitch, int channel, u_long soundAddr, u_short key, int inst, u_short volL, u_short volR);

u_long sound_settransfer(VAGsound *sound, u_long *file);
void sound_playsfx(VAGsound *sound, int channel, u_short key, int inst, u_char volL, u_char volR);
void sound_stopsfx(int channel);

void sound_loadmusic(u_long *file, int size, int max_chans);
void sound_playmusic();
void sound_stopmusic();
void sound_clearmusic();
void sound_setbpm(long bpm);
static long sound_processmusic();
void sound_musicsync();