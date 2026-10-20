#include "editor.h"

void fill_player_entry17(player_entry &players, int &current_byte, void* ghdescriptor, bool preserveId)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;
	
	int id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);
	if (!preserveId)
		players.id = id;

	current_byte += 0x6;

	players.nation = read_dataOld(0, 2 * 8, current_byte, pDescriptorOld);

	players.height = pDescriptorOld->data[current_byte];
	current_byte++;

	players.weight = pDescriptorOld->data[current_byte];
	current_byte++;

	players.gc1 = pDescriptorOld->data[current_byte];
	current_byte++;

	players.gc2 = pDescriptorOld->data[current_byte];
	current_byte++;

	players.atk = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.def = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.gk = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.drib = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.mo_fk = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.finish = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.lowpass = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.loftpass = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.header = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.form = read_dataOld(4, 3, current_byte, pDescriptorOld);

	players.b_edit_player = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.swerve = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.catching = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.clearing = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.reflex = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.injury = read_dataOld(4, 2, current_byte, pDescriptorOld);
	
	//Unknown B - 1 bit

	players.b_edit_basicset = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.body_ctrl = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.phys_cont = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.kick_pwr = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.exp_pwr = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.mo_armd = read_dataOld(4, 3, current_byte, pDescriptorOld);

	players.b_edit_regpos = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.age = read_dataOld(0, 6, current_byte, pDescriptorOld);

	players.reg_pos = read_dataOld(6, 4, current_byte, pDescriptorOld);
	
	//Unknown C - 1 bit

	players.play_style = read_dataOld(3, 5, current_byte, pDescriptorOld);

	players.ball_ctrl = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.ball_win = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.weak_acc = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.jump = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.mo_armr = read_dataOld(7, 3, current_byte, pDescriptorOld);

	players.mo_ck = read_dataOld(2, 3, current_byte, pDescriptorOld);

	players.cover = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.weak_use = read_dataOld(4, 2, current_byte, pDescriptorOld);

	players.play_pos[0] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[1] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[2] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[3] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[4] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[5] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[6] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[7] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[8] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[9] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[10] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[11] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[12] = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.mo_hunchd = read_dataOld(0, 2, current_byte, pDescriptorOld);

	players.mo_hunchr = read_dataOld(2, 2, current_byte, pDescriptorOld);

	players.mo_pk = read_dataOld(4, 2, current_byte, pDescriptorOld);

	players.place_kick = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.b_edit_playpos = read_dataOld(5, 1, current_byte, pDescriptorOld);

	players.b_edit_ability = read_dataOld(6, 1, current_byte, pDescriptorOld);

	players.b_edit_skill = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.stamina = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.speed = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.b_edit_style = read_dataOld(6, 1, current_byte, pDescriptorOld);

	players.b_edit_com = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.b_edit_motion = read_dataOld(0, 1, current_byte, pDescriptorOld);

	players.b_base_copy = read_dataOld(1, 1, current_byte, pDescriptorOld);

	//Unknown D - 1/1
	
	players.strong_foot = read_dataOld(3, 1, current_byte, pDescriptorOld);
	//Unknown E - 1/1
	players.com_style[0] = read_dataOld(5, 1, current_byte, pDescriptorOld);
	players.com_style[1] = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.com_style[2] = read_dataOld(7, 1, current_byte, pDescriptorOld);
	players.com_style[3] = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.com_style[4] = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.com_style[5] = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.com_style[6] = read_dataOld(3, 1, current_byte, pDescriptorOld);

	players.play_skill[0] = read_dataOld(4, 1, current_byte, pDescriptorOld);
	players.play_skill[1] = read_dataOld(5, 1, current_byte, pDescriptorOld);
	players.play_skill[2] = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.play_skill[3] = read_dataOld(7, 1, current_byte, pDescriptorOld);
	players.play_skill[4] = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.play_skill[5] = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.play_skill[6] = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.play_skill[7] = read_dataOld(3, 1, current_byte, pDescriptorOld);
	players.play_skill[8] = read_dataOld(4, 1, current_byte, pDescriptorOld);
	players.play_skill[9] = read_dataOld(5, 1, current_byte, pDescriptorOld);
	players.play_skill[10] = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.play_skill[11] = read_dataOld(7, 1, current_byte, pDescriptorOld);
	players.play_skill[12] = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.play_skill[13] = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.play_skill[14] = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.play_skill[15] = read_dataOld(3, 1, current_byte, pDescriptorOld);
	players.play_skill[16] = read_dataOld(4, 1, current_byte, pDescriptorOld);
	players.play_skill[17] = read_dataOld(5, 1, current_byte, pDescriptorOld);
	players.play_skill[18] = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.play_skill[19] = read_dataOld(7, 1, current_byte, pDescriptorOld);
	players.play_skill[20] = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.play_skill[21] = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.play_skill[22] = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.play_skill[23] = read_dataOld(3, 1, current_byte, pDescriptorOld);
	players.play_skill[24] = read_dataOld(4, 1, current_byte, pDescriptorOld);
	players.play_skill[25] = read_dataOld(5, 1, current_byte, pDescriptorOld);
	players.play_skill[26] = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.play_skill[27] = read_dataOld(7, 1, current_byte, pDescriptorOld);

	//Unknown F - 8/8
	current_byte++;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorOld->data[current_byte]), -1, players.name, 46);
	current_byte+=46;

	strncpy_s(players.shirt_name, 18, (const char*)&(pDescriptorOld->data[current_byte]), 18 - 1);
	current_byte+=18;

	//Appearance entries
	//playerID
	current_byte+=4;

	players.b_edit_face = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.b_edit_hair = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.b_edit_phys = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.b_edit_strip = read_dataOld(3, 1, current_byte, pDescriptorOld);

	players.boot_id = read_dataOld(4, 14, current_byte, pDescriptorOld);

	players.glove_id = read_dataOld(2, 14, current_byte, pDescriptorOld); //Extend to be 14 bits, using Unk A space

	players.copy_id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);

	players.neck_len = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.neck_size = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.shldr_hi = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.shldr_wid = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.chest = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.waist = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.arm_size = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.arm_len = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.thigh = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.calf = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.leg_len = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.head_len = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.head_wid = read_dataOld(0, 4, current_byte, pDescriptorOld);

	players.head_dep = read_dataOld(4, 4, current_byte, pDescriptorOld);

	players.wrist_col_l = read_dataOld(0, 3, current_byte, pDescriptorOld);
	players.wrist_col_r = read_dataOld(3, 3, current_byte, pDescriptorOld);
	players.wrist_tape = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.spec_col = read_dataOld(0, 3, current_byte, pDescriptorOld);
	players.spec_style = read_dataOld(3, 3, current_byte, pDescriptorOld);
	players.sleeve = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.inners = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.socks = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.undershorts = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.untucked = read_dataOld(6, 1, current_byte, pDescriptorOld);
	players.ankle_tape = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.gloves = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.gloves_col = read_dataOld(1, 3, current_byte, pDescriptorOld);
	//Unknown D
	current_byte++;

	//Unknown E
	current_byte+=22;

	players.skin_col = read_dataOld(0, 3, current_byte, pDescriptorOld);
	//Unknown F
	current_byte++;

	//Unknown G
	current_byte+=18;

	players.iris_col = read_dataOld(0, 4, current_byte, pDescriptorOld);
	//Unknown H
	current_byte++;

	//Unknown I
	current_byte+=7;
}


