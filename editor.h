//----------------------------------------------------------------------
/*Header files and preprocessor directives*/

#define WIN32_LEAN_AND_MEAN //Exclude rarely-used services from Windows headers

#include <tchar.h>		//Provides TCHAR type and functions
#include <windows.h>	//Win32 types and functions
#include <errno.h>		//Standard C error handling
#include <Shlwapi.h>	//Provides PathFileExists
#include <commctrl.h>	//Provides common control types 
						//  (e.g. HTREEITEM, TVITEM, LVITEM)
#include <fstream>
#include <unordered_map> //Unordered map for Player Appearance start byte lookup
#include "atlstr.h"
#include "crypt.h"

#pragma comment( lib, "Shlwapi.lib" )	//Needed to make Shlwapi.h link
#pragma comment( lib, "comctl32.lib" )	//Needed to link to common controls functions 
										// (InitCommonControls(), ImageList funcs,
										//  Subclass funcs, etc.)

//----------------------------------------------------------------------
/*Data structures*/
//char gc_ver4ccs[] = "20a";
struct player_export
{
	unsigned int nation;
	unsigned char height;
	unsigned char weight;
	unsigned char gc1;
	unsigned char gc2;
	unsigned char atk; //Attacking Prowess 
	unsigned char def; //Defensive Prowess 
	unsigned char gk; //Goalkeeping 
	unsigned char drib; //Dribbling 
	unsigned char mo_fk; //Motion: Free Kick
	unsigned char finish; //Finishing 
	unsigned char lowpass; //Low Pass 
	unsigned char loftpass; //Lofted Pass 
	unsigned char header; //Header 
	unsigned char form; //Form 
	bool b_edit_player; //Edited/Created player 
	unsigned char swerve; //Swerve 
	unsigned char catching; //Catching 						(Saving in 15)
	unsigned char clearing; //Clearing 						(16+)
	unsigned char reflex; //Reflexes 						(16+)
	unsigned char injury; //Injury Resistance 
	bool b_edit_basicset; //Whether the player's basic settings are changed
	unsigned char body_ctrl; //Body Control 
	unsigned char phys_cont; //Physical Contact				(17+)
	unsigned char kick_pwr; //Kicking Power
	unsigned char exp_pwr; //Explosive Power 
	unsigned char mo_armd; //Motion: Arm Movement (dribbling) 
	bool b_edit_regpos;//Registered Position edit
	unsigned char age; //Age 
	unsigned char reg_pos; //Registered Position 
	unsigned char play_style; //Playing Styles 
	unsigned char ball_ctrl; //Ball Control 
	unsigned char ball_win; //Ball Winning 
	unsigned char weak_acc; //Weak Foot Accuracy 
	unsigned char jump; //Jump 
	unsigned char mo_armr; //Motion: Arm Movement (running) 
	unsigned char mo_ck; //Motion: Corner Kick 
	unsigned char cover; //Coverage							(16+)
	unsigned char weak_use; //Weak Foot Usage
	unsigned char play_pos[13]; //Playable Position 
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
	unsigned char mo_hunchd; //Motion: Hunching (dribbling) 
	unsigned char mo_hunchr; //Motion: Hunching (running) 
	unsigned char mo_pk; //Motion: Penalty Kick 
	unsigned char place_kick; //Place Kicking 
	unsigned char star; //Star rating						(19+)
	unsigned char mo_drib; //Motion: Dribbling				(20+) 
	unsigned char tight_pos; //Tight Possession				(20+)
	unsigned char aggres; //Aggression						(20+)
	unsigned char play_attit; //Playing Attitude			(20+)

