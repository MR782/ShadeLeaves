#include "Ranking.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"
#include"Necessary.h"
#include"GraphicResource.h"
#include"BasicUI.h"

Ranking::Ranking()
{
	this->font_size = 0;
}

void Ranking::initialize()
{
	//�v���C�������U���g���e�L�X�g�ɕۑ�����
	switch (Necessary::get_music()) {
	case MusicList::fancie:
		//���x���ɓ����Ă���p�X����f�[�^��ǂݍ���
		this->data.input_textfile_data("./data/txt/rank_fan.txt");
		//�Q�[���̃X�R�A�������L���O�ɒǉ�
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_fan.txt");
		break;
	case MusicList::monoceros:
		//���x���ɓ����Ă���p�X����f�[�^��ǂݍ���
		this->data.input_textfile_data("./data/txt/rank_mono.txt");
		//�Q�[���̃X�R�A�������L���O�ɒǉ�
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_mono.txt");
		break;
	case MusicList::m3_500:
		//���x���ɓ����Ă���p�X����f�[�^��ǂݍ���
		this->data.input_textfile_data("./data/txt/rank_m3.txt");
		//�Q�[���̃X�R�A�������L���O�ɒǉ�
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_m3.txt");
		break;
	}
	//Top3�̃f�[�^�������Ă���
	this->rank_data = this->data.get_rank(5);
	//�e�L�X�g�̏�����
	this->font_size = 32;
	this->score_rank_label_header.set_font("%d : ", Point(), create_font(this->font_size, 16, false), setColor(Color::Black));
	this->score_rank_label.set_font("%d", Point(), create_font(this->font_size, 16, false), setColor(Color::Black));
}

void Ranking::finalize()
{
	this->rank_data.clear();
}

void Ranking::update()
{
	this->data.reset_ranking();
	//�I���y�Ȃɂ���ăX�R�A�\���̂��߂̃e�L�X�g�t�@�C�������ւ���
	switch (Necessary::get_music()) {
	case MusicList::fancie:	
		this->data.input_textfile_data("./data/txt/rank_fan.txt");	
		break;
	case MusicList::monoceros:
		this->data.input_textfile_data("./data/txt/rank_mono.txt");
		break;
	case MusicList::m3_500:
		this->data.input_textfile_data("./data/txt/rank_m3.txt");
	}
	this->rank_data = this->data.get_rank(5);
}

void Ranking::draw(Point pos)
{
	int cnt = 1;
	for (auto itr = this->rank_data.begin(); itr != this->rank_data.end(); itr++,cnt++) {
		//���W�Z�b�g
		this->score_rank_label_header.setPosition(Point(pos.x,pos.y + cnt * this->font_size));
		this->score_rank_label.setPosition(Point(pos.x + (this->score_rank_label_header.text_width * (font_size / 2)),pos.y + cnt * this->font_size));
		//�`��
		this->score_rank_label_header.drawformat_font(cnt);
		this->score_rank_label.drawformat_font((*itr).score);
	}
}
