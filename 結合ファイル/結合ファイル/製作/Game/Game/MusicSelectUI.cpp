#include "MusicSelectUI.h"
#include"Necessary.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

MusicSelectUI::MusicSelectUI()
{
	this->cursol[0] = nullptr;
	this->cursol[1] = nullptr;
	this->jacket = nullptr;
	this->guide = nullptr;
	this->speed_label = nullptr;
	this->score_ranking = nullptr;
}

void MusicSelectUI::initialize()
{
	//�J�[�\���̏�����
	{
		const int cursolNum = 2;//�J�[�\���̐�
		std::string graph_name[cursolNum] = { "select_cursol_L","select_cursol_R" };
		//���W����
		const int  select_cursol_height = 64;//�摜�̑傫��(�h�b�g�P��)
		const int select_cursol_width = 64;//�摜�̑傫��(�h�b�g�P��)
		int posY = (ScreenData::height / 2) - (select_cursol_height / 2);
		Vector2 pos[cursolNum] = { Vector2(ScreenData::width / 10, posY),Vector2((ScreenData::width / 4 * 3) - (ScreenData::width / 10) - select_cursol_width, posY) };
		//�J�[�\���̐����������s��
		for (int i = 0; i < cursolNum; i++) {
			this->cursol[i] = new Cursol();	//�������m��
			MemoryFunction::check_mem(this->cursol[i]);
			this->cursol[i]->initialize();
			this->cursol[i]->set_graph(graph_name[i]);
			this->cursol[i]->set_position(pos[i]);
		}
	}
	//���[�r�[���Z�b�g
	this->m_select_movie = std::make_unique<Movie>();
	if (this->m_select_movie == nullptr) throw "MusicSelect movie is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���;
	this->m_select_movie->set("autumn_leaves");
	//�y�ȃW���P�b�g�p
	this->jacket = new Jacket();
	MemoryFunction::check_mem(this->jacket);
	this->jacket->initialize();
	//�K�C�h�̏�����
	this->guide =new MusicSelectGuide();
	MemoryFunction::check_mem(this->guide);
	this->guide->initialize();
	//�X�s�[�h�\��
	this->speed_label = new SpeedLabel();
	MemoryFunction::check_mem(this->speed_label);
	this->speed_label->initialize();
	//�����L���O
	this->score_ranking = new ScoreRanking();
	MemoryFunction::check_mem(this->score_ranking);
	this->score_ranking->initialize();
}

void MusicSelectUI::finalize()
{
	//�I�������ƃ������J��
	const int cursolNum = 2;//�J�[�\���̐�
	for (int i = 0; i < cursolNum; i++) {
		this->cursol[i]->finalize();
	}
	this->jacket->finalize();
	this->guide->finalize();
	this->speed_label->finalize();
	this->score_ranking->finalize();

	delete this->guide;
	delete this->speed_label;
	delete this->jacket;
	for (int i = 0; i < cursolNum; i++) {
		delete this->cursol[i];
	}
	delete score_ranking;
}

void MusicSelectUI::update()
{
	//�W���P�b�g�̍X�V����
	this->jacket->update();
	//�����L���O�̍X�V����
	this->score_ranking->update();
	//�w��̃L�[�������ꂽ��I���y�Ȃ�ς���----------------------------------
	change_music();
}

void MusicSelectUI::draw()
{
	//���[�r�[�̕`��
	this->m_select_movie->draw();
	//�J�[�\���̕`��
	const int cursolNum = 2;//�J�[�\���̐�
	for (int i = 0; i < cursolNum; i++) {
		this->cursol[i]->draw();
	}
	//�W���P�b�g�̕`��
	this->jacket->draw();
	//�K�C�h�̕\��
	this->guide->draw();
	//�X�s�[�h�\��
	this->speed_label->draw();
	//�����L���O�̕\��
	this->score_ranking->draw();
}

void MusicSelectUI::change_music()
{
	//���ݑI�𒆂̊y�Ȃ�����
	int now_select = (int)Necessary::get_music();
	//�w��̃L�[�������ꂽ��I���y�Ȃ�ς���
	if (KeyBoard::key_down(KEY_INPUT_RIGHT)) {
		//1���炷
		now_select = (now_select + 1) % (int)MusicList::MusicNum;
		Necessary::set_music(MusicList(now_select));
		//���ʉ���炷
		Audio::play("cursol");
	}
	if (KeyBoard::key_down(KEY_INPUT_LEFT)) {
		//���ʉ���炷
		Audio::play("cursol");
		//1���炷
		now_select = (now_select + ((int)MusicList::MusicNum - 1)) % (int)MusicList::MusicNum;
		Necessary::set_music(MusicList(now_select));
	}
}