	bool b_edit_playpos; //Playable Position edit
	bool b_edit_ability; //Ability edit
	bool b_edit_skill; //Player Skills edit
	unsigned char stamina; //Stamina 
	unsigned char speed; //Speed 
	bool b_edit_style; //Playing Styles edit
	bool b_edit_com; //COM Playing Styles edit
	bool b_edit_motion; //Motion edit
	bool b_base_copy; //Is Base Copy?
	unsigned char strong_foot; //Stronger Foot 
	unsigned char strong_hand; //Stronger hand				(20+)
	bool com_style[7]; //COM Playing Styles
	/*	Bit 0 - Trickster
		Bit 1 - Mazing Run
		Bit 2 - Speeding Bullet
		Bit 3 - Incisive Run
		Bit 4 - Long Ball Expert
		Bit 5 - Early Cross
		Bit 6 - Long Ranger
	*/
	bool play_skill[41]; //Player Skills 
	/*
	0 Scissors Feint
	1 Flip flap
	2 Marseille turn
	3 Sombrero
	4 Cut Behind & Turn
	5 Scotch Move
	6 Heading
	7 Long range drive
	8 Knuckle shot
	9 Acro finishing
	10 Heel trick
	11 First time shot
	12 One touch pass
	13 Weighted pass
	14 Pinpoint crossing
	15 Outside curler
	16 Rabona
	17 Low Lofted Pass
	18 Low Punt trajectory
	19 Long throw
	20 GK long throw
	21 Malicia
	22 Man marking
	23 Track back
	24 Acro clear
	25 Captaincy
	26 Super sub
	27 Fighting spirit
	28 Double Touch
	29 Crossover Turn
	30 Step on Skill
	31 Chip Shot
	32 Dipping Shots
	33 Rising Shots
	34 No Look Pass
	35 GK High Punt Trajectory
	36 Penalty Specialist
	37 GK Penalty Specialist
	38 Interception
	39 Long Range Shooting (20+)
	40 Through Passing (20+)
	*/
	wchar_t name[61]; //Player Name
	char shirt_name[21]; //Shirt Name

	//Appearance
	bool b_edit_face; //Edited Face 
	bool b_edit_hair; //Edited Hairstyle 
	bool b_edit_phys; //Edited Physique
	bool b_edit_strip; //Edited Strip Style
	unsigned int boot_id; //Boots
	unsigned int glove_id; //Goalkeeper gloves
	unsigned long copy_id; //Base Copy Player
	int neck_len; //Neck Length 
	int neck_size; //Neck Size
	int shldr_hi; //Shoulder Height 
	int shldr_wid; //Shoulder Width 
	int chest; //Chest Measurement 
	int waist; //Waist Size 
	int arm_size; //Arm Size 
	int arm_len; //Arm Length
	int thigh; //Thigh Size 
	int calf; //Calf Size
	int leg_len; //Leg Length 
	int head_len; //Head Length 
	int head_wid; //Head Width 
	int head_dep; //Head Depth 
	unsigned char wrist_col_l; //Wrist Tape: Color left 
	unsigned char wrist_col_r; //Wrist Tape: Color right 
	unsigned char wrist_tape; //Wrist Taping 
	unsigned char spec_col; //Spectacles frame color 
	unsigned char spec_style; //Spectacles style
	unsigned char sleeve; //Sleeves 
	unsigned char inners; //Long-Sleeved Inners 
	unsigned char socks; //Sock Length 
	unsigned char undershorts; //Undershorts 
	bool untucked; //Shirttail 
	bool ankle_tape; //Ankle Taping 
	bool gloves; //Player Gloves 
	unsigned char gloves_col; //Player Gloves color 
	unsigned char skin_col; //Skin color 
	unsigned char iris_col; //Iris color 
};

struct player_entry : player_export
{
	unsigned long id;
	//Appearance
	unsigned long app_id; //Player ID again

	bool b_changed;
	bool b_show;
	int team_ind;
	int team_lineup_ind;

	//Constructor
	player_entry()
	{
		b_changed = false;
		b_show = true;
		team_ind = -1;
		memset(name,0,sizeof(name));
		memset(shirt_name,0,sizeof(shirt_name));
		memset(play_skill,0,sizeof(play_skill));
	}

