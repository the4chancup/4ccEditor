#include "editor.h"
#include "resource.h"
#include <stdio.h> 
#include <windowsx.h>

//Boots and glove IDs for FPC are now 55 and 11 respectively in all versions
int iHideBootId = 55;
int iHideGkGloveId = 11;
int iShowBootId = 0;
int iShowGkGloveId = 0;


void disable_fpc_invis_for_displayed_player(HWND hw_tab2, int iPesVersion)
{
	wchar_t buffer[20];
	wchar_t hideBoot[3], hideGkGlove[3], showBoot[3], showGkGlove[3];

	//Boots and glove IDs for FPC are now 55 and 11 respectively in all versions
	swprintf_s(hideBoot, 3, L"%d", iHideBootId);
	swprintf_s(hideGkGlove, 3, L"%d", iHideGkGloveId);

	swprintf_s(showBoot, 3, L"%d", iShowBootId);
	swprintf_s(showGkGlove, 3, L"%d", iShowGkGloveId);

	SendDlgItemMessage(hw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)0, 0); //Set wrist taping to None

	//Get skin color; in pre-Fox PES, Custom skin is invisible, so set any "Custom" skin to "Light"
	GetDlgItemText(hw_tab2, IDC_PHYS_SKIN, buffer, 20);
	if (iPesVersion < 18 && lstrcmp(buffer, L"Custom") == 0)
		SendDlgItemMessage(hw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)1, 0);

	SendDlgItemMessage(hw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)1, 0); //Set sleeves to Short
	SendDlgItemMessage(hw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)0, 0); //Set socks to Standard
	SendDlgItemMessage(hw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)1, 0); //Set shirttail to Untucked
	Button_SetCheck(GetDlgItem(hw_tab2, IDB_STRP_ANTA), BST_UNCHECKED); //Turn off ankle taping

	//Get Boots ID; if it's equal to the hideBoot value, set it to 0
	GetDlgItemText(hw_tab2, IDT_STRP_BOID, buffer, 20);
	if (!lstrcmp(buffer, hideBoot))
		SendDlgItemMessage(hw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)showBoot);

	//Get GK gloves ID; if it's equal to the hideGkGlove value, set it to 0
	GetDlgItemText(hw_tab2, IDT_STRP_GLID, buffer, 20);
	if (!lstrcmp(buffer, hideGkGlove))
		SendDlgItemMessage(hw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)showGkGlove);

	//if(iPesVersion==18) Button_SetCheck(GetDlgItem(hw_tab2, IDB_STRP_GLOV),BST_UNCHECKED); //Uncheck "Gloves?"
}


void enable_fpc_invis_for_displayed_player(HWND hw_tab2, int iPesVersion)
{
	wchar_t buffer[20];
	wchar_t hideBoot[3], hideGkGlove[3], showBoot[3], showGkGlove[3];

	//Boots and glove IDs for FPC are now 55 and 11 respectively in all versions
	swprintf_s(hideBoot, 3, L"%d", iHideBootId);
	swprintf_s(hideGkGlove, 3, L"%d", iHideGkGloveId);

	swprintf_s(showBoot, 3, L"%d", iShowBootId);
	swprintf_s(showGkGlove, 3, L"%d", iShowGkGloveId);

	SendDlgItemMessage(hw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)0, 0); //Set wrist taping to None

	if (iPesVersion < 18)
		SendDlgItemMessage(hw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)7, 0); //Set Skin to "Custom"

	SendDlgItemMessage(hw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)2, 0); //Set sleeves to Long		
	SendDlgItemMessage(hw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)2, 0); //Set socks to Short
	SendDlgItemMessage(hw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)0, 0); //Set shirttail to Tucked
	Button_SetCheck(GetDlgItem(hw_tab2, IDB_STRP_ANTA), BST_UNCHECKED); //Turn off ankle taping
	SendDlgItemMessage(hw_tab2, IDC_STRP_SLIN, CB_SETCURSEL, (WPARAM)0, 0); //Set inners to None
	SendDlgItemMessage(hw_tab2, IDC_STRP_UNDR, CB_SETCURSEL, (WPARAM)0, 0); //Set Undershorts to None

	//Get Boots ID; if it's 0, set to fpcBoot value
	GetDlgItemText(hw_tab2, IDT_STRP_BOID, buffer, 20);
	if (!lstrcmp(buffer, showBoot))
		SendDlgItemMessage(hw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)(hideBoot));

	//Get GK gloves ID; if it's 0, set to fpcGkGlove value
	GetDlgItemText(hw_tab2, IDT_STRP_GLID, buffer, 20);
	if (!lstrcmp(buffer, showGkGlove))
		SendDlgItemMessage(hw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)(hideGkGlove));

	//if (iPesVersion == 18) 
	//	Button_SetCheck(GetDlgItem(hw_tab2, IDB_STRP_GLOV), BST_CHECKED);
	//else 
	Button_SetCheck(GetDlgItem(hw_tab2, IDB_STRP_GLOV), BST_UNCHECKED); //Uncheck "Gloves?"
}


