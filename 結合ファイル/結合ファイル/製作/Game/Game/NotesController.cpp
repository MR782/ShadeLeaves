#include "NotesController.h"
#include"MemoryFunc.h"
#include"ScreenSystem.h"
#include"GameScene.h"

bool NotesController::delete_notes(std::unique_ptr<Notes>& note)
{
	//すでに判定を行っているなら
	if ((*note).get_result() != JudgeResult::none) {
		add_score((*note).get_result());
		//データを初期化してvectorに挿入
		MemoryFunction::check_mem(result_creater);
		result_creater->create((*note).get_result(), (*note).get_judge_key());
		//判定結果のエフェクトを追加
		std::unique_ptr<Effect> judge_effect;
		//メモリ確保
		judge_effect = std::make_unique<JudgeResultEffect>();
		//生成位置の定義
		const int judge_line_height = 16;
		Vector2 create_pos = Vector2((*note).get_position().x, Model::judge_line->get_position().y - (judge_line_height / 2));
		//座標と種類をセットする
		judge_effect->set_effect(this->effect_kind[(*note).get_result()], create_pos);
		//エフェクトの登録
		Model::effects.push_back(std::move(judge_effect));

		return true;
	}
	return false;
}

void NotesController::callUpdate(std::vector<std::unique_ptr<Notes>>& lane)
{
	for (auto itr = lane.begin(); itr != lane.end(); itr++) {
		(*itr)->update();
		//削除処理
		if (delete_notes((*itr))) {
			//条件を満たしているなら配列から削除
			lane.erase(itr);
			//最後でなければ新たな先頭を決める
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
	//メモリ確保
	this->result_creater = new JudgeResultCreater();
	MemoryFunction::check_mem(this->result_creater);
	//レーンごとに配置(ゲームシーンに登録したデータを移動する)
	if (Model::notes.empty()) throw"ノーツデータが空っぽです";
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
			throw"予期しないデータが含まれている";
		}
	}
	//先頭を決める
	lane_data["D"].at(0)->set_is_first(true);
	lane_data["F"].at(0)->set_is_first(true);
	lane_data["J"].at(0)->set_is_first(true);
	lane_data["K"].at(0)->set_is_first(true);

	//理論値のためどれだけのノーツ数だけスコアに1加算するか決定
	const int theoretical_value = 110000;//理論値
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
	//ゲージの上昇量
	int gauge_add_balue = (ScreenData::width / 4 / 100);

	int add_score = 0;
	//判定結果を描画するためのオブジェクトをvectorに追加
	//判定結果がどうだったかでスコアを増加させる
	const int theoretical_value = 110000;//理論値
	switch (jr)
	{
	case JudgeResult::perfect:
		//増加するスコアの値を決定
		add_score = theoretical_value / Counter::notes_num;
		//カウンタ上昇
		Counter::perfect_cnt++;
		Counter::combo_cnt++;
		//クリアゲージ上昇
		ClearGaugeUI::clear_gauge->draw_width += gauge_add_balue;

		if (this->counter_increment_1_score > 0) {
			this->counter_increment_1_score--;
			add_score += 1;
		}
		break;
	case JudgeResult::good:
		//増加するスコアの値を決定
		add_score = theoretical_value / Counter::notes_num / 2;
		//カウンタ上昇
		Counter::good_cnt++;
		Counter::combo_cnt++;
		//クリアゲージ上昇
		ClearGaugeUI::clear_gauge->draw_width += (gauge_add_balue / 2);

		if (this->counter_increment_1_score > 0) {
			this->counter_increment_1_score--;
			add_score += 1;
		}
		break;
	case JudgeResult::miss:
		//増加するスコアの値を決定
		add_score = 0;
		//カウンタ上昇
		Counter::miss_cnt++;
		//クリアゲージ減少
		ClearGaugeUI::clear_gauge->draw_width -= gauge_add_balue;
		break;
	default:
		throw("スコア上昇時に判定結果に無効な値が入っている");
	}
	//現在スコアに加算する
	Necessary::score = Necessary::score + add_score;
}
