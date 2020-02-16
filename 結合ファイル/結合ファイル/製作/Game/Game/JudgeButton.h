#pragma once
#include"Object.h"
#include"Notes.h"

//判定を行うキーのボタンを表示

class JudgeButton : public Object {
	JudgeKey key;//自身のキー
	std::map<std::string, std::string> graph_name;//押されている状態とされていない状態で違う画像を使用

	bool judge();//自分のキーのボタンが押されているか
public:
	JudgeButton();
	void initialize()override;
	void finalize()override;
	void update()override;
	//他のクラスで初期化するための関数
	void set_contents(Vector2 pos, std::string name_[2], JudgeKey key_);
	//自分が押されているか
	bool is_pushed();
};