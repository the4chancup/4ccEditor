/*Header files and preprocessor directives*/

#include "resource.h"
#include "editor.h"
#include "window.h"

//----------------------------------------------------------------------
/*Function prototypes*/
/*
//Dialog procedures: (Now in window.h)
LRESULT CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK aatf_sing_dlg_proc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK aatf_mult_dlg_proc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK aatf_sel_dlg_proc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK aatf_comp_dlg_proc(HWND, UINT, WPARAM, LPARAM);
//BOOL CALLBACK tab_two_dlg_proc(HWND, UINT, WPARAM, LPARAM);

//Control procedures: (Now in window.h)
LRESULT CALLBACK lv_cntl_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK cb_cntl_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK cb2_cntl_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK scale_cntl_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK scale_static_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK onto_tab_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK from_tab_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK tab_two_dlg_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
LRESULT CALLBACK tab_three_dlg_proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR);
BOOL CALLBACK statDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK bumpDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK scale_children(HWND,LPARAM);
BOOL CALLBACK draw_children(HWND,LPARAM);
*/
int loadDLL();
void DoFileOpen(HWND, TCHAR* = NULL);
void DoFileSave(HWND);
void data_handler(const TCHAR *);
void save_handler(const TCHAR *);

void export_squad(HWND);
void import_squad(HWND);

void extract_player_entry(player_entry, int &);

void extract_team_info(team_entry, int &);
void extract_teamplayer_info(team_entry, int &);

void show_player_info(int);
player_entry get_form_player_info(int);
bool get_form_team_info(int, team_entry &);
void fill_list_all_players();
void make_pony_phys();
void trim_team();
void team_vis_clear();
void team_created_set();
void team_fpc_on();
void team_fpc_off();
void fpc_toggle();
void toggle_hid();
void set_stats();
void bump_stats();
//void setup_control(HWND,HFONT,SUBCLASSPROC); (Now in window.h)
//void setup_combo(HWND,HFONT,SUBCLASSPROC);
void common_shortcuts(WPARAM);
void roster_data_output();
void fix_database();
void scroll_player_up();
void scroll_player_down();
void update_tables();

void SD_OnHVScroll(HWND hwnd, int bar, UINT code);
void SD_ScrollClient(HWND hwnd, int bar, int pos);
int SD_GetScrollPos(HWND hwnd, int bar, UINT code);

//----------------------------------------------------------------------
/*Global variables*/
char gc_ver4ccs[] = "20a";
HINSTANCE ghinst;			//Main window instance
HINSTANCE hPesDecryptDLL;	//Handle to libpesXcrypter.dll 
HWND ghw_main;				//Handle to main window
HWND ghw_tabcon, ghw_tab1, ghw_tab2, ghw_tab3;
HFONT ghFont;
HWND ghw_stat=NULL, ghw_bump=NULL, ghw_import=NULL;
HWND ghw_DlgCurrent = NULL;
HWND ghAatfbox=NULL;
void* ghdescriptor = NULL; //void, cast as FileDescriptorOld or FileDescriptorNew depending on version
player_entry* gplayers = NULL;
int* gn_playind = NULL; //positions in gplayers array of each item in player listbox
team_entry* gteams = NULL;
int* gn_teamCbIndToArray = NULL; //positions in gteams array of each item in team combobox
int* gn_teamArrayIndToCb = NULL; //vice versa
int gnum_players, gnum_teams, gn_listsel, gn_teamsel=-1, gn_forceupdate;
bool gb_forceupdate = false;
bool gb_firstsave = true;
bool gb_importStats = true, gb_importAes = true; //Squad import options
int gn_oldysize = 642;
int g_prevx=0;
int giPesVersion = 0;
int g_bumpAmount = 0;
const uint8_t* gpMasterKey;

int gi_lastAbility = IDC_ABIL_AGGR; //Final control ID in list of Player Ability, for looping over them

//Brushes
HBRUSH gTeamColor1 = NULL;
HBRUSH gTeamColor2 = NULL;

pf_createFileDescriptorOld createFileDescriptorOld;
pf_createFileDescriptorNew createFileDescriptorNew;
pf_destroyFileDescriptorOld destroyFileDescriptorOld;
pf_destroyFileDescriptorNew destroyFileDescriptorNew;
pf_decryptWithKeyOld decryptWithKeyOld;
pf_decryptWithKeyNew decryptWithKeyNew;
pf_encryptWithKeyOld encryptWithKeyOld;
pf_encryptWithKeyNew encryptWithKeyNew;


