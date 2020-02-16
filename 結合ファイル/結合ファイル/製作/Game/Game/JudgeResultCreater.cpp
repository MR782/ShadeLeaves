#include "JudgeResultCreater.h"
#include"JudgeResultUI.h"
#include"MemoryFunc.h"
#include"GameScene.h"

void JudgeResultCreater::create(JudgeResult result,JudgeKey lane)
{
	std::unique_ptr<JudgeResultUI> jr_ui;
	jr_ui = std::make_unique<JudgeResultUI>();//�������m��
	if (jr_ui == nullptr) throw ("JudgeResult is null_ptr");//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	jr_ui->initialize();//������
	std::string graph_name = "";//�摜�̖��O
	//���肵�����W�ɐ�������
	switch (lane)
	{
	case JudgeKey::Key_D: 	jr_ui->set_lane(JudgeKey::Key_D); break;
	case JudgeKey::Key_F:	jr_ui->set_lane(JudgeKey::Key_F); break;
	case JudgeKey::Key_J:	jr_ui->set_lane(JudgeKey::Key_J); break;
	case JudgeKey::Key_K:	jr_ui->set_lane(JudgeKey::Key_K); break;
	}
	//���茋�ʂɊ�Â��ĉ摜���Z�b�g
	switch (result)
	{
	case JudgeResult::perfect:    jr_ui->set_graph("perfect"); break;
	case JudgeResult::good:       jr_ui->set_graph("good");    break;
	case JudgeResult::miss:       jr_ui->set_graph("miss");    break;
	default:	throw"���茋�ʂ̒l�������Ȓl�ł�";
	}

	Model::judge_results.push_back(std::move(jr_ui));
}
