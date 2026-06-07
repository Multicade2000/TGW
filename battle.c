#include "battle.h"
#include "game.h"

FX *fire;

void battle_init(SceneBattle *battle)
{
    graph.last_vsync = VSync(-1);
    battle->people = NULL;
    battle->b_save = FALSE;
    battle->fx = NULL;
    battle->active = TRUE;
    battle->max_people = 1;
    battle->turn = 0;
    battle->retry = FALSE;
    battle->reverse = FALSE;
    battle->lvl_max = 1;

    battle->spell_cost[0] = 10;
    battle->spell_cost[1] = 20;
    battle->spell_cost[2] = 40;
    battle->spell_cost[3] = 60;
    battle->spell_cost[4] = 80;
    battle->spell_cost[5] = 100;
    battle->spell_cost[6] = 200;
    battle->spell_cost[7] = 400;
    battle->spell_cost[8] = 500;
    battle->spell_cost[9] = 1000;

    if (plr[0] > 0)
    {
        battle->max_people++;
    }
    if (plr[1] > 0)
    {
        battle->max_people++;
    }
    if (plr[2] > 0)
    {
        battle->max_people++;
    }

    battle->people = (Person *)malloc(battle->max_people * sizeof(Person));

    battle->people[0].type = 0;
    battle->people[0].plr = 1;

    if (battle->max_people >= 2)
    {
        battle->people[1].type = 0;
        battle->people[1].plr = plr[0] == 2 ? 2 : 0;
    }

    if (battle->max_people >= 3)
    {
        battle->people[2].type = 0;
        battle->people[2].plr = plr[1] == 2 ? 3 : 0;
    }

    if (battle->max_people >= 4)
    {
        battle->people[3].type = 0;
        battle->people[3].plr = plr[2] == 2 ? 4 : 0;
    }

    battle->turn = (u_char)(rand() % battle->max_people);

    for (u_char i = 0; i < battle->max_people; i++)
    {
        battle->people[i].b_load = FALSE;

        person_init(&battle->people[i]);

        if (battle->people[i].plr > 0 && battle->lvl_max <= battle->people[i].lvl)
        {
            battle->lvl_max = battle->people[i].lvl;
        }
    }

    battle->people[0].spr.MovVector.vx = -128;
    battle->people[1].spr.MovVector.vx = 128;
    battle->people[1].spr.ScaleVector.vx = -(ONE * 2);

    if (battle->max_people >= 3)
    {
        battle->people[2].spr.MovVector.vy = -(graph.ResH / 2);
    }

    if (battle->max_people >= 4)
    {
        battle->people[3].spr.MovVector.vy = (graph.ResH / 2);
    }

    battle->people[0].def_loc = battle->people[0].spr.MovVector;
    battle->people[1].def_loc = battle->people[1].spr.MovVector;
    battle->people[2].def_loc = battle->people[2].spr.MovVector;
    battle->people[3].def_loc = battle->people[3].spr.MovVector;

    graph.scr_fade = 0;
}

void battle_update(SceneBattle *battle)
{
    // battle->reverse = TRUE;

    if (!battle->reverse)
    {
        if (graph.scr_fade < 128 - graph.delta)
        {
            graph.scr_fade += 2 * graph.delta;
        }
        else
        {
            graph.scr_fade = 128;
        }
        // else
        // {
        //     battle->retry = TRUE;
        //     battle->reverse = !battle->reverse;
        // }
    }
    else
    {
        if (graph.scr_fade > 0 + graph.delta)
        {
            graph.scr_fade -= 2 * graph.delta;
        }
        else
        {
            graph.scr_fade = 0;
            if (battle->retry)
            {
                battle->reverse = !battle->reverse;
                battle->retry = FALSE;

                for (u_char i = 0; i < battle->max_people; i++)
                {
                    person_init(&battle->people[i]);

                    if (battle->people[i].plr > 0 && battle->lvl_max <= battle->people[i].lvl)
                    {
                        battle->lvl_max = battle->people[i].lvl;
                    }
                }

                battle->people[0].spr.MovVector.vx = -128;
                battle->people[1].spr.MovVector.vx = 128;
                battle->people[1].spr.ScaleVector.vx = -(ONE * 2);

                if (battle->max_people >= 3)
                {
                    battle->people[2].spr.MovVector.vy = -(graph.ResH / 2);
                }

                if (battle->max_people >= 4)
                {
                    battle->people[3].spr.MovVector.vy = (graph.ResH / 2);
                }

                battle->people[0].def_loc = battle->people[0].spr.MovVector;
                battle->people[1].def_loc = battle->people[1].spr.MovVector;
                battle->people[2].def_loc = battle->people[2].spr.MovVector;
                battle->people[3].def_loc = battle->people[3].spr.MovVector;

                battle->menu = 0;
            }
            else
            {
                lvl = 1;
                free(battle->people);

                FX *curr = battle->fx;
                FX *prev = NULL;

                while (curr)
                {
                    FX *toDelete = curr;
                    if (prev)
                        prev->next = curr->next;
                    else
                        battle->fx = curr->next;

                    curr = curr->next;

                    free(toDelete);
                    continue;
                }

                battle->active = FALSE;
            }
        }
    }

    for (u_char i = 0; i < battle->max_people; i++)
    {
        battle->people[i].turn = (battle->turn == i ? TRUE : FALSE);
        person_update(&battle->people[i]);
    }

    u_char exp = 0;
    VECTOR parent;

    FX *curr = battle->fx;
    FX *prev = NULL;

    while (curr)
    {
        fx_update(curr);

        if (curr->active == FALSE)
        {
            if (curr->type == 0)
            {
                exp = 1;
            }
            else if (curr->type == 3)
            {
                exp = 2;
            }

            if (exp > 0)
            {
                parent.vx = curr->spr.MovVector.vx;
                parent.vy = curr->spr.MovVector.vy;
                parent.vz = curr->spr.MovVector.vz;
            }

            if (fire == curr)
            {
                fire = NULL;
            }

            FX *toDelete = curr;
            if (prev)
                prev->next = curr->next;
            else
                battle->fx = curr->next;

            curr = curr->next;

            free(toDelete);
            continue;
        }

        prev = curr;
        curr = curr->next;
    }

    if (exp > 0)
    {
        FX *obj = battle_spawnfx(btl);

        if (obj)
        {
            obj->type = exp == 1 ? 1 : 10;
            obj->reverse = FALSE;
            fx_init(obj);

            obj->spr.MovVector.vx = parent.vx;
            obj->spr.MovVector.vy = parent.vy;
            obj->spr.MovVector.vz = parent.vz - 1;

            sound_playsfx(&sfx[10], 16, 0x0000, FALSE, 255, 255);
        }
    }

    graph_drawback(getTPage(0, 0, 960, 0), getClut(256, 510));
}

void person_init(Person *person)
{
    person->tick = 0;
    person->max_tick = 20;
    person->turn = FALSE;
    person->walk = FALSE;
    person->act = 0;
    person->act_tick = 0;
    person->act_count = 0;
    person->anim = 0;
    person->action[0] = 0;
    person->action[1] = 0;
    person->action[2] = 0;
    person->alive = TRUE;
    person->turn_start = FALSE;

    person->dmgt = FALSE;
    person->dmgt_speed = -4;
    person->dmgt_c = 0;
    person->dmgt_x = 0;
    person->dmgt_y = 0;
    person->dmgt_tick = 0;

    person->dodge = FALSE;
    person->parry = FALSE;

    person->spr.MovVector.vx = 0;
    person->spr.MovVector.vy = 0;
    person->spr.MovVector.vz = 256;
    person->spr.RotVector.vx = 0;
    person->spr.RotVector.vy = 0;
    person->spr.RotVector.vz = 0;
    person->spr.ScaleVector.vx = ONE * 2;
    person->spr.ScaleVector.vy = ONE * 2;
    person->spr.ScaleVector.vz = ONE * 2;

    person->spell_used[0] = FALSE;
    person->spell_used[1] = FALSE;
    person->spell_used[2] = FALSE;
    person->spell_used[3] = FALSE;
    person->spell_used[4] = FALSE;
    person->spell_used[5] = FALSE;
    person->spell_used[6] = FALSE;
    person->spell_used[7] = FALSE;
    person->spell_used[8] = FALSE;
    person->spell_used[9] = FALSE;

    person->pivot.vx = 0;
    person->pivot.vy = 0;
    person->pivot.vz = 0;

    person->spr.r = 128;
    person->spr.g = 128;
    person->spr.b = 128;
    person->spr.alpha = 128;
    person->shd_mode = FALSE;

    switch (person->type)
    {
    case 0:
    {
        if (person->plr > 0)
        {
            if (!person->b_load)
            {
                if (memlod)
                {
                    person->ctrl = controller_getplayer(person->plr - 1);

                    if (person->ctrl.connected)
                    {
                        controller_vibrate(person->ctrl.porter);
                        DATALOAD load = memcard_load(person->ctrl.porter, REGION_CODE, 1);

                        graph.last_vsync = VSync(-1);

                        if (load.load)
                        {
                            person->lvl = load.data.lvl;
                            person->pot[0] = load.data.pot[0];
                            person->pot[1] = load.data.pot[1];
                            person->pot[2] = load.data.pot[2];
                            person->spell_rank[0] = load.data.spell_rank[0];
                            person->spell_rank[1] = load.data.spell_rank[1];
                            person->spell_rank[2] = load.data.spell_rank[2];
                            person->spell_rank[3] = load.data.spell_rank[3];
                            person->spell_rank[4] = load.data.spell_rank[4];
                            person->spell_rank[5] = load.data.spell_rank[5];
                            person->spell_rank[6] = load.data.spell_rank[6];
                            person->spell_rank[7] = load.data.spell_rank[7];
                            person->spell_rank[8] = load.data.spell_rank[8];
                            person->spell_rank[9] = load.data.spell_rank[9];
                        }
                        else
                        {
                            person->lvl = 1;
                            person->pot[0] = 0;
                            person->pot[1] = 0;
                            person->pot[2] = 0;
                            person->spell_rank[0] = 1;
                            person->spell_rank[1] = 1;
                            person->spell_rank[2] = 1;
                            person->spell_rank[3] = 1;
                            person->spell_rank[4] = 1;
                            person->spell_rank[5] = 1;
                            person->spell_rank[6] = 1;
                            person->spell_rank[7] = 1;
                            person->spell_rank[8] = 1;
                            person->spell_rank[9] = 1;
                        }
                    }
                    else
                    {
                        person->lvl = 1;
                        person->pot[0] = 0;
                        person->pot[1] = 0;
                        person->pot[2] = 0;
                        person->spell_rank[0] = 1;
                        person->spell_rank[1] = 1;
                        person->spell_rank[2] = 1;
                        person->spell_rank[3] = 1;
                        person->spell_rank[4] = 1;
                        person->spell_rank[5] = 1;
                        person->spell_rank[6] = 1;
                        person->spell_rank[7] = 1;
                        person->spell_rank[8] = 1;
                        person->spell_rank[9] = 1;
                    }
                }
                else
                {
                    person->lvl = 1;
                    person->pot[0] = 0;
                    person->pot[1] = 0;
                    person->pot[2] = 0;
                    person->spell_rank[0] = 1;
                    person->spell_rank[1] = 1;
                    person->spell_rank[2] = 1;
                    person->spell_rank[3] = 1;
                    person->spell_rank[4] = 1;
                    person->spell_rank[5] = 1;
                    person->spell_rank[6] = 1;
                    person->spell_rank[7] = 1;
                    person->spell_rank[8] = 1;
                    person->spell_rank[9] = 1;
                }

                person->b_load = TRUE;
            }
        }
        else
        {
            person->lvl = (u_char)((rand() % btl->lvl_max) + 1);

            for (u_char i = 0; i < 3; i++)
            {
                person->pot[i] = (u_char)(rand() % (50 + 1));

                if (person->pot[i] > person->lvl - 1)
                {
                    person->pot[i] = person->lvl - 1;
                }
            }

            person->spell_rank[0] = (u_char)((rand() % 5) + 1);
            person->spell_rank[1] = (u_char)((rand() % 5) + 1);
            person->spell_rank[2] = (u_char)((rand() % 5) + 1);
            person->spell_rank[3] = (u_char)((rand() % 5) + 1);
            person->spell_rank[4] = (u_char)((rand() % 5) + 1);
            person->spell_rank[5] = (u_char)((rand() % 5) + 1);
            person->spell_rank[6] = (u_char)((rand() % 5) + 1);
            person->spell_rank[7] = (u_char)((rand() % 5) + 1);
            person->spell_rank[8] = (u_char)((rand() % 5) + 1);
            person->spell_rank[9] = (u_char)((rand() % 5) + 1);

            if (person->spell_rank[0] > person->lvl - 1)
            {
                person->spell_rank[0] = person->lvl - 1;
            }

            if (person->spell_rank[1] > person->lvl - 4)
            {
                person->spell_rank[1] = person->lvl - 4;
            }

            if (person->spell_rank[2] > person->lvl - 9)
            {
                person->spell_rank[2] = person->lvl - 9;
            }

            if (person->spell_rank[3] > person->lvl - 19)
            {
                person->spell_rank[3] = person->lvl - 19;
            }

            if (person->spell_rank[4] > person->lvl - 39)
            {
                person->spell_rank[4] = person->lvl - 39;
            }

            if (person->spell_rank[5] > person->lvl - 49)
            {
                person->spell_rank[5] = person->lvl - 49;
            }

            if (person->spell_rank[6] > person->lvl - 74)
            {
                person->spell_rank[6] = person->lvl - 74;
            }

            if (person->spell_rank[7] > person->lvl - 89)
            {
                person->spell_rank[7] = person->lvl - 89;
            }

            if (person->spell_rank[8] > person->lvl - 99)
            {
                person->spell_rank[8] = person->lvl - 99;
            }

            if (person->spell_rank[9] > person->lvl - 199)
            {
                person->spell_rank[9] = person->lvl - 199;
            }
        }

        person->max_hp = 5 * person->lvl;
        person->max_mp = 10 * person->lvl;
        person->hp = person->max_hp;
        person->mp = person->max_mp;
        person->shd_mana = 0;
        person->regen = 0;
        person->poison = 0;
        person->freeze = 0;

        person->spell[0] = person->lvl >= 2 ? TRUE : FALSE;
        person->spell[1] = person->lvl >= 5 ? TRUE : FALSE;
        person->spell[2] = person->lvl >= 10 ? TRUE : FALSE;
        person->spell[3] = person->lvl >= 20 ? TRUE : FALSE;
        person->spell[4] = person->lvl >= 40 ? TRUE : FALSE;
        person->spell[5] = person->lvl >= 50 ? TRUE : FALSE;
        person->spell[6] = person->lvl >= 75 ? TRUE : FALSE;
        person->spell[7] = person->lvl >= 90 ? TRUE : FALSE;
        person->spell[8] = person->lvl >= 100 ? TRUE : FALSE;
        person->spell[9] = person->lvl >= 200 ? TRUE : FALSE;

        person->armor = 0;
        person->shd = 0;
        person->dmg = 2;

        if (person->lvl >= 5) // Wooden Armor
        {
            person->armor = 1;
            person->shd = 1;
            person->dmg = 10;
        }

        if (person->lvl >= 10) // Stone Armor
        {
            person->armor = 2;
            person->shd = 2;
            person->dmg = 20;
        }

        if (person->lvl >= 20) // Golden Armor
        {
            person->armor = 3;
            person->shd = 3;
            person->dmg = 40;
        }

        if (person->lvl >= 40) // Iron Armor
        {
            person->armor = 4;
            person->shd = 4;
            person->dmg = 80;
        }

        if (person->lvl >= 50) // Diamond Armor
        {
            person->armor = 5;
            person->shd = 5;
            person->dmg = 100;
        }

        if (person->lvl >= 75) // Emerald Armor
        {
            person->armor = 6;
            person->shd = 6;
            person->dmg = 200;
        }

        if (person->lvl >= 100) // Redstone Armor
        {
            person->armor = 7;
            person->shd = 7;
            person->dmg = 2500;
        }

        if (person->lvl >= 200) // Ender Armor
        {
            person->armor = 8;
            person->shd = 8;
            person->dmg = 5000;
        }

        switch (person->armor)
        {
        case 0:
        {
            person->armor_hp = 0;
            person->spr.clut = getClut(256, 448);
            break;
        }
        case 1:
        {
            person->armor_hp = 10;
            person->spr.clut = getClut(256, 451); // Wooden Armor
            break;
        }
        case 2:
        {
            person->armor_hp = 20;
            person->spr.clut = getClut(256, 452); // Stone Armor
            break;
        }
        case 3:
        {
            person->armor_hp = 40;
            person->spr.clut = getClut(256, 453); // Golden Armor
            break;
        }
        case 4:
        {
            person->armor_hp = 80;
            person->spr.clut = getClut(256, 454); // Iron Armor
            break;
        }
        case 5:
        {
            person->armor_hp = 100;
            person->spr.clut = getClut(256, 455); // Diamond Armor
            break;
        }
        case 6:
        {
            person->armor_hp = 200;
            person->spr.clut = getClut(256, 456); // Emerald Armor
            break;
        }
        case 7:
        {
            person->armor_hp = 5000;
            person->spr.clut = getClut(256, 457); // Redstone Armor
            break;
        }
        case 8:
        {
            person->armor_hp = 10000;
            person->spr.clut = getClut(256, 458); // Ender Armor
            break;
        }
        default:
        {
            break;
        }
        }

        switch (person->shd)
        {
        case 0:
        {
            person->shd_hp = 0;
            break;
        }
        case 1:
        {
            person->shd_hp = 5;
            break;
        }
        case 2:
        {
            person->shd_hp = 10;
            break;
        }
        case 3:
        {
            person->shd_hp = 20;
            break;
        }
        case 4:
        {
            person->shd_hp = 40;
            break;
        }
        case 5:
        {
            person->shd_hp = 50;
            break;
        }
        case 6:
        {
            person->shd_hp = 100;
            break;
        }
        case 7:
        {
            person->shd_hp = 2500;
            break;
        }
        case 8:
        {
            person->shd_hp = 5000;
            break;
        }
        default:
        {
            break;
        }
        }

        person->spr.tpage = getTPage(0, 0, 256, 0);
        person->spr.u = 0;
        person->spr.v = 0;
        person->spr.w = 32;
        person->spr.h = 32;

        break;
    }
    default:
    {
        break;
    }
    }
}

