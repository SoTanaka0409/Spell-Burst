#pragma once
#include "Object2D.h"

class CapsuleCollider;

<<<<<<< HEAD
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

    int m_enemyType;      // 敵の種類（1: 移動のみ, 2: 通常弾, 3: スタン弾, 4: 中ボス）
    int m_attackTimer;    // 弾を発射するためのタイマー

    float m_targetX, m_targetY; // ランダム移動の目的地（中ボス用）
    void SelectNewTarget();     // 次のランダム移動の目的地を決定する（中ボス用）
=======
// 荳闊ｬ逧・↑謨ｵ繧ｭ繝｣繝ｩ繧ｯ繧ｿ繝ｼ縺ｮ繝・・繧ｿ繧・険繧玖・縺・ｒ邂｡逅・☆繧九け繝ｩ繧ｹ
// Object2D繧堤ｶ呎価縺励∫判髱｢荳翫・謠冗判繧・ｽ薙◆繧雁愛螳壹ｒ謖√▲縺ｦ縺・∪縺吶・
class Enemy : public Object2D {
private:
    float m_speed;        // 謨ｵ縺ｮ遘ｻ蜍暮溷ｺｦ
    bool m_isActive;      // 謨ｵ縺檎判髱｢蜀・↓蟄伜惠縺励∵ｴｻ蜍穂ｸｭ縺九←縺・°縺ｮ繝輔Λ繧ｰ
    int m_hp;             // 謨ｵ縺ｮ迴ｾ蝨ｨ縺ｮ菴灘鴨
    int m_maxHp;          // 謨ｵ縺ｮ譛螟ｧ菴灘鴨
    CapsuleCollider* mpCollider; // 蠖薙◆繧雁愛螳壹ｒ邂｡逅・☆繧九さ繝ｩ繧､繝繝ｼ・医き繝励そ繝ｫ迥ｶ/蜀・ｽ｢・・

    int m_enemyType;      // 謨ｵ縺ｮ遞ｮ鬘橸ｼ・: 遘ｻ蜍輔・縺ｿ, 2: 騾壼ｸｸ蠑ｾ, 3: 繧ｹ繧ｿ繝ｳ蠑ｾ, 4: 荳ｭ繝懊せ・・
    int m_attackTimer;    // 蠑ｾ繧堤匱蟆・☆繧九◆繧√・繧ｿ繧､繝槭・

    float m_targetX, m_targetY; // 繝ｩ繝ｳ繝繝�遘ｻ蜍輔・逶ｮ逧・慍・井ｸｭ繝懊せ逕ｨ・・
    void SelectNewTarget();     // 谺｡縺ｮ繝ｩ繝ｳ繝繝�遘ｻ蜍輔・逶ｮ逧・慍繧呈ｱｺ螳壹☆繧具ｼ井ｸｭ繝懊せ逕ｨ・・
>>>>>>> main

public:
    Enemy(float x, float y, int enemyType = 1);
    virtual ~Enemy() override;

<<<<<<< HEAD
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
    float GetRadius() const { 
        if (m_enemyType == 4) return 45.0f; // 中ボスは少し大きくする
        return 15.0f; 
    }

    // HPが0になった時などに呼ばれ、敵を消滅させる処理
    void Kill();

    // 他のオブジェクトと重なっている時の処理（当たり判定イベント）
=======
    // 豈弱ヵ繝ｬ繝ｼ繝�蜻ｼ縺ｰ繧後∵雰縺ｮ遘ｻ蜍募・逅・ｄ逕ｻ髱｢螟悶↓蜃ｺ縺滄圀縺ｮ蜑企勁蜃ｦ逅・ｒ陦後≧
    void Update() override;

    // 豈弱ヵ繝ｬ繝ｼ繝�蜻ｼ縺ｰ繧後∵雰縺ｮ逕ｻ蜒上ｄHP繝舌・繧呈緒逕ｻ縺吶ｋ
    void Draw() override;

    // 豢ｻ蜍慕憾諷九ヵ繝ｩ繧ｰ縺ｮ蜿門ｾ・
    bool IsActive() const { return m_isActive; }



    // HP諠・�ｱ縺ｮ蜿門ｾ励→繝繝｡繝ｼ繧ｸ蜃ｦ逅・
    int GetHp() const { return m_hp; }
    int GetEnemyType() const { return m_enemyType; }
    int GetMaxHp() const { return m_maxHp; }

    // 繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・ｒ蜿励￠縺滄圀縺ｫ蜻ｼ縺ｰ繧後？P繧呈ｸ帙ｉ縺吝・逅・
    void TakeDamage(int damage);

    // 蠎ｧ讓吶ｄ蠖薙◆繧雁愛螳壹・蜊雁ｾ・ｒ蜿門ｾ・
    float GetX() const { return mvPosition.x; }
    float GetY() const { return mvPosition.y; }
    float GetRadius() const { 
        if (m_enemyType == 4) return 45.0f; // 荳ｭ繝懊せ縺ｯ蟆代＠螟ｧ縺阪￥縺吶ｋ
        return 15.0f; 
    }

    // HP縺・縺ｫ縺ｪ縺｣縺滓凾縺ｪ縺ｩ縺ｫ蜻ｼ縺ｰ繧後∵雰繧呈ｶ域ｻ・＆縺帙ｋ蜃ｦ逅・
    void Kill();

    // 莉悶・繧ｪ繝悶ず繧ｧ繧ｯ繝医→驥阪↑縺｣縺ｦ縺・ｋ譎ゅ・蜃ｦ逅・ｼ亥ｽ薙◆繧雁愛螳壹う繝吶Φ繝茨ｼ・
>>>>>>> main
    virtual void OnTrigger(Collider* collider, Collider* check) override;
};
