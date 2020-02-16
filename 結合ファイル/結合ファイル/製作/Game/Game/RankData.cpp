#include "RankData.h"
#include <string>
#include <algorithm>
#include <functional>
#include<fstream>
#include"./dxlib/DxLib.h"

RankData::RankData()
{
}

void RankData::input_ranking(int score_)
{
	Status state;
	state.score = score_;
	//ランキングの配列に追加
	ranking.push_back(state);

	swap_ranking(Sort::DESC);
	//ランキングのデータが50個以上あるなら
	if (ranking.size() > 50) {
		//50個以降を削除する
		ranking.erase(ranking.begin() + 50, ranking.end());
	}
}

void RankData::swap_ranking(Sort s)
{
	switch (s)
	{
	case RankData::ASC:
		//昇順に並び替える
		std::sort(ranking.begin(), ranking.end());
		break;
	case RankData::DESC:
		//降順に並び替える
		std::sort(ranking.begin(), ranking.end(), std::greater<Status>());
		break;
	}
}

void RankData::reset_ranking()
{
	//データを削除する
	ranking.clear();
}

void RankData::input_textfile_data(std::string filepath)
{
	reset_ranking();//データを削除
	std::ifstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "ranking text file is not found";
	Status state;
	while (!fp.eof()) {//末端ではないなら
		//データを入れる
		fp >> state.score;
		//vectorに入れる
		ranking.push_back(state);
	}
	//降順に並び替える
	swap_ranking(Sort::DESC);
	fp.close();//ファイルを閉じる
}

void RankData::output_textfile_data(std::string filepath)
{
	//ランキングの中身が空なら例外を投げる
	if (ranking.empty())throw "ranking data is empty";

	std::ofstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "text file is not found";
	swap_ranking(Sort::DESC);//並び替え

	int size = 0;
	for (auto itr = ranking.begin(); itr != ranking.end(); itr++, size++) {
		if (size < 50) {
			//最後でないなら改行する
			if (itr == ranking.end() - 1) fp << " " << itr->score;
			else fp << " " << itr->score << "\n";
		}
	}
	fp.close();//データを入れたら閉じる
}

void RankData::reset_textfile_data(std::string filepath)
{
	std::ofstream fp(filepath);
	//見つからないなら例外を投げる
	if (fp.fail()) "text file is not found";
	for (int i = 0; i < 50; ++i) {
		//    name      score
		if (i < 50 - 1) fp << "NULL" << 0 << "\n";
		else fp << "NULL" << 0;
	}
}

std::vector<RankData::Status> RankData::get_ranking()
{
	return this->ranking;
}

std::vector<RankData::Status> RankData::get_rank(int val)
{
	std::vector<Status> return_value;
	int cnt = 0;
	for (auto itr = ranking.begin(); itr != ranking.end(); itr++, cnt++) {
		if (cnt >= val) break;//指定数受け取ったらループを抜ける
		return_value.push_back(*itr);
	}
	return return_value;
}
