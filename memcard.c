#include "memcard.h"

GameSave game_saver;

void memcard_init()
{
    MemCardInit(0);
    MemCardStart();
}

void memcard_prepareheader(u_long *icon1, u_long *icon2, int region)
{
    TIM_IMAGE *tim1;
    TIM_IMAGE *tim2;

    game_saver.mem_header.id[0] = 'S';
    game_saver.mem_header.id[1] = 'C';

    game_saver.mem_header.type = 0x12;
    game_saver.mem_header.size = 2;

    if (region == 0)
    {
        game_saver.mem_header.title[0] = 'L';
        game_saver.mem_header.title[1] = 'U';
        game_saver.mem_header.title[2] = 'P';
        game_saver.mem_header.title[3] = 'T';
        game_saver.mem_header.title[4] = 'A';
        game_saver.mem_header.title[5] = 'T';
        game_saver.mem_header.title[6] = 'O';
        game_saver.mem_header.title[7] = 'R';
        game_saver.mem_header.title[8] = 'I';
        game_saver.mem_header.title[9] = 'G';
        game_saver.mem_header.title[10] = 'R';
        game_saver.mem_header.title[11] = 'O';
        game_saver.mem_header.title[12] = 'Z';
        game_saver.mem_header.title[13] = 'A';
        game_saver.mem_header.title[14] = 'V';
        game_saver.mem_header.title[15] = 'I';
    }
    else if (region == 1)
    {
        game_saver.mem_header.title[0] = 'T';
        game_saver.mem_header.title[1] = 'H';
        game_saver.mem_header.title[2] = 'E';
        game_saver.mem_header.title[3] = 'G';
        game_saver.mem_header.title[4] = 'R';
        game_saver.mem_header.title[5] = 'E';
        game_saver.mem_header.title[6] = 'A';
        game_saver.mem_header.title[7] = 'T';
        game_saver.mem_header.title[8] = 'W';
        game_saver.mem_header.title[9] = 'A';
        game_saver.mem_header.title[10] = 'R';
        game_saver.mem_header.title[11] = 'R';
        game_saver.mem_header.title[12] = 'I';
        game_saver.mem_header.title[13] = 'O';
        game_saver.mem_header.title[14] = 'R';
        game_saver.mem_header.title[15] = 'S';
    }
    // else if (region == 2)
    // {
    //     game_saver.mem_header.title[0] = 0x83;
    //     game_saver.mem_header.title[1] = 0x77;
    //     game_saver.mem_header.title[2] = 0x83;
    //     game_saver.mem_header.title[3] = 0x8D;
    //     game_saver.mem_header.title[4] = 0x83;
    //     game_saver.mem_header.title[5] = 0x8F;
    //     game_saver.mem_header.title[6] = 0x83;
    //     game_saver.mem_header.title[7] = 0x8B;
    // }

    OpenTIM(icon1);
    ReadTIM(tim1);

    memcpy(game_saver.mem_header.clut, tim1->caddr, 32);
    memcpy(game_saver.icon1.sprt, tim1->paddr, 128);

    OpenTIM(icon2);
    ReadTIM(tim2);

    memcpy(game_saver.icon2.sprt, tim2->paddr, 128);
}

void memcard_clearheader()
{
    free(&game_saver.icon2);
    free(&game_saver.icon1);
    free(&game_saver.mem_header);
}

void memcard_save(u_char port, DATALOAD *data, int region, int mp)
{
    const char *save_name = "__MAIN-EXE01HELOCPP0";

    data->load = FALSE;

    if (region == 0)
    {
        strcpy((char *)save_name, SAVENAME_EU);
    }
    else if (region == 1)
    {
        strcpy((char *)save_name, SAVENAME_US);
    }
    else if (region == 2)
    {
        strcpy((char *)save_name, SAVENAME_JP);
    }

    MemCardExist(port);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    if ((game_saver.slotResult[0] == McErrNone) || (game_saver.slotResult[0] == McErrNewCard))
    {
        MemCardAccept(port);
        MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);
    }
    else if ((game_saver.slotResult[0] == McErrNotFormat))
    {
        MemCardFormat(port);
    }
    else
    {
        return;
    }

    if (MemCardOpen(port, (char *)save_name, O_WRONLY) == McErrFileNotExist)
    {

        if (MemCardCreateFile(port, (char *)save_name, game_saver.mem_header.size) == 0x07)
        {
            return;
        }
        MemCardOpen(port, (char *)save_name, O_WRONLY);
    }

    MemCardWriteData((u_long *)&game_saver.mem_header, 128 * 0, 128);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    MemCardWriteData((u_long *)&game_saver.icon1, 128 * 1, 128);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    MemCardWriteData((u_long *)&game_saver.icon2, 128 * 2, 128);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    MemCardWriteData((u_long *)&data->data, 128 * (3 + mp), 128);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    MemCardClose();

    data->load = TRUE;
}

DATALOAD memcard_load(u_char port, int region, int mp)
{
    const char *save_name = "__MAIN-EXE00HELOCPP0";

    if (region == 0)
    {
        strcpy((char *)save_name, SAVENAME_EU);
    }
    else if (region == 1)
    {
        strcpy((char *)save_name, SAVENAME_US);
    }
    else if (region == 2)
    {
        strcpy((char *)save_name, SAVENAME_JP);
    }

    DATALOAD dump_data = {0};
    dump_data.load = FALSE;

    MemCardExist(port);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    if ((game_saver.slotResult[0] == McErrNone) || (game_saver.slotResult[0] == McErrNewCard))
    {
        MemCardAccept(port);
        MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);
    }
    else
    {
        return dump_data;
    }

    if (MemCardOpen(port, (char *)save_name, O_RDONLY) == McErrFileNotExist)
    {
        return dump_data;
    }

    MemCardReadData((u_long *)&dump_data.data, 128 * (3 + mp), 128);
    MemCardSync(0, &game_saver.cardCmd, &game_saver.slotResult[0]);

    MemCardClose();

    dump_data.load = TRUE;

    return dump_data;
}