#pragma once
#include"Notes.h"

class HoldNotes : public Notes {
	//���\�b�h
	JudgeResult judge()override;//������s��
	virtual bool check_key();
public:
	void initialize()override;
};