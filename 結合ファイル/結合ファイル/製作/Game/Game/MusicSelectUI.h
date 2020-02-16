#pragma once
#include<memory>
#include"Animation.h"
#include"Movie.h"
#include"Jacket.h"
#include"Cursol.h"
#include"MusicSelectGuide.h"
#include"SpeedLabel.h"
#include"ScoreRanking.h"

class MusicSelectUI {
	Cursol* cursol[2];//�J�[�\����p��
	Jacket* jacket;//�W���P�b�g
	MusicSelectGuide* guide;//�K�C�h
	SpeedLabel* speed_label;//���x��\������
	ScoreRanking* score_ranking;//�����L���O
	std::unique_ptr<Movie> m_select_movie;
	//���\�b�h
	void change_music();//�I�𒆂̊y�Ȃ�ς���
public:
	MusicSelectUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};