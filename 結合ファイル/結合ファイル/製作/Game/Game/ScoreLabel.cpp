#include "ScoreLabel.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"./dxlib/DxLib.h"

ScoreLabel::ScoreLabel()
{
	this->font = 0;
	this->head_font = 0;
}

void ScoreLabel::initialize()
{
	const int font_size = 64;
	this->font = create_font(font_size, 16, false);
	//‰Šú‰»
	this->score_label_header.set_font("SCORE", Point(ScreenData::width / 20 + int(this->position.x),(ScreenData::height / 20) + (int)this->position.y),
		this->font, setColor(Color::Gray));
	this->score_label.set_font("%d",
		Point(ScreenData::width / 20 + (int)this->position.x, this->score_label_header.pos.y + font_size),
		this->font, setColor(Color::White));
}

void ScoreLabel::finalize()
{
	DeleteFontToHandle(this->font);
}

void ScoreLabel::draw(bool a_blend)
{
	this->score_label_header.draw_font();
	this->score_label.drawformat_font(Necessary::score);
}