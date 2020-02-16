#include "MusicSelectGuide.h"
#include"ScreenSystem.h"
#include<string.h>
#include"./dxlib/DxLib.h"

void MusicSelectGuide::initialize()
{
	//固定データの定義
	const int font_size = 16;
	//フォントの作成
	const char* msg = "DFJK 速度設定　←→ 楽曲選択　Enter 決定";
	int str_len = (int)strlen(msg);
	this->guide_label.set_font(msg,
		Point(ScreenData::width / 2 - (str_len * (font_size / 2)) / 2, ScreenData::height - font_size),
		create_font(16, 15, false), setColor(Color::Black));
}

void MusicSelectGuide::finalize()
{
	//フォント削除
	DeleteFontToHandle(this->guide_label.font);
}

void MusicSelectGuide::draw(bool a_blend)
{
	this->guide_label.draw_font();
}
