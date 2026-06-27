#include "SpecialBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

SpecialBullet::SpecialBullet(float x, float y)
    : Projectile(Vector2(x, y), Vector2(0, -1), 12.0f, 5)
{
    SetTag(Tag2D_PlayerBullet); // プレイヤー側の攻撃として判定させるためのタグ設定
    collider = new CapsuleCollider(this, position, position, 90.0f);
}

SpecialBullet::~SpecialBullet() {
}

// 毎フレーム呼ばれる更新処理
// 必殺技の弾を上方向に移動させ、画面外に出たら削除フラグを立てます
void SpecialBullet::Update() {
    position += dir * (speed * Utility::TimeScale);

    Projectile::Update();

    if (position.y < -120.0f) {
        Projectile::Kill(); // 画面外なら本当に消す
    }
}

// 描画処理
// 必殺技のエフェクト（大きな光弾など）を描画します
void SpecialBullet::Draw() {
    if (!isActive) return;

    unsigned int colorGold = GetColor(255, 215, 0);
    unsigned int colorOrange = GetColor(255, 140, 0);
    unsigned int colorWhite = GetColor(255, 255, 255);

    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 90, colorOrange, TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 75, colorGold, TRUE);
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 45, colorWhite, TRUE);

    DrawLine(static_cast<int>(position.x - 90), static_cast<int>(position.y), static_cast<int>(position.x + 90), static_cast<int>(position.y), colorGold);
    DrawLine(static_cast<int>(position.x), static_cast<int>(position.y - 90), static_cast<int>(position.x), static_cast<int>(position.y + 90), colorGold);
}

void SpecialBullet::Kill() {
    // 敵を貫通して一網打尽にする仕様とするため、衝突時の消滅処理を行わない（オーバーライドして無効化）
}

void SpecialBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr) {
                enemy->TakeDamage(damage);
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}