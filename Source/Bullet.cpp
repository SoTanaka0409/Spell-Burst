#include "Bullet.h"
#include "CapsuleCollider.h"
#include "DxLib.h"

Bullet::Bullet(float x, float y,float damage) 
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    m_x = x;
    m_y = y;
    m_speed = 10.0f;
    m_isActive = true;
    m_damage = damage;

    // Create a circular collider with radius 10 (previously 5)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 10.0f);
}

Bullet::~Bullet()
{
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

void Bullet::Update() 
{
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (m_y < -20.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

void Bullet::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

void Bullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Kill();
        }
    }
}

void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)m_x, (int)m_y, 10, GetColor(255, 255, 255), TRUE);
}
