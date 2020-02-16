#pragma once
#include"Animation.h"
#include"Movie.h"
#include"ResultGuide.h"
#include"ScoreLabel.h"
#include"RankLabel.h"
#include"ResultSceneTitle.h"
#include"GameResult.h"
#include"JudgeResultText.h"

class ResultUI {
	ResultGuide* guide;//�K�C�h�\��
	ScoreLabel* score;//�X�R�A
	RankLabel* rank;//�����N
	ResultSceneTitle* scene_title;//result�@��\������
	GameResult* game_result;//�t���R���{���̕\��(AP�܂�)
	JudgeResultText* judgeResult_text;
	//���[�r�[----------------------------------------------------
	std::unique_ptr<Movie> result_mv;//movie
public:
	ResultUI();
	void initialize();
	void finalize();
	void update();
	void draw();
	bool IsSceneTransition();
};