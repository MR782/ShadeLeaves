#pragma once
#include"Notes.h"

class JudgeResultUI : public Object {
	int active_cnt;//1�b�ԑ��݂���
	int lane;//�o�����郌�[��
public:
	JudgeResultUI();
	void initialize();
	void finalize();
	void update();

	bool is_active();//��������ׂ����m�F���邽�߂̃��\�b�h
	void set_lane(JudgeKey j_key);//�����̏o�����[�����Z�b�g
	void set_graph(std::string name);//�摜���Z�b�g����
};