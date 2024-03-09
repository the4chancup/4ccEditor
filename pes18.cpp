#include "editor.h"

void fill_player_entry18(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	players.id = pDescriptorNew->data[current_byte];
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 8;
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 16;
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 24;
	current_byte++;

	current_byte += 0x6;

	players.nation = pDescriptorNew->data[current_byte];
	current_byte++;
	players.nation += pDescriptorNew->data[current_byte] << 8;
	current_byte++;

	players.height = pDescriptorNew->data[current_byte];
	current_byte++;

	players.weight = pDescriptorNew->data[current_byte];
	current_byte++;

	players.gc1 = pDescriptorNew->data[current_byte];
	current_byte++;

	players.gc2 = pDescriptorNew->data[current_byte];
	current_byte++;

	players.atk = pDescriptorNew->data[current_byte] & 127;

	players.def = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.def += (pDescriptorNew->data[current_byte] << 1) & 127;

	players.gk = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;
	players.gk += (pDescriptorNew->data[current_byte] << 2) & 127;

	players.drib = pDescriptorNew->data[current_byte] >> 5;
	current_byte++;
	players.drib += (pDescriptorNew->data[current_byte] << 3) & 127;

	players.mo_fk = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.finish = pDescriptorNew->data[current_byte] & 127;

	players.lowpass = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.lowpass += (pDescriptorNew->data[current_byte] << 1) & 127;

	players.loftpass = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;
	players.loftpass += (pDescriptorNew->data[current_byte] << 2) & 127;

	players.header = pDescriptorNew->data[current_byte] >> 5;
	current_byte++;
	players.header += (pDescriptorNew->data[current_byte] << 3) & 127;

	players.form = (pDescriptorNew->data[current_byte] >> 4) & 7;

	players.b_edit_player = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;

	players.swerve = pDescriptorNew->data[current_byte] & 127;

	players.catching = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.catching += (pDescriptorNew->data[current_byte] << 1) & 127;

	players.clearing = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;
	players.clearing += (pDescriptorNew->data[current_byte] << 2) & 127;

	players.reflex = pDescriptorNew->data[current_byte] >> 5;
	current_byte++;
	players.reflex += (pDescriptorNew->data[current_byte] << 3) & 127;

	players.injury = (pDescriptorNew->data[current_byte] >> 4) & 3;
	
	//Unknown B - 1 bit

	players.b_edit_basicset = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;

	players.body_ctrl = pDescriptorNew->data[current_byte] & 127;

	players.phys_cont = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.phys_cont += (pDescriptorNew->data[current_byte] << 1) & 127;

	players.kick_pwr = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;
	players.kick_pwr += (pDescriptorNew->data[current_byte] << 2) & 127;

	players.exp_pwr = pDescriptorNew->data[current_byte] >> 5;
	current_byte++;
	players.exp_pwr += (pDescriptorNew->data[current_byte] << 3) & 127;

	//-------------------Changes start here
	
	//Unknown motion - 3 bits (pDescriptorNew->data[current_byte] >> 4) & 7;

	players.b_edit_regpos = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;

	players.age = pDescriptorNew->data[current_byte] & 63;

	players.reg_pos = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;
	players.reg_pos += (pDescriptorNew->data[current_byte] << 2) & 12;
	
	//Unknown C - 1 bit

//	if(players.id == 73301)
//	{
//		int test1 = pDescriptorNew->data[current_byte] >> 3;
//		test1 = 0;
//	}

	players.play_style = pDescriptorNew->data[current_byte] >> 3;
	current_byte++;

	players.ball_ctrl = pDescriptorNew->data[current_byte] & 127;

	players.ball_win = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.ball_win += (pDescriptorNew->data[current_byte] << 1) & 127;

	players.weak_acc = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;

	players.jump = pDescriptorNew->data[current_byte] & 127;

	players.mo_armd = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.mo_armd += (pDescriptorNew->data[current_byte] << 1) & 3;

	players.mo_armr = (pDescriptorNew->data[current_byte] >> 2) & 7;

//	if(current_byte==138525 || current_byte==138526)
//	{
//		int test3=0;
//	}

	players.mo_ck = pDescriptorNew->data[current_byte] >> 5;
	current_byte++;

	players.cover = pDescriptorNew->data[current_byte] & 127;

	players.weak_use = (pDescriptorNew->data[current_byte] >> 7);
	current_byte++;
	players.weak_use += (pDescriptorNew->data[current_byte] << 1) & 3;

	players.play_pos[0] = (pDescriptorNew->data[current_byte] >> 1) & 3;
	players.play_pos[1] = (pDescriptorNew->data[current_byte] >> 3) & 3;
	players.play_pos[2] = (pDescriptorNew->data[current_byte] >> 5) & 3;
	players.b_edit_playpos = (pDescriptorNew->data[current_byte] >> 7);
	current_byte++;
	
	players.play_pos[4] = (pDescriptorNew->data[current_byte]) & 3;
	players.play_pos[5] = (pDescriptorNew->data[current_byte] >> 2) & 3;
	players.play_pos[6] = (pDescriptorNew->data[current_byte] >> 4) & 3;
	players.play_pos[7] = (pDescriptorNew->data[current_byte] >> 6) & 3;
	current_byte++;

	players.play_pos[8] = (pDescriptorNew->data[current_byte]) & 3;
	players.play_pos[9] = (pDescriptorNew->data[current_byte] >> 2) & 3;
	players.play_pos[10] = (pDescriptorNew->data[current_byte] >> 4) & 3;
	players.play_pos[11] = (pDescriptorNew->data[current_byte] >> 6) & 3;
	current_byte++;

	players.play_pos[12] = (pDescriptorNew->data[current_byte]) & 3;
	
	players.mo_hunchd = (pDescriptorNew->data[current_byte] >> 2) & 3;

	players.mo_hunchr = (pDescriptorNew->data[current_byte] >> 4) & 3;

	players.mo_pk = (pDescriptorNew->data[current_byte] >> 6) & 3;
	current_byte++;

	players.place_kick = pDescriptorNew->data[current_byte] & 127;

	players.b_edit_ability = (pDescriptorNew->data[current_byte] >> 7);
	current_byte++;

	players.stamina = pDescriptorNew->data[current_byte] & 127;

	players.play_pos[3] = (pDescriptorNew->data[current_byte] >> 7);
	current_byte++;
	players.play_pos[3] += (pDescriptorNew->data[current_byte] << 1) & 3;

	players.speed = pDescriptorNew->data[current_byte] >> 1;
	current_byte++;

	players.b_edit_skill = (pDescriptorNew->data[current_byte]) & 1;

	players.b_edit_style = (pDescriptorNew->data[current_byte] >> 1) & 1;

	players.b_edit_com = (pDescriptorNew->data[current_byte] >> 2) & 1;

	players.b_edit_motion = (pDescriptorNew->data[current_byte] >> 3) & 1;

	players.b_base_copy = (pDescriptorNew->data[current_byte] >> 4) & 1;
	//Unknown D - 1/1
	
	players.strong_foot = (pDescriptorNew->data[current_byte] >> 6) & 1;
	//Unknown E - 1/1
	current_byte++;

	players.com_style[0] = (pDescriptorNew->data[current_byte]) & 1;
	players.com_style[1] = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.com_style[2] = (pDescriptorNew->data[current_byte] >> 2) & 1;
	players.com_style[3] = (pDescriptorNew->data[current_byte] >> 3) & 1;
	players.com_style[4] = (pDescriptorNew->data[current_byte] >> 4) & 1;
	players.com_style[5] = (pDescriptorNew->data[current_byte] >> 5) & 1;
	players.com_style[6] = (pDescriptorNew->data[current_byte] >> 6) & 1;

	players.play_skill[0] = (pDescriptorNew->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[1] = (pDescriptorNew->data[current_byte]) & 1;
	players.play_skill[2] = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.play_skill[3] = (pDescriptorNew->data[current_byte] >> 2) & 1;
	players.play_skill[4] = (pDescriptorNew->data[current_byte] >> 3) & 1;
	players.play_skill[5] = (pDescriptorNew->data[current_byte] >> 4) & 1;
	players.play_skill[6] = (pDescriptorNew->data[current_byte] >> 5) & 1;
	players.play_skill[7] = (pDescriptorNew->data[current_byte] >> 6) & 1;
	players.play_skill[8] = (pDescriptorNew->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[9] = (pDescriptorNew->data[current_byte]) & 1;
	players.play_skill[10] = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.play_skill[11] = (pDescriptorNew->data[current_byte] >> 2) & 1;
	players.play_skill[12] = (pDescriptorNew->data[current_byte] >> 3) & 1;
	players.play_skill[13] = (pDescriptorNew->data[current_byte] >> 4) & 1;
	players.play_skill[14] = (pDescriptorNew->data[current_byte] >> 5) & 1;
	players.play_skill[15] = (pDescriptorNew->data[current_byte] >> 6) & 1;
	players.play_skill[16] = (pDescriptorNew->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[17] = (pDescriptorNew->data[current_byte]) & 1;
	players.play_skill[18] = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.play_skill[19] = (pDescriptorNew->data[current_byte] >> 2) & 1;
	players.play_skill[20] = (pDescriptorNew->data[current_byte] >> 3) & 1;
	players.play_skill[21] = (pDescriptorNew->data[current_byte] >> 4) & 1;
	players.play_skill[22] = (pDescriptorNew->data[current_byte] >> 5) & 1;
	players.play_skill[23] = (pDescriptorNew->data[current_byte] >> 6) & 1;
	players.play_skill[24] = (pDescriptorNew->data[current_byte] >> 7) & 1;
	current_byte++;
	players.play_skill[25] = (pDescriptorNew->data[current_byte]) & 1;
	players.play_skill[26] = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.play_skill[27] = (pDescriptorNew->data[current_byte] >> 2) & 1;

	//Unknown F - 5/8
	current_byte++;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorNew->data[current_byte]), -1, players.name, 46);
	current_byte+=46;

	strcpy_s(players.shirt_name, 18, (const char*)&(pDescriptorNew->data[current_byte]));
	current_byte+=18;

	//Appearance entries
	//playerID
	current_byte+=4;

	players.b_edit_face = pDescriptorNew->data[current_byte] & 1;
	players.b_edit_hair = (pDescriptorNew->data[current_byte] >> 1) & 1;
	players.b_edit_phys = (pDescriptorNew->data[current_byte] >> 2) & 1;
	players.b_edit_strip = (pDescriptorNew->data[current_byte] >> 3) & 1;

	players.boot_id = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;
	players.boot_id += pDescriptorNew->data[current_byte] << 4;
	current_byte++;
	players.boot_id += (pDescriptorNew->data[current_byte] & 3) << 12;

	players.glove_id = pDescriptorNew->data[current_byte] >> 2;
	current_byte++;
	//players.glove_id += (pDescriptorNew->data[current_byte] & 15) << 6;
	players.glove_id += (pDescriptorNew->data[current_byte]) << 6; //Extend to be 14 bits, using Unk B space

	//Unknown B - 4/4
	current_byte++;

	players.copy_id = pDescriptorNew->data[current_byte];
	current_byte++;
	players.copy_id += pDescriptorNew->data[current_byte] << 8;
	current_byte++;
	players.copy_id += pDescriptorNew->data[current_byte] << 16;
	current_byte++;
	players.copy_id += pDescriptorNew->data[current_byte] << 24;
	current_byte++;

	players.neck_len = pDescriptorNew->data[current_byte] & 15;

	players.neck_size = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.shldr_hi = pDescriptorNew->data[current_byte] & 15;

	players.shldr_wid = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.chest = pDescriptorNew->data[current_byte] & 15;

	players.waist = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.arm_size = pDescriptorNew->data[current_byte] & 15;

	players.arm_len = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.thigh = pDescriptorNew->data[current_byte] & 15;

	players.calf = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.leg_len = pDescriptorNew->data[current_byte] & 15;

	players.head_len = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.head_wid = pDescriptorNew->data[current_byte] & 15;

	players.head_dep = pDescriptorNew->data[current_byte] >> 4;
	current_byte++;

	players.wrist_col_l = pDescriptorNew->data[current_byte] & 7;
	players.wrist_col_r = (pDescriptorNew->data[current_byte] >> 3) & 7;
	players.wrist_tape = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;

	players.spec_col = pDescriptorNew->data[current_byte] & 7;
	players.spec_style = (pDescriptorNew->data[current_byte] >> 3) & 7;
	players.sleeve = pDescriptorNew->data[current_byte] >> 6;
	current_byte++;

	players.inners = pDescriptorNew->data[current_byte] & 3;
	players.socks = (pDescriptorNew->data[current_byte] >> 2) & 3;
	players.undershorts = (pDescriptorNew->data[current_byte] >> 4) & 3;
	players.tucked = (pDescriptorNew->data[current_byte] >> 6) & 1;
	players.ankle_tape = (pDescriptorNew->data[current_byte] >> 7) & 1;
	current_byte++;

	players.gloves = pDescriptorNew->data[current_byte] & 1;
	players.gloves_col = (pDescriptorNew->data[current_byte] >> 1) & 7;
	//Unknown D
	current_byte++;

	//Unknown E
	current_byte+=22;

	players.skin_col = pDescriptorNew->data[current_byte] & 7;
	//No custom skin in 18
	if(players.skin_col==7)
	{
        players.skin_col=0;
		players.b_changed=true;
	}
	//Unknown F
	current_byte++;

	//Unknown G
	current_byte+=18;

	players.iris_col = pDescriptorNew->data[current_byte] & 15;
	//Unknown H
	current_byte++;

	//Unknown I
	current_byte+=7;
}


void fill_team_ids18(team_entry &teams, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	teams.id = pDescriptorNew->data[current_byte];
	current_byte++; //1
	teams.id += pDescriptorNew->data[current_byte] << 8;
	current_byte++; //2
	teams.id += pDescriptorNew->data[current_byte] << 16;
	current_byte++; //3
	teams.id += pDescriptorNew->data[current_byte] << 24;
	current_byte++; //4

	current_byte+=0xE; //12
	teams.color1_red = (pDescriptorNew->data[current_byte]) & 63;

	teams.color1_green = (pDescriptorNew->data[current_byte] >> 6);
	current_byte++; //13
	teams.color1_green += (pDescriptorNew->data[current_byte] << 2) & 63;
	
	current_byte++; //14
	teams.color2_red = (pDescriptorNew->data[current_byte]) & 63;
	
	teams.color2_green = (pDescriptorNew->data[current_byte] >> 6);
	current_byte++; //15
	teams.color2_green += (pDescriptorNew->data[current_byte] << 2) & 63;
	
	teams.color2_blue = (pDescriptorNew->data[current_byte] >> 4);
	current_byte++; //16
	teams.color2_blue += (pDescriptorNew->data[current_byte] << 4) & 63;

	teams.color1_blue = (pDescriptorNew->data[current_byte] >> 2);
	

	//current_byte+=0x94;
	current_byte+=0x3; //19
	teams.b_edit_name = (pDescriptorNew->data[current_byte] >> 4) & 1;

	current_byte+=0x7F;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorNew->data[current_byte]), -1, teams.name, 0x46);
	current_byte+=0x46;

	strcpy_s(teams.short_name, 0x4, (const char*)&(pDescriptorNew->data[current_byte]));
	//Remove non alphanumeric characters
	for(int ii=0;ii<4;ii++)
	{
		if((int)teams.short_name[ii]<33 || (int)teams.short_name[ii]>95)
			teams.short_name[ii]=(char)0;
	}
	current_byte+=0x4;

	current_byte+=0xFE;
}


