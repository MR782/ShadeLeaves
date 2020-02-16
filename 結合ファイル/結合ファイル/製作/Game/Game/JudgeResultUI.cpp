#include "JudgeResultUI.h"
#include"SceneManager.h"

JudgeResultUI::JudgeResultUI()
{
	this->active_cnt = 0;
	this->lane = 0;
}

void JudgeResultUI::initialize()
{
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr) throw "JudgeResult anime is null_ptr";//�������m�ۂł��Ȃ������Ȃ��O
	//������
	this->position = Vector2();
	this->active_cnt = 0;
}

void JudgeResultUI::finalize()
{
	this->anime.reset();
}

void JudgeResultUI::update()
{
	this->active_cnt++;//�������߂Â�
	this->position.y--;//���X�ɏ�Ɉړ�����
}

bool JudgeResultUI::is_active()
{
	const int judgeUI_active_cnt = 60;//���茋�ʂ�`�悷��UI�̐����t���[����
	//�������Ă����true��Ԃ�
	return this->active_cnt < judgeUI_active_cnt;
}

void JudgeResultUI::set_lane(JudgeKey j_key)
{
	const int note_width = 64;
	const int judge_line_height = 16;
	//�o���ʒu���Z�b�g
	this->position = Vector2(Model::judge_line->get_position().x + (note_width * (int)j_key), 
						     Model::judge_line->get_position().y - (judge_line_height * 2));
}

void JudgeResultUI::set_graph(std::string name)
{
	//�摜���Z�b�g
	this->anime->set(name);
}