#include "BasicUI.h"
#include"Mouse.h"
#include"Necessary.h"
#include"./dxlib/DxLib.h"

int create_font(int size, int thick, bool is_anti_alias)
{
	int handle;
	//アンチエイリアスを使用するなら
	if (is_anti_alias) {
		handle = CreateFontToHandle("", size, thick, DX_FONTTYPE_ANTIALIASING);
	}
	else {
		handle = CreateFontToHandle("", size, thick, DX_FONTTYPE_NORMAL);
	}
	return handle;
}

int setColor(Color color)
{
	unsigned int _color = 0;
	switch (color)
	{
	case Color::Orange:
		_color = GetColor(255, 165, 0);
		break;
	case Color::Red:
		_color = GetColor(255, 0, 0);
		break;
	case Color::Blue:
		_color = GetColor(0, 0, 255);
		break;
	case Color::Green:
		_color = GetColor(0, 255, 0);
		break;
	case Color::Yellow:
		_color = GetColor(255, 255, 0);
		break;
	case Color::Purple:
		_color = GetColor(255, 0, 255);
		break;
	case Color::Aqua:
		_color = GetColor(0, 255, 255);
		break;
	case Color::White:
		_color = GetColor(255, 255, 255);
		break;
	case Color::Black:
		_color = GetColor(0, 0, 0);
		break;
	case Color::Gray:
		_color = GetColor(128, 128, 128);
	}
	return _color;
}

Text::Text()
{
	this->color = 0;
	this->font = 0;
	this->text_width = 0;
	this->str = "";
	this->pos = { 0,0 };
}

void Text::set_font(const char* str, Point pos, int font, int color)
{
	this->str = str;
	this->pos = pos;
	this->font = font;
	this->color = color;
	this->text_width = (int)strlen(this->str);
}

void Text::delete_font()
{
	DeleteFontToHandle(this->font);
}

void Text::draw_font()
{
	DrawStringToHandle(this->pos.x, this->pos.y, this->str, this->color, this->font);
}

void Text::setPosition(Point pos)
{
	this->pos = pos;
}

