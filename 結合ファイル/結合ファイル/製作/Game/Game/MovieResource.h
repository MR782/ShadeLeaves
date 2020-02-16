#pragma once
#include<memory>
#include<string>
#include<vector>

struct MovieObject {
	MovieObject();
	friend class MovieResource;
	std::string name;//識別名
	std::string path;//ファイルパス
	bool loop;//ループ再生するか
	int handle;//ハンドル
private:
	std::vector<std::string> scopes;//読み込み時の名前
	bool exist_scope(std::string);
	bool exist;//読み込み済みか判断
};

class MovieResource {
	static std::vector<std::shared_ptr<MovieObject>> movie_obj;//ムービーデータを格納する配列
	static void register_movie(MovieObject&);//オブジェクトを登録
public:
	static void initialize();
	static void finalize();
	static int load(std::string scope);//スコープ内を検索して一致するものをロードする
	static bool check_play(std::string name);//すでに再生されているか確認
	static void delete_movie_mem(std::string name);//メモリからムービーデータを削除する
	static std::shared_ptr<MovieObject> get(std::string name);//名前が一致するもののポインタを返す
};