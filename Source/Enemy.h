#pragma once
#include "Character.h"

class CapsuleCollider;

class Enemy : public Character
{
private:
    int enemy_type_;      
    int attack_timer_;    

    float target_x_;
    float target_y_;
    void SelectNewTarget();     

public:
    Enemy(float x, float y, int enemyType = 1);
    virtual ~Enemy() override;

    void Update() override;
    void Draw() override;

    int GetEnemyType() const { return enemy_type_; }

    /*
     * 敵キャラクターにダメージを与える。
     * [入力] damage: 受けるダメージ量
     * [出力] なし
     * [副作用] HPを減らし、0以下になったらOnDeathを呼ぶ
     */
    virtual void TakeDamage(int damage) override;
    virtual void Kill() override;

    float GetRadius() const
    { 
        if (enemy_type_ == 4) return 45.0f;
        return 15.0f; 
    }

    /*
     * コライダー接触中の毎フレーム処理。プレイヤーへのダメージ等を行う。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] プレイヤーにダメージが入ることがある
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    /*
     * 敵の死亡時処理を行う（スコアやXP付与）。
     * [入力] なし
     * [出力] なし
     * [副作用] 削除フラグが立ち、プレイヤーにXPが付与される
     */
    void OnDeath();

    /*
     * 敵タイプに応じた攻撃パターンを毎フレーム更新する。
     * [入力] なし
     * [出力] なし
     * [副作用] タイマーに応じて弾が生成される
     */
    void UpdateAttackPattern();
    void DrawEnemySprite();
    void DrawHpBar();
};
