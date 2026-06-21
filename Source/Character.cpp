#include "Character.h"
#include "CapsuleCollider.h"

Character::Character(Vector2 pos, int maxHp, float speed)
    : Object2D(pos)
    , m_hp(maxHp)
    , m_maxHp(maxHp)
    , m_speed(speed)
    , m_isActive(true)
    , m_stunTimer(0)
    , mpCollider(nullptr)
{
}

Character::~Character() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Character::Update() {
    // スタン時間の減少
    if (m_stunTimer > 0) {
        m_stunTimer--;
    }

    // コライダーの座標追従
    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
}

void Character::Draw() {
    // 基底クラスは描画しない
}

void Character::OnTrigger(Collider* collider, Collider* check) {
    // デフォルト実装：派生先でオーバーライド
}

void Character::Heal(int amount) {
    m_hp += amount;
    if (m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }
}

void Character::TakeDamage(int damage) {
    m_hp -= damage;
    if (m_hp <= 0) {
        m_hp = 0;
        Kill();
    }
}

void Character::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}