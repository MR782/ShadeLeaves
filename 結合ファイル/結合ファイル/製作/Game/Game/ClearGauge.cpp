#include "ClearGauge.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"GameUI.h"
#include"./dxlib/DxLib.h"

void ClearGauge::initialize()
{
	this->draw_width = 0;
	this->clear_line_handle = GraphicResource::get_handle("clear_line")[0];
	this->gauge_handle = GraphicResource::get_handle("normal_gauge")[0];
}

void ClearGauge::finalize()
{
	this->anime.reset();
}

void ClearGauge::update()
{
	//0�ȏ�ő�l�̊Ԃŕϓ�����悤�ɂ���
	this->draw_width = min(this->draw_width, ScreenData::width / 4);
	this->draw_width = max(this->draw_width, 0);
	//�Q�[�W�̏㏸�ʂɉ����ĉ摜��ς���
	if (draw_width == ScreenData::width / 4) {
		this->clear_line_handle = GraphicResource::get_handle("clear_line_max")[0];
	}
	else if (draw_width > ScreenData::width / 5 - ScreenData::width / 100) {
		Necessary::clear_flag = true;
		this->gauge_handle = GraphicResource::get_handle("clear_gauge")[0];
		this->clear_line_handle = GraphicResource::get_handle("clear_line")[0];
	}
	//-----------------�N���A�{�[�_�[----------------------
	else {
		Necessary::clear_flag = false;
		this->gauge_handle = GraphicResource::get_handle("normal_gauge")[0];
	}
}

void ClearGauge::draw(bool a_blend)
{
	const int white_fream_width = 2;
	//�N���A�Q�[�W
	//��ʃT�C�Y�p�Ɋg�k���Ă���w�肵���͈͂����`�悵����
	DrawExtendGraph(ScreenData::width / 20 + white_fream_width,
		ScreenData::height / 3 + white_fream_width,
		max(this->draw_width - white_fream_width, ScreenData::width / 20 + white_fream_width),
		ScreenData::height / 3 + 51 - white_fream_width
		, this->gauge_handle, TRUE);

	//�N���A���C�� �摜�̕ύX
	DrawExtendGraph(ScreenData::width / 20 + white_fream_width, ScreenData::height / 3,
		ScreenData::width / 4, ScreenData::height / 3 + 50
		, this->clear_line_handle, TRUE);
}
