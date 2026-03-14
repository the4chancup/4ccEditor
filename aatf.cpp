#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#include "aatf.h"
#ifndef UNICODE
  typedef std::string tstring; 
  typedef std::stringstream tstringstream;
#else
  typedef std::wstring tstring; 
  typedef std::wstringstream tstringstream;
#endif

//Struct to hold the necessary data to check if each player skill matches its target rating and, if not, print an error message
struct skillCheck
{
	unsigned char c_skillRate; //The player's rating in a skill
	tstring s_skillName; //The skill name
	int n_minPesVersion; //The PES version in which skill was introduced (0 if in all versions)
	int n_targetRate; //What the player's rating in this skill should be under the rules
};

//This array encodes the mapping between the registered position IDs (0-12) used in the player_export struct's reg_pos field
// and the corresponding index in the playable position array (player_export play_pos).  It is used to check that a player has 
// playable position set to A in the same position in which they are registered.
/* position	reg_pos	play_pos
	GK		0		12
	CB		1		9
	LB		2		10
	RB		3		11
	DMF		4		5
	CMF		5		6
	LMF		6		7
	RMF		7		8
	AMF		8		4
	LWF		9		2
	RWF		10		3
	SS		11		1
	CF		12		0 */
int regPosToPlayPosMap[13] = { 12, 9, 10, 11, 5, 6, 7, 8, 4, 2, 3, 1, 0 };

//============================
//AATF Settings
int manletCardBonus = 1; //Manlets get 1 extra card
int manletWeakFootUse = 4; //Manlets get 4/4 weak foot usage/accuracy
int manletWeakFootAcc = 4;
int manletPosBonus = 1; //Manlets get 1 extra double A position

int greenGiga = 0; //Green height bracket
int greenGiant = 5;
int greenTall = 6;
int greenMid = 6;
int greenManlet = 6;

int redGiga = 0; //Red height bracket
int redGiant = 0;
int redTall = 10;
int redMid = 7;
int redManlet = 6;

int heightGiga = 199; //Player heights in each category
int heightGiant = 194;
int heightTall = 185;
int heightTallGK = 189;
int heightMid = 180;
int heightManlet = 175;


