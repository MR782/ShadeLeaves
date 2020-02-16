#include "TitleUI.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

TitleUI::TitleUI()
{
	this->guide = nullptr;
	this->title_logo = nullptr;
}

void TitleUI::initialize()
{
	//メモリ確保
	this->guide = new TitleGuide();
	this->title_mv = std::make_unique<Movie>();
	this->title_logo = new TitleLogo();
	//確保できていないなら例外を投げる
	MemoryFunction::check_mem(this->guide);
	MemoryFunction::check_mem(this->title_logo);
	if (this->title_mv == nullptr)throw"TitleUI movie is null_ptr";
	
	//画像をセットする
	this->guide->initialize();
	this->title_logo->initialize();
	title_mv->set("reaf");
}

void TitleUI::finalize()
{
	delete this->guide;
	delete this->title_logo;
}

void TitleUI::update()
{
	this->guide->update();
}

void TitleUI::draw()
{
	//葉っぱの描画
	this->title_mv->draw();
	//座標決定
	//描画
	this->title_logo->draw();
	//UIの描画
	this->guide->draw(true);
}