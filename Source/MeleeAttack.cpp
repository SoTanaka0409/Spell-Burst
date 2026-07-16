#include "MeleeAttack.h"
#include "ObjectManager.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <algorithm>
#include <cmath>

MeleeAttack::MeleeAttack(float x, float y)
    : Object2D(Vector2(x, y))
    , collider_(nullptr)
{
    SetTag(kTag2dPlayerBullet); // プレイヤーの攻撃として当たり判定を処理させるため専用タグを設定
    position_.x = x;
    position_.y = y;
    life_time_ = 10; // 近接攻撃であるため短期間（10フレーム）で消失させる
    damage_ = 3;    // リスクに見合った高威力のダメージ設定

    // 近接攻撃の当たり判定として、キャラクター前方に巨大な円形コライダーを配置
    collider_ = new CapsuleCollider(this, position_, position_, 80.0f);
}

MeleeAttack::~MeleeAttack()
{
    if (collider_)
    {
        delete collider_;
        collider_ = nullptr;
    }
}

// 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 謖∫ｶ壽凾髢難ｼ亥ｯｿ蜻ｽ・峨ｒ貂帙ｉ縺励・縺ｫ縺ｪ縺｣縺溘ｉ豸域ｻ・＆縺帙∪縺吶・
void MeleeAttack::Update()
{
    life_time_--;
    if (life_time_ <= 0)
    {
        SetDeleteFlag(true);
        if (collider_)
        {
            collider_->SetDeleteFlag(true);
        }
    }
}

// 謠冗判蜃ｦ逅・
// 霑第磁謾ｻ謦・・繧ｨ繝輔ぉ繧ｯ繝茨ｼ亥濠騾乗・縺ｮ譁ｬ謦・↑縺ｩ・峨ｒ謠冗判縺励∪縺吶・
void MeleeAttack::Draw()
{
    // 剣の軌跡を表現するため、複数の円を円弧状に配置して斬撃エフェクトを描画
    unsigned int slashColor = GetColor(100, 255, 255);
    float radius_ = 80.0f;
    const double PI = 3.14159265358979323846;
    // 210度から330度の範囲で円弧を描くように9つの点を計算して描画
    for (int i = 0; i <= 8; i++)
    {
        double angle = (PI + PI/6.0) + (i * (2.0 * PI / 3.0)) / 8.0;
        int sx = static_cast<int>(position_.x + std::cos(angle) * radius_);
        int sy = static_cast<int>(position_.y + std::sin(angle) * radius_);
        DrawCircle(sx, sy, 8, slashColor, TRUE);
        // 斬撃の中心が熱を帯びて光っているような演出のため内側に白い円を重ねる
        DrawCircle(sx, sy, 4, GetColor(255, 255, 255), TRUE);
    }
}

void MeleeAttack::Kill()
{
    // 近接攻撃は敵弾によって相殺されない仕様とするため空処理
}

void MeleeAttack::OnTrigger(Collider* collider, Collider* check)
{
    if (check != nullptr && check->GetParentObject() != nullptr)
    {
        if (check->GetParentObject()->GetTag() == kTag2dEnemy)
        {
            Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
            if (enemy != nullptr)
            {
                // 攻撃判定は短期間（10フレーム）であるため、ヒット間隔を管理せず即座にダメージを与える
                enemy->TakeDamage(damage_);
            }
        }
    }
}

