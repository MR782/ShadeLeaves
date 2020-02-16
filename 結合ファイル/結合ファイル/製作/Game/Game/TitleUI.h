#pragma once
#include<memory>
#include"Animation.h"
#include"Scene.h"
#include"Movie.h"
#include"TitleLogo.h"
#include"TitleGuide.h"

class TitleUI {
	TitleGuide* guide;//ˆÄ“à•¶š‚Ì‰æ‘œ
	TitleLogo* title_logo;//ƒ^ƒCƒgƒ‹ƒƒS
	std::unique_ptr<Movie> title_mv;
public:
	TitleUI();
	void initialize();
	void finalize();
	void update();
	void draw();
};