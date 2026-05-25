#include "Bullet.h"
#include "CapsuleCollider.h"
#include "DxLib.h"
<<<<<<< HEAD
=======
#include "Utility.h"
>>>>>>> main

Bullet::Bullet(float x, float y,float damage) 
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet);
<<<<<<< HEAD
    m_x = x;
    m_y = y;
    m_speed = 20.0f;
    m_isActive = true;
    m_damage = damage;

=======
    mvPosition.x = x;
    mvPosition.y = y;
    m_speed = 20.0f;
    m_isActive = true;
    m_damage = damage;
    m_recivedDamage = 0;
    m_MaxrecivedDamage = 20; // �_���[�W���󂯂Ă���3��ŋZ���o��
>>>>>>> main
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

<<<<<<< HEAD
// 毎フレーム呼ばれる更新処理
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます。
void Bullet::Update() 
{
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);
=======
// 毎フレーム呼ばれる更新処琁E
// 弾を上方向に移動させ、画面外に出たら削除フラグを立てます、E
void Bullet::Update() 
{
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);
>>>>>>> main

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
<<<<<<< HEAD

    if (m_y < -20.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 弾の消滅処理
// 敵に当たった際などに呼ばれ、オブジェクト管理から削除されるようにします。
=======
   

    if (mvPosition.y < -20.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }

}

// 弾の消滁E�E琁E
// 敵に当たった際などに呼ばれ、オブジェクト管琁E��ら削除されるよぁE��します、E
>>>>>>> main
void Bullet::Kill() {
    m_isActive = false;
    SetDeleteFlag(true);
    if (mpCollider) {
        mpCollider->SetDeleteFlag(true);
    }
}

<<<<<<< HEAD
void Bullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
=======
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
>>>>>>> main
            Kill();
        }
    }
}

<<<<<<< HEAD
// 描画処理
// 弾の画像を描画します。
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)m_x, (int)m_y, 10, GetColor(255, 255, 255), TRUE);
=======
// 描画処琁E
// 弾の画像を描画します、E
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)mvPosition.x, (int)mvPosition.y, 10, GetColor(255, 255, 255), TRUE);
>>>>>>> main
}
