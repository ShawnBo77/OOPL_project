#ifndef UTIL_H
#define UTIL_H

///以下為各鍵值
const char KEY_ESC = 27;
const char KEY_LEFT = 0x25; // keyboard左箭頭
const char KEY_UP = 0x26; // keyboard上箭頭
const char KEY_RIGHT = 0x27; // keyboard右箭頭
const char KEY_DOWN = 0x28; // keyboard下箭頭
const char KEY_W = 0x57;
const char KEY_A = 0x41;
const char KEY_S = 0x53;
const char KEY_D = 0x44;
const char KEY_E = 0x69;
const char KEY_SPACE = 0x20;
const char KEY_SHIFT = 0x10;

// 定義各關卡的編號
enum Stage {
	stage_boss,
	stage_props
};

#endif