#include "ScreenFunction.h"
#include"ScreenHelperGraph.h"
#include"./dxlib/DxLib.h"
#include"ScreenSystem.h"
#include"Necessary.h"

#define FadeSpeed 5

int ScreenFunction::blendcnt;

void ScreenFunction::initialize()
{
	//�t�F�[�h�A�E�g�A�C���p�̉摜�����[�h
	ScreenHelperGraph::black_graph = LoadGraph("./data/graph/screen/black_screen.png");
	ScreenHelperGraph::white_graph = LoadGraph("./data/graph/screen/white_screen.png");
	if (ScreenHelperGraph::black_graph == -1 || ScreenHelperGraph::white_graph == -1) {
		throw"ScreenHelperGraph is not found";
	}
	blendcnt = 0;//�����͓����ɂ��Ă���
}

void ScreenFunction::finalize()
{
	DeleteGraph(ScreenHelperGraph::black_graph);
	DeleteGraph(ScreenHelperGraph::white_graph);
}

void ScreenFunction::FeedOut()
{
	//�u�����h�J�E���g�����Z���Ă���
	if (check_blend_max() == false) {//255��菬�����l�Ȃ�
		blendcnt += FadeSpeed;
	}
}

void ScreenFunction::FeedIn()
{
	//�u�����h�J�E���g�����Z���Ă���
	if (check_blend_min() == false) {//0���傫���l�Ȃ�
		blendcnt -= FadeSpeed;
	}
}

void ScreenFunction::update()
{
	if (Necessary::get_fade_ioFlag()) {//�t�F�[�h�A�E�g�̍��}��������
		FeedOut();//�t�F�[�h�A�E�g���Ăяo��
	}
	else {//�t�F�[�h�A�E�g�̍��}�����ĂȂ��Ȃ�
		FeedIn();//�t�F�[�h�C�����Ăяo��
	}
}

void ScreenFunction::draw(int screen_graph)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendcnt);		//�u�����h���[�h�����ɐݒ�
	//�n�_�i0,0�j����I�_(��ʃT�C�Y�iX�j,��ʃT�C�Y(Y)�܂ň����Ŏ󂯎�����摜�n���h����`��)
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, screen_graph, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
}

bool ScreenFunction::check_blend_max()
{
	return blendcnt >= 255;//255���傫���Ȃ�true
}

bool ScreenFunction::check_blend_min()
{
	return blendcnt <= 0;//0��菬�����Ȃ�true
}
