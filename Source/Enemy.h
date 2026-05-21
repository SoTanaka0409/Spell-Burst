#pragma once
#include "Object2D.h"

class CapsuleCollider;

// 一般的な敵キャラクターのデータや振る舞いを管理するクラス
// Object2Dを継承し、画面上の描画や当たり判定を持っています。
class Enemy : public Object2D {
private:
    float m_x, m_y;       // 敵の画面上のXY座標
    float m_speed;        // 敵の移動速度
    bool m_isActive;      // 敵が画面内に存在し、活動中かどうかのフラグ
    int m_hp;             // 敵の現在の体力
    int m_maxHp;          // 敵の最大体力
    CapsuleCollider* mpCollider; // 当たり判定を管理するコライダー（カプセル状/円形）

public:
    Enemy(float x, float y);
    virtual ~Enemy() override;

    // 毎フレーム呼ばれ、敵の移動処理や画面外に出た際の削除処理を行う
    void Update() override;

    // 毎フレーム呼ばれ、敵の画像やHPバーを描画する
    void Draw() override;

    // 活動状態フラグの取得
    bool IsActive() const { return m_isActive; }

    // HP情報の取得とダメージ処理
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }

    // プレイヤーの攻撃を受けた際に呼ばれ、HPを減らす処理
    void TakeDamage(int damage);

    // 座標や当たり判定の半径を取得
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetRadius() const { return 15.0f; }

    // HPが0になった時などに呼ばれ、敵を消滅させる処理
    void Kill();

    // 他のオブジェクトと重なっている時の処理（当たり判定イベント）
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
