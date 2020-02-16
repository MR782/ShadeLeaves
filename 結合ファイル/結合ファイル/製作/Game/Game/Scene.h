#pragma once
#include"Necessary.h"

class Scene {
protected:
	int back_graph_handle;//�w�i�摜�i�[�ϐ�
	void scene_change(bool,SceneData);//�t�F�[�h�C���E�A�E�g���s���V�[����ς���
public:
	Scene();
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};