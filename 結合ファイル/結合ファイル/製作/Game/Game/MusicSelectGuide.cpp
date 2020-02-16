#include "MusicSelectGuide.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

void MusicSelectGuide::initialize()
{
	//�Œ�f�[�^�̒�`
	const int font_size = 16;
	//�t�H���g�̍쐬
	const char* msg = "DFJK ���x�ݒ�@���� �y�ȑI���@Enter ����";
	int str_len = (int)strlen(msg);
	this->guide_label.set_font(msg,
		Point(ScreenData::width / 2 - (str_len * (font_size / 2)) / 2, ScreenData::height - font_size),
		create_font(16, 15, false), setColor(Color::Black));
}

void MusicSelectGuide::finalize()
{
	//�t�H���g�폜
	DeleteFontToHandle(this->guide_label.font);
}

void MusicSelectGuide::draw(bool a_blend)
{
	this->guide_label.draw_font();
}
