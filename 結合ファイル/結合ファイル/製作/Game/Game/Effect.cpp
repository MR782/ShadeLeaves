#include "Effect.h"

Effect::Effect()
{
	this->death_cnt = 0;
}

void Effect::initialize()
{
}

bool Effect::is_death(int death_time)
{
	return this->death_cnt >= death_time;
}

void Effect::set_effect(std::string name,Vector2 pos)
{
	this->position = pos;
	this->anime->set(name);
}