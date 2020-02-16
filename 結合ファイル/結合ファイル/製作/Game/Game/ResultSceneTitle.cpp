#include "ResultSceneTitle.h"
#include"ScreenSystem.h"

void ResultSceneTitle::initialize()
{
	//ƒf[ƒ^‰Šú‰»
	const int result_title_width = 256;
	this->position = Vector2((ScreenData::width / 2) - (result_title_width / 2), ScreenData::height / 10);
	this->anime = std::make_unique<Animation>();
	this->anime->set("result_title");
}

void ResultSceneTitle::finalize()
{
}