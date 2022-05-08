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
const char KEY_R = 82;
const char KEY_SPACE = 0x20;
const char KEY_CTRL = 0x11;

// 定義各關卡的編號
enum Stage
{
	stage_1,
	stage_boss,
	stage_props
};

enum Action
{
	stand_a,
	walk_a,
	roll_a,
	jump_a,
	attack_a
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
	guava_juice_blood_s
};

#endif