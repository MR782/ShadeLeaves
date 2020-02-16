#pragma once
#include"Object.h"

//楽曲選択時のカーソル

class Cursol : public Object {
public:
	void initialize()override;
	void finalize()override;

	void set_position(Vector2 pos);//座標セット
	void set_graph(std::string name);//画像セット
};