#pragma once
#include"Notes.h"

class HoldNotes : public Notes {
	//メソッド
	JudgeResult judge()override;//判定を行う
	virtual bool check_key();
public:
	void initialize()override;
};