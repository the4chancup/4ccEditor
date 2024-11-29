#include "editor.h"

void fill_player_entry16(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	players.id = read_dataOld(0, 4 * 8, current_byte, pDescriptorOld);
	/*
	if(players.id==73301)//Debug
	{
		int d3=0;
	}
	*/
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
	/*
	players.phys_cont = pDescriptorOld->data[current_byte] >> 7;
	current_byte++;
	players.phys_cont += (pDescriptorOld->data[current_byte] << 1) & 127;
	*/
	players.kick_pwr = read_dataOld(7, 7, current_byte, pDescriptorOld);

	players.exp_pwr = read_dataOld(6, 7, current_byte, pDescriptorOld);

	players.jump = read_dataOld(5, 7, current_byte, pDescriptorOld);

	players.mo_armd = read_dataOld(4, 3, current_byte, pDescriptorOld);

	players.b_edit_regpos = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.reg_pos = read_dataOld(0, 4, current_byte, pDescriptorOld);
	
	//Unknown C - 1 bit

	players.play_style = read_dataOld(5, 5, current_byte, pDescriptorOld);

	players.ball_ctrl = read_dataOld(2, 7, current_byte, pDescriptorOld);

	players.ball_win = read_dataOld(1, 7, current_byte, pDescriptorOld);

	players.cover = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.b_edit_playpos = read_dataOld(7, 1, current_byte, pDescriptorOld);

	//players.jump = pDescriptorOld->data[current_byte] & 127;

	players.mo_armr = read_dataOld(0, 3, current_byte, pDescriptorOld);

	players.mo_ck = read_dataOld(3, 3, current_byte, pDescriptorOld);

	players.weak_acc = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.weak_use = read_dataOld(0, 2, current_byte, pDescriptorOld);

	players.play_pos[0] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[1] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[2] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[3] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[4] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[5] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[6] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[7] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[8] = read_dataOld(2, 2, current_byte, pDescriptorOld);
	players.play_pos[9] = read_dataOld(4, 2, current_byte, pDescriptorOld);
	players.play_pos[10] = read_dataOld(6, 2, current_byte, pDescriptorOld);
	players.play_pos[11] = read_dataOld(0, 2, current_byte, pDescriptorOld);
	players.play_pos[12] = read_dataOld(2, 2, current_byte, pDescriptorOld);

	players.mo_hunchd = read_dataOld(4, 2, current_byte, pDescriptorOld);

	players.mo_hunchr = read_dataOld(6, 2, current_byte, pDescriptorOld);

	players.mo_pk = read_dataOld(0, 2, current_byte, pDescriptorOld);

	players.place_kick = read_dataOld(2, 7, current_byte, pDescriptorOld);

	players.speed = read_dataOld(1, 7, current_byte, pDescriptorOld);

	players.age = read_dataOld(0, 6, current_byte, pDescriptorOld);

	players.b_edit_ability = read_dataOld(6, 1, current_byte, pDescriptorOld);

	players.b_edit_skill = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.stamina = read_dataOld(0, 7, current_byte, pDescriptorOld);

	players.b_edit_style = read_dataOld(7, 1, current_byte, pDescriptorOld);

	players.b_edit_com = read_dataOld(0, 1, current_byte, pDescriptorOld);

	players.b_edit_motion = read_dataOld(1, 1, current_byte, pDescriptorOld);

	//Unknown D - 1/1

	players.b_base_copy = read_dataOld(3, 1, current_byte, pDescriptorOld);

	players.strong_foot = read_dataOld(4, 1, current_byte, pDescriptorOld);

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

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorOld->data[current_byte]), -1, players.name, 46);
	current_byte+=46;

	strcpy_s(players.shirt_name, 16, (const char*)&(pDescriptorOld->data[current_byte]));
	current_byte+=16;
}


