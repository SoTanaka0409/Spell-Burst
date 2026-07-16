#pragma once
#include "Object2D.h"

class Collider;

class Barrier : public Object2D
{
public:
    /*
     * バリアオブジェクトを初期化する。
     * [入力] x: 座標X, y: 座標Y, radius: 半径, obj: タグ種別
     * [出力] なし
     * [副作用] コライダーが生成され管理リストに登録される
     */
    Barrier(float x, float y, float radius, Object2D::Tag2D obj);
    virtual ~Barrier();

    /*
     * バリアの展開カウントダウン、コライダーの有無を管理する。
     * [入力] なし
     * [出力] なし
     * [副作用] タイマーが更新されコライダーが生成・削除される
     */
    virtual void Update() override;

    /*
     * バリアのエフェクトを描画する（isDeployed=trueの時のみ）。
     * [入力] なし
     * [出力] なし
     * [副作用] 画面に描画される
     */
    virtual void Draw() override;

    /*
     * 敵の弾と衝突した際、その弾を防ぎhit_count_を加算する。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] hit_count_が更新される
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;

    int GetHitCount() const { return hit_count_; }
    bool IsDeployed() const { return is_deployed_; }
    void SetDeployInterval(float v) { deploy_interval_ = v; }
    void SetActiveDuration(float v) { active_duration_ = v; }
    void SetPosition(Vector2 pos) { position_ = pos; }

private:
    float deploy_interval_;
    float active_duration_;
    float timer_;
    float radius_;
    bool is_deployed_;

    Collider* collider_;
    int hit_count_;
};
