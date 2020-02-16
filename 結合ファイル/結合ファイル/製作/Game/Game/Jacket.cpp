#include "Jacket.h"
#include"ScreenSystem.h"
#include"Audio.h"
#include"Necessary.h"

void Jacket::initialize()
{
	this->anime = std::make_unique<Animation>();//メモリ確保
	if (this->anime == nullptr) throw "Jacket anime is null_ptr";//メモリ確保できていないなら例外を投げる

	switch (Necessary::get_music()) {
	case MusicList::fancie:
		this->now_select = "fancieDemo";
		this->pre_select = "fancieDemo";
		this->anime->set("fancie_jacket");//初期画像
		break;
	case MusicList::monoceros:
		this->now_select = "monocerosDemo";
		this->pre_select = "monocerosDemo";
		this->anime->set("monoceros_jacket");//初期画像をセット
		break;
	case MusicList::m3_500:
		this->now_select = "m3_500Demo";
		this->pre_select = "m3_500Demo";
		this->anime->set("m3_500_jacket");
	}
	//座標セット
	const int jacket_width = 320;//画像の大きさ(ドット単位)
	const int jacket_height =480;//画像の大きさ(ドット単位)
	this->position = Vector2((ScreenData::width / 2) - (jacket_width / 8 * 7), (ScreenData::height / 2) - (jacket_height / 2));
}

void Jacket::finalize()
{
	Audio::stop_scope("all");
	this->anime.reset();
}

void Jacket::update()
{
	//選択楽曲が1フレーム前と違うなら
	if (pre_select != now_select) {
		Audio::stop_scope("bgm");
	}

	pre_select = now_select;
	//ジャケット画像の変更
	change_jacket();
}

void Jacket::change_jacket()
{
	//難易度と楽曲によって画像を変える
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		now_select = "monocerosDemo";
		this->anime->set("monoceros_jacket");
		
		break;
	case MusicList::fancie:
		now_select = "fancieDemo";
		this->anime->set("fancie_jacket");
		break;
	case MusicList::m3_500:
		now_select = "m3_500Demo";
		this->anime->set("m3_500_jacket");
	}
	Audio::play(now_select, false);
}
