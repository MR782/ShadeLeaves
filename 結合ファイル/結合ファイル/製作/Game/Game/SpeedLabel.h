#pragma once
#include"Object.h"
#include"BasicUI.h"

class SpeedLabel : public Object {
	Text speed_label_header;//�����\��
	Text speed_label;//���݂̃X�s�[�h��\��
	int font;
public:
	SpeedLabel();
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};