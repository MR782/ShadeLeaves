#include "Movie.h"
#include"./dxlib/DxLib.h"
#include"ScreenSystem.h"

void Movie::draw()
{
	//���[�r�[���Đ�����Ă��Ȃ��Ȃ�
	if (MovieResource::check_play(object->name) == false) {
		//���[�v�A���Ȃ�ŏ��ɖ߂���
		if (object->loop == true) {
			SeekMovieToGraph(object->handle, 0);
		}
		//�Đ�
		PlayMovieToGraph(object->handle);//�Đ�
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//�u�����h���[�h��ݒ�
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, object->handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�u�����h���[�h���I�t
}

void Movie::set(std::string name)
{
	if (object != MovieResource::get(name)) {
		//���̃��[�r�[�Ɛݒ肷�郀�[�r�[���Ⴄ�Ȃ�
		object = MovieResource::get(name);//�X�V
	}
}
