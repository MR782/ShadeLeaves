#pragma once
#include"MusicSelectUI.h"
#include"Scene.h"
//�v���C�y�Ȃ����߂�V�[��

class MusicSelect : public Scene{
	MusicSelectUI* ms_ui;
	void set_speed();
public:
	MusicSelect();
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw()override;
};