#include "Bullet.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage) 
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
    mvPosition.x = x;
    mvPosition.y = y;
    m_speed = 20.0f;
    m_isActive = true;
    m_damage = damage;
    m_recivedDamage = 0;
    m_MaxrecivedDamage = 20; // ダメージを受けてから3回で技を出す
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
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
   

    if (mvPosition.y < -20.0f) {
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

void Bullet::OnTrigger(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        if(check->GetParentObject()->GetTag() == tag2D_BarierEne)
        {
           
            Kill();
            return;
		}
    }
    if (check != nullptr && check->GetParentObject() != nullptr) 
    {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy)
        {
            Kill();
        }
    }
}
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)mvPosition.x, (int)mvPosition.y, 10, GetColor(255, 255, 255), TRUE);
}
