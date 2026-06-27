#pragma once
#include "Object2D.h"

// �����G�t�F�N�g�̔j�Ёi�p�[�e�B�N���j�N���X
// �G�̌��j���Ȃǂɐ�������A�w�肳�ꂽ�����ɔ�U�����̂�����(LifeTime)�ŏ��ł���
class ExplosionParticle : public Object2D {
private:
    float vx;         // X�����̈ړ����x�x�N�g��
    float vy;         // Y�����̈ړ����x�x�N�g��
    int lifeTime;     // �p�[�e�B�N���̌��݂̎c������i�t���[�����j
    int maxLife;      // �p�[�e�B�N���̍ő�����i�����l�j
    int color;        // �p�[�e�B�N���̐F�iDxLib�̃J���[�R�[�h�Ȃǁj
    float size;       // �p�[�e�B�N���̕`��T�C�Y�i���a�Ȃǁj

public:
    // [����] x, y: �������W, speed: ��U���x, angle: ��U����p�x(���W�A����), color: �`��F, lifeTime: ���ł܂ł̃t���[����, size: �p�[�e�B�N���̑傫��
    // [�o��] �Ȃ�
    // [����p] �p�x�Ƒ��x����XY�̈ړ��x�N�g��(vx, vy)��v�Z���A�e��p�����[�^�����������
    ExplosionParticle(float x, float y, float speed, float angle, int color, int lifeTime, float size);
    virtual ~ExplosionParticle();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] ���x�x�N�g���Ɋ�Â����W��X�V���A����(lifeTime)����炷�B�������s������폜�t���O�𗧂Ă�
    virtual void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �c������ɉ����ăT�C�Y��k��������A�܂��͓����x�������Ȃǂ̌v�Z��s���A�p�[�e�B�N����`�悷��
    virtual void Draw() override;
};