//The TCHAR-version of a user-provided entry point for a graphical 
//  Windows-based application.
// I 	[in] A handle to the current instance of the application
// PI	[in] A handle to the previous instance of the application. This 
//				parameter is always NULL
// CL	[in] The command line for the program, excluding the program name
// SC	[in] Controls how the window is to be shown
int APIENTRY _tWinMain(HINSTANCE I, HINSTANCE PI, LPTSTR CL, int SC)
{
	ghinst = I; //Global handle to the program instance
	
	WNDCLASSEX wc;
	MSG msg;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = wnd_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = I;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_MENU+1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = _T("4cc_app");
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, _T("Window Registration Failed!"), _T("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//Load libpesXcrypter.dll and its functions
	int retval = loadDLL();
	if(retval) return retval;

	ghw_main = CreateWindowEx(
		0,
		wc.lpszClassName,
		_T("4ccEditor 10th Anniversary Edition (Version B)"),
		WS_OVERLAPPEDWINDOW,
		20, 20, 1120+144, 700,
		NULL, NULL, ghinst, NULL);

	if(ghw_main == NULL)
	{
		MessageBox(NULL, _T("Window Creation Failed!"), _T("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	srand(time(NULL));

	ShowWindow(ghw_main, SC);
	UpdateWindow(ghw_main);

	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if( !IsDialogMessage(ghw_main, &msg) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

//Message loop for the main window
LRESULT CALLBACK wnd_proc(HWND H, UINT M, WPARAM W, LPARAM L)
{
	switch(M)
	{
		case WM_CREATE:
		{
			int ii;

			//Initialize common controls so we can use tabbed page, 
			// tooltip, and progress bar controls
			INITCOMMONCONTROLSEX ix;
			ix.dwSize = sizeof(INITCOMMONCONTROLSEX);
			ix.dwICC = ICC_TAB_CLASSES | ICC_PROGRESS_CLASS;			
			InitCommonControlsEx(&ix); 

			//AATF Dialog box
			ghAatfbox = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AATF), H, aatf_sing_dlg_proc);

			HICON hi_big = (HICON)LoadImage(ghinst, MAKEINTRESOURCE(IDI_4CC_MED), IMAGE_ICON, 48, 48, NULL);
			HICON hi_sml = (HICON)LoadImage(ghinst, MAKEINTRESOURCE(IDI_4CC), IMAGE_ICON, 16, 16, NULL);
			SendMessage(H, WM_SETICON, ICON_BIG, (LPARAM)hi_big);
			SendMessage(H, WM_SETICON, ICON_SMALL, (LPARAM)hi_sml);

			HFONT hfDefault;
			HWND hw_new;
			HWND hw_bud;

			RECT *chd_rect;

			hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

			ghFont = CreateFont(15,0,0,0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));

			hw_new = CreateWindowEx(0,_T("SCROLLBAR"),(PTSTR) NULL, WS_CHILD | SBS_HORZ, 
				0, 642-18, 1102, 18, H, (HMENU)IDC_HSCROLL, GetModuleHandle(NULL), (PVOID) NULL);

			RECT rc = {};
			GetClientRect(H, &rc);
			const SIZE sz = { rc.right - rc.left, rc.bottom - rc.top };
			SCROLLINFO si = {};
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
			si.nPos = si.nMin = 1;

			si.nMax = sz.cx;
			si.nPage = sz.cx;
			SetScrollInfo(hw_new, SB_HORZ, &si, FALSE);

			//In window.cpp:
			setup_main(H);
			setup_tab1(H);
			setup_tab2(H);
			setup_tab3(H);

			int x1, x2, y1;
			x1 = GetSystemMetrics(SM_CXSCREEN);
			y1 = GetSystemMetrics(SM_CYSCREEN); //1120, 700

			if(y1<700)
			{
				x2 = y1/700*1120;
				if(x2>x1) x2=x1;
				SetWindowPos(H,0,0,0,x2,y1,SWP_NOZORDER);
			}

			SetFocus(GetDlgItem(H, IDC_TEAM_LIST));
		}
		break;
		case WM_SIZE:
		{
			RECT rcClient;
			resize_info ri;

			GetClientRect(H, &rcClient);
			//GetWindowRect(H, &rcClient);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&rcClient, 2);

			//hEdit = GetDlgItem(H, IDC_MAIN_EDIT);
			//SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
			//float scale = (float)(rcClient.bottom-rcClient.top)/700.0;
			ri.scale = (float)(rcClient.bottom-rcClient.top)/642.0;
			int font_height = ceil(ri.scale*15.0);
			DeleteObject((HGDIOBJ)ghFont);
			ghFont = CreateFont(font_height,0,0,0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI"));

			HWND hscroll = GetDlgItem(H, IDC_HSCROLL);
			SetWindowPos(hscroll, 0, rcClient.left, rcClient.bottom - 18, rcClient.right, 18, 
					SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			const SIZE sz = { rcClient.right - rcClient.left, rcClient.bottom - rcClient.top };

			if( !(W != SIZE_RESTORED && W != SIZE_MAXIMIZED) )
			{
				//----------------
				
				SCROLLINFO si = {};
				si.cbSize = sizeof(SCROLLINFO);

				si.fMask = SIF_PAGE | SIF_RANGE;
				si.nPage = sz.cx;
				si.nMax = 1104*ri.scale;
				SetScrollInfo(hscroll, SB_CTL, &si, TRUE);

				si.fMask = SIF_RANGE | SIF_POS;
				GetScrollInfo(hscroll, SB_CTL, &si);

				const int maxScrollPos = si.nMax - (sz.cx - 1);

				// Scroll client only if scroll bar is visible and window's
				// content is fully scrolled toward right and/or bottom side.
				// Also, update window's content on maximize.
				const bool needToScroll =
					(si.nPos != si.nMin && si.nPos == maxScrollPos) ||
					(W == SIZE_MAXIMIZED);

				if(needToScroll)
				{
					SD_ScrollClient(hscroll, SB_CTL, si.nPos);
				}
				//---------------------

				if( (float)sz.cx/(float)sz.cy< 1.718 ) ShowWindow(hscroll, SW_SHOW);
				else ShowWindow(hscroll, SW_HIDE);

				//ri.hdefer = BeginDeferWindowPos(500);
				EnumChildWindows(H, scale_children, (LPARAM)&ri); 
				//EndDeferWindowPos(ri.hdefer);
				EnumChildWindows(H, draw_children, (LPARAM)0); 

				InvalidateRect(H,NULL,true);
			}
		}
		break;
		case WM_HSCROLL:
		{
			SD_OnHVScroll(GetDlgItem(H, IDC_HSCROLL), SB_CTL, LOWORD(W));
		}
		break;
		case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)L; // item drawing information
			HWND hTabCtrl = GetDlgItem(H, IDC_TAB_MAIN);
			TCITEM tci;
			TCHAR szTabText[30];
			HBRUSH hbr;
			COLORREF bkColor;

			if (hTabCtrl == lpdis->hwndItem)   // is this the tab control?
			{
				bkColor = (COLORREF)GetSysColor(COLOR_3DFACE);
				hbr = (HBRUSH)CreateSolidBrush(bkColor);
			
				memset(szTabText, '\0', sizeof(szTabText));
				tci.mask = TCIF_TEXT;
				tci.pszText = szTabText;
				tci.cchTextMax = 29;

				TabCtrl_GetItem(hTabCtrl, lpdis->itemID, &tci);

				FillRect(lpdis->hDC, &lpdis->rcItem, hbr);
				SetBkColor(lpdis->hDC, bkColor);

				//RECT rctext = lpdis->rcItem;
				//rctext.top -= GetSystemMetrics(SM_CYEDGE);
				//rctext.left += GetSystemMetrics(SM_CXEDGE);

				//int test = TabCtrl_GetCurSel(hTabCtrl);

				//TextOut(lpdis->hDC,rctext.left,rctext.top,tci.pszText,lstrlen(tci.pszText));
				if( lpdis->itemID == TabCtrl_GetCurSel(hTabCtrl) )
					DrawText(lpdis->hDC, tci.pszText, lstrlen(tci.pszText), &lpdis->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
				else
					DrawText(lpdis->hDC, tci.pszText, lstrlen(tci.pszText), &lpdis->rcItem, DT_SINGLELINE|DT_BOTTOM|DT_CENTER);

				DeleteObject(hbr);
			}
		}
		break;
		case WM_KEYDOWN:
		{
			//When P key is pressed
			if( W == 0x50 && (GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000) )
			{
				make_pony_phys();
			}
		}
		break;
		case WM_NOTIFY:
		{
			switch( ((LPNMHDR)L)->code )
			{
				//Message sent because user changed the tab selection 
				// (clicked on another tab)
				case TCN_SELCHANGING: 
				{
					//Hide the old tab from view
					if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 0 )
					{
						ShowWindow(ghw_tab1, SW_HIDE);
					}
					else if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 1 )
					{
						ShowWindow(ghw_tab2, SW_HIDE);
					}
					else if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 2 )
					{
						ShowWindow(ghw_tab3, SW_HIDE);
					}
				}
				break;

				//Message sent when new tab gains focus
				case TCN_SELCHANGE:
				{
					//Make the new tab visible
					if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 0 )
					{
						ShowWindow(ghw_tab1, SW_SHOW);
					} 
					else if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 1 )
					{
						ShowWindow(ghw_tab2, SW_SHOW);
					}
					else if( TabCtrl_GetCurSel(GetDlgItem(ghw_main, IDC_TAB_MAIN)) == 2 )
					{
						ShowWindow(ghw_tab3, SW_SHOW);
					}
				}
				break;

				case LVN_ITEMCHANGED:
				{
					if(gb_forceupdate)
					{
						player_entry pe_current = get_form_player_info(gn_forceupdate);
						if( !(gplayers[gn_forceupdate] == pe_current) )
						{
							if( wcscmp(gplayers[gn_forceupdate].name, pe_current.name) )
								pe_current.b_edit_player = true;
							gplayers[gn_forceupdate] = pe_current;

							//Check if name is still in ListView
							int list_size,ii;
							bool b_upd = false;
							list_size = SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_GETITEMCOUNT, 0, 0);
							for(ii=0;ii<list_size;ii++)
							{
								if(gplayers[gn_playind[ii]].id==pe_current.id)
								{
									b_upd = true;
									break;
								}
							}
							if(b_upd)
							{
								//Update displayed name
								LVITEM lvI;
								memset(&lvI,0,sizeof(lvI)); //Zero out struct members
								lvI.mask = LVIF_TEXT;
								lvI.pszText = pe_current.name;
								lvI.iItem = ii;
								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);
							}
						}

						//Check and update team tables
						team_entry te_current;
						if( get_form_team_info(gn_forceupdate, te_current) )
						{
							int ti = gplayers[gn_forceupdate].team_ind;
							if( !(gteams[ti] == te_current) )
							{
								gteams[ti] = te_current;

								//Update combobox
								int csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_DELETESTRING, gn_teamArrayIndToCb[ti]+1, 0);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_INSERTSTRING, gn_teamArrayIndToCb[ti]+1, (LPARAM)te_current.name);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, csel, 0);								
							}
						}

						gn_listsel = ((LPNMLISTVIEW)L)->iItem;
						show_player_info(gn_playind[gn_listsel]);

						gb_forceupdate = false;
					}
					else if(((LPNMLISTVIEW)L)->iItem != gn_listsel)
					{
						player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
						if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
						{
							if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
								pe_current.b_edit_player = true;
							gplayers[gn_playind[gn_listsel]] = pe_current;
							
							//Update displayed name
							LVITEM lvI;
							memset(&lvI,0,sizeof(lvI)); //Zero out struct members
							lvI.mask = LVIF_TEXT;
							lvI.pszText = pe_current.name;
							lvI.iItem = gn_listsel;
							SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);
						}

						//Check and update team tables
						team_entry te_current;
						if( get_form_team_info(gn_playind[gn_listsel], te_current) )
						{
							int ti = gplayers[gn_playind[gn_listsel]].team_ind;
							if( !(gteams[ti] == te_current) )
							{
								gteams[ti] = te_current;

								//Update combobox
								int csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_DELETESTRING, gn_teamArrayIndToCb[ti]+1, 0);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_INSERTSTRING, gn_teamArrayIndToCb[ti]+1, (LPARAM)te_current.name);
								SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, csel, 0);								
							}
						}

						gn_listsel = ((LPNMLISTVIEW)L)->iItem;
						show_player_info(gn_playind[gn_listsel]);
					}
				}
				break;

				case UDN_DELTAPOS:
				{
					LPNMUPDOWN lpnmud = (LPNMUPDOWN)L;
					if(LOWORD(W)==IDB_MOVE_PLYR)
					{
						if(lpnmud->iDelta<0 && gn_listsel != 0) //Ensure can't move up if at top of list
						{
							//Get team of player in prev position on list, check if equal to current player team
							if(gplayers[gn_playind[gn_listsel-1]].team_ind == gplayers[gn_playind[gn_listsel]].team_ind)
							{
								//Update current player entry
								player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
								if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
								{
									if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
										pe_current.b_edit_player = true;
									gplayers[gn_playind[gn_listsel]] = pe_current;
								}
								//export settings for current player into temp struct 1
								player_export currPlyrExport = gplayers[gn_playind[gn_listsel]].PlayerExport();
								//export settings for prev player into temp struct 2
								player_export prevPlyrExport = gplayers[gn_playind[gn_listsel-1]].PlayerExport();

								//Have player copy ids match new slot
								unsigned long tmp_id = currPlyrExport.copy_id;
								currPlyrExport.copy_id = prevPlyrExport.copy_id;
								prevPlyrExport.copy_id = tmp_id;

								//swap temp struct 2 into (old) current player, set b_changed flag
								gplayers[gn_playind[gn_listsel]].PlayerImport(prevPlyrExport);
								gplayers[gn_playind[gn_listsel]].b_changed = true;
								//import temp struct 1 into (old) prev player, set b_changed flag
								gplayers[gn_playind[gn_listsel-1]].PlayerImport(currPlyrExport);
								gplayers[gn_playind[gn_listsel-1]].b_changed = true;

								show_player_info(gn_playind[gn_listsel]);

								//Update displayed names
								LVITEM lvI;
								memset(&lvI,0,sizeof(lvI)); //Zero out struct members
								lvI.mask = LVIF_TEXT;
								lvI.pszText = gplayers[gn_playind[gn_listsel]].name;
								lvI.iItem = gn_listsel;
								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);

								lvI.pszText = gplayers[gn_playind[gn_listsel-1]].name;
								lvI.iItem = gn_listsel-1;
								//Note this will set the current selection to gn_listsel-1, the prev player
								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);
								//As gn_listsel has changed, make the selection visible and highlighted
								ListView_EnsureVisible(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel, false);
								ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel, LVIS_SELECTED, LVIS_SELECTED);
							}
						}
						else if(lpnmud->iDelta>0 && gn_listsel != ListView_GetItemCount(GetDlgItem(ghw_main, IDC_NAME_LIST))-1) //Ensure can't move down if at bottom of list
						{
							//Get team of player in next position on list, check if equal to current player team
							if(gplayers[gn_playind[gn_listsel+1]].team_ind == gplayers[gn_playind[gn_listsel]].team_ind)
							{
								//Update current player entry
								player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
								if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
								{
									if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
										pe_current.b_edit_player = true;
									gplayers[gn_playind[gn_listsel]] = pe_current;
								}
								//export settings for current player into temp struct 1
								player_export currPlyrExport = gplayers[gn_playind[gn_listsel]].PlayerExport();
								//export settings for next player into temp struct 2
								player_export nextPlyrExport = gplayers[gn_playind[gn_listsel+1]].PlayerExport();

								//Have player copy ids match new slot
								unsigned long tmp_id = currPlyrExport.copy_id;
								currPlyrExport.copy_id = nextPlyrExport.copy_id;
								nextPlyrExport.copy_id = tmp_id;

								//swap temp struct 2 into (old) current player, set b_changed flag
								gplayers[gn_playind[gn_listsel]].PlayerImport(nextPlyrExport);
								gplayers[gn_playind[gn_listsel]].b_changed = true;
								//import temp struct 1 into (old) next player, set b_changed flag
								gplayers[gn_playind[gn_listsel+1]].PlayerImport(currPlyrExport);
								gplayers[gn_playind[gn_listsel+1]].b_changed = true;

								show_player_info(gn_playind[gn_listsel]);

								//Update displayed names
								LVITEM lvI;
								memset(&lvI,0,sizeof(lvI)); //Zero out struct members
								lvI.mask = LVIF_TEXT;
								lvI.pszText = gplayers[gn_playind[gn_listsel]].name;
								lvI.iItem = gn_listsel;
								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);

								lvI.pszText = gplayers[gn_playind[gn_listsel+1]].name;
								lvI.iItem = gn_listsel+1;
								//Note this will set the current selection to gn_listsel+1, the next player
								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);
								//As gn_listsel has changed, make the selection visible and highlighted
								ListView_EnsureVisible(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel, false);
								ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel, LVIS_SELECTED, LVIS_SELECTED);
							}
						}
					}
				}
				break;
			}
		}
		break;
		case WM_CLOSE:
			if(ghdescriptor) 
			{
				if(giPesVersion>=18)
					destroyFileDescriptorNew((FileDescriptorNew*)ghdescriptor);
				else
					destroyFileDescriptorOld((FileDescriptorOld*)ghdescriptor);
				ghdescriptor = NULL;
			}
			if(gplayers) 
			{
				delete[] gplayers;
				gplayers = NULL;
			}
			if(gn_playind) 
			{
				delete[] gn_playind;
				gn_playind = NULL;
			}
			if(gteams) 
			{
				delete[] gteams;
				gteams = NULL;
			}

			//Delete icons, fonts and bitmaps
			DeleteObject((HGDIOBJ)ghFont);
			FreeLibrary(hPesDecryptDLL);

			DestroyWindow(H);
		break;
		case WM_DESTROY:
			DestroyWindow(ghAatfbox);
			PostQuitMessage(0);
		break;
		case WM_COMMAND:
			switch(LOWORD(W))
			{
				case ID_FILE_EXIT:
					PostMessage(H, WM_CLOSE, 0, 0);
				break;
				case ID_FILE_OPEN_16_EN:
					giPesVersion = 16;
					DoFileOpen(H, _T("Open PES16 EDIT file"));
				break;
				case ID_FILE_OPEN_17_EN:
					giPesVersion = 17;
					DoFileOpen(H, _T("Open PES17 EDIT file"));
				break;
				case ID_FILE_OPEN_18_EN:
					giPesVersion = 18;
					DoFileOpen(H, _T("Open PES18 EDIT file"));
				break;
				case ID_FILE_OPEN_19_EN:
					giPesVersion = 19;
					DoFileOpen(H, _T("Open PES19 EDIT file"));
				break;
				case ID_FILE_OPEN_20_EN:
					giPesVersion = 20;
					DoFileOpen(H, _T("Open PES20 EDIT file"));
				break;
				case ID_FILE_OPEN_EN:
				case ID_FILE_OPEN_21_EN:
					giPesVersion = 21;
					DoFileOpen(H, _T("Open PES21 EDIT file"));
				break;
				case ID_FILE_SAVE_EN:
					if(ghdescriptor)
					{
						DoFileSave(H);
					}
				break;
				case IDM_PLAY_STAT:
					set_stats();
				break;
				case IDM_PLAY_BUMP:
					bump_stats();
				break;
				case IDM_PLAY_FTOG:
					fpc_toggle();
				break;
				case IDM_TEAM_CLEAR:
					if(gplayers) team_vis_clear();
				break;
				case IDM_TEAM_CREAT:
					if(gplayers) team_created_set();
				break;
				case IDM_TEAM_FPCON:
					if(gplayers) team_fpc_on();
				break;
				case IDM_TEAM_FPOFF:
					if(gplayers) team_fpc_off();
				break;
				case IDM_TEAM_SAVES:
					if(gn_teamsel > -1) export_squad(H);
					else MessageBox(H,_T("Please select a team to be saved."),NULL,MB_ICONWARNING);
				break;
				case IDM_TEAM_LOADS:
					if(gn_teamsel > -1) import_squad(H);
					else MessageBox(H,_T("Please select a team to overwrite."),NULL,MB_ICONWARNING);
				break;
				case IDM_DATA_OUTPUT:
					if(gplayers) roster_data_output();
				break;
				case IDM_DATA_FIX:
					if(gplayers) fix_database();
				break;
				case IDC_TEAM_LIST:
				{
					if(HIWORD(W)==CBN_SELCHANGE)
					{
						//fill player, text lists in window
						int ii, jj, num_on_team, csel;
						csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0) - 1;
						if(gn_teamCbIndToArray[csel]!=gn_teamsel)
						{
							if(csel>-1)
							{
								gb_forceupdate = true;
								gn_forceupdate = gn_playind[gn_listsel];

								for(num_on_team=0;num_on_team < gteams->team_max; num_on_team++)
								{
									if(!gteams[gn_teamCbIndToArray[csel]].players[num_on_team]) break;
								}

								delete[] gn_playind;
								gn_playind = new int[num_on_team];

								SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_DELETEALLITEMS, 0, 0);
								LVITEM lvI;
								memset(&lvI,0,sizeof(lvI)); //Zero out struct members
								lvI.mask = LVIF_TEXT;
								int kk=0;
								for(ii=0;ii<gnum_players;ii++)
								{
									for(jj=0;jj<num_on_team;jj++)
									{
										if(gplayers[ii].id == gteams[gn_teamCbIndToArray[csel]].players[jj])
										{
											gn_playind[kk] = ii;
											lvI.pszText = gplayers[ii].name;
											lvI.iItem = kk;
											SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_INSERTITEM, 0, (LPARAM)&lvI);
											kk++;
											break;
										}
									}
									if(kk==num_on_team) break;
								}
								ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), 0, LVIS_SELECTED, LVIS_SELECTED);
								gn_listsel = 0;
								gn_teamsel = gn_teamCbIndToArray[csel];
							}
							else
							{
								gb_forceupdate = true;
								gn_forceupdate = gn_playind[gn_listsel];
								fill_list_all_players();
								gn_teamsel = -1;
							}
						}
					}
				}
				break;
				case IDB_CAPTAIN:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						if(ghdescriptor)
						{
							SendDlgItemMessage(H, IDB_CAPTAIN, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
							if(gteams[gplayers[gn_playind[gn_listsel]].team_ind].captain_ind != 
								gplayers[gn_playind[gn_listsel]].team_lineup_ind)
							{
								gteams[gplayers[gn_playind[gn_listsel]].team_ind].captain_ind = 
									gplayers[gn_playind[gn_listsel]].team_lineup_ind;
								gteams[gplayers[gn_playind[gn_listsel]].team_ind].b_changed = true;
							}
						}
					}
				}
				break;
				case IDB_MAKE_GOLD:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						int ii;
						for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
							SendDlgItemMessage(ghw_tab1, ii, WM_SETTEXT, 0, (LPARAM)_T("99"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_SETTEXT, 0, (LPARAM)_T("8"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_SETTEXT, 0, (LPARAM)_T("3"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKUS, WM_SETTEXT, 0, (LPARAM)_T("4"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKAC, WM_SETTEXT, 0, (LPARAM)_T("4"));
					}
				}
				break;
				case IDB_MAKE_SILV:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						int ii;
						for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
							SendDlgItemMessage(ghw_tab1, ii, WM_SETTEXT, 0, (LPARAM)_T("88"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_SETTEXT, 0, (LPARAM)_T("8"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_SETTEXT, 0, (LPARAM)_T("3"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKUS, WM_SETTEXT, 0, (LPARAM)_T("4"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKAC, WM_SETTEXT, 0, (LPARAM)_T("4"));
					}
				}
				break;
				case IDB_MAKE_REGU:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						int ii;
						for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
							if(ii==IDT_ABIL_DEFP || ii==IDT_ABIL_BWIN || ii==IDT_ABIL_EXPL) //Nerf Defensive Prowess, Ball winning and Explosive power to 72
								SendDlgItemMessage(ghw_tab1, ii, WM_SETTEXT, 0, (LPARAM)_T("77"));
							else
								SendDlgItemMessage(ghw_tab1, ii, WM_SETTEXT, 0, (LPARAM)_T("77"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_SETTEXT, 0, (LPARAM)_T("4"));
						SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_SETTEXT, 0, (LPARAM)_T("1"));
					}
				}
				break;
				case IDB_SET_STATS:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						int ii;
						TCHAR buffer[3];
						GetDlgItemText(H, IDT_SET_STATS, buffer, 3);
						for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
						{
							SetDlgItemText(ghw_tab1, ii, buffer);
						}
					}
				}
				break;
				case IDM_DATA_AATFC: //Run AATF on currently-selected team and show results in a dialog box
				{
					if(gn_teamsel > -1)
					{
						update_tables();
						ShowWindow(ghAatfbox, SW_SHOW);
						aatf_single(ghAatfbox, giPesVersion, gn_teamsel, gplayers, gteams, gnum_players);
					}
					else MessageBox(H,_T("Please select a team to check."),NULL,MB_ICONWARNING);
				}
				break;
				case IDM_DATA_AATFS: //Run AATF on teams selected from a list
				{
					if(ghdescriptor)
					{
						update_tables();
						DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AATF_SEL), H, aatf_sel_dlg_proc);
					}
				}
				break;
				case IDM_DATA_COMPE: //Compare this save to another and report any changes
				{
					if(ghdescriptor)
					{
						update_tables();
						
						//Open dialog box to get file path
						OPENFILENAME ofn;
						TCHAR cs_file_name[MAX_PATH] = _T("");
						TCHAR cs_open_title[40];

						_stprintf_s(cs_open_title, 40, _T("Select PES%d EDIT file for comparison"), giPesVersion);

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = NULL;
					//	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = cs_file_name;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrTitle = cs_open_title;

						if(GetOpenFileName(&ofn))
						{
							DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AATF), H, aatf_comp_dlg_proc, (LPARAM)cs_file_name);
							//DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AATF), H, aatf_comp_dlg_proc);
						}
						//else
						//{
						//	DWORD ret = CommDlgExtendedError();
						//	int lll=0;
						//}
					}
				}
				break;
				/*case IDC_NAME_LIST:
				{
					if(HIWORD(W)==LBN_SELCHANGE)
					{
						player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
						if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
							gplayers[gn_playind[gn_listsel]] = pe_current;

						//Update displayed name

						//Check and update team tables
						//team_entry te_current = get_form_team_info();

						gn_listsel = SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LB_GETCURSEL, 0, 0);
						show_player_info(gn_playind[gn_listsel]);
					}
				}*/
				break;
			}
		break;
		default:
			return DefWindowProc(H, M, W, L);
	}
	return 0;
}

