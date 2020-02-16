#pragma once
#include"Object.h"

class ClearGauge : public Object {
	int clear_line_handle;
	int gauge_handle;
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;

	int draw_width;
};