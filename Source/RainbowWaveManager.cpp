#include "RainbowWaveManager.h"
#include "ObjectManager.h"
#include "RainbowBullet.h"
#include "Utility.h"

/// @brief RainbowWaveManager を生成する
/// @param x x の値
/// @param y y の値
RainbowWaveManager::RainbowWaveManager(float x, float y)
    : Object2D(Vector2(x, y))
    , life_timer_(120) // 持続時間
    , spawn_interval_(10) // 弾の生成間隔
    , spawn_timer_(0)
{
    SetTag(kTag2dPlayerBullet);
}

/// @brief 破棄処理を行う
RainbowWaveManager::~RainbowWaveManager()
{
}

/// @brief 毎フレームの更新処理を行う
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
        float yPos = static_cast<float>(Utility::kScreenHeight) + 20.0f; // 画面下から少し外れた位置に生成する

        for (int i = 0; i < numBullets; i++)
        {
            ObjectManager::Instantiate<RainbowBullet>(startX + i * spacing, yPos);
        }
    }
}

/// @brief 描画処理を行う
void RainbowWaveManager::Draw()
{
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void RainbowWaveManager::OnTrigger(Collider* collider, Collider* check)
{
}




