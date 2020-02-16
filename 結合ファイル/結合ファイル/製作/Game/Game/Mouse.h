#pragma once
#include"Purpose.h"

//マウス入力を受け取る

class Mouse {
	//左クリック用
	static int left_previous;//1フレーム前
	static int left_current;//作業領域
	//右クリック用
	static int right_previous;//1フレーム前
	static int right_current;//作業領域
public:
	static void initialize();
	static void update();
	//左クリック用
	static bool left_click_down();
	static bool left_click_up();
	static bool left_click_press();
	static bool left_click_not_press();
	//右クリック用
	static bool right_click_down();
	static bool right_click_up();
	static bool right_click_press();
	static bool right_click_not_press();
};