	bool operator==(const player_entry& rhs)
	{
		int ii;
		bool b_out=true;

		for(ii=0;ii<13;ii++) b_out = b_out && (this->play_pos[ii]==rhs.play_pos[ii]);
		for(ii=0;ii<7;ii++) b_out = b_out && (this->com_style[ii]==rhs.com_style[ii]);
		for(ii=0;ii<41;ii++) b_out = b_out && (this->play_skill[ii]==rhs.play_skill[ii]);
		b_out = b_out && (wcscmp(this->name, rhs.name)==0);
		b_out = b_out && (strcmp(this->shirt_name, rhs.shirt_name)==0);
		b_out = b_out && (this->id==rhs.id);
		b_out = b_out &&(this->age==rhs.age);
		b_out = b_out &&(this->ankle_tape==rhs.ankle_tape);
		b_out = b_out &&(this->app_id==rhs.app_id);
		b_out = b_out &&(this->arm_len==rhs.arm_len);
		b_out = b_out &&(this->arm_size==rhs.arm_size);
		b_out = b_out &&(this->atk==rhs.atk);
		b_out = b_out &&(this->b_base_copy==rhs.b_base_copy);
		b_out = b_out &&(this->b_edit_face==rhs.b_edit_face);
		b_out = b_out &&(this->b_edit_hair==rhs.b_edit_hair);
		b_out = b_out &&(this->b_edit_phys==rhs.b_edit_phys);
		b_out = b_out &&(this->b_edit_player==rhs.b_edit_player);
		b_out = b_out &&(this->b_edit_strip==rhs.b_edit_strip);
		b_out = b_out &&(this->ball_ctrl==rhs.ball_ctrl);
		b_out = b_out &&(this->ball_win==rhs.ball_win);
		b_out = b_out &&(this->body_ctrl==rhs.body_ctrl);
		b_out = b_out &&(this->boot_id==rhs.boot_id);
		b_out = b_out &&(this->calf==rhs.calf);
		b_out = b_out &&(this->catching==rhs.catching);
		b_out = b_out &&(this->chest==rhs.chest);
		b_out = b_out &&(this->clearing==rhs.clearing);
		b_out = b_out &&(this->copy_id==rhs.copy_id);
		b_out = b_out &&(this->cover==rhs.cover);
		b_out = b_out &&(this->def==rhs.def);
		b_out = b_out &&(this->drib==rhs.drib);
		b_out = b_out &&(this->exp_pwr==rhs.exp_pwr);
		b_out = b_out &&(this->finish==rhs.finish);
		b_out = b_out &&(this->form==rhs.form);
		b_out = b_out &&(this->gc1==rhs.gc1);
		b_out = b_out &&(this->gc2==rhs.gc2);
		b_out = b_out &&(this->gk==rhs.gk);
		b_out = b_out &&(this->glove_id==rhs.glove_id);
		b_out = b_out &&(this->gloves==rhs.gloves);
		b_out = b_out &&(this->gloves_col==rhs.gloves_col);
		b_out = b_out &&(this->head_dep==rhs.head_dep);
		b_out = b_out &&(this->head_len==rhs.head_len);
		b_out = b_out &&(this->head_wid==rhs.head_wid);
		b_out = b_out &&(this->header==rhs.header);
		b_out = b_out &&(this->height==rhs.height);
		b_out = b_out &&(this->injury==rhs.injury);
		b_out = b_out &&(this->inners==rhs.inners);
		b_out = b_out &&(this->iris_col==rhs.iris_col);
		b_out = b_out &&(this->jump==rhs.jump);
		b_out = b_out &&(this->kick_pwr==rhs.kick_pwr);
		b_out = b_out &&(this->leg_len==rhs.leg_len);
		b_out = b_out &&(this->loftpass==rhs.loftpass);
		b_out = b_out &&(this->lowpass==rhs.lowpass);
		b_out = b_out &&(this->mo_armd==rhs.mo_armd);
		b_out = b_out &&(this->mo_armr==rhs.mo_armr);
		b_out = b_out &&(this->mo_ck==rhs.mo_ck);
		b_out = b_out &&(this->mo_fk==rhs.mo_fk);
		b_out = b_out &&(this->mo_hunchd==rhs.mo_hunchd);
		b_out = b_out &&(this->mo_hunchr==rhs.mo_hunchr);
		b_out = b_out &&(this->mo_pk==rhs.mo_pk);
		b_out = b_out &&(this->nation==rhs.nation);
		b_out = b_out &&(this->neck_len==rhs.neck_len);
		b_out = b_out &&(this->neck_size==rhs.neck_size);
		b_out = b_out &&(this->phys_cont==rhs.phys_cont);
		b_out = b_out &&(this->place_kick==rhs.place_kick);
		b_out = b_out &&(this->play_style==rhs.play_style);
		b_out = b_out &&(this->reflex==rhs.reflex);
		b_out = b_out &&(this->reg_pos==rhs.reg_pos);
		b_out = b_out &&(this->shldr_hi==rhs.shldr_hi);
		b_out = b_out &&(this->shldr_wid==rhs.shldr_wid);
		b_out = b_out &&(this->skin_col==rhs.skin_col);
		b_out = b_out &&(this->sleeve==rhs.sleeve);
		b_out = b_out &&(this->socks==rhs.socks);
		b_out = b_out &&(this->spec_col==rhs.spec_col);
		b_out = b_out &&(this->spec_style==rhs.spec_style);
		b_out = b_out &&(this->speed==rhs.speed);
		b_out = b_out &&(this->stamina==rhs.stamina);
		b_out = b_out &&(this->strong_foot==rhs.strong_foot);
		b_out = b_out &&(this->swerve==rhs.swerve);
		b_out = b_out &&(this->thigh==rhs.thigh);
		b_out = b_out &&(this->untucked==rhs.untucked);
		b_out = b_out &&(this->undershorts==rhs.undershorts);
		b_out = b_out &&(this->waist==rhs.waist);
		b_out = b_out &&(this->weak_acc==rhs.weak_acc);
		b_out = b_out &&(this->weak_use==rhs.weak_use);
		b_out = b_out &&(this->weight==rhs.weight);
		b_out = b_out &&(this->wrist_col_l==rhs.wrist_col_l);
		b_out = b_out &&(this->wrist_col_r==rhs.wrist_col_r);
		b_out = b_out &&(this->wrist_tape==rhs.wrist_tape);

		b_out = b_out &&(this->tight_pos==rhs.tight_pos);
		b_out = b_out &&(this->aggres==rhs.aggres);
		//
		b_out = b_out &&(this->star==rhs.star);
		b_out = b_out &&(this->mo_drib==rhs.mo_drib);
		b_out = b_out &&(this->play_attit==rhs.play_attit);
		b_out = b_out &&(this->strong_hand==rhs.strong_hand);

		return b_out;
	}

