#pragma once
#include"Object.h"
#include"BasicUI.h"

//�R���{����\������

class ComboLabel : public Object {
	Text combo_label_header;//Combo�Ƃ���������\������
	Text combo_label;//�R���{����\������
	int previous_miss_cnt;//1�t���[���O�̃~�X�̐����i�[����
	int current_miss_cnt;//��Ɨ̈�
	int font;
public:
	ComboLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
};