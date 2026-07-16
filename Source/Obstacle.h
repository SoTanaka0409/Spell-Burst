#pragma once
#include "Object2D.h"

class CapsuleCollider;

class Obstacle : public Object2D
{
private:
    CapsuleCollider* collider_;
    float fall_speed_;

public:
    Obstacle(float x, float y);
    virtual ~Obstacle() override;

    virtual void Update() override;
    virtual void Draw() override;
    /*
     * プレイヤー等と接触中に毎フレーム呼ばれる。岩のダメージ処理。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] プレイヤーにダメージが入る
     */
    virtual void OnTrigger(Collider* collider, Collider* check) override;
    /*
     * コライダーに接触した瞬間に呼ばれる（接触開始イベント）。
     * [入力] collider: 自身のコライダー, check: 相手のコライダー
     * [出力] なし
     * [副作用] 接触した相手の種類に応じた初期処理が行われる
     */
    virtual void OnEnter(Collider* collider, Collider* check) override;
};
