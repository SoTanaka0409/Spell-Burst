#pragma once
#include "Character.h"

class CapsuleCollider;

// 敵キャラクターのクラス（Character継承）
class Enemy : public Character {
private:
    int m_enemyType;      
    int m_attackTimer;    

    float m_targetX, m_targetY; 
    void SelectNewTarget();     

public:
    Enemy(float x, float y, int enemyType = 1);
    virtual ~Enemy() override;

    void Update() override;
    void Draw() override;

    int GetEnemyType() const { return m_enemyType; }

    virtual void TakeDamage(int damage) override;
    virtual void Kill() override;

    float GetRadius() const { 
        if (m_enemyType == 4) return 45.0f;
        return 15.0f; 
    }

    virtual void OnTrigger(Collider* collider, Collider* check) override;
};