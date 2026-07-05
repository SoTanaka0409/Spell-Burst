#pragma once
#include "Object2D.h"

// �����G�t�F�N�g�̔j�Ёi�p�[�e�B�N���j�N���X
// �G�̌��j���Ȃǂɐ�������A�w�肳�ꂽ�����ɔ�U�����̂�����(LifeTime)�ŏ��ł���
class ExplosionParticle : public Object2D {
private:
    float vx_;         // X�����̈ړ����x�x�N�g��
    float vy_;         // Y�����̈ړ����x�x�N�g��
    int life_time_;     // �p�[�e�B�N���̌��݂̎c������i�t���[�����j
    int max_life_;      // �p�[�e�B�N���̍ő�����i�����l�j
    int color_;        // �p�[�e�B�N���̐F�iDxLib�̃J���[�R�[�h�Ȃǁj
    float size_;       // �p�[�e�B�N���̕`��T�C�Y�i���a�Ȃǁj

public:
    // [����] x, y: �������W, speed_: ��U���x, angle: ��U����p�x(���W�A����), color_: �`��F, life_time_: ���ł܂ł̃t���[����, size_: �p�[�e�B�N���̑傫��
    // [�o��] �Ȃ�
    // [����p] �p�x�Ƒ��x����XY�̈ړ��x�N�g��(vx_, vy_)��v�Z���A�e��p�����[�^�����������
    ExplosionParticle(float x, float y, float speed_, float angle, int color_, int life_time_, float size_);
    virtual ~ExplosionParticle();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���x�x�N�g���Ɋ�Â����W��X�V���A����(life_time_)����炷�B�������s������폜�t���O�𗧂Ă�
    virtual void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �c������ɉ����ăT�C�Y��k��������A�܂��͓����x�������Ȃǂ̌v�Z��s���A�p�[�e�B�N����`�悷��
    virtual void Draw() override;
};