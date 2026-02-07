#include "editor.h"

void fill_player_entry20(player_entry &players, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	players.id = read_data(0, 4*8, current_byte, pDescriptorNew);

	current_byte += 0x4;

	players.nation = read_data(0, 2*8, current_byte, pDescriptorNew);
	players.height = read_data(0, 8, current_byte, pDescriptorNew);
	players.weight = read_data(0, 8, current_byte, pDescriptorNew);
	
	players.gc1 = read_data(0, 8, current_byte, pDescriptorNew);
	players.gc2 = read_data(0, 8, current_byte, pDescriptorNew);

	players.atk = read_data(0, 7, current_byte, pDescriptorNew);
	players.ball_ctrl = read_data(7, 7, current_byte, pDescriptorNew);
	players.weak_use = read_data(6, 2, current_byte, pDescriptorNew);
	players.tight_pos = read_data(0, 7, current_byte, pDescriptorNew);
	players.lowpass		= read_data(7, 7, current_byte, pDescriptorNew);
	players.loftpass	= read_data(6, 7, current_byte, pDescriptorNew); 
	players.finish		= read_data(5, 7, current_byte, pDescriptorNew);
	players.mo_armd		= read_data(4, 4, current_byte, pDescriptorNew);
	players.place_kick	= read_data(0, 7, current_byte, pDescriptorNew);
	players.swerve		= read_data(7, 7, current_byte, pDescriptorNew); //Curl
	players.speed		= read_data(6, 7, current_byte, pDescriptorNew);
	players.exp_pwr		= read_data(5, 7, current_byte, pDescriptorNew); //Acceleration
	players.mo_armr		= read_data(4, 4, current_byte, pDescriptorNew);
	players.jump		= read_data(0, 7, current_byte, pDescriptorNew);
	players.phys_cont	= read_data(7, 7, current_byte, pDescriptorNew);
	players.body_ctrl	= read_data(6, 7, current_byte, pDescriptorNew); //Balance
	players.stamina		= read_data(5, 7, current_byte, pDescriptorNew);
	players.mo_ck		= read_data(4, 4, current_byte, pDescriptorNew);
	players.ball_win	= read_data(0, 7, current_byte, pDescriptorNew);
	players.aggres		= read_data(7, 7, current_byte, pDescriptorNew);
	players.gk			= read_data(6, 7, current_byte, pDescriptorNew); //GK Awareness
	players.catching	= read_data(5, 7, current_byte, pDescriptorNew);
	players.form		= read_data(4, 3, current_byte, pDescriptorNew);
	players.b_edit_player = read_data(7, 1, current_byte, pDescriptorNew);
	players.cover		= read_data(0, 7, current_byte, pDescriptorNew); //GK Reach
	players.age			= read_data(7, 6, current_byte, pDescriptorNew);
	players.reg_pos		= read_data(5, 4, current_byte, pDescriptorNew);
    //Unknown A - 1/1
	players.play_style	= read_data(2, 5, current_byte, pDescriptorNew);
	players.mo_fk		= read_data(7, 5, current_byte, pDescriptorNew);
	players.star		= read_data(4, 3, current_byte, pDescriptorNew);
	players.b_edit_basicset	= read_data(7, 1, current_byte, pDescriptorNew);
	players.def			= read_data(0, 7, current_byte, pDescriptorNew);
	players.clearing	= read_data(7, 7, current_byte, pDescriptorNew);
	players.header		= read_data(6, 7, current_byte, pDescriptorNew);
	players.mo_hunchd	= read_data(5, 3, current_byte, pDescriptorNew);
	players.mo_hunchr	= read_data(0, 3, current_byte, pDescriptorNew);
	players.mo_pk		= read_data(3, 3, current_byte, pDescriptorNew);
	players.weak_acc	= read_data(6, 2, current_byte, pDescriptorNew);
	players.drib		= read_data(0, 7, current_byte, pDescriptorNew);
	players.injury		= read_data(7, 2, current_byte, pDescriptorNew);
	players.play_attit	= read_data(1, 2, current_byte, pDescriptorNew);
	players.mo_drib		= read_data(3, 2, current_byte, pDescriptorNew);
	players.play_pos[12] = read_data(5, 2, current_byte, pDescriptorNew); //GK
	players.play_pos[9] = read_data(7, 2, current_byte, pDescriptorNew); //CB
	players.play_pos[10] = read_data(1, 2, current_byte, pDescriptorNew); //LB
	players.play_pos[11] = read_data(3, 2, current_byte, pDescriptorNew); //RB
	players.play_pos[5] = read_data(5, 2, current_byte, pDescriptorNew); //DMF
	players.play_pos[6] = read_data(7, 2, current_byte, pDescriptorNew); //CMF
	players.play_pos[7] = read_data(1, 2, current_byte, pDescriptorNew); //LMF
	players.play_pos[8] = read_data(3, 2, current_byte, pDescriptorNew); //RMF
	players.play_pos[4] = read_data(5, 2, current_byte, pDescriptorNew); //AMF
	players.b_edit_regpos = read_data(7, 1, current_byte, pDescriptorNew);
	players.play_pos[3] = read_data(0, 2, current_byte, pDescriptorNew); //RWF
	players.play_pos[1] = read_data(2, 2, current_byte, pDescriptorNew); //SS
	players.play_pos[0] = read_data(4, 2, current_byte, pDescriptorNew); //CF
	players.reflex		= read_data(6, 7, current_byte, pDescriptorNew);
	players.kick_pwr	= read_data(5, 7, current_byte, pDescriptorNew);
	players.play_pos[2] = read_data(4, 2, current_byte, pDescriptorNew); //LWF
	players.b_edit_playpos = read_data(6, 1, current_byte, pDescriptorNew);
	players.b_edit_ability = read_data(7, 1, current_byte, pDescriptorNew);
	players.b_edit_skill = read_data(0, 1, current_byte, pDescriptorNew);
	players.b_edit_style = read_data(1, 1, current_byte, pDescriptorNew);
	players.b_edit_com = read_data(2, 1, current_byte, pDescriptorNew);
	players.b_edit_motion = read_data(3, 1, current_byte, pDescriptorNew);
	//Unknown C - 4/1
	players.strong_foot	= read_data(5, 1, current_byte, pDescriptorNew);
	players.strong_hand	= read_data(6, 1, current_byte, pDescriptorNew);
	//COM playing styles
	players.com_style[0] = read_data(7, 1, current_byte, pDescriptorNew);
	players.com_style[1] = read_data(0, 1, current_byte, pDescriptorNew);
	players.com_style[2] = read_data(1, 1, current_byte, pDescriptorNew);
	players.com_style[3] = read_data(2, 1, current_byte, pDescriptorNew);
	players.com_style[4] = read_data(3, 1, current_byte, pDescriptorNew);
	players.com_style[5] = read_data(4, 1, current_byte, pDescriptorNew);
	players.com_style[6] = read_data(5, 1, current_byte, pDescriptorNew);
	//Player skills
	players.play_skill[0]	= read_data(6, 1, current_byte, pDescriptorNew); //Scissors Feint
	players.play_skill[28]	= read_data(7, 1, current_byte, pDescriptorNew); //Double Touch
	players.play_skill[1]	= read_data(0, 1, current_byte, pDescriptorNew); //Flip flap
	players.play_skill[2]	= read_data(1, 1, current_byte, pDescriptorNew); //Marseille turn
	players.play_skill[3]	= read_data(2, 1, current_byte, pDescriptorNew); //Sombrero
	players.play_skill[29]	= read_data(3, 1, current_byte, pDescriptorNew); //Crossover Turn
	players.play_skill[4]	= read_data(4, 1, current_byte, pDescriptorNew); //Cut Behind & Turn
	players.play_skill[5]	= read_data(5, 1, current_byte, pDescriptorNew); //Scotch Move
	players.play_skill[30]	= read_data(6, 1, current_byte, pDescriptorNew); //Step on Skill
	players.play_skill[6]	= read_data(7, 1, current_byte, pDescriptorNew); //Heading
	players.play_skill[7]	= read_data(0, 1, current_byte, pDescriptorNew); //Long range drive
	players.play_skill[31]	= read_data(1, 1, current_byte, pDescriptorNew); //Chip Shot
	players.play_skill[39]	= read_data(2, 1, current_byte, pDescriptorNew); //Long range shooting
	players.play_skill[8]	= read_data(3, 1, current_byte, pDescriptorNew); //Knuckle shot
	players.play_skill[32]	= read_data(4, 1, current_byte, pDescriptorNew); //Dipping Shots
	players.play_skill[33]	= read_data(5, 1, current_byte, pDescriptorNew); //Rising Shots
	players.play_skill[9]	= read_data(6, 1, current_byte, pDescriptorNew); //Acro finishing
	players.play_skill[10]	= read_data(7, 1, current_byte, pDescriptorNew); //Heel trick
	players.play_skill[11]	= read_data(0, 1, current_byte, pDescriptorNew); //First time shot
	players.play_skill[12]	= read_data(1, 1, current_byte, pDescriptorNew); //One touch pass
	players.play_skill[40]	= read_data(2, 1, current_byte, pDescriptorNew); //Through passing
	players.play_skill[13]	= read_data(3, 1, current_byte, pDescriptorNew); //Weighted pass
	players.play_skill[14]	= read_data(4, 1, current_byte, pDescriptorNew); //Pinpoint crossing
	players.play_skill[15]	= read_data(5, 1, current_byte, pDescriptorNew); //Outside curler
	players.play_skill[16]	= read_data(6, 1, current_byte, pDescriptorNew); //Rabona
	players.play_skill[34]	= read_data(7, 1, current_byte, pDescriptorNew); //No Look Pass
	players.play_skill[17]	= read_data(0, 1, current_byte, pDescriptorNew); //Low Lofted Pass
	players.play_skill[18]	= read_data(1, 1, current_byte, pDescriptorNew); //Low Punt trajectory
	players.play_skill[35]	= read_data(2, 1, current_byte, pDescriptorNew); //GK High Punt Trajectory
	players.play_skill[19]	= read_data(3, 1, current_byte, pDescriptorNew); //Long throw
	players.play_skill[20]	= read_data(4, 1, current_byte, pDescriptorNew); //GK long throw
	players.play_skill[36]	= read_data(5, 1, current_byte, pDescriptorNew); //Penalty Specialist
	players.play_skill[37]	= read_data(6, 1, current_byte, pDescriptorNew); //GK Penalty Specialist
	players.play_skill[21]	= read_data(7, 1, current_byte, pDescriptorNew); //Malicia
	players.play_skill[22]	= read_data(0, 1, current_byte, pDescriptorNew); //Man marking
	players.play_skill[23]	= read_data(1, 1, current_byte, pDescriptorNew); //Track back
	players.play_skill[38]	= read_data(2, 1, current_byte, pDescriptorNew); //Interception
	players.play_skill[24]	= read_data(3, 1, current_byte, pDescriptorNew); //Acro clear
	players.play_skill[25]	= read_data(4, 1, current_byte, pDescriptorNew); //Captaincy
	players.play_skill[26]	= read_data(5, 1, current_byte, pDescriptorNew); //Super sub
	players.play_skill[27]	= read_data(6, 1, current_byte, pDescriptorNew); //Fighting spirit
	current_byte++; //Unknown D 7/1

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorNew->data[current_byte]), -1, players.name, 61);
	current_byte+=61;

	strncpy_s(players.shirt_name, 21, (const char*)&(pDescriptorNew->data[current_byte]), 21 - 1);
	current_byte+=61;

	current_byte+=64; //Print Name (National Team) 

	//Appearance entries
	//playerID
	current_byte+=4; 
	//0x04:0
	players.b_edit_face	= read_data(0, 1, current_byte, pDescriptorNew);
	players.b_edit_hair	= read_data(1, 1, current_byte, pDescriptorNew);
	players.b_edit_phys	= read_data(2, 1, current_byte, pDescriptorNew);
	players.b_edit_strip = read_data(3, 1, current_byte, pDescriptorNew);
	players.boot_id		= read_data(4, 14, current_byte, pDescriptorNew);
	players.glove_id	= read_data(2, 14, current_byte, pDescriptorNew); //Extend to be 14 bits, using Unk A space
	players.copy_id		= read_data(0, 4*8, current_byte, pDescriptorNew);
	players.neck_len	= read_data(0, 4, current_byte, pDescriptorNew);
	players.neck_size	= read_data(4, 4, current_byte, pDescriptorNew);
	players.shldr_hi	= read_data(0, 4, current_byte, pDescriptorNew);
	players.shldr_wid	= read_data(4, 4, current_byte, pDescriptorNew);
	players.chest		= read_data(0, 4, current_byte, pDescriptorNew);
	players.waist		= read_data(4, 4, current_byte, pDescriptorNew);
	players.arm_size	= read_data(0, 4, current_byte, pDescriptorNew);
	players.arm_len		= read_data(4, 4, current_byte, pDescriptorNew);
	players.thigh		= read_data(0, 4, current_byte, pDescriptorNew);
	players.calf		= read_data(4, 4, current_byte, pDescriptorNew);
	players.leg_len		= read_data(0, 4, current_byte, pDescriptorNew);
	players.head_len	= read_data(4, 4, current_byte, pDescriptorNew);
	players.head_wid	= read_data(0, 4, current_byte, pDescriptorNew);
	players.head_dep	= read_data(4, 4, current_byte, pDescriptorNew);
	players.wrist_col_l	= read_data(0, 3, current_byte, pDescriptorNew);
	players.wrist_col_r = read_data(3, 3, current_byte, pDescriptorNew);
	players.wrist_tape	= read_data(6, 2, current_byte, pDescriptorNew);
	players.spec_col	= read_data(0, 3, current_byte, pDescriptorNew);
	players.spec_style	= read_data(3, 3, current_byte, pDescriptorNew);
	players.sleeve		= read_data(6, 2, current_byte, pDescriptorNew);
	players.inners		= read_data(0, 2, current_byte, pDescriptorNew);
	players.socks		= read_data(2, 2, current_byte, pDescriptorNew);
	players.undershorts = read_data(4, 2, current_byte, pDescriptorNew);
	players.untucked		= read_data(6, 1, current_byte, pDescriptorNew);
	players.ankle_tape	= read_data(7, 1, current_byte, pDescriptorNew);
	//0x16:0
	players.gloves		= read_data(0, 1, current_byte, pDescriptorNew);
	players.gloves_col	= read_data(1, 3, current_byte, pDescriptorNew);
	//Skip face settings
	current_byte+=23;
	//0x2D:0
	players.skin_col = read_data(0, 3, current_byte, pDescriptorNew);
	//No custom skin in 18+
	if(players.skin_col==7)
	{
        players.skin_col=0;
		players.b_changed=true;
	}
	//Skip additional face settings
	current_byte+=19;
	//0x40:0
	players.iris_col = read_data(0, 4, current_byte, pDescriptorNew);
	//Skip hair settings
	current_byte+=8;
}


