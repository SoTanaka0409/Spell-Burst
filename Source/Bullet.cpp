#include "Bullet.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y, int damage) 
    : Object2D(Vector2(x, y))
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
<<<<<<< Updated upstream
=======

<<<<<<< HEAD
// 毎フレーム呼ばれる更新処琁E
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます、E
void Bullet::Update() 
{
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);
=======
// 毎フレーム呼ばれる更新処琁E
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます、E
>>>>>>> Stashed changes
void Bullet::Update() 
{
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = Vector2(mvPosition.x, mvPosition.y);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
<<<<<<< Updated upstream
=======
<<<<<<< HEAD

    if (m_y < -20.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 弾の消滁E�E琁E
// 敵に当たった際などに呼ばれ、オブジェクト管琁E��ら削除されるよぁE��します、E
=======
>>>>>>> Stashed changes
   

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
<<<<<<< Updated upstream
=======

<<<<<<< HEAD
// 描画処琁E
// 弾の画像を描画します、E
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)m_x, (int)m_y, 10, GetColor(255, 255, 255), TRUE);
=======
// 描画処琁E
// 弾の画像を描画します、E
>>>>>>> Stashed changes
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)mvPosition.x, (int)mvPosition.y, 10, GetColor(255, 255, 255), TRUE);
}
