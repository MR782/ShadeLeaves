#pragma once
#include"MovieResource.h"

class Movie {
	std::shared_ptr<MovieObject> object;
public:
	void draw();
	void set(std::string name);//ムービーをセット
};