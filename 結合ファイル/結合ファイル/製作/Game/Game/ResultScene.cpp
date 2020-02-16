#include "ResultScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"ScreenFunction.h"
#include"Audio.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

Result::Result()
{
	this->result_ui = nullptr;
}

void Result::initialize()
{
	//リソースの読み込み
	Audio::load("result");
	MovieResource::load("reaf");
	//メモリ確保
	this->result_ui = new ResultUI();
	MemoryFunction::check_mem(this->result_ui);
	//データの初期化
	this->back_graph_handle = GraphicResource::get_handle("result_back")[0];
	this->result_ui->initialize();
	//音楽再生
	Audio::play("result");
}

void Result::finalize()
{
	Audio::stop("result");
	Audio::delete_soundData_name("result");
	MovieResource::delete_movie_mem("reaf");
	this->result_ui->finalize();
	delete this->result_ui;
}

void Result::update()
{
	if (ScreenFunction::check_blend_min()) {
		this->result_ui->update();
	} 
	//シーン切り替え-----------------------------------------
	scene_change(KeyBoard::key_down(KEY_INPUT_RETURN) && this->result_ui->IsSceneTransition(), SceneData::m_select);
}

void Result::draw()
{
	//背景を描画
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//リザルト描画
	this->result_ui->draw();
}
