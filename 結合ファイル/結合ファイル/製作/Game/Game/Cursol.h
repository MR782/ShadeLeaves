#pragma once
#include"Object.h"

//�y�ȑI�����̃J�[�\��

class Cursol : public Object {
public:
	void initialize()override;
	void finalize()override;

	void set_position(Vector2 pos);//���W�Z�b�g
	void set_graph(std::string name);//�摜�Z�b�g
};