//Load libpesXcrypter.dll and the helper functions we need from it
int loadDLL()
{
	//Load DLL
	hPesDecryptDLL = LoadLibrary(L"lib\\libpesXcrypter.dll");
	if(!hPesDecryptDLL)
	{
		MessageBox(NULL, _T("Failed to load libpesXcrypter.dll"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return EXIT_FAILURE;
	}
	//Load functions from DLL
	createFileDescriptorOld = (pf_createFileDescriptorOld)GetProcAddress(hPesDecryptDLL, "createFileDescriptorOld");
	if(!createFileDescriptorOld)
	{
		MessageBox(NULL, _T("Failed to load createFileDescriptorOld"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	createFileDescriptorNew = (pf_createFileDescriptorNew)GetProcAddress(hPesDecryptDLL, "createFileDescriptorNew");
	if(!createFileDescriptorNew)
	{
		MessageBox(NULL, _T("Failed to load createFileDescriptorNew"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	destroyFileDescriptorOld = (pf_destroyFileDescriptorOld)GetProcAddress(hPesDecryptDLL, "destroyFileDescriptorOld");
	if(!destroyFileDescriptorOld)
	{
		MessageBox(NULL, _T("Failed to load destroyFileDescriptorOld"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	destroyFileDescriptorNew = (pf_destroyFileDescriptorNew)GetProcAddress(hPesDecryptDLL, "destroyFileDescriptorNew");
	if(!destroyFileDescriptorNew)
	{
		MessageBox(NULL, _T("Failed to load destroyFileDescriptorNew"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	decryptWithKeyOld = (pf_decryptWithKeyOld)GetProcAddress(hPesDecryptDLL, "decryptWithKeyOld");
	if(!decryptWithKeyOld)
	{
		MessageBox(NULL, _T("Failed to load decryptWithKeyOld"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	decryptWithKeyNew = (pf_decryptWithKeyNew)GetProcAddress(hPesDecryptDLL, "decryptWithKeyNew");
	if(!decryptWithKeyNew)
	{
		MessageBox(NULL, _T("Failed to load decryptWithKeyNew"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	encryptWithKeyOld = (pf_encryptWithKeyOld)GetProcAddress(hPesDecryptDLL, "encryptWithKeyOld");
	if(!encryptWithKeyOld)
	{
		MessageBox(NULL, _T("Failed to load encryptWithKeyOld"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	encryptWithKeyNew = (pf_encryptWithKeyNew)GetProcAddress(hPesDecryptDLL, "encryptWithKeyNew");
	if(!encryptWithKeyNew)
	{
		MessageBox(NULL, _T("Failed to load encryptWithKeyNew"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
		FreeLibrary(hPesDecryptDLL);
		return EXIT_FAILURE;
	}
	return 0;
}

//Launch an Open File dialog box and attempt to open the selected file
void DoFileOpen(HWND hwnd, TCHAR* pcs_title)
{
	OPENFILENAME ofn;
	TCHAR cs_file_name[MAX_PATH] = _T("");

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
//	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = cs_file_name;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
//	ofn.lpstrDefExt = "txt";
	ofn.lpstrTitle = pcs_title;

	if(GetOpenFileName(&ofn))
	{
		gb_firstsave = true;
		__try
		{
			data_handler(cs_file_name);
		}
		__except(EXCEPTION_EXECUTE_HANDLER) //If file loading fails (usually due to trying to open the wrong type of file for the chosen loader, 
											// e.g. opening a PES21 save file with the PES19 loading function), report the error and fail gracefully
		{
			TCHAR errBuffer[MAX_PATH] = _T("");
			_stprintf_s(errBuffer, MAX_PATH, _T("File loading failed with code %d.\nThe EDIT file may be from a different PES version or may be malformed."),
				GetExceptionCode());
			MessageBox(ghw_main, errBuffer, _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
			//Clear all entries, as no save has been loaded
			if(ghdescriptor) 
			{
				if(giPesVersion>=18)
					destroyFileDescriptorNew((FileDescriptorNew*)ghdescriptor);
				else
					destroyFileDescriptorOld((FileDescriptorOld*)ghdescriptor);
				ghdescriptor = NULL;
			}
			SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_DELETEALLITEMS, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_RESETCONTENT, 0, 0);
			return;
		}
	}
}

//Launch a Save File dialog box and save the PES EDIT data to the chosen location
void DoFileSave(HWND hwnd)
{
	OPENFILENAME ofn;
	TCHAR cs_file_name[MAX_PATH] = _T("");

	ZeroMemory(&ofn, sizeof(ofn));
	TCHAR cs_save_title[30];
	_stprintf_s(cs_save_title, 30, _T("Save PES%d EDIT file"), giPesVersion);

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = cs_file_name;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = cs_save_title;

	if(GetSaveFileName(&ofn))
	{
		if( PathFileExists(cs_file_name) && gb_firstsave )
		{
			gb_firstsave = false;

			TCHAR cs_backup_file_name[MAX_PATH];
			int size = _tcsnlen(cs_file_name,MAX_PATH);
			_tcsncpy(cs_backup_file_name, cs_file_name, size);
			_tcsncpy(&cs_backup_file_name[size], _T(".BACKUP\0"), 8);
			CopyFile(cs_file_name, cs_backup_file_name, false);
		}	
		save_handler(cs_file_name);
	}
}


void data_handler(const TCHAR *pcs_file_name)
{
	int ii, current_byte, appearance_byte;

	if(ghdescriptor) 
	{
		if(giPesVersion>=18)
			destroyFileDescriptorNew((FileDescriptorNew*)ghdescriptor);
		else
			destroyFileDescriptorOld((FileDescriptorOld*)ghdescriptor);
		ghdescriptor = NULL;
	}
	if(gplayers) 
	{
		delete[] gplayers;
		gplayers = NULL;
	}
	if(gn_playind) 
	{
		delete[] gn_playind;
		gn_playind = NULL;
	}
	if(gteams) 
	{
		delete[] gteams;
		gteams = NULL;
	}
	if(gn_teamCbIndToArray) 
	{
		delete[] gn_teamCbIndToArray;
		gn_teamCbIndToArray = NULL;
	}
	if(gn_teamArrayIndToCb) 
	{
		delete[] gn_teamArrayIndToCb;
		gn_teamArrayIndToCb = NULL;
	}

	//Disable extra skill checkboxes
	for(ii=28;ii<41;ii++)
	{
		Button_SetCheck(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii),BST_UNCHECKED);
		Button_Enable(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii), FALSE); 
	}
	//Disable extra ability editboxes
	EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_TIPO), FALSE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_TIPO));
	EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T44), FALSE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T44));
	EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_AGGR), FALSE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_AGGR));
	EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T45), FALSE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T45));

	//Enable Physical Contact skill edit control
	EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_PHCO), TRUE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_PHCO));
	EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T36), TRUE);
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T36));

	//Remove Custom Skin option
	if(SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_GETCOUNT, 0, 0) == 8)
		SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_DELETESTRING, (WPARAM)7, 0);

	//Change Attacking Prowess label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T21), _T("Attacking Prowess:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T21));

	//Change Swerve label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T28), _T("Swerve:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T28));

	//Change Defensive Prowess label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T30), _T("Defensive Prowess:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T30));

	//Change Explosive Power label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T34), _T("Explosive Power:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T34));

	//Change Body Control label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T35), _T("Body Control:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T35));

	//Change Goalkeeping label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T39), _T("Goalkeeping:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T39));

	//Change Coverage label to default
	SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T43), _T("Coverage:"));
	UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T43));

	if(giPesVersion==16)
	{
		ghdescriptor = (void*)createFileDescriptorOld();
		gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes16");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyOld((FileDescriptorOld*)ghdescriptor, pfin, reinterpret_cast<const char*>(gpMasterKey));

		//Ensure Custom Skin option is available
		if(SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_GETCOUNT, 0, 0) < 8)
			SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_ADDSTRING, 0, (LPARAM)_T("Custom"));

		//Disable Physical Contact skill box in 16, as this stat doesn't exist
		EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_PHCO), FALSE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_PHCO));
		EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T36), FALSE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T36));

		//Change Body Control label to "Body Balance"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T35), _T("Body Balance:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T35));

		//Fill Play Style combobox:	
		if(SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCOUNT, 0, 0) > 18)
		{
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("None"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Goal Poacher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Dummy Runner"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fox in the Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Prolific Winger"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Classic No. 10"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Hole Player"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Box to Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Anchor Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("The Destroyer"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Extra Frontman"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Target Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Creative Playmaker"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Build Up"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Goalkeeper"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Goalkeeper"));
		}
		
		//get number of player, team entries
		gnum_players = ((FileDescriptorOld*)ghdescriptor)->data[0x34];
		gnum_players += (((FileDescriptorOld*)ghdescriptor)->data[0x35])*256;
		
		gnum_teams = ((FileDescriptorOld*)ghdescriptor)->data[0x38];
		gnum_teams += (((FileDescriptorOld*)ghdescriptor)->data[0x39])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x4C;
		appearance_byte = 0x2AB9CC;
		gplayers = new player_entry[gnum_players];
		for(ii=0;ii<gnum_players;ii++)
		{
			fill_player_entry16(gplayers[ii], current_byte, ghdescriptor);
			fill_appearance_entry16(gplayers[ii], appearance_byte, ghdescriptor);
		}

		//place team entries into array of structs
		current_byte = 0x46310C;
		gteams = new team_entry[gnum_teams];
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_ids16(gteams[ii], current_byte, ghdescriptor);
		}

		current_byte = 0x4FCC6C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_rosters16(current_byte, ghdescriptor, gteams, gnum_teams);
		}

		current_byte = 0x51F814;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_tactics16(current_byte, ghdescriptor, gteams, gnum_teams);
		}
	}
	else if(giPesVersion==17)
	{
		ghdescriptor = (void*)createFileDescriptorOld();
		gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes17");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyOld((FileDescriptorOld*)ghdescriptor, pfin, reinterpret_cast<const char*>(gpMasterKey));

		//Ensure Custom Skin option is available
		if(SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_GETCOUNT, 0, 0) < 8)
			SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_ADDSTRING, 0, (LPARAM)_T("Custom"));

		//Fill Play Style combobox:	
		if(SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCOUNT, 0, 0) > 18)
		{
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("None"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Goal Poacher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Dummy Runner"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fox in the Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Prolific Winger"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Classic No. 10"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Hole Player"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Box to Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Anchor Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("The Destroyer"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Extra Frontman"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Target Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Creative Playmaker"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Build Up"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Goalkeeper"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Goalkeeper"));
		}

		//get number of player, team entries
		gnum_players = ((FileDescriptorOld*)ghdescriptor)->data[0x5C];
		gnum_players += (((FileDescriptorOld*)ghdescriptor)->data[0x5D])*256;

		gnum_teams = ((FileDescriptorOld*)ghdescriptor)->data[0x60];
		gnum_teams += (((FileDescriptorOld*)ghdescriptor)->data[0x61])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x78;
		gplayers = new player_entry[gnum_players];
		for(ii=0;ii<gnum_players;ii++)
		{
			fill_player_entry17(gplayers[ii], current_byte, ghdescriptor);
		}

		//place team entries into array of structs
		current_byte = 0x3C3E58;
		gteams = new team_entry[gnum_teams];
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_ids17(gteams[ii], current_byte, ghdescriptor);
		}

		current_byte = 0x475A90;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_rosters17(current_byte, ghdescriptor, gteams, gnum_teams);
		}

		current_byte = 0x490640;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_tactics17(current_byte, ghdescriptor, gteams, gnum_teams);
		}
	}
	else if(giPesVersion==18)
	{
		ghdescriptor = (void*)createFileDescriptorNew();
		gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes18");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyNew((FileDescriptorNew*)ghdescriptor, pfin, reinterpret_cast<const char*>(gpMasterKey));

		//Change Body Control label to "Strength on the Ball"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T35), _T("Strength on Ball:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T35)); //RedrawWindow(static_label, NULL, NULL, RDW_ERASE);

		//Fill Play Style combobox:	
		if(SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCOUNT, 0, 0) > 18)
		{
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("None"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Goal Poacher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Dummy Runner"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fox in the Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Prolific Winger"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Classic No. 10"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Hole Player"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Box to Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Anchor Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("The Destroyer"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Extra Frontman"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Target Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Creative Playmaker"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Build Up"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Goalkeeper"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Goalkeeper"));
		}

		//get number of player, team entries
		gnum_players = ((FileDescriptorNew*)ghdescriptor)->data[96];
		gnum_players += (((FileDescriptorNew*)ghdescriptor)->data[97])*256;

		gnum_teams = ((FileDescriptorNew*)ghdescriptor)->data[100];
		gnum_teams += (((FileDescriptorNew*)ghdescriptor)->data[101])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x7C;
		gplayers = new player_entry[gnum_players];
		for(ii=0;ii<gnum_players;ii++)
		{
			fill_player_entry18(gplayers[ii], current_byte, ghdescriptor);
		}

		//place team entries into array of structs
		current_byte = 0x3C3E5C;
		gteams = new team_entry[gnum_teams];
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_ids18(gteams[ii], current_byte, ghdescriptor);
		}

		current_byte = 0x46FF54;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_rosters18(current_byte, ghdescriptor, gteams, gnum_teams);
		}

		current_byte = 0x488B74;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_tactics18(current_byte, ghdescriptor, gteams, gnum_teams);
		}
	}
	else if(giPesVersion==19) // PES 19
	{
		ghdescriptor = (void*)createFileDescriptorNew();
		gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes19");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyNew((FileDescriptorNew*)ghdescriptor, pfin, reinterpret_cast<const char*>(gpMasterKey));

		//Change Body Control label to "Unwavering Balance"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T35), _T("Unwavering Balance:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T35)); //RedrawWindow(static_label, NULL, NULL, RDW_ERASE);

		//Fill Play Style combobox:	
		if(SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCOUNT, 0, 0) < 22)
		{
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("None"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Goal Poacher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Dummy Runner"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fox in the Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Target Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Creative Playmaker"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Prolific Winger"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Roaming Flank"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Crossing Specialist"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Classic No. 10"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Hole Player"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Box to Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("The Destroyer"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Orchestrator"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Anchor Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Build Up"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fullback Finisher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Extra Frontman"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Goalkeeper"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Goalkeeper"));
		}

		//Enable extra skill checkboxes up to 39
		for(ii=28;ii<39;ii++)
		{
			Button_Enable(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii), TRUE); 
		}

		//get number of player, team entries
		gnum_players = ((FileDescriptorNew*)ghdescriptor)->data[96];
		gnum_players += (((FileDescriptorNew*)ghdescriptor)->data[97])*256;

		gnum_teams = ((FileDescriptorNew*)ghdescriptor)->data[100];
		gnum_teams += (((FileDescriptorNew*)ghdescriptor)->data[101])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x7C;
		gplayers = new player_entry[gnum_players];
		for(ii=0;ii<gnum_players;ii++)
		{
			fill_player_entry19(gplayers[ii], current_byte, ghdescriptor);
		}

		//place team entries into array of structs
		current_byte = 0x5BCC7C;
		gteams = new team_entry[gnum_teams];
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_ids19(gteams[ii], current_byte, ghdescriptor);
		}

		current_byte = 0x6773C4;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_rosters19(current_byte, ghdescriptor, gteams, gnum_teams);
		}

		current_byte = 0x69EC8C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_tactics19(current_byte, ghdescriptor, gteams, gnum_teams);
		}
	}
	else // PES 20/21
	{
		ghdescriptor = (void*)createFileDescriptorNew();
		if(giPesVersion==20)
			gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes20");
		else
			gpMasterKey = (const uint8_t*)GetProcAddress(hPesDecryptDLL, "MasterKeyPes21");
		uint8_t *pfin = readFile(pcs_file_name, NULL);
		decryptWithKeyNew((FileDescriptorNew*)ghdescriptor, pfin, reinterpret_cast<const char*>(gpMasterKey));

		//Enable extra ability editboxes
		EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_TIPO), TRUE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_TIPO));
		EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T44), TRUE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T44));
		EnableWindow(GetDlgItem(ghw_tab1, IDT_ABIL_AGGR), TRUE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDT_ABIL_AGGR));
		EnableWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T45), TRUE);
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T45));

		//Change Attacking Prowess label to "Offensive Awareness"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T21), _T("Offensive Awareness:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T21));

		//Change Swerve label to "Curl"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T28), _T("Curl:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T28));

		//Change Defensive Prowess label to "Defensive Awareness"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T30), _T("Defensive Awareness:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T30));

		//Change Explosive Power label to "Acceleration"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T34), _T("Acceleration:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T34));
		
		//Change Body Control label to "Balance"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T35), _T("Balance:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T35));

		//Change Goalkeeping label to "GK Awareness"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T39), _T("GK Awareness:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T39));

		//Change Coverage label to "GK Reach"
		SetWindowText(GetDlgItem(ghw_tab1, IDC_STATIC_T43), _T("GK Reach:"));
		UpdateWindow(GetDlgItem(ghw_tab1, IDC_STATIC_T43));

		//Fill Play Style combobox:	
		if(SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCOUNT, 0, 0) < 22)
		{
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("None"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Goal Poacher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Dummy Runner"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fox in the Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Target Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Creative Playmaker"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Prolific Winger"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Roaming Flank"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Crossing Specialist"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Classic No. 10"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Hole Player"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Box to Box"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("The Destroyer"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Orchestrator"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Anchor Man"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Fullback Finisher"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Fullback"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Build Up"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Extra Frontman"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Offensive Goalkeeper"));
			SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_ADDSTRING, 0, (LPARAM)_T("Defensive Goalkeeper"));
		}

		//Enable extra skill checkboxes
		for(ii=28;ii<41;ii++)
		{
			Button_Enable(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii), TRUE); 
		}

		//get number of player, team entries
		gnum_players = ((FileDescriptorNew*)ghdescriptor)->data[96];
		gnum_players += (((FileDescriptorNew*)ghdescriptor)->data[97])*256;

		gnum_teams = ((FileDescriptorNew*)ghdescriptor)->data[100];
		gnum_teams += (((FileDescriptorNew*)ghdescriptor)->data[101])*256;

		//place player info+appearance entries into array of structs
		current_byte = 0x7C;
		gplayers = new player_entry[gnum_players];
		for(ii=0;ii<gnum_players;ii++)
		{
			fill_player_entry20(gplayers[ii], current_byte, ghdescriptor);
		}

		//place team entries into array of structs
		current_byte = 0x8ED2FC;
		gteams = new team_entry[gnum_teams];
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_ids20(gteams[ii], current_byte, ghdescriptor);
		}

		current_byte = 0x9D4648;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_rosters20(current_byte, ghdescriptor, gteams, gnum_teams);
		}

		current_byte = 0xA09880;
		for(ii=0;ii<gnum_teams;ii++)
		{
			fill_team_tactics20(current_byte, ghdescriptor, gteams, gnum_teams);
		}
	}

	//Find, hide loose players
	int jj, kk;
	for(ii=0;ii<gnum_players;ii++)
	{
		bool match = false;
		for(jj=0;jj<gnum_teams;jj++)
		{
			for(kk=0;kk < gteams->team_max;kk++)
			{
				if(gteams[jj].players[kk]==gplayers[ii].id)
				{
					match = true;
					break;
				}
			}
			if(match)
			{
				gplayers[ii].team_ind = jj;
				gplayers[ii].team_lineup_ind = kk;
				break;
			}
		}
		if(gplayers[ii].team_ind < 0) 
		{
			//player_entry pe = gplayers[ii]; //DEBUG
			gplayers[ii].b_show = false;
		}
	}

	fill_list_all_players();

	SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_ADDSTRING, 0, (LPARAM)_T("ALL"));
	gn_teamCbIndToArray = new int[gnum_teams];
	gn_teamArrayIndToCb = new int[gnum_teams];
	jj=0;
	for(ii=0;ii<gnum_teams;ii++)
	{
		if(gteams[ii].b_show)
		{
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_ADDSTRING, 0, (LPARAM)gteams[ii].name);
			gn_teamCbIndToArray[jj] = ii;
			gn_teamArrayIndToCb[ii] = jj;
			jj++;
		}
	}
	SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, (WPARAM)0, 0);
	gn_teamsel = -1;

	//display the info for first player in list
	ii=0;
	while(!gplayers[ii].b_show) ii++;
	show_player_info(ii);

	//Cleanup should go elsewhere...
}


