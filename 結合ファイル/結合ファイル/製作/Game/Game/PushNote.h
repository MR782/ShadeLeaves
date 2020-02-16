#pragma once
#include"Notes.h"

class PushNotes : public Notes {
	//メソッド
	JudgeResult judge()override;//判定を行う
public:
	void initialize()override;
};