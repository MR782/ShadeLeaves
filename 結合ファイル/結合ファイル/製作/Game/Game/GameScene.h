#pragma once
#include"NotesController.h"
#include"JudgeLine.h"
#include"NotesCreater.h"
#include"Scene.h"
#include"JudgeResultUI.h"
#include"JudgeResultEffect.h"
#include"GameUI.h"

class Game : public Scene{
	//ゲームシーン開始時間
	LARGE_INTEGER start_time;
	LARGE_INTEGER now_time;
	LARGE_INTEGER freq;
	//ノーツの生成装置
	NotesCreater *notes_creater;
	//ノーツコントローラー
	NotesController* notes_controller;
	//UI
	GameUI* game_ui;
	//メソッド
	//条件を満たしたオブジェクトをvectorから削除
	void delete_judge_resultUI();
	//条件を満たしたエフェクトを配列から削除
	void delete_judge_effect();
	//選択楽曲によって譜面データを入れる
	void set_musical_score();
	//音楽を再生する
	void start_music();
public:
	Game();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw()override;
};

namespace Counter {
	extern float game_cnt;//ゲームカウンタ
	extern int notes_num;//ノーツの合計数
	extern int combo_cnt;//コンボ数
	//ノーツの判定結果の数を格納
	extern int perfect_cnt;
	extern int good_cnt;
	extern int miss_cnt;
}

namespace Model {
	//ゲーム内オブジェクト(キャラクター)
	extern std::vector<std::unique_ptr<Notes>> notes;
	extern JudgeLine* judge_line;
	extern std::vector<std::unique_ptr<JudgeResultUI>> judge_results;
	extern std::vector<std::unique_ptr<Effect>> effects;
}