#include "MovieResource.h"
#include"./dxlib/DxLib.h"
#include"json11.hpp"
#include<fstream>

std::vector<std::shared_ptr<MovieObject>> MovieResource::movie_obj;

bool MovieResource::check_play(std::string name)
{
	bool check = false;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			check = GetMovieStateToGraph((*itr)->handle);
		}
	}
	return check;
}

void MovieResource::register_movie(MovieObject& obj)
{
	//まだ読み込んでいないなら
	if (obj.exist == false) {
		//ハンドルにムービーデータを読み込む
		obj.handle = LoadGraph(obj.path.c_str());
		obj.exist = true;//読み込み済み
	}
}

void MovieResource::initialize()
{
	std::ifstream moviepath("./data/json/movie.json");//使用ファイル設定
	if (moviepath.fail()) throw("movie.json is not found.");//例外処理
	//Jsonを使用する準備------------------------------------------
	std::istreambuf_iterator<char> it(moviepath);
	std::istreambuf_iterator<char> last;
	std::string str_json(it, last);	//string形式のjson
	std::string err;
	json11::Json json = json11::Json::parse(str_json, err);//Jsonで使えるようにする
	//-------------------------------------------------------------
	for (auto& item : json["movie"].array_items()) {//ファイル内のデータ分繰り返す
		std::shared_ptr<MovieObject> movie = std::make_shared<MovieObject>();
		movie->exist = false;//まだ読み込んでいない
		movie->name = item["name"].string_value();//識別子
		movie->loop = item["loop"].bool_value();//ループの判断
		movie->path = item["path"].string_value();//ファイルのパス
		for (auto& scope : item["scope"].array_items()) {//読み込む際の識別子
			movie->scopes.push_back(scope.string_value());
		}
		movie_obj.push_back(std::move(movie));//所有権の移行
	}
	//ファイルを閉じてvectorに入れたのでデータを消す
	moviepath.close();
}

void MovieResource::finalize()
{
	movie_obj.clear();
}

int MovieResource::load(std::string scope_)
{
	int num = 0;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->exist == false) {//読み込まれていないなら
			if ((*itr)->exist_scope(scope_)) {
				register_movie(*(*itr));//登録
				num++;
			}
		}
	}
	return num;//番号を返す
}

void MovieResource::delete_movie_mem(std::string name)
{
	//指定したオブジェクトをメモリから消す
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			DeleteGraph((*itr)->handle);//ハンドルデータを削除
			(*itr)->exist = false;
		}
	}
}

std::shared_ptr<MovieObject> MovieResource::get(std::string name)
{
	std::shared_ptr<MovieObject> ret = nullptr;//空っぽの状態
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->name == name) {//その名前があるなら
			ret = (*itr);//そのオブジェクトを返す
		}
	}
	return ret;
}

MovieObject::MovieObject()
{
	this->exist = false;
	this->handle = 0;
	this->loop = false;
	this->name = "";
	this->path = "";
}

bool MovieObject::exist_scope(std::string scope_)
{
	bool check = false;
	//そのオブジェクトのスコープの数だけ繰り返す
	for (auto&& scope : scopes) {
		if (scope == scope_) {//引数とスコープが合致するものがあったら
			check = true;//trueにする
			break;
		}
	}
	return check;//調べた結果を返す
}
