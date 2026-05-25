#include "Bullet.h"
#include "CapsuleCollider.h"
#include "DxLib.h"
#include "Utility.h"

Bullet::Bullet(float x, float y,float damage) 
    : Object2D(VGet(x, y, 0.0f))
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

// 豈弱ヵ繝ｬ繝ｼ繝蜻ｼ縺ｰ繧後ｋ譖ｴ譁ｰ蜃ｦ逅・
// 蠑ｾ繧剃ｸ頑婿蜷代↓遘ｻ蜍輔＆縺帙∫判髱｢螟悶↓蜃ｺ縺溘ｉ蜑企勁繝輔Λ繧ｰ繧堤ｫ九※縺ｾ縺吶・
void Bullet::Update() 
{
    mvPosition.y -= m_speed * Utility::TimeScale;
    mvPosition = VGet(mvPosition.x, mvPosition.y, 0.0f);

    if (mpCollider) {
        mpCollider->mvPosition = mvPosition;
        mpCollider->mvPosition2 = mvPosition;
    }
   

    if (mvPosition.y < -20.0f) {
        m_isActive = false;
        SetDeleteFlag(true);
    }

}

// 蠑ｾ縺ｮ豸域ｻ・・逅・
// 謨ｵ縺ｫ蠖薙◆縺｣縺滄圀縺ｪ縺ｩ縺ｫ蜻ｼ縺ｰ繧後√が繝悶ず繧ｧ繧ｯ繝育ｮ｡逅・°繧牙炎髯､縺輔ｌ繧九ｈ縺・↓縺励∪縺吶・
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

// 謠冗判蜃ｦ逅・
// 蠑ｾ縺ｮ逕ｻ蜒上ｒ謠冗判縺励∪縺吶・
void Bullet::Draw()
{
    if (!m_isActive) return;
    DrawCircle((int)mvPosition.x, (int)mvPosition.y, 10, GetColor(255, 255, 255), TRUE);
}
