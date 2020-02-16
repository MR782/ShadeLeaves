#include "KeyBoard.h"
#include"./dxlib/DxLib.h"

#define KEY_BOARD_BUF 256
//実体化
char* KeyBoard::current;
char* KeyBoard::previous;

void KeyBoard::initialize()
{
	//領域確保
	current = new char[KEY_BOARD_BUF];
	previous = new char[KEY_BOARD_BUF];
}

void KeyBoard::finalize()
{
	//領域開放
	delete[] current;
	delete[] previous;
}

void KeyBoard::update()
{
	//作業領域と１フレーム前の入れ替え
	static char* work;

	work = current;     
	current = previous;  
	previous = work;    

	GetHitKeyStateAll(current);
}

bool KeyBoard::key_down(int k_)
{
	//今は押されているが１フレーム前は押されていない
	return *(current + k_) == 1 && *(previous + k_) == 0;
}

bool KeyBoard::key_up(int k_)
{
	//今は押されていないが1フレーム前は押されていた
	return *(current + k_) == 0 && *(previous + k_) == 1;
}

bool KeyBoard::key_press(int k_)
{
	//今現在押されているなら
	return *(current + k_) == 1;
}