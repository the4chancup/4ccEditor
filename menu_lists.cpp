#include "editor.h"

TCHAR* gpc_playstyle20[22] = { _T("None"),
						  _T("Goal Poacher"),
						  _T("Dummy Runner"),
						  _T("Fox in the Box"),
						  _T("Target Man"),
						  _T("Creative Playmaker"),
						  _T("Prolific Winger"),
						  _T("Roaming Flank"),
						  _T("Crossing Specialist"),
						  _T("Classic No. 10"),
						  _T("Hole Player"),
						  _T("Box to Box"),
						  _T("The Destroyer"),
						  _T("Orchestrator"),
						  _T("Anchor Man"),
						  _T("Offensive Fullback"),
						  _T("Fullback Finisher"),
						  _T("Defensive Fullback"),
						  _T("Build Up"),
						  _T("Extra Frontman"),
						  _T("Offensive Goalkeeper"),
						  _T("Defensive Goalkeeper") };

TCHAR* gpc_playstyle19[22] = { _T("None"),
						  _T("Goal Poacher"),
						  _T("Dummy Runner"),
						  _T("Fox in the Box"),
						  _T("Target Man"),
						  _T("Creative Playmaker"),
						  _T("Prolific Winger"),
						  _T("Roaming Flank"),
						  _T("Crossing Specialist"),
						  _T("Classic No. 10"),
						  _T("Hole Player"),
						  _T("Box to Box"),
						  _T("The Destroyer"),
						  _T("Orchestrator"),
						  _T("Anchor Man"),
						  _T("Build Up"),
						  _T("Offensive Fullback"),
						  _T("Fullback Finisher"),
						  _T("Defensive Fullback"),
						  _T("Extra Frontman"),
						  _T("Offensive Goalkeeper"),
						  _T("Defensive Goalkeeper") };

TCHAR* gpc_playstyle18[18] = { _T("None"),
					  _T("Goal Poacher"),
					  _T("Dummy Runner"),
					  _T("Fox in the Box"),
					  _T("Prolific Winger"),
					  _T("Classic No. 10"),
					  _T("Hole Player"),
					  _T("Box to Box"),
					  _T("Anchor Man"),
					  _T("The Destroyer"),
					  _T("Extra Frontman"),
					  _T("Offensive Fullback"),
					  _T("Defensive Fullback"),
					  _T("Target Man"),
					  _T("Creative Playmaker"),
					  _T("Build Up"),
					  _T("Offensive Goalkeeper"),
					  _T("Defensive Goalkeeper") };

//Playstyle conversion arrays XtoY: playstyle number in version X goes to array[X] in version Y
//Used in import_squad() function in main.cpp
unsigned char n_playstyle16to1718[] = {	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	0,	16,	17 };
unsigned char n_playstyle1718to16[] = { 0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	17,	18 };
unsigned char n_playstyle16to19[] =	{   0,	1,	2,	3,	6,	9,	10,	11,	14,	12,	19,	16,	18,	4,	5,	15,	0,	20,	21 };
unsigned char n_playstyle19to16[] = {   0,	1,	2,	3,	13,	14,	4,	0,	0,	5,	6,	7,	9,	0,	8,	15,	11,	0,	12, 10, 17, 18 };
unsigned char n_playstyle16to2021[] = { 0,	1,	2,	3,	6,	9,	10,	11,	14,	12,	19,	15,	17,	4,	5,	18,	0,	20, 21 };
unsigned char n_playstyle2021to16[] = { 0,	1,	2,	3,	13, 14, 4,	0,	0,	5,	6,	7,	9,	0,	8,	11, 0,	12, 15, 10, 17, 18 };
unsigned char n_playstyle1718to19[] = { 0,	1,	2,	3,	6,	9,	10, 11, 14, 12, 19, 16, 18, 4,	5,	15, 20, 21 };
unsigned char n_playstyle19to1718[] = { 0,	1,	2,	3,	13, 14, 4,	0,	0,	5,	6,	7,	9,	0,	8,	15, 11,	0,	12, 10, 16, 17 };
unsigned char n_playstyle1718to2021[] = { 0, 1,	2,	3,	6,	9,	10, 11, 14, 12, 19, 15, 17, 4,	5,	18, 20, 21 };
unsigned char n_playstyle2021to1718[] = { 0, 1,	2,	3,	13, 14, 4,	0,	0,	5,	6,	7,	9,	0,	8,	11, 0,	12, 15, 10, 16, 17 };
unsigned char n_playstyle19to2021[] = { 0,	1,	2,	3,	4,	5,	6,	7,	8,	9, 10, 11, 12, 13, 14,	18, 15, 16, 17, 19, 20, 21 };
unsigned char n_playstyle2021to19[] = { 0,	1,	2,	3,	4,	5,	6,	7,	8,	9, 10, 11, 12, 13, 14,	16, 17, 18, 15, 19, 20, 21 };

TCHAR* gpc_positions[13] = { _T("Goalkeeper"),
							_T("Center Back"),
							_T("Left Back"),
							_T("Right Back"),
							_T("Defensive Midfielder"),
							_T("Center Midfielder"),
							_T("Left Midfielder"),
							_T("Right Midfielder"),
							_T("Attacking Midfielder"),
							_T("Left Wing Forward"),
							_T("Right Wing Forward"),
							_T("Second Striker"),
							_T("Centre Forward") };

TCHAR* gpc_pos_short[13] = { _T("GK"),_T("CB"),_T("LB"),_T("RB"),_T("DMF"),_T("CMF"),_T("LMF"),_T("RMF"),_T("AMF"),
					       _T("LWF"),_T("RWF"),_T("SS"),_T("CF") };

