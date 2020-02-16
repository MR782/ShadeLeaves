#pragma once
#include"Object.h"
#include"BasicUI.h"

class SpeedLabel : public Object {
	Text speed_label_header;//文字表示
	Text speed_label;//現在のスピードを表示
	int font;
public:
	SpeedLabel();
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};