void fill_appearance_entry16(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	//Appearance entries
	unsigned long checkId;
	checkId = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

	if(players.id!=checkId) return;

	players.b_edit_face = read_dataOld(0, 1, current_byte, pDescriptorOld);
	players.b_edit_hair = read_dataOld(1, 1, current_byte, pDescriptorOld);
	players.b_edit_phys = read_dataOld(2, 1, current_byte, pDescriptorOld);
	players.b_edit_strip = read_dataOld(3, 1, current_byte, pDescriptorOld);

	players.boot_id = read_dataOld(4, 14, current_byte, pDescriptorOld);

	players.glove_id = read_dataOld(2, 14, current_byte, pDescriptorOld); //Extend to be 14 bits, using Unk B space

	players.copy_id = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

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


void fill_team_ids16(team_entry &teams, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	teams.id = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

	current_byte+=0xE;
	teams.b_edit_name = read_dataOld(0, 1, current_byte, pDescriptorOld); //(pDescriptorOld->data[current_byte]) & 1;

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

	team_id = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}

	for(ii=0;ii<32;ii++)
	{
		player_id = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

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

	team_id = read_dataOld(0, 4*8, current_byte, pDescriptorOld);

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
	
	write_dataOld(player.id, 0, 4*8, current_byte, pDescriptorOld);
	
	current_byte += 0x6;
	
	write_dataOld(player.nation, 0, 2 * 8, current_byte, pDescriptorOld);
	
	pDescriptorOld->data[current_byte] = player.height;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.weight;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.gc1;
	current_byte++;
	
	pDescriptorOld->data[current_byte] = player.gc2;
	current_byte++;
	
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

	write_dataOld(player.kick_pwr, 7, 7, current_byte, pDescriptorOld);

	write_dataOld(player.exp_pwr, 6, 7, current_byte, pDescriptorOld);

	write_dataOld(player.jump, 5, 7, current_byte, pDescriptorOld);

	write_dataOld(player.mo_armd, 4, 3, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_regpos, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.reg_pos, 0, 4, current_byte, pDescriptorOld);

	//Unknown C - 1 bit

	write_dataOld(player.play_style, 5, 5, current_byte, pDescriptorOld);

	write_dataOld(player.ball_ctrl, 2, 7, current_byte, pDescriptorOld);

	write_dataOld(player.ball_win, 1, 7, current_byte, pDescriptorOld);

	write_dataOld(player.cover, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_playpos, 7, 1, current_byte, pDescriptorOld);

	//player.jump = pDescriptorOld->data[current_byte] & 127;

	write_dataOld(player.mo_armr, 0, 3, current_byte, pDescriptorOld);

	write_dataOld(player.mo_ck, 3, 3, current_byte, pDescriptorOld);

	write_dataOld(player.weak_acc, 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.weak_use, 0, 2, current_byte, pDescriptorOld);

	write_dataOld(player.play_pos[0], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[1], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[2], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[3], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[4], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[5], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[6], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[7], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[8], 2, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[9], 4, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[10], 6, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[11], 0, 2, current_byte, pDescriptorOld);
	write_dataOld(player.play_pos[12], 2, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_hunchd, 4, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_hunchr, 6, 2, current_byte, pDescriptorOld);

	write_dataOld(player.mo_pk, 0, 2, current_byte, pDescriptorOld);

	write_dataOld(player.place_kick, 2, 7, current_byte, pDescriptorOld);

	write_dataOld(player.speed, 1, 7, current_byte, pDescriptorOld);

	write_dataOld(player.age, 0, 6, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_ability, 6, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_skill, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.stamina, 0, 7, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_style, 7, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_com, 0, 1, current_byte, pDescriptorOld);

	write_dataOld(player.b_edit_motion, 1, 1, current_byte, pDescriptorOld);

	//Unknown D - 1/1

	write_dataOld(player.b_base_copy, 3, 1, current_byte, pDescriptorOld);

	write_dataOld(player.strong_foot, 4, 1, current_byte, pDescriptorOld);

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
	
	uint8_t nameBuffer[46];
	memset(nameBuffer, 0, sizeof(nameBuffer));
	int len = WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)nameBuffer, 45, NULL, NULL); //set byte limit to 45 to ensure null termination of truncated strings
	memcpy(&(pDescriptorOld->data[current_byte]), nameBuffer, 46);
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
	
	write_dataOld(player.b_edit_face, 0, 1, appear_byte, pDescriptorOld);
	write_dataOld(player.b_edit_hair, 1, 1, appear_byte, pDescriptorOld);
	write_dataOld(player.b_edit_phys, 2, 1, appear_byte, pDescriptorOld);
	write_dataOld(player.b_edit_strip, 3, 1, appear_byte, pDescriptorOld);

	write_dataOld(player.boot_id, 4, 14, appear_byte, pDescriptorOld);

	write_dataOld(player.glove_id, 2, 14, appear_byte, pDescriptorOld); //Extend to be 14 bits, using Unk B space

	write_dataOld(player.copy_id, 0, 4 * 8, appear_byte, pDescriptorOld);

	write_dataOld(player.neck_len, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.neck_size, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.shldr_hi, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.shldr_wid, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.chest, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.waist, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.arm_size, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.arm_len, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.thigh, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.calf, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.leg_len, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.head_len, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.head_wid, 0, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.head_dep, 4, 4, appear_byte, pDescriptorOld);

	write_dataOld(player.wrist_col_l, 0, 3, appear_byte, pDescriptorOld);
	write_dataOld(player.wrist_col_r, 3, 3, appear_byte, pDescriptorOld);
	write_dataOld(player.wrist_tape, 6, 2, appear_byte, pDescriptorOld);

	write_dataOld(player.spec_col, 0, 3, appear_byte, pDescriptorOld);
	write_dataOld(player.spec_style, 3, 3, appear_byte, pDescriptorOld);
	write_dataOld(player.sleeve, 6, 2, appear_byte, pDescriptorOld);

	write_dataOld(player.inners, 0, 2, appear_byte, pDescriptorOld);
	write_dataOld(player.socks, 2, 2, appear_byte, pDescriptorOld);
	write_dataOld(player.undershorts, 4, 2, appear_byte, pDescriptorOld);
	write_dataOld(player.untucked, 6, 1, appear_byte, pDescriptorOld);
	write_dataOld(player.ankle_tape, 7, 1, appear_byte, pDescriptorOld);

	write_dataOld(player.gloves, 0, 1, appear_byte, pDescriptorOld);
	write_dataOld(player.gloves_col, 1, 3, appear_byte, pDescriptorOld);
	//Unknown D
	appear_byte++;

	//Unknown E
	appear_byte += 22;

	write_dataOld(player.skin_col, 0, 3, appear_byte, pDescriptorOld);
	//Unknown F
	appear_byte++;

	//Unknown G
	appear_byte += 18;

	write_dataOld(player.iris_col, 0, 4, appear_byte, pDescriptorOld);
	//Unknown H
	appear_byte++;

	//Unknown I
	appear_byte += 7;
}


