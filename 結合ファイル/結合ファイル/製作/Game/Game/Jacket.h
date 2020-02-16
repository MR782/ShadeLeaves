#pragma once
#include"Object.h"

//ジャケット画像を表示

class Jacket : public Object {
	void change_jacket();//選択楽曲に応じて画像を切り替える
	std::string now_select;//選択中の楽曲
	std::string pre_select;//1フレーム前の選択楽曲
public:
	void initialize()override;
	void finalize()override;
	void update()override;
};