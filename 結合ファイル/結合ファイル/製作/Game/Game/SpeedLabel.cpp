#include "SpeedLabel.h"
#include"Necessary.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

SpeedLabel::SpeedLabel()
{
	this->font = 0;
}

void SpeedLabel::initialize()
{
	const int font_size = 32;
	this->font = create_font(32, 16, false);
	
	const char* msg = "Speed : ";
	int str_len = (int)strlen(msg);
	//文字
	this->speed_label_header.set_font("Speed : ",
		Point((ScreenData::width / 2) - ((font_size * (str_len / 2))), ScreenData::height - (font_size * 2)),
		this->font, setColor(Color::Black));
	//スピード表示
	this->speed_label.set_font(" %d",
		Point(this->speed_label_header.pos.x + (font_size * (this->speed_label_header.text_width / 2)), this->speed_label_header.pos.y),
		this->font, setColor(Color::Black));
}

void SpeedLabel::finalize()
{
	DeleteFontToHandle(this->font);
}

void SpeedLabel::draw(bool a_blend)
{
	this->speed_label_header.draw_font();
	this->speed_label.drawformat_font(Necessary::speed);
}