void fill_team_ids17(team_entry &team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	team.id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);

	current_byte+=0xE; //0x12
	team.color1_red = read_dataOld(0, 6, current_byte, pDescriptorOld); //0x12:0 - 0x12:5

	team.color1_green = read_dataOld(6, 6, current_byte, pDescriptorOld); //0x12:6 - 0x13:3
	
	current_byte++; //0x14
	team.color2_red = read_dataOld(0, 6, current_byte, pDescriptorOld); //0x14:0 - 0x14:5
	
	team.color2_green = read_dataOld(6, 6, current_byte, pDescriptorOld); //0x14:6 - 0x15:3
	
	team.color2_blue = read_dataOld(4, 6, current_byte, pDescriptorOld); //0x15:4 - 0x16:1

	team.color1_blue = read_dataOld(2, 6, current_byte, pDescriptorOld); //0x16:2 - 0x16:7
	
	current_byte+=0x2; //0x19
	team.b_edit_name = read_dataOld(4, 1, current_byte, pDescriptorOld); //0x19:4

	current_byte++; //0x1A
	team.b_edit_strip = read_dataOld(5, 1, current_byte, pDescriptorOld); //0x1A:5

	current_byte += 2; //0x1C
	for (int ii = 0; ii < 10; ii++)
	{
		team.stripBlock[ii].stripNumber = read_dataOld(0, 1 * 8, current_byte, pDescriptorOld); //Loop from 0x1C to 0x40
		team.stripBlock[ii].stripTeamId = read_dataOld(0, 3 * 8, current_byte, pDescriptorOld);
	}

	current_byte += 0x54;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorOld->data[current_byte]), -1, team.name, 0x46); //0x98
	current_byte+=0x46;

	strncpy_s(team.short_name, 0x4, (const char*)&(pDescriptorOld->data[current_byte]), 0x4 - 1); //0xDE
	//Remove non alphanumeric characters
	for(int ii=0;ii<4;ii++)
	{
		if((int)team.short_name[ii]<33 || (int)team.short_name[ii]>95)
			team.short_name[ii]=(char)0;
	}
	current_byte+=0x4; //48-90

	current_byte+=0xFE;
}


