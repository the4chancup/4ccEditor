
#include "resource.h"
#include "editor.h"
#include "window.h"

void setup_main(HWND H)
{
	HWND hw_new, hw_bud;
	int x1, x2, x3, x4, x5, x6;

	hw_new = CreateWindowEx(NULL, _T("Static"), _T("Select team:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		20, 24, 80, 20, H, (HMENU)IDC_STATIC_G1, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		100, 20, 170, 200, H, (HMENU)IDC_TEAM_LIST, GetModuleHandle(NULL), NULL);
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("ALL"));
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb_cntl_proc);
	
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("SysListView32"), _T(""), 
		LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOCOLUMNHEADER | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		20, 50, 250, 452, H, (HMENU)IDC_NAME_LIST, GetModuleHandle(NULL), NULL);	
	ListView_SetExtendedListViewStyle(hw_new, LVS_EX_FULLROWSELECT);
	LVCOLUMN lvc;
	memset(&lvc,0,sizeof(lvc)); //Zero out struct members
	RECT rc_lv;
	GetClientRect(hw_new, &rc_lv);
	lvc.mask=LVCF_WIDTH;	//Type of mask
	lvc.cx = rc_lv.right;
	SendMessage(hw_new,LVM_INSERTCOLUMN,0,(LPARAM)&lvc);
	setup_control(hw_new, ghFont, lv_cntl_proc);

	hw_new = CreateWindowEx(0, _T("msctls_updown32"), NULL, 
		WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		270, 470, 20, 33, H, (HMENU)IDB_MOVE_PLYR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Make Gold Medal"), 
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		20, 520, 250, 26, H, (HMENU)IDB_MAKE_GOLD, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Make Silver Medal"), 
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, //| WS_DISABLED 
		20, 552, 250, 26, H, (HMENU)IDB_MAKE_SILV, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Make Regular"), 
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		20, 584, 110, 26, H, (HMENU)IDB_MAKE_REGU, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Set Stats to:"), 
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		140, 584, 80, 26, H, (HMENU)IDB_SET_STATS, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		230, 585, 40, 23, H, (HMENU)IDT_SET_STATS, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, H, (HMENU)IDC_SET_STATS, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(99, 40));
	SendMessage(hw_new, WM_SETTEXT, 0, (LPARAM)_T("77"));

	//ghw_basic = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_BASIC), H, NULL);
	x1=309-18, x2=376, x3=394-18, x4=403-18, x5=430, x6=475;

	hw_new = CreateWindowEx(0, _T("Button"), _T("General Info"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		280, 9, 240, 433, H, (HMENU)IDC_STATIC_B1, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Player name:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 33, 70, 17, H, (HMENU)IDC_STATIC_B2, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, 50, 219, 23, H, (HMENU)IDT_PLAY_NAME, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Player ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 82, 53, 17, H, (HMENU)IDC_STATIC_B3, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_READONLY | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, 99, 88, 23, H, (HMENU)IDT_PLAY_ID, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Shirt name:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x4, 82, 70, 17, H, (HMENU)IDC_STATIC_B4, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x4, 99, 125, 23, H, (HMENU)IDT_PLAY_SHIRT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Team name:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 131, 70, 17, H, (HMENU)IDC_STATIC_B5, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, 148, 219, 23, H, (HMENU)IDT_TEAM_NAME, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Team ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 180, 70, 17, H, (HMENU)IDC_STATIC_B6, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_READONLY | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, 197, 88, 23, H, (HMENU)IDT_TEAM_ID, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Team abbr.:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x4, 180, 70, 17, H, (HMENU)IDC_STATIC_B7, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x4, 197, 125, 23, H, (HMENU)IDT_TEAM_SHORT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 3, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Height (cm):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 232, 70, 17, H, (HMENU)IDC_STATIC_B10, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, 228, 35, 23, H, (HMENU)IDT_PLAY_HGT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 3, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Weight (kg):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 264, 70, 17, H, (HMENU)IDC_STATIC_B11, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, 260, 35, 23, H, (HMENU)IDT_PLAY_WGT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 3, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Age:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 296, 70, 17, H, (HMENU)IDC_STATIC_B12, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, 292, 35, 23, H, (HMENU)IDT_PLAY_AGE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Shirt #:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x5, 232, 70, 17, H, (HMENU)IDC_STATIC_B9, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x6, 228, 35, 23, H, (HMENU)IDT_PLAY_NUM, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 3, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Nation:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x5, 264, 70, 17, H, (HMENU)IDC_STATIC_B8, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x6, 260, 35, 23, H, (HMENU)IDT_PLAY_NAT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 3, 0);

	hw_new = CreateWindowEx(0, _T("Button"), _T(" Is Captain"), 
		BS_RADIOBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x5, 292, 85, 26, H, (HMENU)IDB_CAPTAIN, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Edited/created player"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, 324, 193, 17, H, (HMENU)IDB_PLAY_EDIT, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Stronger foot:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 352, 105, 17, H, (HMENU)IDC_STATIC_B13, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x3, 348, 134, 100, H, (HMENU)IDC_PLAY_FOOT, GetModuleHandle(NULL), NULL);
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Right foot"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Left foot"));
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Registered pos.:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 382, 105, 17, H, (HMENU)IDC_STATIC_B14, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x3, 378, 134, 120, H, (HMENU)IDC_PLAY_RPOS, GetModuleHandle(NULL), NULL);
	//Fill combobox
	int numPositions = 13;
	for (int ii = 0; ii < numPositions; ii++)
	{
		SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)gpc_positions[ii]);
	}
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Playing style:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, 412, 105, 17, H, (HMENU)IDC_STATIC_B15, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x3, 408, 134, 120, H, (HMENU)IDC_PLAY_STYL, GetModuleHandle(NULL), NULL);
	//Fill combobox
	int numPlayStyles = 18;
	for (int ii = 0; ii < numPlayStyles; ii++)
	{
		SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)gpc_playstyle18[ii]);
	}
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, onto_tab_proc);
	
	hw_new = CreateWindowEx(NULL, _T("Static"), NULL, 
         SS_BITMAP | WS_CHILD | WS_VISIBLE, 
         310, 450, 180, 180, H, (HMENU)IDC_LOGO, GetModuleHandle(NULL), NULL);
	HBITMAP hb_logo = (HBITMAP)LoadImage(ghinst, MAKEINTRESOURCE(IDB_4CCLOGO), IMAGE_BITMAP, 180, 180, LR_LOADTRANSPARENT);
	//HBITMAP hb_logo = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_4CCLOGO));
	SendMessage(hw_new, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hb_logo);
	setup_control(hw_new, ghFont, scale_static_proc);

	ghw_tabcon = CreateWindowEx(WS_EX_CONTROLPARENT, _T("SysTabControl32"), _T(""), 
		TCS_OWNERDRAWFIXED | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		530, 4, 555+144, 620, H, (HMENU)IDC_TAB_MAIN, GetModuleHandle(NULL), NULL);
	setup_control(ghw_tabcon, ghFont, from_tab_proc);

	TCITEM ti;
	ti.mask = TCIF_TEXT; //Tab displays text only
	ti.pszText = _T("Stats"); //Tab one title
	TabCtrl_InsertItem(ghw_tabcon,0,&ti);
	ti.pszText = _T("Appearance"); //Tab two title
	TabCtrl_InsertItem(ghw_tabcon,1,&ti);
	ti.pszText = _T("Team"); //Tab three title
	TabCtrl_InsertItem(ghw_tabcon,2,&ti);

	TabCtrl_SetCurSel(ghw_tabcon,0); //tab 1 visible by default
}
			
			//Subclass controls inside basic dialog
