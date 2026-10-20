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
int manletBonus = 5;
int bronzeManletBonus = 3;
int silverManletBonus = 2;
int goldManletBonus = 0;
int bronzeGiantPen = 0;
int silverGiantPen = 0;
int goldGiantPen = 0;

int goldRate = 99; //Player skill ratings
int silverRate = 92;
int bronzeRate = 86;
int regRate = 77;
int gkRate = 77;

int reqNumGold = 1; //Numbers of medals
int reqNumSilver = 2;
int reqNumBronze = 2;

int goldForm = 8; //possible range 1-8
int silverForm = 8;
int bronzeForm = 8;
int regForm = 4;

int goldIR = 3; //Injury resistence (possible range 1-3)
int silverIR = 3;
int bronzeIR = 3;
int regIR = 1;

int goldWeakFootUse = 4; //Gold medal weak foot usage limit
int silverWeakFootUse = 4;
int bronzeWeakFootUse = 4;
int regWeakFootUse = 2;

int goldWeakFootAcc = 4; //Gold medal weak foot accuracy limit
int silverWeakFootAcc = 4;
int bronzeWeakFootAcc = 4;
int regWeakFootAcc = 2;

int manletCardBonus = 1; //Manlets get 1 extra card
int manletWeakFootUse = 4; //Manlets get 4/4 weak foot usage/accuracy
int manletWeakFootAcc = 4;
int manletPosBonus = 1; //Manlets get 1 extra double A position

int gkSkillCards = 2; //Skill cards
int regSkillCards = 3;
int bronzeSkillCards = 4;
int silverSkillCards = 5;
int goldSkillCards = 6;

int gkTrickCards = 0; //Trick cards
int regTrickCards = 2;
int bronzeTrickCards = 2;
int silverTrickCards = 3;
int goldTrickCards = 3;

int regCOM = 0; //COM playing styles
int bronzeCOM = 1;
int silverCOM = 1;
int goldCOM = 2;

int greenGiga = 0; //Green height bracket
int greenGiant = 6;
int greenTall = 6;
int greenMid = 5;
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


