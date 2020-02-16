#include "GameUI.h"
#include"SceneManager.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

ClearGauge* ClearGaugeUI::clear_gauge;//�N���A�Q�[�W

GameUI::GameUI()
{
	this->score_label = nullptr;
	this->combo_label = nullptr;
	this->jacket = nullptr;
	this->result_text = nullptr;
	ClearGaugeUI::clear_gauge = nullptr;
	this->clear_gauge_fream = nullptr;
}

void GameUI::initialize()
{
	//JudgeButton�̏�����-----------------------------------------------------------------------------
	{
		const int buttonNum = 4;//����{�^���̐�
		std::string name[buttonNum][2];
		name[0][0] = "not_pushD"; name[0][1] = "pushD";//D�L�[
		name[1][0] = "not_pushF"; name[1][1] = "pushF";//F�L�[
		name[2][0] = "not_pushJ"; name[2][1] = "pushJ";//J�L�[
		name[3][0] = "not_pushK"; name[3][1] = "pushK";//K�L�[
		//�v�f�ǉ�
		for (int i = 0; i < buttonNum; i++) {
			judge_button.push_back(new JudgeButton());
		}
		int cnt = 0;
		for (auto itr = judge_button.begin(); itr != judge_button.end(); itr++, cnt++) {
			MemoryFunction::check_mem(*itr);
			(*itr)->initialize();
			//�������W
			const int note_width = 64;
			const int judge_line_height = 16;
			Vector2 pos = Vector2(Model::judge_line->get_position().x + (note_width * cnt),//x
				Model::judge_line->get_position().y + judge_line_height);//y
			//�����f�[�^�Z�b�g
			(*itr)->set_contents(pos, name[cnt], JudgeKey(cnt));
		}
	}
	//UI---------------------------------------------------------------------------------------------
	this->result_text = new JudgeResultText();
	MemoryFunction::check_mem(this->result_text);
	this->result_text->initialize();
	//�X�R�AUI--------------------------------------------------------------------------------------------
	this->score_label = new ScoreLabel();
	MemoryFunction::check_mem(this->score_label);
	this->score_label->initialize();
	//�R���{���x���̏�����
	this->combo_label =new ComboLabel();
	MemoryFunction::check_mem(this->combo_label);
	this->combo_label->initialize();
	//�W���P�b�g�摜
	this->jacket = new GameSceneJacket();
	MemoryFunction::check_mem(this->jacket);
	this->jacket->initialize();
	//�N���A�Q�[�W
	ClearGaugeUI::clear_gauge = new ClearGauge();
	MemoryFunction::check_mem(ClearGaugeUI::clear_gauge);
	ClearGaugeUI::clear_gauge->initialize();

	this->clear_gauge_fream = new ClearGaugeFream();
	MemoryFunction::check_mem(clear_gauge_fream);
	this->clear_gauge_fream->initialize();
}

void GameUI::finalize()
{
	this->combo_label->finalize();
	this->score_label->finalize();
	this->result_text->finalize();
	this->jacket->finalize();
	ClearGaugeUI::clear_gauge->finalize();
	this->clear_gauge_fream->finalize();
	for (auto itr : judge_button) {
		(itr)->finalize();
		delete (itr);
	}
	this->judge_button.clear();
	delete this->result_text;
	delete this->combo_label;
	delete this->score_label;
	delete this->jacket;
	delete ClearGaugeUI::clear_gauge;
	delete this->clear_gauge_fream;
}

void GameUI::update()
{
	//����{�^���̍X�V����
	for (auto itr : judge_button) {
		(itr)->update();
	}
	this->combo_label->update();
	ClearGaugeUI::clear_gauge->update();
}

void GameUI::draw()
{
	//����{�^���̕`�揈��
	for (auto itr : judge_button) {
		//�{�^����������Ă�����
		if (itr->is_pushed()) {
			const int buttomWidth = 64;//����{�^���̉��̑傫��(�h�b�g�P��)
			//�����{�^���̏�ɔ����{�b�N�X��`�悷��
			SetDrawBlendMode(DX_BLENDMODE_ADD, 128);//�u�����h���[�h��ݒ�
			DrawBox((int)itr->get_position().x, (int)itr->get_position().y,
				(int)itr->get_position().x + buttomWidth, ScreenData::height / 6,
				setColor(Color::Gray), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�u�����h���[�h�I�t
		}
		(itr)->draw();
	}
	//result
	this->result_text->draw();
	//score
	this->score_label->draw();
	//combo
	this->combo_label->draw();
	//jacket
	this->jacket->draw();
	//�N���A�Q�[�W
	this->clear_gauge_fream->draw();
	ClearGaugeUI::clear_gauge->draw();
}
