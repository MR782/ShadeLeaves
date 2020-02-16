#pragma once
#include"Object.h"

//判定結果
enum class JudgeResult {
	perfect,
	good,
	miss,
	none
};

//判定を行うキー
enum class JudgeKey {
	Key_D,//0
	Key_F,//1
	Key_J,//2
	Key_K,//3
	JudgeKeyNum//
};

class Notes : public Object {
	JudgeResult judge_result;//判定結果
	//メソッド
	void move();//移動を行う
protected:
	bool is_first;//自身がvectorの先頭にいるか
	JudgeKey judge_key;//判定キー
	float key_down_timing;//判定キーが押されたタイミング
	float perfect_timing;//perfectのタイミング(フレーム単位)
	virtual bool check_key();
	virtual JudgeResult judge();//判定を行う
public:
	Notes();
	virtual void initialize()override;
	void finalize()final;
	void update()final;

	void set_is_first(bool);
	JudgeResult get_result();//判定結果を受け取らせる
	JudgeKey get_judge_key();//判定キーを受け取らせる
	void set_contents(float timing,JudgeKey j_key);//データを入れる
};