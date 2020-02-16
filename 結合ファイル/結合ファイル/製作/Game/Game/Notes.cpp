#include "Notes.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"GameScene.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

Notes::Notes() : Object()
{
	this->judge_key = JudgeKey::Key_D;
	this->judge_result = JudgeResult::none;
	this->key_down_timing = 0;
	this->is_first = false;
	this->perfect_timing = 0;
}

void Notes::initialize()
{
	throw" called super class method";
}

void Notes::finalize()
{
	this->anime.reset();
}

void Notes::update()
{
	move();
	//�����̔���L�[�������ꂽ�猻�݂̃Q�[���J�E���g���L�[���������^�C�~���O�Ƃ��ēo�^
	if (this->check_key()) {
		this->key_down_timing = Counter::game_cnt;
	}
	this->judge_result = this->judge();
}

void Notes::set_is_first(bool flag)
{
	this->is_first = flag;
}

JudgeResult Notes::get_result()
{
	return this->judge_result;
}

JudgeKey Notes::get_judge_key()
{
	return this->judge_key;
}

void Notes::set_contents(float timing, JudgeKey j_key)
{
	this->judge_key = j_key;
	//����L�[�ɂ���ď������W��ς���
	float posY = 0 + 1 * ((this->perfect_timing - Counter::game_cnt) * -(Model::judge_line->get_position().y) * 1);

	const int judge_line_width = 256;
	const int note_width = 64;
	this->position =
		Vector2((float)((ScreenData::width / 2) - (judge_line_width / 2) + (int)(this->judge_key)* note_width),
			             posY);
	//�ړ��ʂƃ^�C�~���O���Z�b�g����
	this->perfect_timing = timing;
}

void Notes::move()
{
	//�I�_�̈ʒu + �I�_����n�_�ւ̕��� * ((���胉�C���ɂ��鎞�� - �Ȃ̍Đ�����)*���[���̒���*�X�s�[�h);                                    
	float posY = Model::judge_line->get_position().y + ((this->perfect_timing - Counter::game_cnt)
		* -(Model::judge_line->get_position().y) * (0.001f * Necessary::speed));
	this->position.y = posY;
}

JudgeResult Notes::judge()
{
	throw"Called Parent's Method<Notes::judge()>";
	return JudgeResult::none;
}

bool Notes::check_key()
{
	bool check_key = false;
	//����L�[�ɂ���ď�����ς���---------------------
	switch (this->judge_key)
	{
	case JudgeKey::Key_D:
		check_key = KeyBoard::key_down(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		check_key = KeyBoard::key_down(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		check_key = KeyBoard::key_down(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		check_key = KeyBoard::key_down(KEY_INPUT_K);
		break;
	}
	return check_key;
}
