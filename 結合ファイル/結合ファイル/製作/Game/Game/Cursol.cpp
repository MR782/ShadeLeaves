#include "Cursol.h"

void Cursol::initialize()
{
	//�������m��
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "Cursol anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
}

void Cursol::finalize()
{
	this->anime.reset();
}

void Cursol::set_position(Vector2 pos)
{
	//���W�Z�b�g
	this->position = pos;
}

void Cursol::set_graph(std::string name)
{
	if (this->anime == nullptr) throw "could not memory allocation";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	//�摜�Z�b�g
	this->anime->set(name);
}
