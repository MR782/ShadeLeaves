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
	//�f�[�^�̏�����
	const int fontsize = 32;
	const int thick = 16;
	const int default_fontsize = 16;
	this->font = create_font(fontsize, thick, false);
	//�t�H���g(�e�L�X�g)�쐬-----------------------------------
	this->combo_label_header.set_font("Combo",
		Point(ScreenData::width / 2 - ((this->combo_label_header.text_width * fontsize) / 2), ScreenData::height / 2 - fontsize),
		this->font, setColor(Color::Orange));
	//�R���{��
	this->combo_label.set_font("%d", Point(this->combo_label_header.pos.x, ScreenData::height / 2 + fontsize),
		this->font, setColor(Color::Orange));
	//---------------------------------------------
	this->current_miss_cnt = 0;
	this->previous_miss_cnt = 0;
}

void ComboLabel::finalize()
{
	//�t�H���g�f�[�^��j��
	DeleteFontToHandle(this->font);
}

void ComboLabel::update()
{
	//�̈����ւ�
	this->previous_miss_cnt = this->current_miss_cnt;
	this->current_miss_cnt = Counter::miss_cnt;
	//������̒������Ƃ�
	this->combo_label.text_width = (int)strlen(this->combo_label_header.str);
	//1�t���[���O�Ɣ�ׂă~�X�̐����Ⴄ�Ȃ�
	if (this->previous_miss_cnt != this->current_miss_cnt) {
		Counter::combo_cnt = 0;//�R���{��؂�
	}
}

void ComboLabel::draw(bool a_blend)
{
	this->combo_label_header.draw_font();//�����`�悷��
	//�R���{���\��
	std::string combonum = std::to_string(Counter::combo_cnt);
	this->combo_label.drawformat_font(Counter::combo_cnt);
}
