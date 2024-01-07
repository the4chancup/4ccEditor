#include "editor.h"

void fill_player_entry16(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	players.id = pDescriptorOld->data[current_byte];
	current_byte++;
	players.id += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	players.id += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	players.id += pDescriptorOld->data[current_byte] << 24;
	current_byte++;
	/*
	if(players.id==73301)//Debug
	{
		int d3=0;
	}
	*/
	current_byte += 0x6;

	players.nation = pDescriptorOld->data[current_byte];
	current_byte++;
	players.nation += pDescriptorOld->data[current_byte] << 8;
	current_byte++;

	players.height = pDescriptorOld->data[current_byte];
	current_byte++;

	players.weight = pDescriptorOld->data[current_byte];
	current_byte++;

	players.gc1 = pDescriptorOld->data[current_byte];
	current_byte++;

	players.gc2 = pDescriptorOld->data[current_byte];
	current_byte++;

	players.atk = pDescriptorOld->data[current_byte] & 127;

	players.def = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.def += (pDescriptorOld->data[current_byte] << 1) & 127;

	players.gk = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;
	players.gk += (pDescriptorOld->data[current_byte] << 2) & 127;

	players.drib = pDescriptorOld->data[current_byte] >> 5;
	current_byte++;
	players.drib += (pDescriptorOld->data[current_byte] << 3) & 127;

	players.mo_fk = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.finish = pDescriptorOld->data[current_byte] & 127;

	players.lowpass = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.lowpass += (pDescriptorOld->data[current_byte] << 1) & 127;

	players.loftpass = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;
	players.loftpass += (pDescriptorOld->data[current_byte] << 2) & 127;

	players.header = pDescriptorOld->data[current_byte] >> 5;
	current_byte++;
	players.header += (pDescriptorOld->data[current_byte] << 3) & 127;

	players.form = (pDescriptorOld->data[current_byte] >> 4) & 7;

	players.b_edit_player = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;

	players.swerve = pDescriptorOld->data[current_byte] & 127;

	players.catching = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.catching += (pDescriptorOld->data[current_byte] << 1) & 127;

	players.clearing = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;
	players.clearing += (pDescriptorOld->data[current_byte] << 2) & 127;

	players.reflex = pDescriptorOld->data[current_byte] >> 5;
	current_byte++;
	players.reflex += (pDescriptorOld->data[current_byte] << 3) & 127;

	players.injury = (pDescriptorOld->data[current_byte] >> 4) & 3;
	
	//Unknown B - 1 bit

	players.b_edit_basicset = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;

	players.body_ctrl = pDescriptorOld->data[current_byte] & 127;
	/*
	players.phys_cont = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.phys_cont += (pDescriptorOld->data[current_byte] << 1) & 127;
	*/
	players.kick_pwr = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.kick_pwr += (pDescriptorOld->data[current_byte] << 1) & 127;

	players.exp_pwr = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;
	players.exp_pwr += (pDescriptorOld->data[current_byte] << 2) & 127;

	players.jump = pDescriptorOld->data[current_byte] >> 5;
	current_byte++;
	players.jump += (pDescriptorOld->data[current_byte] << 3) & 127;

	players.mo_armd = (pDescriptorOld->data[current_byte] >> 4) & 7;

	players.b_edit_regpos = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;

	players.reg_pos = pDescriptorOld->data[current_byte] & 15;
	
	//Unknown C - 1 bit

	players.play_style = pDescriptorOld->data[current_byte] >> 5;
	current_byte++;
	players.play_style += (pDescriptorOld->data[current_byte] << 3) & 31;

	players.ball_ctrl = pDescriptorOld->data[current_byte] >> 2;
	current_byte++;
	players.ball_ctrl += (pDescriptorOld->data[current_byte] << 6) & 127;

	players.ball_win = pDescriptorOld->data[current_byte] >> 1;
	current_byte++;

	players.cover = pDescriptorOld->data[current_byte] & 127;

	players.b_edit_playpos = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;

	//players.jump = pDescriptorOld->data[current_byte] & 127;

	players.mo_armr = pDescriptorOld->data[current_byte] & 7;

	players.mo_ck = (pDescriptorOld->data[current_byte] >> 3) & 7;

	players.weak_acc = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;

	players.weak_use = pDescriptorOld->data[current_byte] & 3;

	players.play_pos[0] = (pDescriptorOld->data[current_byte] >> 2) & 3;
	players.play_pos[1] = (pDescriptorOld->data[current_byte] >> 4) & 3;
	players.play_pos[2] = (pDescriptorOld->data[current_byte] >> 6) & 3;
	current_byte++;
	players.play_pos[3] = pDescriptorOld->data[current_byte] & 3;
	players.play_pos[4] = (pDescriptorOld->data[current_byte] >> 2) & 3;
	players.play_pos[5] = (pDescriptorOld->data[current_byte] >> 4) & 3;
	players.play_pos[6] = (pDescriptorOld->data[current_byte] >> 6) & 3;
	current_byte++;
	players.play_pos[7] = pDescriptorOld->data[current_byte] & 3;
	players.play_pos[8] = (pDescriptorOld->data[current_byte] >> 2) & 3;
	players.play_pos[9] = (pDescriptorOld->data[current_byte] >> 4) & 3;
	players.play_pos[10] = (pDescriptorOld->data[current_byte] >> 6) & 3;
	current_byte++;
	players.play_pos[11] = pDescriptorOld->data[current_byte] & 3;
	players.play_pos[12] = (pDescriptorOld->data[current_byte] >> 2) & 3;

	players.mo_hunchd = (pDescriptorOld->data[current_byte] >> 4) & 3;

	players.mo_hunchr = (pDescriptorOld->data[current_byte] >> 6) & 3;
	current_byte++;

	players.mo_pk = pDescriptorOld->data[current_byte] & 3;

	players.place_kick = pDescriptorOld->data[current_byte] >> 2;
	current_byte++;
	players.place_kick += (pDescriptorOld->data[current_byte] << 6) & 127;

	players.speed = pDescriptorOld->data[current_byte] >> 1;
	current_byte++;

	players.age = pDescriptorOld->data[current_byte] & 63;

	players.b_edit_ability = (pDescriptorOld->data[current_byte] >> 6) & 1;

	players.b_edit_skill = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;

	players.stamina = pDescriptorOld->data[current_byte] & 127;

	players.b_edit_style = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;

	players.b_edit_com = pDescriptorOld->data[current_byte] & 1;

	players.b_edit_motion = (pDescriptorOld->data[current_byte] >> 1) & 1;

	//Unknown D - 1/1

	players.b_base_copy = (pDescriptorOld->data[current_byte] >> 3) & 1;

	players.strong_foot = (pDescriptorOld->data[current_byte] >> 4) & 1;

	players.com_style[0] = (pDescriptorOld->data[current_byte] >> 5) & 1;
	players.com_style[1] = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.com_style[2] = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;
	players.com_style[3] = pDescriptorOld->data[current_byte] & 1;
	players.com_style[4] = (pDescriptorOld->data[current_byte] >> 1) & 1;
	players.com_style[5] = (pDescriptorOld->data[current_byte] >> 2) & 1;
	players.com_style[6] = (pDescriptorOld->data[current_byte] >> 3) & 1;

	players.play_skill[0] = (pDescriptorOld->data[current_byte] >> 4) & 1;
	players.play_skill[1] = (pDescriptorOld->data[current_byte] >> 5) & 1;
	players.play_skill[2] = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.play_skill[3] = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[4] = pDescriptorOld->data[current_byte] & 1;
	players.play_skill[5] = (pDescriptorOld->data[current_byte] >> 1) & 1;
	players.play_skill[6] = (pDescriptorOld->data[current_byte] >> 2) & 1;
	players.play_skill[7] = (pDescriptorOld->data[current_byte] >> 3) & 1;
	players.play_skill[8] = (pDescriptorOld->data[current_byte] >> 4) & 1;
	players.play_skill[9] = (pDescriptorOld->data[current_byte] >> 5) & 1;
	players.play_skill[10] = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.play_skill[11] = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[12] = pDescriptorOld->data[current_byte] & 1;
	players.play_skill[13] = (pDescriptorOld->data[current_byte] >> 1) & 1;
	players.play_skill[14] = (pDescriptorOld->data[current_byte] >> 2) & 1;
	players.play_skill[15] = (pDescriptorOld->data[current_byte] >> 3) & 1;
	players.play_skill[16] = (pDescriptorOld->data[current_byte] >> 4) & 1;
	players.play_skill[17] = (pDescriptorOld->data[current_byte] >> 5) & 1;
	players.play_skill[18] = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.play_skill[19] = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[20] = pDescriptorOld->data[current_byte] & 1;
	players.play_skill[21] = (pDescriptorOld->data[current_byte] >> 1) & 1;
	players.play_skill[22] = (pDescriptorOld->data[current_byte] >> 2) & 1;
	players.play_skill[23] = (pDescriptorOld->data[current_byte] >> 3) & 1;
	players.play_skill[24] = (pDescriptorOld->data[current_byte] >> 4) & 1;
	players.play_skill[25] = (pDescriptorOld->data[current_byte] >> 5) & 1;
	players.play_skill[26] = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.play_skill[27] = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorOld->data[current_byte]), -1, players.name, 46);
	current_byte+=46;
	/*
	if(players.id==75505) //Debug
	{
		char strcheck[16]; //DEBUG
		memcpy(strcheck, &(pDescriptorOld->data[current_byte]), 16);
		int checker=0;
	}
	*/
	char strcheck[16];
	memcpy(strcheck, &(pDescriptorOld->data[current_byte]), 16);
	strcheck[15] = 0;
	strcpy_s(players.shirt_name, 16, strcheck); //(const char*)&(pDescriptorOld->data[current_byte]));
	/*
	if(players.id>73300 && players.id<73400) //Debug
	{
		int checker=0;
	}
	*/
	current_byte+=16;
}