void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players)
{
	player_entry player;
	tstring msgOut;
	msgOut+=_T("Team: ");
	msgOut+=gteams[teamSel].name;
	msgOut+=_T("\r\n");

	//============================

	bool hasCaptain = false;
	int numGK = 0;
	//Count of player ratings
	int numReg = 0;
	int numBronze = 0;
	int numSilver = 0;
	int numGold = 0;
	//Count of height brackets
	int numGiga = 0;
	int numGiant = 0;
	int numTall = 0;
	int numMid = 0;
	int numManlet = 0;
	bool usingRed = true;
	bool eCheck = false;

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
	for(int ii=0; ii<gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for(int jj=0; jj<gnum_players; jj++)
		{
			if(gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}

		msgOut+=_T("\x2022 Checking ");
		msgOut+=player.name;
		msgOut+=_T("\r\n");

		tstringstream errorMsg;

		int cardCount = 0;
        int cardMod = 0;
		int cardLimit = 0;
		int heightMod = 0;
		int weakFootUse = 0;
		int weakFootAcc = 0;
        bool hasTrick = false;
		int targetRate = 0, targetRate2 = 0, targetRate3 = 0;
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
		if(player.play_pos[requiredAPos] != 2)
		{
			errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
		
		//Count number of registered GKs
		if(player.reg_pos == 0) numGK++;

		//Count A positions
        int countA = 0;
		int countB = 0;
		int limitA = 1; //Allowable A positions 
        for(int jj=0;jj<13;jj++)
        {
            if(player.play_pos[jj] == 2)
				countA++;
			else if (player.play_pos[jj] == 1)
				countB++;
        }

        //If more than 1 A, 1 card less for each
        if(countA > 1)
        {
            if(player.play_pos[12] == 2) //Can't have GK as second A
			{
                errorTot++;
				errorMsg << _T("Has GK as second A position; ");
			}

            cardMod -= (countA - 1);
        }

		//Count cards
		int numTrick = 0;
		int numCom = 0;
		int comMod = 0;
		int numSkill;
		if(pesVersion==19) numSkill=39;
		else if(pesVersion>19) numSkill=41;
		else numSkill=28;
        for(int jj=0;jj<numSkill;jj++)
        {
            if(player.play_skill[jj])
            {
                cardCount++;
				//SPECIAL Winter/Spring 24: Malicia (21) is a free card
				if(jj==21) cardMod++;
                //Captain gets free captaincy card
				if(jj==25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
                    cardMod++;
                //Trick cards may be free, count number
                if(jj<6 || jj==16 || jj==28 || jj==29 || jj==30 || jj==34)
				{
                    hasTrick = true;
					numTrick++;
				}
            }
        }
		for(int jj=0;jj<7;jj++)
        {
            if(player.com_style[jj])
			{
				cardCount++;
				numCom++;
			}
		}

		if(player.age<15 || player.age>50)
		{
			errorTot++;
			errorMsg << _T("Age out of range (15,50); ");
		}

		if(player.weight<max(30,player.height-129) || player.weight>(player.height-81))
		{
			errorTot++;
			errorMsg << _T("Weight out of range (") << max(30,player.height-129) << _T(",") << player.height-81 << _T("); ");
		}

		//Check playing style and registered position are in valid range per PES version
		if (player.reg_pos > 12) 
		{
			errorTot++;
			errorMsg << _T("Registered position out of range (0-12); ");
		}

		if (pesVersion <= 16)
		{
			if (player.play_style > 18 || player.play_style == 16)
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-18, excluding 16); ");
			}
		}
		else if (pesVersion > 16 && pesVersion < 19)
		{
			if (player.play_style > 17) 
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-17); ");
			}
		}
		else
		{
			if (player.play_style > 21) 
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-21); ");
			}
		}

		//Check player height for bonus card
		if (((player.height - heightMod) <= heightManlet))
		{
			cardLimit += manletCardBonus; //Manlets get a bonus card
			if (countA > 1)
			{
				limitA += manletPosBonus; //Manlets get a bonus double A position
				cardMod++; //Offset the reduction in cards above by one if they have second A
			}
		}

		/* REGULAR */
		if(rating < bronzeRate-bronzeGiantPen) //Regular player
        {
            numReg++;
			targetRate = regRate;
			targetRate2 = regRate;
			targetRate3 = regRate;
			if(player.reg_pos == 0) //GK target rate is 77
            {
				targetRate = gkRate;
				targetRate2 = gkRate;
				targetRate3 = gkRate;
			}

			weakFootUse = regWeakFootUse;
			weakFootAcc = regWeakFootAcc;

			/*if(countA > 3)
			{
				errorTot++;
				errorMsg << _T("Regular player with > 3 A positions; ");
			}*/

			/*//SPECIAL Summer 24: Malicia (21) is now mandatory on all non-medal players
			if (!player.play_skill[21])
			{
				errorTot++;
				errorMsg << _T("Malicia card is mandatory for all non-medal players; ");
			}*/

            if(player.form+1 != regForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << regForm << _T("; ");
			}
			
            if(player.reg_pos == 0) //GK gets 2 cards
            {
				cardMod += min(gkTrickCards, numTrick); //free tricks
				cardLimit += gkSkillCards + cardMod;
                
				if(player.height > heightMid && player.height < heightTallGK)
				{
                    errorTot++;
					errorMsg << _T("GKs in this bracket must be ") << heightTallGK << _T("cm; ");
				}
				//SPECIAL Autumn 24 - GK and medals can'ts be in giant height bracket
				if (player.height >= heightGiant)
				{
					errorMsg << _T("GK heights cannot be ") << heightGiant << _T("cm; ");
				}
            }
            else
			{
				cardMod += min(regCOM, numCom); //free COM styles
				cardMod += min(regTrickCards, numTrick); //free tricks
				//cardMod += min(1, (countA - 1)); //1 free A-position
				cardLimit += regSkillCards + cardMod; //skill cards
				limitA += regSkillCards; //Can trade up to the number of non-free cards for double As
			}
            
			if(player.injury+1 > regIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << regIR << _T("; ");
			}

			if (player.height <= heightManlet && usingRed)
			{
				targetRate += manletBonus;
				targetRate2 += manletBonus;
				targetRate3 += manletBonus;
			}

			/*//SPECIAL Spring 24: non-medals that are registered in a blue position (CB, LB, RB) get +5 defensive prowess
			if (player.reg_pos >= 1 && player.reg_pos <= 3)
			{
				targetRate2 += 5;
			}*/
			
			/*//SPECIAL Spring 24: red heights non-medals registered in a red position (CF/SS/LWF/RWF) receive a +5 boost to all stats and can stack with the boost from being 175cm however these players cannot be given a 2nd A position
			if (player.reg_pos >= 9 && player.reg_pos <= 12 && usingRed)
			{
				targetRate += 5;
				targetRate2 += 5;
				//SPECIAL Summer 24: Red Position non-medal manlet players (CF/SS/LWF/RWF) have stamina stat = 77
				if (player.height <= heightManlet && usingRed)
					targetRate3 = regRate;
				else
					targetRate3 += 5;
				if (countA > 1)
				{
					errorTot++;
					errorMsg << _T("Illegal 2nd A position on red heights non-medal forward; ");
				}
			}*/

			/*//SPECIAL Summer 24: green heights non-medals registered in a red position (CF/SS/LWF/RWF) get an additional 5cm of height except for 199cm players
			if (player.reg_pos >= 9 && player.reg_pos <= 12 && !usingRed && player.height <= heightGiant)
			{
				heightMod = 5;
			}*/

			//SPECIAL Autumn 26: Red heights non-medal players in the 185cm bracket that have Center Back as Registered and their only A Playable Position can go up to 189cm
			if (usingRed && player.reg_pos == 1 && player.play_pos[n_regPosToPlayPos[1]] == 2 && countA == 1)
			{
				heightMod = 4;
			}

			if (eCheck)
			{
				if (player.reg_pos == 0)
				{
					if (numTrick < gkTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << gkTrickCards << _T("; ");
					if (numCom < regCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << regCOM << _T("; ");
				}
				else
				{
					if (numTrick < regTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << regTrickCards << _T("; ");
					if (numCom < regCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << regCOM << _T("; ");
				}
				if (player.injury + 1 < regIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << regIR << _T("; ");
			}
		}
		/* BRONZE */
		else if (rating < silverRate-silverGiantPen //Bronze player
			|| (usingRed && player.height == heightManlet && rating == bronzeRate + bronzeManletBonus)) //Autumn 26 special
		{
			numBronze++;
			targetRate = bronzeRate;
			targetRate2 = bronzeRate;
			targetRate3 = bronzeRate;

			weakFootUse = bronzeWeakFootUse;
			weakFootAcc = bronzeWeakFootAcc;

			if (numBronze > reqNumBronze)
			{
				errorTot++;
				errorMsg << _T("Too many Bronze medals; ");
			}
			if (player.form+1 != bronzeForm)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << bronzeForm << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= bronzeGiantPen;
				targetRate2 -= bronzeGiantPen;
				targetRate3 -= bronzeGiantPen;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += bronzeManletBonus;
				targetRate2 += bronzeManletBonus;
				targetRate3 += bronzeManletBonus;
			}

			//SPECIAL Autumn 26: Medals may trade a Free COM playing Style for a Double A position
			int freeCOM = bronzeCOM;
			if (countA > limitA || numCom > 0)
			{
				//Gets a free A (here) OR a free COM (below)
				if (countA > limitA)
				{
					comMod -= min(freeCOM, countA - limitA); //Reduce free COMs by 1 if the double A is being used
					cardMod += min(freeCOM, countA - limitA); //Replaces the reduction in non-free cards from double A calc, above
					limitA += min(freeCOM, countA - limitA); //Raise A limit by 1
				}
			}

			cardMod += min(bronzeTrickCards, numTrick); //free tricks
			cardMod += min(freeCOM + comMod, numCom); //free COM
			//cardMod += min(1, (countA - 1)); //1 free A-position
			cardLimit += bronzeSkillCards + cardMod; //skill cards
			limitA += bronzeSkillCards; //Can trade up to the number of non-free cards for double As

			if (player.injury+1 > bronzeIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << bronzeIR << _T("; ");
			}

			if (eCheck)
			{
				if (numTrick < bronzeTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << bronzeTrickCards << _T("; ");
				if (numCom < bronzeCOM + comMod) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << bronzeCOM + comMod << _T("; ");
				if (player.injury + 1 < bronzeIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << bronzeIR << _T("; ");
			}


			//SPECIAL FAG13: Medals can trade a card for 4/4 footedness
			/*if (player.weak_use + 1 > weakFootUse)
			{
				weakFootUse = 4;
				cardLimit--;
			}*/
		}
		/* SILVER */
        else if(rating < goldRate-goldGiantPen) //Silver player
        {
            numSilver++;
			targetRate = silverRate;
			targetRate2 = silverRate;
			targetRate3 = silverRate;

			weakFootUse = silverWeakFootUse;
			weakFootAcc = silverWeakFootAcc;

            if(numSilver > reqNumSilver)
			{
                errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
            if(player.form+1 != silverForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << silverForm << _T("; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height >= heightGiant) //HA get penalty
			{
				targetRate -= silverGiantPen;
				targetRate2 -= silverGiantPen;
				targetRate3 -= silverGiantPen;
			}
			else if(player.height <= heightManlet && usingRed)
            {
				targetRate += silverManletBonus;
				targetRate2 += silverManletBonus;
				targetRate3 += silverManletBonus;
			}

			//SPECIAL Autumn 26: Medals may trade a Free COM playing Style for a Double A position
			int freeCOM = silverCOM;
			if (countA > limitA || numCom > 0)
			{
				//Gets a free A (here) OR a free COM (below)
				if (countA > limitA)
				{
					comMod -= min(freeCOM, countA - limitA); //Reduce free COMs by 1 if the double A is being used
					cardMod += min(freeCOM, countA - limitA); //Replaces the reduction in non-free cards from double A calc, above
					limitA += min(freeCOM, countA - limitA); //Raise A limit by 1
				}
			}

            cardMod += min(silverTrickCards, numTrick); //free tricks
			cardMod += min(freeCOM + comMod, numCom); //free COM
			//cardMod += min(1, (countA - 1)); //free A-position
			cardLimit += silverSkillCards + cardMod; //skill cards
			limitA += silverSkillCards; //Can trade up to the number of non-free cards for double As


			if(player.injury+1 > silverIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << silverIR << _T("; ");
			}

			if (eCheck)
			{
				if (numTrick < silverTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << silverTrickCards << _T("; ");
				if (numCom < silverCOM + comMod) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << silverCOM + comMod << _T("; ");
				if (player.injury + 1 < silverIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << silverIR << _T("; ");
			}

			//SPECIAL FAG13: Medals can trade a card for 4/4 footedness
			/*if (player.weak_use + 1 > weakFootUse)
			{
				weakFootUse = 4;
				cardLimit--;
			}*/

			//SPECIAL Autumn 26: Greens can have silver 194cms, but with a -3 stat penalty
			if (!usingRed && player.height == heightGiant && rating > silverRate - 3)
			{
				errorTot++;
				errorMsg << _T("Illegal Ability scores: 194cm Silvers can only have ") << silverRate - 3 << _T(" ratings; ");
			}
        }
		/* GOLD */
        else //rating == 99 //Gold player
        {
            numGold++;
			targetRate = goldRate;
			targetRate2 = goldRate;
			targetRate3 = goldRate;

			weakFootUse = goldWeakFootUse;
			weakFootAcc = goldWeakFootAcc;

            if(numGold > reqNumGold)
			{
                errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
            if(player.form+1 != goldForm)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be ") << goldForm << _T("; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height >= heightGiant) //Medal HA penalty
			{
				targetRate -= goldGiantPen;
				targetRate2 -= goldGiantPen;
				targetRate3 -= goldGiantPen;
			}
			else if(player.height <= heightManlet && usingRed)
            {
				targetRate += goldManletBonus;
				targetRate2 += goldManletBonus;
				targetRate3 += goldManletBonus;
			}

			if (player.height > heightGiant)
			{
				errorMsg << _T("Gold heights cannot exceed ") << heightGiant << _T("cm; ");
			}

			//SPECIAL Autumn 26: Medals may trade a Free COM playing Style for a Double A position
			int freeCOM = goldCOM;
			if (countA > limitA || numCom > 0)
			{
				//Gets a free A (here) OR a free COM (below)
				if (countA > limitA)
				{
					comMod -= min(freeCOM, countA - limitA); //Reduce free COMs by 1 if the double A is being used
					cardMod += min(freeCOM, countA - limitA); //Replaces the reduction in non-free cards from double A calc, above
					limitA += min(freeCOM, countA - limitA); //Raise A limit by 1
				}
			}
			
            cardMod += min(goldTrickCards, numTrick); //free tricks
			cardMod += min(freeCOM + comMod, numCom); //free COMs
			cardLimit += goldSkillCards + cardMod; //skill cards
			limitA += goldSkillCards; //Can trade up to the number of non-free cards for double As
           
			if(player.injury+1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << goldIR << _T("; ");
			}

			if (eCheck)
			{
				if (cardCount < 10)
				{
					if (numTrick < goldTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << goldTrickCards << _T("; ");
					if (numCom < goldCOM + comMod) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << goldCOM + comMod << _T("; ");
				}
				if (player.injury + 1 < goldIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << goldIR << _T("; ");
			}

			//SPECIAL Spring 25 - GK and gold medals can't be in giant height bracket
			if (player.height >= heightGiant)
			{
				errorMsg << _T("Gold medal heights cannot be ") << heightGiant << _T("cm; ");
			}

			//SPECIAL FAG13: Medals can trade a card for 4/4 footedness
			/*if (player.weak_use + 1 > weakFootUse)
			{
				weakFootUse = 4;
				cardLimit--;
			}*/
		}

		//Check player height
		if (((player.height - heightMod) <= heightManlet))
		{
			numManlet++;
			weakFootUse = manletWeakFootUse; //Manlets get weak foot acc/use 4/4
			weakFootAcc = manletWeakFootAcc;
		}
		else if ((player.height) <= heightMid)
		{
			numMid++;
		}
		else if ((player.height - heightMod) == heightTall)
			numTall++;
		else if ((player.height) == heightTallGK && player.reg_pos == 0) //GK
			numTall++;
		else if ((player.height) == heightGiant)
			numGiant++;
		else if ((player.height) == heightGiga)
			numGiga++;
		else
		{
			errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
		}

		//Check weak foot ratings
		if (player.weak_use + 1 > weakFootUse)
		{
			errorTot++;
			errorMsg << _T("Weak foot usage > ") << weakFootUse << _T("; ");
		}
		if (player.weak_acc + 1 > weakFootAcc)
		{
			errorTot++;
			errorMsg << _T("Weak foot accuracy > ") << weakFootAcc << _T("; ");
		}

		//Check player card count
		if (cardCount > cardLimit)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
		}

		//Check PES skill card limit of 10
		if(cardCount-numCom > 10)
		{
            errorTot++;
			errorMsg << _T("Has ") << cardCount-numCom << _T(" skill cards, PES limit is 10, please swap to COM cards or trade for additional A positions; ");
		}

		//Check player double A count
		if (countA > limitA)
		{
			errorTot++;
			errorMsg << _T("Has ") << countA << _T(" double A positions, only allowed ") << limitA << _T("; ");
		}

		//No B positions allowed:
		if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("Has B position; ");
		}

		if (eCheck)
		{
			if (cardCount < min(cardLimit,10)) errorMsg << _T("WARN: Has ") << cardCount << _T(" cards, allowed ") << cardLimit << _T("; ");
			if (countA < limitA) errorMsg << _T("WARN: Has ") << countA << _T(" A positions, allowed ") << limitA << _T("; ");
			if (player.weak_use + 1 < weakFootUse) errorMsg << _T("WARN: Has weak usage ") << player.weak_use + 1 << _T(", allowed ") << weakFootUse << _T("; ");
			if (player.weak_acc + 1 < weakFootAcc) errorMsg << _T("WARN: Has weak accuracy ") << player.weak_acc + 1 << _T(", allowed ") << weakFootAcc << _T("; ");
		}

		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings
		//								c_skillRate			s_skillName			n_minPesVersion	n_targetRate
		skillCheck skillChecks[25] = {	{player.drib,		_T("Dribbling"),			0,		targetRate	},
										{player.gk,			_T("Goalkeeping"),			0,		targetRate	},
										{player.finish,		_T("Finishing"),			0,		targetRate	},
										{player.lowpass,	_T("Low Pass"),				0,		targetRate	},
										{player.loftpass,	_T("Lofted Pass"),			0,		targetRate	},
										{player.header,		_T("Header"),				0,		targetRate	},
										{player.swerve,		_T("Swerve"),				0,		targetRate	},
										{player.catching,	_T("Catching"),				0,		targetRate	},
										{player.clearing,	_T("Clearing"),				16,		targetRate	},
										{player.reflex,		_T("Reflexes"),				16,		targetRate	},
										{player.body_ctrl,	_T("Body Control"),			0,		targetRate	},
										{player.phys_cont,	_T("Physical Contact"),		17,		targetRate	},
										{player.kick_pwr,	_T("Kicking Power"),		0,		targetRate	},
										{player.exp_pwr,	_T("Explosive Power"),		0,		targetRate	},
										{player.ball_ctrl,	_T("Ball Control"),			0,		targetRate	},
										{player.ball_win,	_T("Ball Winning"),			0,		targetRate	},
										{player.jump,		_T("Jump"),					0,		targetRate	},
										{player.cover,		_T("Coverage"),				16,		targetRate	},
										{player.place_kick, _T("Place Kicking"),		0,		targetRate	},
										{player.stamina,	_T("Stamina"),				0,		targetRate3	},
										{player.speed,		_T("Speed"),				0,		targetRate	},
										{player.atk,		_T("Attacking Prowess"),	0,		targetRate	},
										{player.def,		_T("Defensive Prowess"),	0,		targetRate2	},
										{player.tight_pos,	_T("Tight Possession"),		20,		targetRate	},
										{player.aggres,		_T("Aggression"),			20,		targetRate	} };

		for (int ii = 0; ii < 25; ii++)
		{
			//atk and def can be lower than the target rate
			if (skillChecks[ii].s_skillName == _T("Attacking Prowess") || skillChecks[ii].s_skillName == _T("Defensive Prowess"))
			{
				if (skillChecks[ii].n_minPesVersion <= pesVersion && skillChecks[ii].c_skillRate > skillChecks[ii].n_targetRate)
				{
					errorTot++;
					errorMsg << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be <= ") << skillChecks[ii].n_targetRate << _T("; ");
				}
			}
			else if (skillChecks[ii].n_minPesVersion <= pesVersion && 
				     skillChecks[ii].c_skillRate != skillChecks[ii].n_targetRate)
			{
				errorTot++;
				errorMsg << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be ") << skillChecks[ii].n_targetRate << _T("; ");
			}
		}

		//The position of each player on a team's first preset in their deadline export are required to match one of the player's 'A' positions
		if (!aatf_check_player_in_A_position_in_P1(gteams[teamSel], player))
		{
			errorTot++;
			errorMsg << _T("Playing in non-A position on P1 [ignore if this isn't the deadline export]; ");
		}

		if(errorMsg.rdbuf()->in_avail())
		{
			errorMsg << _T("\r\n");
			msgOut+=_T("\t");
			msgOut+=errorMsg.str();
		}
	}
	//Team level errors
	int diff;
	tstringstream errorMsg;

	if (!hasCaptain)
	{
		errorTot++;
		errorMsg << _T("Team must have an assigned Captain; ");
	}

	//Must have at least 1 GK
	if (numGK < 1)
	{
		errorTot++;
		errorMsg << _T("Team must have a registered GK; ");
	}

    //Check heights
    if(!usingRed) //Using Green height system
    {
		msgOut+=_T("Using Green height system\r\n");
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
			errorMsg << _T("Has ") << numGiga << _T("/") << greenGiga << _T(" ") << heightGiga << _T("cm players; ");
		}
        if(diff = greenGiant - numGiant)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numGiant << _T("/") << greenGiant << _T(" ") << heightGiant << _T("cm players; ");
        }
        if(diff = greenTall - numTall)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numTall << _T("/") << greenTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
        }
        if(diff = greenMid - numMid)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numMid << _T("/") << greenMid << _T(" ") << heightMid << _T("cm players; ");
        }
        if(diff = greenManlet - numManlet)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numManlet << _T("/") << greenManlet << _T(" ") << heightManlet << _T("cm players; ");
        }
    }
    else //Using Red height system
    {
		msgOut+=_T("Using Red height system\r\n");
		if (diff = numGiga)
		{
			errorTot += diff;
			errorMsg << _T("Has ") << numGiga << _T("/") << redGiga << _T(" ") << heightGiga << _T("cm players; ");
		}
        if(diff = numGiant)
        {
            errorTot += diff;
			errorMsg << _T("Has ") << numGiant << _T("/") << redGiant << _T(" ") << heightGiant << _T("cm players; ");
        }
        if(diff = redTall - numTall)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numTall << _T("/") << redTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
        }
        if(diff = redMid - numMid)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numMid << _T("/") << redMid << _T(" ") << heightMid << _T("cm players; ");
        }
        if(diff = redManlet - numManlet)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numManlet << _T("/") << redManlet << _T(" ") << heightManlet << _T("cm players; ");
        }
    }
	if(errorMsg.rdbuf()->in_avail())
	{
		errorMsg << _T("\r\n");
		msgOut+=errorMsg.str();
		errorMsg.clear();
		errorMsg.str(tstring());
	}
    
    //Check ability stats
    if(numReg != (23-reqNumBronze-reqNumSilver-reqNumGold))
    {
        errorTot++;
        errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << 23-reqNumBronze-reqNumSilver-reqNumGold << _T("; ");
    }
    if(numSilver != reqNumBronze)
    {
        errorTot++;
        errorMsg << _T("Number of Bronze medals is ") << numBronze << _T(", should be ") << reqNumBronze << _T("; ");
    }
    if(numSilver != reqNumSilver)
    {
        errorTot++;
        errorMsg << _T("Number of Silver medals is ") << numSilver << _T(", should be ") << reqNumSilver << _T("; ");
    }
    if(numGold != reqNumGold)
    {
        errorTot++;
        errorMsg << _T("Number of Gold medals is ") << numGold << _T(", should be ") << reqNumGold << _T("; ");
    }
	if(errorMsg.rdbuf()->in_avail())
		errorMsg << _T("\r\n");
	errorMsg << _T("\r\nErrors: ") << errorTot << _T("\r\n");
	msgOut+=errorMsg.str();

	SetWindowText(GetDlgItem(hAatfbox, IDT_AATFOUT), msgOut.c_str());
	if(errorTot)
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Alright, get their clothes"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("GO TEAM EXPORT!"));
}

//Exclusive: Check if player is ONLY in that position across all presets and formations
bool aatf_check_player_in_pos(team_entry& team, player_entry& player, int position, bool exclusive)
{
	bool isInPos = true;
	bool isInStarting11 = false;
	int playerIndex = 0;

	for (int ii = 0; ii < 11; ii++)
	{
		if (player.id == (team.id * 100) + 1 + team.starting11[ii])
		{
			isInStarting11 = true;
			playerIndex = ii;
			break;
		}
	}

	if (isInStarting11)
	{
		for (int indexP = 0; indexP < 3; indexP++)
		{
			int formationCount = team.presets[indexP].fluid ? 3 : 1;
			for (int indexF = 0; indexF < formationCount; indexF++)
			{
				int playerPos = team.presets[indexP].formations[indexF].players[playerIndex].pos;

				//If not exclusive, return true if any player has that position in any preset or formation
				if (!exclusive && playerPos == position)
					return true;

				isInPos = isInPos && team.presets[indexP].formations[indexF].players[playerIndex].pos == position;
			}
		}
	}
	else
	{
		return player.reg_pos == position;
	}

	return isInPos;
}

//The position of each player on a team's first preset in their deadline export are required to match one of the player's 'A' positions
bool aatf_check_player_in_A_position_in_P1(team_entry& team, player_entry& player)
{
	bool isInPos = true;
	bool isInStarting11 = false;
	int playerIndex = 0;

	for (int ii = 0; ii < 11; ii++)
	{
		if (player.id == (team.id * 100) + 1 + team.starting11[ii])
		{
			isInStarting11 = true;
			playerIndex = ii;
			break;
		}
	}

	if (isInStarting11)
	{
		int indexP = 0;
		int formationCount = team.presets[indexP].fluid ? 3 : 1;
		for (int indexF = 0; indexF < formationCount; indexF++)
		{
			//Get the position the player is in in this formation (uses Registered Position values)
			int playerPos = team.presets[indexP].formations[indexF].players[playerIndex].pos;

			//Loop over A positions for this player and see if matches position in formation
			bool inAPos = false;
			for (int jj = 0; jj < 13; jj++)
			{
				//Check if any A position matches the formation position, converted to Playable Position values
				if (player.play_pos[jj] == 2 && jj == n_regPosToPlayPos[playerPos])
				{
					inAPos = true;
				}
			}

			isInPos = isInPos && inAPos;
		}
	}
	else
	{
		return true;
	}

	return isInPos;
}