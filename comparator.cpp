#include <string>
#include <sstream>
#include "editor.h"
//#include <Commdlg.h>
#include "crypt.h"
#include "resource.h"

#ifndef UNICODE  
  typedef std::string tstring; 
  typedef std::stringstream tstringstream;
#else
  typedef std::wstring tstring; 
  typedef std::wstringstream tstringstream;
#endif

void compare_data_handler(const TCHAR*, int);
tstring do_comparison(int, player_entry*, int, team_entry*, int);
tstring compare_single_team(int, int, player_entry*, int, team_entry*);

void *hc_descriptor;
player_entry* c_players = NULL;
team_entry* c_teams = NULL;
int c_num_players, c_num_teams;

extern HINSTANCE hPesDecryptDLL; //Handle to libpesXdecrypter.dll
extern pf_createFileDescriptorOld createFileDescriptorOld;
extern pf_createFileDescriptorNew createFileDescriptorNew;
extern pf_destroyFileDescriptorOld destroyFileDescriptorOld;
extern pf_destroyFileDescriptorNew destroyFileDescriptorNew;
extern pf_decryptWithKeyOld decryptWithKeyOld;
extern pf_decryptWithKeyNew decryptWithKeyNew;
extern pf_encryptWithKeyOld encryptWithKeyOld;
extern pf_encryptWithKeyNew encryptWithKeyNew;

void save_comparator(HWND hCompareBox, int nPesVersion, player_entry* gplayers, int gnum_players, team_entry* gteams, int gnum_teams, TCHAR *cs_file_name)
{
//	//Open dialog box to get file path
//	OPENFILENAME ofn;
//	TCHAR cs_file_name[MAX_PATH];
//	TCHAR cs_open_title[40];
//
//	_stprintf_s(cs_open_title, 40, _T("Select PES%d EDIT file for comparison"), nPesVersion);
//
//	ZeroMemory(&ofn, sizeof(ofn));
//
//	ofn.lStructSize = sizeof(OPENFILENAME);
//	ofn.hwndOwner = hCompareBox;
////	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
//	ofn.lpstrFile = cs_file_name;
//	ofn.nMaxFile = MAX_PATH;
//	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
//	ofn.lpstrTitle = cs_open_title;
//
//	if(GetOpenFileName(&ofn))
	{
		compare_data_handler(cs_file_name, nPesVersion);

		//Do comparison between players, teams
		tstring result = do_comparison(nPesVersion, gplayers, gnum_players, gteams, gnum_teams);
		if(result.empty()) result = _T("No changes found!");

		//Display result in dialog box
		SetWindowText(GetDlgItem(hCompareBox, IDT_AATFOUT), result.c_str());

		//Cleanup should go here...
		if(hc_descriptor) 
		{
			if(nPesVersion>=18)
				destroyFileDescriptorNew((FileDescriptorNew*)hc_descriptor);
			else
				destroyFileDescriptorOld((FileDescriptorOld*)hc_descriptor);
			hc_descriptor = NULL;
		}
		if(c_players) 
		{
			delete[] c_players;
			c_players = NULL;
		}
		if(c_teams) 
		{
			delete[] c_teams;
			c_teams = NULL;
		}
	}
}

