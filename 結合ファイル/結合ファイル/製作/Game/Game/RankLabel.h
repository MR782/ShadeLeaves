#pragma once
#include"Object.h"
#include"BasicUI.h"

//�Q�[�����ʂ̃����N�\��

class RankLabel : public Object {
	const char* check_rank();//�Q�[���̃X�R�A�Ń����N��t����
	Color set_rankColor();
	Text rank_label;
	Text rank_label_header;
	int		draw_start_countor;	//�`��J�n�̃J�E���^�[
public:
	RankLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
	bool check_scene_transition();
};