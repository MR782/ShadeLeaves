#pragma once
#include"Animation.h"
#include"Purpose.h"

//ゲームオブジェクトの親クラス

class Object {
protected:
	enum class BlendState {
		Addition,
		Subtraction
	};
	int blend_cnt;//ラベルの画像を半透明にしたりするためのカウンタ
	BlendState b_state;//加算か減算かを判断
	void check_blendCnt();//カウンタの状態で更新を行う

	std::unique_ptr<Animation> anime;//画像描画
	Vector2 position;//座標
public:
	Object();
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void update();
	virtual void draw(bool a_blend = false);

	void set_position(Vector2 pos);
	Vector2 get_position();//座標を受け取らせる
};