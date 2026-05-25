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
<<<<<<< HEAD
    m_x = x;
    m_y = y;
=======
    mvPosition.x = x;
    mvPosition.y = y;
>>>>>>> main
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

<<<<<<< HEAD
// 毎フレーム呼ばれる更新処理
// 持続時間（寿命）を減らし、0になったら消滅させます。
=======
// 毎フレーム呼ばれる更新処琁E
// 持続時間（寿命�E�を減らし、Eになったら消滁E��せます、E
>>>>>>> main
void MeleeAttack::Update() {
    m_lifetime--;
    if (m_lifetime <= 0) {
        SetDeleteFlag(true);
        if (mpCollider) {
            mpCollider->SetDeleteFlag(true);
        }
    }
}

<<<<<<< HEAD
// 描画処理
// 近接攻撃のエフェクト（半透明の斬撃など）を描画します。
=======
// 描画処琁E
// 近接攻撁E�Eエフェクト（半透�Eの斬撁E��ど�E�を描画します、E
>>>>>>> main
void MeleeAttack::Draw() {
    // Draw a beautiful white and cyan slash arc pointing upwards using overlapping circles
    unsigned int slashColor = GetColor(100, 255, 255);
    float radius = 80.0f;
    const double PI = 3.14159265358979323846;
    // Draw 9 small circles forming an arc pointing upwards (from 210 degrees to 330 degrees)
    for (int i = 0; i <= 8; i++) {
        double angle = (PI + PI/6.0) + (i * (2.0 * PI / 3.0)) / 8.0;
<<<<<<< HEAD
        int sx = static_cast<int>(m_x + std::cos(angle) * radius);
        int sy = static_cast<int>(m_y + std::sin(angle) * radius);
=======
        int sx = static_cast<int>(mvPosition.x + std::cos(angle) * radius);
        int sy = static_cast<int>(mvPosition.y + std::sin(angle) * radius);
>>>>>>> main
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
