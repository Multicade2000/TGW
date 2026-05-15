#include "sound.h"
#include "region.h"

GameSound sound;
#define TIMER_FREQ 4233600

void sound_init()
{
    for (int i = 0; i < 12; i++)
    {
        sound.mus_tick[i] = 0;
        sound.curPos[i] = 0;
        sound.chan_loop[i] = 0;
        sound.chan_start[i] = FALSE;
        sound.chan_stop[i] = FALSE;
        sound.chan_ofs[i] = 0;
        sound.chan_loop[i] = 0;
    }

    sound.stopper = 0;

    sound.muser = NULL;

    SpuCommonAttr commonAttributes;
    SpuInit();
    SpuInitMalloc(MALLOC_MAX, sound.spu_malloc_rec);
    SpuWrite0(0);

#if SPU_REVERBING == SPU_ON
    SpuClearReverbWorkArea(SPU_REV_MODE_STUDIO_C);
#endif
    commonAttributes.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX);
    commonAttributes.mvol.left = 0x3fff;
    commonAttributes.mvol.right = 0x3fff;
    commonAttributes.cd.volume.left = 0x3fff;
    commonAttributes.cd.volume.right = 0x3fff;
    commonAttributes.cd.mix = SPU_ON;
    SpuSetCommonAttr(&commonAttributes);
    SpuSetIRQ(SPU_OFF);
}

u_long sound_vagtospu(unsigned int VAG_data_size, u_char *VAG_data)
{
    u_long size;
    SpuSetTransferMode(SpuTransByDMA);
    size = SpuWrite(VAG_data + sizeof(VAGhdr), VAG_data_size);
    SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
    return size;
}

void sound_setvoiceattr(unsigned int pitch, int channel, u_long soundAddr, u_short key, int inst, u_short volL, u_short volR)
{
    SpuVoiceAttr voiceAttributes;

    if (inst)
    {
        voiceAttributes.mask =
            (SPU_VOICE_VOLL |
             SPU_VOICE_VOLR |
             SPU_VOICE_PITCH |
             SPU_VOICE_WDSA |
             SPU_VOICE_ADSR_AMODE |
             SPU_VOICE_ADSR_SMODE |
             SPU_VOICE_ADSR_RMODE |
             SPU_VOICE_ADSR_AR |
             SPU_VOICE_ADSR_DR |
             SPU_VOICE_ADSR_SR |
             SPU_VOICE_ADSR_RR |
             SPU_VOICE_ADSR_SL |
             SPU_VOICE_NOTE);
    }
    else
    {
        voiceAttributes.mask =
            (SPU_VOICE_VOLL |
             SPU_VOICE_VOLR |
             SPU_VOICE_PITCH |
             SPU_VOICE_WDSA |
             SPU_VOICE_ADSR_AMODE |
             SPU_VOICE_ADSR_SMODE |
             SPU_VOICE_ADSR_RMODE |
             SPU_VOICE_ADSR_AR |
             SPU_VOICE_ADSR_DR |
             SPU_VOICE_ADSR_SR |
             SPU_VOICE_ADSR_RR |
             SPU_VOICE_ADSR_SL);
    }
    voiceAttributes.voice = (0x1L << channel);
    voiceAttributes.volume.left = volL;
    voiceAttributes.volume.right = volR;
    voiceAttributes.pitch = pitch;
    voiceAttributes.addr = soundAddr;
    voiceAttributes.a_mode = SPU_VOICE_LINEARIncN;
    voiceAttributes.s_mode = SPU_VOICE_LINEARIncN;
    voiceAttributes.r_mode = SPU_VOICE_LINEARDecN;
    voiceAttributes.ar = 0x0;
    voiceAttributes.dr = 0x0;
    voiceAttributes.rr = inst == TRUE ? 0xC : 0x0;
    voiceAttributes.sr = 0x0;
    voiceAttributes.sl = 0xf;
    if (inst)
    {
        voiceAttributes.note = key;
    }
    SpuSetVoiceAttr(&voiceAttributes);

#if SPU_REVERBING == SPU_ON
    SpuReverbAttr reverbAttr;
    reverbAttr.mask = (SPU_REV_MODE | SPU_REV_DEPTHL | SPU_REV_DEPTHR);
    reverbAttr.depth.left = 0x0fff;
    reverbAttr.depth.right = 0x0fff;
    reverbAttr.mode = SPU_REV_MODE_STUDIO_C;
    SpuSetReverbModeParam(&reverbAttr);
    SpuSetReverbDepth(&reverbAttr);
#endif
}

