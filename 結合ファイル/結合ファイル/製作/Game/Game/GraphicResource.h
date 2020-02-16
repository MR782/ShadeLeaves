#pragma once
#include <iostream>
#include <memory>
#include "json11.hpp"

//画像読み込みなどを行う

class GraphicObject {
private:
	friend class GraphicResource;//initialize()でデフォルト値を入れるため必要
	bool exist;//データがすでに入っているか
	std::string path;	//ファイルパス
	std::vector<std::string> scopes;//読み込むときの名前
	int vertical, horizontal;//縦、横に画像を割った時の数
	void set_default_to_empty();	//オブジェクトにデフォルト値を設定する
	bool exits_scope(std::string);	//スコープが存在しているか調べる
public:
	GraphicObject();
	bool loop;	//ループの有無
	std::string name;//名前
	int *handle;//ハンドル
	int width, height, interval, sheets;//画像の大きさ、画像切り替えのインターバル、画像を割った時の最大数
};

class GraphicResource
{
public:
	static int load(std::string _scope);
	static void initialize();
	//複数が同じ画像を使う可能性があるためshared_ptrとする
	static std::shared_ptr<GraphicObject> get(std::string name);//引数のnameを持つオブジェクトポインタを返す
	static void finalize();//使い終わったデータを全削除
	static int* get_handle(std::string name_);//ハンドルのみ受け取らせる(Animationクラスを使用しない描画で使用)
private:
	static void delete_all();//全ての画像をメモリから解放する
	static bool exist_name(std::string);		//名前が存在しているか調べる
	static void register_graph(GraphicObject&);	//画像を登録する
	static std::vector<std::shared_ptr<GraphicObject>> graph;	//画像データなどを保持するオブジェクト
};