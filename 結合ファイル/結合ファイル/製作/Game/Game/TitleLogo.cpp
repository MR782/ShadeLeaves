#include "TitleLogo.h"
#include"ScreenSystem.h"

void TitleLogo::initialize()
{
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "TitleLogo anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("title_logo");

	const int logo_width = 768;//画像の大きさ(ドット単位)
	this->position = Vector2((ScreenData::width / 2.0f) - (logo_width / 2.0f), (ScreenData::height / 4.0f));
}

void TitleLogo::finalize()
{
	this->anime.reset();
}