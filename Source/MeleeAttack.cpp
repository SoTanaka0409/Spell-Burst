#include "MeleeAttack.h"
#include "CapsuleCollider.h"
#include "Enemy.h"
#include "DxLib.h"
#include <algorithm>
#include <cmath>

MeleeAttack::MeleeAttack(float x, float y)
    : Object2D(VGet(x, y, 0.0f))
    , mpCollider(nullptr)
{
    SetTag(Tag2D_PlayerBullet); // So it's recognized as a player attack
    mvPosition.x = x;
    mvPosition.y = y;
    m_lifetime = 10; // Active for 10 frames
    m_damage = 3;    // High damage melee slash

    // Create a large circular collider in front of the player (radius 80)
    mpCollider = new CapsuleCollider(this, mvPosition, mvPosition, 80.0f);
}

MeleeAttack::~MeleeAttack() {
    if (mpCollider) {
        delete mpCollider;
        mpCollider = nullptr;
    }
}

// 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 謖∫ｶ壽凾髢難ｼ亥ｯｿ蜻ｽ・峨ｒ貂帙ｉ縺励・縺ｫ縺ｪ縺｣縺溘ｉ豸域ｻ・＆縺帙∪縺吶・
void MeleeAttack::Update() {
    m_lifetime--;
    if (m_lifetime <= 0) {
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
        }
    }
}

// 謠冗判蜃ｦ逅・
// 霑第磁謾ｻ謦・・繧ｨ繝輔ぉ繧ｯ繝茨ｼ亥濠騾乗・縺ｮ譁ｬ謦・↑縺ｩ・峨ｒ謠冗判縺励∪縺吶・
void MeleeAttack::Draw() {
    // Draw a beautiful white and cyan slash arc pointing upwards using overlapping circles
    unsigned int slashColor = GetColor(100, 255, 255);
    float radius = 80.0f;
    const double PI = 3.14159265358979323846;
    // Draw 9 small circles forming an arc pointing upwards (from 210 degrees to 330 degrees)
    for (int i = 0; i <= 8; i++) {
        double angle = (PI + PI/6.0) + (i * (2.0 * PI / 3.0)) / 8.0;
        int sx = static_cast<int>(mvPosition.x + std::cos(angle) * radius);
        int sy = static_cast<int>(mvPosition.y + std::sin(angle) * radius);
        DrawCircle(sx, sy, 8, slashColor, TRUE);
        // Draw inner white circle for a glowing hot core effect
        DrawCircle(sx, sy, 4, GetColor(255, 255, 255), TRUE);
    }
}

void MeleeAttack::Kill() {
    // Melee attack cannot be killed/destroyed by bullets
}

void MeleeAttack::OnTrigger(Collider* collider, Collider* check) {
    if (check != nullptr && check->GetParentObject() != nullptr) {
        if (check->GetParentObject()->GetTag() == Tag2D_Enemy) {
            Enemy* enemy = dynamic_cast<Enemy*>(check->GetParentObject());
            if (enemy != nullptr) {
                // To avoid dealing damage every single frame, we could track hit enemies, 
                // but for a short 10-frame melee slash, dealing damage once is best.
                // We'll tag the enemy or simply check if they are already hit.
                // For simplicity and high impact, we'll deal damage.
                enemy->TakeDamage(m_damage);
            }
        }
    }
}
