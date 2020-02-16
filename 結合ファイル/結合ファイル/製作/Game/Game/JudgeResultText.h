#pragma once
#include"BasicUI.h"
#include"Object.h"
#include<vector>

class JudgeResultText :public Object{
	std::vector<Text> result_header;
	std::vector<Text> result;
	int font;
public:
	JudgeResultText();
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};