void fill_appearance_entry16(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	//Appearance entries
	unsigned long checkId;
	checkId = pDescriptorOld->data[current_byte];
	current_byte++;
	checkId += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	checkId += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	checkId += pDescriptorOld->data[current_byte] << 24;
	current_byte++;

	if(players.id!=checkId) return;

	players.b_edit_face = pDescriptorOld->data[current_byte] & 1;
	players.b_edit_hair = (pDescriptorOld->data[current_byte] >> 1) & 1;
	players.b_edit_phys = (pDescriptorOld->data[current_byte] >> 2) & 1;
	players.b_edit_strip = (pDescriptorOld->data[current_byte] >> 3) & 1;

	players.boot_id = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;
	players.boot_id += pDescriptorOld->data[current_byte] << 4;
	current_byte++;
	players.boot_id += (pDescriptorOld->data[current_byte] & 3) << 12;

	players.glove_id = pDescriptorOld->data[current_byte] >> 2;
	current_byte++;
	players.glove_id += (pDescriptorOld->data[current_byte] & 15) << 6;

	//Unknown B - 4/4
	current_byte++;

	players.copy_id = pDescriptorOld->data[current_byte];
	current_byte++;
	players.copy_id += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	players.copy_id += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	players.copy_id += pDescriptorOld->data[current_byte] << 24;
	current_byte++;

	players.neck_len = pDescriptorOld->data[current_byte] & 15;

	players.neck_size = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.shldr_hi = pDescriptorOld->data[current_byte] & 15;

	players.shldr_wid = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.chest = pDescriptorOld->data[current_byte] & 15;

	players.waist = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.arm_size = pDescriptorOld->data[current_byte] & 15;

	players.arm_len = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.thigh = pDescriptorOld->data[current_byte] & 15;

	players.calf = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.leg_len = pDescriptorOld->data[current_byte] & 15;

	players.head_len = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.head_wid = pDescriptorOld->data[current_byte] & 15;

	players.head_dep = pDescriptorOld->data[current_byte] >> 4;
	current_byte++;

	players.wrist_col_l = pDescriptorOld->data[current_byte] & 7;
	players.wrist_col_r = (pDescriptorOld->data[current_byte] >> 3) & 7;
	players.wrist_tape = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;

	players.spec_col = pDescriptorOld->data[current_byte] & 7;
	players.spec_style = (pDescriptorOld->data[current_byte] >> 3) & 7;
	players.sleeve = pDescriptorOld->data[current_byte] >> 6;
	current_byte++;

	players.inners = pDescriptorOld->data[current_byte] & 3;
	players.socks = (pDescriptorOld->data[current_byte] >> 2) & 3;
	players.undershorts = (pDescriptorOld->data[current_byte] >> 4) & 3;
	players.tucked = (pDescriptorOld->data[current_byte] >> 6) & 1;
	players.ankle_tape = (pDescriptorOld->data[current_byte] >> 7) & 1;
	current_byte++;

	players.gloves = pDescriptorOld->data[current_byte] & 1;
	players.gloves_col = (pDescriptorOld->data[current_byte] >> 1) & 7;
	//Unknown D
	current_byte++;

	//Unknown E
	current_byte+=22;

	players.skin_col = pDescriptorOld->data[current_byte] & 7;
	//Unknown F
	current_byte++;

	//Unknown G
	current_byte+=18;

	players.iris_col = pDescriptorOld->data[current_byte] & 15;
	//Unknown H
	current_byte++;

	//Unknown I
	current_byte+=7;
}