void save_handler(const TCHAR *pcs_file_name)
{
	//First update the data structure to reflect any changes the user has made to the current player/team
	player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
	if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
	{
		if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
			pe_current.b_edit_player = true;
		gplayers[gn_playind[gn_listsel]] = pe_current;
		
		//Update displayed name
		LVITEM lvI;
		memset(&lvI,0,sizeof(lvI)); //Zero out struct members
		lvI.mask = LVIF_TEXT;
		lvI.pszText = pe_current.name;
		lvI.iItem = gn_listsel;
		SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);

		show_player_info(gn_playind[gn_listsel]);
	}

	//Check and update team tables
	team_entry te_current;
	if( get_form_team_info(gn_playind[gn_listsel], te_current) )
	{
		int ti = gplayers[gn_playind[gn_listsel]].team_ind;
		if( !(gteams[ti] == te_current) )
		{
			gteams[ti] = te_current;

			//Update combobox
			int csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_DELETESTRING, gn_teamArrayIndToCb[ti]+1, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_INSERTSTRING, gn_teamArrayIndToCb[ti]+1, (LPARAM)te_current.name);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, csel, 0);								
		}
	}

	//Now write any changed player and team entries back into the ghdescriptor
	if(giPesVersion==16)
	{
		//Extract player info & appearance from array of structs
		int ii, current_byte = 0x4C, appearance_byte = 0x2AB9CC;
		//char strcheck[0x72]; //DEBUG
		for(ii=0;ii<gnum_players;ii++)
		{
			extract_player_entry16(gplayers[ii], current_byte, appearance_byte, ghdescriptor);
			//memcpy(strcheck, &(ghdescriptor->data[0x82C]), 0x70); //DEBUG
			//t2=0;
		}

		//Extract team info from array of structs
		current_byte = 0x46310C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_info16(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x4FCC6C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_teamplayer_info16(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x51F814;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_tactics16(gteams[ii], current_byte, ghdescriptor);
		}

		//Write out data to file
		int outputSize;
		uint8_t *output;
		output = encryptWithKeyOld((FileDescriptorOld*)ghdescriptor, &outputSize, reinterpret_cast<const char*>(gpMasterKey));
		writeFile(pcs_file_name, output, outputSize);
	}
	else if(giPesVersion==17)
	{
		//Extract player info & appearance from array of structs
		int ii, current_byte = 0x78;
		for(ii=0;ii<gnum_players;ii++)
		{
			extract_player_entry17(gplayers[ii], current_byte, ghdescriptor);
		}

		//Extract team info from array of structs
		current_byte = 0x3C3E58;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_info17(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x475A90;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_teamplayer_info17(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x490640;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_tactics17(gteams[ii], current_byte, ghdescriptor);
		}

		//Write out data to file
		int outputSize;
		uint8_t *output;
		output = encryptWithKeyOld((FileDescriptorOld*)ghdescriptor, &outputSize, reinterpret_cast<const char*>(gpMasterKey));
		writeFile(pcs_file_name, output, outputSize);
	}
	else if(giPesVersion==18)
	{
		//Extract player info & appearance from array of structs
		int ii, current_byte = 0x7C;
		for(ii=0;ii<gnum_players;ii++)
		{
			extract_player_entry18(gplayers[ii], current_byte, ghdescriptor);
		}

		//Extract team info from array of structs
		current_byte = 0x3C3E5C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_info18(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x46FF54;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_teamplayer_info18(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x488B74;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_tactics18(gteams[ii], current_byte, ghdescriptor);
		}

		//Write out data to file
		int outputSize;
		uint8_t *output;
		output = encryptWithKeyNew((FileDescriptorNew*)ghdescriptor, &outputSize, reinterpret_cast<const char*>(gpMasterKey));
		writeFile(pcs_file_name, output, outputSize);
	}
	else if(giPesVersion==19)
	{
		//Extract player info & appearance from array of structs
		int ii, current_byte = 0x7C;
		for(ii=0;ii<gnum_players;ii++)
		{
			extract_player_entry19(gplayers[ii], current_byte, ghdescriptor);
		}

		//Extract team info from array of structs
		current_byte = 0x5BCC7C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_info19(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x6773C4;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_teamplayer_info19(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x69EC8C;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_tactics19(gteams[ii], current_byte, ghdescriptor);
		}

		//Write out data to file
		int outputSize;
		uint8_t *output;
		output = encryptWithKeyNew((FileDescriptorNew*)ghdescriptor, &outputSize, reinterpret_cast<const char*>(gpMasterKey));
		writeFile(pcs_file_name, output, outputSize);
	}
	else //PES 20/21
	{
		//Extract player info & appearance from array of structs
		int ii, current_byte = 0x7C;
		for(ii=0;ii<gnum_players;ii++)
		{
			extract_player_entry20(gplayers[ii], current_byte, ghdescriptor);
		}

		//Extract team info from array of structs
		current_byte = 0x8ED2FC;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_info20(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0x9D4648;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_teamplayer_info20(gteams[ii], current_byte, ghdescriptor);
		}
		current_byte = 0xA09880;
		for(ii=0;ii<gnum_teams;ii++)
		{
			extract_team_tactics20(gteams[ii], current_byte, ghdescriptor);
		}

		//Write out data to file
		int outputSize;
		uint8_t *output;
		output = encryptWithKeyNew((FileDescriptorNew*)ghdescriptor, &outputSize, reinterpret_cast<const char*>(gpMasterKey));
		writeFile(pcs_file_name, output, outputSize);
	}
}

void fill_list_all_players()
{
	int ii, jj;

	//fill player, text lists in window
	gn_playind = new int[gnum_players];
	SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_DELETEALLITEMS, 0, 0);
	LVITEM lvI;
	memset(&lvI,0,sizeof(lvI)); //Zero out struct members
	lvI.mask = LVIF_TEXT;
	jj=0;
	for(ii=0;ii<gnum_players;ii++)
	{
		if(gplayers[ii].b_show)
		{
			gn_playind[jj] = ii;
			lvI.pszText = gplayers[ii].name;
			lvI.iItem = jj;
			SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_INSERTITEM, 0, (LPARAM)&lvI);
			jj++;
		}
	}
	gn_listsel = 0;
	ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), 0, LVIS_SELECTED, LVIS_SELECTED);	
}


void show_player_info(int p_ind)
{
	int ii,jj;
	bool match=false;
	wchar_t buffer[21];
	memset(buffer,0,sizeof(buffer));
	//ZeroMemory(buffer,12);

	SendDlgItemMessage(ghw_main, IDT_PLAY_NAME, WM_SETTEXT, 0, (LPARAM)gplayers[p_ind].name);

	_itow_s(gplayers[p_ind].id, buffer, 12, 10);
	SendDlgItemMessage(ghw_main, IDT_PLAY_ID, WM_SETTEXT, 0, (LPARAM)buffer);

	mbstowcs(buffer, gplayers[p_ind].shirt_name, 20);
	SendDlgItemMessage(ghw_main, IDT_PLAY_SHIRT, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].nation, buffer, 12, 10);
	SendDlgItemMessage(ghw_main, IDT_PLAY_NAT, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].height, buffer, 12, 10);
	SendDlgItemMessage(ghw_main, IDT_PLAY_HGT, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].weight, buffer, 12, 10);
	SendDlgItemMessage(ghw_main, IDT_PLAY_WGT, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].age, buffer, 12, 10);
	SendDlgItemMessage(ghw_main, IDT_PLAY_AGE, WM_SETTEXT, 0, (LPARAM)buffer);

	if(gplayers[p_ind].b_edit_player) Button_SetCheck(GetDlgItem(ghw_main, IDB_PLAY_EDIT),BST_CHECKED);
	else Button_SetCheck(GetDlgItem(ghw_main, IDB_PLAY_EDIT),BST_UNCHECKED);

	SendDlgItemMessage(ghw_main, IDC_PLAY_FOOT, CB_SETCURSEL, (WPARAM)gplayers[p_ind].strong_foot, 0);
	SendDlgItemMessage(ghw_tab2, IDC_PLAY_HAND, CB_SETCURSEL, (WPARAM)gplayers[p_ind].strong_hand, 0);
	
	SendDlgItemMessage(ghw_main, IDC_PLAY_RPOS, CB_SETCURSEL, (WPARAM)gplayers[p_ind].reg_pos, 0);

	ii = gplayers[p_ind].play_style;
	if(giPesVersion==16 && ii>16) ii--;
	SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_SETCURSEL, (WPARAM)ii, 0);

	for(ii=0;ii<13;ii++)
	{
		SendDlgItemMessage(ghw_tab1, IDS_PLAY_CF+ii, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)gplayers[p_ind].play_pos[ii]);
	}

	for(ii=0;ii<7;ii++)
	{
		Button_SetCheck(GetDlgItem(ghw_tab1, IDB_COM_TRIC+ii),gplayers[p_ind].com_style[ii]);
	}

	int numSkill;
	if(giPesVersion==19) numSkill=39;
	else if(giPesVersion>=20) numSkill=41;
	else numSkill=28;
	for(ii=0;ii<numSkill;ii++)
	{
		Button_SetCheck(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii),gplayers[p_ind].play_skill[ii]);
	}

	_itow_s(gplayers[p_ind].atk, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_ATKP, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].ball_ctrl, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BCON, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].drib, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_DRIB, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].lowpass, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_LOWP, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].loftpass, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_LOFT, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].finish, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_FINI, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].place_kick, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_PKIC, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].swerve, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_SWER, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].header, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_HEAD, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].def, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_DEFP, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].ball_win, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BWIN, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].kick_pwr, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_KPOW, WM_SETTEXT, 0, (LPARAM)buffer);	

	_itow_s(gplayers[p_ind].speed, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_SPED, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].exp_pwr, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_EXPL, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].body_ctrl, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BODB, WM_SETTEXT, 0, (LPARAM)buffer);

	if(giPesVersion!=16)
	{
		_itow_s(gplayers[p_ind].phys_cont, buffer, 3, 10);
		SendDlgItemMessage(ghw_tab1, IDT_ABIL_PHCO, WM_SETTEXT, 0, (LPARAM)buffer);
	}

	_itow_s(gplayers[p_ind].jump, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_JUMP, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].stamina, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_STAM, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].gk, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_GOAL, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].catching, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_CATC, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].clearing, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_CLEA, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].reflex, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_REFL, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].cover, buffer, 3, 10); //ERROR HERE
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_COVE, WM_SETTEXT, 0, (LPARAM)buffer);

	if(giPesVersion>=20)
	{
		_itow_s(gplayers[p_ind].tight_pos, buffer, 3, 10);
		SendDlgItemMessage(ghw_tab1, IDT_ABIL_TIPO, WM_SETTEXT, 0, (LPARAM)buffer);

		_itow_s(gplayers[p_ind].aggres, buffer, 3, 10);
		SendDlgItemMessage(ghw_tab1, IDT_ABIL_AGGR, WM_SETTEXT, 0, (LPARAM)buffer);
	}

	_itow_s(gplayers[p_ind].weak_use + 1, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKUS, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].weak_acc + 1, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKAC, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].form + 1, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].injury + 1, buffer, 3, 10);
	SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_SETTEXT, 0, (LPARAM)buffer);

	if(giPesVersion>=19)
	{
		_itow_s(gplayers[p_ind].star, buffer, 3, 10);
		SendDlgItemMessage(ghw_tab1, IDT_STAR, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	if(giPesVersion>=20)
	{
		_itow_s(gplayers[p_ind].play_attit, buffer, 3, 10);
		SendDlgItemMessage(ghw_tab1, IDT_PLAY_ATT, WM_SETTEXT, 0, (LPARAM)buffer);
	}

	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_FACE),gplayers[p_ind].b_edit_face);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_HAIR),gplayers[p_ind].b_edit_hair);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_PHYS),gplayers[p_ind].b_edit_phys);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_STRP),gplayers[p_ind].b_edit_strip);

	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_COPY_BASE),gplayers[p_ind].b_base_copy);

	_itow_s(gplayers[p_ind].copy_id, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_COPY_ID, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].head_len - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HELE, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].head_wid - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEWI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].head_dep - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEDE, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].neck_len - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_NELE, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].neck_size - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_NESI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].shldr_hi - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_SHHE, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].shldr_wid - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_SHWI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].chest - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CHSI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].waist - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_WASI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].arm_size - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_ARSI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].arm_len - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_ARLE, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].thigh - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_THSI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].calf - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CASI, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].leg_len - 7, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_LELE, WM_SETTEXT, 0, (LPARAM)buffer);

	if(giPesVersion>=18 && gplayers[p_ind].skin_col==7)
	{
        gplayers[p_ind].skin_col=0;
		gplayers[p_ind].b_changed=true;
	}
	SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)gplayers[p_ind].skin_col, 0);

	SendDlgItemMessage(ghw_tab2, IDC_PHYS_EYES, CB_SETCURSEL, (WPARAM)gplayers[p_ind].iris_col, 0);

	_itow_s(gplayers[p_ind].boot_id, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)buffer);

	_itow_s(gplayers[p_ind].glove_id, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)buffer);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)gplayers[p_ind].wrist_tape, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_SETCURSEL, (WPARAM)gplayers[p_ind].spec_style, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_SETCURSEL, (WPARAM)gplayers[p_ind].spec_col, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)gplayers[p_ind].sleeve, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_SETCURSEL, (WPARAM)gplayers[p_ind].inners, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)gplayers[p_ind].socks, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_SETCURSEL, (WPARAM)gplayers[p_ind].undershorts, 0);

	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)gplayers[p_ind].tucked, 0);

	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_ANTA),gplayers[p_ind].ankle_tape);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV),gplayers[p_ind].gloves);

	_itow_s(gplayers[p_ind].mo_hunchd + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUND, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_armd + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMD, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_hunchr + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUNR, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_armr + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMR, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_ck + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_CK, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_fk + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_FK, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].mo_pk + 1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_PK, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].gc1, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC1, WM_SETTEXT, 0, (LPARAM)buffer);
	_itow_s(gplayers[p_ind].gc2, buffer, 18, 10);
	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC2, WM_SETTEXT, 0, (LPARAM)buffer);

	for(ii=0;ii<gnum_teams;ii++)
	{
		for(jj=0;jj < gteams->team_max;jj++)
		{
			if(gteams[ii].players[jj]==gplayers[p_ind].id)
			{
				match = true;
				break;
			}
		}
		if(match)
		{
			gplayers[p_ind].team_ind = ii;
			gplayers[p_ind].team_lineup_ind = jj;

			SendDlgItemMessage(ghw_main, IDT_TEAM_NAME, WM_SETTEXT, 0, (LPARAM)gteams[ii].name);

			_itow_s(gteams[ii].id, buffer, 12, 10);
			SendDlgItemMessage(ghw_main, IDT_TEAM_ID, WM_SETTEXT, 0, (LPARAM)buffer);

			mbstowcs(buffer, gteams[ii].short_name, 18);
			SendDlgItemMessage(ghw_main, IDT_TEAM_SHORT, WM_SETTEXT, 0, (LPARAM)buffer);
			
			_itow_s(gteams[ii].numbers[jj], buffer, 12, 10);
			SendDlgItemMessage(ghw_main, IDT_PLAY_NUM, WM_SETTEXT, 0, (LPARAM)buffer);

			//If is captain, mark the radio button, otherwise clear it
			if(gteams[ii].players[gteams[ii].captain_ind] == gplayers[p_ind].id)
				SendDlgItemMessage(ghw_main, IDB_CAPTAIN, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
			else
				SendDlgItemMessage(ghw_main, IDB_CAPTAIN, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

			//Update Team tab
			_itow_s((int)gteams[ii].color1_red, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_R1, WM_SETTEXT, 0, (LPARAM)buffer);

			_itow_s((int)gteams[ii].color1_green, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_G1, WM_SETTEXT, 0, (LPARAM)buffer);

			_itow_s((int)gteams[ii].color1_blue, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_B1, WM_SETTEXT, 0, (LPARAM)buffer);

			InvalidateRect(GetDlgItem(ghw_tab3, IDB_TCOLOR1), NULL, TRUE);

			_itow_s((int)gteams[ii].color2_red, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_R2, WM_SETTEXT, 0, (LPARAM)buffer);

			_itow_s((int)gteams[ii].color2_green, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_G2, WM_SETTEXT, 0, (LPARAM)buffer);

			_itow_s((int)gteams[ii].color2_blue, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_TCOL_B2, WM_SETTEXT, 0, (LPARAM)buffer);

			InvalidateRect(GetDlgItem(ghw_tab3, IDB_TCOLOR2), NULL, TRUE);

			_itow_s((int)gteams[ii].manager_id, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_MANAGER, WM_SETTEXT, 0, (LPARAM)buffer);

			_itow_s((int)gteams[ii].stadium_id, buffer, 12, 10);
			SendDlgItemMessage(ghw_tab3, IDT_STADIUM, WM_SETTEXT, 0, (LPARAM)buffer);

			break;
		}
	}


}
player_entry get_form_player_info(int index)
{
	wchar_t buffer[21], wc;
	int ii, shirtNameLen;
	memset(buffer,0,sizeof(buffer));
	//player_entry output;
	//if(index<0 || index > gnum_players) return output; //DEBUG, fix

	player_entry output = gplayers[index]; //need to handle case it is empty
	output.b_changed = true;

	SendDlgItemMessage(ghw_main, IDT_PLAY_NAME, WM_GETTEXT, (WPARAM)46, (LPARAM)output.name);

	SendDlgItemMessage(ghw_main, IDT_PLAY_ID, WM_GETTEXT, 18, (LPARAM)buffer);
	output.id = _wtoi(buffer);

	if(giPesVersion==16) shirtNameLen=16;
	else if(giPesVersion<20) shirtNameLen=18;
	else shirtNameLen=20;
	SendDlgItemMessage(ghw_main, IDT_PLAY_SHIRT, WM_GETTEXT, shirtNameLen+1, (LPARAM)buffer);
	ii = 0;
	while(buffer[ii]) 
	{
		wc = buffer[ii];
		buffer[ii] = towupper(wc);
		ii++;
	}
	wcstombs(output.shirt_name, buffer, shirtNameLen);

	SendDlgItemMessage(ghw_main, IDT_PLAY_NAT, WM_GETTEXT, 18, (LPARAM)buffer);
	output.nation = _wtoi(buffer);

	SendDlgItemMessage(ghw_main, IDT_PLAY_HGT, WM_GETTEXT, 18, (LPARAM)buffer);
	output.height = _wtoi(buffer);

	SendDlgItemMessage(ghw_main, IDT_PLAY_WGT, WM_GETTEXT, 18, (LPARAM)buffer);
	output.weight = _wtoi(buffer);

	SendDlgItemMessage(ghw_main, IDT_PLAY_AGE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.age = _wtoi(buffer);

	if(Button_GetCheck(GetDlgItem(ghw_main, IDB_PLAY_EDIT))==BST_CHECKED) output.b_edit_player=true;
	else output.b_edit_player=false;

	output.strong_foot = SendDlgItemMessage(ghw_main, IDC_PLAY_FOOT, CB_GETCURSEL, 0, 0);
	output.strong_hand = SendDlgItemMessage(ghw_tab2, IDC_PLAY_HAND, CB_GETCURSEL, 0, 0);
	
	output.reg_pos = SendDlgItemMessage(ghw_main, IDC_PLAY_RPOS, CB_GETCURSEL, 0, 0);

	ii = SendDlgItemMessage(ghw_main, IDC_PLAY_STYL, CB_GETCURSEL, 0, 0);
	if(giPesVersion==16 && ii>15) ii++;
	output.play_style = ii;

	for(ii=0;ii<13;ii++)
	{
		output.play_pos[ii] = SendDlgItemMessage(ghw_tab1, IDS_PLAY_CF+ii, TBM_GETPOS, 0, 0);
	}

	for(ii=0;ii<7;ii++)
	{
		if(Button_GetCheck(GetDlgItem(ghw_tab1, IDB_COM_TRIC+ii))==BST_CHECKED) 
			output.com_style[ii]=true;
		else output.com_style[ii]=false;
	}

	int numSkill;
	if(giPesVersion==19) numSkill=39;
	else if(giPesVersion>=20) numSkill=41;
	else numSkill=28;
	for(ii=0;ii<numSkill;ii++)
	{
		if(Button_GetCheck(GetDlgItem(ghw_tab1, IDB_SKIL_SCIS+ii))==BST_CHECKED) 
			output.play_skill[ii]=true;
		else output.play_skill[ii]=false;
	}

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_ATKP, WM_GETTEXT, 18, (LPARAM)buffer);
	output.atk = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BCON, WM_GETTEXT, 18, (LPARAM)buffer);
	output.ball_ctrl = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_DRIB, WM_GETTEXT, 18, (LPARAM)buffer);
	output.drib = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_LOWP, WM_GETTEXT, 18, (LPARAM)buffer);
	output.lowpass = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_LOFT, WM_GETTEXT, 18, (LPARAM)buffer);
	output.loftpass = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_FINI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.finish = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_PKIC, WM_GETTEXT, 18, (LPARAM)buffer);
	output.place_kick = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_SWER, WM_GETTEXT, 18, (LPARAM)buffer);
	output.swerve = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_HEAD, WM_GETTEXT, 18, (LPARAM)buffer);
	output.header = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_DEFP, WM_GETTEXT, 18, (LPARAM)buffer);
	output.def = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BWIN, WM_GETTEXT, 18, (LPARAM)buffer);
	output.ball_win = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_KPOW, WM_GETTEXT, 18, (LPARAM)buffer);
	output.kick_pwr = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_SPED, WM_GETTEXT, 18, (LPARAM)buffer);
	output.speed = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_EXPL, WM_GETTEXT, 18, (LPARAM)buffer);
	output.exp_pwr = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_BODB, WM_GETTEXT, 18, (LPARAM)buffer);
	output.body_ctrl = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_PHCO, WM_GETTEXT, 18, (LPARAM)buffer);
	output.phys_cont = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_JUMP, WM_GETTEXT, 18, (LPARAM)buffer);
	output.jump = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_STAM, WM_GETTEXT, 18, (LPARAM)buffer);
	output.stamina = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_GOAL, WM_GETTEXT, 18, (LPARAM)buffer);
	output.gk = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_CATC, WM_GETTEXT, 18, (LPARAM)buffer);
	output.catching = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_CLEA, WM_GETTEXT, 18, (LPARAM)buffer);
	output.clearing = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_REFL, WM_GETTEXT, 18, (LPARAM)buffer);
	output.reflex = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_COVE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.cover = _wtoi(buffer);

	if(giPesVersion>=20)
	{
		SendDlgItemMessage(ghw_tab1, IDT_ABIL_TIPO, WM_GETTEXT, 18, (LPARAM)buffer);
		output.tight_pos = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab1, IDT_ABIL_AGGR, WM_GETTEXT, 18, (LPARAM)buffer);
		output.aggres = _wtoi(buffer);
	}

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKUS, WM_GETTEXT, 18, (LPARAM)buffer);
	output.weak_use = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_WKAC, WM_GETTEXT, 18, (LPARAM)buffer);
	output.weak_acc = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_FORM, WM_GETTEXT, 18, (LPARAM)buffer);
	output.form = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab1, IDT_ABIL_INJU, WM_GETTEXT, 18, (LPARAM)buffer);
	output.injury = _wtoi(buffer) - 1;

	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_FACE))==BST_CHECKED) output.b_edit_face=true;
	else output.b_edit_face=false;
	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_HAIR))==BST_CHECKED) output.b_edit_hair=true;
	else output.b_edit_hair=false;
	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_PHYS))==BST_CHECKED) output.b_edit_phys=true;
	else output.b_edit_phys=false;
	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_STRP))==BST_CHECKED) output.b_edit_strip=true;
	else output.b_edit_strip=false;

	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_COPY_BASE))==BST_CHECKED) 
	{
		output.b_base_copy=true;
		output.b_edit_ability=true;
		output.b_edit_com=true;
		output.b_edit_motion=true;
		output.b_edit_playpos=true;
		output.b_edit_regpos=true;
		output.b_edit_skill=true;
		output.b_edit_style=true;
	}
	else output.b_base_copy=false;

	SendDlgItemMessage(ghw_tab2, IDT_COPY_ID, WM_GETTEXT, 18, (LPARAM)buffer);
	output.copy_id = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HELE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.head_len = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEWI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.head_wid = _wtoi(buffer) + 7;;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEDE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.head_dep = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_NELE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.neck_len = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_NESI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.neck_size = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_SHHE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.shldr_hi = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_SHWI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.shldr_wid = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CHSI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.chest = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_WASI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.waist = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_ARSI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.arm_size = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_ARLE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.arm_len = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_THSI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.thigh = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CASI, WM_GETTEXT, 18, (LPARAM)buffer);
	output.calf = _wtoi(buffer) + 7;

	SendDlgItemMessage(ghw_tab2, IDT_PHYS_LELE, WM_GETTEXT, 18, (LPARAM)buffer);
	output.leg_len = _wtoi(buffer) + 7;

	output.skin_col = SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_GETCURSEL, 0, 0);

	output.iris_col = SendDlgItemMessage(ghw_tab2, IDC_PHYS_EYES, CB_GETCURSEL, 0, 0);

	SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_GETTEXT, 18, (LPARAM)buffer);
	output.boot_id = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_GETTEXT, 18, (LPARAM)buffer);
	output.glove_id = _wtoi(buffer);

	output.wrist_tape = SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_GETCURSEL, 0, 0);

	output.spec_style = SendDlgItemMessage(ghw_tab2, IDC_STRP_GLST, CB_GETCURSEL, 0, 0);

	output.spec_col = SendDlgItemMessage(ghw_tab2, IDC_STRP_GLCO, CB_GETCURSEL, 0, 0);

	output.sleeve = SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_GETCURSEL, 0, 0);

	output.inners = SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_GETCURSEL, 0, 0);

	output.socks = SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_GETCURSEL, 0, 0);

	output.undershorts = SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_GETCURSEL, 0, 0);

	output.tucked = SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_GETCURSEL, 0, 0);

	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_STRP_ANTA))==BST_CHECKED) output.ankle_tape=true;
	else output.ankle_tape=false;
	if(Button_GetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV))==BST_CHECKED) output.gloves=true;
	else output.gloves=false;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUND, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_hunchd = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMD, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_armd = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_HUNR, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_hunchr = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_ARMR, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_armr = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_CK, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_ck = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_FK, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_fk = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_PK, WM_GETTEXT, 18, (LPARAM)buffer);
	output.mo_pk = _wtoi(buffer) - 1;

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC1, WM_GETTEXT, 18, (LPARAM)buffer);
	output.gc1 = _wtoi(buffer);

	SendDlgItemMessage(ghw_tab2, IDT_MOTI_GC2, WM_GETTEXT, 18, (LPARAM)buffer);
	output.gc2 = _wtoi(buffer);

	return output;
}

