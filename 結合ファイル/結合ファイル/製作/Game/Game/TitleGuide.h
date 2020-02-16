#pragma once
#include"Object.h"

class TitleGuide : public Object {
public:
	TitleGuide();
	void initialize()override;
	void finalize()override;
	void update()override;
};