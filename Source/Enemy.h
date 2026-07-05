#pragma once
#include "Character.h"

class CapsuleCollider;

// 敵キャラクターのクラス（Character継承）
class Enemy : public Character {
private:
    int enemy_type_;      
    int attack_timer_;    

    float targetX, targetY; 
    void SelectNewTarget();     

public:
    Enemy(float x, float y, int enemy_type_ = 1);
    virtual ~Enemy() override;

    void Update() override;
    void Draw() override;

    int GetEnemyType() const { return enemy_type_; }

    virtual void TakeDamage(int damage_) override;
    virtual void Kill() override;

    float GetRadius() const { 
        if (enemy_type_ == 4) return 45.0f;
        return 15.0f; 
    }

    virtual void OnTrigger(Collider* collider_, Collider* check) override;
};