bool get_form_team_info(int player_index, team_entry &output)
{
	bool result;
	wchar_t buffer[70], wc;
	char cbuff[4];
	int ii, ti, tli;

	ti = gplayers[player_index].team_ind;
	tli = gplayers[player_index].team_lineup_ind;

	result = ti > -1;

	if(result)
	{
		output = gteams[ti];
		output.b_changed = true;

		SendDlgItemMessage(ghw_main, IDT_TEAM_NAME, WM_GETTEXT, 70, (LPARAM)buffer);
		if( _tcscmp(buffer,output.name) )
		{
			_tcscpy(output.name, buffer);
			output.b_edit_name = true;
		}

		SendDlgItemMessage(ghw_main, IDT_TEAM_ID, WM_GETTEXT, 18, (LPARAM)buffer);
		output.id = _wtoi(buffer);

		SendDlgItemMessage(ghw_main, IDT_TEAM_SHORT, WM_GETTEXT, 4, (LPARAM)buffer);
		buffer[4] = 0;
		ii = 0;
		while(buffer[ii]) 
		{
			wc = buffer[ii];
			buffer[ii] = towupper(wc);
			ii++;
		}
		wcstombs(cbuff,buffer,4);
		if( strcmp(cbuff,output.short_name) )
		{
			strcpy(output.short_name, cbuff);
			output.b_edit_name = true;
		}
		
		SendDlgItemMessage(ghw_main, IDT_PLAY_NUM, WM_GETTEXT, 18, (LPARAM)buffer);
		output.numbers[tli] = _wtoi(buffer);
		if(giPesVersion < 19 && output.numbers[tli]>231) output.numbers[tli] = 231;

		//Get info from Team tab
		SendDlgItemMessage(ghw_tab3, IDT_TCOL_R1, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color1_red = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_TCOL_G1, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color1_green = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_TCOL_B1, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color1_blue = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_TCOL_R2, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color2_red = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_TCOL_G2, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color2_green = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_TCOL_B2, WM_GETTEXT, 4, (LPARAM)buffer);
		output.color2_blue = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_MANAGER, WM_GETTEXT, 9, (LPARAM)buffer);
		output.manager_id = _wtoi(buffer);

		SendDlgItemMessage(ghw_tab3, IDT_STADIUM, WM_GETTEXT, 4, (LPARAM)buffer);
		if( output.stadium_id != _wtoi(buffer) )
		{
			output.stadium_id = _wtoi(buffer);
			output.b_edit_stadium = true;
		}
	}

	return result;
}

//Subclassed control procedure for a listview control.  Used by the
// IDC_PATH_LIST backup path list
LRESULT CALLBACK lv_cntl_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SETCOLUMN:
		{
			//User-defined message to keep the columns of the backup 
			// paths LV tidy.  Called when client area size changes
			// (e.g. a scrollbar is added), it aligns the column widths
			// with the client area width, unless they were already set
			// to be wider than the client area.
			RECT rc_lv;
			GetClientRect(H, &rc_lv);

			ListView_SetColumnWidth(H, 0, rc_lv.right);
			
			return true;
		}

		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy;
			//RECT parent_rect;

			//GetClientRect(ghw_main, &parent_rect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			//BringWindowToTop(H);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			SetWindowPos(H, HWND_TOP, X-g_prevx, Y, cx, cy, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_SIZE:
		{
			//ListView_SetColumnWidth(H, 1, LVSCW_AUTOSIZE_USEHEADER);
			PostMessage(H,UM_SETCOLUMN,0,0);
			return DefSubclassProc(H, M, W, L);
		}

		case WM_KEYDOWN:
		{
			if( W == 0x21 || W == 0x22 ) //We want ONLY default behavior for PGUP and PGDN
				return DefSubclassProc(H, M, W, L);
			common_shortcuts(W);
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}

//Subclassed control procedure for a combobox control.  Used by the
// IDC_TEAM_LIST combobox
LRESULT CALLBACK cb_cntl_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			SetWindowPos(H, HWND_TOP, X-g_prevx, Y, cx, cy, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			//When T key is pressed - CTRL+SHIFT+T trims the team lists to max 23 players each
			if( W == 0x54 && (GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000) )
			{
				int ii=0;
				while(ii< gteams->team_max && gteams[gn_teamsel].players[ii]!=0)
				{
					if(ii>22) gteams[gn_teamsel].players[ii]=0;
					ii++;
				}
				gteams[gn_teamsel].b_changed = true;
				//SendMessage(ghw_main, WM_COMMAND, MAKEWPARAM(IDC_TEAM_LIST,CBN_SELCHANGE), 0);
				trim_team();
				return true;
			}
			else
				common_shortcuts(W);
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}


//Subclassed control procedure for a combobox control.  Used by the
// non-IDC_TEAM_LIST comboboxes
LRESULT CALLBACK cb2_cntl_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			SetWindowPos(H, HWND_TOP, X-g_prevx, Y, cx, cy, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			common_shortcuts(W);
			if( W == 0x21 || W == 0x22 ) //We don't want default behavior for PGUP and PGDN
				return true;
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}


//Subclassed control procedure
LRESULT CALLBACK scale_cntl_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy, offset=0;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			
			if(GetParent(H)==ghw_main)
				offset = g_prevx;
			SetWindowPos(H, HWND_TOPMOST, X-offset, Y, cx, cy, SWP_NOREDRAW|SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			common_shortcuts(W);
		}
		break;

		case WM_DESTROY:
		{
			delete (RECT*)dwRefData;
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}


//Subclassed control procedure
LRESULT CALLBACK scale_static_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy, offset=0;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			if(GetParent(H)==ghw_main)
				offset = g_prevx;
			SetWindowPos(H, HWND_NOTOPMOST, X-offset, Y, cx, cy, SWP_NOREDRAW|SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			//SetWindowPos(H, HWND_TOP, X, Y, cx, cy, SWP_NOACTIVATE);
			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			common_shortcuts(W);
		}
		break;

		case WM_DESTROY:
		{
			delete (RECT*)dwRefData;
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}


//Subclassed control procedure for the last control in the main dialog
// tab order.  I need this special proc to force the tab order to include
// the tab control itself - the tab has the WS_EX_CONTROLPARENT style so
// that its child controls will be appended to the main dialog tab order,
// but as a result the tab control itself is invisible to the tab order.
// This subproc overrides that behavior, forcing a TAB key press on the
// item to transfer focus to the tab control itself.
// The 'Cancel' button (IDB_CANCEL_BKUP) uses this proc
LRESULT CALLBACK onto_tab_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case WM_CHAR:
		{
			//To prevent 'ding' sounding when TAB key is pressed with 
			// this item selected, skip default handling of char 13 (TAB)
			if( W==9 ) return true;
			return DefSubclassProc(H, M, W, L);
		}

		case WM_KEYDOWN:
		{
			if( W==VK_TAB )
			{
				//When the TAB key is pressed, pass focus to the tab control
				//SendMessage(ghw_main, WM_NEXTDLGCTL, (WPARAM)ghw_tabcon, (LPARAM)TRUE);
				SetFocus(ghw_tabcon);

				return true;
			}
			else
			{
				common_shortcuts(W);

				if( W == 0x21 || W == 0x22 ) //We don't want default behavior for PGUP and PGDN
					return true;
			}
			break;
		}

		case WM_GETDLGCODE:
		{
			//Request that this control handles the WM_KEYDOWN and the
			// WM_CHAR messages for the TAB key itself
			if( L && ((MSG *)L)->message == WM_KEYDOWN &&
				((MSG *)L)->wParam == VK_TAB )
				return DLGC_WANTMESSAGE;
			else if( L && ((MSG *)L)->message == WM_CHAR &&
				((MSG *)L)->wParam == 9 )
				return DLGC_WANTMESSAGE;

			break;
		}

		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			SetWindowPos(H, HWND_TOPMOST, X-g_prevx, Y, cx, cy, SWP_NOREDRAW|SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_DESTROY:
		{
			delete (RECT*)dwRefData;
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}

//Subclassed control procedure for the tab control to pass focus to the
// first item of the currently displayed tab page when TAB is pressed,
// resuming the regular tabbing order.
LRESULT CALLBACK from_tab_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case WM_KEYDOWN:
		{
			if( W==VK_TAB )
			{
				HWND h_tab_to;
				int i_tab = TabCtrl_GetCurSel(H);
				
				if( i_tab==0 ) h_tab_to = GetDlgItem(ghw_tab1,IDS_PLAY_CF);
				else if(i_tab==1) h_tab_to = GetDlgItem(ghw_tab2,IDB_EDIT_FACE);
				else h_tab_to = GetDlgItem(ghw_tab3,IDT_TCOL_R1);

				//SendMessage(ghw_main, WM_NEXTDLGCTL, (WPARAM)h_tab_to, (LPARAM)TRUE);
				SetFocus(h_tab_to);
				return true;
			}
			else 
				common_shortcuts(W);

			break;
		}

		case WM_GETDLGCODE:
		{
			//Request that this control handles the WM_KEYDOWN message
			// for the TAB key itself
			if( L && ((MSG *)L)->message == WM_KEYDOWN &&
				((MSG *)L)->wParam == VK_TAB )
				return DLGC_WANTMESSAGE;

			break;
		}

		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			SetWindowPos(H, HWND_TOPMOST, X-g_prevx, Y, cx, cy, SWP_NOREDRAW|SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);

			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_DESTROY:
		{
			delete (RECT*)dwRefData;
		}
		break;
	}
	return DefSubclassProc(H, M, W, L);
}

