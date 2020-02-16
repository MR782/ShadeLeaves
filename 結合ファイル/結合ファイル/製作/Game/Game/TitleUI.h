#pragma once
#include<memory>
#include"Animation.h"
#include"Scene.h"
#include"Movie.h"
#include"TitleLogo.h"
#include"TitleGuide.h"

class TitleUI {
	TitleGuide* guide;//�ē������̉摜
	TitleLogo* title_logo;//�^�C�g�����S
	std::unique_ptr<Movie> title_mv;
public:
	TitleUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};