#pragma once
#include<memory>
#include<string>
#include<vector>

struct MovieObject {
	MovieObject();
	friend class MovieResource;
	std::string name;//���ʖ�
	std::string path;//�t�@�C���p�X
	bool loop;//���[�v�Đ����邩
	int handle;//�n���h��
private:
	std::vector<std::string> scopes;//�ǂݍ��ݎ��̖��O
	bool exist_scope(std::string);
	bool exist;//�ǂݍ��ݍς݂����f
};

class MovieResource {
	static std::vector<std::shared_ptr<MovieObject>> movie_obj;//���[�r�[�f�[�^���i�[����z��
	static void register_movie(MovieObject&);//�I�u�W�F�N�g��o�^
public:
	static void initialize();
	static void finalize();
	static int load(std::string scope);//�X�R�[�v�����������Ĉ�v������̂����[�h����
	static bool check_play(std::string name);//���łɍĐ�����Ă��邩�m�F
	static void delete_movie_mem(std::string name);//���������烀�[�r�[�f�[�^���폜����
	static std::shared_ptr<MovieObject> get(std::string name);//���O����v������̂̃|�C���^��Ԃ�
};