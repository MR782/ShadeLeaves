#include "JudgeLine.h"
#include"ScreenSystem.h"

void JudgeLine::initialize()
{
	//データの初期化
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "JudgeLine anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("judge_line");
	const int judge_line_width = 256;
	this->position = Vector2((ScreenData::width / 2) - (judge_line_width / 2), ScreenData::height / 6 * 5);
}

void JudgeLine::finalize()
{
	this->anime.reset();
}
