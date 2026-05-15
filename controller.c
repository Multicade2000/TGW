#include "controller.h"

GameController control;

void controller_init()
{
    control.align[0] = 0;
    control.align[1] = 1;
    control.align[2] = 0xFF;
    control.align[3] = 0xFF;
    control.align[4] = 0xFF;
    control.align[5] = 0xFF;

    control.motor[0][0] = 0;
    control.motor[0][1] = 0;
    control.motor[1][0] = 0;
    control.motor[1][1] = 0;
    control.motor[2][0] = 0;
    control.motor[2][1] = 0;
    control.motor[3][0] = 0;
    control.motor[3][1] = 0;
    control.motor[4][0] = 0;
    control.motor[4][1] = 0;
    control.motor[5][0] = 0;
    control.motor[5][1] = 0;
    control.motor[6][0] = 0;
    control.motor[6][1] = 0;
    control.motor[7][0] = 0;
    control.motor[7][1] = 0;

    control.vib_sync[0] = FALSE;
    control.vib_sync[1] = FALSE;
    control.vib_sync[2] = FALSE;
    control.vib_sync[3] = FALSE;
    control.vib_sync[4] = FALSE;
    control.vib_sync[5] = FALSE;
    control.vib_sync[6] = FALSE;
    control.vib_sync[7] = FALSE;

    PadInitMtap(control.padbuff[0], control.padbuff[1]);
    PadStartCom();
}

