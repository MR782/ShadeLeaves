#pragma once
#include"Object.h"

class GameSceneJacket : public Object {
	std::string set_jacket();
	int jacket_handle;
public:
	GameSceneJacket();
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false)override;
};