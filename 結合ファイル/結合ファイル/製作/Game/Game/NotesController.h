#pragma once
#include"Notes.h"
#include"JudgeResultCreater.h"

//���[�����Ƃ̃m�[�c����

class NotesController : public Object{
	//�������锻�茋�ʃG�t�F�N�g�̎��
	std::map<JudgeResult, std::string> effect_kind;
	//���茋�ʂ̐������u
	JudgeResultCreater* result_creater;
	//���_�l�ɒB���邽�߂̐�(���̐������m�[�c�������ꂽ��X�R�A��+1����)
	int counter_increment_1_score;

	std::map<std::string, std::vector<std::unique_ptr<Notes>>> lane_data;
	//�m�[�c�̍폜
	bool delete_notes(std::unique_ptr<Notes>& note);
	//�m�[�c��Update,Draw���Ă�(���[����)
	void callUpdate(std::vector<std::unique_ptr<Notes>>& lane);
	void callDraw(std::vector<std::unique_ptr<Notes>>& lane);

	//�X�R�A��ǉ�����
	void add_score(JudgeResult jr);
public:
	NotesController();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
};