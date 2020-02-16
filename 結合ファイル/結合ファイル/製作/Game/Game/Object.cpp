#include "Object.h"
#include"./dxlib/DxLib.h"

void Object::check_blendCnt()
{
	if (this->blend_cnt >= 255) this->b_state = BlendState::Subtraction;//Max�܂ł������猸���J�n
	else if (this->blend_cnt <= 0) this->b_state = BlendState::Addition;//Min�܂ōs�����瑝���J�n
}

Object::Object()
{
	this->blend_cnt = 0;
	this->b_state = BlendState::Subtraction;
}

void Object::update()
{
}

void Object::draw(bool a_blend)
{
	if (this->anime == nullptr) throw "anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	if(a_blend) SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->blend_cnt);//�u�����h���[�h��ݒ�
	this->anime->draw_anime(this->position);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�u�����h���[�h���I�t
}

void Object::set_position(Vector2 pos)
{
	this->position = pos;
}

Vector2 Object::get_position()
{
	return this->position;
}
