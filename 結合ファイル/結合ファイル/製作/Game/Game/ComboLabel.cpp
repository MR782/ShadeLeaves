#include "ComboLabel.h"
#include"ScreenSystem.h"
#include"SceneManager.h"
#include"dxlib/DxLib.h"

ComboLabel::ComboLabel()
{
	this->font = 0;
	this->previous_miss_cnt = 0;
	this->current_miss_cnt = 0;
}

void ComboLabel::initialize()
{
	//データの初期化
	const int fontsize = 32;
	const int thick = 16;
	const int default_fontsize = 16;
	this->font = create_font(fontsize, thick, false);
	//フォント(テキスト)作成-----------------------------------
	this->combo_label_header.set_font("Combo",
		Point(ScreenData::width / 2 - ((this->combo_label_header.text_width * fontsize) / 2), ScreenData::height / 2 - fontsize),
		this->font, setColor(Color::Orange));
	//コンボ数
	this->combo_label.set_font("%d", Point(this->combo_label_header.pos.x, ScreenData::height / 2 + fontsize),
		this->font, setColor(Color::Orange));
	//---------------------------------------------
	this->current_miss_cnt = 0;
	this->previous_miss_cnt = 0;
}

void ComboLabel::finalize()
{
	//フォントデータを破棄
	DeleteFontToHandle(this->font);
}

void ComboLabel::update()
{
	//領域入れ替え
	this->previous_miss_cnt = this->current_miss_cnt;
	this->current_miss_cnt = Counter::miss_cnt;
	//文字列の長さをとる
	this->combo_label.text_width = (int)strlen(this->combo_label_header.str);
	//1フレーム前と比べてミスの数が違うなら
	if (this->previous_miss_cnt != this->current_miss_cnt) {
		Counter::combo_cnt = 0;//コンボを切る
	}
}

void ComboLabel::draw(bool a_blend)
{
	this->combo_label_header.draw_font();//文字描画する
	//コンボ数表示
	std::string combonum = std::to_string(Counter::combo_cnt);
	this->combo_label.drawformat_font(Counter::combo_cnt);
}
