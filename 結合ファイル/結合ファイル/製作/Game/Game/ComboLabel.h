#pragma once
#include"Object.h"
#include"BasicUI.h"

//コンボ数を表示する

class ComboLabel : public Object {
	Text combo_label_header;//Comboという文字を表示する
	Text combo_label;//コンボ数を表示する
	int previous_miss_cnt;//1フレーム前のミスの数を格納する
	int current_miss_cnt;//作業領域
	int font;
public:
	ComboLabel();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
};