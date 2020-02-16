#pragma once
#include"Object.h"
#include"Ranking.h"
#include"BasicUI.h"

class ScoreRanking : public Object {
	Ranking* rank;
	int rank_board_graph;
public:
	ScoreRanking();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_blend = false)override;
};