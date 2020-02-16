#pragma once
#include<memory>

//キーボード入力を受け取る

class KeyBoard {
public:
	static void initialize();//初期化
	static void finalize();//終了処理
	static void update();//更新処理
	//キー操作
	static bool key_down(int);//押された瞬間
	static bool key_up(int);//離された瞬間
	static bool key_press(int);//押されている間
private:
	KeyBoard();
	static char* current;//キーボード対応
	static char* previous;//1フレーム前の配列を記憶
};