LRESULT CALLBACK tab_two_dlg_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			//float scale = *(float*)L;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy, offset = 0;

			//GetWindowRect(H, &winrect);
			//MapWindowPoints(HWND_DESKTOP, GetParent(H), (LPPOINT)&winrect, 2);
			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			if(GetParent(H)==ghw_main)
				offset = g_prevx;
			SetWindowPos(H, HWND_TOP, X-offset, Y, cx, cy, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			//pri->hdefer = DeferWindowPos(pri->hdefer, H, HWND_TOPMOST, X, Y, cx, cy, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
			
			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			common_shortcuts(W);
		}
		break;

		case WM_COMMAND:
		{
			switch(LOWORD(W))
			{
				case IDB_MOTI_RAND:
				{
					if(HIWORD(W)==BN_CLICKED)
					{
						int val;
						wchar_t buffer[4];

						val = rand() % 3 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_HUND, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 8 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_ARMD, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 3 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_HUNR, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 8 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_ARMR, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 6 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_CK, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 16 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_FK, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 4 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_PK, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 122 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_GC1, WM_SETTEXT, 0, (LPARAM)buffer);

						val = rand() % 122 + 1;
						_itow_s(val, buffer, 4, 10);
						SendDlgItemMessage(H, IDT_MOTI_GC2, WM_SETTEXT, 0, (LPARAM)buffer);
					}
				}
				break;
			}
		}
        break;
    }
    return DefSubclassProc(H, M, W, L);
}


LRESULT CALLBACK tab_three_dlg_proc(HWND H, UINT M, WPARAM W, LPARAM L,
					UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch(M)
	{
		case UM_SCALE:
		{
			RECT winrect = *(RECT*)dwRefData;
			resize_info *pri = (resize_info*)L;
			int X, Y, cx, cy, offset = 0;

			X = ceil(pri->scale*winrect.left);
			Y = ceil(pri->scale*winrect.top);
			cx = ceil(pri->scale*(winrect.right-winrect.left));
			cy = ceil(pri->scale*(winrect.bottom-winrect.top));
			if(GetParent(H)==ghw_main)
				offset = g_prevx;
			SetWindowPos(H, HWND_TOP, X-offset, Y, cx, cy, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
			
			SendMessage(H, WM_SETFONT, (WPARAM)ghFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_KEYDOWN:
		{
			common_shortcuts(W);
		}
		break;

		case WM_CTLCOLORBTN:
		{
			if(gplayers)
			{
				int red, green, blue;
				wchar_t buffer[5];
				if((HWND)L == GetDlgItem(H, IDB_TCOLOR1))
				{
					DeleteObject(gTeamColor1);

					//p_ind = gn_playind[gn_listsel];
					//t_ind = gplayers[p_ind].team_ind;
					//red = floor(4.05*gteams[t_ind].color1_red);
					//green = floor(4.05*gteams[t_ind].color1_green);
					//blue = floor(4.05*gteams[t_ind].color1_blue);
					SendDlgItemMessage(ghw_tab3, IDT_TCOL_R1, WM_GETTEXT, 4, (LPARAM)buffer);
					red = floor(4.05*_wtoi(buffer));

					SendDlgItemMessage(ghw_tab3, IDT_TCOL_G1, WM_GETTEXT, 4, (LPARAM)buffer);
					green = floor(4.05*_wtoi(buffer));

					SendDlgItemMessage(ghw_tab3, IDT_TCOL_B1, WM_GETTEXT, 4, (LPARAM)buffer);
					blue = floor(4.05*_wtoi(buffer));
					gTeamColor1 = CreateSolidBrush(RGB(red, green, blue));
					return (INT_PTR)gTeamColor1;
				}
				else if((HWND)L == GetDlgItem(H, IDB_TCOLOR2))
				{
					DeleteObject(gTeamColor2);

					SendDlgItemMessage(ghw_tab3, IDT_TCOL_R2, WM_GETTEXT, 4, (LPARAM)buffer);
					red = floor(4.05*_wtoi(buffer));

					SendDlgItemMessage(ghw_tab3, IDT_TCOL_G2, WM_GETTEXT, 4, (LPARAM)buffer);
					green = floor(4.05*_wtoi(buffer));

					SendDlgItemMessage(ghw_tab3, IDT_TCOL_B2, WM_GETTEXT, 4, (LPARAM)buffer);
					blue = floor(4.05*_wtoi(buffer));
					gTeamColor2 = CreateSolidBrush(RGB(red, green, blue));
					return (INT_PTR)gTeamColor2;
				}
			}
		}
        break;

		case WM_COMMAND:
		{
			switch(HIWORD(W))
			{
				case EN_CHANGE:
				{
					int test=0;
					switch(LOWORD(W))
					{
						case IDT_TCOL_R1:
						case IDT_TCOL_G1:
						case IDT_TCOL_B1:
						{
							InvalidateRect(GetDlgItem(H, IDB_TCOLOR1), NULL, TRUE);
						}
						break;

						case IDT_TCOL_R2:
						case IDT_TCOL_G2:
						case IDT_TCOL_B2:
						{
							InvalidateRect(GetDlgItem(H, IDB_TCOLOR2), NULL, TRUE);
						}
						break;
					}
				}
				break;

				case BN_CLICKED:
				{
					switch(LOWORD(W))
					{
						case IDB_TCOLOR1:
						{
							int red, green, blue;
							wchar_t buffer[5];
							COLORREF acrCustClr[16] = {RGB(0, 0, 0),
													    RGB(255, 0, 0),
														RGB(0, 255, 0),
														RGB(0, 0, 255),
														RGB(255, 255, 0),
														RGB(0, 255, 255),
														RGB(255, 255, 255),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0)};
							CHOOSECOLOR cc;
							ZeroMemory(&cc, sizeof(cc));

							if(gplayers)
							{
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_R1, WM_GETTEXT, 4, (LPARAM)buffer);
								red = floor(4.05*_wtoi(buffer));

								SendDlgItemMessage(ghw_tab3, IDT_TCOL_G1, WM_GETTEXT, 4, (LPARAM)buffer);
								green = floor(4.05*_wtoi(buffer));

								SendDlgItemMessage(ghw_tab3, IDT_TCOL_B1, WM_GETTEXT, 4, (LPARAM)buffer);
								blue = floor(4.05*_wtoi(buffer));

								cc.lStructSize = sizeof(cc);
								cc.hwndOwner = ghw_main; //H;
								cc.rgbResult = RGB(red, green, blue);
								cc.lpCustColors = acrCustClr;
								cc.Flags = CC_FULLOPEN | CC_RGBINIT;
								if (ChooseColor(&cc)==TRUE) 
								{
									red = GetRValue(cc.rgbResult); 
									green = GetGValue(cc.rgbResult); 
									blue = GetBValue(cc.rgbResult); 
								}

								_itow_s(ceil(red/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_R1, WM_SETTEXT, NULL, (LPARAM)buffer);
								_itow_s(ceil(green/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_G1, WM_SETTEXT, NULL, (LPARAM)buffer);
								_itow_s(ceil(blue/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_B1, WM_SETTEXT, NULL, (LPARAM)buffer);

								InvalidateRect(GetDlgItem(H, IDB_TCOLOR1), NULL, TRUE);
							}
						}
						break;

						case IDB_TCOLOR2:
						{
							int red, green, blue;
							wchar_t buffer[5];
							COLORREF acrCustClr[16] = {RGB(0, 0, 0),
													    RGB(255, 0, 0),
														RGB(0, 255, 0),
														RGB(0, 0, 255),
														RGB(255, 255, 0),
														RGB(0, 255, 255),
														RGB(255, 255, 255),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0),
														RGB(0, 0, 0)};
							CHOOSECOLOR cc;
							ZeroMemory(&cc, sizeof(cc));

							if(gplayers)
							{
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_R2, WM_GETTEXT, 4, (LPARAM)buffer);
								red = floor(4.05*_wtoi(buffer));

								SendDlgItemMessage(ghw_tab3, IDT_TCOL_G2, WM_GETTEXT, 4, (LPARAM)buffer);
								green = floor(4.05*_wtoi(buffer));

								SendDlgItemMessage(ghw_tab3, IDT_TCOL_B2, WM_GETTEXT, 4, (LPARAM)buffer);
								blue = floor(4.05*_wtoi(buffer));

								cc.lStructSize = sizeof(cc);
								cc.hwndOwner = ghw_main; //H;
								cc.rgbResult = RGB(red, green, blue);
								cc.lpCustColors = acrCustClr;
								cc.Flags = CC_FULLOPEN | CC_RGBINIT;
								if (ChooseColor(&cc)==TRUE) 
								{
									red = GetRValue(cc.rgbResult); 
									green = GetGValue(cc.rgbResult); 
									blue = GetBValue(cc.rgbResult); 
								}

								_itow_s(ceil(red/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_R2, WM_SETTEXT, NULL, (LPARAM)buffer);
								_itow_s(ceil(green/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_G2, WM_SETTEXT, NULL, (LPARAM)buffer);
								_itow_s(ceil(blue/4.05), buffer, 4, 10);
								SendDlgItemMessage(ghw_tab3, IDT_TCOL_B2, WM_SETTEXT, NULL, (LPARAM)buffer);

								InvalidateRect(GetDlgItem(H, IDB_TCOLOR2), NULL, TRUE);
							}
						}
						break;
					}
				}
				break;
			}
		}
		break;
    }
    return DefSubclassProc(H, M, W, L);
}


void make_pony_phys()
{
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HELE, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEWI, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_HEDE, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_SHWI, WM_SETTEXT, 0, (LPARAM)_T("-7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CHSI, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_WASI, WM_SETTEXT, 0, (LPARAM)_T("-7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_THSI, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_CASI, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDT_PHYS_LELE, WM_SETTEXT, 0, (LPARAM)_T("7"));
	SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)7, 0);
	SendMessage(ghw_tab2, WM_COMMAND, MAKEWPARAM(IDB_MOTI_RAND,BN_CLICKED), 0);
	Button_SetCheck(GetDlgItem(ghw_main, IDB_PLAY_EDIT),BST_CHECKED);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)1, 0);
}


void trim_team()
{
	int csel, num_on_team, ii, jj;

	csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
	gb_forceupdate = true;
	gn_forceupdate = gn_playind[gn_listsel];

	for(num_on_team=0;num_on_team< gteams->team_max;num_on_team++)
	{
		if(!gteams[csel].players[num_on_team]) break;
	}

	delete[] gn_playind;
	gn_playind = new int[num_on_team];

	SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_DELETEALLITEMS, 0, 0);
	LVITEM lvI;
	memset(&lvI,0,sizeof(lvI)); //Zero out struct members
	lvI.mask = LVIF_TEXT;
	jj=0;
	for(ii=0;ii<gnum_players;ii++)
	{
		if(gplayers[ii].id == gteams[csel].players[jj] && gplayers[ii].b_show)
		{
			gn_playind[jj] = ii;
			lvI.pszText = gplayers[ii].name;
			lvI.iItem = jj;
			SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_INSERTITEM, 0, (LPARAM)&lvI);

			jj++;
		}
		if(jj==num_on_team) break;
	}
	ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), 0, LVIS_SELECTED, LVIS_SELECTED);
	gn_listsel = 0;

	SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, (WPARAM)csel, 0);
}


void team_vis_clear()
{
	int iteam, ii, jj;

	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_FACE),BST_UNCHECKED);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_HAIR),BST_UNCHECKED);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_PHYS),BST_UNCHECKED);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_EDIT_STRP),BST_UNCHECKED);

	if(gplayers[gn_playind[gn_listsel]].team_ind >= 0)
	{
		iteam = gplayers[gn_playind[gn_listsel]].team_ind;
		for(ii=0;ii< gteams->team_max;ii++)
		{
			if( gteams[iteam].players[ii] && gteams[iteam].players[ii]!=gplayers[gn_playind[gn_listsel]].id )
			{
				for(jj=0;jj<gnum_players;jj++)
				{
					if( gteams[iteam].players[ii]==gplayers[jj].id )
					{
						if(gplayers[jj].b_edit_face) 
						{
							gplayers[jj].b_edit_face=false;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].b_edit_hair)
						{
							gplayers[jj].b_edit_hair=false;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].b_edit_phys)
						{
							gplayers[jj].b_edit_phys=false;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].b_edit_strip)
						{
							gplayers[jj].b_edit_strip=false;
							gplayers[jj].b_changed=true;
						}
						break;
					}
				}
			}
		}
	}
}

void team_created_set()
{
	int iteam, ii, jj;

	Button_SetCheck(GetDlgItem(ghw_main, IDB_PLAY_EDIT),BST_CHECKED);

	if(gplayers[gn_playind[gn_listsel]].team_ind >= 0)
	{
		iteam = gplayers[gn_playind[gn_listsel]].team_ind;
		for(ii=0;ii< gteams->team_max;ii++)
		{
			if( gteams[iteam].players[ii] && gteams[iteam].players[ii]!=gplayers[gn_playind[gn_listsel]].id )
			{
				for(jj=0;jj<gnum_players;jj++)
				{
					if( gteams[iteam].players[ii]==gplayers[jj].id )
					{
						if(!gplayers[jj].b_edit_player) 
						{
							gplayers[jj].b_edit_player=true;
							gplayers[jj].b_changed=true;
						}
						break;
					}
				}
			}
		}
	}
}


void team_fpc_on()
{
	int iteam, ii, jj;
	TCHAR fpcBoot[3], fpcGkGlove[3];
	int i_fpcBoot, i_fpcGkGlove;

	if(giPesVersion==16)
	{
		_tcscpy_s(fpcBoot, 3, _T("55"));
		_tcscpy_s(fpcGkGlove, 3, _T("11"));
		i_fpcBoot = 55;
		i_fpcGkGlove = 11;
	}
	else
	{
		_tcscpy_s(fpcBoot, 3, _T("38"));
		_tcscpy_s(fpcGkGlove, 3, _T("12"));
		i_fpcBoot = 38;
		i_fpcGkGlove = 12;
	}

	if(giPesVersion<18) SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)7, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)0, 0);
	if( SendDlgItemMessage(ghw_main, IDC_PLAY_RPOS, CB_GETCURSEL, 0, 0) )
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)2, 0);
	else
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)1, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)2, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)0, 0);
	SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)fpcBoot);
	SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)fpcGkGlove);
	Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_ANTA),BST_UNCHECKED);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_SETCURSEL, (WPARAM)0, 0);
	if(giPesVersion>=18) Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV),BST_CHECKED);

	if(gplayers[gn_playind[gn_listsel]].team_ind >= 0)
	{
		iteam = gplayers[gn_playind[gn_listsel]].team_ind;
		for(ii=0;ii< gteams->team_max;ii++)
		{
			if( gteams[iteam].players[ii] && gteams[iteam].players[ii]!=gplayers[gn_playind[gn_listsel]].id )
			{
				for(jj=0;jj<gnum_players;jj++)
				{
					if( gteams[iteam].players[ii]==gplayers[jj].id )
					{
						if(gplayers[jj].tucked) 
						{
							gplayers[jj].tucked=false;
							gplayers[jj].b_changed=true;
						}

						if(gplayers[jj].sleeve!=2 && gplayers[jj].reg_pos!=0 )
						{
							gplayers[jj].sleeve=2;
							gplayers[jj].b_changed=true;
						}
						else if(gplayers[jj].sleeve!=1 && gplayers[jj].reg_pos==0 )
						{
							gplayers[jj].sleeve=1;
							gplayers[jj].b_changed=true;
						}

						if(gplayers[jj].skin_col!=7 && giPesVersion<18)
						{
							gplayers[jj].skin_col=7;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].boot_id!=i_fpcBoot)
						{
							gplayers[jj].boot_id=i_fpcBoot;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].glove_id!=i_fpcGkGlove)
						{
							gplayers[jj].glove_id=i_fpcGkGlove;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].socks!=2)
						{
							gplayers[jj].socks=2;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].wrist_tape!=0)
						{
							gplayers[jj].wrist_tape=0;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].ankle_tape) 
						{
							gplayers[jj].ankle_tape=false;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].inners) 
						{
							gplayers[jj].inners=0;
							gplayers[jj].b_changed=true;
						}
						if(!gplayers[jj].gloves && giPesVersion>=18) 
						{
							gplayers[jj].gloves=true;
							gplayers[jj].b_changed=true;
						}
						break;
					}
				}
			}
		}
	}
}


void team_fpc_off()
{
	int iteam, ii, jj;
	TCHAR buffer[20];
	TCHAR fpcBoot[3], fpcGkGlove[3];
	int i_fpcBoot, i_fpcGkGlove;

	if(giPesVersion==16)
	{
		_tcscpy_s(fpcBoot, 3, _T("55"));
		_tcscpy_s(fpcGkGlove, 3, _T("11"));
		i_fpcBoot = 55;
		i_fpcGkGlove = 11;
	}
	else
	{
		_tcscpy_s(fpcBoot, 3, _T("38"));
		_tcscpy_s(fpcGkGlove, 3, _T("12"));
		i_fpcBoot = 38;
		i_fpcGkGlove = 12;
	}

	SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)1, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)0, 0);
	SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)1, 0);
	GetDlgItemText(ghw_tab2, IDT_STRP_BOID, buffer, 20);
	if( !_tcscmp(buffer,fpcBoot) )
		SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)_T("0"));
	GetDlgItemText(ghw_tab2, IDT_STRP_GLID, buffer, 20);
	if( !_tcscmp(buffer,fpcGkGlove) )
		SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)_T("0"));
	if(giPesVersion>=18) Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV),BST_UNCHECKED);

	if(gplayers[gn_playind[gn_listsel]].team_ind >= 0)
	{
		iteam = gplayers[gn_playind[gn_listsel]].team_ind;
		for(ii=0;ii< gteams->team_max;ii++)
		{
			if( gteams[iteam].players[ii] && gteams[iteam].players[ii]!=gplayers[gn_playind[gn_listsel]].id )
			{
				for(jj=0;jj<gnum_players;jj++)
				{
					if( gteams[iteam].players[ii]==gplayers[jj].id )
					{
						if(!gplayers[jj].tucked) 
						{
							gplayers[jj].tucked=true;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].sleeve==2)
						{
							gplayers[jj].sleeve=1;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].boot_id==i_fpcBoot)
						{
							gplayers[jj].boot_id=0;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].glove_id==i_fpcGkGlove)
						{
							gplayers[jj].glove_id=0;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].socks==2)
						{
							gplayers[jj].socks=0;
							gplayers[jj].b_changed=true;
						}
						if(gplayers[jj].gloves && giPesVersion>=18) 
						{
							gplayers[jj].gloves=false;
							gplayers[jj].b_changed=true;
						}
						break;
					}
				}
			}
		}
	}
}

