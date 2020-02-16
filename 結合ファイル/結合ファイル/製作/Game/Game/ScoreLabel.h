#pragma once
#include"Object.h"
#include"BasicUI.h"

//ゲームスコアを表示する

class ScoreLabel : public Object {
	Text score_label;
	Text score_label_header;
	int font;
	int head_font;
public:
	ScoreLabel();
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};