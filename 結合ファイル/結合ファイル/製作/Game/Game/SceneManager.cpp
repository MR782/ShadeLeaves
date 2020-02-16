#include "SceneManager.h"
#include"ScreenFunction.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"MovieResource.h"
#include"MemoryFunc.h"
#include"ScreenHelperGraph.h"

void SceneManager::initialize()
{
	//���\�[�X�̓ǂݍ��ޏ���(Json�������Ɨ�O�𓊂���)
	GraphicResource::initialize();
	Audio::initialize();
	MovieResource::initialize();

	//�t�F�[�h�C���A�E�g�̏���
	ScreenFunction::initialize();

	//���\�[�X�̓ǂݍ���
	GraphicResource::load("all");
	Audio::load("system");//�V�X�e�����̓ǂݍ���
	Audio::set_volume_audioscope("system", 50);
	//�������m��
	this->title = new Title();
	MemoryFunction::check_mem(this->title);
	//�����V�[�����Z�b�g
	Necessary::set_scene(SceneData::title);
	this->title->initialize();
}

void SceneManager::finalize()
{
	//���\�[�X�̊J��
	Audio::stop_all();
	Audio::finalize();
	MovieResource::finalize();
	ScreenFunction::finalize();
	GraphicResource::finalize();
	//���݂̃V�[���ɂ���ď�����ς���
	switch (Necessary::get_now_scene())
	{
	case SceneData::title:
		this->title->finalize();
		delete this->title;
		break;
	case SceneData::m_select:
		this->m_select->finalize();
		delete this->m_select;
		break;
	case SceneData::game:
		this->game->finalize();
		delete this->game;
		break;
	case SceneData::result:
		this->result->finalize();
		delete this->result;
		break;
	}
}

void SceneManager::update()
{
	//�V�[�����Ƃ̍X�V�������Ă�
	switch (Necessary::get_now_scene())
	{
	case SceneData::title:
		this->title->update();
		break;
	case SceneData::m_select:
		this->m_select->update();
		break;
	case SceneData::game:
		this->game->update();
		break;
	case SceneData::result:
		this->result->update();
		break;
	default:
		throw ("�V�[��������������Ă��Ȃ��������͖����Ȓl�����͂���Ă���");
		break;
	}
	ScreenFunction::update();
}

void SceneManager::draw()
{
	//�V�[�����Ƃ̕`�揈�����Ă�
	switch (Necessary::get_now_scene())
	{
	case SceneData::title:
		this->title->draw();
		break;
	case SceneData::m_select:
		this->m_select->draw();
		break;
	case SceneData::game:
		this->game->draw();
		break;
	case SceneData::result:
		this->result->draw();
		break;
	default:
		throw "�V�[��������������Ă��Ȃ��������͖����Ȓl�����͂���܂���";
		break;
	}
	//�t�F�[�h�A�E�g�p�摜�̕`��
	ScreenFunction::draw(ScreenHelperGraph::black_graph);
}

void SceneManager::change_scene(SceneData next_scene)
{
	//���݂̃V�[���̏I���������s��
	switch (Necessary::get_now_scene())
	{
	case SceneData::title:
		this->title->finalize();
		delete this->title;
		break;
	case SceneData::m_select:
		this->m_select->finalize();
		delete this->m_select;
		break;
	case SceneData::game:
		this->game->finalize();
		delete this->game;
		break;
	case SceneData::result:
		this->result->finalize();
		delete this->result;
		break;
	default:
		throw ("�V�[��������������Ă��Ȃ��������͖����Ȓl�����͂���Ă���");
		break;
	}
	//���̃V�[���̏������������s��
	switch (next_scene)
	{
	case SceneData::title:
		this->title = new Title();//�������m��
		MemoryFunction::check_mem(this->title);
		this->title->initialize();
		break;
	case SceneData::m_select:
		this->m_select = new MusicSelect();//�������m��
		if (this->m_select == nullptr) throw "MusicSelectScene is null_ptr";//�������m�ۂł��Ȃ��������O�𓊂���
		this->m_select->initialize();
		break;
	case SceneData::game:
		this->game = new Game();
		MemoryFunction::check_mem(this->game);
		this->game->initialize();
		break;
	case SceneData::result:
		this->result = new Result();
		MemoryFunction::check_mem(this->result);
		this->result->initialize();
		break;
	default:
		throw "�V�[��������������Ă��Ȃ��������͖����Ȓl�����͂���܂���";
		break;
	}
	//�V�[���̍X�V
	Necessary::set_scene(next_scene);
}