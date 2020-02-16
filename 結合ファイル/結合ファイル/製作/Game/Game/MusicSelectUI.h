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
	Cursol* cursol[2];//カーソル二つ用意
	Jacket* jacket;//ジャケット
	MusicSelectGuide* guide;//ガイド
	SpeedLabel* speed_label;//速度を表示する
	ScoreRanking* score_ranking;//ランキング
	std::unique_ptr<Movie> m_select_movie;
	//メソッド
	void change_music();//選択中の楽曲を変える
public:
	MusicSelectUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};