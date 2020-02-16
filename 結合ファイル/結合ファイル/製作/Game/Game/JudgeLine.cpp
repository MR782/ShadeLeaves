#include "JudgeLine.h"
#include"ScreenSystem.h"

void JudgeLine::initialize()
{
	//�f�[�^�̏�����
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "JudgeLine anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("judge_line");
	const int judge_line_width = 256;
	this->position = Vector2((ScreenData::width / 2) - (judge_line_width / 2), ScreenData::height / 6 * 5);
}

void JudgeLine::finalize()
{
	this->anime.reset();
}