void fill_team_ids16(team_entry &teams, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	teams.id = pDescriptorOld->data[current_byte];
	current_byte++;
	teams.id += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	teams.id += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	teams.id += pDescriptorOld->data[current_byte] << 24;
	current_byte++;

	current_byte+=0xE;
	teams.b_edit_name = (pDescriptorOld->data[current_byte] >> 7) & 1;

	current_byte+=0x82;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorOld->data[current_byte]), -1, teams.name, 0x46);
	current_byte+=0x46;

	strcpy_s(teams.short_name, 0x4, (const char*)&(pDescriptorOld->data[current_byte]));
	//Remove non alphanumeric characters
	for(int ii=0;ii<4;ii++)
	{
		if((int)teams.short_name[ii]<33 || (int)teams.short_name[ii]>95)
			teams.short_name[ii]=(char)0;
	}
	current_byte+=0x4;

	current_byte+=0xEA;
}


void fill_team_rosters16(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	int ii, t_ind;
	unsigned long team_id, player_id;

	team_id = pDescriptorOld->data[current_byte];
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 24;
	current_byte++;

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}

	for(ii=0;ii<32;ii++)
	{
		player_id = pDescriptorOld->data[current_byte];
		current_byte++;
		player_id += pDescriptorOld->data[current_byte] << 8;
		current_byte++;
		player_id += pDescriptorOld->data[current_byte] << 16;
		current_byte++;
		player_id += pDescriptorOld->data[current_byte] << 24;
		current_byte++;

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


void fill_team_tactics16(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	int t_ind;
	unsigned long team_id;

	team_id = pDescriptorOld->data[current_byte];
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 8;
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 16;
	current_byte++;
	team_id += pDescriptorOld->data[current_byte] << 24;
	current_byte++;

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}
	current_byte+=0x1FA;

	gteams[t_ind].captain_ind = (char)pDescriptorOld->data[current_byte];
	current_byte+=0xA;
}

