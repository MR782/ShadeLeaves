#include "ClearGaugeFream.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

void ClearGaugeFream::initialize()
{
	this->fream_accessories = GraphicResource::get_handle("gauge_fream_decoration")[0];
	this->gauge_fream_graph = GraphicResource::get_handle("gauge_fream")[0];
	this->position = Vector2(ScreenData::width / 25,ScreenData::height / 8);
}

void ClearGaugeFream::finalize()
{
	this->anime.reset();
}

void ClearGaugeFream::draw(bool a_blend)
{
	const int graph_height = 247;
	const int graph_width = 1038;
	DrawExtendGraph(0, ScreenData::height / 3 - 50,
		ScreenData::width / 4 + graph_width / 10, ScreenData::height / 3 + 100
		, this->fream_accessories, TRUE);

	DrawExtendGraph(ScreenData::width / 20, ScreenData::height / 3,
		ScreenData::width / 4, ScreenData::height / 3 + 50
		, this->gauge_fream_graph, TRUE);
}