void fill_team_rosters18(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	int ii, t_ind;
	unsigned long team_id, player_id;

	team_id = pDescriptorNew->data[current_byte];
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 8;
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 16;
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 24;
	current_byte++;

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}

	for(ii=0;ii<32;ii++)
	{
		player_id = pDescriptorNew->data[current_byte];
		current_byte++;
		player_id += pDescriptorNew->data[current_byte] << 8;
		current_byte++;
		player_id += pDescriptorNew->data[current_byte] << 16;
		current_byte++;
		player_id += pDescriptorNew->data[current_byte] << 24;
		current_byte++;

		gteams[t_ind].players[ii] = player_id;
		if(player_id) gteams[t_ind].num_on_team++; //new
	}
	//Hide team with no players
	if(gteams[t_ind].players[0] == 0) 
		gteams[t_ind].b_show = false;

	for(ii=0;ii<32;ii++)
	{
		gteams[t_ind].numbers[ii] = pDescriptorNew->data[current_byte];
		current_byte++;
	}
}


void fill_team_tactics18(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	int t_ind;
	unsigned long team_id;

	team_id = pDescriptorNew->data[current_byte];
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 8;
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 16;
	current_byte++;
	team_id += pDescriptorNew->data[current_byte] << 24;
	current_byte++;

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}
	//current_byte+=0x209;
	current_byte+=0x1E0;

	//Starting lineup
	for(int ii=0; ii<11; ii++)
	{
		gteams[t_ind].starting11[ii] = pDescriptorNew->data[current_byte];
		current_byte++;
	}
	current_byte+=0x1E;

	gteams[t_ind].captain_ind = (char)pDescriptorNew->data[current_byte];
	current_byte+=0x67;
}

