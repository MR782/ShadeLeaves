#include "GameScene.h"
#include"Necessary.h"
#include"Audio.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

#include<time.h>
#include <windows.h>

//�J�E���^
float Counter::game_cnt;
int Counter::perfect_cnt;
int Counter::good_cnt;
int Counter::miss_cnt;
int Counter::notes_num;
int Counter::combo_cnt;
//���f��
std::vector<std::unique_ptr<Notes>> Model::notes;
JudgeLine* Model::judge_line;
std::vector<std::unique_ptr<JudgeResultUI>> Model::judge_results;
std::vector<std::unique_ptr<Effect>> Model::effects;

Game::Game() :Scene()
{
	this->notes_controller = nullptr;
	this->game_ui = nullptr;
	this->notes_creater = nullptr;
	this->start_time.QuadPart = 0;
	this->now_time.QuadPart = 0;
	this->freq.QuadPart = 0;
}

void Game::initialize()
{
	//�f�[�^�폜
	Model::notes.clear();
	Model::effects.clear();
	Model::judge_results.clear();
	//���\�[�X�̓ǂݍ���
	Audio::load("game");

	//�������m�� - �������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	//���胉�C��------------------------------------------------------------------
	Model::judge_line = new JudgeLine();
	MemoryFunction::check_mem(Model::judge_line);
	//UI�̏�����
	this->game_ui = new GameUI();
	MemoryFunction::check_mem(this->game_ui);
	//�m�[�c�̐������u----------------------------------------------------------------
	this->notes_creater = new NotesCreater();
	MemoryFunction::check_mem(notes_creater);
	//�m�[�c�R���g���[���[----------------------------------------------------------
	this->notes_controller = new NotesController();
	MemoryFunction::check_mem(this->notes_controller);
	//�I�u�W�F�N�g�̏�����
	Model::judge_line->initialize();//���胉�C���̏�����
	this->notes_creater->initialize();
	this->game_ui->initialize();//UI�̏�����
	//�I���y�Ȃɂ���ēǂݍ��ރf�[�^��ς���
	set_musical_score();
	this->notes_controller->initialize();

	//�J�E���^�̏�����-----------------------------------------------------------------
	QueryPerformanceFrequency(&this->freq);
	QueryPerformanceCounter(&this->start_time);
	QueryPerformanceCounter(&this->now_time);

	Counter::game_cnt = 0;
	Counter::perfect_cnt = 0;
	Counter::good_cnt = 0;
	Counter::miss_cnt = 0;
	Counter::combo_cnt = 0;
	Necessary::score = 0;//�X�R�A�̏�����
	//�摜���Z�b�g
	std::string graph_name = "";
	switch (Necessary::get_music()) {
	case MusicList::fancie:
		graph_name = "Fancie_BG";
		break;
	case MusicList::monoceros:
		graph_name = "monoceros_BG";
		break;
	case MusicList::m3_500:
		graph_name = "M3_BG";
		break;
	default:
		throw("�s���Ȓl�������Ă��� MusicList -> GameScene");
	}
	this->back_graph_handle = GraphicResource::get_handle(graph_name)[0];

	start_music();
}

void Game::finalize()
{
	Model::judge_line->finalize();
	this->notes_creater->finalize();
	this->game_ui->finalize();
	this->notes_controller->finalize();
	//�������J��
	Model::judge_results.clear();
	Model::notes.clear();
	Model::effects.clear();

	delete Model::judge_line;
	delete this->notes_creater;
	delete this->game_ui;
	delete this->notes_controller;
}

void Game::update()
{
	//�Q�[���J�E���^�̍X�V
	QueryPerformanceCounter(&this->now_time);
	//�}�C�N���b����~���b�ɕϊ����ăt���[���ɕϊ�
	Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//�t���[���P�ʂɕϊ�
	//�m�[�c�̍X�V����
	this->notes_controller->update();
	//���茋��
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->update();
	}
	//�G�t�F�N�g�̍X�V����
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		(*itr)->update();
	}
	//���茋�ʂ���������UI�̍폜����
	delete_judge_resultUI();
	//�G�t�F�N�g�̍폜����
	delete_judge_effect();
	//���胉�C���̍X�V����
	Model::judge_line->update();
	//UI�̍X�V����
	this->game_ui->update();

	//�Ȃ��I��������t�F�[�h�A�E�g�J�n----------------------
	if (Audio::check_play_scope("game") == false) {
		Necessary::set_fade_ioFlag(true);
	}
	//�Ó]����������
	if (ScreenFunction::check_blend_max()) {
		//�t�F�[�h�C�����s���悤�w�����o��
		Necessary::set_fade_ioFlag(false);
		//�V�[����؂�ւ���
		scene_manager->change_scene(SceneData::result);
	}
}

void Game::draw()
{
	//�w�i�̊g�k�`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//���[���̕`��-------------------------------------------------------------
	const int judge_lineX = (int)Model::judge_line->get_position().x;
	const int judge_lineY = (int)Model::judge_line->get_position().y;
	const int judge_line_width = 256;
	const int judge_line_height = 16;
	const int buttonNum = 4;//����{�^���̐�
	const int note_width = 64;
	DrawBox(judge_lineX, 0, judge_lineX + judge_line_width, judge_lineY, setColor(Color::Black), TRUE);
	for (int i = 0; i <= buttonNum; i++) {
		DrawLine(judge_lineX + note_width * i, 0,
			judge_lineX + note_width * i,
			judge_lineY + judge_line_height,
			setColor(Color::White));
	}
	//���胉�C���̕`��---------------------------------------------------------
	Model::judge_line->draw();
	//�m�[�c�̕`��
	this->notes_controller->draw();
	//UI�̕`��
	this->game_ui->draw();
	//���茋��
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->draw();
	}
	//�G�t�F�N�g�̕`�揈��
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		(*itr)->draw();
	}
}

void Game::delete_judge_resultUI()
{
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		//���݂���ׂ��ł͂Ȃ��Ȃ�
		if ((*itr)->is_active() == false) {
			//�z�񂩂�폜
			Model::judge_results.erase(itr);
			break;
		}
	}
}

void Game::delete_judge_effect()
{
	for (auto itr = Model::effects.begin(); itr != Model::effects.end(); itr++) {
		const int judge_result_effect_active_cnt = 30;
		if ((*itr)->is_death(judge_result_effect_active_cnt)) {
			Model::effects.erase(itr);
			break;
		}
	}
}

void Game::set_musical_score()
{
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		this->notes_creater->get_notes_data("monoceros");
		Counter::notes_num = notes_creater->get_all_notes_num("monoceros");
		break;
	case MusicList::fancie:
		this->notes_creater->get_notes_data("fancie");
		Counter::notes_num = notes_creater->get_all_notes_num("fancie");
		break;
	case MusicList::m3_500:
		this->notes_creater->get_notes_data("m3_500");
		Counter::notes_num = notes_creater->get_all_notes_num("m3_500");
		break;
	default:
		throw("���ʃZ�b�g���Ɋy�Ȃɖ����Ȓl�������Ă���");
	}
}

void Game::start_music()
{
	//�y�ȑI���Ɋ�Â��ĕς���
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Audio::play("monoceros");
		break;
	case MusicList::fancie:
		Audio::play("fancie");
		break;
	case MusicList::m3_500:
		Audio::play("m3_500");	
		break;
	default:
		throw "�y�Ȃɖ����Ȓl�������Ă���";
	}
}
