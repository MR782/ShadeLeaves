#pragma once
#include"Notes.h"
#include"JudgeResultCreater.h"

//レーンごとのノーツ処理

class NotesController : public Object{
	//生成する判定結果エフェクトの種類
	std::map<JudgeResult, std::string> effect_kind;
	//判定結果の生成装置
	JudgeResultCreater* result_creater;
	//理論値に達するための数(この数だけノーツが消されたらスコアに+1する)
	int counter_increment_1_score;

	std::map<std::string, std::vector<std::unique_ptr<Notes>>> lane_data;
	//ノーツの削除
	bool delete_notes(std::unique_ptr<Notes>& note);
	//ノーツのUpdate,Drawを呼ぶ(レーン分)
	void callUpdate(std::vector<std::unique_ptr<Notes>>& lane);
	void callDraw(std::vector<std::unique_ptr<Notes>>& lane);

	//スコアを追加する
	void add_score(JudgeResult jr);
public:
	NotesController();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
};