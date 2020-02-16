#include "Necessary.h"
#include"Audio.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"
//-------------------------------------
// 実体化
//-------------------------------------
bool Necessary::fade_ioFlag;//フェードを管理するフラグ
bool Necessary::clear_flag;//ゲームクリアを管理するフラグ

int Necessary::score;//スコア
int Necessary::speed;//ノーツの落ちる速度

SceneData Necessary::scene;//シーン
MusicList Necessary::m_list;//楽曲

void Necessary::initialize()
{
	//初期化
	fade_ioFlag = false;
}

void Necessary::set_fade_ioFlag(bool flag)
{
	fade_ioFlag = flag;
}

void Necessary::set_scene(SceneData scene_)
{
	scene = scene_;
}

void Necessary::set_music(MusicList list)
{
	m_list = list;
}

bool Necessary::get_fade_ioFlag()
{
	return fade_ioFlag;
}

SceneData Necessary::get_now_scene()
{
	return scene;
}

MusicList Necessary::get_music()
{
	return m_list;
}
