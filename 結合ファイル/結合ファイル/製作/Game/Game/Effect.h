#pragma once
#include"Object.h"
#include"Notes.h"

class Effect : public Object {
protected:
	int death_cnt;//自身が消滅するまでの時間
public:
	Effect();
	virtual void initialize()final;
	virtual void finalize()override = 0;
	virtual void update()override = 0;
	bool is_death(int death_time);
	virtual void set_effect(std::string name, Vector2 pos);
};