void fill_team_ids20(team_entry &team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	team.id = read_data(0, 4*8, current_byte, pDescriptorNew);
	team.manager_id = read_data(0, 4*8, current_byte, pDescriptorNew);

	current_byte+=2; //Team emblem
	//0xA
	team.stadium_id = read_data(0, 2*8, current_byte, pDescriptorNew);

	current_byte+=0xA; //Skip to 0x16
	team.color1_red	= read_data(2, 6, current_byte, pDescriptorNew);
	team.color1_green	= read_data(0, 6, current_byte, pDescriptorNew);
	team.b_edit_name	= read_data(6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited emblem: 1 bit
	team.color2_green	= read_data(0, 6, current_byte, pDescriptorNew);
	team.color2_blue	= read_data(6, 6, current_byte, pDescriptorNew);
	current_byte+=2; //Media backdrop colors
	team.b_edit_stadium = read_data(6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited stadium name: 1 bit
	current_byte+=2; //Stadium settings
	team.color1_blue	= read_data(0, 6, current_byte, pDescriptorNew);
	team.color2_red	= read_data(6, 6, current_byte, pDescriptorNew);

	current_byte+=0x39;
	current_byte+=4; //Rival team ID 1
	current_byte+=4; //Rival team ID 2
	current_byte+=4; //Rival team ID 3
	current_byte+=4; //Banner Edited flags

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)&(pDescriptorNew->data[current_byte]), -1, team.name, 0x46);
	current_byte+=0x46;

	strncpy_s(team.short_name, 0x4, (const char*)&(pDescriptorNew->data[current_byte]), 0x4 - 1);
	current_byte+=0x4;
	//Remove non alphanumeric characters
	for(int ii=0;ii<4;ii++)
	{
		if((int)team.short_name[ii]<33 || (int)team.short_name[ii]>95)
			team.short_name[ii]=(char)0;
	}

	current_byte+=181; //Stadium name
	current_byte+=16; //Banner 1 text
	current_byte+=16; //Banner 2 text
	current_byte+=16; //Banner 3 text
	current_byte+=16; //Banner 4 text

	current_byte+=105; //Unknown D
}


