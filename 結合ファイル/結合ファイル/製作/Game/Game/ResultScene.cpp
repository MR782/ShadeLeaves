#include "ResultScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"ScreenFunction.h"
#include"Audio.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

Result::Result()
{
	this->result_ui = nullptr;
}

void Result::initialize()
{
	//���\�[�X�̓ǂݍ���
	Audio::load("result");
	MovieResource::load("reaf");
	//�������m��
	this->result_ui = new ResultUI();
	MemoryFunction::check_mem(this->result_ui);
	//�f�[�^�̏�����
	this->back_graph_handle = GraphicResource::get_handle("result_back")[0];
	this->result_ui->initialize();
	//���y�Đ�
	Audio::play("result");
}

void Result::finalize()
{
	Audio::stop("result");
	Audio::delete_soundData_name("result");
	MovieResource::delete_movie_mem("reaf");
	this->result_ui->finalize();
	delete this->result_ui;
}

void Result::update()
{
	if (ScreenFunction::check_blend_min()) {
		this->result_ui->update();
	} 
	//�V�[���؂�ւ�-----------------------------------------
	scene_change(KeyBoard::key_down(KEY_INPUT_RETURN) && this->result_ui->IsSceneTransition(), SceneData::m_select);
}

void Result::draw()
{
	//�w�i��`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//���U���g�`��
	this->result_ui->draw();
}
