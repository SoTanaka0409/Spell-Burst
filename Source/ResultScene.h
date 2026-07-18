#pragma once
#include "Scene.h"
#include <vector>

struct ResultParticle
{
    float x, y;       // 座標
    float vx_;        // X方向の速度
    float vy_;        // Y方向の速度
    float size_;      // サイズ
    float angle_;     // 回転角
    float rot_speed_; // 回転速度
    int color_;       // 描画色
    int life_;        // 残り寿命フレーム数
};

// 勝利・敗北のリザルト画面を表示するシーン
class ResultScene : public Scene
{
public:
    static bool kIsVictory; // 勝利リザルトかどうか

public:
    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Finalize() override;

private:
    void UpdateVictory();

    void UpdateGameOver();

    void DrawVictory();

    void DrawGameOver();

private:
    std::vector<ResultParticle> particles_; // 背景演出用パーティクル
    int state_timer_;                // リザルト画面の経過タイマー
    int bg_graph_;                   // 背景画像ハンドル
    int player_graph_;               // プレイヤー画像ハンドル

    void DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle);
};