void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players, bool useSuggestions)
{
	player_entry player;
	tstring msgOut;
	msgOut += _T("Team: ");
	msgOut += gteams[teamSel].name;
	msgOut += _T("\r\n");

	//============================

	bool hasCaptain = false;
	bool captainHasCaptaincy = false;
	int numGK = 0;
	//Count of player ratings
	int numReg = 0;
	int numSilver = 0;
	int numGold = 0;
	//Count of height brackets
	int numGiga = 0;
	int numGiant = 0;
	int numTall = 0;
	int numMid = 0;
	int numManlet = 0;
	bool usingRed = true;

	//Run through all players once to determine height system
	for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for (int jj = 0; jj < gnum_players; jj++)
		{
			if (gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}
		//If any player is in the green height brackets, team is on Green height system and we can halt
		if (player.height >= heightGiant)
		{
			usingRed = false;
			break;
		}
	}

	//Now check each player for errors
	int errorTot = 0;
	for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for (int jj = 0; jj < gnum_players; jj++)
		{
			if (gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}

		msgOut += _T("\x2022 Checking ");
		msgOut += player.name;
		msgOut += _T("\r\n");

		tstringstream errorMsg;

		int heightMod = 0;
		int statMod = 0;
		bool hasTrick = false;
		// Form, Injury Resist and Weak Foot
		int reqForm = 0;
		int reqInjResist = 0;
		int reqAPos = 0;
		int weakFootUse = 0;
		int weakFootAcc = 0;
		// Cards
		int reqSkill = 0;
		int reqTrick = 0;
		int reqCom = 0;
		// Individual Stat Comparison
		int targetRate = 0;
		int targetDrib = 0;
		int targetGk = 0;
		int targetFinish = 0;
		int targetLowPass = 0;
		int targetLoftPass = 0;
		int targetHeader = 0;
		int targetSwerve = 0;
		int targetCatching = 0;
		int targetClearing = 0;
		int targetReflex = 0;
		int targetBodyCtrl = 0;
		int targetPhysCont = 0;
		int targetKickPwr = 0;
		int targetExpPwr = 0;
		int targetBallCtrl = 0;
		int targetBallWin = 0;
		int targetJump = 0;
		int targetCover = 0;
		int targetPlcKick = 0;
		int targetStamina = 0;
		int targetSpeed = 0;
		int targetAtkProw = 0;
		int targetDefProw = 0;
		int targetTightPos = 0;
		int targetAggres = 0;
		// Rating Calculation
		int rating = player.drib;
		rating = max(player.gk, rating);
		rating = max(player.finish, rating);
		rating = max(player.lowpass, rating);
		rating = max(player.loftpass, rating);
		rating = max(player.header, rating);
		rating = max(player.swerve, rating);
		rating = max(player.catching, rating);
		if (pesVersion > 15)
		{
			rating = max(player.clearing, rating);
			rating = max(player.reflex, rating);
			rating = max(player.cover, rating);
		}
		rating = max(player.body_ctrl, rating);
		if (pesVersion > 16) rating = max(player.phys_cont, rating); //Not in 16
		rating = max(player.kick_pwr, rating);
		rating = max(player.exp_pwr, rating);
		rating = max(player.ball_ctrl, rating);
		rating = max(player.ball_win, rating);
		rating = max(player.jump, rating);
		rating = max(player.place_kick, rating);
		rating = max(player.stamina, rating);
		rating = max(player.speed, rating);
		if (pesVersion > 19) rating = max(player.aggres, rating);

		/*if(player.injury+1 > 3)
		{
			errorTot++;
			errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", cannot exceed 3; ");
		}*/

		//Check if this player is the captain
		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind]) hasCaptain = true;

		//Check if registered pos has playable set to A
		int requiredAPos = regPosToPlayPosMap[player.reg_pos];
		if (player.play_pos[requiredAPos] != 2)
		{
			errorTot++;
			errorMsg << _T("\tDoesn't have A in registered position;\r\n");
		}

		//Count A positions
		int countA = 0;
		int countB = 0;
		for (int jj = 0; jj < 13; jj++)
		{
			if (player.play_pos[jj] == 2)
				countA++;
			else if (player.play_pos[jj] == 1)
				countB++;
		}

		//No B positions allowed:
		if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("\tHas B position;\r\n");
		}

		if (player.reg_pos != 0 && player.play_pos[12] == 2) //Can't have GK as second A
		{
			errorTot++;
			errorMsg << _T("\tHas GK as second A position;\r\n");
		}

		if (player.age < 15 || player.age>50)
		{
			errorTot++;
			errorMsg << _T("\tAge out of range (15,50);\r\n");
		}

		if (player.weight<max(30, player.height - 129) || player.weight>(player.height - 81))
		{
			errorTot++;
			errorMsg << _T("\tWeight out of range (") << max(30, player.height - 129) << _T(",") << player.height - 81 << _T(");\r\n");
		}

		//Check playing style and registered position are in valid range per PES version
		if (player.reg_pos > 12)
		{
			errorTot++;
			errorMsg << _T("\tRegistered position out of range (0-12);\r\n");
		}

		if (pesVersion <= 16)
		{
			if (player.play_style > 18 || player.play_style == 16)
			{
				errorTot++;
				errorMsg << _T("\tPlaying style out of range (0-18, excluding 16);\r\n");
			}
		}
		else if (pesVersion > 16 && pesVersion < 19)
		{
			if (player.play_style > 17)
			{
				errorTot++;
				errorMsg << _T("\tPlaying style out of range (0-17);\r\n");
			}
		}
		else
		{
			if (player.play_style > 21)
			{
				errorTot++;
				errorMsg << _T("\tPlaying style out of range (0-21);\r\n");
			}
		}
		/* GOALKEEPER */
		if (player.reg_pos == 0) //Goalkeeper player, counts towards regular
		{
			numGK++;
			numReg++;
			using namespace goalkeeper;

			reqAPos = a_pos;
			reqForm = form;
			reqInjResist = injury_resistance;
			weakFootUse = weak_foot_usage;
			weakFootAcc = weak_foot_accuracy;

			reqSkill = skills;
			reqTrick = tricks;
			reqCom = coms;

			targetRate = base_stat;
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowPass = low_pass;
			targetLoftPass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBodyCtrl = balance;
			targetPhysCont = physical_contact;
			targetKickPwr = kicking_power;
			targetExpPwr = acceleration;
			targetBallCtrl = ball_control;
			targetBallWin = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlcKick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtkProw = offensive_awareness;
			targetDefProw = defensive_awareness;
			targetTightPos = tight_possession;
			targetAggres = aggression;

			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= height_nerf;
				statMod -= height_nerf;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += manlet_buff;
				statMod += manlet_buff;
			}
		}
		/* REGULAR */
		else if (rating < (silver::base_stat - silver::height_nerf)) //Regular player
		{
			numReg++;
			using namespace regular;

			reqAPos = a_pos;
			reqForm = form;
			reqInjResist = injury_resistance;
			weakFootUse = weak_foot_usage;
			weakFootAcc = weak_foot_accuracy;

			reqSkill = skills;
			reqTrick = tricks;
			reqCom = coms;

			targetRate = base_stat;
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowPass = low_pass;
			targetLoftPass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBodyCtrl = balance;
			targetPhysCont = physical_contact;
			targetKickPwr = kicking_power;
			targetExpPwr = acceleration;
			targetBallCtrl = ball_control;
			targetBallWin = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlcKick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtkProw = offensive_awareness;
			targetDefProw = defensive_awareness;
			targetTightPos = tight_possession;
			targetAggres = aggression;

			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= height_nerf;
				statMod -= height_nerf;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += manlet_buff;
				statMod += manlet_buff;
			}
		}
		/* SILVER */
		else if (rating < (gold::base_stat - gold::height_nerf)) //Silver player
		{
			numSilver++;
			using namespace silver;

			reqAPos = a_pos;
			reqForm = form;
			reqInjResist = injury_resistance;
			weakFootUse = weak_foot_usage;
			weakFootAcc = weak_foot_accuracy;

			reqSkill = skills;
			reqTrick = tricks;
			reqCom = coms;

			targetRate = base_stat;
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowPass = low_pass;
			targetLoftPass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBodyCtrl = balance;
			targetPhysCont = physical_contact;
			targetKickPwr = kicking_power;
			targetExpPwr = acceleration;
			targetBallCtrl = ball_control;
			targetBallWin = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlcKick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtkProw = offensive_awareness;
			targetDefProw = defensive_awareness;
			targetTightPos = tight_possession;
			targetAggres = aggression;

			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("\tMedals cannot play as GK;\r\n");
			}
			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= height_nerf;
				statMod -= height_nerf;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += manlet_buff;
				statMod += manlet_buff;
			}
		}
		/* GOLD */
		else if (rating == gold::base_stat || rating == (gold::base_stat - gold::height_nerf)) //Gold player
		{
			numGold++;
			using namespace gold;

			reqAPos = a_pos;
			reqForm = form;
			reqInjResist = injury_resistance;
			weakFootUse = weak_foot_usage;
			weakFootAcc = weak_foot_accuracy;

			reqSkill = skills;
			reqTrick = tricks;
			reqCom = coms;

			targetRate = base_stat;
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowPass = low_pass;
			targetLoftPass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBodyCtrl = balance;
			targetPhysCont = physical_contact;
			targetKickPwr = kicking_power;
			targetExpPwr = acceleration;
			targetBallCtrl = ball_control;
			targetBallWin = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlcKick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtkProw = offensive_awareness;
			targetDefProw = defensive_awareness;
			targetTightPos = tight_possession;
			targetAggres = aggression;

			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("\tMedals cannot play as GK;\r\n");
			}
			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= height_nerf;
				statMod -= height_nerf;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += manlet_buff;
				statMod += manlet_buff;
			}
		}
		else
		{
			errorTot++;
			errorMsg << _T("\tIllegal Ability scores;\r\n");
			//spit out whatever errors were already found, but target scores can't be set, so quit out of this player to avoid useless error outputs
			msgOut += errorMsg.str();
			continue;
		}

		//Count cards
		int numSkill = 0;
		int numTrick = 0;
		int numCom = 0;
		int cardCount;
		if (pesVersion > 19) cardCount = 41;
		else if (pesVersion == 19) cardCount = 39;
		else cardCount = 28;
		for (int jj = 0; jj < cardCount; jj++)
		{
			if (player.play_skill[jj])
			{
				//SPECIAL Winter/Spring 24: Malicia (21) is a free card
				if (jj == 21)
				{
					numSkill++;
					reqSkill++;
				}
				//Captain gets free captaincy card
				else if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
				{
					captainHasCaptaincy = true;
					numSkill++;
					reqSkill++;
				}
				//Trick cards may be free, count number
				else if ((jj < 6 || jj == 16 || jj == 28 || jj == 29 || jj == 30 || jj == 34) && numTrick < reqTrick)
				{
					hasTrick = true;
					numTrick++;
				}
				else numSkill++;
			}
		}

		for (int jj = 0; jj < 7; jj++)
		{
			if (player.com_style[jj])
			{
				if (numCom < reqCom) numCom++;
				else numSkill++;
			}
		}

		//Check player height
		if (((player.height - heightMod) <= heightManlet))
		{
			numManlet++;
			reqSkill += manletCardBonus; //Manlets get a bonus card
			reqAPos++; //Manlets get a bonus double A position
			weakFootUse = manletWeakFootUse; //Manlets get weak foot acc/use 4/4
			weakFootAcc = manletWeakFootAcc;
		}
		else if ((player.height - heightMod) <= heightMid)
		{
			numMid++;
		}
		else if ((player.height - heightMod) == heightTall)
			numTall++;
		else if ((player.height - heightMod) == heightTallGK && player.reg_pos == 0) //GK
			numTall++;
		else if ((player.height - heightMod) == heightGiant)
			numGiant++;
		else if ((player.height - heightMod) == heightGiga)
			numGiga++;
		else
		{
			errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
		}

		if (player.form + 1 != reqForm)
		{
			errorTot++;
			errorMsg << _T("\tForm is ") << player.form + 1 << _T(", should be ") << reqForm << _T(";\r\n");
		}

		//Check injury resistance
		if (player.injury + 1 > reqInjResist)
		{
			errorTot++;
			errorMsg << _T("\tInjury resist is ") << player.injury + 1 << _T(", should be ") << reqInjResist << _T(";\r\n");
		}

		//Check weak foot ratings
		if (player.weak_use + 1 > weakFootUse)
		{
			errorTot++;
			errorMsg << _T("\tWeak foot usage > ") << weakFootUse << _T(";\r\n");
		}
		if (player.weak_acc + 1 > weakFootAcc)
		{
			errorTot++;
			errorMsg << _T("\tWeak foot accuracy > ") << weakFootAcc << _T(";\r\n");
		}

		//If more than allowed A positions, 1 card less for each
		if (countA > reqAPos) reqSkill -= (countA - reqAPos);

		//Check player card count
		if (numSkill > reqSkill)
		{
			errorTot++;
			errorMsg << _T("\tHas ") << numSkill << _T(" skill cards, only allowed ") << reqSkill << _T(";\r\n");
		}

		//Check PES skill card limit of 10
		if (numSkill + numTrick > 10)
		{
			errorTot++;
			errorMsg << _T("\tHas ") << numSkill + numTrick << _T(" cards, PES limit is 10, please swap to COM cards or trade for additional A positions;\r\n");
		}

		if (useSuggestions)
		{
			if (numSkill < reqSkill && numSkill + numTrick < 10) errorMsg << _T("\tWARN: Has ") << numSkill << _T(" skill cards, allowed ") << reqSkill << _T(";\r\n");
			if (numTrick < reqTrick && numSkill + numTrick < 10) errorMsg << _T("\tWARN: Has ") << numTrick << _T(" trick cards, allowed ") << reqTrick << _T(";\r\n");
			if (numCom < reqCom) errorMsg << _T("\tWARN: Has ") << numCom << _T(" COM cards, allowed ") << reqCom << _T(";\r\n");
			if (countA < reqAPos) errorMsg << _T("\tWARN; Has ") << countA << _T(" A positions, allowed ") << reqAPos << _T(";\r\n");
			if (player.injury + 1 < reqInjResist) errorMsg << _T("\tWARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << reqInjResist << _T(";\r\n");
			if (player.weak_use + 1 < weakFootUse) errorMsg << _T("\tWARN: Has weak usage ") << player.weak_use + 1 << _T(", allowed ") << weakFootUse << _T(";\r\n");
			if (player.weak_acc + 1 < weakFootAcc) errorMsg << _T("\tWARN: Has weak accuracy ") << player.weak_acc + 1 << _T(", allowed ") << weakFootAcc << _T(";\r\n");
		}

		//Check individual skill ratings
		//								c_skillRate			s_skillName			n_minPesVersion	n_targetRate
		skillCheck skillChecks[25] = { {player.drib,		_T("Dribbling"),			0,		(targetDrib == 0) ? targetRate : (targetDrib + statMod)		},
										{player.gk,			_T("Goalkeeping"),			0,		(targetGk == 0) ? targetRate : (targetGk + statMod)		},
										{player.finish,		_T("Finishing"),			0,		(targetFinish == 0) ? targetRate : (targetFinish + statMod)	},
										{player.lowpass,	_T("Low Pass"),				0,		(targetLowPass == 0) ? targetRate : (targetLowPass + statMod)	},
										{player.loftpass,	_T("Lofted Pass"),			0,		(targetLoftPass == 0) ? targetRate : (targetLoftPass + statMod)	},
										{player.header,		_T("Header"),				0,		(targetHeader == 0) ? targetRate : (targetHeader + statMod)	},
										{player.swerve,		_T("Swerve"),				0,		(targetSwerve == 0) ? targetRate : (targetSwerve + statMod)	},
										{player.catching,	_T("Catching"),				0,		(targetCatching == 0) ? targetRate : (targetCatching + statMod)	},
										{player.clearing,	_T("Clearing"),				16,		(targetClearing == 0) ? targetRate : (targetClearing + statMod)	},
										{player.reflex,		_T("Reflexes"),				16,		(targetReflex == 0) ? targetRate : (targetReflex + statMod)	},
										{player.body_ctrl,	_T("Body Control"),			0,		(targetBodyCtrl == 0) ? targetRate : (targetBodyCtrl + statMod)	},
										{player.phys_cont,	_T("Physical Contact"),		17,		(targetPhysCont == 0) ? targetRate : (targetPhysCont + statMod)	},
										{player.kick_pwr,	_T("Kicking Power"),		0,		(targetKickPwr == 0) ? targetRate : (targetKickPwr + statMod)	},
										{player.exp_pwr,	_T("Explosive Power"),		0,		(targetExpPwr == 0) ? targetRate : (targetExpPwr + statMod)	},
										{player.ball_ctrl,	_T("Ball Control"),			0,		(targetBallCtrl == 0) ? targetRate : (targetBallCtrl + statMod)	},
										{player.ball_win,	_T("Ball Winning"),			0,		(targetBallWin == 0) ? targetRate : (targetBallWin + statMod)	},
										{player.jump,		_T("Jump"),					0,		(targetJump == 0) ? targetRate : (targetJump + statMod)		},
										{player.cover,		_T("Coverage"),				16,		(targetCover == 0) ? targetRate : (targetCover + statMod)	},
										{player.place_kick, _T("Place Kicking"),		0,		(targetPlcKick == 0) ? targetRate : (targetPlcKick + statMod)	},
										{player.stamina,	_T("Stamina"),				0,		(targetStamina == 0) ? targetRate : (targetStamina + statMod)	},
										{player.speed,		_T("Speed"),				0,		(targetSpeed == 0) ? targetRate : (targetSpeed + statMod)	},
										{player.atk,		_T("Attacking Prowess"),	0,		(targetAtkProw == 0) ? targetRate : (targetAtkProw + statMod)	},
										{player.def,		_T("Defensive Prowess"),	0,		(targetDefProw == 0) ? targetRate : (targetDefProw + statMod)	},
										{player.tight_pos,	_T("Tight Possession"),		20,		(targetTightPos == 0) ? targetRate : (targetTightPos + statMod)	},
										{player.aggres,		_T("Aggression"),			20,		(targetAggres == 0) ? targetRate : (targetAggres + statMod)	} };

		for (int ii = 0; ii < 25; ii++)
		{
			//atk and def can be lower than the target rate
			if (skillChecks[ii].s_skillName == _T("Attacking Prowess") || skillChecks[ii].s_skillName == _T("Defensive Prowess"))
			{
				if (skillChecks[ii].n_minPesVersion <= pesVersion && skillChecks[ii].c_skillRate > skillChecks[ii].n_targetRate)
				{
					errorTot++;
					errorMsg << _T("\t") << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be <= ") << skillChecks[ii].n_targetRate << _T(";\r\n");
				}
			}
			else if (skillChecks[ii].n_minPesVersion <= pesVersion &&
				skillChecks[ii].c_skillRate != skillChecks[ii].n_targetRate)
			{
				errorTot++;
				errorMsg << _T("\t") << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be ") << skillChecks[ii].n_targetRate << _T(";\r\n");
			}
		}

		if (errorMsg.rdbuf()->in_avail()) msgOut += errorMsg.str();
	}
	//Team level errors
	int diff;
	tstringstream errorMsg;

	if (!hasCaptain)
	{
		errorTot++;
		errorMsg << _T("\tTeam must have an assigned Captain;\r\n");
	}

	if (!captainHasCaptaincy && useSuggestions) errorMsg << _T("\tWARN: Captain does not have the free Captaincy card;\r\n");

	//Must have at least 1 GK
	if (numGK < 1)
	{
		errorTot++;
		errorMsg << _T("\tTeam must have a registered GK;\r\n");
	}

	//Check heights
	if (!usingRed) //Using Green height system
	{
		msgOut += _T("Using Green height system\r\n");
		if (diff = greenGiga - numGiga)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numGiga << _T("/") << greenGiga << _T(" ") << heightGiga << _T("cm players;\r\n");
		}
		if (diff = greenGiant - numGiant)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numGiant << _T("/") << greenGiant << _T(" ") << heightGiant << _T("cm players;\r\n");
		}
		if (diff = greenTall - numTall)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numTall << _T("/") << greenTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players;\r\n");
		}
		if (diff = greenMid - numMid)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numMid << _T("/") << greenMid << _T(" ") << heightMid << _T("cm players;\r\n");
		}
		if (diff = greenManlet - numManlet)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numManlet << _T("/") << greenManlet << _T(" ") << heightManlet << _T("cm players;\r\n");
		}
	}
	else //Using Red height system
	{
		msgOut += _T("Using Red height system\r\n");
		if (diff = numGiga)
		{
			errorTot += diff;
			errorMsg << _T("\tHas ") << numGiga << _T("/") << redGiga << _T(" ") << heightGiga << _T("cm players;\r\n");
		}
		if (diff = numGiant)
		{
			errorTot += diff;
			errorMsg << _T("\tHas ") << numGiant << _T("/") << redGiant << _T(" ") << heightGiant << _T("cm players;\r\n");
		}
		if (diff = redTall - numTall)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numTall << _T("/") << redTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players;\r\n");
		}
		if (diff = redMid - numMid)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numMid << _T("/") << redMid << _T(" ") << heightMid << _T("cm players;\r\n");
		}
		if (diff = redManlet - numManlet)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("\tHas ") << numManlet << _T("/") << redManlet << _T(" ") << heightManlet << _T("cm players;\r\n");
		}
	}
	if (errorMsg.rdbuf()->in_avail())
	{
		errorMsg << _T("\r\n");
		msgOut += errorMsg.str();
		errorMsg.clear();
		errorMsg.str(tstring());
	}

	//Check ability stats
	if (numReg != regular::count)
	{
		errorTot++;
		errorMsg << _T("\tNumber of Regular players is ") << numReg << _T(", should be ") << regular::count << _T(";\r\n");
	}
	if (numSilver != silver::count)
	{
		errorTot++;
		errorMsg << _T("\tNumber of Silver medals is ") << numSilver << _T(", should be ") << silver::count << _T(";\r\n");
	}
	if (numGold != gold::count)
	{
		errorTot++;
		errorMsg << _T("\tNumber of Gold medals is ") << numGold << _T(", should be ") << gold::count << _T(";\r\n");
	}
	if (errorMsg.rdbuf()->in_avail()) errorMsg << _T("\r\n");
	errorMsg << _T("\r\nErrors: ") << errorTot << _T("\r\n");
	msgOut += errorMsg.str();

	SetWindowText(GetDlgItem(hAatfbox, IDT_AATFOUT), msgOut.c_str());
	if(errorTot)
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Alright, get their clothes"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("GO TEAM EXPORT!"));
}