void fill_team_ids21(team_entry& team, int& current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	team.id = read_data(0, 4 * 8, current_byte, pDescriptorNew);
	team.manager_id = read_data(0, 4 * 8, current_byte, pDescriptorNew);

	current_byte += 2; //Team emblem
	//0xA
	team.stadium_id = read_data(0, 2 * 8, current_byte, pDescriptorNew);

	current_byte += 0xA; //Skip to 0x16
	team.color1_red = read_data(2, 6, current_byte, pDescriptorNew);
	team.color1_green = read_data(0, 6, current_byte, pDescriptorNew);
	team.b_edit_name = read_data(6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited emblem: 1 bit
	team.color2_green = read_data(0, 6, current_byte, pDescriptorNew);
	team.color2_blue = read_data(6, 6, current_byte, pDescriptorNew);
	current_byte += 2; //Media backdrop colors
	team.b_edit_stadium = read_data(6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited stadium name: 1 bit
	current_byte += 2; //Stadium settings
	team.color1_blue = read_data(0, 6, current_byte, pDescriptorNew);
	team.color2_red = read_data(6, 6, current_byte, pDescriptorNew);

	current_byte += 0x39;
	current_byte += 4; //Rival team ID 1
	current_byte += 4; //Rival team ID 2
	current_byte += 4; //Rival team ID 3
	current_byte += 4; //Banner Edited flags

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR) & (pDescriptorNew->data[current_byte]), -1, team.name, 0x46);
	current_byte += 0x46;

	strncpy_s(team.short_name, 0x4, (const char*)&(pDescriptorNew->data[current_byte]), 0x4 - 1);
	current_byte += 0x4;
	//Remove non alphanumeric characters
	for (int ii = 0; ii < 4; ii++)
	{
		if ((int)team.short_name[ii] < 33 || (int)team.short_name[ii]>95)
			team.short_name[ii] = (char)0;
	}

	current_byte += 181; //Stadium name
	current_byte += 16; //Banner 1 text
	current_byte += 16; //Banner 2 text
	current_byte += 16; //Banner 3 text
	current_byte += 16; //Banner 4 text

	current_byte += 165; //Unknown D
}


