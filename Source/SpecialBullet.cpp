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

<<<<<<< Updated upstream
// 雎亥ｼｱ繝ｵ郢晢ｽｬ郢晢ｽｼ郢晢ｿｽ陷ｻ・ｼ邵ｺ・ｰ郢ｧ蠕鯉ｽ玖ｭ厄ｽｴ隴・ｽｰ陷・ｽｦ騾・・
// 陟｢繝ｻ・ｮ・ｺ隰堋邵ｺ・ｮ陟托ｽｾ郢ｧ蜑・ｽｸ鬆大ｩｿ陷ｷ莉｣竊馴§・ｻ陷崎ｼ費ｼ・ｸｺ蟶卍竏ｫ蛻､鬮ｱ・｢陞滓じ竊楢怎・ｺ邵ｺ貅假ｽ芽恆莨∝求郢晁ｼ釆帷ｹｧ・ｰ郢ｧ蝣､・ｫ荵昶ｻ邵ｺ・ｾ邵ｺ蜷ｶﾂ繝ｻ
=======
<<<<<<< HEAD
// 毎フレーム呼ばれる更新処琁E
// 忁E��技の弾を上方向に移動させ、画面外に出たら削除フラグを立てます、E
void SpecialBullet::Update() {
    m_y -= m_speed;
    mvPosition = VGet(m_x, m_y, 0.0f);
=======
// 毎フレーム呼ばれる更新処琁E
// 忁E��技の弾を上方向に移動させ、画面外に出たら削除フラグを立てます、E
>>>>>>> Stashed changes
void SpecialBullet::Update() {
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = Vector2(mvPosition.x, mvPosition.y);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }

    if (mvPosition.y < -120.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }
}

<<<<<<< Updated upstream
// 隰蜀怜愛陷・ｽｦ騾・・
// 陟｢繝ｻ・ｮ・ｺ隰堋邵ｺ・ｮ郢ｧ・ｨ郢晁ｼ斐♂郢ｧ・ｯ郢晁肩・ｼ莠･・､・ｧ邵ｺ髦ｪ竊題怦迚呻ｽｼ・ｾ邵ｺ・ｪ邵ｺ・ｩ繝ｻ蟲ｨ・定ｬ蜀怜愛邵ｺ蜉ｱ竏ｪ邵ｺ蜷ｶﾂ繝ｻ
=======
<<<<<<< HEAD
// 描画処琁E
// 忁E��技のエフェクト（大きな光弾など�E�を描画します、E
=======
// 描画処琁E
// 忁E��技のエフェクト（大きな光弾など�E�を描画します、E
>>>>>>> main
>>>>>>> Stashed changes
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
            // 謨ｵ縺ｮ蠑ｾ繧呈ｶ医☆
            check->GetParentObject()->SetDeleteFlag(true);
        }
    }
}
