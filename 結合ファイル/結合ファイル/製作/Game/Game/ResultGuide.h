#pragma once
#include"Object.h"

//���U���g��ʂł̃K�C�h�\��

class ResultGuide : public Object {
public:
	ResultGuide();
	void initialize()override;
	void finalize()override;
	void update()override;
};