void fill_team_rosters20(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	int ii, t_ind;
	unsigned long team_id, player_id;

	team_id = read_data(0, 4*8, current_byte, pDescriptorNew);

	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}

	for(ii=0;ii<40;ii++)
	{
		player_id = read_data(0, 4*8, current_byte, pDescriptorNew);

		gteams[t_ind].players[ii] = player_id;
		if(player_id) gteams[t_ind].num_on_team++; //Increment player count
	}
	//Hide team with no players
	if(gteams[t_ind].players[0] == 0) 
		gteams[t_ind].b_show = false;

	for(ii=0;ii<40;ii++)
	{
		//Player shirt numbers
		gteams[t_ind].numbers[ii] = read_data(0, 2*8, current_byte, pDescriptorNew);
	}

	current_byte+=40; //Unknown A
}


void fill_team_tactics20(int &current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	//Total block length: 0x274 bytes
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	int t_ind;
	unsigned long team_id;

	team_id = read_data(0, 4*8, current_byte, pDescriptorNew);

	//Find team array entry that matches this ID
	for(t_ind=0;t_ind<gnum_teams;t_ind++)
	{
		if(team_id == gteams[t_ind].id) break;
	}
	current_byte+=0x1E0;

	//Starting lineup
	for(int ii=0; ii<11; ii++)
	{
		gteams[t_ind].starting11[ii] = pDescriptorNew->data[current_byte];
		current_byte++;
	}
	current_byte+=0x26;
	//Captain index at byte 0x215:
	gteams[t_ind].captain_ind = (char)pDescriptorNew->data[current_byte];
	current_byte+=0x5f;
}