u_long sound_settransfer(VAGsound *sound, u_long *file)
{
    u_long transferred, spu_address;
    const VAGhdr *VAGheader = (VAGhdr *)file;
    sound->pitch = (SWAP_ENDIAN32(VAGheader->samplingFrequency) << 12) / 44100L;
    spu_address = SpuMalloc(SWAP_ENDIAN32(VAGheader->dataSize));
    SpuSetTransferStartAddr(spu_address);
    transferred = sound_vagtospu(SWAP_ENDIAN32(VAGheader->dataSize), (u_char *)file);

    return spu_address;
}

void sound_playsfx(VAGsound *sound, int channel, u_short key, int inst, u_char volL, u_char volR)
{
    if (sound->spu_address != NULL)
    {
        sound_setvoiceattr(sound->pitch, channel, sound->spu_address, key, inst, volL == 0 ? 0 : (ushort)((volL * 4095u + 127u) / 255u), volR == 0 ? 0 : (ushort)((volL * 4095u + 127u) / 255u));

        SpuSetKey(SpuOn, (0x1L << channel));

#if SPU_REVERBING == SPU_ON
        SpuSetReverb(SPU_ON);
        SpuSetReverbVoice(SPU_ON, (0x1L << channel));
#endif
        sound_musicsync();
    }
}

void sound_stopsfx(int channel)
{
    SpuSetKey(SpuOff, (0x1L << channel));
    sound_musicsync();
}

void sound_loadmusic(u_long *file, int size, int max_chans)
{
    const char *lister = (char *)file;
    int idx = 0;
    int looper = 0;

    sound.max_channels = max_chans;

    sound.muser = (MusHdr *)malloc(size * sizeof(MusHdr));

    if (!sound.muser)
    {
        return;
    }

    for (int i = 0; i < 12 * size; i += 12)
    {
        sound.muser[idx].sampleid = (u_char)lister[i + 0];
        sound.muser[idx].channel = (u_char)lister[i + 1];
        sound.muser[idx].note_key = ((u_char)lister[i + 2] << 8) | (u_char)lister[i + 3];
        sound.muser[idx].timer = ((u_char)lister[i + 7] << 24) | ((u_char)lister[i + 6] << 16) | ((u_char)lister[i + 5] << 8) | (u_char)lister[i + 4];
        sound.muser[idx].loopStart = (u_char)lister[i + 8];
        sound.muser[idx].loopEnd = (u_char)lister[i + 9];
        sound.muser[idx].volL = (u_char)lister[i + 10];
        sound.muser[idx].volR = (u_char)lister[i + 11];

        for (int j = 0; j < max_chans; j++)
        {
            if (sound.muser[idx].channel == j && !sound.chan_start[j])
            {
                sound.chan_ofs[j] = idx;
                sound.chan_start[j] = TRUE;
                looper = 0;
            }
        }

        if (sound.muser[idx].loopStart == 0x01)
        {
            sound.chan_loop[sound.muser[idx].channel] = looper;
        }

        idx++;
        looper++;
    }
}

void sound_playmusic()
{
    sound.stopper = 0;
    ResetRCnt(RCntCNT1);
    SetRCnt(RCntCNT1, sound.mus_bpm, RCntMdINTR);
    StartRCnt(RCntCNT1);
    sound.musicEvent = OpenEvent(RCntCNT1, EvSpINT, EvMdINTR, sound_processmusic);
    EnableEvent(sound.musicEvent);

    sound.mus_playing = TRUE;
}

