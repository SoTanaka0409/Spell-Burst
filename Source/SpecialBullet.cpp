#include "SpecialBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"

SpecialBullet::SpecialBullet(float x, float y)
    : Object2D(Vector2(x, y))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet); // プレイヤー側の攻撃として判定させるためのタグ設定
    mvPosition.x = x;
    mvPosition.y = y;
    m_speed = 12.0f;
    m_isActive = true;
    m_damage = 5; // 必殺技としての威力を表現するための高ダメージ設定

    // 画面広範囲の敵を巻き込むため、通常弾よりも極めて巨大な当たり判定を設定
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 90.0f);
}

SpecialBullet::~SpecialBullet() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// 毎フレーム呼ばれる更新処理
// 必殺技の弾を上方向に移動させ、画面外に出たら削除フラグを立てます
void SpecialBullet::Update() {
    mvPosition.y -= m_speed * Utility::TimeScale;

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y < -120.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 描画処理
// 必殺技のエフェクト（大きな光弾など）を描画します
void SpecialBullet::Draw() {
    if (!m_isActive) return;

    // 強力なエネルギー弾であることを視覚的に強調するため、輝く金色の球体を描画
    unsigned int colorGold = GetColor(255, 215, 0);
    unsigned int colorOrange = GetColor(255, 140, 0);
    unsigned int colorWhite = GetColor(255, 255, 255);

    // 光の重なりによる発光感を出すため、色とサイズを変えた複数の円を同心円状に描画
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 90, colorOrange, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 75, colorGold, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, colorWhite, TRUE);

    // 十字のラインを重ねることで、エネルギーが凝縮され溢れ出しているような演出を追加
    DrawLine(static_cast<int>(mvPosition.x - 90), static_cast<int>(mvPosition.y), static_cast<int>(mvPosition.x + 90), static_cast<int>(mvPosition.y), colorGold);
    DrawLine(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y - 90), static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y + 90), colorGold);
}

void SpecialBullet::Kill() {
    // 敵を貫通して一網打尽にする仕様とするため、衝突時の消滅処理を行わない
}

void SpecialBullet::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                // 貫通弾であるため、敵にダメージを与えつつ自身はそのまま直進させる
                enemy->TakeDamage(m_damage);
            }
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            // 敵の弾を消す
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}