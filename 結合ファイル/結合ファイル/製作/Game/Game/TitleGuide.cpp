#include "TitleGuide.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

TitleGuide::TitleGuide()
{
	this->blend_cnt = 0;
	this->b_state = BlendState::Subtraction;
}

void TitleGuide::initialize()
{
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "TitleGuide anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("title_ui");

	const int titleLabel_width = 512;//画像の大きさ(ドット単位)
	this->position = Vector2((ScreenData::width / 2.0f) - (titleLabel_width / 2.0f), (ScreenData::height / 3.0f) * 2.0f);
	//データの初期化
	this->blend_cnt = 255;
	this->b_state = BlendState::Subtraction;
}

void TitleGuide::finalize()
{
	this->anime.reset();
}

void TitleGuide::update()
{
	const int blend_speed = 5;//点滅スピード
	//αブレンド用のカウンタ
	if (this->b_state == BlendState::Addition) this->blend_cnt += blend_speed;
	else if (this->b_state == BlendState::Subtraction) this->blend_cnt -= blend_speed;
	check_blendCnt();
}