	player_export PlayerExport()
	{
		player_export pExport;
		pExport.nation = this->nation;
		pExport.height = this->height;
		pExport.weight = this->weight;
		pExport.gc1 = this->gc1;
		pExport.gc2 = this->gc2;
		pExport.atk = this->atk; 
		pExport.def = this->def; 
		pExport.gk = this->gk; //Goalkeeping 
		pExport.drib = this->drib; //Dribbling 
		pExport.mo_fk = this->mo_fk; //Motion: Free Kick
		pExport.finish = this->finish; //Finishing 
		pExport.lowpass = this->lowpass; //Low Pass 
		pExport.loftpass = this->loftpass; //Lofted Pass 
		pExport.header = this->header; //Header 
		pExport.form = this->form; //Form 
		pExport.b_edit_player = this->b_edit_player; //Edited/Created player 
		pExport.swerve = this->swerve; //Swerve 
		pExport.catching = this->catching; //Catching 
		pExport.clearing = this->clearing; //Clearing 
		pExport.reflex = this->reflex; //Reflexes 
		pExport.injury = this->injury; //Injury Resistance 
		pExport.b_edit_basicset = this->b_edit_basicset; //Whether the player's basic settings are changed
		pExport.body_ctrl = this->body_ctrl; //Body Control 
		pExport.phys_cont = this->phys_cont; //Physical Contact 
		pExport.kick_pwr = this->kick_pwr; //Kicking Power
		pExport.exp_pwr = this->exp_pwr; //Explosive Power 
		pExport.mo_armd = this->mo_armd; //Motion: Arm Movement (dribbling) 
		pExport.b_edit_regpos = this->b_edit_regpos;//Registered Position edit
		pExport.age = this->age; //Age 
		pExport.reg_pos = this->reg_pos; //Registered Position 
		pExport.play_style = this->play_style; //Playing Styles 
		pExport.ball_ctrl = this->ball_ctrl; //Ball Control 
		pExport.ball_win = this->ball_win; //Ball Winning 
		pExport.weak_acc = this->weak_acc; //Weak Foot Accuracy 
		pExport.jump = this->jump; //Jump 
		pExport.mo_armr = this->mo_armr; //Motion: Arm Movement (running) 
		pExport.mo_ck = this->mo_ck; //Motion: Corner Kick 
		pExport.cover = this->cover; //Coverage 
		pExport.weak_use = this->weak_use; //Weak Foot Usage
		memcpy(pExport.play_pos,this->play_pos,sizeof(this->play_pos)); //Playable Position 
		pExport.mo_hunchd = this->mo_hunchd; //Motion: Hunching (dribbling) 
		pExport.mo_hunchr = this->mo_hunchr; //Motion: Hunching (running) 
		pExport.mo_pk = this->mo_pk; //Motion: Penalty Kick 
		pExport.place_kick = this->place_kick; //Place Kicking 
		pExport.b_edit_playpos = this->b_edit_playpos; //Playable Position edit
		pExport.b_edit_ability = this->b_edit_ability; //Ability edit
		pExport.b_edit_skill = this->b_edit_skill; //Player Skills edit
		pExport.stamina = this->stamina; //Stamina 
		pExport.speed = this->speed; //Speed 
		pExport.b_edit_style = this->b_edit_style; //Playing Styles edit
		pExport.b_edit_com = this->b_edit_com; //COM Playing Styles edit
		pExport.b_edit_motion = this->b_edit_motion; //Motion edit
		pExport.b_base_copy = this->b_base_copy; //Is Base Copy?
		pExport.strong_foot = this->strong_foot; //Stronger Foot 
		memcpy(pExport.com_style, this->com_style, sizeof(this->com_style)); //COM Playing Styles
		memcpy(pExport.play_skill, this->play_skill, sizeof(this->play_skill)); //Player Skills 
		memcpy(pExport.name, this->name, sizeof(this->name)); //Player Name
		memcpy(pExport.shirt_name, this->shirt_name, sizeof(this->shirt_name)); //Shirt Name
		pExport.b_edit_face = this->b_edit_face; //Edited Face 
		pExport.b_edit_hair = this->b_edit_hair; //Edited Hairstyle 
		pExport.b_edit_phys = this->b_edit_phys; //Edited Physique
		pExport.b_edit_strip = this->b_edit_strip; //Edited Strip Style
		pExport.boot_id = this->boot_id; //Boots
		pExport.glove_id = this->glove_id; //Goalkeeper gloves
		pExport.copy_id = this->copy_id; //Base Copy Player
		pExport.neck_len = this->neck_len; //Neck Length 
		pExport.neck_size = this->neck_size; //Neck Size
		pExport.shldr_hi = this->shldr_hi; //Shoulder Height 
		pExport.shldr_wid = this->shldr_wid; //Shoulder Width 
		pExport.chest = this->chest; //Chest Measurement 
		pExport.waist = this->waist; //Waist Size 
		pExport.arm_size = this->arm_size; //Arm Size 
		pExport.arm_len = this->arm_len; //Arm Length
		pExport.thigh = this->thigh; //Thigh Size 
		pExport.calf = this->calf; //Calf Size
		pExport.leg_len = this->leg_len; //Leg Length 
		pExport.head_len = this->head_len; //Head Length 
		pExport.head_wid = this->head_wid; //Head Width 
		pExport.head_dep = this->head_dep; //Head Depth 
		pExport.wrist_col_l = this->wrist_col_l; //Wrist Tape: Color left 
		pExport.wrist_col_r = this->wrist_col_r; //Wrist Tape: Color right 
		pExport.wrist_tape = this->wrist_tape; //Wrist Taping 
		pExport.spec_col = this->spec_col; //Spectacles frame color 
		pExport.spec_style = this->spec_style; //Spectacles style
		pExport.sleeve = this->sleeve; //Sleeves 
		pExport.inners = this->inners; //Long-Sleeved Inners 
		pExport.socks = this->socks; //Sock Length 
		pExport.undershorts = this->undershorts; //Undershorts 
		pExport.untucked = this->untucked; //Shirttail 
		pExport.ankle_tape = this->ankle_tape; //Ankle Taping 
		pExport.gloves = this->gloves; //Player Gloves 
		pExport.gloves_col = this->gloves_col; //Player Gloves color 
		pExport.skin_col = this->skin_col; //Skin color 
		pExport.iris_col = this->iris_col; //Iris color 

		pExport.tight_pos = this->tight_pos;
		pExport.aggres = this->aggres;
		//
		pExport.star = this->star;
		pExport.mo_drib = this->mo_drib;		
		pExport.play_attit = this->play_attit;
		pExport.strong_hand = this->strong_hand;

		return pExport;
	}