//---------------------------------------------------------------------------------------------------------


void extract_player_entry20(player_entry player, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!player.b_changed)
	{
		current_byte += 0xF0+0x48;
		return;
	}
	
	write_data(player.id, 0, 4*8, current_byte, pDescriptorNew);
	current_byte += 0x4; //Commentary name
	write_data(player.nation, 0, 2*8, current_byte, pDescriptorNew);
	write_data(player.height,		0, 8, current_byte, pDescriptorNew);
	write_data(player.weight,		0, 8, current_byte, pDescriptorNew);
	write_data(player.gc1,			0, 8, current_byte, pDescriptorNew);
	write_data(player.gc2,			0, 8, current_byte, pDescriptorNew);
	write_data(player.atk,			0, 7, current_byte, pDescriptorNew);
	write_data(player.ball_ctrl,	7, 7, current_byte, pDescriptorNew);
	write_data(player.weak_use,		6, 2, current_byte, pDescriptorNew);	
	write_data(player.tight_pos,	0, 7, current_byte, pDescriptorNew);
	write_data(player.lowpass,		7, 7, current_byte, pDescriptorNew);
	write_data(player.loftpass,	6, 7, current_byte, pDescriptorNew); 
	write_data(player.finish,		5, 7, current_byte, pDescriptorNew);
	write_data(player.mo_armd,		4, 4, current_byte, pDescriptorNew);
	write_data(player.place_kick,	0, 7, current_byte, pDescriptorNew);
	write_data(player.swerve,		7, 7, current_byte, pDescriptorNew); //Curl
	write_data(player.speed,		6, 7, current_byte, pDescriptorNew);
	write_data(player.exp_pwr,		5, 7, current_byte, pDescriptorNew); //Acceleration
	write_data(player.mo_armr,		4, 4, current_byte, pDescriptorNew);
	write_data(player.jump,		0, 7, current_byte, pDescriptorNew);
	write_data(player.phys_cont,	7, 7, current_byte, pDescriptorNew);
	write_data(player.body_ctrl,	6, 7, current_byte, pDescriptorNew); //Balance
	write_data(player.stamina,		5, 7, current_byte, pDescriptorNew);
	write_data(player.mo_ck,		4, 4, current_byte, pDescriptorNew);
	write_data(player.ball_win,	0, 7, current_byte, pDescriptorNew);
	write_data(player.aggres,		7, 7, current_byte, pDescriptorNew);
	write_data(player.gk,			6, 7, current_byte, pDescriptorNew); //GK Awareness
	write_data(player.catching,	5, 7, current_byte, pDescriptorNew);
	write_data(player.form,		4, 3, current_byte, pDescriptorNew);
	write_data(player.b_edit_player,7, 1, current_byte, pDescriptorNew);
	write_data(player.cover,		0, 7, current_byte, pDescriptorNew); //GK Reach
	write_data(player.age,			7, 6, current_byte, pDescriptorNew);
	write_data(player.reg_pos,		5, 4, current_byte, pDescriptorNew);
    //Unknown A - 1 bit
	write_data(player.play_style,	2, 5, current_byte, pDescriptorNew);
	write_data(player.mo_fk,		7, 5, current_byte, pDescriptorNew);
	write_data(player.star,			4, 3, current_byte, pDescriptorNew);
	write_data(player.b_edit_basicset,	7, 1, current_byte, pDescriptorNew);
	write_data(player.def,				0, 7, current_byte, pDescriptorNew);
	write_data(player.clearing,		7, 7, current_byte, pDescriptorNew);
	write_data(player.header,			6, 7, current_byte, pDescriptorNew);
	write_data(player.mo_hunchd,		5, 3, current_byte, pDescriptorNew);
	write_data(player.mo_hunchr,		0, 3, current_byte, pDescriptorNew);
	write_data(player.mo_pk,			3, 3, current_byte, pDescriptorNew);
	write_data(player.weak_acc,		6, 2, current_byte, pDescriptorNew);
	write_data(player.drib,			0, 7, current_byte, pDescriptorNew);
	write_data(player.injury,			7, 2, current_byte, pDescriptorNew);
	write_data(player.play_attit,		1, 2, current_byte, pDescriptorNew); //Playing attitude
	write_data(player.mo_drib,			3, 2, current_byte, pDescriptorNew); //Dribbling motion
	write_data(player.play_pos[12],	5, 2, current_byte, pDescriptorNew); //GK
	write_data(player.play_pos[9],		7, 2, current_byte, pDescriptorNew); //CB
	write_data(player.play_pos[10],	1, 2, current_byte, pDescriptorNew); //LB
	write_data(player.play_pos[11],	3, 2, current_byte, pDescriptorNew); //RB
	write_data(player.play_pos[5],		5, 2, current_byte, pDescriptorNew); //DMF
	write_data(player.play_pos[6],		7, 2, current_byte, pDescriptorNew); //CMF
	write_data(player.play_pos[7],		1, 2, current_byte, pDescriptorNew); //LMF
	write_data(player.play_pos[8],		3, 2, current_byte, pDescriptorNew); //RMF
	write_data(player.play_pos[4],		5, 2, current_byte, pDescriptorNew); //AMF
	write_data(player.b_edit_regpos,	7, 1, current_byte, pDescriptorNew);
	write_data(player.play_pos[3],		0, 2, current_byte, pDescriptorNew); //RWF
	write_data(player.play_pos[1],		2, 2, current_byte, pDescriptorNew); //SS
	write_data(player.play_pos[0],		4, 2, current_byte, pDescriptorNew); //CF
	write_data(player.reflex,			6, 7, current_byte, pDescriptorNew);
	write_data(player.kick_pwr,		5, 7, current_byte, pDescriptorNew);
	write_data(player.play_pos[2],		4, 2, current_byte, pDescriptorNew); //LWF
	write_data(player.b_edit_playpos,	6, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_ability,	7, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_skill,	0, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_style,	1, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_com,		2, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_motion,	3, 1, current_byte, pDescriptorNew);
	//Unknown C - 1/1
	write_data(player.strong_foot,		5, 1, current_byte, pDescriptorNew);
	write_data(player.strong_hand,		6, 1, current_byte, pDescriptorNew);
	//COM playing styles
	write_data(player.com_style[0],	7, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[1],	0, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[2],	1, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[3],	2, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[4],	3, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[5],	4, 1, current_byte, pDescriptorNew);
	write_data(player.com_style[6],	5, 1, current_byte, pDescriptorNew);
	//Player skills
	write_data(player.play_skill[0],	6, 1, current_byte, pDescriptorNew); //Scissors Feint
	write_data(player.play_skill[28],	7, 1, current_byte, pDescriptorNew); //Double Touch
	write_data(player.play_skill[1],	0, 1, current_byte, pDescriptorNew); //Flip flap
	write_data(player.play_skill[2],	1, 1, current_byte, pDescriptorNew); //Marseille turn
	write_data(player.play_skill[3],	2, 1, current_byte, pDescriptorNew); //Sombrero
	write_data(player.play_skill[29],	3, 1, current_byte, pDescriptorNew); //Crossover Turn
	write_data(player.play_skill[4],	4, 1, current_byte, pDescriptorNew); //Cut Behind & Turn
	write_data(player.play_skill[5],	5, 1, current_byte, pDescriptorNew); //Scotch Move
	write_data(player.play_skill[30],	6, 1, current_byte, pDescriptorNew); //Step on Skill
	write_data(player.play_skill[6],	7, 1, current_byte, pDescriptorNew); //Heading
	write_data(player.play_skill[7],	0, 1, current_byte, pDescriptorNew); //Long range drive
	write_data(player.play_skill[31],	1, 1, current_byte, pDescriptorNew); //Chip Shot
	write_data(player.play_skill[39],	2, 1, current_byte, pDescriptorNew); //Long range shooting
	write_data(player.play_skill[8],	3, 1, current_byte, pDescriptorNew); //Knuckle shot
	write_data(player.play_skill[32],	4, 1, current_byte, pDescriptorNew); //Dipping Shots
	write_data(player.play_skill[33],	5, 1, current_byte, pDescriptorNew); //Rising Shots
	write_data(player.play_skill[9],	6, 1, current_byte, pDescriptorNew); //Acro finishing
	write_data(player.play_skill[10],	7, 1, current_byte, pDescriptorNew); //Heel trick
	write_data(player.play_skill[11],	0, 1, current_byte, pDescriptorNew); //First time shot
	write_data(player.play_skill[12],	1, 1, current_byte, pDescriptorNew); //One touch pass
	write_data(player.play_skill[40],	2, 1, current_byte, pDescriptorNew); //Through passing
	write_data(player.play_skill[13],	3, 1, current_byte, pDescriptorNew); //Weighted pass
	write_data(player.play_skill[14],	4, 1, current_byte, pDescriptorNew); //Pinpoint crossing
	write_data(player.play_skill[15],	5, 1, current_byte, pDescriptorNew); //Outside curler
	write_data(player.play_skill[16],	6, 1, current_byte, pDescriptorNew); //Rabona
	write_data(player.play_skill[34],	7, 1, current_byte, pDescriptorNew); //No Look Pass
	write_data(player.play_skill[17],	0, 1, current_byte, pDescriptorNew); //Low Lofted Pass
	write_data(player.play_skill[18],	1, 1, current_byte, pDescriptorNew); //Low Punt trajectory
	write_data(player.play_skill[35],	2, 1, current_byte, pDescriptorNew); //GK High Punt Trajectory
	write_data(player.play_skill[19],	3, 1, current_byte, pDescriptorNew); //Long throw
	write_data(player.play_skill[20],	4, 1, current_byte, pDescriptorNew); //GK long throw
	write_data(player.play_skill[36],	5, 1, current_byte, pDescriptorNew); //Penalty Specialist
	write_data(player.play_skill[37],	6, 1, current_byte, pDescriptorNew); //GK Penalty Specialist
	write_data(player.play_skill[21],	7, 1, current_byte, pDescriptorNew); //Malicia
	write_data(player.play_skill[22],	0, 1, current_byte, pDescriptorNew); //Man marking
	write_data(player.play_skill[23],	1, 1, current_byte, pDescriptorNew); //Track back
	write_data(player.play_skill[38],	2, 1, current_byte, pDescriptorNew); //Interception
	write_data(player.play_skill[24],	3, 1, current_byte, pDescriptorNew); //Acro clear
	write_data(player.play_skill[25],	4, 1, current_byte, pDescriptorNew); //Captaincy
	write_data(player.play_skill[26],	5, 1, current_byte, pDescriptorNew); //Super sub
	write_data(player.play_skill[27],	6, 1, current_byte, pDescriptorNew); //Fighting spirit
	current_byte++; //Unknown D 1/1
	
	uint8_t nameBuffer[61];
	memset(nameBuffer, 0, sizeof(nameBuffer));
	int len = WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)nameBuffer, 60, NULL, NULL); //set byte limit to 60 to ensure null termination of truncated strings
	memcpy(&(pDescriptorNew->data[current_byte]), nameBuffer, 61);
	current_byte += 61;
	
	//strcpy_s((char *)&(pDescriptorNew->data[current_byte]), 21, player.shirt_name);
	strncpy_s((char *)&(pDescriptorNew->data[current_byte]), 21, player.shirt_name, 21-1);
	current_byte+=61;

	current_byte+=64; //Print Name (National Team)
	
	//Appearance entries
	//playerID
	current_byte+=4;
	//0x04:0
	write_data(player.b_edit_face,	0, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_hair,	1, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_phys,	2, 1, current_byte, pDescriptorNew);
	write_data(player.b_edit_strip,3, 1, current_byte, pDescriptorNew);
	write_data(player.boot_id,		4, 14, current_byte, pDescriptorNew);
	write_data(player.glove_id,	2, 14, current_byte, pDescriptorNew); //Extended to use 14 bits, using Unk A space
	write_data(player.copy_id,		0, 4*8, current_byte, pDescriptorNew);
	write_data(player.neck_len,	0, 4, current_byte, pDescriptorNew);
	write_data(player.neck_size,	4, 4, current_byte, pDescriptorNew);
	write_data(player.shldr_hi,	0, 4, current_byte, pDescriptorNew);
	write_data(player.shldr_wid,	4, 4, current_byte, pDescriptorNew);
	write_data(player.chest,		0, 4, current_byte, pDescriptorNew);
	write_data(player.waist,		4, 4, current_byte, pDescriptorNew);
	write_data(player.arm_size,	0, 4, current_byte, pDescriptorNew);
	write_data(player.arm_len,		4, 4, current_byte, pDescriptorNew);
	write_data(player.thigh,		0, 4, current_byte, pDescriptorNew);
	write_data(player.calf,		4, 4, current_byte, pDescriptorNew);
	write_data(player.leg_len,		0, 4, current_byte, pDescriptorNew);
	write_data(player.head_len,	4, 4, current_byte, pDescriptorNew);
	write_data(player.head_wid,	0, 4, current_byte, pDescriptorNew);
	write_data(player.head_dep,	4, 4, current_byte, pDescriptorNew);
	write_data(player.wrist_col_l,	0, 3, current_byte, pDescriptorNew);
	write_data(player.wrist_col_r,	3, 3, current_byte, pDescriptorNew);
	write_data(player.wrist_tape,	6, 2, current_byte, pDescriptorNew);
	write_data(player.spec_col,	0, 3, current_byte, pDescriptorNew);
	write_data(player.spec_style,	3, 3, current_byte, pDescriptorNew);
	write_data(player.sleeve,		6, 2, current_byte, pDescriptorNew);
	write_data(player.inners,		0, 2, current_byte, pDescriptorNew);
	write_data(player.socks,		2, 2, current_byte, pDescriptorNew);
	write_data(player.undershorts,	4, 2, current_byte, pDescriptorNew);
	write_data(player.untucked,		6, 1, current_byte, pDescriptorNew);
	write_data(player.ankle_tape,	7, 1, current_byte, pDescriptorNew);
	//0x16:0
	write_data(player.gloves,		0, 1, current_byte, pDescriptorNew);
	write_data(player.gloves_col,	1, 3, current_byte, pDescriptorNew);
	//Skip face settings
	current_byte+=23;
	
	//No custom in 18
	if(player.skin_col==7) player.skin_col=0;
	write_data(player.skin_col,	0, 3, current_byte, pDescriptorNew);
	//Skip additional face settings
	current_byte+=19;
	//0x40:0
	write_data(player.iris_col,	0, 4, current_byte, pDescriptorNew);
	//Skip hair settings
	current_byte+=8;
}


