#pragma once
#include"Animation.h"
#include"Purpose.h"

//�Q�[���I�u�W�F�N�g�̐e�N���X

class Object {
protected:
	enum class BlendState {
		Addition,
		Subtraction
	};
	int blend_cnt;//���x���̉摜�𔼓����ɂ����肷�邽�߂̃J�E���^
	BlendState b_state;//���Z�����Z���𔻒f
	void check_blendCnt();//�J�E���^�̏�ԂōX�V���s��

	std::unique_ptr<Animation> anime;//�摜�`��
	Vector2 position;//���W
public:
	Object();
	virtual void initialize() = 0;
	virtual void finalize() = 0;
	virtual void update();
	virtual void draw(bool a_blend = false);

	void set_position(Vector2 pos);
	Vector2 get_position();//���W���󂯎�点��
};