	void PlayerImport(player_export pImport, bool importStats=true, bool importAes=true)
	{
		if(importStats)
		{
			this->height = pImport.height;
			this->weight = pImport.weight;
			this->atk = pImport.atk; 
			this->def = pImport.def; 
			this->gk = pImport.gk; //Goalkeeping 
			this->drib = pImport.drib; //Dribbling 
			this->mo_fk = pImport.mo_fk; //Motion: Free Kick
			this->finish = pImport.finish; //Finishing 
			this->lowpass = pImport.lowpass; //Low Pass 
			this->loftpass = pImport.loftpass; //Lofted Pass 
			this->header = pImport.header; //Header 
			this->form = pImport.form; //Form 
			this->b_edit_player = pImport.b_edit_player; //Edited/Created player 
			this->swerve = pImport.swerve; //Swerve 
			this->catching = pImport.catching; //Catching 
			this->clearing = pImport.clearing; //Clearing 
			this->reflex = pImport.reflex; //Reflexes 
			this->injury = pImport.injury; //Injury Resistance 
			this->b_edit_basicset = pImport.b_edit_basicset; //Whether the player's basic settings are changed
			this->body_ctrl = pImport.body_ctrl; //Body Control 
			this->phys_cont = pImport.phys_cont; //Physical Contact 
			this->kick_pwr = pImport.kick_pwr; //Kicking Power
			this->exp_pwr = pImport.exp_pwr; //Explosive Power 
			this->b_edit_regpos = pImport.b_edit_regpos;//Registered Position edit
			this->reg_pos = pImport.reg_pos; //Registered Position 
			this->play_style = pImport.play_style; //Playing Styles 
			this->ball_ctrl = pImport.ball_ctrl; //Ball Control 
			this->ball_win = pImport.ball_win; //Ball Winning 
			this->weak_acc = pImport.weak_acc; //Weak Foot Accuracy 
			this->jump = pImport.jump; //Jump 
			this->cover = pImport.cover; //Coverage 
			this->weak_use = pImport.weak_use; //Weak Foot Usage
			memcpy(this->play_pos,pImport.play_pos,sizeof(pImport.play_pos)); //Playable Position 
			this->place_kick = pImport.place_kick; //Place Kicking 
			this->b_edit_playpos = pImport.b_edit_playpos; //Playable Position edit
			this->b_edit_ability = pImport.b_edit_ability; //Ability edit
			this->b_edit_skill = pImport.b_edit_skill; //Player Skills edit
			this->stamina = pImport.stamina; //Stamina 
			this->speed = pImport.speed; //Speed 
			this->b_edit_style = pImport.b_edit_style; //Playing Styles edit
			this->b_edit_com = pImport.b_edit_com; //COM Playing Styles edit
			this->strong_foot = pImport.strong_foot; //Stronger Foot 
			memcpy(this->com_style, pImport.com_style, sizeof(pImport.com_style)); //COM Playing Styles
			memcpy(this->play_skill, pImport.play_skill, sizeof(pImport.play_skill)); //Player Skills

			this->tight_pos = pImport.tight_pos;
			this->aggres = pImport.aggres;
			//
			this->star = pImport.star;		
			this->play_attit = pImport.play_attit;
			this->strong_hand = pImport.strong_hand;
		}
		if(importAes)
		{
			this->nation = pImport.nation;
			this->gc1 = pImport.gc1;
			this->gc2 = pImport.gc2;
			this->mo_armd = pImport.mo_armd; //Motion: Arm Movement (dribbling) 
			this->mo_hunchd = pImport.mo_hunchd; //Motion: Hunching (dribbling) 
			this->mo_hunchr = pImport.mo_hunchr; //Motion: Hunching (running) 
			this->mo_pk = pImport.mo_pk; //Motion: Penalty Kick
			this->mo_armr = pImport.mo_armr; //Motion: Arm Movement (running) 
			this->mo_ck = pImport.mo_ck; //Motion: Corner Kick 
			this->age = pImport.age; //Age 
			this->b_edit_motion = pImport.b_edit_motion; //Motion edit
			this->b_base_copy = pImport.b_base_copy; //Is Base Copy?
			memcpy(this->name, pImport.name, sizeof(pImport.name)); //Player Name
			memcpy(this->shirt_name, pImport.shirt_name, sizeof(pImport.shirt_name)); //Shirt Name
			this->b_edit_face = pImport.b_edit_face; //Edited Face 
			this->b_edit_hair = pImport.b_edit_hair; //Edited Hairstyle 
			this->b_edit_phys = pImport.b_edit_phys; //Edited Physique
			this->b_edit_strip = pImport.b_edit_strip; //Edited Strip Style
			this->boot_id = pImport.boot_id; //Boots
			this->glove_id = pImport.glove_id; //Goalkeeper gloves
			this->copy_id = pImport.copy_id; //Base Copy Player
			this->neck_len = pImport.neck_len; //Neck Length 
			this->neck_size = pImport.neck_size; //Neck Size
			this->shldr_hi = pImport.shldr_hi; //Shoulder Height 
			this->shldr_wid = pImport.shldr_wid; //Shoulder Width 
			this->chest = pImport.chest; //Chest Measurement 
			this->waist = pImport.waist; //Waist Size 
			this->arm_size = pImport.arm_size; //Arm Size 
			this->arm_len = pImport.arm_len; //Arm Length
			this->thigh = pImport.thigh; //Thigh Size 
			this->calf = pImport.calf; //Calf Size
			this->leg_len = pImport.leg_len; //Leg Length 
			this->head_len = pImport.head_len; //Head Length 
			this->head_wid = pImport.head_wid; //Head Width 
			this->head_dep = pImport.head_dep; //Head Depth 
			this->wrist_col_l = pImport.wrist_col_l; //Wrist Tape: Color left 
			this->wrist_col_r = pImport.wrist_col_r; //Wrist Tape: Color right 
			this->wrist_tape = pImport.wrist_tape; //Wrist Taping 
			this->spec_col = pImport.spec_col; //Spectacles frame color 
			this->spec_style = pImport.spec_style; //Spectacles style
			this->sleeve = pImport.sleeve; //Sleeves 
			this->inners = pImport.inners; //Long-Sleeved Inners 
			this->socks = pImport.socks; //Sock Length 
			this->undershorts = pImport.undershorts; //Undershorts 
			this->untucked = pImport.untucked; //Shirttail 
			this->ankle_tape = pImport.ankle_tape; //Ankle Taping 
			this->gloves = pImport.gloves; //Player Gloves 
			this->gloves_col = pImport.gloves_col; //Player Gloves color 
			this->skin_col = pImport.skin_col; //Skin color 
			this->iris_col = pImport.iris_col; //Iris color

			//
			this->mo_drib = pImport.mo_drib;
		}
		this->b_changed = true;
	}
};

