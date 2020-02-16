#pragma once
#include"Object.h"

//リザルト画面でのガイド表示

class ResultGuide : public Object {
public:
	ResultGuide();
	void initialize()override;
	void finalize()override;
	void update()override;
};