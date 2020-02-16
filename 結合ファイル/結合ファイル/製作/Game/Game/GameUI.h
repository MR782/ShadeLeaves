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
	std::vector<JudgeButton*> judge_button;//判定ボタン
	ScoreLabel* score_label;//スコア表示のラベル
	ComboLabel* combo_label;//コンボ表示のラベル
	GameSceneJacket* jacket;//プレイ中の楽曲を表示
	ClearGaugeFream* clear_gauge_fream;//フレーム
public:
	GameUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};

namespace ClearGaugeUI {
	extern ClearGauge* clear_gauge;//クリアゲージ
}