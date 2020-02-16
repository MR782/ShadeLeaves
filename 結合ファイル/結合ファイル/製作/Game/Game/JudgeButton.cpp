#include "JudgeButton.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"ScreenSystem.h"
#include"BasicUI.h"
#include"./dxlib/DxLib.h"

bool JudgeButton::judge()
{
	//キーが押されたか判定
	bool flag = false;
	switch (this->key) {
	case JudgeKey::Key_D:
		flag = KeyBoard::key_press(KEY_INPUT_D);
		break;
	case JudgeKey::Key_F:
		flag = KeyBoard::key_press(KEY_INPUT_F);
		break;
	case JudgeKey::Key_J:
		flag = KeyBoard::key_press(KEY_INPUT_J);
		break;
	case JudgeKey::Key_K:
		flag = KeyBoard::key_press(KEY_INPUT_K);
		break;
	}
	return flag;
}

JudgeButton::JudgeButton()
{
	this->position = Vector2();
	this->key = JudgeKey::Key_D;
}

void JudgeButton::initialize()
{
	//データの初期化
	this->position = Vector2();
	this->key = JudgeKey(0);
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "JudgeButton anime is null_ptr";//メモリ確保できていないなら例外を投げる
}

void JudgeButton::finalize()
{
	this->anime.reset();
}

void JudgeButton::update()
{
	//更新処理
	//押されているなら画像を変える
	if (is_pushed()) { 
		this->anime->set(this->graph_name["push"]);
	}
	else this->anime->set(this->graph_name["not_push"]);//押されていないなら画像を変える
}

void JudgeButton::set_contents(Vector2 pos, std::string name_[2], JudgeKey key_)
{
	//データ初期化
	this->position = pos;
	this->graph_name["not_push"] = name_[0];
	this->graph_name["push"] = name_[1];
	this->key = key_;
}

bool JudgeButton::is_pushed()
{
	return judge();
}
