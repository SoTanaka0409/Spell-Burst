#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 全てのキャラクター（プレイヤー、敵、ボス）の基底クラス
class Character : public Object2D
{
protected:
    int hp_;                    // 現在の体力（HP）
    int max_hp_;                 // 最大体力
    float speed_;               // 移動速度
    bool is_active_;             // 有効フラグ
    int stun_timer_;             // スタン（行動不能）の残り時間（フレーム数）
    CapsuleCollider* collider_; // 当たり判定コライダー

public:
    // [入力] pos: 初期座標, max_hp_: 最大体力, speed_: 移動速度
    Character(Vector2 pos, int max_hp_, float speed_);
    virtual ~Character() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider_, Collider* check) override;

    // --- ゲッター ---
    int GetHp() const { return hp_; }
    int GetMaxHp() const { return max_hp_; }
    float GetSpeed() const { return speed_; }
    bool IsActive() const { return is_active_; }
    bool IsStunned() const { return stun_timer_ > 0; }
    int GetStunTimer() const { return stun_timer_; }
    float GetX() const { return position_.x; }
    float GetY() const { return position_.y; }

    // --- セッター・操作 ---
    void SetHp(int hp_) { hp_ = hp_; }
    void SetMaxHp(int max_hp_) { max_hp_ = max_hp_; }
    void SetSpeed(float speed_) { speed_ = speed_; }
    void Stun(int frames) { stun_timer_ = frames; }

    // [入力] amount: 回復量
    // [副作用] HPを回復し、最大値を超えないように制限する
    virtual void Heal(int amount);

    // [入力] damage_: 受けるダメージ量
    // [副作用] HPを減らし、0以下になったら死亡処理などを呼ぶ
    virtual void TakeDamage(int damage_);

    // [入力] なし
    // [副作用] キャラクターを死亡状態にし、削除フラグを立てる
    virtual void Kill();
};