//---------------------------------------------------------------------------------------------------------


void extract_player_entry18(player_entry player, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!player.b_changed)
	{
		current_byte += 0xBC;
		return;
	}
	
//	unsigned char test[4];
	int cb=0;
	
	pDescriptorNew->data[current_byte] = player.id & 255;
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.id >> 8) & 255;
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.id >> 16) & 255;
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.id >> 24) & 255;
	current_byte++;
	
	current_byte += 0x6;
	
	pDescriptorNew->data[current_byte] = player.nation & 255;
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.nation >> 8) & 255;
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.height;
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.weight;
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.gc1;
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.gc2;
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.atk & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.def << 7; //1/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.def >> 1) & 63; //6/7
	
	pDescriptorNew->data[current_byte] += player.gk << 6; //2/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.gk >> 2) & 31; //5/7
	
	pDescriptorNew->data[current_byte] += player.drib << 5; //3/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.drib >> 3) & 15; //4/7
	
	pDescriptorNew->data[current_byte] += player.mo_fk << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.finish & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.lowpass << 7; //1/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.lowpass >> 1) & 63; //6/7
	
	pDescriptorNew->data[current_byte] += player.loftpass << 6; //2/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.loftpass >> 2) & 31; //5/7
	
	pDescriptorNew->data[current_byte] += player.header << 5; //3/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.header >> 3) & 15; //4/7
	
	pDescriptorNew->data[current_byte] += player.form << 4; //3/3
	
	pDescriptorNew->data[current_byte] += player.b_edit_player << 7; //1/1
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.swerve & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.catching << 7; //1/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.catching >> 1) & 63; //6/7
	
	pDescriptorNew->data[current_byte] += player.clearing << 6; //2/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.clearing >> 2) & 31; //5/7
	
	pDescriptorNew->data[current_byte] += player.reflex << 5; //3/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.reflex >> 3) & 15; //4/7
	
	pDescriptorNew->data[current_byte] += player.injury << 4; //2/2
	
	//Unknown B - 1/1
	pDescriptorNew->data[current_byte] += player.b_edit_basicset << 7; //1/1
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.body_ctrl & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.phys_cont << 7; //1/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.phys_cont >> 1) & 63; //6/7
	
	pDescriptorNew->data[current_byte] += player.kick_pwr << 6; //2/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.kick_pwr >> 2) & 31; //5/7

	pDescriptorNew->data[current_byte] += player.exp_pwr << 5; //3/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.exp_pwr >> 3) & 15; //4/7
	
	//pDescriptorNew->data[current_byte] += player.mo_armd << 4; //3/3
	
	pDescriptorNew->data[current_byte] += player.b_edit_regpos << 7; //1/1
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.age & 63; //6/6
	
	pDescriptorNew->data[current_byte] += player.reg_pos << 6; //2/4
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.reg_pos >> 2) & 3; //2/4

	//Unknown C - 1/1
	pDescriptorNew->data[current_byte] += (player.play_style << 3); //5/5
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.ball_ctrl & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.ball_win << 7; //1/7
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.ball_win >> 1) & 63; //6/7
	
	pDescriptorNew->data[current_byte] += player.weak_acc << 6; //2/2
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.jump & 127; //7/7
	
	pDescriptorNew->data[current_byte] += player.mo_armd << 7; //1/3
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.mo_armd >> 1) & 3; //2/3
	
	pDescriptorNew->data[current_byte] += (player.mo_armr << 2) & 31; //3/3 FIX IN 17, 16 
	
	pDescriptorNew->data[current_byte] += (player.mo_ck << 5); //3/3
	current_byte++;

	pDescriptorNew->data[current_byte] = (player.cover) & 127; //7/7

	pDescriptorNew->data[current_byte] += (player.weak_use << 7); //1/2
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.weak_use >> 1) & 1; //2/2
	
	pDescriptorNew->data[current_byte] += (player.play_pos[0] << 1); //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[1] << 3; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[2] << 5; //2/2

	pDescriptorNew->data[current_byte] += player.b_edit_playpos << 7; //1/1
	current_byte++;

	pDescriptorNew->data[current_byte] = player.play_pos[4]; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[5] << 2; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[6] << 4; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[7] << 6; //2/2
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_pos[8]; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[9] << 2; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[10] << 4; //2/2
	pDescriptorNew->data[current_byte] += player.play_pos[11] << 6; //2/2
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_pos[12]; //2/2
	
	pDescriptorNew->data[current_byte] += player.mo_hunchd << 2; //2/2
	
	pDescriptorNew->data[current_byte] += player.mo_hunchr << 4; //2/2
	
	pDescriptorNew->data[current_byte] += player.mo_pk << 6; //2/2
	current_byte++;
	
	pDescriptorNew->data[current_byte] = (player.place_kick); //7/7	
	
	pDescriptorNew->data[current_byte] += player.b_edit_ability << 7; //1/1
	current_byte++;

	pDescriptorNew->data[current_byte] = player.stamina & 127; //7/7

	pDescriptorNew->data[current_byte] += player.play_pos[3] << 7; //1/2
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_pos[3] >> 1; //2/2

	pDescriptorNew->data[current_byte] += player.speed << 1; //7/7
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.b_edit_skill; //1/1
	
	pDescriptorNew->data[current_byte] += player.b_edit_style << 1; //1/1
	
	pDescriptorNew->data[current_byte] += player.b_edit_com << 2; //1/1
	
	pDescriptorNew->data[current_byte] += player.b_edit_motion << 3; //1/1
	
	pDescriptorNew->data[current_byte] += player.b_base_copy << 4; //1/1
	//Unknown D - 1/1
	pDescriptorNew->data[current_byte] += player.strong_foot << 6; //1/1
	//Unknown E - 1/1
	current_byte++;

	pDescriptorNew->data[current_byte] = player.com_style[0]; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[1] << 1; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[2] << 2; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[3] << 3; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[4] << 4; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[5] << 5; //1/1
	pDescriptorNew->data[current_byte] += player.com_style[6] << 6; //1/1
	
	pDescriptorNew->data[current_byte] += player.play_skill[0] << 7; //1/1
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_skill[1]; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[2] << 1; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[3] << 2; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[4] << 3; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[5] << 4; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[6] << 5; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[7] << 6; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[8] << 7; //1/1
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_skill[9]; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[10] << 1; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[11] << 2; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[12] << 3; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[13] << 4; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[14] << 5; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[15] << 6; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[16] << 7; //1/1
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_skill[17]; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[18] << 1; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[19] << 2; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[20] << 3; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[21] << 4; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[22] << 5; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[23] << 6; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[24] << 7; //1/1
	current_byte++;
	pDescriptorNew->data[current_byte] = player.play_skill[25]; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[26] << 1; //1/1
	pDescriptorNew->data[current_byte] += player.play_skill[27] << 2; //1/1
	//Unknown F - 5/5
	current_byte++;
	
	//char tbuffer[46];
	WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)&(pDescriptorNew->data[current_byte]), 46, NULL, NULL);
	//(LPSTR)&(pDescriptorNew->data[current_byte])
	current_byte+=46;
	
	//strcpy_s((char *)&(pDescriptorNew->data[current_byte]), 18, player.shirt_name); //FIX THIS
	strncpy_s((char *)&(pDescriptorNew->data[current_byte]), 18, player.shirt_name, 18-1);
	current_byte+=18;
	
	//Appearance entries
	//playerID
	current_byte+=4;
	
	pDescriptorNew->data[current_byte] = player.b_edit_face; //1/1
	pDescriptorNew->data[current_byte] += player.b_edit_hair << 1; //1/1
	pDescriptorNew->data[current_byte] += player.b_edit_phys << 2; //1/1
	pDescriptorNew->data[current_byte] += player.b_edit_strip << 3; //1/1
	
	pDescriptorNew->data[current_byte] += (player.boot_id << 4) & 240; //4/14
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.boot_id >> 4) & 255; //8/14
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.boot_id >> 12) & 3; //2/14
	
	pDescriptorNew->data[current_byte] += (player.glove_id << 2) & 252; //6/10
	current_byte++;
	//pDescriptorNew->data[current_byte] = (player.glove_id >> 6) & 15; //4/10
	pDescriptorNew->data[current_byte] = (player.glove_id >> 6); //8/14 - extended to be 14 bits, using Unk B space
	
	//Unknown B - 4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.copy_id & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.copy_id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.copy_id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (player.copy_id >> 24) & 255; //8/32
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.neck_len; //4/4
	
	pDescriptorNew->data[current_byte] += player.neck_size << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.shldr_hi; //4/4
	
	pDescriptorNew->data[current_byte] += player.shldr_wid << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.chest; //4/4
	
	pDescriptorNew->data[current_byte] += player.waist << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.arm_size; //4/4
	
	pDescriptorNew->data[current_byte] += player.arm_len << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.thigh; //4/4
	
	pDescriptorNew->data[current_byte] += player.calf << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.leg_len; //4/4
	
	pDescriptorNew->data[current_byte] += player.head_len << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.head_wid; //4/4
	
	pDescriptorNew->data[current_byte] += player.head_dep << 4; //4/4
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.wrist_col_l; //3/3
	pDescriptorNew->data[current_byte] += player.wrist_col_r << 3; //3/3
	pDescriptorNew->data[current_byte] += player.wrist_tape << 6; //2/2
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.spec_col; //3/3
	pDescriptorNew->data[current_byte] += player.spec_style << 3; //3/3
	pDescriptorNew->data[current_byte] += player.sleeve << 6; //2/2
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.inners; //2/2
	pDescriptorNew->data[current_byte] += player.socks << 2; //2/2
	pDescriptorNew->data[current_byte] += player.undershorts << 4; //2/2
	pDescriptorNew->data[current_byte] += player.tucked << 6; //1/1
	pDescriptorNew->data[current_byte] += player.ankle_tape << 7; //1/1
	current_byte++;
	
	pDescriptorNew->data[current_byte] = player.gloves; //1/1
	pDescriptorNew->data[current_byte] += player.gloves_col << 1; //3/3
	//Unknown D - 4/4
	current_byte++;
	
	//Unknown E - 22 bytes
	current_byte+=22;
	
	//No custom in 18
	if(player.skin_col==7) player.skin_col=0;
	pDescriptorNew->data[current_byte] = player.skin_col; //3/3
	//Unknown F - 5/5
	current_byte++;
	
	//Unknown G - 18 bytes
	current_byte+=18;
	
	pDescriptorNew->data[current_byte] = player.iris_col; //4/4
	//Unknown H - 4/4
	current_byte++;
	
	//Unknown I - 7 bytes
	current_byte+=7;
}