void compare_data_handler(const TCHAR *pcs_file_name, int nPesVersion)
{
	int ii, current_byte, appearance_byte;
	const uint8_t* pMasterKey;

	if(hc_descriptor) 
	{
		if(nPesVersion>=18)
			destroyFileDescriptorNew((FileDescriptorNew*)hc_descriptor);
		else
			destroyFileDescriptorOld((FileDescriptorOld*)hc_descriptor);
		hc_descriptor = NULL;
	}
	if(c_players) 
	{
		delete[] c_players;
		c_players = NULL;
	}
	if(c_teams) 
	{
		delete[] c_teams;
		c_teams = NULL;
	}

	if(nPesVersion==16)
	{
		hc_descriptor = (void*)createFileDescriptorOld();
		pMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes16");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyOld((FileDescriptorOld*)hc_descriptor, pfin, reinterpret_cast<const char*>(pMasterKey));
		
		//get number of player, team entries
		c_num_players = ((FileDescriptorOld*)hc_descriptor)->data[0x34];
		c_num_players += (((FileDescriptorOld*)hc_descriptor)->data[0x35])*256;
		
		c_num_teams = ((FileDescriptorOld*)hc_descriptor)->data[0x38];
		c_num_teams += (((FileDescriptorOld*)hc_descriptor)->data[0x39])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x4C;
		appearance_byte = 0x2AB9CC;
		c_players = new player_entry[c_num_players];
		for(ii=0;ii<c_num_players;ii++)
		{
			fill_player_entry16(c_players[ii], current_byte, hc_descriptor);
			fill_appearance_entry16(c_players[ii], appearance_byte, hc_descriptor);
		}

		//place team entries into array of structs
		current_byte = 0x46310C;
		c_teams = new team_entry[c_num_teams];
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_ids16(c_teams[ii], current_byte, hc_descriptor);
		}

		current_byte = 0x4FCC6C;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_rosters16(current_byte, hc_descriptor, c_teams, c_num_teams);
		}

		current_byte = 0x51F814;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_tactics16(current_byte, hc_descriptor, c_teams, c_num_teams);
		}
	}
	else if(nPesVersion==17)
	{
		hc_descriptor = (void*)createFileDescriptorOld();
		pMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes17");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyOld((FileDescriptorOld*)hc_descriptor, pfin, reinterpret_cast<const char*>(pMasterKey));

		//get number of player, team entries
		c_num_players = ((FileDescriptorOld*)hc_descriptor)->data[0x5C];
		c_num_players += (((FileDescriptorOld*)hc_descriptor)->data[0x5D])*256;

		c_num_teams = ((FileDescriptorOld*)hc_descriptor)->data[0x60];
		c_num_teams += (((FileDescriptorOld*)hc_descriptor)->data[0x61])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x78;
		c_players = new player_entry[c_num_players];
		for(ii=0;ii<c_num_players;ii++)
		{
			fill_player_entry17(c_players[ii], current_byte, hc_descriptor);
		}

		//place team entries into array of structs
		current_byte = 0x3C3E58;
		c_teams = new team_entry[c_num_teams];
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_ids17(c_teams[ii], current_byte, hc_descriptor);
		}

		current_byte = 0x475A90;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_rosters17(current_byte, hc_descriptor, c_teams, c_num_teams);
		}

		current_byte = 0x490640;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_tactics17(current_byte, hc_descriptor, c_teams, c_num_teams);
		}
	}
	else if(nPesVersion==18)
	{
		hc_descriptor = (void*)createFileDescriptorNew();
		pMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes18");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		//try
		//{
			decryptWithKeyNew((FileDescriptorNew*)hc_descriptor, pfin, reinterpret_cast<const char*>(pMasterKey));
		//}
		//catch(...)
		//{
		//	MessageBox(ghw_main, _T("Bad file, cannot load."), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		//	return;
		//}

		//get number of player, team entries
		c_num_players = ((FileDescriptorNew*)hc_descriptor)->data[96];
		c_num_players += (((FileDescriptorNew*)hc_descriptor)->data[97])*256;

		c_num_teams = ((FileDescriptorNew*)hc_descriptor)->data[100];
		c_num_teams += (((FileDescriptorNew*)hc_descriptor)->data[101])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x7C;
		c_players = new player_entry[c_num_players];
		for(ii=0;ii<c_num_players;ii++)
		{
			fill_player_entry18(c_players[ii], current_byte, hc_descriptor);
		}

		//place team entries into array of structs
		current_byte = 0x3C3E5C;
		c_teams = new team_entry[c_num_teams];
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_ids18(c_teams[ii], current_byte, hc_descriptor);
		}

		current_byte = 0x46FF54;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_rosters18(current_byte, hc_descriptor, c_teams, c_num_teams);
		}

		current_byte = 0x488B74;
		for(ii=0;ii<c_num_teams;ii++)
		{
			fill_team_tactics18(current_byte, hc_descriptor, c_teams, c_num_teams);
		}
	}
	else // PES 19
	{
		hc_descriptor = (void*)createFileDescriptorNew();
		pMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes19");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		//try
		//{
			decryptWithKeyNew((FileDescriptorNew*)hc_descriptor, pfin, reinterpret_cast<const char*>(pMasterKey));
		//}
		//catch(...)
		//{
		//	MessageBox(ghw_main, _T("Bad file, cannot load."), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		//	return;
		//}

		//get number of player, team entries
		c_num_players = ((FileDescriptorNew*)hc_descriptor)->data[96];
		c_num_players += (((FileDescriptorNew*)hc_descriptor)->data[97])*256;

		c_num_teams = ((FileDescriptorNew*)hc_descriptor)->data[100];
		c_num_teams += (((FileDescriptorNew*)hc_descriptor)->data[101])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x7C;
		c_players = new player_entry[c_num_players];
		for(int ii=0;ii<c_num_players;ii++)
		{
			fill_player_entry19(c_players[ii], current_byte, hc_descriptor);
		}

		//place team entries into array of structs
		current_byte = 0x5BCC7C;
		c_teams = new team_entry[c_num_teams];
		for(int ii=0;ii<c_num_teams;ii++)
		{
			fill_team_ids19(c_teams[ii], current_byte, hc_descriptor);
		}

		current_byte = 0x6773C4;
		for(int ii=0;ii<c_num_teams;ii++)
		{
			fill_team_rosters19(current_byte, hc_descriptor, c_teams, c_num_teams);
		}

		current_byte = 0x69EC8C;
		for(int ii=0;ii<c_num_teams;ii++)
		{
			fill_team_tactics19(current_byte, hc_descriptor, c_teams, c_num_teams);
		}
	}

	//Find, hide loose players
	int jj, kk;
	for(ii=0;ii<c_num_players;ii++)
	{
		bool match = false;
		for(jj=0;jj<c_num_teams;jj++)
		{
			for(kk=0;kk<32;kk++)
			{
				if(c_teams[jj].players[kk]==c_players[ii].id)
				{
					match = true;
					break;
				}
			}
			if(match)
			{
				c_players[ii].team_ind = jj;
				c_players[ii].team_lineup_ind = kk;
				break;
			}
		}
		if(c_players[ii].team_ind < 0) 
		{
			c_players[ii].b_show = false;
		}
	}

	//

}