void fill_team_rosters17(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	int ii, t_ind;
	unsigned long team_id, player_id;

	team_id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}

	for(ii=0;ii<32;ii++)
	{
		player_id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);

		gteams[t_ind].players[ii] = player_id;
		if(player_id) gteams[t_ind].num_on_team++; //new
	}
	//Hide team with no players
	if(gteams[t_ind].players[0] == 0) 
		gteams[t_ind].b_show = false;

	for(ii=0;ii<32;ii++)
	{
		gteams[t_ind].numbers[ii] = pDescriptorOld->data[current_byte];
		current_byte++;
	}
}


void fill_team_tactics17(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams, int t_ind)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	unsigned long team_id;

	team_id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);

	if (t_ind == -1)
	{
		for (t_ind=0; t_ind<gnum_teams; t_ind++)
		{
			if (team_id == gteams[t_ind].id) break;
		}
	}
	//current_byte+=0x1E0;

	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			for (int kk = 0; kk < 11; kk++)
			{
				gteams[t_ind].presets[ii].formations[jj].players[kk].pos = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			}

			for (int kk = 0; kk < 11; kk++)
			{
				//Y/X rather than X/Y strangely
				gteams[t_ind].presets[ii].formations[jj].players[kk].y = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
				gteams[t_ind].presets[ii].formations[jj].players[kk].x = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			}
		}

		gteams[t_ind].presets[ii].attacking_style = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].buildup = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].attacking_zone = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].positioning = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].defensive_style = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].containment_area = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].pressure = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);

		//Begin differences from 16
		current_byte+=0x2;
		for (int jj = 0; jj < 2; jj++)
		{
			gteams[t_ind].presets[ii].atk_instructions[jj].instruction = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
			gteams[t_ind].presets[ii].atk_instructions[jj].player_id = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
		}
		for (int jj = 0; jj < 2; jj++)
		{
			gteams[t_ind].presets[ii].def_instructions[jj].instruction = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
			gteams[t_ind].presets[ii].def_instructions[jj].player_id = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
		}

		gteams[t_ind].presets[ii].support_range = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].numbers_in_attack = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].defensive_line = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].compactness = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		gteams[t_ind].presets[ii].numbers_in_defense = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		current_byte+=0xB; //Man Marking data, useless for the save file
		gteams[t_ind].presets[ii].fluid = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
		current_byte+=0x3;
	}

	for (int ii = 0; ii < 11; ii++)
	{
		gteams[t_ind].starting11[ii] = read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	}
	for (int ii = 0; ii < 21; ii++)
	{
		gteams[t_ind].bench_order[ii] = read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	}
	gteams[t_ind].fk_taker_long = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].fk_taker_short = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].fk_taker_2 = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].ck_taker_left = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].ck_taker_right = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].pk_taker = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	for (int ii = 0; ii < 3; ii++)
	{
		gteams[t_ind].players_to_join_attack[ii] = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	}
	gteams[t_ind].captain_ind = (char)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].auto_substitution = (byte)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].auto_offside_trap = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].auto_preset_change = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	gteams[t_ind].auto_change_atk_def_levels = (bool)read_dataOld(0, 1 * 8, current_byte, pDescriptorOld);
	current_byte+=0x1; //Auto Lineup Select, no reason for us to use that
	current_byte+=0x61; //Skip unknown byte plus padding
}

