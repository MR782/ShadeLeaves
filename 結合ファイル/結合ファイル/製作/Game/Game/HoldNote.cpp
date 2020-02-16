#include "HoldNote.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

JudgeResult HoldNotes::judge()
{
	JudgeResult jr = JudgeResult::none;
	//レーンの先頭出ないならまだ判定を行わない
	if (this->is_first == false) return jr;
	float absolute = abs(this->perfect_timing - this->key_down_timing);//絶対値を求める

	if (absolute <= 2) {
		//perfect判定をした音を鳴らす
		Audio::play("perfect");
		//perfect判定
		jr = JudgeResult::perfect;
	}
	//パーフェクトのタイミングが過ぎているなら
	else if (this->perfect_timing < Counter::game_cnt) {
		Audio::play("miss");
		jr = JudgeResult::miss;
	}
	return jr;
}

bool HoldNotes::check_key()
{
	bool check_key = false;
	//判定キーによって処理を変える---------------------
	switch (this->judge_key)
	{
	case JudgeKey::Key_D:
		check_key = KeyBoard::key_press(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		check_key = KeyBoard::key_press(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		check_key = KeyBoard::key_press(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		check_key = KeyBoard::key_press(KEY_INPUT_K);
		break;
	}
	return check_key;
}

void HoldNotes::initialize()
{
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr)throw "HoldNotes anime is null_ptr";//メモリ確保できていないなら例外を投げる
	this->anime->set("hold_notes");
}
