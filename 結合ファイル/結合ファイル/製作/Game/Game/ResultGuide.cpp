#include "ResultGuide.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

ResultGuide::ResultGuide()
{
	this->blend_cnt = 255;
	this->b_state = BlendState::Subtraction;
}

void ResultGuide::initialize()
{
	const int result_guide_width = 284;//�摜�̑傫��(�h�b�g�P��)
	const int result_guide_height = 64;//�摜�̑傫��(�h�b�g�P��)
	//�f�[�^������
	this->blend_cnt = 255;
	this->b_state = BlendState::Subtraction;
	this->position = Vector2(ScreenData::width / 2 - result_guide_width / 2, ScreenData::height - result_guide_height * 2);
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr) throw "ResultGuide anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("result_guide");
}

void ResultGuide::finalize()
{
	this->anime.reset();
}

void ResultGuide::update()
{
	//���u�����h�p�̃J�E���^
	const int blend_speed = 5;//�_�ŃX�s�[�h
	if (this->b_state == BlendState::Addition) this->blend_cnt += blend_speed;
	else if (this->b_state == BlendState::Subtraction) this->blend_cnt -= blend_speed;
	check_blendCnt();
}
