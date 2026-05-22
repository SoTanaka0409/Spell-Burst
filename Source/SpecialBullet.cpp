#include "SpecialBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "DxLib.h"

SpecialBullet::SpecialBullet(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet); // So it's recognized as a player projectile
    m_x = x;
    m_y = y;
    m_speed = 12.0f;
    m_isActive = true;
    m_damage = 5; // Ultimate piercing damage!

    // Create a giant circular collider with radius 90 (previously 60)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 90.0f);
}

SpecialBullet::~SpecialBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// 毎フレーム呼ばれる更新処理
// 必殺技の弾を上方向に移動させ、画面外に出たら削除フラグを立てます。
void SpecialBullet::Update() {
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (m_y < -120.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 描画処理
// 必殺技のエフェクト（大きな光弾など）を描画します。
void SpecialBullet::Draw() {
    if (!m_isActive) return;

    // Draw a giant glowing golden energy sphere representing the ultimate sushi attack!
    unsigned int colorGold = GetColor(255, 215, 0);
    unsigned int colorOrange = GetColor(255, 140, 0);
    unsigned int colorWhite = GetColor(255, 255, 255);

    // Draw concentric circles for a nice glowing effect
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 90, colorOrange, TRUE);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 75, colorGold, TRUE);
    DrawCircle(static_cast<int>(m_x), static_cast<int>(m_y), 45, colorWhite, TRUE);

    // Add cross lines to make it look like a giant ultimate energy blast
    DrawLine(static_cast<int>(m_x - 90), static_cast<int>(m_y), static_cast<int>(m_x + 90), static_cast<int>(m_y), colorGold);
    DrawLine(static_cast<int>(m_x), static_cast<int>(m_y - 90), static_cast<int>(m_x), static_cast<int>(m_y + 90), colorGold);
}

void SpecialBullet::Kill() {
    // Ultimate piercing bullet does not get killed on impact!
}

void SpecialBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                // Deal high ultimate damage (does not call Kill() so it pierces through!)
                enemy->TakeDamage(m_damage);
            }
        }
    }
}
