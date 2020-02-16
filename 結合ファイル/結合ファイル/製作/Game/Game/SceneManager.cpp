#include "SceneManager.h"
#include"ScreenFunction.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"MovieResource.h"
#include"MemoryFunc.h"
#include"ScreenHelperGraph.h"

void SceneManager::initialize()
{
	//リソースの読み込む準備(Jsonが無いと例外を投げる)
	GraphicResource::initialize();
	Audio::initialize();
	MovieResource::initialize();

	//フェードインアウトの準備
	ScreenFunction::initialize();

	//リソースの読み込み
	GraphicResource::load("all");
	Audio::load("system");//システム音の読み込み
	Audio::set_volume_audioscope("system", 50);
	//メモリ確保
	this->title = new Title();
	MemoryFunction::check_mem(this->title);
	//初期シーンをセット
	Necessary::set_scene(SceneData::title);
	this->title->initialize();
}

void SceneManager::finalize()
{
	//リソースの開放
	Audio::stop_all();
	Audio::finalize();
	MovieResource::finalize();
	ScreenFunction::finalize();
	GraphicResource::finalize();
	//現在のシーンによって処理を変える
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
	//シーンごとの更新処理を呼ぶ
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
		throw ("シーンが初期化されていないもしくは無効な値が入力されている");
		break;
	}
	ScreenFunction::update();
}

void SceneManager::draw()
{
	//シーンごとの描画処理を呼ぶ
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
		throw "シーンが初期化されていないもしくは無効な値が入力されました";
		break;
	}
	//フェードアウト用画像の描画
	ScreenFunction::draw(ScreenHelperGraph::black_graph);
}

void SceneManager::change_scene(SceneData next_scene)
{
	//現在のシーンの終了処理を行う
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
		throw ("シーンが初期化されていないもしくは無効な値が入力されている");
		break;
	}
	//次のシーンの初期化処理を行う
	switch (next_scene)
	{
	case SceneData::title:
		this->title = new Title();//メモリ確保
		MemoryFunction::check_mem(this->title);
		this->title->initialize();
		break;
	case SceneData::m_select:
		this->m_select = new MusicSelect();//メモリ確保
		if (this->m_select == nullptr) throw "MusicSelectScene is null_ptr";//メモリ確保できなかったら例外を投げる
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
		throw "シーンが初期化されていないもしくは無効な値が入力されました";
		break;
	}
	//シーンの更新
	Necessary::set_scene(next_scene);
}