#pragma once
#include"Object.h"
#include"BasicUI.h"

//[リザルト]の表示

class ResultSceneTitle : public Object{
public:
	void initialize()override;
	void finalize()override;
};