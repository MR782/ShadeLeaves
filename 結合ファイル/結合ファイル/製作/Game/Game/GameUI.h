#pragma once
#include"JudgeButton.h"
#include"ScoreLabel.h"
#include"ComboLabel.h"
#include"GameSceneJacket.h"
#include"JudgeResultText.h"
#include"ClearGaugeFream.h"
#include"ClearGauge.h"

class GameUI {
	JudgeResultText* result_text;
	std::vector<JudgeButton*> judge_button;//����{�^��
	ScoreLabel* score_label;//�X�R�A�\���̃��x��
	ComboLabel* combo_label;//�R���{�\���̃��x��
	GameSceneJacket* jacket;//�v���C���̊y�Ȃ�\��
	ClearGaugeFream* clear_gauge_fream;//�t���[��
public:
	GameUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};

namespace ClearGaugeUI {
	extern ClearGauge* clear_gauge;//�N���A�Q�[�W
}