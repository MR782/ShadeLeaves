#include "Scene.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"SceneManager.h"

void Scene::scene_change(bool conditions, SceneData next)
{
	//フラグがtrueなら
	if (conditions && ScreenFunction::check_blend_min()) {
		Audio::play("decision",false);//決定音を鳴らす
		Necessary::set_fade_ioFlag(true);//フェードアウト開始
	}
	//暗転しきったら
	if (ScreenFunction::check_blend_max()) {
		//フェードインを行うよう指示を出す
		Necessary::set_fade_ioFlag(false);
		//シーンを切り替える
		scene_manager->change_scene(next);
	}
}

Scene::Scene()
{
	this->back_graph_handle = 0;
}