void extract_team_info20(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x210;
		return;
	}
	
	write_data(team.id,		0, 4*8, current_byte, pDescriptorNew);
	write_data(team.manager_id,0, 4*8, current_byte, pDescriptorNew);

	current_byte+=2; //Team emblem

	write_data(team.stadium_id,	0, 2*8, current_byte, pDescriptorNew);

	current_byte+=0xA; //Skip to 0x16
	write_data(team.color1_red,		2, 6, current_byte, pDescriptorNew);
	write_data(team.color1_green,	0, 6, current_byte, pDescriptorNew);
	write_data(team.b_edit_name,	6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited emblem: 1 bit
	write_data(team.color2_green,	0, 6, current_byte, pDescriptorNew);
	write_data(team.color2_blue,	6, 6, current_byte, pDescriptorNew);
	
	current_byte+=2; //Media backdrop colors
	write_data(team.b_edit_stadium, 6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited stadium name: 1 bit

	current_byte+=2; //Stadium settings
	write_data(team.color1_blue,	0, 6, current_byte, pDescriptorNew);
	write_data(team.color2_red,		6, 6, current_byte, pDescriptorNew);

	current_byte+=0x39;
	current_byte+=4; //Rival team ID 1
	current_byte+=4; //Rival team ID 2
	current_byte+=4; //Rival team ID 3
	current_byte+=4; //Banner Edited flags

	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR)&(pDescriptorNew->data[current_byte]), 0x46, NULL, NULL);
	current_byte+=0x46;
	
	strncpy_s((char*)&(pDescriptorNew->data[current_byte]), 0x4, team.short_name, 0x4 - 1);
	current_byte+=0x4;
	
	current_byte+=181; //Stadium name
	current_byte+=16; //Banner 1 text
	current_byte+=16; //Banner 2 text
	current_byte+=16; //Banner 3 text
	current_byte+=16; //Banner 4 text

	current_byte+=105; //Unknown D
}


