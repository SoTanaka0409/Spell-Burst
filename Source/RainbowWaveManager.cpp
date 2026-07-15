#include "RainbowWaveManager.h"
#include "ObjectManager.h"
#include "RainbowBullet.h"
#include "Utility.h"

RainbowWaveManager::RainbowWaveManager(float x, float y)
    : Object2D(Vector2(x, y))
    , life_timer_(120) // 管理オブジェクト自体の生存期間（3秒）
    , spawn_interval_(10) // 弾を生成するインターバル（5フレームごと）
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
        
        // 画面下部から画面全体を覆うように弾を配置するため、等間隔に座標を計算
        int numBullets = 10;
        float spacing = static_cast<float>(Utility::SCREEN_WIDTH) / static_cast<float>(numBullets);
        float startX = spacing / 2.0f;
        float yPos = static_cast<float>(Utility::SCREEN_HEIGHT) + 20.0f; // 画面外から出現させるため下部にオフセット

        for (int i = 0; i < numBullets; i++)
        {
            ObjectManager::Instantiate<RainbowBullet>(startX + i * spacing, yPos);
        }
    }
}

void RainbowWaveManager::Draw()
{
    // 弾の生成管理のみを行う不可視オブジェクトであるため描画処理は不要
}

void RainbowWaveManager::OnTrigger(Collider* collider_, Collider* check)
{
    // 自身は当たり判定を持たず、生成した弾に判定を委ねるため空処理
}




