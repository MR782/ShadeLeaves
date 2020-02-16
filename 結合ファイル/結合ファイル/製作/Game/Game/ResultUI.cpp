#include "ResultUI.h"
#include"ScreenSystem.h"
#include"SceneManager.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

ResultUI::ResultUI()
{
	this->game_result = nullptr;
	this->guide = nullptr;
	this->rank = nullptr;
	this->scene_title = nullptr;
	this->score = nullptr;
	this->judgeResult_text = nullptr;
}

void ResultUI::initialize()
{
	//スコアUI--------------------------------------------------------------------------------------------
	this->score = new ScoreLabel();
	MemoryFunction::check_mem(this->score);
	this->score->set_position(Vector2(ScreenData::width / 3,ScreenData::height / 4));
	this->score->initialize();
	//ランク----------------------------------------------------------------------------------------------
	this->rank = new RankLabel();
	MemoryFunction::check_mem(this->rank);
	this->rank->initialize();
	//シーンタイトル--------------------------------------------------------------------------------
	this->scene_title = new ResultSceneTitle();
	MemoryFunction::check_mem(this->scene_title);
	this->scene_title->initialize();
	//ガイド-------------------------------------------------------------------------------------
	this->guide = new ResultGuide();
	MemoryFunction::check_mem(this->guide);
	this->guide->initialize();
	//フルコンボ表示------------------------------------------------------------------------------
	this->game_result = new GameResult();
	MemoryFunction::check_mem(this->guide);
	this->game_result->initialize();
	//リザルト-------------------------------------------------------------------------------------
	this->judgeResult_text = new JudgeResultText();
	MemoryFunction::check_mem(this->judgeResult_text);
	this->judgeResult_text->set_position(Vector2(ScreenData::width / 3,0));
	this->judgeResult_text->initialize();
	//ムービー--------------------------------------------------------------------------------------
	this->result_mv = std::make_unique<Movie>();
	if (this->result_mv == nullptr)throw"ResultUI movie is null_ptr";
	this->result_mv->set("reaf");
}

void ResultUI::finalize()
{
	//終了処理
	this->score->finalize();
	this->guide->finalize();
	this->scene_title->finalize();
	this->game_result->finalize();
	this->rank->finalize();
	this->judgeResult_text->finalize();
	//メモリ開放
	delete this->judgeResult_text;
	delete this->score;
	delete this->guide;
	delete this->scene_title;
	delete this->game_result;
	delete this->rank;
}

void ResultUI::update()
{
	this->guide->update();
	this->rank->update();
}

void ResultUI::draw()
{
	//葉っぱの描画
	this->result_mv->draw();
	//scenetitle--------------------------------------------------------
	this->scene_title->draw();
	//result--------------------------------------------------------------
	this->judgeResult_text->draw();
	//score---------------------------------------------------------------------
	this->score->draw();
	//rank-----------------------------------------------------------------------
	this->rank->draw();
	//fullcomb,AllPerfect表示-----------------------------------------------------
	this->game_result->draw();
	//guide-----------------------------------------------------------------------
	this->guide->draw(true);
}

bool ResultUI::IsSceneTransition()
{
	return this->rank->check_scene_transition();
}
