#include "Movie.h"
#include"./dxlib/DxLib.h"
#include"ScreenSystem.h"

void Movie::draw()
{
	//ムービーが再生されていないなら
	if (MovieResource::check_play(object->name) == false) {
		//ループアリなら最初に戻して
		if (object->loop == true) {
			SeekMovieToGraph(object->handle, 0);
		}
		//再生
		PlayMovieToGraph(object->handle);//再生
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//ブレンドモードを設定
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, object->handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//ブレンドモードをオフ
}

void Movie::set(std::string name)
{
	if (object != MovieResource::get(name)) {
		//今のムービーと設定するムービーが違うなら
		object = MovieResource::get(name);//更新
	}
}
