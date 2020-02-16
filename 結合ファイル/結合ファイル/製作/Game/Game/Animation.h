#pragma once
#include <memory>
#include "GraphicResource.h"
#include"Purpose.h"

//アニメーションを行う

class Animation {
private:
	std::shared_ptr<GraphicObject> object;
	int current_anime;//何枚目にいるか
	int current_rate;

	void switch_anime();
public:
	Animation();
	~Animation();
	void draw_anime(Point);
	void draw_anime(Vector2);
	void set(std::string);
};