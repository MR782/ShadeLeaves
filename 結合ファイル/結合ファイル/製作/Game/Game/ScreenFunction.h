#pragma once

//フェードアウトやフェードインの処理

class ScreenFunction {
private:
	//フィールド
	static int blendcnt;//画像の透明度を示す
	//ブレンドカウントのチェックメソッド
	static void FeedOut();//暗くする処理
	static void FeedIn();//明るくする処理
public:
	static void initialize();//画像のロードなど
	static void finalize();//画像の開放など

	//画像の透明度に合わせてtrueかfalseを返す
	//brendcntが255を超えたらtrueを返す
	static bool check_blend_max();
	//brendcntが0を下回ったらtrueを返す
	static bool check_blend_min();//0になったらtrueを返す
	//どういうときに呼ぶかなどはシーンが決める

	static void update();
	static void draw(int screen_graph);
};