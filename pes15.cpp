#include "editor.h"

void build_appearance_map15(appearance_map& umap_pid_to_startByte, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;
	//Appearance entries
	int pid, startByte;
	startByte = current_byte;
	pid = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	umap_pid_to_startByte[pid] = startByte;

	current_byte = startByte + 0x44; //Advance by length of 1 Appearance Entry
}

void read_player_entry15(player_entry& player, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	player.id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	//Commentary Name
	//Unknown A
	current_byte += 0x6;

	player.nation = read_data15(0, 2 * 8, current_byte, pDescriptor15); //0xA

	player.height = pDescriptor15->data[current_byte]; //0xC
	current_byte++;

	player.weight = pDescriptor15->data[current_byte]; //0xD
	current_byte++;

	player.gc1 = pDescriptor15->data[current_byte]; //0xE
	current_byte++;

	player.gc2 = pDescriptor15->data[current_byte]; //0xF
	current_byte++;

	player.atk = read_data15(0, 7, current_byte, pDescriptor15); //0x10

	player.def = read_data15(7, 7, current_byte, pDescriptor15); //0x10:7
	
	player.gk = read_data15(6, 7, current_byte, pDescriptor15); //0x11:6

	//Unknown B 0x12:5
	current_byte++;

	player.mo_fk = read_data15(4, 4, current_byte, pDescriptor15); //0x13:4

	player.ball_ctrl = read_data15(0, 7, current_byte, pDescriptor15); //0x14

	player.finish = read_data15(7, 7, current_byte, pDescriptor15); //0x14:7

	player.lowpass = read_data15(6, 7, current_byte, pDescriptor15);

	player.loftpass = read_data15(5, 7, current_byte, pDescriptor15); //0x16:5

	player.weak_acc = read_data15(4, 2, current_byte, pDescriptor15); //0x17:4

	//Unknown C - 1 bit

	player.b_edit_player = read_data15(7, 1, current_byte, pDescriptor15); //0x17:7

	player.place_kick = read_data15(0, 7, current_byte, pDescriptor15); //0x18

	player.swerve = read_data15(7, 7, current_byte, pDescriptor15);

	player.catching = read_data15(6, 7, current_byte, pDescriptor15); //0x19:6 - called "Saving" in 15

	player.speed = read_data15(5, 7, current_byte, pDescriptor15);

	player.form = read_data15(4, 3, current_byte, pDescriptor15); //0x1B:4

	//Unknown D - 1 bit 0x1B:7
	current_byte++;

	player.exp_pwr = read_data15(0, 7, current_byte, pDescriptor15); //0x1C:0

	player.jump = read_data15(7, 7, current_byte, pDescriptor15); //0x1C:7

	player.stamina = read_data15(6, 7, current_byte, pDescriptor15); //0x1D:6

	player.age = read_data15(5, 6, current_byte, pDescriptor15); //0x1E:5

	player.reg_pos = read_data15(3, 4, current_byte, pDescriptor15); //0x1F:3

	//Unknown E - 1 bit 0x1F:7
	current_byte++;

	player.play_style = read_data15(0, 5, current_byte, pDescriptor15); //0x20:0

	player.drib = read_data15(5, 7, current_byte, pDescriptor15); //0x20:5

	player.header = read_data15(4, 7, current_byte, pDescriptor15); //0x21:4

	player.body_ctrl = read_data15(3, 7, current_byte, pDescriptor15); //0x22:3

	player.injury = read_data15(2, 2, current_byte, pDescriptor15); //0x23:2

	//Unknown F - 1 bit 0x23:4

	player.mo_armd = read_data15(5, 3, current_byte, pDescriptor15); //0x23:5

	player.mo_armr = read_data15(0, 3, current_byte, pDescriptor15); //0x24:0

	player.mo_ck = read_data15(3, 3, current_byte, pDescriptor15); //0x24:3

	player.weak_use = read_data15(6, 2, current_byte, pDescriptor15); //0x24:6

	player.play_pos[0] = read_data15(0, 2, current_byte, pDescriptor15); //0x25:0
	player.play_pos[1] = read_data15(2, 2, current_byte, pDescriptor15);
	player.play_pos[2] = read_data15(4, 2, current_byte, pDescriptor15);
	player.play_pos[3] = read_data15(6, 2, current_byte, pDescriptor15);
	player.play_pos[4] = read_data15(0, 2, current_byte, pDescriptor15);
	player.play_pos[5] = read_data15(2, 2, current_byte, pDescriptor15);
	player.play_pos[6] = read_data15(4, 2, current_byte, pDescriptor15);
	player.play_pos[7] = read_data15(6, 2, current_byte, pDescriptor15);
	player.play_pos[8] = read_data15(0, 2, current_byte, pDescriptor15);
	player.play_pos[9] = read_data15(2, 2, current_byte, pDescriptor15);
	player.play_pos[10] = read_data15(4, 2, current_byte, pDescriptor15);
	player.play_pos[11] = read_data15(6, 2, current_byte, pDescriptor15);
	player.play_pos[12] = read_data15(0, 2, current_byte, pDescriptor15); //0x28:0

	player.mo_hunchd = read_data15(2, 2, current_byte, pDescriptor15); //0x28:2

	player.mo_hunchr = read_data15(4, 2, current_byte, pDescriptor15); //0x28:4

	player.mo_pk = read_data15(6, 2, current_byte, pDescriptor15); //0x28:6

	player.ball_win = read_data15(0, 7, current_byte, pDescriptor15); //0x29:0

	player.kick_pwr = read_data15(7, 7, current_byte, pDescriptor15); //0x29:7

	//Unknown G - 2 bits 0x2A:6
	current_byte++;
	//Edited Age? //0x2B:0
	//Edited Footing? //0x2B:1

	player.b_base_copy = read_data15(2, 1, current_byte, pDescriptor15); //0x2B:2

	player.b_edit_basicset = read_data15(3, 1, current_byte, pDescriptor15); //Edited Player Settings? 0x2B:3

	//Unknown H - 6 bits 0x2B:4
	current_byte++;

	player.strong_foot = read_data15(2, 1, current_byte, pDescriptor15); //0x2C:2

	player.com_style[0] = read_data15(3, 1, current_byte, pDescriptor15); //0x2C:3
	player.com_style[1] = read_data15(4, 1, current_byte, pDescriptor15);
	player.com_style[2] = read_data15(5, 1, current_byte, pDescriptor15);
	player.com_style[3] = read_data15(6, 1, current_byte, pDescriptor15);
	player.com_style[4] = read_data15(7, 1, current_byte, pDescriptor15);
	player.com_style[5] = read_data15(0, 1, current_byte, pDescriptor15);
	player.com_style[6] = read_data15(1, 1, current_byte, pDescriptor15); //0x2D:1

	player.play_skill[0] = read_data15(2, 1, current_byte, pDescriptor15); //0x2D:2
	player.play_skill[1] = read_data15(3, 1, current_byte, pDescriptor15);
	player.play_skill[2] = read_data15(4, 1, current_byte, pDescriptor15);
	player.play_skill[3] = read_data15(5, 1, current_byte, pDescriptor15);
	player.play_skill[4] = read_data15(6, 1, current_byte, pDescriptor15);
	player.play_skill[5] = read_data15(7, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[6] Heading
	player.play_skill[7] = read_data15(0, 1, current_byte, pDescriptor15);
	player.play_skill[8] = read_data15(1, 1, current_byte, pDescriptor15);
	player.play_skill[9] = read_data15(2, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[10] Heel Trick
	player.play_skill[11] = read_data15(3, 1, current_byte, pDescriptor15);
	player.play_skill[12] = read_data15(4, 1, current_byte, pDescriptor15);
	player.play_skill[13] = read_data15(5, 1, current_byte, pDescriptor15);
	player.play_skill[14] = read_data15(6, 1, current_byte, pDescriptor15);
	player.play_skill[15] = read_data15(7, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[16] Rabona
	//Removed: player.play_skill[17] Low Lofted Pass
	player.play_skill[18] = read_data15(0, 1, current_byte, pDescriptor15);
	player.play_skill[19] = read_data15(1, 1, current_byte, pDescriptor15);
	player.play_skill[20] = read_data15(2, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[21] Malicia
	player.play_skill[22] = read_data15(3, 1, current_byte, pDescriptor15);
	player.play_skill[23] = read_data15(4, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[24] Acro clear
	player.play_skill[25] = read_data15(5, 1, current_byte, pDescriptor15);
	player.play_skill[26] = read_data15(6, 1, current_byte, pDescriptor15);
	player.play_skill[27] = read_data15(7, 1, current_byte, pDescriptor15); //0x2F:7

	//player.b_edit_regpos = read_data15(7, 1, current_byte, pDescriptor15);

	//player.b_edit_playpos = read_data15(7, 1, current_byte, pDescriptor15);

	//player.b_edit_ability = read_data15(6, 1, current_byte, pDescriptor15);

	//player.b_edit_skill = read_data15(7, 1, current_byte, pDescriptor15);

	//player.b_edit_style = read_data15(7, 1, current_byte, pDescriptor15);

	//player.b_edit_com = read_data15(0, 1, current_byte, pDescriptor15);

	//player.b_edit_motion = read_data15(1, 1, current_byte, pDescriptor15);

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR) & (pDescriptor15->data[current_byte]), -1, player.name, 46); //0x30
	current_byte += 0x2E; //46

	strncpy_s(player.shirt_name, 18, (const char*)&(pDescriptor15->data[current_byte]), 18 - 1); //0x5E
	current_byte += 0x12; //18

	//Block length: 0x70
}


void read_appearance_entry15(player_entry& player, appearance_map& umap_pid_to_startByte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	//Check if played ID has a corresponding start byte in the map, return if not
	auto checkKey = umap_pid_to_startByte.find(player.id);
	if (checkKey == umap_pid_to_startByte.end()) 
		return;

	int current_byte = checkKey->second; //Set current byte to PID start byte
	current_byte += 4; //Advance by 4 to get past 4 byte PID entry

	player.b_edit_face = read_data15(0, 1, current_byte, pDescriptor15);
	player.b_edit_hair = read_data15(1, 1, current_byte, pDescriptor15);
	player.b_edit_phys = read_data15(2, 1, current_byte, pDescriptor15);
	player.b_edit_strip = read_data15(3, 1, current_byte, pDescriptor15);

	player.boot_id = read_data15(4, 14, current_byte, pDescriptor15);

	player.glove_id = read_data15(2, 14, current_byte, pDescriptor15); //Extend to be 14 bits, using Unk B space

	player.copy_id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	player.neck_len = read_data15(0, 4, current_byte, pDescriptor15);

	player.neck_size = read_data15(4, 4, current_byte, pDescriptor15);

	player.shldr_hi = read_data15(0, 4, current_byte, pDescriptor15);

	player.shldr_wid = read_data15(4, 4, current_byte, pDescriptor15);

	player.chest = read_data15(0, 4, current_byte, pDescriptor15);

	player.waist = read_data15(4, 4, current_byte, pDescriptor15);

	player.arm_size = read_data15(0, 4, current_byte, pDescriptor15);

	player.arm_len = read_data15(4, 4, current_byte, pDescriptor15);

	player.thigh = read_data15(0, 4, current_byte, pDescriptor15);

	player.calf = read_data15(4, 4, current_byte, pDescriptor15);

	player.leg_len = read_data15(0, 4, current_byte, pDescriptor15);

	player.head_len = read_data15(4, 4, current_byte, pDescriptor15);

	player.head_wid = read_data15(0, 4, current_byte, pDescriptor15);

	player.head_dep = read_data15(4, 4, current_byte, pDescriptor15);

	player.wrist_col_l = read_data15(0, 3, current_byte, pDescriptor15);
	player.wrist_col_r = read_data15(3, 3, current_byte, pDescriptor15);
	player.wrist_tape = read_data15(6, 2, current_byte, pDescriptor15);

	player.spec_col = read_data15(0, 3, current_byte, pDescriptor15);
	player.spec_style = read_data15(3, 3, current_byte, pDescriptor15);
	player.sleeve = read_data15(6, 2, current_byte, pDescriptor15);

	player.inners = read_data15(0, 2, current_byte, pDescriptor15);
	player.socks = read_data15(2, 2, current_byte, pDescriptor15);
	player.undershorts = read_data15(4, 2, current_byte, pDescriptor15);
	player.untucked = read_data15(6, 1, current_byte, pDescriptor15);
	player.ankle_tape = read_data15(7, 1, current_byte, pDescriptor15);

	player.gloves = read_data15(0, 1, current_byte, pDescriptor15);
	player.gloves_col = read_data15(1, 3, current_byte, pDescriptor15);
	//Unknown D
	current_byte++;

	//Unknown E
	current_byte += 22;

	player.skin_col = read_data15(0, 3, current_byte, pDescriptor15);
	//Unknown F
	current_byte++;

	//Unknown G
	current_byte += 18;

	player.iris_col = read_data15(0, 4, current_byte, pDescriptor15);
	//Unknown H
	current_byte++;

	//Unknown I
	current_byte += 3; //Shortened by 3 compared to 16: 0x44 vs 0x48 block length

	//Block length: 0x44
}


void read_team_ids15(team_entry& team, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	team.id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	current_byte += 0xE;
	team.b_edit_name = read_data15(0, 1, current_byte, pDescriptor15);
	team.b_edit_shortname = read_data15(1, 1, current_byte, pDescriptor15);

	current_byte += 0x82;

	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR) & (pDescriptor15->data[current_byte]), -1, team.name, 0x46);
	current_byte += 0x46;

	strncpy_s(team.short_name, 0x4, (const char*)&(pDescriptor15->data[current_byte]), 0x4 - 1);

	//Remove non alphanumeric characters
	for (int ii = 0; ii < 4; ii++)
	{
		if ((int)team.short_name[ii] < 33 || (int)team.short_name[ii]>95)
			team.short_name[ii] = (char)0;
	}
	current_byte += 0x4;

	current_byte += 0xEA;

	//Block length: 0x1C8
}


void read_team_rosters15(int& current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	int ii, t_ind;
	unsigned long team_id, player_id;

	team_id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	for (t_ind = 0; t_ind < gnum_teams; t_ind++)
	{
		if (team_id == gteams[t_ind].id) break;
	}

	for (ii = 0; ii < 32; ii++)
	{
		player_id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

		gteams[t_ind].players[ii] = player_id;
		if (player_id) gteams[t_ind].num_on_team++; //new
	}
	//Hide team with no players
	if (gteams[t_ind].players[0] == 0)
		gteams[t_ind].b_show = false;

	for (ii = 0; ii < 32; ii++)
	{
		gteams[t_ind].numbers[ii] = pDescriptor15->data[current_byte];
		current_byte++;
	}

	//Block length: 0xA4
}


void read_team_tactics15(int& current_byte, void* ghdescriptor, team_entry* gteams, int gnum_teams)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	int t_ind;
	unsigned long team_id;

	team_id = read_data15(0, 4 * 8, current_byte, pDescriptor15);

	for (t_ind = 0; t_ind < gnum_teams; t_ind++)
	{
		if (team_id == gteams[t_ind].id) break;
	}
	current_byte += 0x1F6;

	gteams[t_ind].captain_ind = (char)pDescriptor15->data[current_byte]; //0x1FA
	current_byte += 0xA; 
	
	//Block length: 0x204
}


