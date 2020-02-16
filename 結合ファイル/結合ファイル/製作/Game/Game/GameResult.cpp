#include "GameResult.h"
#include"ScreenSystem.h"
#include"SceneManager.h"

void GameResult::initialize()
{
	//�f�[�^������
	//�~�X����0��
	char* s = const_cast<char*>("");
	if (Counter::miss_cnt == 0) {
		//good��0�Ȃ�
		if (Counter::good_cnt == 0) {
			//AllPerfect�Ƃ���
			s = const_cast<char*>("All Perfect");
		}
		//good������Ȃ�
		else {
			//FullCombo�ƕ\��
			s = const_cast<char*>("Full Combo");
		}
	}
	int str_size = (int)strlen(s);
	const int font_size = 32;
	this->position = Vector2(ScreenData::width / 2 + (str_size * font_size) / 2,
		ScreenData::height / 2 + font_size * 4);
	Point pos = Point(this->position.x,this->position.y);
	this->game_result_text.set_font(s, pos, create_font(font_size, 16, false), setColor(Color::Yellow));

	//�N���A���\��----------------------------------------
	this->anime = std::make_unique<Animation>();
	switch (Necessary::clear_flag) {
	case true:
		this->anime->set("Clear");
		break;
	case false:
		this->anime->set("Failed");
		break;
	}
	const int graph_height = 64;
	const int graph_width = 256;
	this->position = Vector2(ScreenData::width / 2 + graph_width / 2,ScreenData::height / 3 - graph_height / 2);
	//--------------------------------------------------
}

void GameResult::finalize()
{
	DeleteFontToHandle(this->game_result_text.font);
}

void GameResult::draw(bool a_blend)
{
	this->game_result_text.draw_font();
	this->anime->draw_anime(this->position);
}
