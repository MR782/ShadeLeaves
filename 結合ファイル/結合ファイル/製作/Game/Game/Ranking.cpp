#include "Ranking.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"
#include"Necessary.h"
#include"GraphicResource.h"
#include"BasicUI.h"

Ranking::Ranking()
{
	this->font_size = 0;
}

void Ranking::initialize()
{
	//プレイしたリザルトをテキストに保存する
	switch (Necessary::get_music()) {
	case MusicList::fancie:
		//ラベルに入っているパスからデータを読み込む
		this->data.input_textfile_data("./data/txt/rank_fan.txt");
		//ゲームのスコアをランキングに追加
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_fan.txt");
		break;
	case MusicList::monoceros:
		//ラベルに入っているパスからデータを読み込む
		this->data.input_textfile_data("./data/txt/rank_mono.txt");
		//ゲームのスコアをランキングに追加
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_mono.txt");
		break;
	case MusicList::m3_500:
		//ラベルに入っているパスからデータを読み込む
		this->data.input_textfile_data("./data/txt/rank_m3.txt");
		//ゲームのスコアをランキングに追加
		this->data.input_ranking(Necessary::score);
		this->data.output_textfile_data("./data/txt/rank_m3.txt");
		break;
	}
	//Top3のデータを持ってくる
	this->rank_data = this->data.get_rank(5);
	//テキストの初期化
	this->font_size = 32;
	this->score_rank_label_header.set_font("%d : ", Point(), create_font(this->font_size, 16, false), setColor(Color::Black));
	this->score_rank_label.set_font("%d", Point(), create_font(this->font_size, 16, false), setColor(Color::Black));
}

void Ranking::finalize()
{
	this->rank_data.clear();
}

void Ranking::update()
{
	this->data.reset_ranking();
	//選択楽曲によってスコア表示のためのテキストファイルを入れ替える
	switch (Necessary::get_music()) {
	case MusicList::fancie:	
		this->data.input_textfile_data("./data/txt/rank_fan.txt");	
		break;
	case MusicList::monoceros:
		this->data.input_textfile_data("./data/txt/rank_mono.txt");
		break;
	case MusicList::m3_500:
		this->data.input_textfile_data("./data/txt/rank_m3.txt");
	}
	this->rank_data = this->data.get_rank(5);
}

void Ranking::draw(Point pos)
{
	int cnt = 1;
	for (auto itr = this->rank_data.begin(); itr != this->rank_data.end(); itr++,cnt++) {
		//座標セット
		this->score_rank_label_header.setPosition(Point(pos.x,pos.y + cnt * this->font_size));
		this->score_rank_label.setPosition(Point(pos.x + (this->score_rank_label_header.text_width * (font_size / 2)),pos.y + cnt * this->font_size));
		//描画
		this->score_rank_label_header.drawformat_font(cnt);
		this->score_rank_label.drawformat_font((*itr).score);
	}
}
