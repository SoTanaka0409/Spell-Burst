#include "Bullet.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage) 
    : Projectile(Vector2(x, y), Vector2(0, -1), 20.0f, damage)
{
    SetTag(Tag2D_PlayerBullet);
    m_recivedDamage = 0;
    m_MaxrecivedDamage = 20; // ダメージを受けてから3回で技を出す
    // Create a circular collider with radius 10 (previously 5)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 10.0f);
}

Bullet::~Bullet()
{
}

// 毎フレーム呼ばれる更新処理
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます
void Bullet::Update() 
{
    mvPosition += m_dir * (m_speed * Utility::TimeScale);

    Projectile::Update();

    if (IsOutOfBounds()) {
        Kill();
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

// 描画処理
// 弾の画像を描画します
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 10, GetColor(255, 255, 255), TRUE);
}