#pragma once
#include "Object2D.h"

class CapsuleCollider;

// �v���C���[�ɂ��ߐڍU������i�a���Ȃǁj��Ǘ�����N���X
class MeleeAttack : public Object2D {
private:
    int life_time_; 
    int damage_;   
    CapsuleCollider* collider_;

public:
    MeleeAttack(float x, float y);
    virtual ~MeleeAttack() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �����^�C�}�[��X�V���A��莞�Ԍo�ߌ�Ɏ��g��j��(Kill)����
    virtual void Update() override;

    // [����] �Ȃ�
    // [�o��] �Ȃ�
    // [����p] �U���͈͂�����a���G�t�F�N�g��`�悷��
    virtual void Draw() override;

    int GetDamage() const { return damage_; }
    void Kill();

    // [����] collider_: ���g�̃R���C�_�[, check: ����̃R���C�_�[
    // [�o��] �Ȃ�
    // [����p] �Փˑ��肪�G�L�����N�^�[�̏ꍇ�A�_���[�W��^����
    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};