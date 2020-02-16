#include "JudgeResultUI.h"
#include"SceneManager.h"

JudgeResultUI::JudgeResultUI()
{
	this->active_cnt = 0;
	this->lane = 0;
}

void JudgeResultUI::initialize()
{
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr) throw "JudgeResult anime is null_ptr";//メモリ確保できなかったなら例外
	//初期化
	this->position = Vector2();
	this->active_cnt = 0;
}

void JudgeResultUI::finalize()
{
	this->anime.reset();
}

void JudgeResultUI::update()
{
	this->active_cnt++;//死期が近づく
	this->position.y--;//徐々に上に移動する
}

bool JudgeResultUI::is_active()
{
	const int judgeUI_active_cnt = 60;//判定結果を描画するUIの生存フレーム数
	//生存している間trueを返す
	return this->active_cnt < judgeUI_active_cnt;
}

void JudgeResultUI::set_lane(JudgeKey j_key)
{
	const int note_width = 64;
	const int judge_line_height = 16;
	//出現位置をセット
	this->position = Vector2(Model::judge_line->get_position().x + (note_width * (int)j_key), 
						     Model::judge_line->get_position().y - (judge_line_height * 2));
}

void JudgeResultUI::set_graph(std::string name)
{
	//画像をセット
	this->anime->set(name);
}