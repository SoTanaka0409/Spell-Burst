#pragma once
#include "Object2D.h"

class Collider;

// 弾を吸収・防御するバリアクラス（基底: Object2D）
// 防いだ弾の数を蓄積し、反撃やエフェクトに利用する制約を持つ
class Barrier : public Object2D
{
public:
    Barrier(float x, float y, float radius, Object2D::Tag2D obj);
    virtual ~Barrier();

    // [入力] なし
    // [出力] なし
    // [副作用] バリアの展開・収縮タイマーを更新し、コライダーの有効状態を切り替える
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 展開状態(m_isDeployed)の場合のみ、バリアの視覚エフェクトを描画する
    virtual void Draw() override;

    // [入力] collider: 自身のコライダー, check: 衝突相手のコライダー
    // [出力] なし
    // [副作用] 敵の弾と衝突した場合、弾を消滅させて防いだ回数(m_hitCount)を加算する
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    int GetHitCount() const { return m_hitCount; }
    bool IsDeployed() const { return m_isDeployed; }

private:
    float m_deployInterval;
    float m_activeDuration;
    float m_timer;
    float m_radius;
    bool m_isDeployed;

    Collider* mpCollider;
    int m_hitCount;
};