void extract_team_info18(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x1E0;
		return;
	}
	
	pDescriptorNew->data[current_byte] = team.id & 255; //8/32
	current_byte++; //1
	pDescriptorNew->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++; //2
	pDescriptorNew->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++; //3
	pDescriptorNew->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++; //4
	
	current_byte+=0xE; //12
	pDescriptorNew->data[current_byte] = team.color1_red;

	pDescriptorNew->data[current_byte] += (team.color1_green << 6);
	current_byte++; //13
	pDescriptorNew->data[current_byte] = (pDescriptorNew->data[current_byte] & (~15)) | (team.color1_green >> 2);
	
	current_byte++; //14
	pDescriptorNew->data[current_byte] = team.color2_red;
	
	pDescriptorNew->data[current_byte] += (team.color2_green << 6);
	current_byte++; //15
	pDescriptorNew->data[current_byte] = (team.color2_green >> 2);
	
	pDescriptorNew->data[current_byte] += (team.color2_blue << 4);
	current_byte++; //16
	pDescriptorNew->data[current_byte] = (team.color2_blue >> 4);

	pDescriptorNew->data[current_byte] += (team.color1_blue << 2) & 255;
	
	current_byte+=0x3; //19
	pDescriptorNew->data[current_byte] = pDescriptorNew->data[current_byte] | (team.b_edit_name << 4);

	current_byte+=0x7F;
	
	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR)&(pDescriptorNew->data[current_byte]), 0x46, NULL, NULL);
	current_byte+=0x46;
	
	strcpy_s((char *)&(pDescriptorNew->data[current_byte]), 0x4, team.short_name);
	current_byte+=0x4;
	
	current_byte+=0xFE;
}

