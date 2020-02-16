#pragma once
#include"Necessary.h"

class Scene {
protected:
	int back_graph_handle;//背景画像格納変数
	void scene_change(bool,SceneData);//フェードイン・アウトを行いシーンを変える
public:
	Scene();
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};