#pragma once
#include "Character.h"
#include "BossState.h"
#include "Barrier.h"
#include <memory>

class CapsuleCollider;

class Boss : public Character
{
private:
    int boss_type_;
    float target_x_;
    float target_y_;
    
    int attack_timer_; 
    int pattern_index_;

    bool is_dying_;
    int death_timer_;
    
    int lives_;
    int invincible_timer_;
    int invincible_cycle_timer_;

    std::unique_ptr<BossState> state_; // Current behavior state
    std::weak_ptr<Barrier> barrier_;   // 繝懊せ2繝ｻ3菴鍋岼蟆ら畑繝舌Μ繧｢縺ｸ縺ｮ蜿ら・

public:
    Boss(float x, float y, int bossType = 3);
    virtual ~Boss() override;

    void Update() override;
    void Draw() override;

    int GetLives() const { return lives_; }

    /*
     * ボスにダメージを与える。無敵中は処理を通さない。
     * [入力] damage: 受けるダメージ量
     * [出力] なし
     * [副作用] HPを減らし、ライフ管理・死亡処理を呼ぶ
     */
    virtual void TakeDamage(int damage) override;
    virtual void Kill() override;

    float GetRadius() const { return 80.0f; }

    /*
     * コライダー接触中の毎フレーム処理。プレイヤーへのダメージ等を行う。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] プレイヤーにダメージが入ることがある
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    void UpdateDamage();
    /*
     * ボスの死亡演出フレームを更新し、最終的に削除フラグを立てる。
     * [入力] なし
     * [出力] なし
     * [副作用] death_timer_が減少し、0になったら破棄処理が実行される
     */
    void UpdateDeath();
    void DrawInvincibility();
    void DrawHealthBar();

    /*
     * ボスの攻撃パターン群（フェーズや状態に応じて呼ばれる）。
     * [入力] なし
     * [出力] なし
     * [副作用] 弾丸がゲーム内にスポーンする
     */
    void ShootRadialBarrage();
    void ShootFanBarrage();
    void ShootTargetedBarrage();
    void ShootSimpleBarrage();
    void ShootBouncingBarrage();
    void ShootSpellCardBarrage();
    void SelectNewTarget();

    void SetState(BossState* newState) { state_.reset(newState); }
    int GetBossType() const { return boss_type_; }
    bool GetIsDying() const { return is_dying_; }
    int GetInvincibleTimer() const { return invincible_timer_; }
    void SetInvincibleTimer(int t) { invincible_timer_ = t; }
};
