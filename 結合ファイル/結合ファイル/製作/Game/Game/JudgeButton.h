#pragma once
#include"Object.h"
#include"Notes.h"

//������s���L�[�̃{�^����\��

class JudgeButton : public Object {
	JudgeKey key;//���g�̃L�[
	std::map<std::string, std::string> graph_name;//������Ă����ԂƂ���Ă��Ȃ���ԂňႤ�摜���g�p

	bool judge();//�����̃L�[�̃{�^����������Ă��邩
public:
	JudgeButton();
	void initialize()override;
	void finalize()override;
	void update()override;
	//���̃N���X�ŏ��������邽�߂̊֐�
	void set_contents(Vector2 pos, std::string name_[2], JudgeKey key_);
	//������������Ă��邩
	bool is_pushed();
};