void person_update(Person *person)
{
    u_int fps = REGION_CODE == 0 ? 50 : 60;
    u_char vib_mode = 0;

    if (person->anim != 3)
    {
        person->pivot.vx = person->spr.MovVector.vx;
        person->pivot.vy = person->spr.MovVector.vy;
        person->pivot.vz = person->spr.MovVector.vz;
    }

    if (person->armor_hp <= 0)
    {
        person->spr.clut = getClut(256, 448);
    }

    if (person->alive)
    {
        person->tick += graph.delta;

        if (person->tick >= person->max_tick)
        {
            if (person->anim == 0)
            {
                if (person->freeze <= 0)
                {
                    if (!person->shd_mode)
                    {
                        if (person->spr.u == 0)
                        {
                            person->spr.u = 32;
                            person->spr.v = 0;
                        }
                        else
                        {
                            person->spr.u = 0;
                            person->spr.v = 0;
                        }
                    }
                    else
                    {
                        person->spr.u = 0;
                        person->spr.v = 32;
                    }
                }
            }
            else if (person->anim == 1)
            {
                if (person->spr.u == 64)
                {
                    person->spr.u = 96;
                    person->spr.v = 0;
                }
                else if (person->spr.u == 96)
                {
                    person->spr.u = person->walk ? 64 : 128;
                    person->spr.v = 0;
                    person->walk = !person->walk;
                }
                else
                {
                    person->spr.u = 96;
                    person->spr.v = 0;
                }
            }
            else if (person->anim == 2)
            {
                if (person->spr.u == 64)
                {
                    person_damage(&btl->people[person->action[2]], person, 0, TRUE);
                    person->spr.u = 160;
                    person->spr.v = 0;
                }
            }
            else if (person->anim == 3)
            {
                person->spr.MovVector.vx = person->pivot.vx;
                person->spr.MovVector.vy = person->pivot.vy;

                person->dmgt_x = (person->spr.MovVector.vx / 2) + 128;
                person->dmgt_y = ((person->spr.MovVector.vy + 48) / 2) + 128;

                person->dmgt = TRUE;

                if (person->hp > 0)
                {
                    if (person->freeze <= 0)
                    {
                        if (!person->shd_mode)
                        {
                            person->spr.u = 0;
                            person->spr.v = 0;
                        }
                        else
                        {
                            person->spr.u = 0;
                            person->spr.v = 32;
                        }
                    }

                    person->anim = 0;
                    person->max_tick = 20;

                    if (person->turn && btl->menu == 3)
                    {
                        if (person->action[0] == 0)
                        {
                            person->act_tick = 0;
                            person->act_count = 0;
                            person->act++;
                        }
                        else if (person->action[1] == 6)
                        {
                            person->act_tick = 0;

                            if (person->act_count >= 5 * person->spell_rank[person->action[1]])
                            {
                                person->act_count = 0;
                                person->act++;
                            }
                        }
                    }
                }
                else
                {
                    sound_playsfx(&sfx[29], 17, 0x0000, FALSE, 255, 255);
                    person->alive = FALSE;
                }
            }
            else if (person->anim == 5)
            {
                if (person->dodge || (person->parry && person->spr.u == 32))
                {
                    person->spr.MovVector.vx = person->def_loc.vx;
                    person->spr.MovVector.vy = person->def_loc.vy;
                    person->spr.MovVector.vz = person->def_loc.vz;

                    person->pivot.vx = person->spr.MovVector.vx;
                    person->pivot.vy = person->spr.MovVector.vy;
                    person->pivot.vz = person->spr.MovVector.vz;

                    if (person->freeze <= 0)
                    {
                        if (!person->shd_mode)
                        {
                            person->spr.u = 0;
                            person->spr.v = 0;
                        }
                        else
                        {
                            person->spr.u = 0;
                            person->spr.v = 32;
                        }
                    }

                    person->anim = 0;
                    person->max_tick = 20;
                    person->dodge = FALSE;
                    person->parry = FALSE;
                }
                else if (person->parry && person->spr.u == 0)
                {
                    if (person->freeze <= 0)
                    {
                        person->spr.u = 32;
                        person->spr.v = 32;
                    }
                }
            }

            person->tick = 0;
        }
        else
        {
            if (person->anim == 3 && person->alive)
            {
                if (person->spr.MovVector.vx < person->pivot.vx)
                {
                    person->spr.MovVector.vx = person->pivot.vx + 4;
                }
                else
                {
                    person->spr.MovVector.vx = person->pivot.vx - 4;
                }

                vib_mode = 1;
            }
        }
    }
    else
    {
        person->tick += graph.delta;

        if (person->tick >= 10 && person->spr.alpha > 63)
        {
            FX *star = battle_spawnfx(btl);

            if (star)
            {
                star->type = 6;
                star->reverse = FALSE;
                fx_init(star);

                star->spr.MovVector.vx = person->spr.MovVector.vx;
                star->spr.MovVector.vy = person->spr.MovVector.vy;
                star->spr.MovVector.vz = person->spr.MovVector.vz - 1;
            }

            person->tick = 0;
        }

        if (person->spr.alpha > 63)
        {
            vib_mode = 2;
        }

        person->spr.tpage = getTPage(0, 1, 256, 0);

        if (person->spr.alpha > 0)
        {
            person->spr.alpha -= graph.delta;
        }
        else
        {
            person->spr.u = 0;
            person->spr.v = 0;
            person->anim = 0;
            person->tick = 0;
            person->max_tick = 20;
        }
    }

    if (person->plr > 0)
    {
        person->ctrl = controller_getplayer(person->plr - 1);

        if (person->ctrl.connected)
        {
            controller_vibrate(person->ctrl.porter);
            int porting;

            if (person->ctrl.porter == 0x00)
            {
                porting = 0;
            }
            else if (person->ctrl.porter == 0x01)
            {
                porting = 1;
            }
            else if (person->ctrl.porter == 0x02)
            {
                porting = 2;
            }
            else if (person->ctrl.porter == 0x03)
            {
                porting = 3;
            }
            else if (person->ctrl.porter == 0x10)
            {
                porting = 4;
            }
            else if (person->ctrl.porter == 0x11)
            {
                porting = 5;
            }
            else if (person->ctrl.porter == 0x12)
            {
                porting = 6;
            }
            else if (person->ctrl.porter == 0x13)
            {
                porting = 7;
            }

            if (vib_mode == 1)
            {
                if (control.motor[porting][0] == 0)
                {
                    control.motor[porting][0] = 1;
                    control.motor[porting][1] = 0;
                    control.vib_sync[porting] = TRUE;
                }
            }
            else if (vib_mode == 2)
            {
                if (control.motor[porting][1] == 0)
                {
                    control.motor[porting][0] = 0;
                    control.motor[porting][1] = 255;
                    control.vib_sync[porting] = TRUE;
                }
            }
            else
            {
                if (control.motor[porting][0] == 1 || control.motor[porting][1] == 255)
                {
                    control.motor[porting][0] = 0;
                    control.motor[porting][1] = 0;
                    control.vib_sync[porting] = TRUE;
                }
            }
        }
    }

    if (person->turn && person->alive)
    {
        if (!person->turn_start)
        {
            person->turn_start = TRUE;

            person->spr.MovVector.vx = person->def_loc.vx;
            person->spr.MovVector.vy = person->def_loc.vy;
            person->spr.MovVector.vz = person->def_loc.vz;

            person->pivot.vx = person->spr.MovVector.vx;
            person->pivot.vy = person->spr.MovVector.vy;
            person->pivot.vz = person->spr.MovVector.vz;

            u_char plrs = 0;

            for (u_char i = 0; i < btl->max_people; i++)
            {
                if (btl->people[i].alive)
                {
                    plrs++;
                }
            }

            if (plrs <= 1)
            {
                person->freeze = 0;
                person->regen = 0;
                person->poison = 0;
                person->shd_mana = 0;
            }

            if (person->freeze > 0)
            {
                person->freeze--;
            }

            if (person->freeze <= 0)
            {
                if (person->armor_hp > 0)
                {
                    switch (person->armor)
                    {
                    case 0:
                    {
                        break;
                    }
                    case 1:
                    {
                        person->spr.clut = getClut(256, 451); // Wooden Armor
                        break;
                    }
                    case 2:
                    {
                        person->spr.clut = getClut(256, 452); // Stone Armor
                        break;
                    }
                    case 3:
                    {
                        person->spr.clut = getClut(256, 453); // Golden Armor
                        break;
                    }
                    case 4:
                    {
                        person->spr.clut = getClut(256, 454); // Iron Armor
                        break;
                    }
                    case 5:
                    {
                        person->spr.clut = getClut(256, 455); // Diamond Armor
                        break;
                    }
                    case 6:
                    {
                        person->spr.clut = getClut(256, 456); // Emerald Armor
                        break;
                    }
                    case 7:
                    {
                        person->spr.clut = getClut(256, 457); // Redstone Armor
                        break;
                    }
                    case 8:
                    {
                        person->spr.clut = getClut(256, 458); // Ender Armor
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                }

                if (!person->shd_mode)
                {
                    person->spr.u = 0;
                    person->spr.v = 0;
                }
                else
                {
                    person->spr.u = 0;
                    person->spr.v = 32;
                }

                person->anim = 0;
                person->max_tick = 20;
                person->dodge = FALSE;
                person->parry = FALSE;
            }

            if (person->regen > 0)
            {
                person->regen--;

                if (person->hp < person->max_hp - 10)
                {
                    person->hp += 10;
                }
                else
                {
                    person->hp = person->max_hp;
                }
            }

            if (person->poison > 0)
            {
                person->poison--;

                person_damage(person, NULL, 10, FALSE);
            }

            if (person->shd_mana > 0)
            {
                person->shd_mana--;
            }
        }
    }
    else
    {
        person->turn_start = FALSE;
    }

    if (person->turn && person->anim != 3 && graph.scr_fade >= 128)
    {
        if (person->alive && person->freeze <= 0)
        {
            if (btl->menu != 3)
            {
                u_char plrs = 0;

                for (u_char i = 0; i < btl->max_people; i++)
                {
                    if (btl->people[i].alive)
                    {
                        plrs++;
                    }
                }

                if (plrs <= 1)
                {
                    person->anim = 4;
                    person->spr.u = 64;
                    person->spr.v = 32;
                    person->max_tick = 1;
                    person->tick = 0;
                    btl->menu = 5;
                }
            }

            if (person->plr > 0)
            {
                Sprite menu[5];

                menu[0].MovVector.vx = person->spr.MovVector.vx;
                menu[0].MovVector.vy = person->spr.MovVector.vy + 48;
                menu[0].MovVector.vz = person->spr.MovVector.vz - 1;
                menu[0].RotVector.vx = 0;
                menu[0].RotVector.vy = 0;
                menu[0].RotVector.vz = 0;
                menu[0].ScaleVector.vx = ONE * 2;
                menu[0].ScaleVector.vy = ONE * 2;
                menu[0].ScaleVector.vz = ONE * 2;
                menu[0].tpage = getTPage(0, 0, 320, 0);
                menu[0].clut = getClut(256, 450);
                menu[0].w = 16;
                menu[0].h = 16;
                menu[0].u = 0;
                menu[0].v = 16;
                menu[0].r = 128;
                menu[0].g = 128;
                menu[0].b = 128;
                menu[0].alpha = 128;

                menu[1].MovVector.vx = person->spr.MovVector.vx + 48;
                menu[1].MovVector.vy = person->spr.MovVector.vy;
                menu[1].MovVector.vz = person->spr.MovVector.vz - 1;
                menu[1].RotVector.vx = 0;
                menu[1].RotVector.vy = 0;
                menu[1].RotVector.vz = 0;
                menu[1].ScaleVector.vx = ONE * 2;
                menu[1].ScaleVector.vy = ONE * 2;
                menu[1].ScaleVector.vz = ONE * 2;
                menu[1].tpage = getTPage(0, 0, 320, 0);
                menu[1].clut = getClut(256, 450);
                menu[1].w = 16;
                menu[1].h = 16;
                menu[1].u = 16;
                menu[1].v = 16;
                menu[1].r = 128;
                menu[1].g = 128;
                menu[1].b = 128;
                menu[1].alpha = 128;

                menu[2].MovVector.vx = person->spr.MovVector.vx;
                menu[2].MovVector.vy = person->spr.MovVector.vy - 48;
                menu[2].MovVector.vz = person->spr.MovVector.vz - 1;
                menu[2].RotVector.vx = 0;
                menu[2].RotVector.vy = 0;
                menu[2].RotVector.vz = 0;
                menu[2].ScaleVector.vx = ONE * 2;
                menu[2].ScaleVector.vy = ONE * 2;
                menu[2].ScaleVector.vz = ONE * 2;
                menu[2].tpage = getTPage(0, 0, 320, 0);
                menu[2].clut = getClut(256, 450);
                menu[2].w = 16;
                menu[2].h = 16;
                menu[2].u = 32;
                menu[2].v = 16;
                menu[2].r = 128;
                menu[2].g = 128;
                menu[2].b = 128;
                menu[2].alpha = 128;

                menu[3].MovVector.vx = person->spr.MovVector.vx - 48;
                menu[3].MovVector.vy = person->spr.MovVector.vy;
                menu[3].MovVector.vz = person->spr.MovVector.vz - 1;
                menu[3].RotVector.vx = 0;
                menu[3].RotVector.vy = 0;
                menu[3].RotVector.vz = 0;
                menu[3].ScaleVector.vx = ONE * 2;
                menu[3].ScaleVector.vy = ONE * 2;
                menu[3].ScaleVector.vz = ONE * 2;
                menu[3].tpage = getTPage(0, 0, 320, 0);
                menu[3].clut = getClut(256, 450);
                menu[3].w = 16;
                menu[3].h = 16;
                menu[3].u = 48;
                menu[3].v = 16;
                menu[3].r = 128;
                menu[3].g = 128;
                menu[3].b = 128;
                menu[3].alpha = 128;

                menu[4].MovVector.vx = person->spr.MovVector.vx;
                menu[4].MovVector.vy = person->spr.MovVector.vy;
                menu[4].MovVector.vz = person->spr.MovVector.vz;
                menu[4].RotVector.vx = 0;
                menu[4].RotVector.vy = 0;
                menu[4].RotVector.vz = 0;
                menu[4].ScaleVector.vx = ONE * 2;
                menu[4].ScaleVector.vy = ONE * 2;
                menu[4].ScaleVector.vz = ONE * 2;
                menu[4].tpage = getTPage(0, 0, 320, 0);
                menu[4].clut = getClut(256, 450);
                menu[4].w = 16;
                menu[4].h = 16;
                menu[4].u = 64;
                menu[4].v = 16;
                menu[4].r = 128;
                menu[4].g = 128;
                menu[4].b = 128;
                menu[4].alpha = 128;

                if (person->ctrl.connected)
                {
                    if (btl->menu == 0)
                    {
                        if (!(person->ctrl.btn & PAD_SELECT))
                        {
                            if (!person->quit_pressed)
                            {
                                btl->menu = 4;
                                person->quit_pressed = TRUE;
                            }
                        }
                        else
                        {
                            person->quit_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_LEFT) || person->ctrl.ls_x <= -63)
                        {
                            if (!person->hor_pressed)
                            {
                                sound_playsfx(&sfx[1], 12, 0x0000, FALSE, 255, 255);
                                person->hor_pressed = TRUE;

                                if (person->action[0] > 0)
                                {
                                    person->action[0]--;
                                }
                                else
                                {
                                    person->action[0] = 3;
                                }
                            }
                        }
                        else if (!(person->ctrl.btn & PAD_RIGHT) || person->ctrl.ls_x >= 63)
                        {
                            if (!person->hor_pressed)
                            {
                                sound_playsfx(&sfx[1], 12, 0x0000, FALSE, 255, 255);
                                person->hor_pressed = TRUE;

                                if (person->action[0] < 3)
                                {
                                    person->action[0]++;
                                }
                                else
                                {
                                    person->action[0] = 0;
                                }
                            }
                        }
                        else
                        {
                            person->hor_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CROSS) || !(person->ctrl.btn & PAD_START))
                        {
                            if (!person->accept_pressed)
                            {
                                person->accept_pressed = TRUE;

                                switch (person->action[0])
                                {
                                case 0:
                                {
                                    sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                    btl->menu = 2;

                                    while (btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                    {
                                        if (person->action[2] < btl->max_people - 1)
                                        {
                                            person->action[2]++;
                                        }
                                        else
                                        {
                                            person->action[2] = 0;
                                        }
                                    }

                                    break;
                                }
                                case 1:
                                {
                                    if (!person->shd_mode && (person->shd_hp > 0 || person->shd == 0))
                                    {
                                        sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                        btl->menu = 3;

                                        while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                        {
                                            if (person->action[2] < btl->max_people - 1)
                                            {
                                                person->action[2]++;
                                            }
                                            else
                                            {
                                                person->action[2] = 0;
                                            }
                                        }
                                    }

                                    break;
                                }
                                case 2:
                                {
                                    for (u_char i = 0; i < 10; i++)
                                    {
                                        if ((i != 4 && person->spell[i] && person->mp >= btl->spell_cost[i] * person->spell_rank[i]) || (i == 4 && person->spell[i] && person->mp >= btl->spell_cost[i] * person->spell_rank[i] && person->shd_mode))
                                        {
                                            sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                            btl->menu = 1;

                                            while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                            {
                                                if (person->action[1] < 9)
                                                {
                                                    person->action[1]++;
                                                }
                                                else
                                                {
                                                    person->action[1] = 0;
                                                }
                                            }

                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3:
                                {
                                    for (u_char i = 0; i < 3; i++)
                                    {
                                        if (person->pot[i] > 0)
                                        {
                                            u_char cond = FALSE;

                                            if (i == 0 && person->hp != person->max_hp)
                                            {
                                                cond = TRUE;
                                            }
                                            else if (i == 1 && person->mp != person->max_mp)
                                            {
                                                cond = TRUE;
                                            }
                                            else if (i == 2 && (person->hp != person->max_hp || person->mp != person->max_mp))
                                            {
                                                cond = TRUE;
                                            }

                                            if (cond)
                                            {
                                                sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                                btl->menu = 1;

                                                while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                                {
                                                    if (person->action[1] < 2)
                                                    {
                                                        person->action[1]++;
                                                    }
                                                    else
                                                    {
                                                        person->action[1] = 0;
                                                    }
                                                }

                                                break;
                                            }
                                        }
                                    }
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                                }
                            }
                        }
                        else
                        {
                            person->accept_pressed = FALSE;
                        }
                    }
                    else if (btl->menu == 1)
                    {
                        if (!(person->ctrl.btn & PAD_UP) || person->ctrl.ls_y <= -63)
                        {
                            if (!person->ver_pressed)
                            {
                                person->ver_pressed = TRUE;
                                sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);

                                u_char max = person->action[0] == 2 ? 9 : 2;

                                if (person->action[1] > 0)
                                {
                                    person->action[1]--;

                                    if (person->action[0] == 2)
                                    {
                                        while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                        {
                                            if (person->action[1] > 0)
                                            {
                                                person->action[1]--;
                                            }
                                            else
                                            {
                                                person->action[1] = max;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                        {
                                            if (person->action[1] > 0)
                                            {
                                                person->action[1]--;
                                            }
                                            else
                                            {
                                                person->action[1] = max;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    person->action[1] = max;

                                    if (person->action[0] == 2)
                                    {
                                        while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                        {
                                            if (person->action[1] > 0)
                                            {
                                                person->action[1]--;
                                            }
                                            else
                                            {
                                                person->action[1] = max;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                        {
                                            if (person->action[1] > 0)
                                            {
                                                person->action[1]--;
                                            }
                                            else
                                            {
                                                person->action[1] = max;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else if (!(person->ctrl.btn & PAD_DOWN) || person->ctrl.ls_y >= 63)
                        {
                            if (!person->ver_pressed)
                            {
                                person->ver_pressed = TRUE;
                                sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);

                                u_char max = person->action[0] == 2 ? 9 : 2;

                                if (person->action[1] < max)
                                {
                                    person->action[1]++;

                                    if (person->action[0] == 2)
                                    {
                                        while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                        {
                                            if (person->action[1] < max)
                                            {
                                                person->action[1]++;
                                            }
                                            else
                                            {
                                                person->action[1] = 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                        {
                                            if (person->action[1] < max)
                                            {
                                                person->action[1]++;
                                            }
                                            else
                                            {
                                                person->action[1] = 0;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    person->action[1] = 0;

                                    if (person->action[0] == 2)
                                    {
                                        while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                        {
                                            if (person->action[1] < max)
                                            {
                                                person->action[1]++;
                                            }
                                            else
                                            {
                                                person->action[1] = 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                        {
                                            if (person->action[1] < max)
                                            {
                                                person->action[1]++;
                                            }
                                            else
                                            {
                                                person->action[1] = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            person->ver_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CROSS) || !(person->ctrl.btn & PAD_START))
                        {
                            if (!person->accept_pressed)
                            {
                                person->accept_pressed = TRUE;

                                if (person->action[0] == 2)
                                {
                                    if (person->action[1] == 0 || person->action[1] == 3 || person->action[1] == 5 || person->action[1] == 6 || person->action[1] == 9)
                                    {
                                        sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                        btl->menu = 2;

                                        while (btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                        {
                                            if (person->action[2] < btl->max_people - 1)
                                            {
                                                person->action[2]++;
                                            }
                                            else
                                            {
                                                person->action[2] = 0;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (person->action[1] == 4 && person->shd_mode)
                                        {
                                            sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                            btl->menu = 3;

                                            while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                            {
                                                if (person->action[2] < btl->max_people - 1)
                                                {
                                                    person->action[2]++;
                                                }
                                                else
                                                {
                                                    person->action[2] = 0;
                                                }
                                            }
                                        }
                                        else if (person->action[1] != 4)
                                        {
                                            sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                            btl->menu = 3;

                                            while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                            {
                                                if (person->action[2] < btl->max_people - 1)
                                                {
                                                    person->action[2]++;
                                                }
                                                else
                                                {
                                                    person->action[2] = 0;
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    u_char cond = FALSE;

                                    if (person->action[1] == 0 && person->hp != person->max_hp)
                                    {
                                        cond = TRUE;
                                    }
                                    else if (person->action[1] == 1 && person->mp != person->max_mp)
                                    {
                                        cond = TRUE;
                                    }
                                    else if (person->action[1] == 2 && (person->hp != person->max_hp || person->mp != person->max_mp))
                                    {
                                        cond = TRUE;
                                    }

                                    if (cond)
                                    {
                                        btl->menu = 3;
                                        sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);

                                        while (!btl->people[person->action[2]].turn && btl->people[person->action[2]].alive)
                                        {
                                            if (person->action[2] < btl->max_people - 1)
                                            {
                                                person->action[2]++;
                                            }
                                            else
                                            {
                                                person->action[2] = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            person->accept_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CIRCLE))
                        {
                            if (!person->decline_pressed)
                            {
                                person->decline_pressed = TRUE;
                                sound_playsfx(&sfx[3], 12, 0x0000, FALSE, 255, 255);
                                btl->menu = 0;
                                person->action[1] = 0;
                            }
                        }
                        else
                        {
                            person->decline_pressed = FALSE;
                        }
                    }
                    else if (btl->menu == 2)
                    {
                        if (!(person->ctrl.btn & PAD_UP) || person->ctrl.ls_y <= -63)
                        {
                            if (!person->ver_pressed)
                            {
                                person->ver_pressed = TRUE;

                                for (u_char i = 0; i < btl->max_people; i++)
                                {
                                    if (btl->people[i].alive && !btl->people[i].turn && btl->people[i].spr.MovVector.vy < btl->people[person->action[2]].spr.MovVector.vy)
                                    {
                                        person->action[2] = i;
                                        sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);
                                        break;
                                    }
                                }
                            }
                        }
                        else if (!(person->ctrl.btn & PAD_DOWN) || person->ctrl.ls_y >= 63)
                        {
                            if (!person->ver_pressed)
                            {
                                person->ver_pressed = TRUE;

                                for (u_char i = 0; i < btl->max_people; i++)
                                {
                                    if (btl->people[i].alive && !btl->people[i].turn && btl->people[i].spr.MovVector.vy > btl->people[person->action[2]].spr.MovVector.vy)
                                    {
                                        person->action[2] = i;
                                        sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            person->ver_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_LEFT) || person->ctrl.ls_x <= -63)
                        {
                            if (!person->hor_pressed)
                            {
                                person->hor_pressed = TRUE;

                                for (u_char i = 0; i < btl->max_people; i++)
                                {
                                    if (btl->people[i].alive && !btl->people[i].turn && btl->people[i].spr.MovVector.vx < btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->action[2] = i;
                                        sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);
                                        break;
                                    }
                                }
                            }
                        }
                        else if (!(person->ctrl.btn & PAD_RIGHT) || person->ctrl.ls_x >= 63)
                        {
                            if (!person->hor_pressed)
                            {
                                person->hor_pressed = TRUE;

                                for (u_char i = 0; i < btl->max_people; i++)
                                {
                                    if (btl->people[i].alive && !btl->people[i].turn && btl->people[i].spr.MovVector.vx > btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->action[2] = i;
                                        sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            person->hor_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CROSS) || !(person->ctrl.btn & PAD_START))
                        {
                            if (!person->accept_pressed)
                            {
                                person->accept_pressed = TRUE;
                                sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);
                                btl->menu = 3;
                            }
                        }
                        else
                        {
                            person->accept_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CIRCLE))
                        {
                            if (!person->decline_pressed)
                            {
                                person->decline_pressed = TRUE;
                                sound_playsfx(&sfx[3], 12, 0x0000, FALSE, 255, 255);
                                btl->menu = person->action[0] == 2 ? 1 : 0;
                                person->action[2] = 0;
                            }
                        }
                        else
                        {
                            person->decline_pressed = FALSE;
                        }
                    }
                    else if (btl->menu == 4)
                    {
                        if ((!(person->ctrl.btn & PAD_LEFT) || person->ctrl.ls_x <= -63) || (!(person->ctrl.btn & PAD_RIGHT) || person->ctrl.ls_x >= 63))
                        {
                            if (!person->hor_pressed)
                            {
                                person->hor_pressed = TRUE;
                                sound_playsfx(&sfx[0], 12, 0x0000, FALSE, 255, 255);
                                btl->b_save = !btl->b_save;
                            }
                        }
                        else
                        {
                            person->hor_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CROSS) || !(person->ctrl.btn & PAD_START))
                        {
                            if (!person->accept_pressed)
                            {
                                person->accept_pressed = TRUE;
                                sound_playsfx(&sfx[2], 12, 0x0000, FALSE, 255, 255);

                                if (btl->b_save)
                                {
                                    for (u_char i = 0; i < btl->max_people; i++)
                                    {
                                        if (btl->people[i].plr > 0)
                                        {
                                            if (btl->people[i].ctrl.connected)
                                            {
                                                DATALOAD data;
                                                data.data.lvl = btl->people[i].lvl;
                                                data.data.pot[0] = btl->people[i].pot[0];
                                                data.data.pot[1] = btl->people[i].pot[1];
                                                data.data.pot[2] = btl->people[i].pot[2];
                                                data.data.spell_rank[0] = btl->people[i].spell_rank[0];
                                                data.data.spell_rank[1] = btl->people[i].spell_rank[1];
                                                data.data.spell_rank[2] = btl->people[i].spell_rank[2];
                                                data.data.spell_rank[3] = btl->people[i].spell_rank[3];
                                                data.data.spell_rank[4] = btl->people[i].spell_rank[4];
                                                data.data.spell_rank[5] = btl->people[i].spell_rank[5];
                                                data.data.spell_rank[6] = btl->people[i].spell_rank[6];
                                                data.data.spell_rank[7] = btl->people[i].spell_rank[7];
                                                data.data.spell_rank[8] = btl->people[i].spell_rank[8];
                                                data.data.spell_rank[9] = btl->people[i].spell_rank[9];

                                                memcard_save(btl->people[i].ctrl.porter, &data, REGION_CODE, 1);
                                                graph.last_vsync = VSync(-1);
                                            }
                                        }
                                    }
                                }

                                btl->reverse = TRUE;
                                btl->menu = 0;
                            }
                        }
                        else
                        {
                            person->accept_pressed = FALSE;
                        }

                        if (!(person->ctrl.btn & PAD_CIRCLE))
                        {
                            if (!person->decline_pressed)
                            {
                                person->decline_pressed = TRUE;
                                sound_playsfx(&sfx[3], 12, 0x0000, FALSE, 255, 255);
                                btl->menu = 0;
                            }
                        }
                        else
                        {
                            person->decline_pressed = FALSE;
                        }
                    }
                }

                switch (person->action[0])
                {
                case 0:
                {
                    menu[0].u = 0;
                    menu[1].u = 16;
                    menu[2].u = 32;
                    menu[3].u = 48;
                    break;
                }
                case 1:
                {
                    menu[0].u = 16;
                    menu[1].u = 32;
                    menu[2].u = 48;
                    menu[3].u = 0;
                    break;
                }
                case 2:
                {
                    menu[0].u = 32;
                    menu[1].u = 48;
                    menu[2].u = 0;
                    menu[3].u = 16;
                    break;
                }
                case 3:
                {
                    menu[0].u = 48;
                    menu[1].u = 0;
                    menu[2].u = 16;
                    menu[3].u = 32;
                    break;
                }
                default:
                {
                    break;
                }
                }

                if (btl->menu == 1)
                {
                    TextChar opt[10][16];
                    TextChar cost[10][5];

                    u_int cost_sz[10];

                    for (u_char i = 0; i < 10; i++)
                    {
                        for (u_char j = 0; j < 16; j++)
                        {
                            graph_inittext(&opt[i][j]);
                        }
                    }

                    for (u_char i = 0; i < 10; i++)
                    {
                        for (u_char j = 0; j < 5; j++)
                        {
                            graph_inittext(&cost[i][j]);
                        }
                    }

                    if (person->action[0] == 2)
                    {
                        if (LNG == 0)
                        {
                            // u_char text[][15] = {{38, 85, 82, 84, 85, 78, 229, 0, 68, 69, 0, 70, 79, 67, 0}};
                            u_char text[][16] =
                                {
                                    {38, 85, 82, 84, 85, 78, 229, 0, 68, 69, 0, 70, 79, 67},
                                    {50, 69, 71, 69, 78, 69, 82, 65, 233, 73, 69},
                                    {226, 78, 71, 72, 69, 233, 65, 82, 69, 0, 82, 65, 80, 73, 68, 229},
                                    {38, 85, 76, 71, 69, 82},
                                    {51, 67, 85, 84, 0, 68, 69, 0, 77, 65, 78, 229},
                                    {50, 79, 73, 0, 77, 79, 82, 84, 65, 76},
                                    {37, 82, 79, 73, 83, 77},
                                    {45, 230, 78, 73, 65, 0, 83, 70, 230, 78, 84, 229},
                                    {48, 73, 65, 84, 82, 229, 0, 78, 85, 67, 76, 69, 65, 82, 229},
                                    {48, 85, 232, 67, 65, 0, 77, 79, 86}};

                            graph_settext(text[0], opt[0], 16);
                            graph_settext(text[1], opt[1], 16);
                            graph_settext(text[2], opt[2], 16);
                            graph_settext(text[3], opt[3], 16);
                            graph_settext(text[4], opt[4], 16);
                            graph_settext(text[5], opt[5], 16);
                            graph_settext(text[6], opt[6], 16);
                            graph_settext(text[7], opt[7], 16);
                            graph_settext(text[8], opt[8], 16);
                            graph_settext(text[9], opt[9], 16);
                        }
                        else
                        {
                            u_char text[][16] =
                                {
                                    {38, 73, 82, 69, 0, 51, 84, 79, 82, 77},
                                    {50, 69, 71, 69, 78, 69, 82, 65, 84, 73, 79, 78},
                                    {51, 78, 65, 80, 0, 38, 82, 69, 69, 90, 69},
                                    {44, 73, 71, 72, 84, 73, 78, 71},
                                    {45, 65, 78, 65, 0, 51, 72, 73, 69, 76, 68},
                                    {36, 69, 65, 68, 76, 89, 0, 51, 87, 65, 82, 77},
                                    {40, 69, 82, 79, 73, 83, 77},
                                    {40, 79, 76, 89, 0, 55, 82, 65, 84, 72},
                                    {50, 69, 68, 83, 84, 79, 78, 69, 0, 46, 85, 75, 69},
                                    {37, 78, 68, 69, 82, 0, 51, 76, 65, 89}};

                            graph_settext(text[0], opt[0], 16);
                            graph_settext(text[1], opt[1], 16);
                            graph_settext(text[2], opt[2], 16);
                            graph_settext(text[3], opt[3], 16);
                            graph_settext(text[4], opt[4], 16);
                            graph_settext(text[5], opt[5], 16);
                            graph_settext(text[6], opt[6], 16);
                            graph_settext(text[7], opt[7], 16);
                            graph_settext(text[8], opt[8], 16);
                            graph_settext(text[9], opt[9], 16);
                        }

                        u_char mgc[10][5] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

                        for (u_char i = 0; i < 10; i++)
                        {
                            u_int num = btl->spell_cost[i] * person->spell_rank[i];

                            if (num < 10)
                            {
                                mgc[i][0] = 16 + (num % 10);
                                mgc[i][1] = 0;
                                mgc[i][2] = 0;
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 1;
                            }
                            else if (num < 100)
                            {
                                mgc[i][0] = 16 + ((num / 10) % 10);
                                mgc[i][1] = 16 + (num % 10);
                                mgc[i][2] = 0;
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 2;
                            }
                            else if (num < 1000)
                            {
                                mgc[i][0] = 16 + ((num / 100) % 10);
                                mgc[i][1] = 16 + ((num / 10) % 10);
                                mgc[i][2] = 16 + (num % 10);
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 3;
                            }
                            else if (num < 10000)
                            {
                                mgc[i][0] = 16 + ((num / 1000) % 10);
                                mgc[i][1] = 16 + ((num / 100) % 10);
                                mgc[i][2] = 16 + ((num / 10) % 10);
                                mgc[i][3] = 16 + (num % 10);
                                mgc[i][4] = 0;
                                cost_sz[i] = 4;
                            }
                            else
                            {
                                mgc[i][0] = 16 + ((num / 10000) % 10);
                                mgc[i][1] = 16 + ((num / 1000) % 10);
                                mgc[i][2] = 16 + ((num / 100) % 10);
                                mgc[i][3] = 16 + ((num / 10) % 10);
                                mgc[i][4] = 16 + (num % 10);
                                cost_sz[i] = 5;
                            }

                            graph_settext(mgc[i], cost[i], cost_sz[i]);
                        }

                        u_char vis = 0;

                        if (person->action[1] >= 2)
                        {
                            vis = person->action[1] - 1;

                            if (vis > 7)
                            {
                                vis = 7;
                            }

                            while (vis > 0 && (!person->spell[vis + 2]))
                            {
                                vis--;
                            }
                        }

                        u_char opt1 = vis;
                        u_char opt2 = vis + 1;
                        u_char opt3 = vis + 2;

                        graph_drawtext(4, 224 - 48, person->action[1] == vis ? 128 : ((opt1 != 4 && person->spell[vis] && person->mp >= btl->spell_cost[vis] * person->spell_rank[vis]) || (opt1 == 4 && person->spell[vis] && person->mp >= btl->spell_cost[vis] * person->spell_rank[vis] && person->shd_mode) ? 63 : (person->spell[vis] ? 31 : 0)), 16, 1, opt[vis], 1);
                        graph_drawtext(4, 224 - 24, person->action[1] == vis + 1 ? 128 : ((opt2 != 4 && person->spell[vis + 1] && person->mp >= btl->spell_cost[vis + 1] * person->spell_rank[vis + 1]) || (opt2 == 4 && person->spell[vis + 1] && person->mp >= btl->spell_cost[vis + 1] * person->spell_rank[vis + 1] && person->shd_mode) ? 63 : (person->spell[vis + 1] ? 31 : 0)), 16, 1, opt[vis + 1], 1);
                        graph_drawtext(4, 224, person->action[1] == vis + 2 ? 128 : ((opt3 != 4 && person->spell[vis + 2] && person->mp >= btl->spell_cost[vis + 2] * person->spell_rank[vis + 2]) || (opt3 == 4 && person->spell[vis + 2] && person->mp >= btl->spell_cost[vis + 2] * person->spell_rank[vis + 2] && person->shd_mode) ? 63 : (person->spell[vis + 2] ? 31 : 0)), 16, 1, opt[vis + 2], 1);

                        graph_drawtext(256, 224 - 48, person->action[1] == vis ? 128 : ((opt1 != 4 && person->spell[vis] && person->mp >= btl->spell_cost[vis] * person->spell_rank[vis]) || (opt1 == 4 && person->spell[vis] && person->mp >= btl->spell_cost[vis] * person->spell_rank[vis] && person->shd_mode) ? 63 : (person->spell[vis] ? 31 : 0)), cost_sz[vis], 2, cost[vis], 1);
                        graph_drawtext(256, 224 - 24, person->action[1] == vis + 1 ? 128 : ((opt2 != 4 && person->spell[vis + 1] && person->mp >= btl->spell_cost[vis + 1] * person->spell_rank[vis + 1]) || (opt2 == 4 && person->spell[vis + 1] && person->mp >= btl->spell_cost[vis + 1] * person->spell_rank[vis + 1] && person->shd_mode) ? 63 : (person->spell[vis + 1] ? 31 : 0)), cost_sz[vis + 1], 2, cost[vis + 1], 1);
                        graph_drawtext(256, 224, person->action[1] == vis + 2 ? 128 : ((opt3 != 4 && person->spell[vis + 2] && person->mp >= btl->spell_cost[vis + 2] * person->spell_rank[vis + 2]) || (opt3 == 4 && person->spell[vis + 2] && person->mp >= btl->spell_cost[vis + 2] * person->spell_rank[vis + 2] && person->shd_mode) ? 63 : (person->spell[vis + 2] ? 31 : 0)), cost_sz[vis + 2], 2, cost[vis + 2], 1);

                        graph_drawtile(0, 224 - 64, 256, 96);
                    }
                    else
                    {
                        if (LNG == 0)
                        {
                            u_char text[][16] =
                                {
                                    {51, 229, 78, 229, 84, 65, 84, 69},
                                    {45, 65, 78, 229},
                                    {50, 69, 83, 84, 65, 66, 73, 76, 73, 82, 69}};

                            graph_settext(text[0], opt[0], 16);
                            graph_settext(text[1], opt[1], 16);
                            graph_settext(text[2], opt[2], 16);
                        }
                        else
                        {
                            u_char text[][16] =
                                {
                                    {40, 69, 65, 76, 84, 72},
                                    {45, 65, 78, 65},
                                    {50, 69, 83, 84, 79, 82, 69}};

                            graph_settext(text[0], opt[0], 16);
                            graph_settext(text[1], opt[1], 16);
                            graph_settext(text[2], opt[2], 16);
                        }

                        u_char mgc[3][5] = {{0}, {0}, {0}};

                        for (u_char i = 0; i < 3; i++)
                        {
                            u_int num = person->pot[i];

                            if (num < 10)
                            {
                                mgc[i][0] = 16 + (num % 10);
                                mgc[i][1] = 0;
                                mgc[i][2] = 0;
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 1;
                            }
                            else if (num < 100)
                            {
                                mgc[i][0] = 16 + ((num / 10) % 10);
                                mgc[i][1] = 16 + (num % 10);
                                mgc[i][2] = 0;
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 2;
                            }
                            else if (num < 1000)
                            {
                                mgc[i][0] = 16 + ((num / 100) % 10);
                                mgc[i][1] = 16 + ((num / 10) % 10);
                                mgc[i][2] = 16 + (num % 10);
                                mgc[i][3] = 0;
                                mgc[i][4] = 0;
                                cost_sz[i] = 3;
                            }
                            else if (num < 10000)
                            {
                                mgc[i][0] = 16 + ((num / 1000) % 10);
                                mgc[i][1] = 16 + ((num / 100) % 10);
                                mgc[i][2] = 16 + ((num / 10) % 10);
                                mgc[i][3] = 16 + (num % 10);
                                mgc[i][4] = 0;
                                cost_sz[i] = 4;
                            }
                            else
                            {
                                mgc[i][0] = 16 + ((num / 10000) % 10);
                                mgc[i][1] = 16 + ((num / 1000) % 10);
                                mgc[i][2] = 16 + ((num / 100) % 10);
                                mgc[i][3] = 16 + ((num / 10) % 10);
                                mgc[i][4] = 16 + (num % 10);
                                cost_sz[i] = 5;
                            }

                            graph_settext(mgc[i], cost[i], cost_sz[i]);
                        }

                        graph_drawtext(4, 224 - 48, person->action[1] == 0 ? 128 : (person->pot[0] > 0 && person->hp != person->max_hp ? 63 : (person->pot[0] > 0 ? 31 : 0)), 16, 1, opt[0], 1);
                        graph_drawtext(4, 224 - 24, person->action[1] == 1 ? 128 : (person->pot[1] > 0 && person->mp != person->max_mp ? 63 : (person->pot[1] > 0 ? 31 : 0)), 16, 1, opt[1], 1);
                        graph_drawtext(4, 224, person->action[1] == 2 ? 128 : (person->pot[2] > 0 && (person->hp != person->max_hp || person->mp != person->max_mp) ? 63 : (person->pot[2] > 0 ? 31 : 0)), 16, 1, opt[2], 1);

                        graph_drawtext(256, 224 - 48, person->action[1] == 0 ? 128 : (person->pot[0] > 0 && person->hp != person->max_hp ? 63 : (person->pot[0] > 0 ? 31 : 0)), cost_sz[0], 2, cost[0], 1);
                        graph_drawtext(256, 224 - 24, person->action[1] == 1 ? 128 : (person->pot[1] > 0 && person->mp != person->max_mp ? 63 : (person->pot[1] > 0 ? 31 : 0)), cost_sz[1], 2, cost[1], 1);
                        graph_drawtext(256, 224, person->action[1] == 2 ? 128 : (person->pot[2] > 0 && (person->hp != person->max_hp || person->mp != person->max_mp) ? 63 : (person->pot[2] > 0 ? 31 : 0)), cost_sz[2], 2, cost[2], 1);

                        graph_drawtile(0, 224 - 64, 256, 96);
                    }
                }

                if (btl->menu == 4)
                {
                    if (LNG == 0)
                    {
                        TextChar lodm1[15], lodm2[16], lod1[2], lod2[2];

                        for (u_char i = 0; i < 15; i++)
                        {
                            graph_inittext(&lodm1[i]);
                        }

                        for (u_char i = 0; i < 19; i++)
                        {
                            graph_inittext(&lodm2[i]);
                        }

                        for (u_char i = 0; i < 2; i++)
                        {
                            graph_inittext(&lod1[i]);
                        }

                        for (u_char i = 0; i < 2; i++)
                        {
                            graph_inittext(&lod2[i]);
                        }

                        u_char lodmt[] = {54, 82, 69, 73, 0, 83, 229, 0, 83, 65, 76, 86, 69, 90, 73};

                        graph_settext(lodmt, lodm1, 15);

                        u_char lodmt2[] = {231, 78, 0, 45, 69, 77, 79, 82, 73, 73, 0, 35, 65, 82, 68, 31};

                        graph_settext(lodmt2, lodm2, 16);

                        u_char lodt1[] = {36, 65};

                        graph_settext(lodt1, lod1, 2);

                        u_char lodt2[] = {46, 85};

                        graph_settext(lodt2, lod2, 2);

                        graph_drawtext(128, 128 - 28, 128, 15, 0, lodm1, 1);
                        graph_drawtext(128, 128 - 16, 128, 16, 0, lodm2, 1);
                        graph_drawtext(64, 128 + 16, btl->b_save ? 128 : 63, 2, 0, lod1, 1);
                        graph_drawtext(192, 128 + 16, !btl->b_save ? 128 : 63, 2, 0, lod2, 1);

                        graph_drawtile(0, graph.ResH / 4, graph.ResW, graph.ResH / 2);
                    }
                    else if (LNG == 1)
                    {
                        TextChar lodm1[19], lodm2[15], lod1[3], lod2[2];

                        for (u_char i = 0; i < 19; i++)
                        {
                            graph_inittext(&lodm1[i]);
                        }

                        for (u_char i = 0; i < 17; i++)
                        {
                            graph_inittext(&lodm2[i]);
                        }

                        for (u_char i = 0; i < 3; i++)
                        {
                            graph_inittext(&lod1[i]);
                        }

                        for (u_char i = 0; i < 2; i++)
                        {
                            graph_inittext(&lod2[i]);
                        }

                        u_char lodmt[] = {36, 79, 0, 89, 79, 85, 0, 87, 65, 78, 84, 0, 84, 79, 0, 83, 65, 86, 69};

                        graph_settext(lodmt, lodm1, 19);

                        u_char lodmt2[] = {84, 79, 0, 45, 69, 77, 79, 82, 89, 0, 35, 65, 82, 68, 31};

                        graph_settext(lodmt2, lodm2, 15);

                        u_char lodt1[] = {57, 69, 83};

                        graph_settext(lodt1, lod1, 3);

                        u_char lodt2[] = {46, 79};

                        graph_settext(lodt2, lod2, 2);

                        graph_drawtext(128, 128 - 28, 128, 19, 0, lodm1, 1);
                        graph_drawtext(128, 128 - 16, 128, 15, 0, lodm2, 1);
                        graph_drawtext(64, 128 + 16, btl->b_save ? 128 : 63, 3, 0, lod1, 1);
                        graph_drawtext(192, 128 + 16, !btl->b_save ? 128 : 63, 2, 0, lod2, 1);

                        graph_drawtile(0, graph.ResH / 4, graph.ResW, graph.ResH / 2);
                    }
                }

                if (btl->menu == 2)
                {
                    menu[4].MovVector.vx = btl->people[person->action[2]].spr.MovVector.vx;
                    menu[4].MovVector.vy = btl->people[person->action[2]].spr.MovVector.vy - 48;

                    graph_drawsprite(menu[4], -1);
                }

                if (btl->menu < 3)
                {
                    graph_drawsprite(menu[0], -1);

                    if (btl->menu < 1)
                    {
                        graph_drawsprite(menu[1], -1);
                        graph_drawsprite(menu[2], -1);
                        graph_drawsprite(menu[3], -1);
                    }
                }
            }
            else
            {
                if (btl->menu == 0)
                {
                    person->action[0] = (u_char)(rand() % 4);

                    u_char conder = TRUE;

                    while (conder)
                    {
                        switch (person->action[0])
                        {
                        case 0:
                        {
                            btl->menu = 2;
                            conder = FALSE;

                            while (btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                            {
                                if (person->action[2] < btl->max_people - 1)
                                {
                                    person->action[2]++;
                                }
                                else
                                {
                                    person->action[2] = 0;
                                }
                            }

                            break;
                        }
                        case 1:
                        {
                            if (!person->shd_mode && (person->shd_hp > 0 || person->shd == 0))
                            {
                                btl->menu = 3;
                                conder = FALSE;

                                while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                {
                                    if (person->action[2] < btl->max_people - 1)
                                    {
                                        person->action[2]++;
                                    }
                                    else
                                    {
                                        person->action[2] = 0;
                                    }
                                }
                            }

                            break;
                        }
                        case 2:
                        {
                            for (u_char i = 0; i < 10; i++)
                            {
                                if ((i != 4 && person->spell[i] && person->mp >= btl->spell_cost[i] * person->spell_rank[i]) || (i == 4 && person->spell[i] && person->mp >= btl->spell_cost[i] * person->spell_rank[i] && person->shd_mode))
                                {
                                    btl->menu = 1;
                                    conder = FALSE;

                                    while (!person->spell[person->action[1]] || person->mp < btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]] || (person->action[1] == 4 && !person->shd_mode))
                                    {
                                        if (person->action[1] < 9)
                                        {
                                            person->action[1]++;
                                        }
                                        else
                                        {
                                            person->action[1] = 0;
                                        }
                                    }

                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            for (u_char i = 0; i < 3; i++)
                            {
                                if (person->pot[i] > 0)
                                {
                                    u_char cond = FALSE;

                                    if (i == 0 && person->hp != person->max_hp)
                                    {
                                        cond = TRUE;
                                    }
                                    else if (i == 1 && person->mp != person->max_mp)
                                    {
                                        cond = TRUE;
                                    }
                                    else if (i == 2 && (person->hp != person->max_hp || person->mp != person->max_mp))
                                    {
                                        cond = TRUE;
                                    }

                                    if (cond)
                                    {
                                        btl->menu = 1;
                                        conder = FALSE;

                                        while (person->pot[person->action[1]] <= 0 || ((person->action[1] == 0 && person->hp == person->max_hp) || (person->action[1] == 1 && person->mp == person->max_mp) || (person->action[1] == 2 && person->hp == person->max_hp && person->mp == person->max_mp)))
                                        {
                                            if (person->action[1] < 2)
                                            {
                                                person->action[1]++;
                                            }
                                            else
                                            {
                                                person->action[1] = 0;
                                            }
                                        }

                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }

                        if (conder)
                        {
                            person->action[0] = (u_char)(rand() % 4);
                        }
                    }
                }
                else if (btl->menu == 1)
                {
                    u_char max = person->action[0] == 2 ? 10 : 3;

                    person->action[1] = (u_char)(rand() % max);

                    u_char conder = TRUE;

                    while (conder)
                    {
                        if (person->action[0] == 2)
                        {
                            if (person->spell[person->action[1]] && person->mp >= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]])
                            {
                                if (person->action[1] == 0 || person->action[1] == 3 || person->action[1] == 5 || person->action[1] == 6 || person->action[1] == 9)
                                {
                                    btl->menu = 2;
                                    conder = FALSE;

                                    while (btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                    {
                                        if (person->action[2] < btl->max_people - 1)
                                        {
                                            person->action[2]++;
                                        }
                                        else
                                        {
                                            person->action[2] = 0;
                                        }
                                    }
                                }
                                else
                                {
                                    if (person->action[1] == 4 && person->shd_mode)
                                    {
                                        btl->menu = 3;
                                        conder = FALSE;

                                        while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                        {
                                            if (person->action[2] < btl->max_people - 1)
                                            {
                                                person->action[2]++;
                                            }
                                            else
                                            {
                                                person->action[2] = 0;
                                            }
                                        }
                                    }
                                    else if (person->action[1] != 4)
                                    {
                                        btl->menu = 3;
                                        conder = FALSE;

                                        while (!btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                                        {
                                            if (person->action[2] < btl->max_people - 1)
                                            {
                                                person->action[2]++;
                                            }
                                            else
                                            {
                                                person->action[2] = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (person->pot[person->action[1]] > 0)
                            {
                                u_char cond = FALSE;

                                if (person->action[1] == 0 && person->hp != person->max_hp)
                                {
                                    cond = TRUE;
                                }
                                else if (person->action[1] == 1 && person->mp != person->max_mp)
                                {
                                    cond = TRUE;
                                }
                                else if (person->action[1] == 2 && (person->hp != person->max_hp || person->mp != person->max_mp))
                                {
                                    cond = TRUE;
                                }

                                if (cond)
                                {
                                    btl->menu = 3;
                                    conder = FALSE;

                                    while (!btl->people[person->action[2]].turn && btl->people[person->action[2]].alive)
                                    {
                                        if (person->action[2] < btl->max_people - 1)
                                        {
                                            person->action[2]++;
                                        }
                                        else
                                        {
                                            person->action[2] = 0;
                                        }
                                    }
                                }
                            }
                        }

                        if (conder)
                        {
                            person->action[1] = (u_char)(rand() % max);
                        }
                    }
                }
                else if (btl->menu == 2)
                {
                    person->action[2] = (u_char)(rand() % btl->max_people);

                    while (btl->people[person->action[2]].turn || !btl->people[person->action[2]].alive)
                    {
                        person->action[2] = (u_char)(rand() % btl->max_people);
                    }

                    btl->menu = 3;
                }
            }

            if (btl->menu == 3)
            {
                if (person->action[0] == 0)
                {
                    if (person->act == 0)
                    {
                        person->target.vx = btl->people[person->action[2]].def_loc.vx;
                        person->target.vy = btl->people[person->action[2]].def_loc.vy;
                        person->target.vz = btl->people[person->action[2]].def_loc.vz;

                        if (person->spr.MovVector.vx > person->target.vx)
                        {
                            person->spr.ScaleVector.vx = -(ONE * 2);
                        }
                        else
                        {
                            person->spr.ScaleVector.vx = ONE * 2;
                        }

                        if (person->anim != 1)
                        {
                            person->spr.u = 64;
                            person->spr.v = 0;
                            person->max_tick = 10;
                            person->tick = 0;
                            person->anim = 1;
                        }

                        VECTOR dir;

                        dir.vx = person->target.vx - person->spr.MovVector.vx;
                        dir.vy = person->target.vy - person->spr.MovVector.vy;

                        short rot = -ratan2(dir.vy, dir.vx) + (-1024);

                        long dis = SquareRoot0(
                            (dir.vx * dir.vx) +
                            (dir.vy * dir.vy));

                        VECTOR forward;

                        forward.vx = csin(rot);
                        forward.vy = ccos(rot);

                        person->spr.MovVector.vx -= ((forward.vx * 4) * graph.delta) >> 12;
                        person->spr.MovVector.vy -= ((forward.vy * 4) * graph.delta) >> 12;

                        if (dis < 32)
                        {
                            person->act = 1;
                        }
                    }
                    else if (person->act == 1)
                    {
                        if (person->act_tick < fps / 2)
                        {
                            if (person->anim != 2)
                            {
                                person->spr.u = 64;
                                person->spr.v = 0;
                                person->max_tick = 10;
                                person->tick = 0;
                                person->anim = 2;
                            }

                            person->act_tick += graph.delta;
                        }
                        else
                        {
                            person->act_tick = 0;
                            person->act = 2;
                        }
                    }
                    else if (person->act == 2)
                    {
                        if (person->act_tick < (fps * 2) + (fps / 2))
                        {
                            person->target.vx = person->def_loc.vx;
                            person->target.vy = person->def_loc.vy;
                            person->target.vz = person->def_loc.vz;

                            if (person->spr.MovVector.vx > person->target.vx)
                            {
                                person->spr.ScaleVector.vx = -(ONE * 2);
                            }
                            else
                            {
                                person->spr.ScaleVector.vx = ONE * 2;
                            }

                            VECTOR dir;

                            dir.vx = person->target.vx - person->spr.MovVector.vx;
                            dir.vy = person->target.vy - person->spr.MovVector.vy;

                            short rot = -ratan2(dir.vy, dir.vx) + (-1024);

                            long dis = SquareRoot0(
                                (dir.vx * dir.vx) +
                                (dir.vy * dir.vy));

                            VECTOR forward;

                            forward.vx = csin(rot);
                            forward.vy = ccos(rot);

                            person->spr.MovVector.vx -= ((forward.vx * 4) * graph.delta) >> 12;
                            person->spr.MovVector.vy -= ((forward.vy * 4) * graph.delta) >> 12;

                            if (dis < 2)
                            {
                                person->spr.MovVector.vx = person->def_loc.vx;
                                person->spr.MovVector.vy = person->def_loc.vy;
                                person->spr.MovVector.vz = person->def_loc.vz;

                                person->pivot.vx = person->spr.MovVector.vx;
                                person->pivot.vy = person->spr.MovVector.vy;
                                person->pivot.vz = person->spr.MovVector.vz;

                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }
                            }
                            else
                            {
                                if (person->anim != 1)
                                {
                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 10;
                                    person->tick = 0;
                                    person->anim = 1;
                                }
                            }

                            person->act_tick += graph.delta;
                        }
                        else
                        {
                            person->act = 0;
                            person->act_tick = 0;
                            person->action[0] = 0;
                            person->action[1] = 0;
                            person->action[2] = 0;

                            btl->menu = 0;

                            if (btl->turn < btl->max_people - 1)
                            {
                                btl->turn++;
                            }
                            else
                            {
                                btl->turn = 0;
                            }

                            person->turn = FALSE;
                        }
                    }
                }
                else if (person->action[0] == 1)
                {
                    if (person->act_tick < fps * 2)
                    {
                        person->act_tick += graph.delta;

                        if (!person->shd_mode)
                        {
                            person->shd_mode = TRUE;
                            person->tick = person->max_tick;
                            sound_playsfx(&sfx[5], 13, 0x0000, FALSE, 255, 255);
                        }
                    }
                    else
                    {
                        person->act = 0;
                        person->act_tick = 0;
                        person->action[0] = 0;
                        person->action[1] = 0;
                        person->action[2] = 0;

                        btl->menu = 0;

                        if (btl->turn < btl->max_people - 1)
                        {
                            btl->turn++;
                        }
                        else
                        {
                            btl->turn = 0;
                        }

                        person->turn = FALSE;
                    }
                }
                else if (person->action[0] == 2)
                {
                    if (person->action[1] == 0)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    if (person->spr.MovVector.vx <= btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->spr.ScaleVector.vx = ONE * 2;
                                    }
                                    else
                                    {
                                        person->spr.ScaleVector.vx = -(ONE * 2);
                                    }

                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 1;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[8], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0 && person->act_count < person->spell_rank[person->action[1]])
                                {
                                    person->spr.u = 160;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 0;
                                        fx_init(obj);

                                        obj->owner = person;

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        obj->target = &btl->people[person->action[2]];

                                        sound_playsfx(&sfx[9], 15, 0x0000, FALSE, 255, 255);

                                        fire = obj;
                                    }

                                    person->act_count++;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;

                                if (person->act_count >= person->spell_rank[person->action[1]] && !fire)
                                {
                                    person->act = 2;
                                    person->act_count = 0;
                                }
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 1)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 4;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[11], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 224;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 4;
                                        obj->reverse = FALSE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[12], 15, 0x0000, FALSE, 255, 255);
                                    }

                                    person->regen = 5 * person->spell_rank[person->action[1]];
                                    person->poison = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 2)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 5;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[13], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 224;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    for (u_char i = 0; i < btl->max_people; i++)
                                    {
                                        if (btl->people[i].alive)
                                        {
                                            FX *obj = battle_spawnfx(btl);

                                            if (obj)
                                            {
                                                obj->type = 5;
                                                obj->reverse = FALSE;
                                                fx_init(obj);

                                                obj->spr.MovVector.vx = btl->people[i].spr.MovVector.vx;
                                                obj->spr.MovVector.vy = btl->people[i].spr.MovVector.vy;
                                                obj->spr.MovVector.vz = btl->people[i].spr.MovVector.vz - 1;

                                                sound_playsfx(&sfx[14], 15, 0x0000, FALSE, 255, 255);
                                            }
                                        }

                                        if (!btl->people[i].turn && btl->people[i].alive)
                                        {
                                            btl->people[i].freeze = 5 * person->spell_rank[person->action[1]];
                                        }
                                    }
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 3)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    if (person->spr.MovVector.vx <= btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->spr.ScaleVector.vx = ONE * 2;
                                    }
                                    else
                                    {
                                        person->spr.ScaleVector.vx = -(ONE * 2);
                                    }

                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 6;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[15], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 160;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 2;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = btl->people[person->action[2]].spr.MovVector.vx - 32 * ((rand() % 3) - 1);
                                        obj->spr.MovVector.vy = btl->people[person->action[2]].spr.MovVector.vy - 96;
                                        obj->spr.MovVector.vz = btl->people[person->action[2]].spr.MovVector.vz - 1;

                                        obj->target = &btl->people[person->action[2]];

                                        sound_playsfx(&sfx[16], 15, 0x0000, FALSE, 255, 255);
                                    }

                                    person_damage(&btl->people[person->action[2]], person, 50, FALSE);

                                    person->act_count++;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;

                                if (person->act_count >= person->spell_rank[person->action[1]])
                                {
                                    person->act = 2;
                                    person->act_count = 0;
                                }
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 4)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 7;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[17], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 224;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 7;
                                        obj->reverse = FALSE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[18], 15, 0x0000, FALSE, 255, 255);
                                    }

                                    person->shd_mana = 5 * person->spell_rank[person->action[1]];
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 5)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    if (person->spr.MovVector.vx <= btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->spr.ScaleVector.vx = ONE * 2;
                                    }
                                    else
                                    {
                                        person->spr.ScaleVector.vx = -(ONE * 2);
                                    }

                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 8;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[19], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 160;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 8;
                                        obj->reverse = FALSE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;
                                    }

                                    FX *obj2 = battle_spawnfx(btl);

                                    if (obj2)
                                    {
                                        obj2->type = 8;
                                        obj2->reverse = FALSE;
                                        fx_init(obj2);

                                        obj2->spr.MovVector.vx = btl->people[person->action[2]].spr.MovVector.vx;
                                        obj2->spr.MovVector.vy = btl->people[person->action[2]].spr.MovVector.vy;
                                        obj2->spr.MovVector.vz = btl->people[person->action[2]].spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[20], 15, 0x0000, FALSE, 255, 255);
                                    }

                                    btl->people[person->action[2]].poison = 5 * person->spell_rank[person->action[1]];
                                    btl->people[person->action[2]].regen = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 6)
                    {
                        if (person->act > 0 && person->act < 3)
                        {
                            Sprite buzz_spr;

                            buzz_spr.MovVector.vx = person->spr.MovVector.vx;
                            buzz_spr.MovVector.vy = person->spr.MovVector.vy;
                            buzz_spr.MovVector.vz = person->spr.MovVector.vz - 1;

                            buzz_spr.RotVector.vx = 0;
                            buzz_spr.RotVector.vy = 0;
                            buzz_spr.RotVector.vz = 0;

                            buzz_spr.ScaleVector.vx = ONE * 2;
                            buzz_spr.ScaleVector.vy = ONE * 2;
                            buzz_spr.ScaleVector.vz = ONE * 2;

                            buzz_spr.tpage = getTPage(0, 0, 320, 0);
                            buzz_spr.clut = getClut(256, 449);

                            buzz_spr.w = 16;
                            buzz_spr.h = 16;
                            buzz_spr.u = 96;
                            buzz_spr.v = 0;

                            buzz_spr.r = 255;
                            buzz_spr.g = 0;
                            buzz_spr.b = 255;
                            buzz_spr.alpha = 128;

                            graph_drawsprite(buzz_spr, -1);
                        }

                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    if (person->spr.MovVector.vx <= btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->spr.ScaleVector.vx = ONE * 2;
                                    }
                                    else
                                    {
                                        person->spr.ScaleVector.vx = -(ONE * 2);
                                    }

                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 9;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[21], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        if (person->act == 1)
                        {
                            if (person->act_tick == 0)
                            {
                                FX *obj = battle_spawnfx(btl);

                                if (obj)
                                {
                                    obj->type = 9;
                                    obj->reverse = FALSE;
                                    fx_init(obj);

                                    obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                    obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                    obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                    sound_playsfx(&sfx[22], 15, 0x0000, FALSE, 255, 255);
                                }

                                person->act_tick += graph.delta;
                            }

                            person->target.vx = btl->people[person->action[2]].def_loc.vx;
                            person->target.vy = btl->people[person->action[2]].def_loc.vy;
                            person->target.vz = btl->people[person->action[2]].def_loc.vz;

                            if (person->spr.MovVector.vx > person->target.vx)
                            {
                                person->spr.ScaleVector.vx = -(ONE * 2);
                            }
                            else
                            {
                                person->spr.ScaleVector.vx = ONE * 2;
                            }

                            if (person->anim != 1)
                            {
                                person->spr.u = 64;
                                person->spr.v = 0;
                                person->max_tick = 2;
                                person->tick = 0;
                                person->anim = 1;
                            }

                            VECTOR dir;

                            dir.vx = person->target.vx - person->spr.MovVector.vx;
                            dir.vy = person->target.vy - person->spr.MovVector.vy;

                            short rot = -ratan2(dir.vy, dir.vx) + (-1024);

                            long dis = SquareRoot0(
                                (dir.vx * dir.vx) +
                                (dir.vy * dir.vy));

                            VECTOR forward;

                            forward.vx = csin(rot);
                            forward.vy = ccos(rot);

                            person->spr.MovVector.vx -= ((forward.vx * 8) * graph.delta) >> 12;
                            person->spr.MovVector.vy -= ((forward.vy * 8) * graph.delta) >> 12;

                            if (dis < 32)
                            {
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 2;

                                    person->act_count++;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;

                                if (person->act_count >= 5 * person->spell_rank[person->action[1]])
                                {
                                    person->act_count = 0;
                                    person->act = 3;
                                }
                            }
                        }
                        else if (person->act == 3)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                person->target.vx = person->def_loc.vx;
                                person->target.vy = person->def_loc.vy;
                                person->target.vz = person->def_loc.vz;

                                if (person->spr.MovVector.vx > person->target.vx)
                                {
                                    person->spr.ScaleVector.vx = -(ONE * 2);
                                }
                                else
                                {
                                    person->spr.ScaleVector.vx = ONE * 2;
                                }

                                VECTOR dir;

                                dir.vx = person->target.vx - person->spr.MovVector.vx;
                                dir.vy = person->target.vy - person->spr.MovVector.vy;

                                short rot = -ratan2(dir.vy, dir.vx) + (-1024);

                                long dis = SquareRoot0(
                                    (dir.vx * dir.vx) +
                                    (dir.vy * dir.vy));

                                VECTOR forward;

                                forward.vx = csin(rot);
                                forward.vy = ccos(rot);

                                person->spr.MovVector.vx -= ((forward.vx * 4) * graph.delta) >> 12;
                                person->spr.MovVector.vy -= ((forward.vy * 4) * graph.delta) >> 12;

                                if (dis < 2)
                                {
                                    person->spr.MovVector.vx = person->def_loc.vx;
                                    person->spr.MovVector.vy = person->def_loc.vy;
                                    person->spr.MovVector.vz = person->def_loc.vz;

                                    person->pivot.vx = person->spr.MovVector.vx;
                                    person->pivot.vy = person->spr.MovVector.vy;
                                    person->pivot.vz = person->spr.MovVector.vz;

                                    if (person->anim != 0)
                                    {
                                        person->spr.u = 0;
                                        person->spr.v = person->shd_mode ? 32 : 0;
                                        person->max_tick = 20;
                                        person->tick = 0;
                                        person->anim = 0;
                                    }
                                }
                                else
                                {
                                    if (person->anim != 1)
                                    {
                                        person->spr.u = 64;
                                        person->spr.v = 0;
                                        person->max_tick = 10;
                                        person->tick = 0;
                                        person->anim = 1;
                                    }
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 7)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps * 2)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 6;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[23], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 224;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    for (u_char i = 0; i < btl->max_people; i++)
                                    {
                                        if (btl->people[i].alive)
                                        {
                                            FX *obj = battle_spawnfx(btl);

                                            if (obj)
                                            {
                                                obj->type = 6;
                                                obj->reverse = FALSE;
                                                fx_init(obj);

                                                obj->spr.MovVector.vx = btl->people[i].spr.MovVector.vx;
                                                obj->spr.MovVector.vy = btl->people[i].spr.MovVector.vy;
                                                obj->spr.MovVector.vz = btl->people[i].spr.MovVector.vz - 1;

                                                sound_playsfx(&sfx[24], 15, 0x0000, FALSE, 255, 255);
                                            }
                                        }

                                        if (!btl->people[i].turn && btl->people[i].alive)
                                        {
                                            person_damage(&btl->people[i], person, 500 * person->spell_rank[person->action[1]], FALSE);
                                        }
                                    }
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 8)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 192;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 4;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[25], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0)
                                {
                                    person->spr.u = 224;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    for (u_char i = 0; i < btl->max_people; i++)
                                    {
                                        if (btl->people[i].alive)
                                        {
                                            FX *obj = battle_spawnfx(btl);

                                            if (obj)
                                            {
                                                obj->type = 4;
                                                obj->reverse = FALSE;
                                                fx_init(obj);

                                                obj->spr.MovVector.vx = btl->people[i].spr.MovVector.vx;
                                                obj->spr.MovVector.vy = btl->people[i].spr.MovVector.vy;
                                                obj->spr.MovVector.vz = btl->people[i].spr.MovVector.vz - 1;

                                                sound_playsfx(&sfx[26], 15, 0x0000, FALSE, 255, 255);
                                            }
                                        }

                                        if (!btl->people[i].turn && btl->people[i].alive)
                                        {
                                            person_damage(&btl->people[i], person, 1250 * person->spell_rank[person->action[1]], FALSE);
                                        }
                                    }
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;
                                person->act = 2;
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                    else if (person->action[1] == 9)
                    {
                        if (person->act == 0)
                        {
                            if (person->act_tick < fps + (fps / 2))
                            {
                                if (person->act_tick == 0)
                                {
                                    if (person->spr.MovVector.vx <= btl->people[person->action[2]].spr.MovVector.vx)
                                    {
                                        person->spr.ScaleVector.vx = ONE * 2;
                                    }
                                    else
                                    {
                                        person->spr.ScaleVector.vx = -(ONE * 2);
                                    }

                                    person->spr.u = 64;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 10;
                                        obj->reverse = TRUE;
                                        fx_init(obj);

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        sound_playsfx(&sfx[27], 14, 0x0000, FALSE, 255, 255);
                                    }

                                    person->mp -= btl->spell_cost[person->action[1]] * person->spell_rank[person->action[1]];
                                    person->spell_used[person->action[1]] = TRUE;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act++;
                                person->act_tick = 0;
                            }
                        }
                        else if (person->act == 1)
                        {
                            if (person->act_tick < fps / 5)
                            {
                                if (person->act_tick == 0 && person->act_count <= 0)
                                {
                                    person->spr.u = 160;
                                    person->spr.v = 0;
                                    person->max_tick = 1;
                                    person->tick = 0;
                                    person->anim = 4;

                                    FX *obj = battle_spawnfx(btl);

                                    if (obj)
                                    {
                                        obj->type = 3;
                                        fx_init(obj);

                                        obj->owner = person;

                                        obj->spr.MovVector.vx = person->spr.MovVector.vx;
                                        obj->spr.MovVector.vy = person->spr.MovVector.vy;
                                        obj->spr.MovVector.vz = person->spr.MovVector.vz - 1;

                                        obj->target = &btl->people[person->action[2]];

                                        sound_playsfx(&sfx[28], 15, 0x0000, FALSE, 255, 255);

                                        fire = obj;
                                    }

                                    person->act_count++;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act_tick = 0;

                                if (!fire)
                                {
                                    person->act_count = 0;
                                    person->act = 2;
                                }
                            }
                        }
                        else if (person->act == 2)
                        {
                            if (person->act_tick < (fps * 2) + (fps / 2))
                            {
                                if (person->anim != 0)
                                {
                                    person->spr.u = 0;
                                    person->spr.v = person->shd_mode ? 32 : 0;
                                    person->max_tick = 20;
                                    person->tick = 0;
                                    person->anim = 0;
                                }

                                person->act_tick += graph.delta;
                            }
                            else
                            {
                                person->act = 0;
                                person->act_tick = 0;

                                person->action[0] = 0;
                                person->action[1] = 0;
                                person->action[2] = 0;

                                btl->menu = 0;

                                if (btl->turn < btl->max_people - 1)
                                {
                                    btl->turn++;
                                }
                                else
                                {
                                    btl->turn = 0;
                                }

                                person->turn = FALSE;
                            }
                        }
                    }
                }
                else if (person->action[0] == 3)
                {
                    if (person->act_tick < fps * 2)
                    {
                        person->act_tick += graph.delta;

                        if (person->action[1] == 0 && person->hp != person->max_hp)
                        {
                            person->hp = person->max_hp;

                            person->pot[person->action[1]]--;
                            sound_playsfx(&sfx[7], 13, 0x0000, FALSE, 255, 255);
                        }
                        else if (person->action[1] == 1 && person->mp != person->max_mp)
                        {
                            person->mp = person->max_mp;

                            person->pot[person->action[1]]--;
                            sound_playsfx(&sfx[7], 13, 0x0000, FALSE, 255, 255);
                        }
                        else if (person->action[1] == 2 && (person->hp != person->max_hp || person->mp != person->max_mp))
                        {
                            person->hp = person->max_hp;
                            person->mp = person->max_mp;

                            person->pot[person->action[1]]--;
                            sound_playsfx(&sfx[7], 13, 0x0000, FALSE, 255, 255);
                        }
                    }
                    else
                    {
                        person->act = 0;
                        person->act_tick = 0;
                        person->action[0] = 0;
                        person->action[1] = 0;
                        person->action[2] = 0;

                        btl->menu = 0;

                        if (btl->turn < btl->max_people - 1)
                        {
                            btl->turn++;
                        }
                        else
                        {
                            btl->turn = 0;
                        }

                        person->turn = FALSE;
                    }
                }
            }
            else if (btl->menu == 5)
            {
                if (person->act_tick < (fps * 5))
                {
                    if (person->act_tick == 0)
                    {
                        if (person->lvl < 1000)
                        {
                            person->lvl++;
                        }

                        for (u_char i = 0; i < 10; i++)
                        {
                            if (person->spell[i] && person->spell_used[i] && person->spell_rank[i] < 5)
                            {
                                person->spell_rank[i]++;
                                person->spell_used[i] = FALSE;
                            }
                        }
                    }

                    person->act_tick += graph.delta;
                }
                else
                {
                    btl->retry = TRUE;
                    btl->reverse = TRUE;
                }
            }
        }
        else
        {
            btl->menu = 0;

            if (btl->turn < btl->max_people - 1)
            {
                btl->turn++;
            }
            else
            {
                btl->turn = 0;
            }

            person->turn = FALSE;
        }
    }
    else if (person->anim != 3 && graph.scr_fade >= 128)
    {
        if (person->alive && person->freeze <= 0)
        {
            if (person->plr > 0)
            {
                if (person->ctrl.connected)
                {
                    if (!(person->ctrl.btn & PAD_CROSS))
                    {
                        if (!person->accept_pressed && !person->dodge)
                        {
                            if (person->anim != 5)
                            {
                                person->anim = 5;
                                person->max_tick = 10;
                                person->tick = 0;

                                if (person->spr.ScaleVector.vx < 0)
                                {
                                    person->spr.MovVector.vx = person->def_loc.vx + 32;
                                }
                                else
                                {
                                    person->spr.MovVector.vx = person->def_loc.vx - 32;
                                }
                                person->spr.MovVector.vy = person->def_loc.vy + 32;
                                person->dodge = TRUE;
                                person->accept_pressed = TRUE;
                            }
                        }
                    }
                    else
                    {
                        person->accept_pressed = FALSE;
                    }

                    if (!(person->ctrl.btn & PAD_CIRCLE))
                    {
                        if (!person->decline_pressed && !person->parry)
                        {
                            if (person->anim != 5)
                            {
                                person->anim = 5;
                                person->tick = 0;
                                person->max_tick = 5;
                                person->spr.u = 0;
                                person->spr.v = 32;
                                person->parry = TRUE;
                                person->decline_pressed = TRUE;
                            }
                        }
                    }
                    else
                    {
                        person->decline_pressed = FALSE;
                    }
                }
            }
        }
    }

    if (person->alive)
    {
        TextChar stat[3][10];

        for (u_char i = 0; i < 3; i++)
        {
            for (u_char j = 0; j < 10; j++)
            {
                graph_inittext(&stat[i][j]);
                stat[i][j].r = i == 0 || i == 2 ? 128 : 0;
                stat[i][j].g = i == 2 ? 128 : 0;
                stat[i][j].b = i == 1 || i == 2 ? 128 : 0;
            }
        }

        if (person->shd_mode && person->shd > 0 && person->shd_hp > 0)
        {
            u_char hpt[10] = {51, 40, 26, 0, 16};

            u_int num = person->shd_hp;

            if (num < 10)
            {
                hpt[4] = 16 + (num % 10);
                hpt[5] = 0;
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 100)
            {
                hpt[4] = 16 + ((num / 10) % 10);
                hpt[5] = 16 + (num % 10);
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 1000)
            {
                hpt[4] = 16 + ((num / 100) % 10);
                hpt[5] = 16 + ((num / 10) % 10);
                hpt[6] = 16 + (num % 10);
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 10000)
            {
                hpt[4] = 16 + ((num / 1000) % 10);
                hpt[5] = 16 + ((num / 100) % 10);
                hpt[6] = 16 + ((num / 10) % 10);
                hpt[7] = 16 + (num % 10);
                hpt[8] = 0;
            }
            else
            {
                hpt[4] = 16 + ((num / 10000) % 10);
                hpt[5] = 16 + ((num / 1000) % 10);
                hpt[6] = 16 + ((num / 100) % 10);
                hpt[7] = 16 + ((num / 10) % 10);
                hpt[8] = 16 + (num % 10);
            }

            hpt[9] = 0;

            graph_settext(hpt, stat[0], 10);
        }
        else if (person->armor_hp > 0)
        {
            u_char hpt[10] = {33, 50, 26, 0, 16};

            u_int num = person->armor_hp;

            if (num < 10)
            {
                hpt[4] = 16 + (num % 10);
                hpt[5] = 0;
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 100)
            {
                hpt[4] = 16 + ((num / 10) % 10);
                hpt[5] = 16 + (num % 10);
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 1000)
            {
                hpt[4] = 16 + ((num / 100) % 10);
                hpt[5] = 16 + ((num / 10) % 10);
                hpt[6] = 16 + (num % 10);
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 10000)
            {
                hpt[4] = 16 + ((num / 1000) % 10);
                hpt[5] = 16 + ((num / 100) % 10);
                hpt[6] = 16 + ((num / 10) % 10);
                hpt[7] = 16 + (num % 10);
                hpt[8] = 0;
            }
            else
            {
                hpt[4] = 16 + ((num / 10000) % 10);
                hpt[5] = 16 + ((num / 1000) % 10);
                hpt[6] = 16 + ((num / 100) % 10);
                hpt[7] = 16 + ((num / 10) % 10);
                hpt[8] = 16 + (num % 10);
            }

            hpt[9] = 0;

            graph_settext(hpt, stat[0], 10);
        }
        else
        {
            u_char hpt[10] = {40, 48, 26, 0, 16};

            u_int num = person->hp;

            if (num < 10)
            {
                hpt[4] = 16 + (num % 10);
                hpt[5] = 0;
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 100)
            {
                hpt[4] = 16 + ((num / 10) % 10);
                hpt[5] = 16 + (num % 10);
                hpt[6] = 0;
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 1000)
            {
                hpt[4] = 16 + ((num / 100) % 10);
                hpt[5] = 16 + ((num / 10) % 10);
                hpt[6] = 16 + (num % 10);
                hpt[7] = 0;
                hpt[8] = 0;
            }
            else if (num < 10000)
            {
                hpt[4] = 16 + ((num / 1000) % 10);
                hpt[5] = 16 + ((num / 100) % 10);
                hpt[6] = 16 + ((num / 10) % 10);
                hpt[7] = 16 + (num % 10);
                hpt[8] = 0;
            }
            else
            {
                hpt[4] = 16 + ((num / 10000) % 10);
                hpt[5] = 16 + ((num / 1000) % 10);
                hpt[6] = 16 + ((num / 100) % 10);
                hpt[7] = 16 + ((num / 10) % 10);
                hpt[8] = 16 + (num % 10);
            }

            hpt[9] = 0;

            graph_settext(hpt, stat[0], 10);
        }

        u_char mpt[10] = {45, 48, 26, 0, 16};

        u_int num = person->mp;

        if (num < 10)
        {
            mpt[4] = 16 + (num % 10);
            mpt[5] = 0;
            mpt[6] = 0;
            mpt[7] = 0;
            mpt[8] = 0;
        }
        else if (num < 100)
        {
            mpt[4] = 16 + ((num / 10) % 10);
            mpt[5] = 16 + (num % 10);
            mpt[6] = 0;
            mpt[7] = 0;
            mpt[8] = 0;
        }
        else if (num < 1000)
        {
            mpt[4] = 16 + ((num / 100) % 10);
            mpt[5] = 16 + ((num / 10) % 10);
            mpt[6] = 16 + (num % 10);
            mpt[7] = 0;
            mpt[8] = 0;
        }
        else if (num < 10000)
        {
            mpt[4] = 16 + ((num / 1000) % 10);
            mpt[5] = 16 + ((num / 100) % 10);
            mpt[6] = 16 + ((num / 10) % 10);
            mpt[7] = 16 + (num % 10);
            mpt[8] = 0;
        }
        else
        {
            mpt[4] = 16 + ((num / 10000) % 10);
            mpt[5] = 16 + ((num / 1000) % 10);
            mpt[6] = 16 + ((num / 100) % 10);
            mpt[7] = 16 + ((num / 10) % 10);
            mpt[8] = 16 + (num % 10);
        }

        mpt[9] = 0;

        graph_settext(mpt, stat[1], 10);

        u_char lvt[10] = {44, 54, 44, 26, 0, 16};

        num = person->lvl;

        if (num < 10)
        {
            lvt[5] = 16 + (num % 10);
            lvt[6] = 0;
            lvt[7] = 0;
            lvt[8] = 0;
            lvt[9] = 0;
        }
        else if (num < 100)
        {
            lvt[5] = 16 + ((num / 10) % 10);
            lvt[6] = 16 + (num % 10);
            lvt[7] = 0;
            lvt[8] = 0;
            lvt[9] = 0;
        }
        else if (num < 1000)
        {
            lvt[5] = 16 + ((num / 100) % 10);
            lvt[6] = 16 + ((num / 10) % 10);
            lvt[7] = 16 + (num % 10);
            lvt[8] = 0;
            lvt[9] = 0;
        }
        else if (num < 10000)
        {
            lvt[5] = 16 + ((num / 1000) % 10);
            lvt[6] = 16 + ((num / 100) % 10);
            lvt[7] = 16 + ((num / 10) % 10);
            lvt[8] = 16 + (num % 10);
            lvt[9] = 0;
        }
        else
        {
            lvt[5] = 16 + ((num / 10000) % 10);
            lvt[6] = 16 + ((num / 1000) % 10);
            lvt[7] = 16 + ((num / 100) % 10);
            lvt[8] = 16 + ((num / 10) % 10);
            lvt[9] = 16 + (num % 10);
        }

        graph_settext(lvt, stat[2], 10);

        graph_drawtext((person->def_loc.vx / 2) + 128, ((person->def_loc.vy + 48) / 2) + 128, 128, 10, 0, stat[0], 513);
        graph_drawtext((person->def_loc.vx / 2) + 128, ((person->def_loc.vy + 80) / 2) + 128, 128, 10, 0, stat[1], 514);
        graph_drawtext((person->def_loc.vx / 2) + 128, ((person->def_loc.vy - 80) / 2) + 128, 128, 10, 0, stat[2], 515);

        if (person->freeze > 0)
        {
            person->spr.clut = getClut(256, 459);
        }

        if (person->shd_mode && person->shd > 0)
        {
            Sprite shd_spr;

            shd_spr.MovVector.vx = person->spr.ScaleVector.vx > 0 ? person->spr.MovVector.vx + 64 : person->spr.MovVector.vx - 64;
            shd_spr.MovVector.vy = person->spr.MovVector.vy;
            shd_spr.MovVector.vz = person->spr.MovVector.vz;

            shd_spr.RotVector.vx = 0;
            shd_spr.RotVector.vy = 0;
            shd_spr.RotVector.vz = 0;

            shd_spr.ScaleVector.vx = person->spr.ScaleVector.vx;
            shd_spr.ScaleVector.vy = ONE * 2;
            shd_spr.ScaleVector.vz = ONE * 2;

            shd_spr.tpage = getTPage(0, 0, 320, 0);
            shd_spr.clut = getClut(256, 449);

            shd_spr.w = 16;
            shd_spr.h = 16;
            shd_spr.u = 0;
            shd_spr.v = 0;

            shd_spr.r = 128;
            shd_spr.g = 128;
            shd_spr.b = 128;
            shd_spr.alpha = 128;

            switch (person->shd)
            {
            case 1:
            {
                shd_spr.u = 0;

                shd_spr.r = 128;
                shd_spr.g = 64;
                shd_spr.b = 0;

                break;
            }
            case 2:
            {
                shd_spr.u = 0;

                shd_spr.r = 128;
                shd_spr.g = 128;
                shd_spr.b = 128;

                break;
            }
            case 3:
            {
                shd_spr.u = 0;

                shd_spr.r = 255;
                shd_spr.g = 255;
                shd_spr.b = 0;

                break;
            }
            case 4:
            {
                shd_spr.u = 0;

                shd_spr.r = 255;
                shd_spr.g = 255;
                shd_spr.b = 255;

                break;
            }
            case 5:
            {
                shd_spr.u = 0;

                shd_spr.r = 0;
                shd_spr.g = 255;
                shd_spr.b = 255;

                break;
            }
            case 6:
            {
                shd_spr.u = 0;

                shd_spr.r = 0;
                shd_spr.g = 255;
                shd_spr.b = 0;

                break;
            }
            case 7:
            {
                shd_spr.u = 16;

                shd_spr.r = 255;
                shd_spr.g = 0;
                shd_spr.b = 0;

                break;
            }
            case 8:
            {
                shd_spr.u = 32;

                shd_spr.r = 127;
                shd_spr.g = 0;
                shd_spr.b = 255;

                break;
            }
            default:
            {
                break;
            }
            }

            if (person->shd_mana > 0)
            {
                shd_spr.r = 0;
                shd_spr.g = 0;
                shd_spr.b = 255;
            }

            graph_drawsprite(shd_spr, -1);
        }

        if (person->regen > 0)
        {
            Sprite buzz_spr;

            buzz_spr.MovVector.vx = person->spr.MovVector.vx;
            buzz_spr.MovVector.vy = person->spr.MovVector.vy;
            buzz_spr.MovVector.vz = person->spr.MovVector.vz - 1;

            buzz_spr.RotVector.vx = 0;
            buzz_spr.RotVector.vy = 0;
            buzz_spr.RotVector.vz = 0;

            buzz_spr.ScaleVector.vx = ONE * 2;
            buzz_spr.ScaleVector.vy = ONE * 2;
            buzz_spr.ScaleVector.vz = ONE * 2;

            buzz_spr.tpage = getTPage(0, 0, 320, 0);
            buzz_spr.clut = getClut(256, 449);

            buzz_spr.w = 16;
            buzz_spr.h = 16;
            buzz_spr.u = 96;
            buzz_spr.v = 0;

            buzz_spr.r = 128;
            buzz_spr.g = 0;
            buzz_spr.b = 0;
            buzz_spr.alpha = 128;

            graph_drawsprite(buzz_spr, -1);
        }
        else if (person->poison > 0)
        {
            Sprite buzz_spr;

            buzz_spr.MovVector.vx = person->spr.MovVector.vx;
            buzz_spr.MovVector.vy = person->spr.MovVector.vy;
            buzz_spr.MovVector.vz = person->spr.MovVector.vz - 1;

            buzz_spr.RotVector.vx = 0;
            buzz_spr.RotVector.vy = 0;
            buzz_spr.RotVector.vz = 0;

            buzz_spr.ScaleVector.vx = ONE * 2;
            buzz_spr.ScaleVector.vy = ONE * 2;
            buzz_spr.ScaleVector.vz = ONE * 2;

            buzz_spr.tpage = getTPage(0, 0, 320, 0);
            buzz_spr.clut = getClut(256, 449);

            buzz_spr.w = 16;
            buzz_spr.h = 16;
            buzz_spr.u = 96;
            buzz_spr.v = 0;

            buzz_spr.r = 0;
            buzz_spr.g = 128;
            buzz_spr.b = 0;
            buzz_spr.alpha = 128;

            graph_drawsprite(buzz_spr, -1);
        }
    }

    if (person->dmgt)
    {
        person->dmgt_y += person->dmgt_speed * graph.delta;
        if (person->dmgt_y > ((person->def_loc.vy + 48) / 2) + 128)
        {
            person->dmgt_y = ((person->def_loc.vy + 48) / 2) + 128;
        }

        if (person->dmgt_speed < 4)
        {
            person->dmgt_speed += graph.delta;
        }

        u_char dmgt_t[9] = {0, 0, 0, 0, 0};
        TextChar dmgt_tx[9];

        u_int dmgt_sz = 0;

        for (u_char i = 0; i < 9; i++)
        {
            graph_inittext(&dmgt_tx[i]);
            dmgt_tx[i].r = 63;
            dmgt_tx[i].g = 63;
            dmgt_tx[i].b = 63;
        }

        if (person->dmgt_c < 10)
        {
            dmgt_t[0] = 16 + (person->dmgt_c % 10);
            dmgt_t[1] = 0;
            dmgt_t[2] = 0;
            dmgt_t[3] = 0;
            dmgt_t[4] = 0;
            dmgt_t[5] = 0;
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 1;
        }
        else if (person->dmgt_c < 100)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[1] = 16 + (person->dmgt_c % 10);
            dmgt_t[2] = 0;
            dmgt_t[3] = 0;
            dmgt_t[4] = 0;
            dmgt_t[5] = 0;
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 2;
        }
        else if (person->dmgt_c < 1000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[2] = 16 + (person->dmgt_c % 10);
            dmgt_t[3] = 0;
            dmgt_t[4] = 0;
            dmgt_t[5] = 0;
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 3;
        }
        else if (person->dmgt_c < 10000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[3] = 16 + (person->dmgt_c % 10);
            dmgt_t[4] = 0;
            dmgt_t[5] = 0;
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 4;
        }
        else if (person->dmgt_c < 100000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 10000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[3] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[4] = 16 + (person->dmgt_c % 10);
            dmgt_t[5] = 0;
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 5;
        }
        else if (person->dmgt_c < 1000000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 100000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 10000) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[3] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[4] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[5] = 16 + (person->dmgt_c % 10);
            dmgt_t[6] = 0;
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 6;
        }
        else if (person->dmgt_c < 10000000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 1000000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 100000) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 10000) % 10);
            dmgt_t[3] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[4] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[5] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[6] = 16 + (person->dmgt_c % 10);
            dmgt_t[7] = 0;
            dmgt_t[8] = 0;
            dmgt_sz = 7;
        }
        else if (person->dmgt_c < 100000000)
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 10000000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 1000000) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 100000) % 10);
            dmgt_t[3] = 16 + ((person->dmgt_c / 10000) % 10);
            dmgt_t[4] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[5] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[6] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[7] = 16 + (person->dmgt_c % 10);
            dmgt_t[8] = 0;
            dmgt_sz = 8;
        }
        else
        {
            dmgt_t[0] = 16 + ((person->dmgt_c / 100000000) % 10);
            dmgt_t[1] = 16 + ((person->dmgt_c / 10000000) % 10);
            dmgt_t[2] = 16 + ((person->dmgt_c / 1000000) % 10);
            dmgt_t[3] = 16 + ((person->dmgt_c / 100000) % 10);
            dmgt_t[4] = 16 + ((person->dmgt_c / 10000) % 10);
            dmgt_t[5] = 16 + ((person->dmgt_c / 1000) % 10);
            dmgt_t[6] = 16 + ((person->dmgt_c / 100) % 10);
            dmgt_t[7] = 16 + ((person->dmgt_c / 10) % 10);
            dmgt_t[8] = 16 + (person->dmgt_c % 10);
            dmgt_sz = 9;
        }

        graph_settext(dmgt_t, dmgt_tx, dmgt_sz);

        graph_drawtext(person->dmgt_x, person->dmgt_y, 128, dmgt_sz, 0, dmgt_tx, 1);

        person->dmgt_tick += graph.delta;

        if (person->dmgt_tick > (fps * 2) + (fps / 2))
        {
            person->dmgt_tick = 0;
            person->dmgt_c = 0;
            person->dmgt_speed = -4;
            person->dmgt = FALSE;
        }
    }

    graph_drawsprite(person->spr, -1);
}

void person_damage(Person *victim, Person *attacker, u_int dmg, u_char allow_dodging)
{
    if (!victim)
    {
        return;
    }

    if (dmg == 0 && attacker)
    {
        dmg = attacker->dmg;
    }

    if (attacker)
    {
        if (victim->spr.MovVector.vx <= attacker->spr.MovVector.vx)
        {
            victim->spr.ScaleVector.vx = ONE * 2;
        }
        else
        {
            victim->spr.ScaleVector.vx = -(ONE * 2);
        }
    }

    Person *person = victim;
    Person *target = NULL;

    if (attacker)
    {
        target = attacker;
    }

    if (allow_dodging && victim->parry && victim->freeze <= 0 && attacker)
    {
        person = attacker;
        target = victim;
        dmg = victim->dmg;
    }

    if (person->shd_mode && person->shd == 0)
    {
        dmg /= 2;
    }
    else if (person->shd_mode && person->shd_mana > 0)
    {
        dmg = 0;
    }

    if (allow_dodging && person->dodge && person->freeze <= 0)
    {
        dmg = 0;
    }

    if (dmg <= 0)
    {
        return;
    }

    if (person->dmgt)
    {
        person->dmgt_tick = 0;
        person->dmgt_c = 0;
        person->dmgt_speed = -4;
        person->dmgt = FALSE;
    }

    person->dmgt_c += dmg;

    if (!person->turn)
    {
        person->spr.MovVector.vx = person->def_loc.vx;
        person->spr.MovVector.vy = person->def_loc.vy;
        person->spr.MovVector.vz = person->def_loc.vz;

        person->pivot.vx = person->spr.MovVector.vx;
        person->pivot.vy = person->spr.MovVector.vy;
        person->pivot.vz = person->spr.MovVector.vz;
    }

    person->dodge = FALSE;
    person->parry = FALSE;

    if (!person->shd_mode && person->freeze <= 0)
    {
        person->spr.u = 96;
        person->spr.v = 32;
    }

    person->max_tick = 30;
    person->tick = 0;
    person->anim = 3;

    if (person->armor_hp <= 0 && (!person->shd_mode || person->shd_hp <= 0 || person->shd == 0))
    {
        sound_playsfx(&sfx[4], 13, 0x0000, FALSE, 255, 255);

        if (person->hp > dmg)
        {
            person->hp -= dmg;
        }
        else
        {
            if (person->hp != 0)
            {
                if (target)
                {
                    for (u_char i = 0; i < 3; i++)
                    {
                        if (person->pot[i] <= 0)
                        {
                            if (target->pot[i] < 50)
                            {
                                target->pot[i]++;
                            }
                            else
                            {
                                target->pot[i] = 50;
                            }
                        }
                        else
                        {
                            if (target->pot[i] < 50 - person->pot[i])
                            {
                                target->pot[i] += person->pot[i];
                            }
                            else
                            {
                                target->pot[i] = 50;
                            }
                        }
                    }
                }
            }

            person->hp = 0;
        }
    }

    if (person->armor_hp > 0 && (!person->shd_mode || person->shd_hp <= 0 || person->shd == 0))
    {
        sound_playsfx(&sfx[6], 13, 0x0000, FALSE, 255, 255);

        if (person->armor_hp > dmg)
        {
            person->armor_hp -= dmg;
        }
        else
        {
            person->armor_hp = 0;
        }
    }

    if (person->shd_mode && person->shd_hp > dmg && person->shd > 0)
    {
        sound_playsfx(&sfx[6], 13, 0x0000, FALSE, 255, 255);
        person->shd_hp -= dmg;
    }
    else
    {
        if (person->shd_mode)
        {
            sound_playsfx(&sfx[6], 13, 0x0000, FALSE, 255, 255);
            person->shd_hp = 0;
        }

        if (person->shd > 0 && person->shd_mode)
        {
            person->shd_mode = FALSE;
        }
    }
}

void fx_init(FX *fx)
{
    fx->active = TRUE;
    fx->tick = 0;
    fx->spr.tpage = getTPage(0, 0, 320, 0);
    fx->spr.clut = getClut(256, 449);
    fx->spr.w = 16;
    fx->spr.h = 16;
    fx->spr.v = 0;
    fx->owner = NULL;

    fx->spr.alpha = 128;

    fx->spr.RotVector.vx = 0;
    fx->spr.RotVector.vy = 0;
    fx->spr.RotVector.vz = 0;

    fx->target = NULL;

    switch (fx->type)
    {
    case 0:
    {
        fx->spr.ScaleVector.vx = ONE * 2;
        fx->spr.ScaleVector.vy = ONE * 2;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 48;

        fx->spr.r = 255;
        fx->spr.g = 127;
        fx->spr.b = 0;
        break;
    }
    case 1:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 255;
        fx->spr.g = 127;
        fx->spr.b = 0;
        break;
    }
    case 2:
    {
        fx->spr.ScaleVector.vx = ONE * 4;
        fx->spr.ScaleVector.vy = (ONE * 8) - 1;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 80;

        fx->spr.r = 255;
        fx->spr.g = 255;
        fx->spr.b = 255;
        break;
    }
    case 3:
    {
        fx->spr.ScaleVector.vx = ONE * 2;
        fx->spr.ScaleVector.vy = ONE * 2;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 48;

        fx->spr.r = 128;
        fx->spr.g = 0;
        fx->spr.b = 255;
        break;
    }
    case 4:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 255;
        fx->spr.g = 0;
        fx->spr.b = 0;
        break;
    }
    case 5:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 0;
        fx->spr.g = 255;
        fx->spr.b = 255;
        break;
    }
    case 6:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 255;
        fx->spr.g = 255;
        fx->spr.b = 255;
        break;
    }
    case 7:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 0;
        fx->spr.g = 0;
        fx->spr.b = 255;
        break;
    }
    case 8:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 0;
        fx->spr.g = 255;
        fx->spr.b = 0;
        break;
    }
    case 9:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 255;
        fx->spr.g = 0;
        fx->spr.b = 255;
        break;
    }
    case 10:
    {
        fx->spr.ScaleVector.vx = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vy = fx->reverse ? (ONE * 8) - 1 : 0;
        fx->spr.ScaleVector.vz = ONE * 2;

        fx->spr.u = 64;

        fx->spr.r = 127;
        fx->spr.g = 0;
        fx->spr.b = 255;
        break;
    }
    default:
    {
        break;
    }
    }
}

void fx_update(FX *fx)
{
    u_int fps = REGION_CODE == 0 ? 50 : 60;

    switch (fx->type)
    {
    case 0:
    {
        VECTOR dir;

        dir.vx = fx->target->def_loc.vx - fx->spr.MovVector.vx;
        dir.vy = fx->target->def_loc.vy - fx->spr.MovVector.vy;

        short rot = -ratan2(dir.vy, dir.vx) + (-1024);

        long dis = SquareRoot0(
            (dir.vx * dir.vx) +
            (dir.vy * dir.vy));

        VECTOR forward;

        forward.vx = csin(rot);
        forward.vy = ccos(rot);

        fx->spr.MovVector.vx -= ((forward.vx * 4) * graph.delta) >> 12;
        fx->spr.MovVector.vy -= ((forward.vy * 4) * graph.delta) >> 12;

        if (dis < 32)
        {
            if (fx->target->parry && fx->target->freeze <= 0)
            {
                Person *trg = fx->owner;

                fx->owner = fx->target;
                fx->target = trg;
            }
            else
            {
                person_damage(fx->target, fx->owner, 5, TRUE);

                fx->active = FALSE;
            }
        }

        break;
    }
    case 1:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 2:
    {
        if (fx->tick < (fps / 2))
        {
            VECTOR dir;

            dir.vx = fx->target->def_loc.vx - fx->spr.MovVector.vx;
            dir.vy = fx->target->def_loc.vy - fx->spr.MovVector.vy;

            short rot = -ratan2(dir.vx, dir.vy);

            fx->spr.RotVector.vz = rot;

            fx->tick += graph.delta;
        }
        else
        {
            fx->active = FALSE;
        }
        break;
    }
    case 3:
    {
        VECTOR dir;

        dir.vx = fx->target->def_loc.vx - fx->spr.MovVector.vx;
        dir.vy = fx->target->def_loc.vy - fx->spr.MovVector.vy;

        short rot = -ratan2(dir.vy, dir.vx) + (-1024);

        long dis = SquareRoot0(
            (dir.vx * dir.vx) +
            (dir.vy * dir.vy));

        VECTOR forward;

        forward.vx = csin(rot);
        forward.vy = ccos(rot);

        fx->spr.MovVector.vx -= ((forward.vx * 4) * graph.delta) >> 12;
        fx->spr.MovVector.vy -= ((forward.vy * 4) * graph.delta) >> 12;

        if (dis < 32)
        {
            if (fx->target->parry && fx->target->freeze <= 0)
            {
                Person *trg = fx->owner;

                fx->owner = fx->target;
                fx->target = trg;
            }
            else
            {
                person_damage(fx->target, fx->owner, 2500 * fx->owner->spell_rank[fx->owner->action[1]], TRUE);

                fx->active = FALSE;
            }
        }

        break;
    }
    case 4:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 5:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 6:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 7:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 8:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 9:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    case 10:
    {
        if (!fx->reverse)
        {
            if (fx->spr.ScaleVector.vx < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vy < ((ONE * 8) - 1) - 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy += 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = (ONE * 8) - 1;
            }

            if (fx->spr.ScaleVector.vx >= (ONE * 8) - 1 && fx->spr.ScaleVector.vy >= (ONE * 8) - 1)
            {
                fx->active = FALSE;
            }
        }
        else
        {
            if (fx->spr.ScaleVector.vx > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vx -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vx = 0;
            }

            if (fx->spr.ScaleVector.vy > 2048 * graph.delta)
            {
                fx->spr.ScaleVector.vy -= 2048 * graph.delta;
            }
            else
            {
                fx->spr.ScaleVector.vy = 0;
            }

            if (fx->spr.ScaleVector.vx <= 0 && fx->spr.ScaleVector.vy <= 0)
            {
                fx->active = FALSE;
            }
        }

        break;
    }
    default:
    {
        break;
    }
    }

    graph_drawsprite(fx->spr, -1);
}

FX *battle_spawnfx(SceneBattle *battle)
{
    FX *mem = (FX *)malloc(sizeof(FX));
    if (!mem)
        return NULL;

    mem->next = battle->fx;
    battle->fx = mem;

    return mem;
}