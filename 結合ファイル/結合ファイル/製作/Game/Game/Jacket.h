#pragma once
#include"Object.h"

//�W���P�b�g�摜��\��

class Jacket : public Object {
	void change_jacket();//�I���y�Ȃɉ����ĉ摜��؂�ւ���
	std::string now_select;//�I�𒆂̊y��
	std::string pre_select;//1�t���[���O�̑I���y��
public:
	void initialize()override;
	void finalize()override;
	void update()override;
};