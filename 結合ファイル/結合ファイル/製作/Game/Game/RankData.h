#pragma once
#include<iostream>
#include<vector>

//テキストファイルからデータを受け取る
//データを追加する

class RankData {
public:
	//ランキングに表示するものの中身
	struct Status {
		Status() { score = 0; }
		//ソート用の判定
		bool operator < (const Status& right)const {
			return this->score < right.score;
		}
		bool operator > (const Status& right)const {
			return this->score > right.score;
		}
		int score;
	};
	//並び替え方法
	enum Sort {
		ASC,//昇順
		DESC//降順
	};
	//メソッド--------------------------------------------------
	RankData();
	//ランキングに追加する
	void input_ranking(int score_);
	//ランキングを並び替える デフォルトは降順
	void swap_ranking(Sort s = DESC);
	//ランキングの中身を削除
	void reset_ranking();
	//テキストファイルからデータを読み取ってくる
	void input_textfile_data(std::string filepath);
	//テキストファイルにデータを出力する
	void output_textfile_data(std::string filepath);
	//テキストファイルの中身をリセットする
	void reset_textfile_data(std::string filepath);
	//setter,getter----------------------------------------
	std::vector<Status> get_ranking();//ランキング全体を取得
	std::vector<Status> get_rank(int val);//ランキング取得個数指定
private:
	//全体のランキング
	std::vector<Status> ranking;
};