//---------------------------------------------------------------------------------------------------------


void extract_player_entry17(player_entry player, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!player.b_changed)
	{
		current_byte += 0xBC;
		return;
	}
	
//	unsigned char test[4];
	int cb=0;
	
	write_dataOld(player.id, 0, 4 * 8, current_byte, pDescriptorOld);

	current_byte += 0x6;

	write_dataOld(player.nation, 0, 2 * 8, current_byte, pDescriptorOld);

	write_dataOld(player.height, 0, 8, current_byte, pDescriptorOld);

	write_dataOld(player.weight, 0, 8, current_byte, pDescriptorOld);

	write_dataOld(player.gc1, 0, 8, current_byte, pDescriptorOld);

	write_dataOld(player.gc2, 0, 8, current_byte, pDescriptorOld);

	write_dataOld(player.atk, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.def, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.gk, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.drib, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.mo_fk, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.finish, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.lowpass, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.loftpass, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.header, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.form, 4, 3, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_player, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.swerve, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.catching, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.clearing, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.reflex, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.injury, 4, 2, current_byte, pDescriptorOld);

	//Unknown B - 1 bit

	write_dataOld(player.b_edit_basicset, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.body_ctrl, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.phys_cont, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.kick_pwr, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.exp_pwr, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.mo_armd, 4, 3, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_regpos, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.age, 0, 6, current_byte, pDescriptorOld);

	write_dataOld(player.reg_pos, 6, 4, current_byte, pDescriptorOld);

	//Unknown C - 1 bit

	write_dataOld(player.play_style, 3, 5, current_byte, pDescriptorOld);

	write_dataOld(player.ball_ctrl, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.ball_win, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.weak_acc, 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.jump, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.mo_armr, 7, 3, current_byte, pDescriptorOld);

	write_dataOld(player.mo_ck, 2, 3, current_byte, pDescriptorOld);

	write_dataOld(player.cover, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.weak_use, 4, 2, current_byte, pDescriptorOld);

	write_dataOld(player.play_pos[0], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[1], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[2], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[3], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[4], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[5], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[6], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[7], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[8], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[9], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[10], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[11], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[12], 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_hunchd, 0, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_hunchr, 2, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_pk, 4, 2, current_byte, pDescriptorOld);

	write_dataOld(player.place_kick, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_playpos, 5, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_ability, 6, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_skill, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.stamina, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.speed, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_style, 6, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_com, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_motion, 0, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_base_copy, 1, 1, current_byte, pDescriptorOld);

	//Unknown D - 1/1

	write_dataOld(player.strong_foot, 3, 1, current_byte, pDescriptorOld);
	//Unknown E - 1/1
	write_dataOld(player.com_style[0], 5, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[1], 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[2], 7, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[3], 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[4], 1, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[5], 2, 1, current_byte, pDescriptorOld);
	write_dataOld(player.com_style[6], 3, 1, current_byte, pDescriptorOld);

	write_dataOld(player.play_skill[0], 4, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[1], 5, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[2], 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[3], 7, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[4], 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[5], 1, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[6], 2, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[7], 3, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[8], 4, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[9], 5, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[10], 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[11], 7, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[12], 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[13], 1, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[14], 2, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[15], 3, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[16], 4, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[17], 5, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[18], 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[19], 7, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[20], 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[21], 1, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[22], 2, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[23], 3, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[24], 4, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[25], 5, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[26], 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.play_skill[27], 7, 1, current_byte, pDescriptorOld);
	
	//Unknown F - 8/8
	current_byte++;
	
	uint8_t nameBuffer[46];
	memset(nameBuffer, 0, sizeof(nameBuffer));
	int len = WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)nameBuffer, 45, NULL, NULL); //set byte limit to 45 to ensure null termination of truncated strings
	memcpy(&(pDescriptorOld->data[current_byte]), nameBuffer, 46);
	current_byte += 46;
	
	strncpy_s((char *)&(pDescriptorOld->data[current_byte]), 18, player.shirt_name, 18-1);
	current_byte+=18;
	
	//Appearance entries
	//playerID
	current_byte+=4;
	
	write_dataOld(player.b_edit_face, 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.b_edit_hair, 1, 1, current_byte, pDescriptorOld);
	write_dataOld(player.b_edit_phys, 2, 1, current_byte, pDescriptorOld);
	write_dataOld(player.b_edit_strip, 3, 1, current_byte, pDescriptorOld);

	write_dataOld(player.boot_id, 4, 14, current_byte, pDescriptorOld);

	write_dataOld(player.glove_id, 2, 14, current_byte, pDescriptorOld); //Extend to be 14 bits, using Unk A space

	write_dataOld(player.copy_id, 0, 4 * 8, current_byte, pDescriptorOld);

	write_dataOld(player.neck_len, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.neck_size, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.shldr_hi, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.shldr_wid, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.chest, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.waist, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.arm_size, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.arm_len, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.thigh, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.calf, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.leg_len, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.head_len, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.head_wid, 0, 4, current_byte, pDescriptorOld);

	write_dataOld(player.head_dep, 4, 4, current_byte, pDescriptorOld);

	write_dataOld(player.wrist_col_l, 0, 3, current_byte, pDescriptorOld);
	write_dataOld(player.wrist_col_r, 3, 3, current_byte, pDescriptorOld);
	write_dataOld(player.wrist_tape, 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.spec_col, 0, 3, current_byte, pDescriptorOld);
	write_dataOld(player.spec_style, 3, 3, current_byte, pDescriptorOld);
	write_dataOld(player.sleeve, 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.inners, 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.socks, 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.undershorts, 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.untucked, 6, 1, current_byte, pDescriptorOld);
	write_dataOld(player.ankle_tape, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.gloves, 0, 1, current_byte, pDescriptorOld);
	write_dataOld(player.gloves_col, 1, 3, current_byte, pDescriptorOld);
	//Unknown D - 4/4
	current_byte++;
	
	//Unknown E - 22 bytes
	current_byte+=22;
	
	write_dataOld(player.skin_col, 0, 3, current_byte, pDescriptorOld);
	//Unknown F - 5/5
	current_byte++;
	
	//Unknown G - 18 bytes
	current_byte+=18;
	
	write_dataOld(player.iris_col, 0, 4, current_byte, pDescriptorOld);
	//Unknown H - 4/4
	current_byte++;
	
	//Unknown I - 7 bytes
	current_byte+=7;
}