/*			chd_rect = new RECT;
			GetWindowRect(ghw_basic, chd_rect);
			MapWindowPoints(HWND_DESKTOP, GetParent(ghw_basic), (LPPOINT)chd_rect, 2);
			SetWindowSubclass(ghw_basic, scale_cntl_proc, 0, (DWORD_PTR)chd_rect); */
//			FILE * pFile;
//			pFile = fopen ("myfile.txt","w");
//			fprintf(pFile, "%d %d %d %d %d\r\n", IDD_BASIC, chd_rect->left, chd_rect->top, chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top);
/*			for(ii=IDD_BASIC+1; ii<=IDC_PLAY_STYL; ii++)
			{
				hw_new = GetDlgItem(ghw_basic, ii);
				chd_rect = new RECT;
				GetWindowRect(hw_new, chd_rect);
				MapWindowPoints(HWND_DESKTOP, GetParent(hw_new), (LPPOINT)chd_rect, 2);
				SetWindowSubclass(hw_new, scale_cntl_proc, 0, (DWORD_PTR)chd_rect);
//				fprintf(pFile, "%d %d %d %d %d\r\n", ii, chd_rect->left, chd_rect->top, chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top);
			}*/
			
void setup_tab1(HWND H)
{
	RECT *chd_rect;
	HWND hw_new, hw_bud;
	int x1, x2, y1, y2, ydiff, xc;

	ghw_tab1 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TAB_ONE), ghw_tabcon, NULL);
	//EnableThemeDialogTexture(ghw_tab1, ETDT_ENABLETAB);

	//Subclass controls inside tab1 dialog
	chd_rect = new RECT;
	GetWindowRect(ghw_tabcon, chd_rect);
	MapWindowPoints(HWND_DESKTOP, ghw_tabcon, (LPPOINT)chd_rect, 2);
	TabCtrl_AdjustRect(ghw_tabcon, false, chd_rect);
	SetWindowPos(ghw_tab1, HWND_TOP, chd_rect->left, chd_rect->top, 
		chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top, 
		SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOACTIVATE);
	SetWindowSubclass(ghw_tab1, scale_cntl_proc, 0, (DWORD_PTR)chd_rect);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Playable Positions"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 5, 130+11, 330, ghw_tab1, (HMENU)IDC_STATIC_T1, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("C"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		49+5, 24, 18, 17, ghw_tab1, (HMENU)IDC_STATIC_T2, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("B"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		85+8, 24, 18, 17, ghw_tab1, (HMENU)IDC_STATIC_T3, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("A"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		119+11, 24, 10, 17, ghw_tab1, (HMENU)IDC_STATIC_T4, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	y1=44, ydiff=22, xc=26+5;

	hw_new = CreateWindowEx(0, _T("Static"), _T("CF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T5, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("SS"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*1, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T6, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("LWF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*2, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T7, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("RWF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*3, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T8, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("AMF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*4, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T9, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("LMF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*5, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T10, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("RMF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*6, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T11, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("CMF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*7, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T12, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("DMF"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*8, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T13, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("LB"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*9, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T14, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("RB"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*10, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T15, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("CB"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*11, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T16, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("GK"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		21, y1+ydiff*12, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T17, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	x1=45+5, xc=88+6, y1=43;

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_CF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_SS, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*2, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_LWF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*3, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_RWF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*4, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_AMF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*5, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_LMF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*6, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_RMF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*7, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_CMF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*8, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_DMF, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*9, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_LB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*10, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_RB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*11, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_CB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(NULL, _T("msctls_trackbar32"), _T(""), 
		TBS_TOP | TBS_NOTICKS | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		x1, y1+ydiff*12, xc, 19, ghw_tab1, (HMENU)IDS_PLAY_GK, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	SendMessage(hw_new, TBM_SETRANGE,(WPARAM)TRUE,(LPARAM)MAKELONG(0,2));

	hw_new = CreateWindowEx(0, _T("Button"), _T("COM Playing Styles"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 345, 130+11, 164, ghw_tab1, (HMENU)IDC_STATIC_T18, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=21, y1=364, xc=112+11; ydiff=20;

	hw_new = CreateWindowEx(0, _T("Button"), _T("Trickster"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1, xc, 17, ghw_tab1, (HMENU)IDB_COM_TRIC, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Mazing Runner"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff, xc, 17, ghw_tab1, (HMENU)IDB_COM_MAZE, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Speeding Bullet"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab1, (HMENU)IDB_COM_SPBU, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Incisive Run"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab1, (HMENU)IDB_COM_INCI, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Long Ball Expert"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, xc, 17, ghw_tab1, (HMENU)IDB_COM_LNGB, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Early Cross"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, xc, 17, ghw_tab1, (HMENU)IDB_COM_CROS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Long Ranger"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, xc, 17, ghw_tab1, (HMENU)IDB_COM_LNGR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	ydiff = 24;
	hw_new = CreateWindowEx(0, _T("Static"), _T("Injury Resistance:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		10, 517+24, 114, 17, ghw_tab1, (HMENU)IDC_STATIC_T46, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		105+11, 515+24, 35, 20, ghw_tab1, (HMENU)IDT_ABIL_INJU, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_INJU, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Form:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		10, 517+24+ydiff, 100, 17, ghw_tab1, (HMENU)IDC_STATIC_T47, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		105+11, 515+24+ydiff, 35, 20, ghw_tab1, (HMENU)IDT_ABIL_FORM, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_FORM, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Player Skills"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		157+11, 5, 144*2+11, 580, ghw_tab1, (HMENU)IDC_STATIC_T19, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=168+11, y1=24, ydiff=20, xc=126+11;

	hw_new = CreateWindowEx(0, _T("Button"), _T("Scissors Feint*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_SCIS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Flip Flap*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_FLIP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Marseille Turn*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_MARS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Sombrero*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_SOMB, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Cut Behind && Turn*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_CUTB, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Scotch Move*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_SCOT, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Heading"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_HEAD, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Long Range Drive"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*7, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_LRDR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Knuckle Shot"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*8, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_KNUC, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Acrobatic Finishing"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*9, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_ACRF, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Heel Trick"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*10, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_HEEL, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("First-time Shot"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*11, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_FIRS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("One-touch Pass"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*12, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_ONET, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Weighted Pass"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*13, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_WEIG, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Pinpoint Crossing"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*14, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_PINP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Outside Curler"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*15, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_OUTS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Rabona*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*16, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_RABO, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Low Lofted Pass"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*17, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_LLPA, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Low Punt Trajectory"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*18, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_LPTR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Long Throw"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*19, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_LTHR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("GK Long Throw"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*20, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_GKLT, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Malicia"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*21, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_MALI, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Man Marking"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*22, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_MANM, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Track Back"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*23, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_TRAC, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Acrobatic Clear"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*24, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_ACRC, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Captaincy"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*25, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_CAPT, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Super-sub"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*26, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_SUPR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Fighting Spirit"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*27, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_FIGH, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	//New for 19
	hw_new = CreateWindowEx(0, _T("Button"), _T("Double Touch*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_DOUB, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Crossover Turn*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*1, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_CROS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Step on Skill*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*2, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_STEP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Chip Shot"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*3, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_CHIP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Dipping Shots"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*4, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_DIPP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Rising Shots"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*5, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_RISI, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("No Look Pass*"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*6, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_NOLO, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("High Punt Trajectory"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*7, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_HIGH, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Penalty Specialist"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*8, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_PENA, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("GK Penalty Specialist"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*9, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_GKPE, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Interception"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*10, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_INTE, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);
	//New for 20+
	hw_new = CreateWindowEx(0, _T("Button"), _T("Long Range Shooting"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*11, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_LRSH, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Through Passing"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1+144, y1+ydiff*12, xc, 17, ghw_tab1, (HMENU)IDB_SKIL_THPA, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Ability"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		318+22+144, 5, 185+11, 580, ghw_tab1, (HMENU)IDC_STATIC_T20, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=329+22+144, x2=448+33+144, xc=114+11, y1=24, y2=22, ydiff=22;//y1=24

	hw_new = CreateWindowEx(0, _T("Static"), _T("Attacking Prowess:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*0, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T21, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Ball Control:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T22, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Dribbling:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T23, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Low Pass:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T24, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Lofted Pass:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T25, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Finishing:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T26, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Place Kicking:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T27, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Swerve:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*7, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T28, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Header:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*8, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T29, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Defensive Prowess:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*9, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T30, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Ball Winning:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*10, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T31, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Kicking Power:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*11, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T32, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Speed:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*12, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T33, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Explosive Power:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*13, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T34, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Body Control:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*14, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T35, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Physical Contact:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*15, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T36, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Jump:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*16, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T37, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Stamina:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*17, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T38, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Goalkeeping:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*18, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T39, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Catching:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*19, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T40, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Clearing:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*20, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T41, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Reflexes:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*21, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T42, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Coverage:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*22, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T43, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Tight Possession:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*23, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T44, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Aggression:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*24, xc, 17, ghw_tab1, (HMENU)IDC_STATIC_T45, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Weak Foot\nUsage:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		323, y1+ydiff*23-12, 80, 17*2, ghw_tab1, (HMENU)IDC_STATIC_T90, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Weak Foot\nAccuracy:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		323, y1+ydiff*24-4, 80, 17*2, ghw_tab1, (HMENU)IDC_STATIC_T91, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		323+90, y1+ydiff*23-4, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_WKUS, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_WKUS, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		323+90, y1+ydiff*24+4, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_WKAC, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_WKAC, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*0, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_ATKP, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_ATKP, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*1, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_BCON, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_BCON, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*2, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_DRIB, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_DRIB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*3, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_LOWP, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_LOWP, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*4, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_LOFT, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_LOFT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*5, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_FINI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_FINI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*6, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_PKIC, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_PKIC, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*7, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_SWER, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_SWER, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*8, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_HEAD, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_HEAD, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*9, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_DEFP, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_DEFP, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*10, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_BWIN, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_BWIN, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*11, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_KPOW, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_KPOW, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*12, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_SPED, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_SPED, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*13, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_EXPL, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_EXPL, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*14, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_BODB, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_BODB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*15, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_PHCO, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_PHCO, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*16, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_JUMP, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_JUMP, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*17, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_STAM, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_STAM, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*18, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_GOAL, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_GOAL, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*19, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_CATC, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_CATC, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*20, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_CLEA, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_CLEA, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*21, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_REFL, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_REFL, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*22, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_COVE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_COVE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	//New for 20+

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*23, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_TIPO, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_TIPO, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*24, 44, 18, ghw_tab1, (HMENU)IDT_ABIL_AGGR, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab1, (HMENU)IDC_ABIL_AGGR, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	for(int ii=IDT_ABIL_ATKP;ii<IDC_ABIL_AGGR;ii++)
	{
		SendDlgItemMessage(ghw_tab1, ii+1, UDM_SETRANGE, 0, MAKELPARAM(99, 40));
		SendDlgItemMessage(ghw_tab1, ii, WM_SETTEXT, 0, (LPARAM)_T("40"));				
	}
	SendDlgItemMessage(ghw_tab1, IDC_ABIL_WKUS, UDM_SETRANGE, 0, MAKELPARAM(4, 1));
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKUS, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab1, IDC_ABIL_WKAC, UDM_SETRANGE, 0, MAKELPARAM(4, 1));
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKAC, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab1, IDC_ABIL_FORM, UDM_SETRANGE, 0, MAKELPARAM(8, 1));
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab1, IDC_ABIL_INJU, UDM_SETRANGE, 0, MAKELPARAM(3, 1));
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_SETTEXT, 0, (LPARAM)_T("1"));
}

void setup_tab2(HWND H)
{
	RECT *chd_rect;
	HWND hw_new, hw_bud;
	int x1, x2, y1, y2, ydiff, xc;

	x1=21, y1=24, ydiff=20, xc=140;

	ghw_tab2 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TAB_TWO), ghw_tabcon, 0);
	ShowWindow(ghw_tab2, SW_HIDE);
	//Subclass controls inside tab2 dialog
	chd_rect = new RECT;
	GetWindowRect(ghw_tabcon, chd_rect);
	MapWindowPoints(HWND_DESKTOP, ghw_tabcon, (LPPOINT)chd_rect, 2);
	TabCtrl_AdjustRect(ghw_tabcon, false, chd_rect);
	SetWindowPos(ghw_tab2, HWND_TOP, chd_rect->left, chd_rect->top, 
		chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top, 
		SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOACTIVATE);
	SetWindowSubclass(ghw_tab2, tab_two_dlg_proc, 0, (DWORD_PTR)chd_rect);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Visual Settings"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 5, 158, 103, ghw_tab2, (HMENU)IDC_STATIC_T48, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	

	hw_new = CreateWindowEx(0, _T("Button"), _T("Edited Face?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1, xc, 17, ghw_tab2, (HMENU)IDB_EDIT_FACE, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Edited Hairstyle?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, xc, 17, ghw_tab2, (HMENU)IDB_EDIT_HAIR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Edited Physique?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab2, (HMENU)IDB_EDIT_PHYS, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Edited Strip Style?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab2, (HMENU)IDB_EDIT_STRP, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Copy Settings"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 118, 158, 94, ghw_tab2, (HMENU)IDC_STATIC_T49, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=21, y1=137, ydiff=20, xc=140;

	hw_new = CreateWindowEx(0, _T("Button"), _T("Is a copy?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1, xc, 17, ghw_tab2, (HMENU)IDB_COPY_BASE, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Model ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff, 114, 17, ghw_tab2, (HMENU)IDC_STATIC_T50, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, 114, 23, ghw_tab2, (HMENU)IDT_COPY_ID, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Player Physique"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 222, 158, 347, ghw_tab2, (HMENU)IDC_STATIC_T51, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=21, y1=243, ydiff=22, xc=102, x2=112, y2=241;

	hw_new = CreateWindowEx(0, _T("Static"), _T("Head length:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*0, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T52, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Head width:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T53, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Head depth:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T54, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Neck length:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T55, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Neck size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T56, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Shoulder height:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T57, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Shoulder width:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T58, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Chest size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*7, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T59, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Waist size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*8, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T60, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Arm size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*9, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T61, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Arm length:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*10, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T62, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Thigh size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*11, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T63, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Calf size:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*12, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T64, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Leg length:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*13, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T65, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*0, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_HELE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_HELE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*1, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_HEWI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_HEWI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*2, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_HEDE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_HEDE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*3, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_NELE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_NELE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*4, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_NESI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_NESI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*5, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_SHHE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_SHHE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*6, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_SHWI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_SHWI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*7, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_CHSI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_CHSI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*8, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_WASI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_WASI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*9, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_ARSI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_ARSI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*10, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_ARLE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_ARLE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*11, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_THSI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_THSI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*12, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_CASI, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_CASI, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*13, 44, 18, ghw_tab2, (HMENU)IDT_PHYS_LELE, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PHYS_LELE, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Colors"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		178, 5, 184, 80, ghw_tab2, (HMENU)IDC_STATIC_T66, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=189, x2=256, y1=26, y2=22, ydiff=28;

	hw_new = CreateWindowEx(0, _T("Static"), _T("Skin color:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1, 65, 17, ghw_tab2, (HMENU)IDC_STATIC_T67, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Eye color:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff, 65, 17, ghw_tab2, (HMENU)IDC_STATIC_T68, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2, 95, 120, ghw_tab2, (HMENU)IDC_PHYS_SKIN, GetModuleHandle(NULL), NULL);
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("White/Def"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Light"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Fair"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Medium"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Olive"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Brown"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Black"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Custom"));
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff, 95, 120, ghw_tab2, (HMENU)IDC_PHYS_EYES, GetModuleHandle(NULL), NULL);
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Black"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Dark brown"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Brown"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Sable"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Navy blue"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Charcoal"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Gray"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Blue"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Sienna"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Green"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Violet"));
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Strip Style"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		178, 95, 358, 234, ghw_tab2, (HMENU)IDC_STATIC_T69, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=189, x2=266, y1=116, y2=112, ydiff=28;

	hw_new = CreateWindowEx(0, _T("Static"), _T("Boots ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T70, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("GK gloves ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T71, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Wrist taping:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T72, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Glasses style:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T73, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		415, y1+ydiff*3, 60, 17, ghw_tab2, (HMENU)IDC_STATIC_T74, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Sleeves:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T75, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Inners:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		390, y1+ydiff*4, 60, 17, ghw_tab2, (HMENU)IDC_STATIC_T76, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Sock length:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T77, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Undershorts:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		390, y1+ydiff*5, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T77, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Shirttail:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, 102, 17, ghw_tab2, (HMENU)IDC_STATIC_T78, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*0, 62, 23, ghw_tab2, (HMENU)IDT_STRP_BOID, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*1, 62, 23, ghw_tab2, (HMENU)IDT_STRP_GLID, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff*2, 105, 120, ghw_tab2, (HMENU)IDC_STRP_WRTA, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff*3, 140, 120, ghw_tab2, (HMENU)IDC_STRP_GLST, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		455, y2+ydiff*3, 70, 120, ghw_tab2, (HMENU)IDC_STRP_GLCO, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff*4, 105, 120, ghw_tab2, (HMENU)IDC_STRP_SLEE, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		437, y2+ydiff*4, 88, 120, ghw_tab2, (HMENU)IDC_STRP_SLIN, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff*5, 105, 120, ghw_tab2, (HMENU)IDC_STRP_SOCK, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		390, y2+ydiff*6, 135, 120, ghw_tab2, (HMENU)IDC_STRP_UNDR, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_VISIBLE | WS_TABSTOP, 
		x2, y2+ydiff*6, 105, 120, ghw_tab2, (HMENU)IDC_STRP_TAIL, GetModuleHandle(NULL), NULL);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Gloves?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		415, y1+ydiff*1, xc, 17, ghw_tab2, (HMENU)IDB_STRP_GLOV, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Ankle taping?"), 
		BS_AUTOCHECKBOX | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		415, y1+ydiff*2, xc, 17, ghw_tab2, (HMENU)IDB_STRP_ANTA, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Motion"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		178, 339, 358, 230, ghw_tab2, (HMENU)IDC_STATIC_T79, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1=189, x2=344, xc=160, y1=360, y2=358, ydiff=22;

	hw_new = CreateWindowEx(0, _T("Static"), _T("Hunching (dribbling):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*0, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T80, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Arm movement (dribbling):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*1, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T81, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Hunching (running):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*2, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T82, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Arm movement (running):"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*3, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T83, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Corner kick:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*4, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T84, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Free kick:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*5, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T85, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Penalty kick:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*6, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T86, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Goal celebration 1:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*7, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T87, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Goal celebration 2:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+ydiff*8, xc, 17, ghw_tab2, (HMENU)IDC_STATIC_T88, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*0, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_HUND, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_HUND, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*1, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_ARMD, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_ARMD, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*2, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_HUNR, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_HUNR, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*3, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_ARMR, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_ARMR, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*4, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_CK, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_CK, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*5, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_FK, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_FK, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*6, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_PK, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_PK, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*7, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_GC1, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_GC1, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*8, 50, 18, ghw_tab2, (HMENU)IDT_MOTI_GC2, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_GC2, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Randomize"), 
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		420, y2, 88, 26, ghw_tab2, (HMENU)IDB_MOTI_RAND, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);

	//PES 20+ Dribbling motion
	hw_new = CreateWindowEx(0, _T("Static"), _T("Dribbling:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		420, y1+10+ydiff*1, 60, 17, ghw_tab2, (HMENU)IDC_STATIC_T89, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		485, y2+10+ydiff*1, 40, 18, ghw_tab2, (HMENU)IDT_MOTI_DRIB, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_MOTI_DRIB, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);

	SendDlgItemMessage(ghw_tab2, IDC_MOTI_DRIB, UDM_SETRANGE, 0, MAKELPARAM(0, 3));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_DRIB, WM_SETTEXT, 0, (LPARAM)_T("0"));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Hand:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		420, y2+10+ydiff*2+4, 35, 17, ghw_tab2, (HMENU)IDT_PLAY_HAND, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(NULL, _T("ComboBox"), _T(""), 
		CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE, 
		465, y2+10+ydiff*2, 60, 100, ghw_tab2, (HMENU)IDC_PLAY_HAND, GetModuleHandle(NULL), NULL);
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Right"));
	SendMessage(hw_new, CB_ADDSTRING, 0, (LPARAM)_T("Left"));
	SendMessage(hw_new, CB_SETCURSEL, (WPARAM)0, 0);
	setup_combo(hw_new, ghFont, cb2_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Misc"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		372, 5, 164, 80, ghw_tab2, (HMENU)IDC_STATIC_T97, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Star rating:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		385, 26, 80, 17, ghw_tab2, (HMENU)IDS_STAR, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Playing Att:"), 
		SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		385, 26+28, 80, 17, ghw_tab2, (HMENU)IDS_PLAY_ATT, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		454, 24, 40, 18, ghw_tab2, (HMENU)IDT_STAR, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_STAR, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STAR, UDM_SETRANGE, 0, MAKELPARAM(7, 0));
	SendDlgItemMessage(ghw_tab2, IDT_STAR, WM_SETTEXT, 0, (LPARAM)_T("0"));

	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		454, 24+28, 40, 18, ghw_tab2, (HMENU)IDT_PLAY_ATT, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab2, (HMENU)IDC_PLAY_ATT, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(ghw_tab2, IDC_PLAY_ATT, UDM_SETRANGE, 0, MAKELPARAM(3, 0));
	SendDlgItemMessage(ghw_tab2, IDT_PLAY_ATT, WM_SETTEXT, 0, (LPARAM)_T("0"));

	/*chd_rect = new RECT;
	GetWindowRect(ghw_tab2, chd_rect);
	MapWindowPoints(HWND_DESKTOP, GetParent(ghw_tab2), (LPPOINT)chd_rect, 2);
	SetWindowSubclass(ghw_tab2, tab_two_dlg_proc, 0, (DWORD_PTR)chd_rect);
	for(ii=IDD_TAB_TWO+1; ii<=IDC_STATIC_T88; ii++)
	{
		hw_new = GetDlgItem(ghw_tab2, ii);
		chd_rect = new RECT;
		GetWindowRect(hw_new, chd_rect);
		MapWindowPoints(HWND_DESKTOP, GetParent(hw_new), (LPPOINT)chd_rect, 2);
		SetWindowSubclass(hw_new, scale_cntl_proc, 0, (DWORD_PTR)chd_rect);
//				fprintf(pFile, "%d %d %d %d %d\r\n", ii, chd_rect->left, chd_rect->top, chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top);
	}*/

//			fclose (pFile);

	for(int ii=IDT_PHYS_HELE;ii<IDC_PHYS_LELE;ii++)
	{
		SendDlgItemMessage(ghw_tab2, ii+1, UDM_SETRANGE, 0, MAKELPARAM(-7, 7));
		SendDlgItemMessage(ghw_tab2, ii, WM_SETTEXT, 0, (LPARAM)_T("0"));				
	}

	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_ADDSTRING, 0, (LPARAM)_T("None"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_ADDSTRING, 0, (LPARAM)_T("Right"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_ADDSTRING, 0, (LPARAM)_T("Left"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_ADDSTRING, 0, (LPARAM)_T("Both"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("None"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Rectangle (rimless)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Rectangle (half frame)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Rectangle (full frame)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Oval (rimless)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Oval (half frame)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Oval (full frame)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_ADDSTRING, 0, (LPARAM)_T("Round (full frame)"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("White"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Black"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Red"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Blue"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Yellow"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Green"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Pink"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_ADDSTRING, 0, (LPARAM)_T("Turquoise"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_ADDSTRING, 0, (LPARAM)_T("Seasonal"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_ADDSTRING, 0, (LPARAM)_T("Short"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_ADDSTRING, 0, (LPARAM)_T("Long"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_ADDSTRING, 0, (LPARAM)_T("None"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_ADDSTRING, 0, (LPARAM)_T("Normal"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_ADDSTRING, 0, (LPARAM)_T("Turtleneck"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_ADDSTRING, 0, (LPARAM)_T("Standard"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_ADDSTRING, 0, (LPARAM)_T("Long"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_ADDSTRING, 0, (LPARAM)_T("Short"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_ADDSTRING, 0, (LPARAM)_T("Tucked"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_ADDSTRING, 0, (LPARAM)_T("Untucked"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)0, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_ADDSTRING, 0, (LPARAM)_T("S: Off / W: Off"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_ADDSTRING, 0, (LPARAM)_T("S: Short / W: Short"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_ADDSTRING, 0, (LPARAM)_T("S: Off / W: Long"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_ADDSTRING, 0, (LPARAM)_T("S: Short / W: Long"));
	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_SETCURSEL, (WPARAM)0, 0);
	
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_HUND, UDM_SETRANGE, 0, MAKELPARAM(1, 3));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUND, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_ARMD, UDM_SETRANGE, 0, MAKELPARAM(1, 8));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMD, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_HUNR, UDM_SETRANGE, 0, MAKELPARAM(1, 3));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUNR, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_ARMR, UDM_SETRANGE, 0, MAKELPARAM(1, 8));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMR, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_CK, UDM_SETRANGE, 0, MAKELPARAM(1, 6));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_CK, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_FK, UDM_SETRANGE, 0, MAKELPARAM(1, 16));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_FK, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_PK, UDM_SETRANGE, 0, MAKELPARAM(1, 4));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_PK, WM_SETTEXT, 0, (LPARAM)_T("1"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_GC1, UDM_SETRANGE, 0, MAKELPARAM(0, 122));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC1, WM_SETTEXT, 0, (LPARAM)_T("0"));
	SendDlgItemMessage(ghw_tab2, IDC_MOTI_GC2, UDM_SETRANGE, 0, MAKELPARAM(0, 122));
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC2, WM_SETTEXT, 0, (LPARAM)_T("0"));
}

void setup_tab3(HWND H)
{
	RECT *chd_rect;
	HWND hw_new, hw_bud;
	int x1, x2, y1, y2, ydiff;

	//##############################
	// Team tab
	ghw_tab3 = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TAB_THREE), ghw_tabcon, 0);
	ShowWindow(ghw_tab3, SW_HIDE);
	//Subclass controls inside tab2 dialog
	chd_rect = new RECT;
	GetWindowRect(ghw_tabcon, chd_rect);
	MapWindowPoints(HWND_DESKTOP, ghw_tabcon, (LPPOINT)chd_rect, 2);
	TabCtrl_AdjustRect(ghw_tabcon, false, chd_rect);
	SetWindowPos(ghw_tab3, HWND_TOP, chd_rect->left, chd_rect->top, 
		chd_rect->right-chd_rect->left, chd_rect->bottom-chd_rect->top, 
		SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOACTIVATE);
	SetWindowSubclass(ghw_tab3, tab_three_dlg_proc, 0, (DWORD_PTR)chd_rect);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Team Colors"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 5, 207, 168, ghw_tab3, (HMENU)IDC_STATIC_T1, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1 = 20;
	x2 = 100;
	y1 = 25;
	y2 = 95;
	ydiff=22;

	//Red 1
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y1+ydiff*0, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_R1, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_R1, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 1 Red:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+2+ydiff*0, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T89, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Green 1
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y1+ydiff*1, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_G1, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_G1, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 1 Green:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+2+ydiff*1, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T90, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Blue 1
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y1+ydiff*2, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_B1, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_B1, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 1 Blue:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y1+2+ydiff*2, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T91, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Color 1 button
	hw_new = CreateWindowEx(0, _T("Button"), NULL, 
		BS_PUSHBUTTON | BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		155, y1+6, 50, 50, ghw_tab3, (HMENU)IDB_TCOLOR1, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	//Red 2
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*0, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_R2, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_R2, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 2 Red:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y2+2+ydiff*0, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T92, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Green 2
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*1, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_G2, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_G2, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 2 Green:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y2+2+ydiff*1, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T93, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Blue 2
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff*2, 44, 18, ghw_tab3, (HMENU)IDT_TCOL_B2, GetModuleHandle(NULL), NULL);
	hw_bud = CreateWindowEx(WS_EX_CLIENTEDGE, _T("msctls_updown32"), _T(""), 
		UDS_AUTOBUDDY|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS | WS_CHILD | WS_VISIBLE, 
		0, 0, 0, 0, ghw_tab3, (HMENU)IDC_TCOL_B2, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	setup_control(hw_bud, ghFont, scale_cntl_proc);
	SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);
	SendMessage(hw_bud, UDM_SETRANGE, 0, MAKELPARAM(63, 0));

	hw_new = CreateWindowEx(0, _T("Static"), _T("Color 2 Blue:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y2+2+ydiff*2, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T94, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Color 2 button
	hw_new = CreateWindowEx(0, _T("Button"), NULL, 
		BS_PUSHBUTTON | BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
		155, y2+6, 50, 50, ghw_tab3, (HMENU)IDB_TCOLOR2, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	hw_new = CreateWindowEx(0, _T("Button"), _T("Team Data"), 
		BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 
		10, 178, 207, 70, ghw_tab3, (HMENU)IDC_STATIC_T1, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_cntl_proc);

	x1 = 20;
	x2 = 100;
	y2 = 198;

	//Manager ID
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2, 44, 18, ghw_tab3, (HMENU)IDT_MANAGER, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	//SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Manager ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y2+2, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T95, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);

	//Stadium ID
	hw_new = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
		ES_NUMBER | ES_AUTOHSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 
		x2, y2+ydiff, 44, 18, ghw_tab3, (HMENU)IDT_STADIUM, GetModuleHandle(NULL), NULL);
	setup_control(hw_new, ghFont, scale_cntl_proc);
	//SendMessage(hw_new, EM_SETLIMITTEXT, 2, 0);

	hw_new = CreateWindowEx(0, _T("Static"), _T("Stadium ID:"), 
		SS_SIMPLE | SS_NOPREFIX | WS_CHILD | WS_VISIBLE, 
		x1, y2+2+ydiff, 80, 17, ghw_tab3, (HMENU)IDC_STATIC_T96, GetModuleHandle(NULL), NULL);	
	setup_control(hw_new, ghFont, scale_static_proc);
}