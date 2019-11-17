#include "editor.h"

int read_data(int start_bit, int bits_to_read, int& current_byte, FileDescriptorNew* pDescriptorNew)
{
	int shift;
	int pow_of_two[] = {1,2,4,8,16,32,64,128};

	int bytes_advanced = 0;
	int output = 0;
	int bit = start_bit;
	for(int ii=0; ii<bits_to_read; ii++)
	{
		if(bit == 8)
		{
			bit = 0;
			current_byte++;
		}
		if(ii%8 == 0 && ii>0) bytes_advanced++;
		shift = bit-(ii%8);
		if(shift>=0)
			output += ((pDescriptorNew->data[current_byte] >> shift) & pow_of_two[ii % 8]) << bytes_advanced*8;
		else
			output += ((pDescriptorNew->data[current_byte] << -shift) & pow_of_two[ii % 8]) << bytes_advanced*8;
		bit++;
	}
	if(bit == 8) current_byte++;

	return output;
}


void write_data(uint8_t input, int start_bit, int bits_to_write, int& current_byte, FileDescriptorNew* pDescriptorNew)
{
	int shift;
	int pow_of_two[] = {1,2,4,8,16,32,64,128};

	int bit = start_bit;
	if(bit == 0) pDescriptorNew->data[current_byte] = 0;
	for(int ii=0; ii<bits_to_write; ii++)
	{
		if(bit == 8)
		{
			bit = 0;
			current_byte++;
			pDescriptorNew->data[current_byte] = 0;
		}
		shift = (ii%8) - bit;
		if(shift>=0)
			pDescriptorNew->data[current_byte] += ((input >> shift) & pow_of_two[bit]);
		else
			pDescriptorNew->data[current_byte] += ((input << -shift) & pow_of_two[bit]);
		bit++;
	}
	if(bit == 8)
	{
		current_byte++;
		pDescriptorNew->data[current_byte] = 0;
	}
}


