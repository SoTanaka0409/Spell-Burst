#include "Character.h"
#include "CapsuleCollider.h"

Character::Character(Vector2 pos, int maxHp, float speed)
    : Object2D(pos)
    , hp(maxHp)
    , maxHp(maxHp)
    , speed(speed)
    , isActive(true)
    , stunTimer(0)
    , collider(nullptr)
{
}

Character::~Character() {
    if (collider) {
        delete collider;
        collider = nullptr;
    }
}

void Character::Update() {
    // スタン時間の減少
    if (stunTimer > 0) {
        stunTimer--;
    }

    // コライダーの座標追従
    if (collider) {
        collider->position = position;
        collider->position2 = position;
    }
}

void Character::Draw() {
    // 基底クラスは描画しない
}

void Character::OnTrigger(Collider* collider, Collider* check) {
    // デフォルト実装：派生先でオーバーライド
}

void Character::Heal(int amount) {
    hp += amount;
    if (hp > maxHp) {
        hp = maxHp;
    }
}

void Character::TakeDamage(int damage) {
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        Kill();
    }
}

void Character::Kill() {
    isActive = false;
    SetDeleteFlag(true);
    if (collider) {
        collider->SetDeleteFlag(true);
    }
}