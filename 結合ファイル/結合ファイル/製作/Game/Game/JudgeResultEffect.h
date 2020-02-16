#pragma once
#include"Effect.h"

class JudgeResultEffect : public Effect {
public:
	JudgeResultEffect();
	void finalize()override;
	void update()override;
};
