#pragma once
#include "Object2D.h"
#include "Vector2.h"

class CapsuleCollider;
class Collider;

// 全てのキャラクター（プレイヤー、敵、ボス）の基底クラス
class Character : public Object2D {
protected:
    int hp;                    // 現在の体力（HP）
    int maxHp;                 // 最大体力
    float speed;               // 移動速度
    bool isActive;             // 有効フラグ
    int stunTimer;             // スタン（行動不能）の残り時間（フレーム数）
    CapsuleCollider* collider; // 当たり判定コライダー

public:
    // [入力] pos: 初期座標, maxHp: 最大体力, speed: 移動速度
    Character(Vector2 pos, int maxHp, float speed);
    virtual ~Character() override;

    virtual void Update() override;
    virtual void Draw() override;
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    // --- ゲッター ---
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    float GetSpeed() const { return speed; }
    bool IsActive() const { return isActive; }
    bool IsStunned() const { return stunTimer > 0; }
    int GetStunTimer() const { return stunTimer; }
    float GetX() const { return position.x; }
    float GetY() const { return position.y; }

    // --- セッター・操作 ---
    void SetHp(int hp) { hp = hp; }
    void SetMaxHp(int maxHp) { maxHp = maxHp; }
    void SetSpeed(float speed) { speed = speed; }
    void Stun(int frames) { stunTimer = frames; }

    // [入力] amount: 回復量
    // [副作用] HPを回復し、最大値を超えないように制限する
    virtual void Heal(int amount);

    // [入力] damage: 受けるダメージ量
    // [副作用] HPを減らし、0以下になったら死亡処理などを呼ぶ
    virtual void TakeDamage(int damage);

    // [入力] なし
    // [副作用] キャラクターを死亡状態にし、削除フラグを立てる
    virtual void Kill();
};