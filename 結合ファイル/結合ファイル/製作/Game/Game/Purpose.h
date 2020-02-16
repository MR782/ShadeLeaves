#pragma once
#define PI 3.1415926f

//ベクトル（ｘ、ｙの移動量など）
class Vector2 {
public:
	Vector2();
	Vector2(int, int);
	Vector2(float, float);
	Vector2 operator+=(Vector2& v2_) {
		this->x += v2_.x;
		this->y += v2_.y;
		return *this;
	}
	Vector2 operator<<(Vector2 v2_) {
		this->x = v2_.x;
		this->y = v2_.y;
		return *this;
	}
	Vector2 operator-(Vector2 v2_) {
		this->x -= v2_.x;
		this->y -= v2_.y;
		return *this;
	}
	float x;
	float y;
};

//点(x,y)のみの場合など
class Point {
public:
	Point();
	Point(int, int);
	Point(float, float);
	Point operator+=(Vector2& v2_) {
		this->x += (int)v2_.x;
		this->y += (int)v2_.y;
		return *this;
	}
	Point operator-(Point& pos) {
		this->x -= pos.x;
		this->y -= pos.y;
		return *this;
	}
	Point operator-(Vector2& pos) {
		this->x -= (int)pos.x;
		this->y -= (int)pos.y;
		return *this;
	}
	Point operator<<(Vector2 v2_) {
		this->x = (int)v2_.x;
		this->y = (int)v2_.y;
		return *this;
	}
	Point operator+=(Point p_) {
		this->x += p_.x;
		this->y += p_.y;
		return *this;
	}
	Point operator<<(Point p_) {
		this->x = p_.x;
		this->y = p_.y;
		return *this;
	}
	bool operator==(Point p_) {
		return this->x == p_.x && this->y == p_.y;
	}
	//移動時に小数点以下も移動量として受け取り可能にするためfloatとする
	int x;
	int y;
};

//矩形（ｘ、ｙ、ｗ、ｈ、）当たり判定、描画範囲など
class Rect {
public:
	Rect();
	Rect(int, int, int, int);
	Rect(float, float, float, float);
	Rect operator<<(Rect& r_);
	//矩形同士の当たり判定
	bool Hit(Rect);
	bool Hit(int, int);
	//オフセット
	Rect Offset(Point);
	Rect Offset(Vector2);
	Rect Offset(int, int);
	//x,y 座標など
	//w,h 幅(縦、横)
	int x;
	int y;
	int w;
	int h;
};