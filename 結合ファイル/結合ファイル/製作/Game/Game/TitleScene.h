#pragma once
#include"TitleUI.h"

//ゲームが始まって最初に見せるシーン

class Title : public Scene{
	TitleUI* title_ui;
public:
	Title();
	void initialize();
	void finalize();
	void update();
	void draw();
};