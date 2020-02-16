#include "JudgeResultEffect.h"

JudgeResultEffect::JudgeResultEffect()
{
	this->death_cnt = 0;
	this->anime = std::make_unique<Animation>();
}

void JudgeResultEffect::finalize()
{
	this->anime.reset();
}

void JudgeResultEffect::update()
{
	this->death_cnt++;
}


