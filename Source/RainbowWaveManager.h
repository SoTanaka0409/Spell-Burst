#pragma once
#include "Object2D.h"

// 虹色の波状弾を一定時間生成する管理オブジェクト
class RainbowWaveManager : public Object2D
{
private:
    int life_timer_;     // 残り寿命フレーム数
    int spawn_interval_; // 弾を生成する間隔
    int spawn_timer_;    // 次の生成までのタイマー

public:
    RainbowWaveManager(float x, float y);
    virtual ~RainbowWaveManager() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};