struct stripSet
{
	unsigned char stripNumber; //1 byte, Number of kit starting from 00, or 0x80 if goalkeeper
	unsigned long stripTeamId; //3 bytes, Team ID * 0x40
};

struct team_entry
{
	static const int team_max = 40; //Number of player entries per team

	unsigned long id; //Team ID
	unsigned long manager_id;
	int stadium_id;
	wchar_t name[0x46];
	char short_name[0x4];
	unsigned long players[team_max];
	uint16_t numbers[team_max];
	bool b_edit_name;
	bool b_edit_stadium;
	bool b_edit_strip; //Edited Strip flag

	int num_on_team;

	int starting11[11];
	char captain_ind;

	char color1_red;
	char color1_blue;
	char color1_green;
	char color2_red;
	char color2_blue;
	char color2_green;

	//Team strip block
	stripSet stripBlock[10];

	bool b_changed;
	bool b_show;

	//Constructor
	team_entry()
	{
		b_changed = false;
		b_show = true;
		b_edit_name = false;
		b_edit_stadium = false;
		b_edit_strip = false;
		memset(name,0,sizeof(name));
		memset(short_name,0,sizeof(short_name));
		for (int ii = 0; ii < team_max; ii++)
		{
			players[ii] = 0;
			numbers[ii] = 0;
		}
		for(int ii=0; ii<11; ii++) starting11[ii]=0;
		num_on_team = 0;
		color1_red = 0;
		color1_blue = 0;
		color1_green = 0;
		color2_red = 0;
		color2_blue = 0;
		color2_green = 0;

		for (int ii = 0; ii < 10; ii++)
		{
			stripBlock[ii].stripNumber = 0;
			stripBlock[ii].stripTeamId = 0;
		}

		manager_id = 0;
		stadium_id = 0;
	}