//-------------------------------------------------------------------------------------


void write_player_entry15(player_entry player, int& current_byte, appearance_map& umap_pid_to_startByte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	if (!player.b_changed || !player.b_show)
	{
		current_byte += 0x70;
		return;
	}

	write_data15(player.id, 0, 4 * 8, current_byte, pDescriptor15);

	//Commentary Name
	//Unknown A
	current_byte += 0x6;

	write_data15(player.nation, 0, 2 * 8, current_byte, pDescriptor15); //0xA

	write_data15(player.height, 0, 1 * 8, current_byte, pDescriptor15); //0xC

	write_data15(player.weight, 0, 1 * 8, current_byte, pDescriptor15); //0xD

	write_data15(player.gc1, 0, 1 * 8, current_byte, pDescriptor15); //0xE

	write_data15(player.gc2, 0, 1 * 8, current_byte, pDescriptor15); //0xF

	write_data15(player.atk, 0, 7, current_byte, pDescriptor15); //0x10

	write_data15(player.def, 7, 7, current_byte, pDescriptor15); //0x10:7

	write_data15(player.gk, 6, 7, current_byte, pDescriptor15); //0x11:6

	//Unknown B 0x12:5
	current_byte++;

	write_data15(player.mo_fk, 4, 4, current_byte, pDescriptor15); //0x13:4

	write_data15(player.ball_ctrl, 0, 7, current_byte, pDescriptor15); //0x14

	write_data15(player.finish, 7, 7, current_byte, pDescriptor15); //0x14:7

	write_data15(player.lowpass, 6, 7, current_byte, pDescriptor15);

	write_data15(player.loftpass, 5, 7, current_byte, pDescriptor15); //0x16:5

	write_data15(player.weak_acc, 4, 2, current_byte, pDescriptor15); //0x17:4

	//Unknown C - 1 bit

	write_data15(player.b_edit_player, 7, 1, current_byte, pDescriptor15); //0x17:7

	write_data15(player.place_kick, 0, 7, current_byte, pDescriptor15); //0x18

	write_data15(player.swerve, 7, 7, current_byte, pDescriptor15);

	write_data15(player.catching, 6, 7, current_byte, pDescriptor15); //0x19:6 - called "Saving" in 15

	write_data15(player.speed, 5, 7, current_byte, pDescriptor15);

	write_data15(player.form, 4, 3, current_byte, pDescriptor15); //0x1B:4

	//Unknown D - 1 bit 0x1B:7
	current_byte++;

	write_data15(player.exp_pwr, 0, 7, current_byte, pDescriptor15); //0x1C:0

	write_data15(player.jump, 7, 7, current_byte, pDescriptor15); //0x1C:7

	write_data15(player.stamina, 6, 7, current_byte, pDescriptor15); //0x1D:6

	write_data15(player.age, 5, 6, current_byte, pDescriptor15); //0x1E:5

	write_data15(player.reg_pos, 3, 4, current_byte, pDescriptor15); //0x1F:3

	//Unknown E - 1 bit 0x1F:7
	current_byte++;

	write_data15(player.play_style, 0, 5, current_byte, pDescriptor15); //0x20:0

	write_data15(player.drib, 5, 7, current_byte, pDescriptor15); //0x20:5

	write_data15(player.header, 4, 7, current_byte, pDescriptor15); //0x21:4

	write_data15(player.body_ctrl, 3, 7, current_byte, pDescriptor15); //0x22:3

	write_data15(player.injury, 2, 2, current_byte, pDescriptor15); //0x23:2

	//Unknown F - 1 bit 0x23:4

	write_data15(player.mo_armd, 5, 3, current_byte, pDescriptor15); //0x23:5

	write_data15(player.mo_armr, 0, 3, current_byte, pDescriptor15); //0x24:0

	write_data15(player.mo_ck, 3, 3, current_byte, pDescriptor15); //0x24:3

	write_data15(player.weak_use, 6, 2, current_byte, pDescriptor15); //0x24:6

	write_data15(player.play_pos[0], 0, 2, current_byte, pDescriptor15); //0x25:0
	write_data15(player.play_pos[1], 2, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[2], 4, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[3], 6, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[4], 0, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[5], 2, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[6], 4, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[7], 6, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[8], 0, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[9], 2, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[10], 4, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[11], 6, 2, current_byte, pDescriptor15);
	write_data15(player.play_pos[12], 0, 2, current_byte, pDescriptor15); //0x28:0

	write_data15(player.mo_hunchd, 2, 2, current_byte, pDescriptor15); //0x28:2

	write_data15(player.mo_hunchr, 4, 2, current_byte, pDescriptor15); //0x28:4

	write_data15(player.mo_pk, 6, 2, current_byte, pDescriptor15); //0x28:6

	write_data15(player.ball_win, 0, 7, current_byte, pDescriptor15); //0x29:0

	write_data15(player.kick_pwr, 7, 7, current_byte, pDescriptor15); //0x29:7

	//Unknown G - 2 bits 0x2A:6
	current_byte++;
	//Edited Age? //0x2B:0
	//Edited Footing? //0x2B:1

	write_data15(player.b_base_copy, 2, 1, current_byte, pDescriptor15); //0x2B:2

	write_data15(player.b_edit_basicset, 3, 1, current_byte, pDescriptor15); //Edited Player Settings? 0x2B:3

	//Unknown H - 6 bits 0x2B:4
	current_byte++;

	write_data15(player.strong_foot, 2, 1, current_byte, pDescriptor15); //0x2C:2

	write_data15(player.com_style[0], 3, 1, current_byte, pDescriptor15); //0x2C:3
	write_data15(player.com_style[1], 4, 1, current_byte, pDescriptor15);
	write_data15(player.com_style[2], 5, 1, current_byte, pDescriptor15);
	write_data15(player.com_style[3], 6, 1, current_byte, pDescriptor15);
	write_data15(player.com_style[4], 7, 1, current_byte, pDescriptor15);
	write_data15(player.com_style[5], 0, 1, current_byte, pDescriptor15);
	write_data15(player.com_style[6], 1, 1, current_byte, pDescriptor15); //0x2D:1

	write_data15(player.play_skill[0], 2, 1, current_byte, pDescriptor15); //0x2D:2
	write_data15(player.play_skill[1], 3, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[2], 4, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[3], 5, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[4], 6, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[5], 7, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[6] Heading
	write_data15(player.play_skill[7], 0, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[8], 1, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[9], 2, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[10] Heel Trick
	write_data15(player.play_skill[11], 3, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[12], 4, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[13], 5, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[14], 6, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[15], 7, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[16] Rabona
	//Removed: player.play_skill[17] Low Lofted Pass
	write_data15(player.play_skill[18], 0, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[19], 1, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[20], 2, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[21] Malicia
	write_data15(player.play_skill[22], 3, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[23], 4, 1, current_byte, pDescriptor15);
	//Removed: player.play_skill[24] Acro clear
	write_data15(player.play_skill[25], 5, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[26], 6, 1, current_byte, pDescriptor15);
	write_data15(player.play_skill[27], 7, 1, current_byte, pDescriptor15); //0x2F:7

	uint8_t nameBuffer[46];
	memset(nameBuffer, 0, sizeof(nameBuffer));
	int len = WideCharToMultiByte(CP_UTF8, 0, player.name, -1, (LPSTR)nameBuffer, 45, NULL, NULL); //set byte limit to 45 to ensure null termination of truncated strings
	memcpy(&(pDescriptor15->data[current_byte]), nameBuffer, 46);
	current_byte += 46;

	char tbuffer[18];
	memset(tbuffer, 0, 18);
	strncpy_s(tbuffer, 18, player.shirt_name, 18 - 1);
	memcpy(&(pDescriptor15->data[current_byte]), tbuffer, 18);
	current_byte += 18;

	//Block length: 0x70

	//=================================================================================
	//Appearance entries

	//Check if played ID has a corresponding start byte in the map, return if not
	auto checkKey = umap_pid_to_startByte.find(player.id);
	if (checkKey == umap_pid_to_startByte.end())
		return;

	int appear_byte = checkKey->second; //Set current byte to PID start byte
	appear_byte += 4; //Advance by 4 to get past 4 byte PID entry

	write_data15(player.b_edit_face, 0, 1, appear_byte, pDescriptor15);
	write_data15(player.b_edit_hair, 1, 1, appear_byte, pDescriptor15);
	write_data15(player.b_edit_phys, 2, 1, appear_byte, pDescriptor15);
	write_data15(player.b_edit_strip, 3, 1, appear_byte, pDescriptor15);

	write_data15(player.boot_id, 4, 14, appear_byte, pDescriptor15);

	write_data15(player.glove_id, 2, 14, appear_byte, pDescriptor15); //Extend to be 14 bits, using Unk B space

	write_data15(player.copy_id, 0, 4 * 8, appear_byte, pDescriptor15);

	write_data15(player.neck_len, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.neck_size, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.shldr_hi, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.shldr_wid, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.chest, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.waist, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.arm_size, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.arm_len, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.thigh, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.calf, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.leg_len, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.head_len, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.head_wid, 0, 4, appear_byte, pDescriptor15);

	write_data15(player.head_dep, 4, 4, appear_byte, pDescriptor15);

	write_data15(player.wrist_col_l, 0, 3, appear_byte, pDescriptor15);
	write_data15(player.wrist_col_r, 3, 3, appear_byte, pDescriptor15);
	write_data15(player.wrist_tape, 6, 2, appear_byte, pDescriptor15);

	write_data15(player.spec_col, 0, 3, appear_byte, pDescriptor15);
	write_data15(player.spec_style, 3, 3, appear_byte, pDescriptor15);
	write_data15(player.sleeve, 6, 2, appear_byte, pDescriptor15);

	write_data15(player.inners, 0, 2, appear_byte, pDescriptor15);
	write_data15(player.socks, 2, 2, appear_byte, pDescriptor15);
	write_data15(player.undershorts, 4, 2, appear_byte, pDescriptor15);
	write_data15(player.untucked, 6, 1, appear_byte, pDescriptor15);
	write_data15(player.ankle_tape, 7, 1, appear_byte, pDescriptor15);

	write_data15(player.gloves, 0, 1, appear_byte, pDescriptor15);
	write_data15(player.gloves_col, 1, 3, appear_byte, pDescriptor15);
	//Unknown D
	appear_byte++;

	//Unknown E
	appear_byte += 22;

	write_data15(player.skin_col, 0, 3, appear_byte, pDescriptor15);
	//Unknown F
	appear_byte++;

	//Unknown G
	appear_byte += 18;

	write_data15(player.iris_col, 0, 4, appear_byte, pDescriptor15);
	//Unknown H
	appear_byte++;

	//Unknown I
	appear_byte += 3;

	//Block length: 0x44
}


void write_team_info15(team_entry team, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	if (!team.b_changed || !team.b_show)
	{
		current_byte += 0x1C8;
		return;
	}

	//teams.id = read_data15(0, 4 * 8, current_byte, pDescriptor15);
	current_byte += 0x4; //Advance past team ID

	current_byte += 0xE;
	write_data15(team.b_edit_name, 0, 1, current_byte, pDescriptor15);
	write_data15(team.b_edit_shortname, 1, 1, current_byte, pDescriptor15);

	current_byte += 0x82;

	WideCharToMultiByte(CP_UTF8, 0, team.name, -1, (LPSTR) & (pDescriptor15->data[current_byte]), 0x46, NULL, NULL);
	current_byte += 0x46;

	strncpy_s((char*)&(pDescriptor15->data[current_byte]), 0x4, team.short_name, 0x4 - 1);

	current_byte += 0x4;

	current_byte += 0xEA;

	//Block length: 0x1C8
}


void write_teamplayer_info15(team_entry team, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	if (!team.b_changed || !team.b_show)
	{
		current_byte += 0xA4;
		return;
	}

	//write_data15(team_id, 0, 4 * 8, current_byte, pDescriptor15);
	current_byte += 0x4; //Advance past team ID

	for (int ii = 0; ii < 32; ii++)
	{
		write_data15(team.players[ii], 0, 4 * 8, current_byte, pDescriptor15);
	}

	for (int ii = 0; ii < 32; ii++)
	{
		write_data15(team.numbers[ii], 0, 1 * 8, current_byte, pDescriptor15);
	}

	//Block length: 0xA4
}


void write_team_tactics15(team_entry team, int& current_byte, void* ghdescriptor)
{
	FileDescriptor15* pDescriptor15 = (FileDescriptor15*)ghdescriptor;

	if (!team.b_changed)
	{
		current_byte += 0x204;
		return;
	}

	current_byte += 0x4; //Advance past team ID

	current_byte += 0x1F6;

	pDescriptor15->data[current_byte] = team.captain_ind; //0x1FA
	current_byte += 0xA;

	//Block length: 0x204
}
