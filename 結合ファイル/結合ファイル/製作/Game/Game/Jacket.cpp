#include "Jacket.h"
#include"ScreenSystem.h"
#include"Audio.h"
#include"Necessary.h"

void Jacket::initialize()
{
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr) throw "Jacket anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���

	switch (Necessary::get_music()) {
	case MusicList::fancie:
		this->now_select = "fancieDemo";
		this->pre_select = "fancieDemo";
		this->anime->set("fancie_jacket");//�����摜
		break;
	case MusicList::monoceros:
		this->now_select = "monocerosDemo";
		this->pre_select = "monocerosDemo";
		this->anime->set("monoceros_jacket");//�����摜���Z�b�g
		break;
	case MusicList::m3_500:
		this->now_select = "m3_500Demo";
		this->pre_select = "m3_500Demo";
		this->anime->set("m3_500_jacket");
	}
	//���W�Z�b�g
	const int jacket_width = 320;//�摜�̑傫��(�h�b�g�P��)
	const int jacket_height =480;//�摜�̑傫��(�h�b�g�P��)
	this->position = Vector2((ScreenData::width / 2) - (jacket_width / 8 * 7), (ScreenData::height / 2) - (jacket_height / 2));
}

void Jacket::finalize()
{
	Audio::stop_scope("all");
	this->anime.reset();
}

void Jacket::update()
{
	//�I���y�Ȃ�1�t���[���O�ƈႤ�Ȃ�
	if (pre_select != now_select) {
		Audio::stop_scope("bgm");
	}

	pre_select = now_select;
	//�W���P�b�g�摜�̕ύX
	change_jacket();
}

void Jacket::change_jacket()
{
	//��Փx�Ɗy�Ȃɂ���ĉ摜��ς���
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		now_select = "monocerosDemo";
		this->anime->set("monoceros_jacket");
		
		break;
	case MusicList::fancie:
		now_select = "fancieDemo";
		this->anime->set("fancie_jacket");
		break;
	case MusicList::m3_500:
		now_select = "m3_500Demo";
		this->anime->set("m3_500_jacket");
	}
	Audio::play(now_select, false);
}