	bool operator==(const team_entry& rhs)
	{
		int ii;
		bool b_out = this->id==rhs.id;

		b_out = b_out && this->manager_id==rhs.manager_id;
		b_out = b_out && this->stadium_id==rhs.stadium_id;

		b_out = b_out && (wcscmp(this->name, rhs.name)==0);
		b_out = b_out && (strcmp(this->short_name, rhs.short_name)==0);
		for(ii=0;ii<this->team_max;ii++) b_out = b_out && (this->players[ii]==rhs.players[ii]);
		for(ii=0;ii<this->team_max;ii++) b_out = b_out && (this->numbers[ii]==rhs.numbers[ii]);
		b_out = b_out && this->captain_ind==rhs.captain_ind;

		b_out = b_out && this->color1_red==rhs.color1_red;
		b_out = b_out && this->color1_blue==rhs.color1_blue;
		b_out = b_out && this->color1_green==rhs.color1_green;
		b_out = b_out && this->color2_red==rhs.color2_red;
		b_out = b_out && this->color2_blue==rhs.color2_blue;
		b_out = b_out && this->color2_green==rhs.color2_green;

		return b_out;
	}
};


struct resize_info
{
	float scale;
	HDWP hdefer;
};


//Combobox item definitions

extern TCHAR* gpc_playstyle18[];
extern TCHAR* gpc_playstyle19[];
extern TCHAR* gpc_playstyle20[];
extern TCHAR* gpc_positions[];
extern TCHAR* gpc_pos_short[];

