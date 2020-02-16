#pragma once
#include"Object.h"
#include"Notes.h"

class Effect : public Object {
protected:
	int death_cnt;//©g‚ªÁ–Å‚·‚é‚Ü‚Å‚ÌŠÔ
public:
	Effect();
	virtual void initialize()final;
	virtual void finalize()override = 0;
	virtual void update()override = 0;
	bool is_death(int death_time);
	virtual void set_effect(std::string name, Vector2 pos);
};