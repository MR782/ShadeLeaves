#include "NotesController.h"
#include"MemoryFunc.h"
#include"ScreenSystem.h"
#include"GameScene.h"

bool NotesController::delete_notes(std::unique_ptr<Notes>& note)
{
	//���łɔ�����s���Ă���Ȃ�
	if ((*note).get_result() != JudgeResult::none) {
		add_score((*note).get_result());
		//�f�[�^������������vector�ɑ}��
		MemoryFunction::check_mem(result_creater);
		result_creater->create((*note).get_result(), (*note).get_judge_key());
		//���茋�ʂ̃G�t�F�N�g��ǉ�
		std::unique_ptr<Effect> judge_effect;
		//�������m��
		judge_effect = std::make_unique<JudgeResultEffect>();
		//�����ʒu�̒�`
		const int judge_line_height = 16;
		Vector2 create_pos = Vector2((*note).get_position().x, Model::judge_line->get_position().y - (judge_line_height / 2));
		//���W�Ǝ�ނ��Z�b�g����
		judge_effect->set_effect(this->effect_kind[(*note).get_result()], create_pos);
		//�G�t�F�N�g�̓o�^
		Model::effects.push_back(std::move(judge_effect));

		return true;
	}
	return false;
}

void NotesController::callUpdate(std::vector<std::unique_ptr<Notes>>& lane)
{
	for (auto itr = lane.begin(); itr != lane.end(); itr++) {
		(*itr)->update();
		//�폜����
		if (delete_notes((*itr))) {
			//�����𖞂����Ă���Ȃ�z�񂩂�폜
			lane.erase(itr);
			//�Ō�łȂ���ΐV���Ȑ擪�����߂�
			if (!lane.empty()) {
				auto it = lane.begin();
				(*it)->set_is_first(true);
			}
			break;
		}
	}
}

void NotesController::callDraw(std::vector<std::unique_ptr<Notes>>& rane)
{
	for (auto itr = rane.begin(); itr != rane.end(); itr++) {
		(*itr)->draw();
	}
}

NotesController::NotesController()
{
	this->counter_increment_1_score = 0;
	this->result_creater = nullptr;
	this->effect_kind[JudgeResult::perfect] = "perfect_effect";
	this->effect_kind[JudgeResult::good] = "good_effect";
}

void NotesController::initialize()
{
	lane_data["D"].clear();
	lane_data["F"].clear();
	lane_data["J"].clear();
	lane_data["K"].clear();
	//�������m��
	this->result_creater = new JudgeResultCreater();
	MemoryFunction::check_mem(this->result_creater);
	//���[�����Ƃɔz�u(�Q�[���V�[���ɓo�^�����f�[�^���ړ�����)
	if (Model::notes.empty()) throw"�m�[�c�f�[�^������ۂł�";
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		switch ((*itr)->get_judge_key())
		{
		case JudgeKey::Key_D:
			lane_data["D"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_F:
			lane_data["F"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_J:
			lane_data["J"].push_back(std::move(*itr));
			break;
		case JudgeKey::Key_K:
			lane_data["K"].push_back(std::move(*itr));
			break;
		default:
			throw"�\�����Ȃ��f�[�^���܂܂�Ă���";
		}
	}
	//�擪�����߂�
	lane_data["D"].at(0)->set_is_first(true);
	lane_data["F"].at(0)->set_is_first(true);
	lane_data["J"].at(0)->set_is_first(true);
	lane_data["K"].at(0)->set_is_first(true);

	//���_�l�̂��߂ǂꂾ���̃m�[�c�������X�R�A��1���Z���邩����
	const int theoretical_value = 110000;//���_�l
	this->counter_increment_1_score = theoretical_value % Counter::notes_num;
}

void NotesController::finalize()
{
	delete this->result_creater;
	this->lane_data.clear();
}

void NotesController::update()
{
	callUpdate(lane_data["D"]);
	callUpdate(lane_data["F"]);
	callUpdate(lane_data["J"]);
	callUpdate(lane_data["K"]);
}

void NotesController::draw(bool a_blend)
{
	callDraw(lane_data["D"]);
	callDraw(lane_data["F"]);
	callDraw(lane_data["J"]);
	callDraw(lane_data["K"]);
}

void NotesController::add_score(JudgeResult jr)
{
	//�Q�[�W�̏㏸��
	int gauge_add_balue = (ScreenData::width / 4 / 100);

	int add_score = 0;
	//���茋�ʂ�`�悷�邽�߂̃I�u�W�F�N�g��vector�ɒǉ�
	//���茋�ʂ��ǂ����������ŃX�R�A�𑝉�������
	const int theoretical_value = 110000;//���_�l
	switch (jr)
	{
	case JudgeResult::perfect:
		//��������X�R�A�̒l������
		add_score = theoretical_value / Counter::notes_num;
		//�J�E���^�㏸
		Counter::perfect_cnt++;
		Counter::combo_cnt++;
		//�N���A�Q�[�W�㏸
		ClearGaugeUI::clear_gauge->draw_width += gauge_add_balue;

		if (this->counter_increment_1_score > 0) {
			this->counter_increment_1_score--;
			add_score += 1;
		}
		break;
	case JudgeResult::good:
		//��������X�R�A�̒l������
		add_score = theoretical_value / Counter::notes_num / 2;
		//�J�E���^�㏸
		Counter::good_cnt++;
		Counter::combo_cnt++;
		//�N���A�Q�[�W�㏸
		ClearGaugeUI::clear_gauge->draw_width += (gauge_add_balue / 2);

		if (this->counter_increment_1_score > 0) {
			this->counter_increment_1_score--;
			add_score += 1;
		}
		break;
	case JudgeResult::miss:
		//��������X�R�A�̒l������
		add_score = 0;
		//�J�E���^�㏸
		Counter::miss_cnt++;
		//�N���A�Q�[�W����
		ClearGaugeUI::clear_gauge->draw_width -= gauge_add_balue;
		break;
	default:
		throw("�X�R�A�㏸���ɔ��茋�ʂɖ����Ȓl�������Ă���");
	}
	//���݃X�R�A�ɉ��Z����
	Necessary::score = Necessary::score + add_score;
}
