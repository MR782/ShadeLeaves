#include "TitleUI.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

TitleUI::TitleUI()
{
	this->guide = nullptr;
	this->title_logo = nullptr;
}

void TitleUI::initialize()
{
	//�������m��
	this->guide = new TitleGuide();
	this->title_mv = std::make_unique<Movie>();
	this->title_logo = new TitleLogo();
	//�m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	MemoryFunction::check_mem(this->guide);
	MemoryFunction::check_mem(this->title_logo);
	if (this->title_mv == nullptr)throw"TitleUI movie is null_ptr";
	
	//�摜���Z�b�g����
	this->guide->initialize();
	this->title_logo->initialize();
	title_mv->set("reaf");
}

void TitleUI::finalize()
{
	delete this->guide;
	delete this->title_logo;
}

void TitleUI::update()
{
	this->guide->update();
}

void TitleUI::draw()
{
	//�t���ς̕`��
	this->title_mv->draw();
	//���W����
	//�`��
	this->title_logo->draw();
	//UI�̕`��
	this->guide->draw(true);
}