#include "ScoreRanking.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"
#include"MemoryFunc.h"

ScoreRanking::ScoreRanking()
{
	this->rank = nullptr;
	this->rank_board_graph = 0;
}

void ScoreRanking::initialize()
{
	this->rank = new Ranking();
	MemoryFunction::check_mem(this->rank);
	this->rank->initialize();
	this->rank_board_graph = GraphicResource::get_handle("score_board")[0];
}

void ScoreRanking::finalize()
{
	this->anime.reset();
	this->rank->finalize();

	delete this->rank;
}

void ScoreRanking::update()
{
	this->rank->update();
}

void ScoreRanking::draw(bool a_blend)
{
	Rect draw(ScreenData::width / 4 * 3, ScreenData::height / 10,ScreenData::width - ScreenData::width / 4 * 3, ScreenData::height / 10 * 7);
	DrawExtendGraph(draw.x, draw.y, draw.x + draw.w, draw.y + draw.h, this->rank_board_graph, FALSE);
	this->rank->draw(Point(draw.x + 16, draw.y + 16));
}
