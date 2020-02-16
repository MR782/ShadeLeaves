#include "MovieResource.h"
#include"./dxlib/DxLib.h"
#include"json11.hpp"
#include<fstream>

std::vector<std::shared_ptr<MovieObject>> MovieResource::movie_obj;

bool MovieResource::check_play(std::string name)
{
	bool check = false;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			check = GetMovieStateToGraph((*itr)->handle);
		}
	}
	return check;
}

void MovieResource::register_movie(MovieObject& obj)
{
	//�܂��ǂݍ���ł��Ȃ��Ȃ�
	if (obj.exist == false) {
		//�n���h���Ƀ��[�r�[�f�[�^��ǂݍ���
		obj.handle = LoadGraph(obj.path.c_str());
		obj.exist = true;//�ǂݍ��ݍς�
	}
}

void MovieResource::initialize()
{
	std::ifstream moviepath("./data/json/movie.json");//�g�p�t�@�C���ݒ�
	if (moviepath.fail()) throw("movie.json is not found.");//��O����
	//Json���g�p���鏀��------------------------------------------
	std::istreambuf_iterator<char> it(moviepath);
	std::istreambuf_iterator<char> last;
	std::string str_json(it, last);	//string�`����json
	std::string err;
	json11::Json json = json11::Json::parse(str_json, err);//Json�Ŏg����悤�ɂ���
	//-------------------------------------------------------------
	for (auto& item : json["movie"].array_items()) {//�t�@�C�����̃f�[�^���J��Ԃ�
		std::shared_ptr<MovieObject> movie = std::make_shared<MovieObject>();
		movie->exist = false;//�܂��ǂݍ���ł��Ȃ�
		movie->name = item["name"].string_value();//���ʎq
		movie->loop = item["loop"].bool_value();//���[�v�̔��f
		movie->path = item["path"].string_value();//�t�@�C���̃p�X
		for (auto& scope : item["scope"].array_items()) {//�ǂݍ��ލۂ̎��ʎq
			movie->scopes.push_back(scope.string_value());
		}
		movie_obj.push_back(std::move(movie));//���L���̈ڍs
	}
	//�t�@�C�������vector�ɓ��ꂽ�̂Ńf�[�^������
	moviepath.close();
}

void MovieResource::finalize()
{
	movie_obj.clear();
}

int MovieResource::load(std::string scope_)
{
	int num = 0;
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->exist == false) {//�ǂݍ��܂�Ă��Ȃ��Ȃ�
			if ((*itr)->exist_scope(scope_)) {
				register_movie(*(*itr));//�o�^
				num++;
			}
		}
	}
	return num;//�ԍ���Ԃ�
}

void MovieResource::delete_movie_mem(std::string name)
{
	//�w�肵���I�u�W�F�N�g���������������
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); itr++) {
		if ((*itr)->name == name) {
			DeleteGraph((*itr)->handle);//�n���h���f�[�^���폜
			(*itr)->exist = false;
		}
	}
}

std::shared_ptr<MovieObject> MovieResource::get(std::string name)
{
	std::shared_ptr<MovieObject> ret = nullptr;//����ۂ̏��
	for (auto itr = movie_obj.begin(); itr != movie_obj.end(); ++itr) {
		if ((*itr)->name == name) {//���̖��O������Ȃ�
			ret = (*itr);//���̃I�u�W�F�N�g��Ԃ�
		}
	}
	return ret;
}

MovieObject::MovieObject()
{
	this->exist = false;
	this->handle = 0;
	this->loop = false;
	this->name = "";
	this->path = "";
}

bool MovieObject::exist_scope(std::string scope_)
{
	bool check = false;
	//���̃I�u�W�F�N�g�̃X�R�[�v�̐������J��Ԃ�
	for (auto&& scope : scopes) {
		if (scope == scope_) {//�����ƃX�R�[�v�����v������̂���������
			check = true;//true�ɂ���
			break;
		}
	}
	return check;//���ׂ����ʂ�Ԃ�
}
