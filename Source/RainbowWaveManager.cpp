#include "RainbowWaveManager.h"
#include "ObjectManager.h"
#include "RainbowBullet.h"
#include "Utility.h"

RainbowWaveManager::RainbowWaveManager(float x, float y)
    : Object2D(Vector2(x, y))
    , life_timer_(120) // 邂｡逅・が繝悶ず繧ｧ繧ｯ繝郁・菴薙・逕溷ｭ俶悄髢難ｼ・遘抵ｼ・
    , spawn_interval_(10) // 蠑ｾ繧堤函謌舌☆繧九う繝ｳ繧ｿ繝ｼ繝舌Ν・・繝輔Ξ繝ｼ繝縺斐→・・
    , spawn_timer_(0)
{
    SetTag(kTag2dPlayerBullet);
}

RainbowWaveManager::~RainbowWaveManager()
{
}

void RainbowWaveManager::Update()
{
    life_timer_--;
    if (life_timer_ <= 0)
    {
        SetDeleteFlag(true);
        return;
    }

    spawn_timer_++;
    if (spawn_timer_ >= spawn_interval_)
    {
        spawn_timer_ = 0;

        int numBullets = 10;
        float spacing = static_cast<float>(Utility::kScreenWidth) / static_cast<float>(numBullets);
        float startX = spacing / 2.0f;
        float yPos = static_cast<float>(Utility::kScreenHeight) + 20.0f; // 逕ｻ髱｢螟悶°繧牙・迴ｾ縺輔○繧九◆繧∽ｸ矩Κ縺ｫ繧ｪ繝輔そ繝・ヨ

        for (int i = 0; i < numBullets; i++)
        {
            ObjectManager::Instantiate<RainbowBullet>(startX + i * spacing, yPos);
        }
    }
}

void RainbowWaveManager::Draw()
{
}

void RainbowWaveManager::OnTrigger(Collider* collider, Collider* check)
{
}




