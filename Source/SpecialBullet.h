#pragma once
#include "Object2D.h"

class CapsuleCollider;

// プレイヤーが発射する特殊弾（高威力または追尾等）を定義するクラス
class SpecialBullet : public Object2D {
private:
    float m_speed;      
    int m_damage;       
    bool m_isActive;    
    CapsuleCollider* mpCollider;

public:
    SpecialBullet(float x, float y);
    virtual ~SpecialBullet() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 弾を上昇させ、画面外に出た場合は破棄する
    virtual void Update() override;

    // [入力] なし
    // [出力] なし
    // [副作用] 特殊弾のグラフィックを描画する
    virtual void Draw() override;

    int GetDamage() const { return m_damage; }
    void Kill();

    // [入力] collider: 自身のコライダー, check: 相手のコライダー
    // [出力] なし
    // [副作用] 敵と衝突した際にダメージを与えて自身を破棄する
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};