void enable_fpc_invis_for_player(player_entry &player, int iPesVersion)
{
	if (player.untucked) //Shirt to tucked
	{
		player.untucked = false;
		player.b_changed = true;
	}
	if (player.sleeve != 2) //Sleeves to long
	{
		player.sleeve = 2;
		player.b_changed = true;
	}
	if (player.skin_col != 7 && iPesVersion < 18) //Skin to Custom
	{
		player.skin_col = 7;
		player.b_changed = true;
	}
	if (player.boot_id == iShowBootId) //Hide boots
	{
		player.boot_id = iHideBootId;
		player.b_changed = true;
	}
	if (player.glove_id == iShowGkGloveId) //Hide GK gloves
	{
		player.glove_id = iHideGkGloveId;
		player.b_changed = true;
	}
	if (player.socks != 2) //Socks to short
	{
		player.socks = 2;
		player.b_changed = true;
	}
	if (player.wrist_tape != 0) //No wrist tape
	{
		player.wrist_tape = 0;
		player.b_changed = true;
	}
	if (player.ankle_tape) //No ankle tape
	{
		player.ankle_tape = false;
		player.b_changed = true;
	}
	if (player.inners) //No inners
	{
		player.inners = 0;
		player.b_changed = true;
	}
	if (player.undershorts != 0) //No undershorts
	{
		player.undershorts = 0;
		player.b_changed = true;
	}
	if (player.gloves) //No gloves
	{
		player.gloves = false;
		player.b_changed = true;
	}
}


void disable_fpc_invis_for_player(player_entry &player, int iPesVersion)
{
	if (!player.untucked) //Untuck shirt
	{
		player.untucked = true;
		player.b_changed = true;
	}
	if (player.sleeve == 2) //Long sleeves to short
	{
		player.sleeve = 1;
		player.b_changed = true;
	}
	if (player.skin_col == 7 && iPesVersion < 18) //Custom skin to Light
	{
		player.skin_col = 1;
		player.b_changed = true;
	}
	if (player.boot_id == iHideBootId) //Show boots
	{
		player.boot_id = iShowBootId;
		player.b_changed = true;
	}
	if (player.glove_id == iHideGkGloveId) //Show GK gloves
	{
		player.glove_id = iShowBootId;
		player.b_changed = true;
	}
	if (player.socks == 2) //Short socks to standard
	{
		player.socks = 0;
		player.b_changed = true;
	}
	if (player.wrist_tape != 0) //Wrist tape off
	{
		player.wrist_tape = 0;
		player.b_changed = true;
	}
	if (player.ankle_tape) //Ankle tape off
	{
		player.ankle_tape = false;
		player.b_changed = true;
	}
}