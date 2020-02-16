#pragma once
#include"Notes.h"
#include<vector>

class NotesCreater {
	std::map<std::string, std::string> filename;
	//ノーツの種類
	enum class NotesKind {
		Push,//pushNotes
		Hold//HoldNotes
	};
	struct NotesData {
		JudgeKey j_key;//判定キー
		NotesKind kind;//ノーツの種類
		float p_timing;//perfectのタイミング
	};
	//譜面データ
	struct MusicalScore {
		std::string name;//名前
		std::vector<NotesData> notes;//ノーツの出現データ
	};
	std::vector<MusicalScore> musical_score_datas;
	//ファイルから読み込んだデータをvectorに格納する
	std::vector<NotesData> create_score(std::string name);
	//種類とレーンによってノーツを生成する
	void create_note(JudgeKey jk,NotesKind nk,float pt);
public:
	void initialize();
	void finalize();
	//vectorからデータを検索してノーツの配列を返す
	int get_all_notes_num(std::string name);
	void get_notes_data(std::string name);
};