void extract_teamplayer_info18(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0xA4;
		return;
	}
	
	pDescriptorNew->data[current_byte] = team.id & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++;
	
	int ii;
	for(ii=0;ii<32;ii++)
	{
		pDescriptorNew->data[current_byte] = team.players[ii] & 255; //8/32
		current_byte++;
		pDescriptorNew->data[current_byte] = (team.players[ii] >> 8) & 255; //8/32
		current_byte++;
		pDescriptorNew->data[current_byte] = (team.players[ii] >> 16) & 255; //8/32
		current_byte++;
		pDescriptorNew->data[current_byte] = (team.players[ii] >> 24) & 255; //8/32
		current_byte++;
	}
	
	for(ii=0;ii<32;ii++)
	{
		pDescriptorNew->data[current_byte] = team.numbers[ii] & 255; //8/32
		current_byte++;
	}
}


void extract_team_tactics18(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x274;
		return;
	}
	
	pDescriptorNew->data[current_byte] = team.id & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 8) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 16) & 255; //8/32
	current_byte++;
	pDescriptorNew->data[current_byte] = (team.id >> 24) & 255; //8/32
	current_byte++;
	
	current_byte+=0x209;
	pDescriptorNew->data[current_byte] = team.captain_ind;

	current_byte+=0x67;
}