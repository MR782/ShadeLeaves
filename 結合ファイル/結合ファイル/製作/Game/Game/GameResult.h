#pragma once
#include"BasicUI.h"
#include"Object.h"

class GameResult : public Object {
	Text game_result_text;
	//�Q�[���N���A���ǂ����̕�����\��
public:
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};