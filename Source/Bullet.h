#pragma once
#include "Object2D.h"

class CapsuleCollider;

<<<<<<< HEAD
// プレイヤーが発射する通常の弾を管理するクラス
=======
// プレイヤーが発封E��る通常の弾を管琁E��るクラス
>>>>>>> main
class Bullet : public Object2D
{
public:
    Bullet(float x, float y,float damage);
    virtual ~Bullet() override;
    void Draw() override;
    void Update() override;
    bool IsActive() { return m_isActive; }

    // Collision helper
<<<<<<< HEAD
    float GetX() { return m_x; }
    float GetY() { return m_y; }
=======
    float GetX() { return mvPosition.x; }
    float GetY() { return mvPosition.y; }
>>>>>>> main
    float GetRadius() const { return 10.0f; }
    int GetDamage() const { return m_damage; }
    void Kill();

<<<<<<< HEAD
    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_x, m_y;       // 弾の座標
    float m_speed;        // 弾の移動速度
    bool m_isActive;      // 弾が有効かどうか
    int m_damage;         // 弾が与えるダメージ量
=======
	void AddReceivedDamage() { m_recivedDamage++; }

    virtual void OnTrigger(Collider* collider, Collider* check) override;

private:
    float m_speed;        // 弾の移動速度
    bool m_isActive;      // 弾が有効かどぁE��
    int m_damage;         // 弾が与えるダメージ釁E
	int m_recivedDamage;    // �_���[�W���󂯂���  
	int m_MaxrecivedDamage; // �_���[�W���󂯂�max�ɂȂ�ƋZ���o��
>>>>>>> main
    CapsuleCollider* mpCollider;
};