void extract_team_info16(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed || !team.b_show)
	{
		current_byte += 0x1C8;
		return;
	}
	
	write_dataOld(team.id, 0, 4 * 8, current_byte, pDescriptorOld); //0x0-0x4
	
	current_byte+=0xE;
	write_dataOld(team.b_edit_name, 0, 1, current_byte, pDescriptorOld); //0x12:0

	current_byte+=0x82;
	/*Check these before enabling:
	current_byte+=0x6; //0x18
	write_dataOld(teams.strip1Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x18
	write_dataOld(teams.strip1TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip2Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x1C
	write_dataOld(teams.strip2TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip3Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x20
	write_dataOld(teams.strip3TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip4Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x24
	write_dataOld(teams.strip4TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip5Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x2C
	write_dataOld(teams.strip5TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip6Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x30
	write_dataOld(teams.strip6TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip7Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x34
	write_dataOld(teams.strip7TeamId, 0, 3 * 8, current_byte, pDescriptorOld);
	write_dataOld(teams.strip8Number, 0, 1 * 8, current_byte, pDescriptorOld); //0x3C
	write_dataOld(teams.strip8TeamId, 0, 3 * 8, current_byte, pDescriptorOld);

	current_byte+=0x54; //0x94
	*/
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


void extract_team_tactics16(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorOld* pDescriptorOld = (FileDescriptorOld*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x208;
		return;
	}
	
	write_dataOld(team.id, 0, 4 * 8, current_byte, pDescriptorOld);

	current_byte+=0x1FA;
	pDescriptorOld->data[current_byte] = team.captain_ind;

	current_byte+=0xA;
}