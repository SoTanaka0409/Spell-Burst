#include "SpecialBullet.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "DxLib.h"
#include "Utility.h"

SpecialBullet::SpecialBullet(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet); // So it's recognized as a player projectile
    mvPosition.x = x;
    mvPosition.y = y;
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

// 豈弱ヵ繝ｬ繝ｼ繝�蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 蠢・ｮｺ謚縺ｮ蠑ｾ繧剃ｸ頑婿蜷代↓遘ｻ蜍輔＆縺帙∫判髱｢螟悶↓蜃ｺ縺溘ｉ蜑企勁繝輔Λ繧ｰ繧堤ｫ九※縺ｾ縺吶・
void SpecialBullet::Update() {
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y < -120.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

// 謠冗判蜃ｦ逅・
// 蠢・ｮｺ謚縺ｮ繧ｨ繝輔ぉ繧ｯ繝茨ｼ亥､ｧ縺阪↑蜈牙ｼｾ縺ｪ縺ｩ・峨ｒ謠冗判縺励∪縺吶・
void SpecialBullet::Draw() {
    if (!m_isActive) return;

    // Draw a giant glowing golden energy sphere representing the ultimate sushi attack!
    unsigned int colorGold = GetColor(255, 215, 0);
    unsigned int colorOrange = GetColor(255, 140, 0);
    unsigned int colorWhite = GetColor(255, 255, 255);

    // Draw concentric circles for a nice glowing effect
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 90, colorOrange, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 75, colorGold, TRUE);
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), 45, colorWhite, TRUE);

    // Add cross lines to make it look like a giant ultimate energy blast
    DrawLine(static_cast<int>(mvPosition.x - 90), static_cast<int>(mvPosition.y), static_cast<int>(mvPosition.x + 90), static_cast<int>(mvPosition.y), colorGold);
    DrawLine(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y - 90), static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y + 90), colorGold);
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
        } else if (check->GetParentObject()->GetTag() == Tag2D_EnemyBullet) {
            // 敵の弾を消す
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
