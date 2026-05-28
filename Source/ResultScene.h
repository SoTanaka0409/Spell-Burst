#pragma once
#include "Scene.h"
#include <vector>

struct ResultParticle {
    float x, y;
    float vx, vy;
    float size;
    float angle;
    float rotSpeed;
    int color;
    int life;
};

class ResultScene : public Scene {
public:
    static bool s_isVictory;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;

private:
    std::vector<ResultParticle> m_particles;
    int m_stateTimer;
    int m_bgGraph;
    int m_playerGraph;
    
    // 縁取り付きテキスト描画用のヘルパー
    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);
};
