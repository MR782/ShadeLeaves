#pragma once
#include"BasicUI.h"
#include"Object.h"

class GameResult : public Object {
	Text game_result_text;
	//ゲームクリアかどうかの文字を表示
public:
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};