void fill_player_entry19(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	players.id = read_data(0, 4*8, current_byte, pDescriptorNew);
	/*players.id = pDescriptorNew->data[current_byte];
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 8;
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 16;
	current_byte++;
	players.id += pDescriptorNew->data[current_byte] << 24;
	current_byte++;*/

	current_byte += 0x4;

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

	players.ball_ctrl = pDescriptorNew->data[current_byte] >> 7;
	current_byte++;
	players.ball_ctrl += (pDescriptorNew->data[current_byte] << 1) & 127; 
	
	players.weak_use = (pDescriptorNew->data[current_byte] >> 6);
	current_byte++;
	
	players.lowpass		= read_data(0, 7, current_byte, pDescriptorNew);
	players.loftpass	= read_data(7, 7, current_byte, pDescriptorNew); //<------
	players.finish		= read_data(6, 7, current_byte, pDescriptorNew);
	players.place_kick	= read_data(5, 7, current_byte, pDescriptorNew);
	players.mo_armd		= read_data(4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown A - 1/1
	players.header		= read_data(0, 7, current_byte, pDescriptorNew);
	players.def			= read_data(7, 7, current_byte, pDescriptorNew);
	players.ball_win	= read_data(6, 7, current_byte, pDescriptorNew);
	players.kick_pwr	= read_data(5, 7, current_byte, pDescriptorNew);
	players.mo_armr		= read_data(4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown B - 1/1
	players.exp_pwr		= read_data(0, 7, current_byte, pDescriptorNew);
	players.body_ctrl	= read_data(7, 7, current_byte, pDescriptorNew);
	players.phys_cont	= read_data(6, 7, current_byte, pDescriptorNew);
	players.jump		= read_data(5, 7, current_byte, pDescriptorNew);
	players.mo_ck		= read_data(4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown C - 1/1
	players.catching	= read_data(0, 7, current_byte, pDescriptorNew);
	players.clearing	= read_data(7, 7, current_byte, pDescriptorNew);
	players.reflex		= read_data(6, 7, current_byte, pDescriptorNew);
	players.cover		= read_data(5, 7, current_byte, pDescriptorNew);
	players.form		= read_data(4, 3, current_byte, pDescriptorNew);
	players.b_edit_player = read_data(7, 1, current_byte, pDescriptorNew);
	players.reg_pos		= read_data(0, 4, current_byte, pDescriptorNew);
	//Unknown D - 1/1
	players.play_style	= read_data(5, 5, current_byte, pDescriptorNew);
	players.mo_fk		= read_data(2, 4, current_byte, pDescriptorNew);
	//Unknown E - 1/1
	players.swerve		= read_data(7, 7, current_byte, pDescriptorNew);
	players.speed		= read_data(6, 7, current_byte, pDescriptorNew);
	current_byte++; // Star Rating 3/3
	players.stamina		= read_data(0, 7, current_byte, pDescriptorNew);
	players.gk			= read_data(7, 7, current_byte, pDescriptorNew);
	players.mo_pk		= read_data(6, 3, current_byte, pDescriptorNew);
	players.drib		= read_data(1, 7, current_byte, pDescriptorNew);
	players.weak_acc	= read_data(0, 2, current_byte, pDescriptorNew);
	players.injury		= read_data(2, 2, current_byte, pDescriptorNew);

	players.play_pos[12] = read_data(4, 2, current_byte, pDescriptorNew); //GK
	players.play_pos[9] = read_data(6, 2, current_byte, pDescriptorNew); //CB
	players.play_pos[10] = read_data(0, 2, current_byte, pDescriptorNew); //LB
	players.play_pos[11] = read_data(2, 2, current_byte, pDescriptorNew); //RB
	players.play_pos[5] = read_data(4, 2, current_byte, pDescriptorNew); //DMF
	players.play_pos[6] = read_data(6, 2, current_byte, pDescriptorNew); //CMF
	players.play_pos[7] = read_data(0, 2, current_byte, pDescriptorNew); //LMF
	players.play_pos[8] = read_data(2, 2, current_byte, pDescriptorNew); //RMF
	players.play_pos[4] = read_data(4, 2, current_byte, pDescriptorNew); //AMF
	players.play_pos[2] = read_data(6, 2, current_byte, pDescriptorNew); //LWF
	players.play_pos[3] = read_data(0, 2, current_byte, pDescriptorNew); //RWF
	players.play_pos[1] = read_data(2, 2, current_byte, pDescriptorNew); //SS
	players.play_pos[0] = read_data(4, 2, current_byte, pDescriptorNew); //CF

	players.mo_hunchd	= read_data(6, 2, current_byte, pDescriptorNew);
	players.mo_hunchr	= read_data(0, 2, current_byte, pDescriptorNew);
	players.age			= read_data(2, 6, current_byte, pDescriptorNew);
	players.b_edit_basicset	= read_data(0, 1, current_byte, pDescriptorNew);
	players.b_edit_regpos = read_data(1, 1, current_byte, pDescriptorNew);
	players.b_edit_playpos = read_data(2, 1, current_byte, pDescriptorNew);
	players.b_edit_ability = read_data(3, 1, current_byte, pDescriptorNew);
	players.b_edit_skill = read_data(4, 1, current_byte, pDescriptorNew);
	players.b_edit_style = read_data(5, 1, current_byte, pDescriptorNew);
	players.b_edit_com = read_data(6, 1, current_byte, pDescriptorNew);
	players.b_edit_motion = read_data(7, 1, current_byte, pDescriptorNew);
	//Unknown F - 1/1
	players.strong_foot	= read_data(1, 1, current_byte, pDescriptorNew);

	players.com_style[0] = read_data(2, 1, current_byte, pDescriptorNew);
	players.com_style[1] = read_data(3, 1, current_byte, pDescriptorNew);
	players.com_style[2] = read_data(4, 1, current_byte, pDescriptorNew);
	players.com_style[3] = read_data(5, 1, current_byte, pDescriptorNew);
	players.com_style[4] = read_data(6, 1, current_byte, pDescriptorNew);
	players.com_style[5] = read_data(7, 1, current_byte, pDescriptorNew);
	players.com_style[6] = read_data(0, 1, current_byte, pDescriptorNew);

	players.play_skill[0]	= read_data(1, 1, current_byte, pDescriptorNew);
	players.play_skill[28]	= read_data(2, 1, current_byte, pDescriptorNew);
	players.play_skill[1]	= read_data(3, 1, current_byte, pDescriptorNew);
	players.play_skill[2]	= read_data(4, 1, current_byte, pDescriptorNew);
	players.play_skill[3]	= read_data(5, 1, current_byte, pDescriptorNew);
	players.play_skill[29]	= read_data(6, 1, current_byte, pDescriptorNew);
	players.play_skill[4]	= read_data(7, 1, current_byte, pDescriptorNew);
	players.play_skill[5]	= read_data(0, 1, current_byte, pDescriptorNew);
	players.play_skill[30]	= read_data(1, 1, current_byte, pDescriptorNew);
	players.play_skill[6]	= read_data(2, 1, current_byte, pDescriptorNew);
	players.play_skill[7]	= read_data(3, 1, current_byte, pDescriptorNew);
	players.play_skill[31]	= read_data(4, 1, current_byte, pDescriptorNew);
	players.play_skill[8]	= read_data(5, 1, current_byte, pDescriptorNew);
	players.play_skill[32]	= read_data(6, 1, current_byte, pDescriptorNew);
	players.play_skill[33]	= read_data(7, 1, current_byte, pDescriptorNew);
	players.play_skill[9]	= read_data(0, 1, current_byte, pDescriptorNew);
	players.play_skill[10]	= read_data(1, 1, current_byte, pDescriptorNew);
	players.play_skill[11]	= read_data(2, 1, current_byte, pDescriptorNew);
	players.play_skill[12]	= read_data(3, 1, current_byte, pDescriptorNew);
	players.play_skill[13]	= read_data(4, 1, current_byte, pDescriptorNew);
	players.play_skill[14]	= read_data(5, 1, current_byte, pDescriptorNew);
	players.play_skill[15]	= read_data(6, 1, current_byte, pDescriptorNew);
	players.play_skill[16]	= read_data(7, 1, current_byte, pDescriptorNew);
	players.play_skill[34]	= read_data(0, 1, current_byte, pDescriptorNew);
	players.play_skill[17]	= read_data(1, 1, current_byte, pDescriptorNew);
	players.play_skill[18]	= read_data(2, 1, current_byte, pDescriptorNew);
	players.play_skill[35]	= read_data(3, 1, current_byte, pDescriptorNew);
	players.play_skill[19]	= read_data(4, 1, current_byte, pDescriptorNew);
	players.play_skill[20]	= read_data(5, 1, current_byte, pDescriptorNew);
	players.play_skill[36]	= read_data(6, 1, current_byte, pDescriptorNew);
	players.play_skill[37]	= read_data(7, 1, current_byte, pDescriptorNew);
	players.play_skill[21]	= read_data(0, 1, current_byte, pDescriptorNew);
	players.play_skill[22]	= read_data(1, 1, current_byte, pDescriptorNew);
	players.play_skill[23]	= read_data(2, 1, current_byte, pDescriptorNew);
	players.play_skill[38]	= read_data(3, 1, current_byte, pDescriptorNew);
	players.play_skill[24]	= read_data(4, 1, current_byte, pDescriptorNew);
	players.play_skill[25]	= read_data(5, 1, current_byte, pDescriptorNew);
	players.play_skill[26]	= read_data(6, 1, current_byte, pDescriptorNew);
	players.play_skill[27]	= read_data(7, 1, current_byte, pDescriptorNew);
	current_byte++; //Unknown G - 8/8

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
	players.glove_id += (pDescriptorNew->data[current_byte] & 15) << 6;

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


void fill_team_ids19(team_entry &teams, int &current_byte, void* ghdescriptor)
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

	current_byte+=0x3F;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorNew->data[current_byte]), -1, teams.name, 0x46);
	current_byte+=0x46;

	strcpy_s(teams.short_name, 0x4, (const char*)&(pDescriptorNew->data[current_byte]));
	current_byte+=0x4;
	//Remove non alphanumeric characters
	for(int ii=0;ii<4;ii++)
	{
		if((int)teams.short_name[ii]<33 || (int)teams.short_name[ii]>95)
			teams.short_name[ii]=(char)0;
	}

	current_byte+=0xFE;
}


void fill_team_rosters19(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
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

	for(ii=0;ii<40;ii++)
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

	for(ii=0;ii<40;ii++)
	{
		gteams[t_ind].numbers[ii] = pDescriptorNew->data[current_byte];
		current_byte++;
		gteams[t_ind].numbers[ii] += pDescriptorNew->data[current_byte] << 8;
		current_byte++;
	}
}


void fill_team_tactics19(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
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


void extract_player_entry19(player_entry player, int &current_byte, void* ghdescriptor)
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
	
	current_byte += 0x4;
	
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
	
	write_data(player.ball_ctrl,	7, 7, current_byte, pDescriptorNew);
	write_data(player.weak_use,	6, 2, current_byte, pDescriptorNew);	
	write_data(player.lowpass,		0, 7, current_byte, pDescriptorNew);
	write_data(player.loftpass,	7, 7, current_byte, pDescriptorNew);
	write_data(player.finish,		6, 7, current_byte, pDescriptorNew);
	write_data(player.place_kick,	5, 7, current_byte, pDescriptorNew);
	write_data(player.mo_armd,		4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown A - 1/1
	write_data(player.header,		0, 7, current_byte, pDescriptorNew);
	write_data(player.def,			7, 7, current_byte, pDescriptorNew);
	write_data(player.ball_win,	6, 7, current_byte, pDescriptorNew);
	write_data(player.kick_pwr,	5, 7, current_byte, pDescriptorNew);
	write_data(player.mo_armr,		4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown B - 1/1
	write_data(player.exp_pwr,		0, 7, current_byte, pDescriptorNew);
	write_data(player.body_ctrl,	7, 7, current_byte, pDescriptorNew);
	write_data(player.phys_cont,	6, 7, current_byte, pDescriptorNew);
	write_data(player.jump,		5, 7, current_byte, pDescriptorNew);
	write_data(player.mo_ck,		4, 3, current_byte, pDescriptorNew);
	current_byte++; //Unknown C - 1/1
	write_data(player.catching,	0, 7, current_byte, pDescriptorNew);
	write_data(player.clearing,	7, 7, current_byte, pDescriptorNew);
	write_data(player.reflex,		6, 7, current_byte, pDescriptorNew);
	write_data(player.cover,		5, 7, current_byte, pDescriptorNew);
	write_data(player.form,		4, 3, current_byte, pDescriptorNew);
	write_data(player.b_edit_player,7, 1, current_byte, pDescriptorNew);
	write_data(player.reg_pos,		0, 4, current_byte, pDescriptorNew);
	//Unknown D - 1/1
	write_data(player.play_style,	5, 5, current_byte, pDescriptorNew);
	write_data(player.mo_fk,		2, 4, current_byte, pDescriptorNew);
	//Unknown E - 1/1
	write_data(player.swerve,		7, 7, current_byte, pDescriptorNew);
	write_data(player.speed,		6, 7, current_byte, pDescriptorNew);
	current_byte++; // Star Rating 3/3
	write_data(player.stamina,		0, 7, current_byte, pDescriptorNew);
	write_data(player.gk,			7, 7, current_byte, pDescriptorNew);
	write_data(player.mo_pk,		6, 3, current_byte, pDescriptorNew);
	write_data(player.drib,		1, 7, current_byte, pDescriptorNew);
	write_data(player.weak_acc,	0, 2, current_byte, pDescriptorNew);
	write_data(player.injury,		2, 2, current_byte, pDescriptorNew);

	write_data(player.play_pos[12],	4, 2, current_byte, pDescriptorNew); //GK
	write_data(player.play_pos[9],	6, 2, current_byte, pDescriptorNew); //CB
	write_data(player.play_pos[10],	0, 2, current_byte, pDescriptorNew); //LB
	write_data(player.play_pos[11],	2, 2, current_byte, pDescriptorNew); //RB
	write_data(player.play_pos[5],	4, 2, current_byte, pDescriptorNew); //DMF
	write_data(player.play_pos[6],	6, 2, current_byte, pDescriptorNew); //CMF
	write_data(player.play_pos[7],	0, 2, current_byte, pDescriptorNew); //LMF
	write_data(player.play_pos[8],	2, 2, current_byte, pDescriptorNew); //RMF
	write_data(player.play_pos[4],	4, 2, current_byte, pDescriptorNew); //AMF
	write_data(player.play_pos[2],	6, 2, current_byte, pDescriptorNew); //LWF
	write_data(player.play_pos[3],	0, 2, current_byte, pDescriptorNew); //RWF
	write_data(player.play_pos[1],	2, 2, current_byte, pDescriptorNew); //SS
	write_data(player.play_pos[0],	4, 2, current_byte, pDescriptorNew); //CF

	write_data(player.mo_hunchd,	6, 2, current_byte, pDescriptorNew);
	write_data(player.mo_hunchr,	0, 2, current_byte, pDescriptorNew);
	write_data(player.age,			2, 6, current_byte, pDescriptorNew);
	write_data(player.b_edit_basicset,	0, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_regpos,	1, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_playpos,	2, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_ability,	3, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_skill,	4, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_style,	5, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_com,	6, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_motion,	7, 1, current_byte, pDescriptorNew);
	//Unknown F - 1/1
	write_data(player.strong_foot,	1, 1, current_byte, pDescriptorNew);

	write_data(player.com_style[0], 2, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[1], 3, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[2], 4, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[3], 5, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[4], 6, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[5], 7, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[6], 0, 1, current_byte, pDescriptorNew);

	write_data(player.play_skill[0],	1, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[28],	2, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[1],	3, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[2],	4, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[3],	5, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[29],	6, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[4],	7, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[5],	0, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[30],	1, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[6],	2, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[7],	3, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[31],	4, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[8],	5, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[32],	6, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[33],	7, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[9],	0, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[10],	1, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[11],	2, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[12],	3, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[13],	4, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[14],	5, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[15],	6, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[16],	7, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[34],	0, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[17],	1, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[18],	2, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[35],	3, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[19],	4, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[20],	5, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[36],	6, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[37],	7, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[21],	0, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[22],	1, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[23],	2, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[38],	3, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[24],	4, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[25],	5, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[26],	6, 1, current_byte, pDescriptorNew);
	write_data(player.play_skill[27],	7, 1, current_byte, pDescriptorNew);
	current_byte++; //Unknown G - 8/8
	
	//char tbuffer[46];
	WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)&(pDescriptorNew->data[current_byte]), 46, NULL, NULL);
	//(LPSTR)&(pDescriptorNew->data[current_byte])
	current_byte+=46;
	
	strcpy_s((char *)&(pDescriptorNew->data[current_byte]), 18, player.shirt_name); //FIX THIS
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
	pDescriptorNew->data[current_byte] = (player.glove_id >> 6) & 15; //4/10
	
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


void extract_team_info19(team_entry team, int &current_byte, void* ghdescriptor)
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
/*	pDescriptorNew->data[current_byte] = team.color1_red;

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
*/	current_byte+=4; //Skip color saving for now	
	current_byte+=0x3; //19
//	pDescriptorNew->data[current_byte] = pDescriptorNew->data[current_byte] | (team.b_edit_name << 4);

	current_byte+=0x3F;
	
	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR)&(pDescriptorNew->data[current_byte]), 0x46, NULL, NULL);
	current_byte+=0x46;
	
	strcpy_s((char *)&(pDescriptorNew->data[current_byte]), 0x4, team.short_name);
	current_byte+=0x4;
	
	current_byte+=0xFE;
}

void extract_teamplayer_info19(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0xF4;
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
	
	for(int ii=0;ii<40;ii++)
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
	
	for(int ii=0;ii<40;ii++)
	{
		pDescriptorNew->data[current_byte] = team.numbers[ii] & 255; //8/16
		current_byte++;
		pDescriptorNew->data[current_byte] = (team.numbers[ii] >> 8) & 255; //8/16
		current_byte++;
	}
}


void extract_team_tactics19(team_entry team, int &current_byte, void* ghdescriptor)
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