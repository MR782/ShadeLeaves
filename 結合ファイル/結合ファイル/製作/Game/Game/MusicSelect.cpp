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
	//リソースの読み込み
	MovieResource::load("m_select");
	//BGMを読み込み
	Audio::load("select");
	//再生
	//Audio::play("m_select", false);
	//メモリ確保
	this->ms_ui = new MusicSelectUI();
	MemoryFunction::check_mem(this->ms_ui);
	//データの初期化
	//背景画像を格納
	this->back_graph_handle = GraphicResource::get_handle("select_back")[0];
	//選択中の楽曲を初期化
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
		//UIの更新処理
		this->ms_ui->update();
		set_speed();
	}
	//----------------------------------------------------------------------
	//Enterキーが押されたらシーン設定
	scene_change(KeyBoard::key_down(KEY_INPUT_RETURN), SceneData::game);
	//-----------------------------------------------------------------------
}

void MusicSelect::draw()
{
	//背景画像を拡縮描画
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//UIの描画
	this->ms_ui->draw();
}

void MusicSelect::set_speed()
{
	//スピードを下げる
	if (KeyBoard::key_down(KEY_INPUT_D) || KeyBoard::key_down(KEY_INPUT_F)) {
		//効果音を鳴らす
		Audio::play("cursol");
		//現状0にはしない
		if (Necessary::speed <= 1) return;
		Necessary::speed = Necessary::speed - 1;
	}
	//スピードを上げる
	if (KeyBoard::key_down(KEY_INPUT_J) || KeyBoard::key_down(KEY_INPUT_K)) {
		//効果音を鳴らす
		Audio::play("cursol");
		//スピード上限を20とする
		if (Necessary::speed >= 20) return;
		Necessary::speed = Necessary::speed + 1;
	}
}