//-------------------------------------------------------------------------------------


void extract_player_entry16(player_entry player, int &current_byte, int &appear_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!player.b_changed || !player.b_show)
	{
		current_byte += 0x70;
		appear_byte += 0x48;
		return;
	}
	
//	unsigned char test[4];
	int cb=0;
	
	pDescriptorOld->data[current_byte] = player.id & 255;
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.id >> 8) & 255;
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.id >> 16) & 255;
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.id >> 24) & 255;
	current_byte++;
	
	current_byte += 0x6;
	
	pDescriptorOld->data[current_byte] = player.nation & 255;
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.nation >> 8) & 255;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.height;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.weight;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.gc1;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.gc2;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.atk & 127; //7/7
	
	pDescriptorOld->data[current_byte] += player.def << 7; //1/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.def >> 1) & 63; //6/7
	
	pDescriptorOld->data[current_byte] += player.gk << 6; //2/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.gk >> 2) & 31; //5/7
	
	pDescriptorOld->data[current_byte] += player.drib << 5; //3/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.drib >> 3) & 15; //4/7
	
	pDescriptorOld->data[current_byte] += player.mo_fk << 4; //4/4
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.finish & 127; //7/7
	
	pDescriptorOld->data[current_byte] += player.lowpass << 7; //1/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.lowpass >> 1) & 63; //6/7
	
	pDescriptorOld->data[current_byte] += player.loftpass << 6; //2/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.loftpass >> 2) & 31; //5/7
	
	pDescriptorOld->data[current_byte] += player.header << 5; //3/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.header >> 3) & 15; //4/7
	
	pDescriptorOld->data[current_byte] += player.form << 4; //3/3
	
	pDescriptorOld->data[current_byte] += player.b_edit_player << 7; //1/1
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.swerve & 127; //7/7
	
	pDescriptorOld->data[current_byte] += player.catching << 7; //1/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.catching >> 1) & 63; //6/7
	
	pDescriptorOld->data[current_byte] += player.clearing << 6; //2/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.clearing >> 2) & 31; //5/7
	
	pDescriptorOld->data[current_byte] += player.reflex << 5; //3/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.reflex >> 3) & 15; //4/7
	
	pDescriptorOld->data[current_byte] += player.injury << 4; //2/2
	
	//Unknown B - 1/1
	pDescriptorOld->data[current_byte] += player.b_edit_basicset << 7; //1/1
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.body_ctrl & 127; //7/7
	/*
	pDescriptorOld->data[current_byte] += player.phys_cont << 7; //1/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.phys_cont >> 1) & 63; //6/7
	*/
	pDescriptorOld->data[current_byte] += player.kick_pwr << 7; //1/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.kick_pwr >> 1) & 63; //6/7

	pDescriptorOld->data[current_byte] += player.exp_pwr << 6; //2/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.exp_pwr >> 2) & 31; //5/7

	pDescriptorOld->data[current_byte] += player.jump << 5; //3/7
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.jump >> 3) & 15; //4/7
	
	pDescriptorOld->data[current_byte] += player.mo_armd << 4; //3/3
	
	pDescriptorOld->data[current_byte] += player.b_edit_regpos << 7; //1/1
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.reg_pos & 15; //4/4

	//Unknown C - 1/1

	pDescriptorOld->data[current_byte] += (player.play_style << 5) & 255; //3/5
	current_byte++;
	pDescriptorOld->data[current_byte] = (player.play_style >> 3) & 3; //2/5

	pDescriptorOld->data[current_byte] += (player.ball_ctrl << 2) & 255; //6/7
	current_byte++;
	pDescriptorOld->data[current_byte] = player.ball_ctrl >> 6; //1/7
	
	pDescriptorOld->data[current_byte] += player.ball_win << 1; //7/7
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.cover; //7/7

	pDescriptorOld->data[current_byte] += player.b_edit_playpos << 7; //1/7
	current_byte++;

	pDescriptorOld->data[current_byte] = player.mo_armr; //3/3
	
	pDescriptorOld->data[current_byte] += player.mo_ck << 3; //3/3

	pDescriptorOld->data[current_byte] += player.weak_acc << 6; //2/2
	current_byte++;

	pDescriptorOld->data[current_byte] = player.weak_use; //2/2
	
	pDescriptorOld->data[current_byte] += player.play_pos[0] << 2; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[1] << 4; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[2] << 6; //2/2
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_pos[3]; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[4] << 2; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[5] << 4; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[6] << 6; //2/2
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_pos[7]; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[8] << 2; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[9] << 4; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[10] << 6; //2/2
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_pos[11]; //2/2
	pDescriptorOld->data[current_byte] += player.play_pos[12] << 2; //2/2
	
	pDescriptorOld->data[current_byte] += player.mo_hunchd << 4; //2/2
	
	pDescriptorOld->data[current_byte] += player.mo_hunchr << 6; //2/2
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.mo_pk; //2/2
	
	pDescriptorOld->data[current_byte] += (player.place_kick << 2) & 255; //6/7	
	current_byte++;
	pDescriptorOld->data[current_byte] = player.place_kick >> 6; //1/7
	
	pDescriptorOld->data[current_byte] += player.speed << 1; //7/7
	current_byte++;

	pDescriptorOld->data[current_byte] = player.age; //6/6

	pDescriptorOld->data[current_byte] += player.b_edit_ability << 6; //1/1
	
	pDescriptorOld->data[current_byte] += player.b_edit_skill << 7; //1/1
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.stamina; //7/7
	//uint8_t db = pDescriptorOld->data[current_byte]; //DEBUG
	pDescriptorOld->data[current_byte] += player.b_edit_style << 7; //1/1
	//db = pDescriptorOld->data[current_byte]; //DEBUG
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.b_edit_com; //1/1
	
	pDescriptorOld->data[current_byte] += player.b_edit_motion << 1; //1/1

	//Unknown D - 1/1

	pDescriptorOld->data[current_byte] += (player.b_base_copy << 3) & 248; //1/1
	
	pDescriptorOld->data[current_byte] += (player.strong_foot << 4) & 248; //1/1
	
	pDescriptorOld->data[current_byte] += (player.com_style[0] << 5) & 248; //1/1
	pDescriptorOld->data[current_byte] += (player.com_style[1] << 6) & 248; //1/1
	pDescriptorOld->data[current_byte] += (player.com_style[2] << 7) & 248; //1/1
	current_byte++;
	pDescriptorOld->data[current_byte] = player.com_style[3]; //1/1
	pDescriptorOld->data[current_byte] += player.com_style[4] << 1; //1/1
	pDescriptorOld->data[current_byte] += player.com_style[5] << 2; //1/1
	pDescriptorOld->data[current_byte] += player.com_style[6] << 3; //1/1
	
	pDescriptorOld->data[current_byte] += player.play_skill[0] << 4; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[1] << 5; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[2] << 6; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[3] << 7; //1/1
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_skill[4]; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[5] << 1; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[6] << 2; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[7] << 3; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[8] << 4; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[9] << 5; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[10] << 6; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[11] << 7; //1/1
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_skill[12]; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[13] << 1; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[14] << 2; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[15] << 3; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[16] << 4; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[17] << 5; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[18] << 6; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[19] << 7; //1/1
	current_byte++;
	pDescriptorOld->data[current_byte] = player.play_skill[20]; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[21] << 1; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[22] << 2; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[23] << 3; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[24] << 4; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[25] << 5; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[26] << 6; //1/1
	pDescriptorOld->data[current_byte] += player.play_skill[27] << 7; //1/1
	current_byte++;
	
	//char tbuffer[46];
	//memset(tbuffer, 0, 46);
	WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)&(pDescriptorOld->data[current_byte]), 46, NULL, NULL);
	//(LPSTR)&(pDescriptorOld->data[current_byte])
	current_byte+=46;
	
	char tbuffer[16];
	memset(tbuffer, 0, 16);
	//strcpy_s(tbuffer, 16, player.shirt_name);
	strncpy_s(tbuffer, 16, player.shirt_name, 16-1);
	memcpy(&(pDescriptorOld->data[current_byte]), tbuffer, 16);
	//strcpy_s((char *)&(pDescriptorOld->data[current_byte]), 16, player.shirt_name); //FIX THIS
	current_byte+=16;
	
	//Appearance entries
	//playerID
	appear_byte+=4;
	
	pDescriptorOld->data[appear_byte] = player.b_edit_face; //1/1
	pDescriptorOld->data[appear_byte] += player.b_edit_hair << 1; //1/1
	pDescriptorOld->data[appear_byte] += player.b_edit_phys << 2; //1/1
	pDescriptorOld->data[appear_byte] += player.b_edit_strip << 3; //1/1
	
	pDescriptorOld->data[appear_byte] += (player.boot_id << 4) & 240; //4/14
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.boot_id >> 4) & 255; //8/14
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.boot_id >> 12) & 3; //2/14
	
	pDescriptorOld->data[appear_byte] += (player.glove_id << 2) & 252; //6/10
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.glove_id >> 6) & 15; //4/10
	
	//Unknown B - 4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.copy_id & 255; //8/32
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.copy_id >> 8) & 255; //8/32
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.copy_id >> 16) & 255; //8/32
	appear_byte++;
	pDescriptorOld->data[appear_byte] = (player.copy_id >> 24) & 255; //8/32
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.neck_len; //4/4
	
	pDescriptorOld->data[appear_byte] += player.neck_size << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.shldr_hi; //4/4
	
	pDescriptorOld->data[appear_byte] += player.shldr_wid << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.chest; //4/4
	
	pDescriptorOld->data[appear_byte] += player.waist << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.arm_size; //4/4
	
	pDescriptorOld->data[appear_byte] += player.arm_len << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.thigh; //4/4
	
	pDescriptorOld->data[appear_byte] += player.calf << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.leg_len; //4/4
	
	pDescriptorOld->data[appear_byte] += player.head_len << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.head_wid; //4/4
	
	pDescriptorOld->data[appear_byte] += player.head_dep << 4; //4/4
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.wrist_col_l; //3/3
	pDescriptorOld->data[appear_byte] += player.wrist_col_r << 3; //3/3
	pDescriptorOld->data[appear_byte] += player.wrist_tape << 6; //2/2
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.spec_col; //3/3
	pDescriptorOld->data[appear_byte] += player.spec_style << 3; //3/3
	pDescriptorOld->data[appear_byte] += player.sleeve << 6; //2/2
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.inners; //2/2
	pDescriptorOld->data[appear_byte] += player.socks << 2; //2/2
	pDescriptorOld->data[appear_byte] += player.undershorts << 4; //2/2
	pDescriptorOld->data[appear_byte] += player.tucked << 6; //1/1
	pDescriptorOld->data[appear_byte] += player.ankle_tape << 7; //1/1
	appear_byte++;
	
	pDescriptorOld->data[appear_byte] = player.gloves; //1/1
	pDescriptorOld->data[appear_byte] += player.gloves_col << 1; //3/3
	//Unknown D - 4/4
	appear_byte++;
	
	//Unknown E - 22 bytes
	appear_byte+=22;
	
	pDescriptorOld->data[appear_byte] = player.skin_col; //3/3
	//Unknown F - 5/5
	appear_byte++;
	
	//Unknown G - 18 bytes
	appear_byte+=18;
	
	pDescriptorOld->data[appear_byte] = player.iris_col; //4/4
	//Unknown H - 4/4
	appear_byte++;
	
	//Unknown I - 7 bytes
	appear_byte+=7;
	/*
	char strcheck[0x72]; //DEBUG
	memcpy(strcheck, &(pDescriptorOld->data[current_byte-0x70]), 0x70);
	int t2=0;
	*/
}


