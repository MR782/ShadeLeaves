#include "Scene.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"SceneManager.h"

void Scene::scene_change(bool conditions, SceneData next)
{
	//�t���O��true�Ȃ�
	if (conditions && ScreenFunction::check_blend_min()) {
		Audio::play("decision",false);//���艹��炷
		Necessary::set_fade_ioFlag(true);//�t�F�[�h�A�E�g�J�n
	}
	//�Ó]����������
	if (ScreenFunction::check_blend_max()) {
		//�t�F�[�h�C�����s���悤�w�����o��
		Necessary::set_fade_ioFlag(false);
		//�V�[����؂�ւ���
		scene_manager->change_scene(next);
	}
}

Scene::Scene()
{
	this->back_graph_handle = 0;
}