void extract_team_info21(team_entry team, int& current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if (!team.b_changed)
	{
		current_byte += 0x24C;
		return;
	}

	write_data(team.id, 0, 4 * 8, current_byte, pDescriptorNew);
	write_data(team.manager_id, 0, 4 * 8, current_byte, pDescriptorNew);

	current_byte += 2; //Team emblem

	write_data(team.stadium_id, 0, 2 * 8, current_byte, pDescriptorNew);

	current_byte += 0xA; //Skip to 0x16
	write_data(team.color1_red, 2, 6, current_byte, pDescriptorNew);
	write_data(team.color1_green, 0, 6, current_byte, pDescriptorNew);
	write_data(team.b_edit_name, 6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited emblem: 1 bit
	write_data(team.color2_green, 0, 6, current_byte, pDescriptorNew);
	write_data(team.color2_blue, 6, 6, current_byte, pDescriptorNew);

	current_byte += 2; //Media backdrop colors
	write_data(team.b_edit_stadium, 6, 1, current_byte, pDescriptorNew);
	current_byte++; //Edited stadium name: 1 bit

	current_byte += 2; //Stadium settings
	write_data(team.color1_blue, 0, 6, current_byte, pDescriptorNew);
	write_data(team.color2_red, 6, 6, current_byte, pDescriptorNew);

	current_byte += 0x39;
	current_byte += 4; //Rival team ID 1
	current_byte += 4; //Rival team ID 2
	current_byte += 4; //Rival team ID 3
	current_byte += 4; //Banner Edited flags

	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR) & (pDescriptorNew->data[current_byte]), 0x46, NULL, NULL);
	current_byte += 0x46;

	strncpy_s((char*)&(pDescriptorNew->data[current_byte]), 0x4, team.short_name, 0x4 - 1);
	current_byte += 0x4;

	current_byte += 181; //Stadium name
	current_byte += 16; //Banner 1 text
	current_byte += 16; //Banner 2 text
	current_byte += 16; //Banner 3 text
	current_byte += 16; //Banner 4 text

	current_byte += 165; //Unknown D
}


void extract_teamplayer_info20(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x11C;
		return;
	}
	
	write_data(team.id, 0, 4*8, current_byte, pDescriptorNew);

	for(int ii=0;ii<40;ii++)
	{
		write_data(team.players[ii], 0, 4*8, current_byte, pDescriptorNew);
	}

	for(int ii=0;ii<40;ii++)
	{
		//Player shirt numbers
		write_data(team.numbers[ii], 0, 2*8, current_byte, pDescriptorNew);
	}

	current_byte+=40; //Unknown A
}


void extract_team_tactics20(team_entry team, int &current_byte, void* ghdescriptor)
{
	FileDescriptorNew* pDescriptorNew = (FileDescriptorNew*)ghdescriptor;

	if(!team.b_changed)
	{
		current_byte += 0x274;
		return;
	}
	
	write_data(team.id, 0, 4*8, current_byte, pDescriptorNew);
	
	current_byte+=0x211;
	pDescriptorNew->data[current_byte] = team.captain_ind;

	current_byte+=0x5f;
}