void fpc_toggle()
{
	TCHAR buffer[20];
	TCHAR fpcBoot[3], fpcGkGlove[3];

	if(giPesVersion==16)
	{
		_tcscpy_s(fpcBoot, 3, _T("55"));
		_tcscpy_s(fpcGkGlove, 3, _T("11"));
	}
	else if(giPesVersion<19)
	{
		_tcscpy_s(fpcBoot, 3, _T("38"));
		_tcscpy_s(fpcGkGlove, 3, _T("12"));
	}

	GetDlgItemText(ghw_tab2, IDT_STRP_BOID, buffer, 20);
	//if( !_tcscmp(buffer, fpcBoot) ) //If it's 38, FPC is set
	if(SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_GETCURSEL, 0, 0) == 2) //If short socks, FPC is set
	{
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)1, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)0, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)1, 0);
		if(giPesVersion<19)
		{
			SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)_T("0"));
			GetDlgItemText(ghw_tab2, IDT_STRP_GLID, buffer, 20);
			if( !_tcscmp(buffer, fpcGkGlove) )
				SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)_T("0"));
		}
		if(giPesVersion==18) Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV),BST_UNCHECKED); 
	}
	else //Otherwise, set to FPC invis
	{
		if(giPesVersion<18) SendDlgItemMessage(ghw_tab2, IDC_PHYS_SKIN, CB_SETCURSEL, (WPARAM)7, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_WRTA, CB_SETCURSEL, (WPARAM)0, 0);
		if( SendDlgItemMessage(ghw_main, IDC_PLAY_RPOS, CB_GETCURSEL, 0, 0) )
			SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)2, 0);
		else
			SendDlgItemMessage(ghw_tab2, IDC_STRP_SLEE, CB_SETCURSEL, (WPARAM)1, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SOCK, CB_SETCURSEL, (WPARAM)2, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_TAIL, CB_SETCURSEL, (WPARAM)0, 0);
		Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_ANTA),BST_UNCHECKED);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_SLIN, CB_SETCURSEL, (WPARAM)0, 0);
		SendDlgItemMessage(ghw_tab2, IDC_STRP_UNDR, CB_SETCURSEL, (WPARAM)0, 0);
		if(giPesVersion<19)
		{
			SendDlgItemMessage(ghw_tab2, IDT_STRP_BOID, WM_SETTEXT, 0, (LPARAM)fpcBoot);
			SendDlgItemMessage(ghw_tab2, IDT_STRP_GLID, WM_SETTEXT, 0, (LPARAM)fpcGkGlove);
		}
		if(giPesVersion==18) Button_SetCheck(GetDlgItem(ghw_tab2, IDB_STRP_GLOV),BST_CHECKED); 
	}
}

void toggle_hid()
{
	int value;
	if (IsWindowVisible(ghw_tab1))
	{
		if (IsWindowVisible(GetDlgItem(ghw_tab1, IDT_STAR)))
			value = SW_HIDE;
		else
			value = SW_SHOW;
	}
	else if (IsWindowVisible(ghw_tab2))
	{
		if (IsWindowVisible(GetDlgItem(ghw_tab2, IDT_MOTI_DRIB)))
			value = SW_HIDE;
		else
			value = SW_SHOW;
	}
	else
		return;

	for(int ii=IDS_STAR; ii<=IDC_PLAY_ATT; ii++)
		ShowWindow(GetDlgItem(ghw_tab1, ii), value);

	ShowWindow(GetDlgItem(ghw_tab2, IDC_STATIC_T89), value);
	ShowWindow(GetDlgItem(ghw_tab2, IDT_MOTI_DRIB), value);
	ShowWindow(GetDlgItem(ghw_tab2, IDC_MOTI_DRIB), value);
	ShowWindow(GetDlgItem(ghw_tab2, IDT_PLAY_HAND), value);
	ShowWindow(GetDlgItem(ghw_tab2, IDC_PLAY_HAND), value);
}

void set_stats()
{
	if (!IsWindow(ghw_stat)) //If dialog isn't already open
	{ 
		ghw_stat = CreateDialog(ghinst, MAKEINTRESOURCE(IDD_STATS), ghw_main, statDlgProc); //Create the unit converter modeless dialog box
		ShowWindow(ghw_stat, SW_SHOW); //Display it
	}
}

void bump_stats()
{
	if (!IsWindow(ghw_bump)) //If dialog isn't already open
	{ 
		ghw_bump = CreateDialog(ghinst, MAKEINTRESOURCE(IDD_STAT_BUMP), ghw_main, bumpDlgProc); //Create the unit converter modeless dialog box
		ShowWindow(ghw_bump, SW_SHOW); //Display it
	}
}

BOOL CALLBACK scale_children(HWND hwnd, LPARAM lParam)
{
	SendMessage(hwnd, UM_SCALE, NULL, lParam);
	return TRUE;
}

BOOL CALLBACK draw_children(HWND hwnd, LPARAM lParam)
{
	InvalidateRect(hwnd,NULL,true);
	return TRUE;
}

void setup_control(HWND hw_new, HFONT hfont, SUBCLASSPROC cntl_proc)
{
	RECT* chd_rect;

	SendMessage(hw_new, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
	chd_rect = new RECT;
	GetWindowRect(hw_new, chd_rect);
	MapWindowPoints(HWND_DESKTOP, GetParent(hw_new), (LPPOINT)chd_rect, 2);
	SetWindowSubclass(hw_new, cntl_proc, 0, (DWORD_PTR)chd_rect);
}


void setup_combo(HWND hw_new, HFONT hfont, SUBCLASSPROC cntl_proc)
{
	RECT* chd_rect;

	SendMessage(hw_new, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
	chd_rect = new RECT;
	SendMessage(hw_new, CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)chd_rect);
	MapWindowPoints(HWND_DESKTOP, GetParent(hw_new), (LPPOINT)chd_rect, 2);
	SetWindowSubclass(hw_new, cntl_proc, 0, (DWORD_PTR)chd_rect);
}


void SD_OnHVScroll(HWND hwnd, int bar, UINT code)
{
    const int scrollPos = SD_GetScrollPos(hwnd, bar, code);

    if(scrollPos == -1)
        return;

    SetScrollPos(hwnd, bar, scrollPos, TRUE);
    SD_ScrollClient(hwnd, bar, scrollPos);
}

void SD_ScrollClient(HWND hwnd, int bar, int pos)
{
    static int s_prevx = 1;
    static int s_prevy = 1;

    int cx = 0;
    int cy = 0;

    int& delta = cx;
    int& prev = s_prevx;

    delta = prev - pos;
    prev = pos;

	g_prevx = s_prevx;

	if(cx)
    {
        ScrollWindow(ghw_main, cx, cy, NULL, NULL);
		RECT rcClient;
		GetClientRect(ghw_main, &rcClient);
		SetWindowPos(hwnd,0,0,rcClient.bottom-18,rcClient.right,18,SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOZORDER);
    }
}

int SD_GetScrollPos(HWND hwnd, int bar, UINT code)
{
    SCROLLINFO si = {};
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
    GetScrollInfo(hwnd, bar, &si);

    const int minPos = si.nMin;
    const int maxPos = si.nMax - (si.nPage - 1);

    int result = -1;

    switch(code)
    {
    case SB_LINEUP /*SB_LINELEFT*/:
        result = max(si.nPos - 1, minPos);
        break;

    case SB_LINEDOWN /*SB_LINERIGHT*/:
        result = min(si.nPos + 1, maxPos);
        break;

    case SB_PAGEUP /*SB_PAGELEFT*/:
        result = max(si.nPos - (int)si.nPage, minPos);
        break;

    case SB_PAGEDOWN /*SB_PAGERIGHT*/:
        result = min(si.nPos + (int)si.nPage, maxPos);
        break;

    case SB_THUMBPOSITION:
        // do nothing
        break;

    case SB_THUMBTRACK:
        result = si.nTrackPos;
        break;

    case SB_TOP /*SB_LEFT*/:
        result = minPos;
        break;

    case SB_BOTTOM /*SB_RIGHT*/:
        result = maxPos;
        break;

    case SB_ENDSCROLL:
        // do nothing
        break;
    }

    return result;
}


void common_shortcuts(WPARAM W)
{
	//When ctrl+shft+P key is pressed
	if( W == 0x50 && (GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000) )
	{
		make_pony_phys();
	}
	//When ctrl+shft+H key is pressed
	else if( W == 0x48 && (GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000) )
	{
		toggle_hid();
	}
	//ctrl+I for toggle FPC invis
	else if( W == 0x49 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		fpc_toggle();
	}
	//ctrl+O for Open dialog
	else if( W == 0x4F && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_EN), 0);
	}
	//ctrl+6 for Open 16 dialog
	else if( W == 0x36 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_16_EN), 0);
	}
	//ctrl+7 for Open 17 dialog
	else if( W == 0x37 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_17_EN), 0);
	}
	//ctrl+8 for Open 18 dialog
	else if( W == 0x38 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_18_EN), 0);
	}
	//ctrl+9 for Open 19 dialog
	else if( W == 0x39 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_19_EN), 0);
	}
	//ctrl+0 for Open 20 dialog
	else if( W == 0x30 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_20_EN), 0);
	}
	//ctrl+1 for Open 21 dialog
	else if( W == 0x31 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_OPEN_21_EN), 0);
	}
	//ctrl+S for Save dialog
	else if( W == 0x53 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(ID_FILE_SAVE_EN), 0);
	}
	//ctrl+F for clear visual flags
	else if( W == 0x46 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		if(gplayers)
			team_vis_clear();
	}
	//Page Up to scroll up player list
	else if( W == 0x21 )
	{
		if(gplayers)
			scroll_player_up();
	}
	//Page Down arrow to scroll down player list
	else if( W == 0x22 )
	{
		if(gplayers)
			scroll_player_down();
	}
	//ctrl+B for bump player stats dialog
	else if( W == 0x42 && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		SendMessage(ghw_main, WM_COMMAND, LOWORD(IDM_PLAY_BUMP), 0);
	}
}

BOOL CALLBACK statDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) //Set all player stats dialog box
{
	switch (Message) 
	{ 
		case WM_INITDIALOG: //when box first opens
		{
			TCHAR buffer[3];

			SendDlgItemMessage(hwnd, IDC_STAT, UDM_SETRANGE, 0, MAKELPARAM(99, 40));

			GetDlgItemText(ghw_tab1, IDT_ABIL_ATKP, buffer, 3);
			SetDlgItemText(hwnd, IDT_STAT, buffer);

			//SetFocus(GetDlgItem(hwnd, IDT_STAT));

			SetClassLongPtr(hwnd, GCLP_HICONSM, (LONG)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_4CC), IMAGE_ICON, 16, 16, 0)); //set 4cc logo as dialog box icon
		}
		break; 
		
		case WM_COMMAND:	
			switch(LOWORD(wParam))
            {
				case IDC_OK: //If the "OK" button is pressed,
				{
					int ii;
					TCHAR buffer[3];

					GetDlgItemText(hwnd, IDT_STAT, buffer, 3);
					for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
					{
						SetDlgItemText(ghw_tab1, ii, buffer);
					}

					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				break;

				case IDC_CANCEL: //If the "OK" button is pressed,
				{
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				break;
			}
		break;

		case WM_CLOSE:
			DestroyIcon((HICON)GetClassLongPtr(hwnd, GCLP_HICONSM)); //Destroy the allocated icon to free the GDI resource
			SetClassLongPtr(hwnd, GCLP_HICONSM, NULL); //Set icon pointer to NULL
			ghw_stat = NULL;
			DestroyWindow(hwnd);
		default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK bumpDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) //Bump player stats dialog box
{
	switch(Message)
	{ 
		case WM_INITDIALOG: //when box first opens
		{
			TCHAR buffer[3];

			SendDlgItemMessage(hwnd, IDC_STAT, UDM_SETRANGE, 0, MAKELPARAM(10, -10));

			//GetDlgItemText(ghw_tab1, IDT_ABIL_ATKP, buffer, 3);
			_itow_s(g_bumpAmount, buffer, 3, 10);
			SetDlgItemText(hwnd, IDT_STAT, buffer);

			SetClassLongPtr(hwnd, GCLP_HICONSM, (LONG)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_4CC), IMAGE_ICON, 16, 16, 0)); //set 4cc logo as dialog box icon
		}
		break; 
		
		case WM_COMMAND:	
			switch(LOWORD(wParam))
            {
				case IDC_OK: //If the "OK" button is pressed,
				{
					int ii, change, cur_stat, new_stat;
					TCHAR buffer[3];

					GetDlgItemText(hwnd, IDT_STAT, buffer, 3);
					change = _wtoi(buffer);
					for(ii=IDT_ABIL_ATKP;ii<gi_lastAbility;ii+=2)
					{
						GetDlgItemText(ghw_tab1, ii, buffer, 3);
						cur_stat = _wtoi(buffer);
						new_stat = cur_stat + change;
						if(new_stat>99) new_stat = 99;
						if(new_stat<40) new_stat = 40;
						_itow_s(new_stat, buffer, 3, 10);
						SetDlgItemText(ghw_tab1, ii, buffer);
					}
					g_bumpAmount = change; 
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				break;

				case IDC_CANCEL: //If the "Cancel" button is pressed,
				{
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				break;
			}
		break;

		case WM_CLOSE:
			DestroyIcon((HICON)GetClassLongPtr(hwnd, GCLP_HICONSM)); //Destroy the allocated icon to free the GDI resource
			SetClassLongPtr(hwnd, GCLP_HICONSM, NULL); //Set icon pointer to NULL
			ghw_stat = NULL;
			DestroyWindow(hwnd);
			SetFocus(GetDlgItem(ghw_main,IDC_NAME_LIST));
		default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK importDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) //import player stats dialog box
{
	switch(Message)
	{ 
		case WM_INITDIALOG: //when box first opens
		{
			if(gb_importStats) Button_SetCheck(GetDlgItem(hwnd, IDB_IMPO_STAT), BST_CHECKED);
			else Button_SetCheck(GetDlgItem(hwnd, IDB_IMPO_STAT), BST_UNCHECKED);

			if(gb_importAes) Button_SetCheck(GetDlgItem(hwnd, IDB_IMPO_AEST), BST_CHECKED);
			else Button_SetCheck(GetDlgItem(hwnd, IDB_IMPO_AEST), BST_UNCHECKED);

			//SetClassLongPtr(hwnd, GCLP_HICONSM, (LONG)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_4CC), IMAGE_ICON, 16, 16, 0)); //set 4cc logo as dialog box icon
		}
		break; 
		
		case WM_COMMAND:	
			switch(LOWORD(wParam))
            {
				case IDC_OK: //If the "OK" button is pressed,
				{
					gb_importStats = IsDlgButtonChecked(hwnd, IDB_IMPO_STAT);
					gb_importAes = IsDlgButtonChecked(hwnd, IDB_IMPO_AEST);
					EndDialog(hwnd, IDC_OK);
				}
				break;

				case IDC_CANCEL: //If the "Cancel" button is pressed, FIX THIS to properly seend cancelled message to parent window
				{
					EndDialog(hwnd, IDC_CANCEL);
				}
				break;
			}
		break;

		default:
            return FALSE;
    }
    return TRUE;
}


void roster_data_output()
{
//	char* buffer;
//	wchar_t short_name[0x4];

	TCHAR* poss[] = {_T("GK"),_T("CB"),_T("LB"),_T("RB"),_T("DMF"),_T("CMF"),_T("LMF"),_T("RMF"),_T("AMF"),
						_T("LWF"),_T("RWF"),_T("SS"),_T("CF")};

	FILE *outStream = _tfopen(_T("EDIT.tsv"), _T("w, ccs=UTF-8")); //ccs=UNICODE

	if(!outStream)
	{
		//buffer = strerror(errno);
		return;
	}
	
	for(int iteam=0;iteam<gnum_teams;iteam++)
	{
		_ftprintf(outStream, _T("%s\n"), gteams[iteam].name);
//for Ved:		mbstowcs(short_name,gteams[iteam].short_name,4); 
		for(int ii=0;ii< gteams->team_max;ii++)
		{
			if( gteams[iteam].players[ii] )
			{
				for(int jj=0;jj<gnum_players;jj++)
				{
					if( gteams[iteam].players[ii]==gplayers[jj].id )
					{
						TCHAR buffer[12];
						
						//Label medal players
						if(gplayers[jj].finish == 99) _tcscpy(buffer,_T("GOLD "));
						else if(gplayers[jj].finish > 85) _tcscpy(buffer,_T("SILVER "));
						else _tcscpy(buffer,_T(""));
						//Label team captain
						if(gteams[iteam].captain_ind == ii) _tcscat(buffer, _T("(C)"));

						_ftprintf(outStream, _T("%d\t%s\t%s\t%s\n"), gteams[iteam].numbers[ii], gplayers[jj].name,
									poss[gplayers[jj].reg_pos], buffer);
//for Ved:					_ftprintf(outStream, _T("%s,%s,%s%d\n"), poss[gplayers[jj].reg_pos], gplayers[jj].name,
//									short_name,ii+1);
						break;
					}
				}
			}
		}
		_fputts(_T("\n"),outStream);
	}
	fclose(outStream);
}


void fix_database()
{
	int ii;

	for(ii=0;ii<gnum_players;ii++)
	{
		if(!gplayers[ii].b_base_copy && gplayers[ii].copy_id != gplayers[ii].id)
		{
			gplayers[ii].copy_id = gplayers[ii].id;
			gplayers[ii].b_changed=true;
		}
		else if(gplayers[ii].b_base_copy && 
			    (gplayers[ii].copy_id == gplayers[ii].id || gplayers[ii].copy_id == 0))
		{
			gplayers[ii].copy_id = gplayers[ii].id;
			gplayers[ii].b_base_copy=false;
			gplayers[ii].b_changed=true;
		}

		if(gplayers[ii].b_edit_face) 
		{
			gplayers[ii].b_edit_face=false;
			gplayers[ii].b_changed=true;
		}

		if(gplayers[ii].b_edit_hair)
		{
			gplayers[ii].b_edit_hair=false;
			gplayers[ii].b_changed=true;
		}

		if(gplayers[ii].b_edit_phys)
		{
			gplayers[ii].b_edit_phys=false;
			gplayers[ii].b_changed=true;
		}

		if(gplayers[ii].b_edit_strip)
		{
			gplayers[ii].b_edit_strip=false;
			gplayers[ii].b_changed=true;
		}
	}
	show_player_info(gn_playind[gn_listsel]);
}


void scroll_player_up()
{
	if( gn_listsel != 0 )
	{
		ListView_EnsureVisible(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel-1, false);
		ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel-1, LVIS_SELECTED, LVIS_SELECTED);
	}	
}

void scroll_player_down()
{
	if( gn_listsel != ListView_GetItemCount(GetDlgItem(ghw_main, IDC_NAME_LIST))-1 )
	{
		ListView_EnsureVisible(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel+1, false);
		ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), gn_listsel+1, LVIS_SELECTED, LVIS_SELECTED);
	}	
}

