#pragma once
#include"Necessary.h"
#include"TitleScene.h"
#include"MusicSelect.h"
#include"GameScene.h"
#include"ResultScene.h"

//シーンを管理する

class SceneManager {
	MusicSelect* m_select;
	Title* title;
	Game* game;
	Result*result;
public:
	void initialize();
	void finalize();
	void update();
	void draw();

	void change_scene(SceneData next_scene);//シーンを変える
};

extern SceneManager* scene_manager;