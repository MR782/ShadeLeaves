#include "GameSceneJacket.h"
#include"Necessary.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

GameSceneJacket::GameSceneJacket()
{
	this->jacket_handle = 0;
}

void GameSceneJacket::initialize()
{
	const int jacket_width = 320;//画像の大きさ(ドット単位)
	this->position = Vector2(ScreenData::width - jacket_width,0);
	this->jacket_handle = GraphicResource::get_handle(set_jacket())[0];
}

void GameSceneJacket::finalize()
{
}

void GameSceneJacket::draw(bool a_blend)
{
	const int jacket_height = 480;//画像の大きさ(ドット単位)
	DrawExtendGraph((int)this->position.x, (int)this->position.y,
		ScreenData::width, jacket_height,
		this->jacket_handle, FALSE);
}

std::string GameSceneJacket::set_jacket()
{
	std::string name;
	switch (Necessary::get_music())
	{
	case MusicList::fancie:
		name = "fancie_jacket";
		break;
	case MusicList::monoceros:
		name = "monoceros_jacket";
		break;
	case MusicList::m3_500:
		name = "m3_500_jacket";
		break;
	default:
		throw("楽曲に無効な値が入っている");
		break;
	}
	return name;
}