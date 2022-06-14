#ifndef __UTIL_H__
#define __UTIL_H__

///以下為各鍵值
const char KEY_ESC = 27;
const char KEY_LEFT = 0x25; // keyboard左箭頭
const char KEY_UP = 0x26; // keyboard上箭頭
const char KEY_RIGHT = 0x27; // keyboard右箭頭
const char KEY_DOWN = 0x28; // keyboard下箭頭
const char KEY_1 = 49;
const char KEY_2 = 50;
const char KEY_3 = 51;
const char KEY_4 = 52;
const char KEY_5 = 53;
const char KEY_6 = 54;
const char KEY_7 = 55;
const char KEY_W = 0x57;
const char KEY_A = 0x41;
const char KEY_S = 0x53;
const char KEY_D = 0x44;
const char KEY_E = 69;
const char KEY_Q = 81;
const char KEY_R = 82;
const char KEY_T = 84;
const char KEY_Y = 89;
const char KEY_U = 85;
const char KEY_H = 72;
const char KEY_G = 71;
const char KEY_P = 80;
const char KEY_SPACE = 0x20;
const char KEY_CTRL = 0x11;
const char KEY_TAB = 9;

// 定義各種音效的編號
enum AUDIO_ID
{				
	AUDIO_STARTMENU,
	AUDIO_CHOOSE,
	AUDIO_COOK,
	AUDIO_ATTACK_HU,
	AUDIO_MUSIC_01,
	AUDIO_MUSIC_02,
	AUDIO_MUSIC_03,
	AUDIO_MUSIC_04,
	AUDIO_MUSIC_05,
	AUDIO_MUSIC_06,
	AUDIO_MUSIC_07,
	AUDIO_VICTORY,
	AUDIO_LOSE,
	AUDIO_RECYCLE_CAN,
	AUDIO_POT,
	AUDIO_ROLL

};

// 定義各關卡的編號
enum BeginningStage
{
	stage_start_menu,
	stage_staff,
	stage_instructions
};

enum InstructionsPage
{
	instructions_page01,
	instructions_page02,
	instructions_page03,
	instructions_page_cheat
};

enum Stage
{
	stage_1,
	stage_2,
	stage_3,
	stage_4,
	stage_5,
	stage_6,
	stage_boss,
	stage_props,
	stage_game_complete
};

enum Action
{
	sleep_a,
	stand_a,
	walk_a,
	roll_a,
	jump_a,
	attack_a,
	hit_a,
	collide_a,
	thron_a
};

enum PropCase
{
	mosquito_jump_p,
	shrimp_blood_p,
	grass_fast_p,
	banana_attack_p,
	shrimp_attack_p,
	guava_juice_blood_p
};

enum SourceCase
{
	mosquito_jump_s,
	shrimp_blood_s,
	grass_fast_s,
	banana_attack_s,
	shrimp_attack_s,
	guava_juice_blood_s,
	green_sword_s
};

#endif