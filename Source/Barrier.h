#pragma once
#include "Object2D.h"

class Collider;

// �e��z���E�h�䂷��o���A�N���X�i���: Object2D�j
// �h�����e�̐���~�ς��A������G�t�F�N�g�ɗ��p���鐧������
class Barrier : public Object2D
{
public:
    Barrier(float x, float y, float radius_, Object2D::Tag2D obj);
    virtual ~Barrier();

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �o���A�̓W�J�E���k�^�C�}�[��X�V���A�R���C�_�[�̗L����Ԃ�؂�ւ���
    virtual void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �W�J���(isDeployed)�̏ꍇ�̂݁A�o���A�̎��o�G�t�F�N�g��`�悷��
    virtual void Draw() override;

    // [����] collider_: ���g�̃R���C�_�[, check: �Փˑ���̃R���C�_�[
    // [�o��] �Ȃ�
    // [����p] �G�̒e�ƏՓ˂����ꍇ�A�e����ł����Ėh������(hit_count)����Z����
    virtual void OnTrigger(Collider* collider_, Collider* check) override;

    int GetHitCount() const { return hit_count; }
    bool IsDeployed() const { return isDeployed; }
    void SetDeployInterval(float v) { deployInterval = v; }
    void SetActiveDuration(float v) { activeDuration = v; }
    void SetPosition(Vector2 pos) { position_ = pos; }

private:
    float deployInterval;
    float activeDuration;
    float timer;
    float radius_;
    bool isDeployed;

    Collider* collider_;
    int hit_count;
};