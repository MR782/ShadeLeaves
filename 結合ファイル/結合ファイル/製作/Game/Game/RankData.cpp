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
	//�����L���O�̔z��ɒǉ�
	ranking.push_back(state);

	swap_ranking(Sort::DESC);
	//�����L���O�̃f�[�^��50�ȏ゠��Ȃ�
	if (ranking.size() > 50) {
		//50�ȍ~���폜����
		ranking.erase(ranking.begin() + 50, ranking.end());
	}
}

void RankData::swap_ranking(Sort s)
{
	switch (s)
	{
	case RankData::ASC:
		//�����ɕ��ёւ���
		std::sort(ranking.begin(), ranking.end());
		break;
	case RankData::DESC:
		//�~���ɕ��ёւ���
		std::sort(ranking.begin(), ranking.end(), std::greater<Status>());
		break;
	}
}

void RankData::reset_ranking()
{
	//�f�[�^���폜����
	ranking.clear();
}

void RankData::input_textfile_data(std::string filepath)
{
	reset_ranking();//�f�[�^���폜
	std::ifstream fp(filepath);
	//������Ȃ��Ȃ��O�𓊂���
	if (fp.fail()) "ranking text file is not found";
	Status state;
	while (!fp.eof()) {//���[�ł͂Ȃ��Ȃ�
		//�f�[�^������
		fp >> state.score;
		//vector�ɓ����
		ranking.push_back(state);
	}
	//�~���ɕ��ёւ���
	swap_ranking(Sort::DESC);
	fp.close();//�t�@�C�������
}

void RankData::output_textfile_data(std::string filepath)
{
	//�����L���O�̒��g����Ȃ��O�𓊂���
	if (ranking.empty())throw "ranking data is empty";

	std::ofstream fp(filepath);
	//������Ȃ��Ȃ��O�𓊂���
	if (fp.fail()) "text file is not found";
	swap_ranking(Sort::DESC);//���ёւ�

	int size = 0;
	for (auto itr = ranking.begin(); itr != ranking.end(); itr++, size++) {
		if (size < 50) {
			//�Ō�łȂ��Ȃ���s����
			if (itr == ranking.end() - 1) fp << " " << itr->score;
			else fp << " " << itr->score << "\n";
		}
	}
	fp.close();//�f�[�^����ꂽ�����
}

void RankData::reset_textfile_data(std::string filepath)
{
	std::ofstream fp(filepath);
	//������Ȃ��Ȃ��O�𓊂���
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
		if (cnt >= val) break;//�w�萔�󂯎�����烋�[�v�𔲂���
		return_value.push_back(*itr);
	}
	return return_value;
}
