#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#ifndef UNICODE  
  typedef std::string tstring; 
  typedef std::stringstream tstringstream;
#else
  typedef std::wstring tstring; 
  typedef std::wstringstream tstringstream;
#endif

void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players)
{
	player_entry player;
	tstring msgOut;
	msgOut+=_T("Team: ");
	msgOut+=gteams[teamSel].name;
	msgOut+=_T("\r\n");

	//Settings
	int manletBonus = 5;
	int giantPen = 0;

	int goldRate = 99;
	int silverRate = 88;
	int reqNumGold = 2;
	int reqNumSilver = 2;

	int greenGiant = 6;
	int greenTall = 5;
	int greenMid = 6;
	int greenManlet = 6;

	int redGiant = 0;
	int redTall = 10;
	int redMid = 7;
	int redManlet = 6;

	int numGK = 0;
    //Player ratings
    int numReg = 0;
    int numSilver = 0;
    int numGold = 0;
    //Height brackets
    int numGiant = 0;
    int numTall = 0;
    int numMid = 0;
    int numManlet = 0;
    bool usingRed = false;
    
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
        bool hasTrick = false;
		int targetRate = 0, targetRate2 = 0;
		int rating = player.drib;
        rating = max(player.gk, rating);
        rating = max(player.finish, rating);
        rating = max(player.lowpass, rating);
        rating = max(player.loftpass, rating);
        rating = max(player.header, rating);
        rating = max(player.swerve, rating);
        rating = max(player.catching, rating);
        rating = max(player.clearing, rating);
        rating = max(player.reflex, rating);
        rating = max(player.body_ctrl, rating);
        if(pesVersion!=16) rating = max(player.phys_cont, rating); //Not in 16
        rating = max(player.kick_pwr, rating);
        rating = max(player.exp_pwr, rating);
        rating = max(player.ball_ctrl, rating);
        rating = max(player.ball_win, rating);
        rating = max(player.jump, rating);
        rating = max(player.cover, rating);
        rating = max(player.place_kick, rating);
        rating = max(player.stamina, rating);
        rating = max(player.speed, rating);
		if(pesVersion>19) rating = max(player.aggres, rating);
		
		if(player.injury+1 > 3)
		{
			errorTot++;
            errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", cannot exceed 3; ");
		}

		//Check if registered pos has playable set to A
        if(player.reg_pos == 12 && player.play_pos[0] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 11 && player.play_pos[1] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 10 && player.play_pos[3] != 2)
		{
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 9 && player.play_pos[2] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 8 && player.play_pos[4] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 7 && player.play_pos[8] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 6 && player.play_pos[7] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 5 && player.play_pos[6] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 4 && player.play_pos[5] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 3 && player.play_pos[11] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 2 && player.play_pos[10] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 1 && player.play_pos[9] != 2)
        {
            errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
        else if(player.reg_pos == 0)
        {
            numGK++;
            if(player.play_pos[12] != 2)
			{
                errorTot++;
				errorMsg << _T("Doesn't have A in registered position; ");
			}
        }

		//Count A positions
        int countA = 0;
        for(int jj=0;jj<13;jj++)
        {
            if(player.play_pos[jj] > 0)
				countA++;
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
		int numSkill;
		if(pesVersion==19) numSkill=39;
		else if(pesVersion>19) numSkill=41;
		else numSkill=28;
        for(int jj=0;jj<numSkill;jj++)
        {
            if(player.play_skill[jj])
            {
                cardCount++;
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

		if(player.height <= 175)
		{
            numManlet++;
			cardMod++; //Manlets get a bonus card
		}
        else if(player.height == 180)
            numMid++;
        else if(player.height == 185)
            numTall++;
        else if(player.height == 189 && player.reg_pos == 0) //GK
            numTall++;
        else if(player.height > 193 && player.height < 200)
            numGiant++;
        else
		{
            errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
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

		/* REGULAR */
		if(rating < silverRate-2) //Regular player
        {
            numReg++;
			targetRate = 77;
			targetRate2 = 77;

			if(player.height >= 180)
			{
				if(player.weak_use+1 > 2)
				{
					errorTot++;
					errorMsg << _T("Weak foot usage > 2; ");
				}
				if(player.weak_acc+1 > 2)
				{
					errorTot++;
					errorMsg << _T("Weak foot accuracy > 2; ");
				}
			}

            if(player.form+1 != 4)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be 4; ");
			}

			
            if(player.reg_pos == 0) //GK gets 2 cards
            {
				cardMod += min(0, numTrick); //0 free tricks
				cardLimit = 2 + cardMod;
                if(cardCount > cardLimit)
				{
                    errorTot++;
					errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
				}
				if(player.height > 184 && player.height < 189)
				{
                    errorTot++;
					errorMsg << _T("GKs in this bracket must be 189cm; ");
				}
            }
            else
			{
				cardMod += min(2, numTrick); //2 free tricks
				cardLimit = 4 + cardMod;
				if(cardCount > cardLimit)
				{
					errorTot++;
					errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
				}
			}
            
			if(player.reg_pos == 0) //GK gets target rate is 77
            {
				targetRate = 77;
				if(player.height <= 175)
				{
					targetRate += manletBonus;
					targetRate2 += manletBonus;
				}
			}
            else if(rating != targetRate)
            {
                if(rating != targetRate+manletBonus || player.height > 175)
				{
                    errorTot++;
					errorMsg << _T("Illegal Ability scores; ");
				}
                else
				{
                    usingRed = true;
					targetRate += manletBonus;
					targetRate2 += manletBonus;
				}
            }
			if(player.injury+1 > 1)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be 1; ");
			}
		}
		/* SILVER */
        else if(rating < goldRate-4) //Silver player
        {
            numSilver++;
			targetRate = silverRate;
			targetRate2 = silverRate;

            if(numSilver > reqNumSilver)
			{
                errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
            if(player.form+1 != 8)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be 8; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height > 185) //HA get penalty
			{
				targetRate -= 2;
				targetRate2 -= 2;
			}
            cardMod += min(3, numTrick); //3 free tricks
			cardMod += min(1, numCom); //1 free COM
			cardLimit = 5 + cardMod;
            if(cardCount > cardLimit)
			{
                errorTot++;
				errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
			}
            if(rating != targetRate)
			{
                errorTot++;
				errorMsg << _T("Illegal Ability scores; ");
			}
			if(player.injury+1 > 3)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be 3; ");
			}
        }
		/* GOLD */
        else //rating == 99 //Gold player
        {
            numGold++;
			targetRate = goldRate;
			targetRate2 = goldRate;

            if(numGold > reqNumGold)
			{
                errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
            if(player.form+1 != 8)
			{
                errorTot++;
				errorMsg << _T("Form is ") << player.form+1 << _T(", should be 8; ");
			}
            if(player.reg_pos == 0) //Medals can't be GK
			{
                errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if(player.height > 185) //Medal HA penalty
			{
				targetRate -= 4;
				targetRate2 -= 4;
			}
            cardMod += min(3, numTrick); //3 free tricks
			cardMod += min(2, numCom); //2 free COMs

			cardLimit = 6 + cardMod;
            if(cardCount > cardLimit)
			{
                errorTot++;
				errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
			}
            if(rating != targetRate)
			{
                errorTot++;
				errorMsg << _T("Illegal Ability scores; ");
			}

			if(player.injury+1 > 3)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be 3; ");
			}
		}

		//Check PES skill card limit of 10
		if(cardCount-numCom > 10)
		{
            errorTot++;
			errorMsg << _T("Has ") << cardCount-numCom << _T(" skill cards, PES limit is 10, please swap to COM cards or trade for additional A positions; ");
		}

		if(player.drib != targetRate)
        {
            errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.gk != targetRate)
        {
            errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.finish != targetRate)
		{
            errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.lowpass != targetRate)
		{
            errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.loftpass != targetRate)
		{
            errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.header != targetRate)
		{
            errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.swerve != targetRate)
		{
            errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.catching != targetRate)
		{
            errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.clearing != targetRate)
		{
            errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.reflex != targetRate)
		{
            errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.body_ctrl != targetRate)
		{
            errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.phys_cont != targetRate && pesVersion!=16) //Not in 16
		{
            errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.kick_pwr != targetRate)
		{
            errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.exp_pwr != targetRate2)
		{
            errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetRate2 << _T("; ");
        }
        if(player.ball_ctrl != targetRate)
		{
            errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.ball_win != targetRate2)
		{
            errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetRate2 << _T("; ");
        }
        if(player.jump != targetRate)
		{
            errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.cover != targetRate)
		{
            errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.place_kick != targetRate)
		{
            errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.stamina != targetRate)
		{
            errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.speed != targetRate)
		{
            errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetRate << _T("; ");
        }
        if(player.atk > targetRate)
		{
            errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetRate << _T(" or less; ");
        }
        if(player.def > targetRate2)
		{
            errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetRate2 << _T(" or less; ");
        }
		if(pesVersion>19 && player.aggres > targetRate)
		{
            errorTot++;
			errorMsg << _T("Aggression is ") << player.aggres << _T(", should be ") << targetRate << _T("; ");
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
    //Check heights
    if(!usingRed) //Using Green height system
    {
		msgOut+=_T("Using Green height system\r\n");
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
			errorMsg << _T("Has ") << numGiant << _T("/") << greenGiant << _T(" 194-199cm players; ");
        }
        if(diff = 5 - numTall)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numTall << _T("/") << greenTall << _T(" 185/9cm players; ");
        }
        if(diff = 6 - numMid)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numMid << _T("/") << greenMid << _T(" 180cm players; ");
        }
        if(diff = 6 - numManlet)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numManlet << _T("/") << greenManlet << _T(" 175cm players; ");
        }
    }
    else //Using Red height system
    {
		msgOut+=_T("Using Red height system\r\n");
        if(diff = numGiant)
        {
            errorTot += diff;
			errorMsg << _T("Has ") << numGiant << _T("/") << redGiant << _T(" 194-199cm players; ");
        }
        if(diff = 10 - numTall)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numTall << _T("/") << redTall << _T(" 185/9cm players; ");
        }
        if(diff = 7 - numMid)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numMid << _T("/") << redMid << _T(" 180cm players; ");
        }
        if(diff = 6 - numManlet)
        {
            if(diff>0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
			errorMsg << _T("Has ") << numManlet << _T("/") << redManlet << _T(" 175cm players; ");
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
    if(numReg != (23-reqNumSilver-reqNumGold))
    {
        errorTot++;
        errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << 23-reqNumSilver-reqNumGold << _T("; ");
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
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("It's all so tiresome."));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("You have received one (1) Official R-word Pass."));
}
