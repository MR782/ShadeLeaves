#pragma once
#include"Object.h"
#include"BasicUI.h"

//ゲーム結果のランク表示

class RankLabel : public Object {
	const char* check_rank();//ゲームのスコアでランクを付ける
	Color set_rankColor();
	Text rank_label;
	Text rank_label_header;
	int		draw_start_countor;	//描画開始のカウンター
public:
	RankLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
	bool check_scene_transition();
};