extern unsigned char n_playstyle16to1718[];
extern unsigned char n_playstyle1718to16[];
extern unsigned char n_playstyle16to19[];
extern unsigned char n_playstyle19to16[];
extern unsigned char n_playstyle16to2021[];
extern unsigned char n_playstyle2021to16[];
extern unsigned char n_playstyle1718to19[];
extern unsigned char n_playstyle19to1718[];
extern unsigned char n_playstyle1718to2021[];
extern unsigned char n_playstyle2021to1718[];
extern unsigned char n_playstyle19to2021[];
extern unsigned char n_playstyle2021to19[];

//Function prototypes
typedef std::unordered_map<int, int> appearance_map;

void build_appearance_map15(appearance_map&, int&, void*);
void read_player_entry15(player_entry&, int&, void*);
void read_appearance_entry15(player_entry&, appearance_map&, void*);
void read_team_ids15(team_entry&, int&, void*);
void read_team_rosters15(int&, void*, team_entry*, int);
void read_team_tactics15(int&, void*, team_entry*, int);
void write_player_entry15(player_entry, int&, appearance_map&, void*);
void write_team_info15(team_entry, int&, void*);
void write_teamplayer_info15(team_entry, int&, void*);
void write_team_tactics15(team_entry, int&, void*);

void fill_player_entry16(player_entry &, int &, void*);
void fill_appearance_entry16(player_entry &, int &, void*);
void fill_team_ids16(team_entry &, int &, void*);
void fill_team_rosters16(int &, void*, team_entry*, int);
void fill_team_tactics16(int &, void*, team_entry*, int);
void extract_player_entry16(player_entry, int &, int &, void*);
void extract_team_info16(team_entry, int &, void*);
void extract_teamplayer_info16(team_entry, int &, void*);
void extract_team_tactics16(team_entry, int &, void*);

void fill_player_entry17(player_entry &, int &, void*);
void fill_team_ids17(team_entry &, int &, void*);
void fill_team_rosters17(int &, void*, team_entry*, int);
void fill_team_tactics17(int &, void*, team_entry*, int);
void extract_player_entry17(player_entry, int &, void*);
void extract_team_info17(team_entry, int &, void*);
void extract_teamplayer_info17(team_entry, int &, void*);
void extract_team_tactics17(team_entry, int &, void*);

void fill_player_entry18(player_entry &, int &, void*);
void fill_team_ids18(team_entry &, int &, void*);
void fill_team_rosters18(int &, void*, team_entry*, int);
void fill_team_tactics18(int &, void*, team_entry*, int);
void extract_player_entry18(player_entry, int &, void*);
void extract_team_info18(team_entry, int &, void*);
void extract_teamplayer_info18(team_entry, int &, void*);
void extract_team_tactics18(team_entry, int &, void*);

void fill_player_entry19(player_entry &, int &, void*);
void fill_team_ids19(team_entry &, int &, void*);
void fill_team_rosters19(int &, void*, team_entry*, int);
void fill_team_tactics19(int &, void*, team_entry*, int);
void extract_player_entry19(player_entry, int &, void*);
void extract_team_info19(team_entry, int &, void*);
void extract_teamplayer_info19(team_entry, int &, void*);
void extract_team_tactics19(team_entry, int &, void*);

void fill_player_entry20(player_entry &, int &, void*);
void fill_team_ids20(team_entry &, int &, void*);
void fill_team_rosters20(int &, void*, team_entry*, int);
void fill_team_tactics20(int &, void*, team_entry*, int);
void extract_player_entry20(player_entry, int &, void*);
void extract_team_info20(team_entry, int &, void*);
void extract_teamplayer_info20(team_entry, int &, void*);
void extract_team_tactics20(team_entry, int &, void*);

void aatf_single(HWND, int, int, player_entry*, team_entry*, int);

void save_comparator(HWND, int, player_entry*, int, team_entry*, int, TCHAR*, void*);

//data_util.cpp functions
int read_data(int, int, int&, FileDescriptorNew*);
void write_data(int, int, int, int&, FileDescriptorNew*);
int read_dataOld(int, int, int&, FileDescriptorOld*);
void write_dataOld(int, int, int, int&, FileDescriptorOld*);
int read_data15(int, int, int&, FileDescriptor15*);
void write_data15(int, int, int, int&, FileDescriptor15*);

//fpc.cpp functions
void enable_fpc_invis_for_displayed_player(HWND, int);
void disable_fpc_invis_for_displayed_player(HWND, int);
void enable_fpc_invis_for_player(player_entry&, int);
void disable_fpc_invis_for_player(player_entry&, int);
