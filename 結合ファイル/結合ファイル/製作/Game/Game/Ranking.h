#pragma once
#include"RankData.h"
#include"Purpose.h"
#include<map>
#include"BasicUI.h"

//�����L���O��\������

class Ranking {
	std::vector<RankData::Status> rank_data;
	RankData data;
	int font_size;
	Text score_rank_label;
	Text score_rank_label_header;
public:
	Ranking();
	void initialize();
	void finalize();
	void update();
	void draw(Point pos);
};