void extract_team_info17(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x1E0;
		return;
	}
	
	write_dataOld(team.id, 0, 4 * 8, current_byte, pDescriptorOld); //0 - 4
	
	current_byte += 0xE; //0x12
	write_dataOld(team.color1_red, 0, 6, current_byte, pDescriptorOld); //0x12:0 - 0x12:5

	write_dataOld(team.color1_green, 6, 6, current_byte, pDescriptorOld); //0x12:6 - 0x13:3

	current_byte++; //0x14
	write_dataOld(team.color2_red, 0, 6, current_byte, pDescriptorOld); //0x14:0 - 0x14:5

	write_dataOld(team.color2_green, 6, 6, current_byte, pDescriptorOld); //0x14:6 - 0x15:3

	write_dataOld(team.color2_blue, 4, 6, current_byte, pDescriptorOld); //0x15:4 - 0x16:1

	write_dataOld(team.color1_blue, 2, 6, current_byte, pDescriptorOld); //0x16:2 - 0x16:7
	
	current_byte+=0x2; //0x19:0
	write_dataOld(team.b_edit_name, 4, 1, current_byte, pDescriptorOld); //0x19:4

	current_byte++; //0x1A
	write_dataOld(team.b_edit_strip, 5, 1, current_byte, pDescriptorOld); //0x1A:5
	current_byte += 2; //0x1C

	for (int ii = 0; ii < 10; ii++)
	{
		write_dataOld(team.stripBlock[ii].stripNumber, 0, 1 * 8, current_byte, pDescriptorOld); //Loop from 0x1C to 0x40
		write_dataOld(team.stripBlock[ii].stripTeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	}
	
	current_byte += 0x54;
	
	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR)&(pDescriptorOld->data[current_byte]), 0x46, NULL, NULL); //0x98
	current_byte+=0x46;
	
	strncpy_s((char*)&(pDescriptorOld->data[current_byte]), 0x4, team.short_name, 0x4 - 1); //0xDE
	current_byte+=0x4;
	
	current_byte+=0xFE;
}

