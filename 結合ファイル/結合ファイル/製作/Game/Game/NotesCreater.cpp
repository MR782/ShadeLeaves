#include "NotesCreater.h"
#include"Necessary.h"
#include<fstream>
#include"GameScene.h"
#include"Necessary.h"
#include"PushNote.h"
#include"HoldNote.h"
#include<iostream>

void NotesCreater::initialize()
{
	this->filename["monoceros"] = "monoceros.txt";
	this->filename["fancie"] = "tenga.txt";
	this->filename["m3_500"] = "m3_500yen.txt";
	//vectorに要素追加
	for (auto itr = this->filename.begin(); itr != this->filename.end(); itr++) {
		NotesCreater::MusicalScore ms;
		ms.name = (*itr).first;//名前
		ms.notes = create_score("./data/txt/" + this->filename[ms.name]);//ファイルを呼んでデータを入れる
		//vectorに格納
		this->musical_score_datas.push_back(ms);
	}
}

void NotesCreater::finalize()
{
	this->filename.clear();
	for (auto itr = this->musical_score_datas.begin(); itr != this->musical_score_datas.end(); itr++) {
		(*itr).notes.clear();
	}
	this->musical_score_datas.clear();
}

std::vector<NotesCreater::NotesData> NotesCreater::create_score(std::string name)
{
	//テキストファイルからデータを受け取りNotesDataのvectorに入れていく
	std::ifstream file(name);
	//ファイルがないなら例外処理を流す
	if (file.fail()) throw("txt file is not found");
	//データを格納する
	std::vector<NotesData> notes_data;
	notes_data.clear();
	//ファイルから読み込んだデータをvectorに登録する
	while (!file.eof()) {
		NotesData n_data;
		int kind;
		int rane;
		float p_timing;
		//ファイルからデータをとってくる
		file >> kind >> rane >> p_timing;
		NotesKind n_kind = NotesKind(kind);
		JudgeKey j_key = JudgeKey(rane);
		//値を格納
		n_data.j_key = j_key;
		n_data.kind = n_kind;
		n_data.p_timing = p_timing;
		//vectorに格納
		notes_data.push_back(n_data);
	}
	file.close();

	return notes_data;
}

void NotesCreater::create_note(JudgeKey jk, NotesKind nk,float pt)
{
	std::unique_ptr<Notes> note = nullptr;
	//種類によって生成するオブジェクトを変える
	switch (nk)
	{
	case NotesKind::Hold:
		note = std::make_unique<HoldNotes>();
		break;
	case NotesKind::Push:
		note = std::make_unique<PushNotes>();
		break;
	default:
		throw "memory is nothing";
	}
	//データ初期化
	note->initialize();
	note->set_contents(pt, jk);
	//メモリの所有権移動
	Model::notes.push_back(std::move(note));
}

int NotesCreater::get_all_notes_num(std::string name)
{
	int note_num = 0;
	for (auto itr : musical_score_datas) {
		if (itr.name == name) {
			note_num = (int)itr.notes.size();
		}
	}
	return note_num;
}

void NotesCreater::get_notes_data(std::string name)
{
	for (auto itr = this->musical_score_datas.begin(); itr != this->musical_score_datas.end(); itr++) {
		if ((*itr).name == name) {
			for (auto itr2 = (*itr).notes.begin(); itr2 != (*itr).notes.end(); itr2++) {
				create_note((*itr2).j_key, (*itr2).kind, (*itr2).p_timing);
			}
			break;
		}
	}
}