#pragma once
#include"Notes.h"

class JudgeResultUI : public Object {
	int active_cnt;//1秒間存在する
	int lane;//出現するレーン
public:
	JudgeResultUI();
	void initialize();
	void finalize();
	void update();

	bool is_active();//生存するべきか確認するためのメソッド
	void set_lane(JudgeKey j_key);//自分の出現レーンをセット
	void set_graph(std::string name);//画像をセットする
};