void extract_teamplayer_info17(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0xA4;
		return;
	}
	
	write_dataOld(team.id, 0, 4 * 8, current_byte, pDescriptorOld);
	
	int ii;
	for(ii=0;ii<32;ii++)
	{
		write_dataOld(team.players[ii], 0, 4 * 8, current_byte, pDescriptorOld);
	}
	
	for(ii=0;ii<32;ii++)
	{
		write_dataOld(team.numbers[ii], 0, 1 * 8, current_byte, pDescriptorOld);
	}
}


void extract_team_tactics17(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x274;
		return;
	}
	
	write_dataOld(team.id, 0, 4 * 8, current_byte, pDescriptorOld);
	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			for (int kk = 0; kk < 11; kk++)
			{
				write_dataOld(team.presets[ii].formations[jj].players[kk].pos, 0, 1 * 8, current_byte, pDescriptorOld);
			}

			for (int kk = 0; kk < 11; kk++)
			{
				//Y/X rather than X/Y strangely
				write_dataOld(team.presets[ii].formations[jj].players[kk].y, 0, 1 * 8, current_byte, pDescriptorOld);
				write_dataOld(team.presets[ii].formations[jj].players[kk].x, 0, 1 * 8, current_byte, pDescriptorOld);
			}
		}

		write_dataOld(team.presets[ii].attacking_style, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].buildup, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].attacking_zone, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].positioning, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].defensive_style, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].containment_area, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].pressure, 0, 1 * 8, current_byte, pDescriptorOld);

		//Begin differences from 16
		current_byte+=0x2;
		for (int jj = 0; jj < 2; jj++)
		{
			write_dataOld(team.presets[ii].atk_instructions[jj].instruction, 0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
			write_dataOld(team.presets[ii].atk_instructions[jj].player_id, 0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
		}
		for (int jj = 0; jj < 2; jj++)
		{
			write_dataOld(team.presets[ii].def_instructions[jj].instruction, 0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
			write_dataOld(team.presets[ii].def_instructions[jj].player_id, 0, 1 * 8, current_byte, pDescriptorOld);
			current_byte+=0x3;
		}

		write_dataOld(team.presets[ii].support_range, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].numbers_in_attack, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].defensive_line, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].compactness, 0, 1 * 8, current_byte, pDescriptorOld);
		write_dataOld(team.presets[ii].numbers_in_defense, 0, 1 * 8, current_byte, pDescriptorOld);
		current_byte+=0xB; //Man Marking data, useless for the save file
		write_dataOld(team.presets[ii].fluid, 0, 1 * 8, current_byte, pDescriptorOld);
		current_byte+=0x3;
	}

	for (int ii = 0; ii < 11; ii++)
	{
		write_dataOld(team.starting11[ii], 0, 1 * 8, current_byte, pDescriptorOld);
	}
	for (int ii = 0; ii < 21; ii++)
	{
		write_dataOld(team.bench_order[ii], 0, 1 * 8, current_byte, pDescriptorOld);
	}
	write_dataOld(team.fk_taker_long, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.fk_taker_short, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.fk_taker_2, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.ck_taker_left, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.ck_taker_right, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.pk_taker, 0, 1 * 8, current_byte, pDescriptorOld);
	for (int ii = 0; ii < 3; ii++)
	{
		write_dataOld(team.players_to_join_attack[ii], 0, 1 * 8, current_byte, pDescriptorOld);
	}
	write_dataOld(team.captain_ind, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.auto_substitution, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.auto_offside_trap, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.auto_preset_change, 0, 1 * 8, current_byte, pDescriptorOld);
	write_dataOld(team.auto_change_atk_def_levels, 0, 1 * 8, current_byte, pDescriptorOld);
	current_byte+=0x1; //Auto Lineup Select, no reason for us to use that
	current_byte+=0x61; //Skip unknown byte plus padding
}