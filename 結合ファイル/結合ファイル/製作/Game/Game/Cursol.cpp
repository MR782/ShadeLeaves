#include "Cursol.h"

void Cursol::initialize()
{
	//メモリ確保
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "Cursol anime is null_ptr";//メモリ確保できていないなら例外を投げる
}

void Cursol::finalize()
{
	this->anime.reset();
}

void Cursol::set_position(Vector2 pos)
{
	//座標セット
	this->position = pos;
}

void Cursol::set_graph(std::string name)
{
	if (this->anime == nullptr) throw "could not memory allocation";//メモリ確保できていないなら例外を投げる
	//画像セット
	this->anime->set(name);
}
