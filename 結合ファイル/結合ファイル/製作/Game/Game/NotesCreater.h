#pragma once
#include"Notes.h"
#include<vector>

class NotesCreater {
	std::map<std::string, std::string> filename;
	//�m�[�c�̎��
	enum class NotesKind {
		Push,//pushNotes
		Hold//HoldNotes
	};
	struct NotesData {
		JudgeKey j_key;//����L�[
		NotesKind kind;//�m�[�c�̎��
		float p_timing;//perfect�̃^�C�~���O
	};
	//���ʃf�[�^
	struct MusicalScore {
		std::string name;//���O
		std::vector<NotesData> notes;//�m�[�c�̏o���f�[�^
	};
	std::vector<MusicalScore> musical_score_datas;
	//�t�@�C������ǂݍ��񂾃f�[�^��vector�Ɋi�[����
	std::vector<NotesData> create_score(std::string name);
	//��ނƃ��[���ɂ���ăm�[�c�𐶐�����
	void create_note(JudgeKey jk,NotesKind nk,float pt);
public:
	void initialize();
	void finalize();
	//vector����f�[�^���������ăm�[�c�̔z���Ԃ�
	int get_all_notes_num(std::string name);
	void get_notes_data(std::string name);
};