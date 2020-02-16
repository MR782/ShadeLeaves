#include "RankLabel.h"
#include"GameScene.h"
#include"ScreenSystem.h"
#include<string>
#include"./dxlib/DxLib.h"

RankLabel::RankLabel()
{
	this->draw_start_countor = 0;
}

void RankLabel::initialize()
{
	this->draw_start_countor = 0;
	const int font_size = 128;
	this->position = Vector2(ScreenData::width / 2 + font_size * 2, ScreenData::height / 2);
	//データの初期化
	Point pos = Point(this->position.x, this->position.y);
	this->rank_label.set_font(check_rank(), pos, create_font(font_size, 32, false), setColor(set_rankColor()));
	this->rank_label_header.set_font("Rank", Point(pos.x,pos.y - font_size / 4), create_font(font_size / 4, 16, false), setColor(Color::White));
}

void RankLabel::finalize()
{
	DeleteFontToHandle(this->rank_label.font);
	DeleteFontToHandle(this->rank_label_header.font);
}

void RankLabel::update()
{
	if (this->draw_start_countor >= 60) {
		const int rank_blend_speed = 6;
		if (this->b_state == BlendState::Addition)this->blend_cnt += rank_blend_speed;
	}
	this->draw_start_countor++;
	this->check_blendCnt();
}

void RankLabel::draw(bool a_blend)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->blend_cnt);//ブレンドモードを設定
	this->rank_label.draw_font();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードをオフ
	this->rank_label_header.draw_font();
}

bool RankLabel::check_scene_transition()
{
	return this->blend_cnt >= 255;
}

const char* RankLabel::check_rank()
{
	const int rankS_border = 90000;
	const int rankA_border = 70000;
	const int rankB_border = 50000;
	const int rankC_border = 0;
	//ランクをチェックする
	int game_score = Necessary::score;
	if (game_score < rankB_border)       return "C";
	else if (game_score < rankA_border)  return "B";
	else if (game_score < rankS_border)  return "A";
	else								 return "S";
	return "";
}

Color RankLabel::set_rankColor()
{
	const int rankS_border = 90000;
	const int rankA_border = 70000;
	const int rankB_border = 50000;
	const int rankC_border = 0;
	Color cl;
	int game_score = Necessary::score;
	if (game_score < rankB_border)       cl = Color::Gray;
	else if (game_score < rankA_border)  cl = Color::Blue;
	else if (game_score < rankS_border) cl = Color::Red;
	else						        cl = Color::Yellow;
	return cl;
}
