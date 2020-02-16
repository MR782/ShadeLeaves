#include "MusicSelect.h"
#include"./dxlib/DxLib.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"SceneManager.h"
#include"MemoryFunc.h"

MusicSelect::MusicSelect()
{
	this->ms_ui = nullptr;
	this->back_graph_handle = 0;
}

void MusicSelect::initialize()
{
	//���\�[�X�̓ǂݍ���
	MovieResource::load("m_select");
	//BGM��ǂݍ���
	Audio::load("select");
	//�Đ�
	//Audio::play("m_select", false);
	//�������m��
	this->ms_ui = new MusicSelectUI();
	MemoryFunction::check_mem(this->ms_ui);
	//�f�[�^�̏�����
	//�w�i�摜���i�[
	this->back_graph_handle = GraphicResource::get_handle("select_back")[0];
	//�I�𒆂̊y�Ȃ�������
	this->ms_ui->initialize();
}

void MusicSelect::finalize()
{
	this->ms_ui->finalize();
	delete this->ms_ui;
	Audio::stop("m_select");
	Audio::delete_soundData_name("m_select");
	MovieResource::delete_movie_mem("autumn_leaves");
}

void MusicSelect::update()
{
	if (ScreenFunction::check_blend_min()) {
		//UI�̍X�V����
		this->ms_ui->update();
		set_speed();
	}
	//----------------------------------------------------------------------
	//Enter�L�[�������ꂽ��V�[���ݒ�
	scene_change(KeyBoard::key_down(KEY_INPUT_RETURN), SceneData::game);
	//-----------------------------------------------------------------------
}

void MusicSelect::draw()
{
	//�w�i�摜���g�k�`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//UI�̕`��
	this->ms_ui->draw();
}

void MusicSelect::set_speed()
{
	//�X�s�[�h��������
	if (KeyBoard::key_down(KEY_INPUT_D) || KeyBoard::key_down(KEY_INPUT_F)) {
		//���ʉ���炷
		Audio::play("cursol");
		//����0�ɂ͂��Ȃ�
		if (Necessary::speed <= 1) return;
		Necessary::speed = Necessary::speed - 1;
	}
	//�X�s�[�h���グ��
	if (KeyBoard::key_down(KEY_INPUT_J) || KeyBoard::key_down(KEY_INPUT_K)) {
		//���ʉ���炷
		Audio::play("cursol");
		//�X�s�[�h�����20�Ƃ���
		if (Necessary::speed >= 20) return;
		Necessary::speed = Necessary::speed + 1;
	}
}