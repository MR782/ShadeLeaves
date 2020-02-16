#pragma once
#include<iostream>
#include"json11.hpp"

//音楽ファイルの読み込みや再生を行う

class AudioObject {
	friend class Audio;
	bool exist;//読み込んで膝窩のフラグ
	std::vector<std::string> scopes;//読み込み時の名前

	bool exist_scope(std::string);
	void set_default();//値が入っていない場合デフォルトで入力
public:
	AudioObject();
	bool loop;//ループ再生するかのフラグ
	std::string  name;//再生又は停止時にどれか判断する識別子
	std::string  path;//音楽ファイルまでのパス
	int handle;//音楽ハンドル
};

class Audio {
private:
	static std::vector<std::shared_ptr<AudioObject>> audioobj;
	static void register_audio(AudioObject&);
public:
	static void initialize();
	static void play(std::string name,bool is_multiple = true);
	static int load(std::string name);
	static void stop_all();
	static void stop(std::string name);
	static void set_volume_audioname(std::string name,int percent);
	static void set_volume_audioscope(std::string scope, int percent);
	static void stop_scope(std::string scope);
	static bool check_play(std::string);//特定のBGMが再生中か調べる
	static bool check_play_scope(std::string scope);//指定したスコープのBGMがなっているか確認
	static void finalize();
	static void delete_soundData_name(std::string name);//特定の音楽データをメモリから削除(nameで指定)
	static void delete_soundData_scope(std::string scope);//特定の音楽データをメモリから削除(scopeで指定)
	static void delete_sound_dataAll();//読み込み済みの音楽データをすべてメモリから削除
};