void extract_team_info16(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed || !team.b_show)
	{
		current_byte += 0x1C8;
		return;
	}
	
	pDescriptorOld->data[current_byte] = team.id & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++;
	
	current_byte+=0xE;
	pDescriptorOld->data[current_byte] = pDescriptorOld->data[current_byte] | (team.b_edit_name << 7);

	current_byte+=0x82;
	
	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR)&(pDescriptorOld->data[current_byte]), 0x46, NULL, NULL);
	current_byte+=0x46;
	
	strcpy_s((char *)&(pDescriptorOld->data[current_byte]), 0x4, team.short_name);
	current_byte+=0x4;
	
	current_byte+=0xEA;
}


void extract_teamplayer_info16(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed || !team.b_show)
	{
		current_byte += 0xA4;
		return;
	}
	
	pDescriptorOld->data[current_byte] = team.id & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++;
	
	int ii;
	for(ii=0;ii<32;ii++)
	{
		pDescriptorOld->data[current_byte] = team.players[ii] & 255; //8/32
		current_byte++;
		pDescriptorOld->data[current_byte] = (team.players[ii] >> 8) & 255; //8/32
		current_byte++;
		pDescriptorOld->data[current_byte] = (team.players[ii] >> 16) & 255; //8/32
		current_byte++;
		pDescriptorOld->data[current_byte] = (team.players[ii] >> 24) & 255; //8/32
		current_byte++;
	}
	
	for(ii=0;ii<32;ii++)
	{
		pDescriptorOld->data[current_byte] = team.numbers[ii] & 255; //8/32
		current_byte++;
	}
}


void extract_team_tactics16(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x208;
		return;
	}
	
	pDescriptorOld->data[current_byte] = team.id & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorOld->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++;
	
	current_byte+=0x1FA;
	pDescriptorOld->data[current_byte] = team.captain_ind;

	current_byte+=0xA;
}