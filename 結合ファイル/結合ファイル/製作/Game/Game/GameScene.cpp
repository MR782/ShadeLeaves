#include "GameScene.h"
#include"Necessary.h"
#include"Audio.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

#include<time.h>
#include <windows.h>

//カウンタ
float Counter::game_cnt;
int Counter::perfect_cnt;
int Counter::good_cnt;
int Counter::miss_cnt;
int Counter::notes_num;
int Counter::combo_cnt;
//モデル
std::vector<std::unique_ptr<Notes>> Model::notes;
JudgeLine* Model::judge_line;
std::vector<std::unique_ptr<JudgeResultUI>> Model::judge_results;
std::vector<std::unique_ptr<Effect>> Model::effects;

Game::Game() :Scene()
{
	this->notes_controller = nullptr;
	this->game_ui = nullptr;
	this->notes_creater = nullptr;
	this->start_time.QuadPart = 0;
	this->now_time.QuadPart = 0;
	this->freq.QuadPart = 0;
}

void Game::initialize()
{
	//データ削除
	Model::notes.clear();
	Model::effects.clear();
	Model::judge_results.clear();
	//リソースの読み込み
	Audio::load("game");

	//メモリ確保 - メモリ確保できていないなら例外を投げる
	//判定ライン------------------------------------------------------------------
	Model::judge_line = new JudgeLine();
	MemoryFunction::check_mem(Model::judge_line);
	//UIの初期化
	this->game_ui = new GameUI();
	MemoryFunction::check_mem(this->game_ui);
	//ノーツの生成装置----------------------------------------------------------------
	this->notes_creater = new NotesCreater();
	MemoryFunction::check_mem(notes_creater);
	//ノーツコントローラー----------------------------------------------------------
	this->notes_controller = new NotesController();
	MemoryFunction::check_mem(this->notes_controller);
	//オブジェクトの初期化
	Model::judge_line->initialize();//判定ラインの初期化
	this->notes_creater->initialize();
	this->game_ui->initialize();//UIの初期化
	//選択楽曲によって読み込むデータを変える
	set_musical_score();
	this->notes_controller->initialize();

	//カウンタの初期化-----------------------------------------------------------------
	QueryPerformanceFrequency(&this->freq);
	QueryPerformanceCounter(&this->start_time);
	QueryPerformanceCounter(&this->now_time);

	Counter::game_cnt = 0;
	Counter::perfect_cnt = 0;
	Counter::good_cnt = 0;
	Counter::miss_cnt = 0;
	Counter::combo_cnt = 0;
	Necessary::score = 0;//スコアの初期化
	//画像をセット
	std::string graph_name = "";
	switch (Necessary::get_music()) {
	case MusicList::fancie:
		graph_name = "Fancie_BG";
		break;
	case MusicList::monoceros:
		graph_name = "monoceros_BG";
		break;
	case MusicList::m3_500:
		graph_name = "M3_BG";
		break;
	default:
		throw("不明な値が入っている MusicList -> GameScene");
	}
	this->back_graph_handle = GraphicResource::get_handle(graph_name)[0];

	start_music();
}

void Game::finalize()
{
	Model::judge_line->finalize();
	this->notes_creater->finalize();
	this->game_ui->finalize();
	this->notes_controller->finalize();
	//メモリ開放
	Model::judge_results.clear();
	Model::notes.clear();
	Model::effects.clear();

	delete Model::judge_line;
	delete this->notes_creater;
	delete this->game_ui;
	delete this->notes_controller;
}

void Game::update()
{
	//ゲームカウンタの更新
	QueryPerformanceCounter(&this->now_time);
	//マイクロ秒からミリ秒に変換してフレームに変換
	Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//フレーム単位に変換
	//ノーツの更新処理
	this->notes_controller->update();
	//判定結果
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->update();
	}
	//エフェクトの更新処理
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		(*itr)->update();
	}
	//判定結果を可視化するUIの削除処理
	delete_judge_resultUI();
	//エフェクトの削除処理
	delete_judge_effect();
	//判定ラインの更新処理
	Model::judge_line->update();
	//UIの更新処理
	this->game_ui->update();

	//曲が終了したらフェードアウト開始----------------------
	if (Audio::check_play_scope("game") == false) {
		Necessary::set_fade_ioFlag(true);
	}
	//暗転しきったら
	if (ScreenFunction::check_blend_max()) {
		//フェードインを行うよう指示を出す
		Necessary::set_fade_ioFlag(false);
		//シーンを切り替える
		scene_manager->change_scene(SceneData::result);
	}
}

void Game::draw()
{
	//背景の拡縮描画
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//レーンの描画-------------------------------------------------------------
	const int judge_lineX = (int)Model::judge_line->get_position().x;
	const int judge_lineY = (int)Model::judge_line->get_position().y;
	const int judge_line_width = 256;
	const int judge_line_height = 16;
	const int buttonNum = 4;//判定ボタンの数
	const int note_width = 64;
	DrawBox(judge_lineX, 0, judge_lineX + judge_line_width, judge_lineY, setColor(Color::Black), TRUE);
	for (int i = 0; i <= buttonNum; i++) {
		DrawLine(judge_lineX + note_width * i, 0,
			judge_lineX + note_width * i,
			judge_lineY + judge_line_height,
			setColor(Color::White));
	}
	//判定ラインの描画---------------------------------------------------------
	Model::judge_line->draw();
	//ノーツの描画
	this->notes_controller->draw();
	//UIの描画
	this->game_ui->draw();
	//判定結果
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->draw();
	}
	//エフェクトの描画処理
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		(*itr)->draw();
	}
}

void Game::delete_judge_resultUI()
{
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		//存在するべきではないなら
		if ((*itr)->is_active() == false) {
			//配列から削除
			Model::judge_results.erase(itr);
			break;
		}
	}
}

void Game::delete_judge_effect()
{
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		const int judge_result_effect_active_cnt = 30;
		if ((*itr)->is_death(judge_result_effect_active_cnt)) {
			Model::effects.erase(itr);
			break;
		}
	}
}

void Game::set_musical_score()
{
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		this->notes_creater->get_notes_data("monoceros");
		Counter::notes_num = notes_creater->get_all_notes_num("monoceros");
		break;
	case MusicList::fancie:
		this->notes_creater->get_notes_data("fancie");
		Counter::notes_num = notes_creater->get_all_notes_num("fancie");
		break;
	case MusicList::m3_500:
		this->notes_creater->get_notes_data("m3_500");
		Counter::notes_num = notes_creater->get_all_notes_num("m3_500");
		break;
	default:
		throw("譜面セット時に楽曲に無効な値が入っている");
	}
}

void Game::start_music()
{
	//楽曲選択に基づいて変える
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Audio::play("monoceros");
		break;
	case MusicList::fancie:
		Audio::play("fancie");
		break;
	case MusicList::m3_500:
		Audio::play("m3_500");	
		break;
	default:
		throw "楽曲に無効な値が入っている";
	}
}