void sound_stopmusic()
{
    if (sound.mus_playing)
    {
        sound.mus_playing = FALSE;
        StopRCnt(RCntCNT1);
        DisableEvent(sound.musicEvent);
        CloseEvent(sound.musicEvent);
        for (int i = 0; i < 12; i++)
        {
            sound_stopsfx(i);
            sound.curPos[i] = 0;
            sound.mus_tick[i] = 0;
            sound.chan_start[i] = FALSE;
            sound.chan_stop[i] = FALSE;
            sound_musicsync();
        }
    }
}

void sound_musicsync()
{
    int cnt = 80;

    while (cnt > 0)
    {
        cnt--;
        VSync(1);
    }
}

void sound_clearmusic()
{
    if (sound.muser)
    {
        for (int i = 0; i < 12; i++)
        {
            sound.curPos[i] = 0;
            sound.mus_tick[i] = 0;
            sound.chan_loop[i] = 0;
            sound.chan_start[i] = FALSE;
            sound.chan_stop[i] = FALSE;
            sound.chan_ofs[i] = 0;
            sound.chan_loop[i] = 0;
            sound_musicsync();
        }

        free(sound.muser);
        sound.muser = NULL;
    }
}

void sound_setbpm(long bpm)
{
    sound.mus_bpm = (TIMER_FREQ * 60) / (bpm * 8600);
}

static long sound_processmusic()
{
    for (int i = 0; i < sound.max_channels; i++)
    {
        if (sound.mus_tick[i] >= sound.muser[sound.chan_ofs[i] + sound.curPos[i]].timer)
        {
            // if (i == sound.stopper)
            // {
            sound_stopsfx(sound.muser[sound.chan_ofs[i] + sound.curPos[i]].channel);
            // sound.chan_stop[i] = FALSE;
            // }
            sound.mus_tick[i] = 0;
            // for (int j = 0; j < sound.max_channels; j++)
            // {
            //     if (j != i && sound.mus_tick[j] > 0 && sound.muser[sound.chan_ofs[j] + sound.curPos[j]].time != sound.muser[sound.chan_ofs[i] + sound.curPos[i]].time)
            //     {
            //         sound.mus_tick[j]--;
            //     }
            // }
            if (sound.muser[sound.chan_ofs[i] + sound.curPos[i]].loopEnd == 0x01)
            {
                sound.curPos[i] = sound.chan_loop[i];
                sound.mus_tick[i] = 0;
            }
            else
            {
                sound.curPos[i]++;
                if (sound.muser[sound.chan_ofs[i] + sound.curPos[i]].channel != i)
                {
                    sound_stopmusic();
                    break;
                }
            }
        }

        if (sound.mus_tick[i] < sound.muser[sound.chan_ofs[i] + sound.curPos[i]].timer)
        {
            if (sound.mus_tick[i] == 0 && sound.muser[sound.chan_ofs[i] + sound.curPos[i]].sampleid != 0xFF)
            {
                sound_playsfx(&sound.mus[sound.muser[sound.chan_ofs[i] + sound.curPos[i]].sampleid], sound.muser[sound.chan_ofs[i] + sound.curPos[i]].channel, sound.muser[sound.chan_ofs[i] + sound.curPos[i]].note_key, TRUE, sound.muser[sound.chan_ofs[i] + sound.curPos[i]].volL, sound.muser[sound.chan_ofs[i] + sound.curPos[i]].volR);
            }

            // if (!sound.chan_stop[i] && sound.stopper == i)
            // {
            //     sound.chan_stop[i] = TRUE;
            // }
            // else
            // {
            sound.mus_tick[i]++;
            // }
        }
    }

    // if (sound.stopper < sound.max_channels - 1)
    // {
    //     sound.stopper++;
    // }
    // else
    // {
    //     sound.stopper = 0;
    // }

    SetRCnt(RCntCNT1, sound.mus_bpm, RCntMdINTR);

    return sound.mus_bpm;
}