int controller_connected(int port)
{
    u_char *buff = control.padbuff[0];
    u_char *buff2 = control.padbuff[1];

    if (port == 0x00)
    {
        if (buff[0] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x10)
    {
        if (buff[2] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x11)
    {
        if (buff[10] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x12)
    {
        if (buff[18] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x13)
    {
        if (buff[26] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x01)
    {
        if (buff2[0] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x20)
    {
        if (buff2[2] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x21)
    {
        if (buff2[10] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x22)
    {
        if (buff2[18] == 0)
        {
            return TRUE;
        }
    }
    if (port == 0x23)
    {
        if (buff2[26] == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

u_char controller_type(int port)
{
    u_char *buff = control.padbuff[0];
    u_char *buff2 = control.padbuff[1];

    if (port == 0x00)
    {
        return buff[1] >> 4;
    }
    if (port == 0x10)
    {
        return buff[3] >> 4;
    }
    if (port == 0x11)
    {
        return buff[11] >> 4;
    }
    if (port == 0x12)
    {
        return buff[19] >> 4;
    }
    if (port == 0x13)
    {
        return buff[27] >> 4;
    }
    if (port == 0x01)
    {
        return buff2[1] >> 4;
    }
    if (port == 0x20)
    {
        return buff2[3] >> 4;
    }
    if (port == 0x21)
    {
        return buff2[11] >> 4;
    }
    if (port == 0x22)
    {
        return buff2[19] >> 4;
    }
    if (port == 0x23)
    {
        return buff2[27] >> 4;
    }

    return 0x0;
}

u_short controller_btn(int port)
{
    u_char *buff = control.padbuff[0];
    u_char *buff2 = control.padbuff[1];

    if (port == 0x00)
    {
        return *((u_short *)(buff + 2));
    }
    if (port == 0x10)
    {
        return *((u_short *)(buff + 4));
    }
    if (port == 0x11)
    {
        return *((u_short *)(buff + 12));
    }
    if (port == 0x12)
    {
        return *((u_short *)(buff + 20));
    }
    if (port == 0x13)
    {
        return *((u_short *)(buff + 28));
    }
    if (port == 0x01)
    {
        return *((u_short *)(buff2 + 2));
    }
    if (port == 0x20)
    {
        return *((u_short *)(buff2 + 4));
    }
    if (port == 0x21)
    {
        return *((u_short *)(buff2 + 12));
    }
    if (port == 0x22)
    {
        return *((u_short *)(buff2 + 20));
    }
    if (port == 0x23)
    {
        return *((u_short *)(buff2 + 28));
    }

    return 0;
}

u_char controller_stick(int port, int stick)
{
    u_char *buff = control.padbuff[0];
    u_char *buff2 = control.padbuff[1];

    if (port == 0x00)
    {
        return buff[4 + stick];
    }
    if (port == 0x10)
    {
        return buff[6 + stick];
    }
    if (port == 0x11)
    {
        return buff[14 + stick];
    }
    if (port == 0x12)
    {
        return buff[22 + stick];
    }
    if (port == 0x13)
    {
        return buff[30 + stick];
    }
    if (port == 0x01)
    {
        return buff2[4 + stick];
    }
    if (port == 0x20)
    {
        return buff2[6 + stick];
    }
    if (port == 0x21)
    {
        return buff2[14 + stick];
    }
    if (port == 0x22)
    {
        return buff2[22 + stick];
    }
    if (port == 0x23)
    {
        return buff2[30 + stick];
    }

    return 0;
}

void controller_vibrate(int port)
{
    int index = 0;

    switch (port)
    {
    case 0x00:
    {
        index = 0;
        break;
    }
    case 0x01:
    {
        index = 1;
        break;
    }
    case 0x02:
    {
        index = 2;
        break;
    }
    case 0x03:
    {
        index = 3;
        break;
    }
    case 0x10:
    {
        index = 4;
        break;
    }
    case 0x11:
    {
        index = 5;
        break;
    }
    case 0x12:
    {
        index = 6;
        break;
    }
    case 0x13:
    {
        index = 7;
        break;
    }
    }

    if (control.vib_sync[index] == TRUE)
    {
        if (PadGetState(port) == PadStateStable)
        {
            while (PadSetActAlign(port, control.align) != 0)
            {
                VSync(0);
            }

            PadSetAct(port, control.motor[index], sizeof(control.motor[index]));
        }

        control.vib_sync[index] = FALSE;
    }
}

PlayerCtrl controller_getplayer(int pidx)
{
    PlayerCtrl plr_ctrl = {0};
    plr_ctrl.connected = FALSE;
    plr_ctrl.btn = 0;
    plr_ctrl.ls_x = 0;
    plr_ctrl.ls_y = 0;
    plr_ctrl.rs_x = 0;
    plr_ctrl.rs_y = 0;
    plr_ctrl.type = 0;
    plr_ctrl.porter = 0;

    if (pidx == 0)
    {
        if (controller_connected(0x00) == TRUE)
        {
            if (controller_type(0x00) == 0x4)
            {
                plr_ctrl.type = controller_type(0x00);
                control.pcon[0] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x00;
                plr_ctrl.btn = controller_btn(0x00);
            }
            else if (controller_type(0x00) == 0x7)
            {
                plr_ctrl.type = controller_type(0x00);
                control.pcon[0] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x00;
                plr_ctrl.btn = controller_btn(0x00);
                plr_ctrl.rs_x = (int)(controller_stick(0x00, 0)-128);
                plr_ctrl.rs_y = (int)(controller_stick(0x00, 1)-128);
                plr_ctrl.ls_x = (int)(controller_stick(0x00, 2)-128);
                plr_ctrl.ls_y = (int)(controller_stick(0x00, 3)-128);
            }
            else if (controller_type(0x00) == 0x8)
            {
                if (controller_connected(0x10) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x10);
                    
                    if (controller_type(0x10) == 0x4)
                    {
                        control.pcon[0] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x00;
                        plr_ctrl.btn = controller_btn(0x10);
                    }
                    else if (controller_type(0x10) == 0x7)
                    {
                        control.pcon[0] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x00;
                        plr_ctrl.btn = controller_btn(0x10);
                        plr_ctrl.rs_x = (int)(controller_stick(0x10, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x10, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x10, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x10, 3)-128);
                    }
                }
            }
        }
        if (controller_connected(0x01) == TRUE && control.pcon[0] == FALSE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x20) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x20);

                    if (controller_type(0x20) == 0x4)
                    {
                        control.pcon[4] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x10;
                        plr_ctrl.btn = controller_btn(0x20);
                    }
                    else if (controller_type(0x20) == 0x7)
                    {
                        control.pcon[4] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x10;
                        plr_ctrl.btn = controller_btn(0x20);
                        plr_ctrl.rs_x = (int)(controller_stick(0x20, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x20, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x20, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x20, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 1)
    {
        if (controller_connected(0x00) == TRUE)
        {
            if (controller_type(0x00) == 0x8)
            {
                if (controller_connected(0x11) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x11);

                    if (controller_type(0x11) == 0x4)
                    {
                        control.pcon[1] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x01;
                        plr_ctrl.btn = controller_btn(0x11);
                    }
                    else if (controller_type(0x11) == 0x7)
                    {
                        control.pcon[1] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x01;
                        plr_ctrl.btn = controller_btn(0x11);
                        plr_ctrl.rs_x = (int)(controller_stick(0x11, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x11, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x11, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x11, 3)-128);
                    }
                }
            }
        }
        if (controller_connected(0x01) == TRUE && control.pcon[1] == FALSE)
        {
            if (controller_type(0x01) == 0x4)
            {
                plr_ctrl.type = controller_type(0x01);
                control.pcon[4] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x10;
                plr_ctrl.btn = controller_btn(0x01);
            }
            else if (controller_type(0x01) == 0x7)
            {
                plr_ctrl.type = controller_type(0x01);
                control.pcon[4] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x10;
                plr_ctrl.btn = controller_btn(0x01);
                plr_ctrl.rs_x = (int)(controller_stick(0x01, 0)-128);
                plr_ctrl.rs_y = (int)(controller_stick(0x01, 1)-128);
                plr_ctrl.ls_x = (int)(controller_stick(0x01, 2)-128);
                plr_ctrl.ls_y = (int)(controller_stick(0x01, 3)-128);
            }
            else if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x21) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x01);
                    
                    if (controller_type(0x21) == 0x4)
                    {
                        control.pcon[5] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x11;
                        plr_ctrl.btn = controller_btn(0x21);
                    }
                    else if (controller_type(0x21) == 0x7)
                    {
                        control.pcon[5] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x11;
                        plr_ctrl.btn = controller_btn(0x21);
                        plr_ctrl.rs_x = (int)(controller_stick(0x21, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x21, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x21, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x21, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 2)
    {
        if (controller_connected(0x00) == TRUE)
        {
            if (controller_type(0x00) == 0x8)
            {
                if (controller_connected(0x12) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x12);
                    
                    if (controller_type(0x12) == 0x4)
                    {
                        control.pcon[2] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x02;
                        plr_ctrl.btn = controller_btn(0x12);
                    }
                    else if (controller_type(0x12) == 0x7)
                    {
                        control.pcon[2] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x02;
                        plr_ctrl.btn = controller_btn(0x12);
                        plr_ctrl.rs_x = (int)(controller_stick(0x12, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x12, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x12, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x12, 3)-128);
                    }
                }
            }
        }
        if (controller_connected(0x01) == TRUE && control.pcon[2] == FALSE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x22) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x22);

                    if (controller_type(0x22) == 0x4)
                    {
                        control.pcon[6] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x12;
                        plr_ctrl.btn = controller_btn(0x22);
                    }
                    else if (controller_type(0x22) == 0x7)
                    {
                        control.pcon[6] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x12;
                        plr_ctrl.btn = controller_btn(0x22);
                        plr_ctrl.rs_x = (int)(controller_stick(0x22, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x22, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x22, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x22, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 3)
    {
        if (controller_connected(0x00) == TRUE)
        {
            if (controller_type(0x00) == 0x8)
            {
                if (controller_connected(0x13) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x13);

                    if (controller_type(0x13) == 0x4)
                    {
                        control.pcon[3] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x03;
                        plr_ctrl.btn = controller_btn(0x13);
                    }
                    else if (controller_type(0x13) == 0x7)
                    {
                        control.pcon[3] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x03;
                        plr_ctrl.btn = controller_btn(0x13);
                        plr_ctrl.rs_x = (int)(controller_stick(0x13, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x13, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x13, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x13, 3)-128);
                    }
                }
            }
        }
        if (controller_connected(0x01) == TRUE && control.pcon[3] == FALSE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x23) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x23);

                    if (controller_type(0x23) == 0x4)
                    {
                        control.pcon[7] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x13;
                        plr_ctrl.btn = controller_btn(0x23);
                    }
                    else if (controller_type(0x23) == 0x7)
                    {
                        control.pcon[7] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x13;
                        plr_ctrl.btn = controller_btn(0x23);
                        plr_ctrl.rs_x = (int)(controller_stick(0x23, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x23, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x23, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x23, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 4 && control.pcon[4] == FALSE)
    {
        if (controller_connected(0x01) == TRUE)
        {
            if (controller_type(0x01) == 0x4)
            {
                plr_ctrl.type = controller_type(0x01);
                control.pcon[4] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x10;
                plr_ctrl.btn = controller_btn(0x01);
            }
            else if (controller_type(0x01) == 0x7)
            {
                plr_ctrl.type = controller_type(0x01);
                control.pcon[4] = TRUE;
                plr_ctrl.connected = TRUE;
                plr_ctrl.porter = 0x10;
                plr_ctrl.btn = controller_btn(0x01);
                plr_ctrl.rs_x = (int)(controller_stick(0x01, 0)-128);
                plr_ctrl.rs_y = (int)(controller_stick(0x01, 1)-128);
                plr_ctrl.ls_x = (int)(controller_stick(0x01, 2)-128);
                plr_ctrl.ls_y = (int)(controller_stick(0x01, 3)-128);
            }
            else if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x20) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x20);

                    if (controller_type(0x20) == 0x4)
                    {
                        control.pcon[4] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x10;
                        plr_ctrl.btn = controller_btn(0x20);
                    }
                    else if (controller_type(0x20) == 0x7)
                    {
                        control.pcon[4] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x10;
                        plr_ctrl.btn = controller_btn(0x20);
                        plr_ctrl.rs_x = (int)(controller_stick(0x20, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x20, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x20, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x20, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 5 && control.pcon[5] == FALSE)
    {
        if (controller_connected(0x01) == TRUE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x21) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x21);
                    
                    if (controller_type(0x21) == 0x4)
                    {
                        control.pcon[5] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x11;
                        plr_ctrl.btn = controller_btn(0x21);
                    }
                    else if (controller_type(0x21) == 0x7)
                    {
                        control.pcon[5] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x11;
                        plr_ctrl.btn = controller_btn(0x21);
                        plr_ctrl.rs_x = (int)(controller_stick(0x21, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x21, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x21, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x21, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 6 && control.pcon[6] == FALSE)
    {
        if (controller_connected(0x01) == TRUE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x22) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x22);
                    
                    if (controller_type(0x22) == 0x4)
                    {
                        control.pcon[6] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x12;
                        plr_ctrl.btn = controller_btn(0x22);
                    }
                    else if (controller_type(0x22) == 0x7)
                    {
                        control.pcon[6] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x12;
                        plr_ctrl.btn = controller_btn(0x22);
                        plr_ctrl.rs_x = (int)(controller_stick(0x22, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x22, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x22, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x22, 3)-128);
                    }
                }
            }
        }
    }
    else if (pidx == 7 && control.pcon[7] == FALSE)
    {
        if (controller_connected(0x01) == TRUE)
        {
            if (controller_type(0x01) == 0x8)
            {
                if (controller_connected(0x23) == TRUE)
                {
                    plr_ctrl.type = controller_type(0x23);
                    
                    if (controller_type(0x23) == 0x4)
                    {
                        control.pcon[7] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x13;
                        plr_ctrl.btn = controller_btn(0x23);
                    }
                    else if (controller_type(0x23) == 0x7)
                    {
                        control.pcon[7] = TRUE;
                        plr_ctrl.connected = TRUE;
                        plr_ctrl.porter = 0x13;
                        plr_ctrl.btn = controller_btn(0x23);
                        plr_ctrl.rs_x = (int)(controller_stick(0x23, 0)-128);
                        plr_ctrl.rs_y = (int)(controller_stick(0x23, 1)-128);
                        plr_ctrl.ls_x = (int)(controller_stick(0x23, 2)-128);
                        plr_ctrl.ls_y = (int)(controller_stick(0x23, 3)-128);
                    }
                }
            }
        }
    }

    return plr_ctrl;
}