void export_squad(HWND hwnd)
{
	USES_CONVERSION; //required for A2W, W2A, A2T, T2A macros
	int ii, jj, kk, num_on_team, csel;

	csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0) - 1;

	//First update the data structure to reflect any changes the user has made to the current player/team
	player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
	if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
	{
		if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
			pe_current.b_edit_player = true;
		gplayers[gn_playind[gn_listsel]] = pe_current;
		
		//Update displayed name
		LVITEM lvI;
		memset(&lvI,0,sizeof(lvI)); //Zero out struct members
		lvI.mask = LVIF_TEXT;
		lvI.pszText = pe_current.name;
		lvI.iItem = gn_listsel;
		SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);

		show_player_info(gn_playind[gn_listsel]);
	}

	//Check and update team tables
	team_entry te_current;
	if( get_form_team_info(gn_playind[gn_listsel], te_current) )
	{
		int ti = gplayers[gn_playind[gn_listsel]].team_ind;
		if( !(gteams[ti] == te_current) )
		{
			gteams[ti] = te_current;

			//Update combobox
			//int csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_DELETESTRING, gn_teamArrayIndToCb[ti]+1, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_INSERTSTRING, gn_teamArrayIndToCb[ti]+1, (LPARAM)te_current.name);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, csel+1, 0);								
		}
	}

	//Dialog to get out_file path
	OPENFILENAME ofn;
	TCHAR outPath[MAX_PATH] = _T("");
	char defName[10];
	strcpy(defName, gteams[gn_teamCbIndToArray[csel]].short_name);
	strcat(defName, ".4ccs");
	_tcscpy(outPath, A2T(defName));

	ii=0;
	const char *invalid_characters = "<>:\"/\\|?*";
	while((int)defName[ii]>0 && ii<10)
	{
		if((int)(defName[ii])<32 || strchr(invalid_characters, defName[ii]))
		{
			_tcscpy(outPath, _T("export.4ccs"));
			break;
		}
		ii++;
	}

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPTSTR)outPath;
	//ofn.lpstrFileTitle = (LPTSTR)outPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = _T("Save squad settings");

	if(GetSaveFileName(&ofn))
	{
		//strcpy(outPath, T2A(tOutPath));
		//Open file stream
		std::ofstream output_file(outPath, std::ios::binary);

		//Write out 4CCS version number to allow compatibility checks
		output_file.write(gc_ver4ccs, 3);

		//Write out PES version we're exporting from
		char cPesVersion[3];
		_itoa_s(giPesVersion, cPesVersion, 3, 10);
		output_file.write(cPesVersion, 2);

		//Find number of players on this team
		for(num_on_team=0;num_on_team< gteams->team_max;num_on_team++)
		{
			if(!gteams[gn_teamCbIndToArray[csel]].players[num_on_team]) break;
		}
		//Find the entry in the gplayer array matching each player ID on this team
		kk=0;
		for(ii=0;ii<gnum_players;ii++)
		{
			for(jj=0;jj<num_on_team;jj++)
			{
				if(gplayers[ii].id == gteams[gn_teamCbIndToArray[csel]].players[jj])
				{
					player_export pOut = gplayers[ii].PlayerExport();
					if(giPesVersion==16) pOut.phys_cont = pOut.body_ctrl;
					output_file.write((char*)&pOut, sizeof(pOut));
					kk++;
					break;
				}
			}
			//Stop when every player has been exported
			if(kk==num_on_team) break;
		}

		//Write out team shirt numbers
		output_file.write((char*)gteams[gn_teamCbIndToArray[csel]].numbers, sizeof(gteams[gn_teamCbIndToArray[csel]].numbers));

		//Close filestream
		output_file.close();
	}
}

void import_squad(HWND hwnd)
{
	USES_CONVERSION; //required for A2W, W2A, A2T, T2A macros
	int ii, jj, kk, num_on_team, csel;

	csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0) - 1;

	//Dialog to get out_file path
	OPENFILENAME ofn;
	TCHAR inPath[MAX_PATH] = _T("");

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPTSTR)inPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = _T("Load squad settings");

	if(GetOpenFileName(&ofn))
	{
		std::ifstream input_file;

		//Initial, fixed size version check: this doesn't actually work in general use because team sizes can vary (!= 23 players)
		//input_file.open(inPath, std::ifstream::ate | std::ios::binary);
		////int byte_pos = 
		//if( (int)(input_file.tellg()) < 7268)
		//{
		//	MessageBox(ghw_main, _T("Invalid 4CCS file!\r\nPlease save a 4CCS for this team using a PES19-compatible version of 4ccEditor."),
		//		_T("Version Error!"), MB_ICONERROR | MB_OK); //wrong file version
		//	input_file.close();
		//	return;
		//}
		//input_file.close();

		//Open file stream for reading
		//std::ifstream input_file(inPath, std::ios::binary);
		input_file.open(inPath, std::ios::binary);

		//Check for squad export version compatibility
		char c_ver[4];
		input_file.read(c_ver, 3);
		c_ver[3] = '\0';
		if(strcmp(c_ver, gc_ver4ccs)!=0)
		{
			TCHAR message[200];
			_stprintf(message, _T("Invalid 4CCS file!\r\nPlease save a 4CCS for this team using a %s-compatible version of 4ccEditor."), A2T(gc_ver4ccs));
			MessageBox(ghw_main, message, _T("Version Error!"), MB_ICONERROR | MB_OK); //wrong file version
			input_file.close();
			return;
		}

		if(DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DATA_IMPORT), ghw_main, importDlgProc) == IDC_OK) //If OK is clicked
		{ 
			//Get version this was imported from
			char c_pesVer[3];
			int pesVer;
			input_file.read(c_pesVer, 2);
			c_pesVer[2] = '\0';
			pesVer = atoi(c_pesVer);
			
			//Find number of players on this team
			for(num_on_team=0;num_on_team< gteams->team_max;num_on_team++)
			{
				if(!gteams[gn_teamCbIndToArray[csel]].players[num_on_team]) break;
			}
			//Find the entry in the gplayer array matching each player ID on this team
			kk=0;
			for(ii=0;ii<gnum_players;ii++)
			{
				for(jj=0;jj<num_on_team;jj++)
				{
					if(gplayers[ii].id == gteams[gn_teamCbIndToArray[csel]].players[jj])
					{
						player_export pIn;
						input_file.read((char *)&pIn, sizeof(pIn));
						gplayers[ii].PlayerImport(pIn, gb_importStats, gb_importAes);
						//No Custom skin in 18
						if(gb_importAes && giPesVersion>=18 && gplayers[ii].skin_col==7) gplayers[ii].skin_col=0;
						//Convert between 19 and 18- play style nunmbers if needed
						if(gb_importStats)
						{
							if(giPesVersion>=19 && pesVer<19)
							{
							  if(gplayers[ii].play_style==13) gplayers[ii].play_style=4;
							  else if(gplayers[ii].play_style==14) gplayers[ii].play_style=5;
							  else if(gplayers[ii].play_style==4) gplayers[ii].play_style=6;
							  else if(gplayers[ii].play_style==5) gplayers[ii].play_style=9;
							  else if(gplayers[ii].play_style==6) gplayers[ii].play_style=10;
							  else if(gplayers[ii].play_style==7) gplayers[ii].play_style=11;
							  else if(gplayers[ii].play_style==9) gplayers[ii].play_style=12;
							  else if(gplayers[ii].play_style==8) gplayers[ii].play_style=14;
							  else if(gplayers[ii].play_style==11) gplayers[ii].play_style=16;
							  else if(gplayers[ii].play_style==12) gplayers[ii].play_style=18;
							  else if(gplayers[ii].play_style==10) gplayers[ii].play_style=19;
							  else if(gplayers[ii].play_style==16) gplayers[ii].play_style=20;
							  else if(gplayers[ii].play_style==17) gplayers[ii].play_style=21;
							}

							if(giPesVersion>=20 && pesVer<20)
							{
								if(gplayers[ii].play_style==15) gplayers[ii].play_style=18;
								else if(gplayers[ii].play_style==16) gplayers[ii].play_style=15;
								else if(gplayers[ii].play_style==17) gplayers[ii].play_style=16;
								else if(gplayers[ii].play_style==18) gplayers[ii].play_style=17;
							}

							if(giPesVersion<20 && pesVer>=20)
							{
								if(gplayers[ii].play_style==18) gplayers[ii].play_style=15;
								else if(gplayers[ii].play_style==15) gplayers[ii].play_style=16;
								else if(gplayers[ii].play_style==16) gplayers[ii].play_style=17;
								else if(gplayers[ii].play_style==17) gplayers[ii].play_style=18;
							}

							if(giPesVersion<19 && pesVer>=19)
							{
							  if(gplayers[ii].play_style==4) gplayers[ii].play_style=13;
							  else if(gplayers[ii].play_style==5) gplayers[ii].play_style=14;
							  else if(gplayers[ii].play_style==6) gplayers[ii].play_style=4;
							  else if(gplayers[ii].play_style==9) gplayers[ii].play_style=5;
							  else if(gplayers[ii].play_style==10) gplayers[ii].play_style=6;
							  else if(gplayers[ii].play_style==11) gplayers[ii].play_style=7;
							  else if(gplayers[ii].play_style==12) gplayers[ii].play_style=9;
							  else if(gplayers[ii].play_style==14) gplayers[ii].play_style=8;
							  else if(gplayers[ii].play_style==16) gplayers[ii].play_style=11;
							  else if(gplayers[ii].play_style==18) gplayers[ii].play_style=12;
							  else if(gplayers[ii].play_style==19) gplayers[ii].play_style=10;
							  else if(gplayers[ii].play_style==20) gplayers[ii].play_style=16;
							  else if(gplayers[ii].play_style==21) gplayers[ii].play_style=17;
							  else if(gplayers[ii].play_style==7 || gplayers[ii].play_style==8 || gplayers[ii].play_style==13 || 
								  gplayers[ii].play_style==17) gplayers[ii].play_style=0;
							}
						}
						kk++;
						break;
					}
				}
				//Stop when every player has been imported
				if(kk==num_on_team) break;
			}

			//Read in team shirt numbers
			if(gb_importAes)
			{
				input_file.read((char*)gteams[gn_teamCbIndToArray[csel]].numbers, sizeof(gteams[gn_teamCbIndToArray[csel]].numbers));
				//Limit shirt numbers to single byte for versions earlier than 19
				if(giPesVersion < 19)
				{
					for(ii=0; ii<gteams[0].team_max; ii++)
					{
						if(gteams[gn_teamCbIndToArray[csel]].numbers[ii] > 231)
							gteams[gn_teamCbIndToArray[csel]].numbers[ii] = 231;
					}
				}
			}

			int num_lv_entries = ListView_GetItemCount(GetDlgItem(ghw_main, IDC_NAME_LIST));
			for(ii=0;ii<num_lv_entries;ii++)
			{
				ListView_SetItemText(GetDlgItem(ghw_main, IDC_NAME_LIST), ii, 0, gplayers[gn_playind[ii]].name)
				show_player_info(gn_playind[gn_listsel]);
			}
			ListView_EnsureVisible(GetDlgItem(ghw_main, IDC_NAME_LIST), 0, false);
			ListView_SetItemState(GetDlgItem(ghw_main, IDC_NAME_LIST), 0, LVIS_SELECTED, LVIS_SELECTED);
			//Fix this: update view to show info on first item in list, as it's been selected
		}

		//Close filestream
		input_file.close();
	}
}

BOOL CALLBACK aatf_sing_dlg_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_AATFOK:
                    ShowWindow(hwnd, SW_HIDE);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK aatf_mult_dlg_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
		case WM_INITDIALOG:
		{
			aatf_single(hwnd, giPesVersion, lParam, gplayers, gteams, gnum_players);
			SetFocus(GetDlgItem(hwnd,IDB_AATFOK));
		}
		break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDB_AATFOK:
                    EndDialog(hwnd, IDB_AATFOK);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK aatf_sel_dlg_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
		case WM_INITDIALOG:
		{
			for(int ii=0;ii<gnum_teams;ii++)
			{
				if(gteams[ii].b_show)
				{
					SendDlgItemMessage(hwnd, IDC_AATF_SEL, LB_ADDSTRING, 0, (LPARAM)gteams[ii].name);
				}
			}
		}
		break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_OK:
					{
						ShowWindow(hwnd, SW_HIDE);
						int selCount = SendDlgItemMessage(hwnd, IDC_AATF_SEL, LB_GETSELCOUNT, 0, 0);
						int *selIndices = new int[selCount];
						//int *teamIndices = new int[selCount];
						int teamInd;
						SendDlgItemMessage(hwnd, IDC_AATF_SEL, LB_GETSELITEMS, (WPARAM)selCount, (LPARAM)selIndices);
						for(int ii=0; ii<selCount; ii++)
						{
							teamInd = gn_teamCbIndToArray[selIndices[ii]];
							DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AATF), hwnd, aatf_mult_dlg_proc, teamInd);
						}

						delete [] selIndices;
						//delete [] teamIndices;
						EndDialog(hwnd, IDC_OK);
					}
                break;
				case IDC_CANCEL:
                    EndDialog(hwnd, IDC_CANCEL);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK aatf_comp_dlg_proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
		case WM_INITDIALOG:
		{
			TCHAR* cs_file_path = (TCHAR*)lParam;
			void *hc_descriptor = NULL;
			__try
			{
				save_comparator(hwnd, giPesVersion, gplayers, gnum_players, gteams, gnum_teams, cs_file_path, hc_descriptor);
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				TCHAR errBuffer[MAX_PATH] = _T("");
				_stprintf_s(errBuffer, MAX_PATH, _T("File decryption failed with code %d.\nThe EDIT file is from a different PES version and cannot be used for comparison."),
					GetExceptionCode());
				MessageBox(ghw_main, errBuffer, _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
				if(hc_descriptor) 
				{
					if(giPesVersion>=18)
						destroyFileDescriptorNew((FileDescriptorNew*)hc_descriptor);
					else
						destroyFileDescriptorOld((FileDescriptorOld*)hc_descriptor);
					hc_descriptor = NULL;
				}
				EndDialog(hwnd, IDB_AATFOK);
			}
		}
		break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_AATFOK:
				{
					EndDialog(hwnd, IDB_AATFOK);
				}
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}


void update_tables()
{
	//First update the data structure to reflect any changes the user has made to the current player/team
	player_entry pe_current = get_form_player_info(gn_playind[gn_listsel]);
	if( !(gplayers[gn_playind[gn_listsel]] == pe_current) )
	{
		if( wcscmp(gplayers[gn_playind[gn_listsel]].name, pe_current.name) )
			pe_current.b_edit_player = true;
		gplayers[gn_playind[gn_listsel]] = pe_current;
		
		//Update displayed name
		LVITEM lvI;
		memset(&lvI,0,sizeof(lvI)); //Zero out struct members
		lvI.mask = LVIF_TEXT;
		lvI.pszText = pe_current.name;
		lvI.iItem = gn_listsel;
		SendDlgItemMessage(ghw_main, IDC_NAME_LIST, LVM_SETITEM, 0, (LPARAM)&lvI);

		show_player_info(gn_playind[gn_listsel]);
	}

	//Check and update team tables
	team_entry te_current;
	if( get_form_team_info(gn_playind[gn_listsel], te_current) )
	{
		int ti = gplayers[gn_playind[gn_listsel]].team_ind;
		if( !(gteams[ti] == te_current) )
		{
			gteams[ti] = te_current;

			//Update combobox
			int csel = SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_DELETESTRING, gn_teamArrayIndToCb[ti]+1, 0);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_INSERTSTRING, gn_teamArrayIndToCb[ti]+1, (LPARAM)te_current.name);
			SendDlgItemMessage(ghw_main, IDC_TEAM_LIST, CB_SETCURSEL, csel, 0);								
		}
	}
}
