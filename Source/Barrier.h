#pragma once
#include "Object2D.h"

class Collider;

// �e��z���E�h�䂷��o���A�N���X�i���: Object2D�j
// �h�����e�̐���~�ς��A������G�t�F�N�g�ɗ��p���鐧������
class Barrier : public Object2D
{
public:
    Barrier(float x, float y, float radius, Object2D::Tag2D obj);
    virtual ~Barrier();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �o���A�̓W�J�E���k�^�C�}�[��X�V���A�R���C�_�[�̗L����Ԃ�؂�ւ���
    virtual void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �W�J���(isDeployed)�̏ꍇ�̂݁A�o���A�̎��o�G�t�F�N�g��`�悷��
    virtual void Draw() override;

    // [����] collider: ���g�̃R���C�_�[, check: �Փˑ���̃R���C�_�[
    // [�o��] �Ȃ�
    // [����p] �G�̒e�ƏՓ˂����ꍇ�A�e����ł����Ėh������(hitCount)����Z����
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    int GetHitCount() const { return hitCount; }
    bool IsDeployed() const { return isDeployed; }

private:
    float deployInterval;
    float activeDuration;
    float timer;
    float radius;
    bool isDeployed;

    Collider* collider;
    int hitCount;
};