tstring do_comparison(int nPesVersion, player_entry* gplayers, int gnum_players, team_entry* gteams, int gnum_teams)
{
	int ii,num_teams;
	tstring msgOut=_T("");
	tstringstream errorMsg;

	if(gnum_teams!=c_num_teams)
	{
		errorMsg << _T("WARNING: Number of teams differs, A: ") << gnum_teams <<_T(", B: ") << c_num_teams << _T("\r\n");
		num_teams = min(gnum_teams, c_num_teams);
		msgOut+=errorMsg.str();
	}
	else
		num_teams = gnum_teams;

	for(ii=0;ii<num_teams;ii++)
	{
		msgOut += compare_single_team(nPesVersion, ii, gplayers, gnum_players, gteams);
	}

	return msgOut;
}


tstring compare_single_team(int pesVersion, int teamSel, player_entry* gplayers, int gnum_players, team_entry* gteams)
{
	player_entry playerA, playerB;
	tstring msgOut = _T("Changes for ");
	msgOut += gteams[teamSel].name;
	msgOut += _T(":\r\n");
	tstringstream errorMsg;
	//msgOut+=_T("Team: ");
	//msgOut+=gteams[teamSel].name;
	//msgOut+=_T("\r\n");

	int num_on_team;

	if(gteams[teamSel].num_on_team != c_teams[teamSel].num_on_team)
	{
		errorMsg << _T("WARNING: Size of squad differs, A: ") << gteams[teamSel].num_on_team <<_T(", B: ") <<
			c_teams[teamSel].num_on_team << _T("\r\n");
		num_on_team = min(gteams[teamSel].num_on_team, c_teams[teamSel].num_on_team);
	}
	else
		num_on_team = gteams[teamSel].num_on_team;

	//Compare captains

	for(int ii=0; ii<num_on_team; ii++)
	{
		//Find each player on team
		for(int jj=0; jj<gnum_players; jj++)
		{
			if(gplayers[jj].id == gteams[teamSel].players[ii])
			{
				playerA = gplayers[jj];
				break;
			}
		}

		for(int jj=0; jj<c_num_players; jj++)
		{
			if(c_players[jj].id == c_teams[teamSel].players[ii])
			{
				playerB = c_players[jj];
				break;
			}
		}

		if(playerA == playerB) continue;
		errorMsg << _T("    Player ") << ii+1 << _T(" (PID ") << playerA.id << _T(")\r\n");

		if(wcscmp(playerA.name, playerB.name)!=0) 
			errorMsg << _T("\tName: ") << playerA.name <<_T(" / ") << playerB.name <<_T("\r\n");
		if(strcmp(playerA.shirt_name, playerB.shirt_name)!=0)
			errorMsg << _T("\tShirt Name: ") << playerA.shirt_name <<_T(" / ") << playerB.shirt_name <<_T("\r\n");
		if(playerA.id!=playerB.id)
			errorMsg << _T("\tPlayerID: ") << playerA.id <<_T(" / ") << playerB.id <<_T("\r\n");
		if(playerA.age!=playerB.age)
			errorMsg << _T("\tAge: ") << (int)playerA.age <<_T(" / ") << (int)playerB.age <<_T("\r\n");
		if(playerA.height!=playerB.height)
			errorMsg << _T("\tHeight: ") << (int)playerA.height <<_T(" / ") << (int)playerB.height <<_T("\r\n");
		if(playerA.weight!=playerB.weight)
			errorMsg << _T("\tWeight: ") << (int)playerA.weight <<_T(" / ") << (int)playerB.weight <<_T("\r\n");
		if(playerA.atk!=playerB.atk)
			errorMsg << _T("\tatk: ") << (int)playerA.atk <<_T(" / ") << (int)playerB.atk <<_T("\r\n");
		if(playerA.ball_ctrl!=playerB.ball_ctrl)
			errorMsg << _T("\tball_ctrl: ") << (int)playerA.ball_ctrl <<_T(" / ") << (int)playerB.ball_ctrl <<_T("\r\n");
		if(playerA.ball_win!=playerB.ball_win)
			errorMsg << _T("\tball_win: ") << (int)playerA.ball_win <<_T(" / ") << (int)playerB.ball_win <<_T("\r\n");
		if(playerA.body_ctrl!=playerB.body_ctrl)
			errorMsg << _T("\tbody_ctrl: ") << (int)playerA.body_ctrl <<_T(" / ") << (int)playerB.body_ctrl <<_T("\r\n");
		if(playerA.catching!=playerB.catching)
			errorMsg << _T("\tcatching: ") << (int)playerA.catching <<_T(" / ") << (int)playerB.catching <<_T("\r\n");
		if(playerA.clearing!=playerB.clearing)
			errorMsg << _T("\tclearing: ") << (int)playerA.clearing <<_T(" / ") << (int)playerB.clearing <<_T("\r\n");
//		(playerA.copy_id!=playerB.copy_id);
		if(playerA.cover!=playerB.cover)
			errorMsg << _T("\tcover: ") << (int)playerA.cover <<_T(" / ") << (int)playerB.cover <<_T("\r\n");
		if(playerA.def!=playerB.def)
			errorMsg << _T("\tdef: ") << (int)playerA.def <<_T(" / ") << (int)playerB.def <<_T("\r\n");
		if(playerA.drib!=playerB.drib)
			errorMsg << _T("\tdrib: ") << (int)playerA.drib <<_T(" / ") << (int)playerB.drib <<_T("\r\n");
		if(playerA.exp_pwr!=playerB.exp_pwr)
			errorMsg << _T("\texp_pwr: ") << (int)playerA.exp_pwr <<_T(" / ") << (int)playerB.exp_pwr <<_T("\r\n");
		if(playerA.finish!=playerB.finish)
			errorMsg << _T("\tfinish: ") << (int)playerA.finish <<_T(" / ") << (int)playerB.finish <<_T("\r\n");
		if(playerA.gk!=playerB.gk)
			errorMsg << _T("\tgk: ") << (int)playerA.gk <<_T(" / ") << (int)playerB.gk <<_T("\r\n");
		if(playerA.header!=playerB.header)
			errorMsg << _T("\theader: ") << (int)playerA.header <<_T(" / ") << (int)playerB.header <<_T("\r\n");
		if(playerA.jump!=playerB.jump)
			errorMsg << _T("\tjump: ") << (int)playerA.jump <<_T(" / ") << (int)playerB.jump <<_T("\r\n");
		if(playerA.kick_pwr!=playerB.kick_pwr)
			errorMsg << _T("\tkick_pwr: ") << (int)playerA.kick_pwr <<_T(" / ") << (int)playerB.kick_pwr <<_T("\r\n");
		if(playerA.loftpass!=playerB.loftpass)
			errorMsg << _T("\tloftpass: ") << (int)playerA.loftpass <<_T(" / ") << (int)playerB.loftpass <<_T("\r\n");
		if(playerA.lowpass!=playerB.lowpass)
			errorMsg << _T("\tlowpass: ") << (int)playerA.lowpass <<_T(" / ") << (int)playerB.lowpass <<_T("\r\n");
		//if(playerA.nation!=playerB.nation)
		//	errorMsg << _T("\tName: ") << (int)playerA.name <<_T(" / ") << (int)playerB.name <<_T("\r\n");
		if(pesVersion!=16 && playerA.phys_cont!=playerB.phys_cont)
			errorMsg << _T("\tphys_cont: ") << (int)playerA.phys_cont <<_T(" / ") << (int)playerB.phys_cont <<_T("\r\n");
		if(playerA.place_kick!=playerB.place_kick)
			errorMsg << _T("\tplace_kick: ") << (int)playerA.place_kick <<_T(" / ") << (int)playerB.place_kick <<_T("\r\n");
		if(playerA.play_style!=playerB.play_style)
			errorMsg << _T("\tplay_style: ") << (int)playerA.play_style <<_T(" / ") << (int)playerB.play_style <<_T("\r\n");
		if(playerA.reflex!=playerB.reflex)
			errorMsg << _T("\treflex: ") << (int)playerA.reflex <<_T(" / ") << (int)playerB.reflex <<_T("\r\n");
		if(playerA.reg_pos!=playerB.reg_pos)
			errorMsg << _T("\treg_pos: ") << (int)playerA.reg_pos <<_T(" / ") << (int)playerB.reg_pos <<_T("\r\n");
		if(playerA.speed!=playerB.speed)
			errorMsg << _T("\tspeed: ") << (int)playerA.speed <<_T(" / ") << (int)playerB.speed <<_T("\r\n");
		if(playerA.stamina!=playerB.stamina)
			errorMsg << _T("\tstamina: ") << (int)playerA.stamina <<_T(" / ") << (int)playerB.stamina <<_T("\r\n");
		if(playerA.strong_foot!=playerB.strong_foot)
			errorMsg << _T("\tstrong_foot: ") << (int)playerA.strong_foot <<_T(" / ") << (int)playerB.strong_foot <<_T("\r\n");
		if(playerA.swerve!=playerB.swerve)
			errorMsg << _T("\tswerve: ") << (int)playerA.swerve <<_T(" / ") << (int)playerB.swerve <<_T("\r\n");

		if(playerA.form!=playerB.form)
			errorMsg << _T("\tForm: ") << (int)playerA.form <<_T(" / ") << (int)playerB.form <<_T("\r\n");
		if(playerA.injury!=playerB.injury)
			errorMsg << _T("\tInjury resist: ") << (int)playerA.injury <<_T(" / ") << (int)playerB.injury <<_T("\r\n");
		if(playerA.weak_acc!=playerB.weak_acc)
			errorMsg << _T("\tWeak foot acc: ") << (int)playerA.weak_acc <<_T(" / ") << (int)playerB.weak_acc <<_T("\r\n");
		if(playerA.weak_use!=playerB.weak_use)
			errorMsg << _T("\tWeak foot use: ") << (int)playerA.weak_use <<_T(" / ") << (int)playerB.weak_use <<_T("\r\n");
		for(int kk=0;kk<13;kk++) 
		{
			if(playerA.play_pos[kk]!=playerB.play_pos[kk])
				errorMsg << _T("\tPlayable position ")<<kk+1<<_T(": ") << (int)playerA.play_pos[kk] <<_T(" / ") << 
					(int)playerB.play_pos[kk] <<_T("\r\n");
		}
		for(int kk=0;kk<7;kk++)
		{
			if(playerA.com_style[kk]!=playerB.com_style[kk])
				errorMsg <<_T("\tCOM style ")<<kk+1<<_T(": ") << (int)playerA.com_style[kk] <<_T(" / ") << 
					(int)playerB.com_style[kk] <<_T("\r\n");
		}
		int numSkill;
		if(pesVersion==19) numSkill=39;
		else numSkill=28;
		for(int kk=0;kk<numSkill;kk++)
		{
			if(playerA.play_skill[kk]!=playerB.play_skill[kk])
				errorMsg <<_T("\tPlayer skill ")<<kk+1<<_T(": ")<< (int)playerA.play_skill[kk] <<_T(" / ") <<
					(int)playerB.play_skill[kk] <<_T("\r\n");
		}
		tstring testdeb = errorMsg.str();
		int kkjj=0;
	}

	if(errorMsg.rdbuf()->in_avail())
	{
		msgOut+=errorMsg.str();
		msgOut+=_T("\r\n");
		//errorMsg.clear();
		//errorMsg.str(tstring());
	}
	else
		msgOut = _T("");
    
	return msgOut;
}