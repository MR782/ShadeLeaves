#pragma once
#include"TitleUI.h"

//�Q�[�����n�܂��čŏ��Ɍ�����V�[��

class Title : public Scene{
	TitleUI* title_ui;
public:
	Title();
	void initialize();
	void finalize();
	void update();
	void draw();
};