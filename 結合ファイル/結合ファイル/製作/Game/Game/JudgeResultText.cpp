#include "JudgeResultText.h"
#include "GameScene.h"
#include"ScreenSystem.h"
#include "./dxlib/DxLib.h"

JudgeResultText::JudgeResultText()
{
	this->font = 0;
}

void JudgeResultText::initialize()
{
	const int result_num = 3;
	const int font_size = 32;
	this->font = create_font(font_size, 16, false);

	std::vector<Point> pos_datas;
	//データ---------------------------------
	for (int cnt = 0; cnt < result_num; cnt++) {
		const int ui_graph_height = 45;
		Point pos((ScreenData::width / 20) + (int)this->position.x,
			(ScreenData::height / 2) + (cnt * ui_graph_height) + (int)this->position.y);
		pos_datas.push_back(pos);
	}
	//ヘッダー-------------------------------
	Text perfect_label_header;
	perfect_label_header.set_font("Perfect : ", pos_datas.at(0), font, setColor(Color::Yellow));
	Text good_label_header;
	good_label_header.set_font("Good    : ", pos_datas.at(1), font, setColor(Color::Blue));
	Text miss_label_header;
	miss_label_header.set_font("Miss    : ", pos_datas.at(2), font, setColor(Color::Gray));

	this->result_header.push_back(perfect_label_header);
	this->result_header.push_back(good_label_header);
	this->result_header.push_back(miss_label_header);
	//データ---------------------------------
	
	Text perfect_label;
	perfect_label.set_font("%d",
		Point(perfect_label_header.pos.x + (font_size * (perfect_label_header.text_width / 2)), perfect_label_header.pos.y),
		font, setColor(Color::White));
	Text good_label;
	good_label.set_font("%d",
		Point(good_label_header.pos.x + (font_size * (good_label_header.text_width / 2)), good_label_header.pos.y),
		font, setColor(Color::White));
	Text miss_label;
	miss_label.set_font("%d",
		Point(miss_label_header.pos.x + (font_size * (miss_label_header.text_width / 2)), miss_label_header.pos.y),
		font, setColor(Color::White));

	this->result.push_back(perfect_label);
	this->result.push_back(good_label);
	this->result.push_back(miss_label);
	pos_datas.clear();
}

void JudgeResultText::finalize()
{
	DeleteFontToHandle(this->font);
	this->result.clear();
	this->result_header.clear();
}

void JudgeResultText::draw(bool a_blend)
{
	const int result_num = 3;
	for (auto header : this->result_header) {
		header.draw_font();
	}
	int cnt[3] = { Counter::perfect_cnt,Counter::good_cnt,Counter::miss_cnt };
	int i = 0;
	for (auto itr = this->result.begin(); itr != this->result.end(); itr++,i++) {
		if (i > 3) break;
		(*itr).drawformat_font(cnt[i]);
	}
}
