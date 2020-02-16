#include "JudgeResultCreater.h"
#include"JudgeResultUI.h"
#include"MemoryFunc.h"
#include"GameScene.h"

void JudgeResultCreater::create(JudgeResult result,JudgeKey lane)
{
	std::unique_ptr<JudgeResultUI> jr_ui;
	jr_ui = std::make_unique<JudgeResultUI>();//メモリ確保
	if (jr_ui == nullptr) throw ("JudgeResult is null_ptr");//メモリ確保できていないなら例外を投げる
	jr_ui->initialize();//初期化
	std::string graph_name = "";//画像の名前
	//判定した座標に生成する
	switch (lane)
	{
	case JudgeKey::Key_D: 	jr_ui->set_lane(JudgeKey::Key_D); break;
	case JudgeKey::Key_F:	jr_ui->set_lane(JudgeKey::Key_F); break;
	case JudgeKey::Key_J:	jr_ui->set_lane(JudgeKey::Key_J); break;
	case JudgeKey::Key_K:	jr_ui->set_lane(JudgeKey::Key_K); break;
	}
	//判定結果に基づいて画像をセット
	switch (result)
	{
	case JudgeResult::perfect:    jr_ui->set_graph("perfect"); break;
	case JudgeResult::good:       jr_ui->set_graph("good");    break;
	case JudgeResult::miss:       jr_ui->set_graph("miss");    break;
	default:	throw"判定結果の値が無効な値です";
	}

	Model::judge_results.push_back(std::move(jr_ui));
}
