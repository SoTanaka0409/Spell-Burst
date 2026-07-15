#pragma once
#include "Scene.h"
#include <vector>

// ・ｽ・ｽ・ｽU・ｽ・ｽ・ｽg・ｽ・ｽﾊの会ｿｽ・ｽo・ｽi・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾈど）・ｽﾉ使・ｽp・ｽ・ｽ・ｽ・ｽ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ構・ｽ・ｽ・ｽ・ｽ
struct ResultParticle
{
    float x, y;         // ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ鯉ｿｽ・ｽﾝ搾ｿｽ・ｽW
    float vx_, vy_;       // X・ｽ・ｽ・ｽ・ｽ・ｽEY・ｽ・ｽ・ｽ・ｽ・ｽﾌ移難ｿｽ・ｽ・ｽ・ｽx・ｽx・ｽN・ｽg・ｽ・ｽ
    float size_;         // ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ描・ｽ・ｽT・ｽC・ｽY
    float angle;        // ・ｽ・ｽ・ｽﾝの描・ｽ・ｽp・ｽx・ｽi・ｽ・ｽ]・ｽ・ｽﾔ）
    float rot_speed;     // ・ｽ・ｽ]・ｽ・ｽ・ｽx・ｽi・ｽ・ｽ・ｽt・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽ・ｽ・ｽZ・ｽ・ｽ・ｽ・ｽ・ｽp・ｽx・ｽj
    int color_;          // ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ色・ｽiDxLib・ｽﾌカ・ｽ・ｽ・ｽ[・ｽR・ｽ[・ｽh・ｽﾈど）
    int life;           // ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ残・ｽ・ｽ・ｽ・ｽ・ｽ・ｽi・ｽt・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽ・ｽ・ｽj
};

// ・ｽ・ｽ・ｽU・ｽ・ｽ・ｽg・ｽi・ｽQ・ｽ[・ｽ・ｽ・ｽN・ｽ・ｽ・ｽA/・ｽQ・ｽ[・ｽ・ｽ・ｽI・ｽ[・ｽo・ｽ[・ｽj・ｽ・ｽﾊゑｿｽ`・ｽ・ｽE・ｽﾇ暦ｿｽ・ｽ・ｽ・ｽ・ｽV・ｽ[・ｽ・ｽ・ｽN・ｽ・ｽ・ｽX
class ResultScene : public Scene
{
public:
    // ・ｽQ・ｽ[・ｽ・ｽ・ｽﾌ擾ｿｽ・ｽs・ｽ・ｽ・ｽﾊゑｿｽﾛ趣ｿｽ・ｽ・ｽ・ｽ・ｽﾃ的・ｽt・ｽ・ｽ・ｽO・ｽitrue: ・ｽN・ｽ・ｽ・ｽA/・ｽ・ｽ・ｽ・ｽ, false: ・ｽQ・ｽ[・ｽ・ｽ・ｽI・ｽ[・ｽo・ｽ[/・ｽs・ｽk・ｽj
    // Scene・ｽﾚ行・ｽO・ｽ・ｽGameScene・ｽ・ｽ・ｽ・ｽ・ｽ迴托ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄ鯉ｿｽ・ｽﾊゑｿｽn・ｽ・ｽ・ｽ・ｽ・ｽﾟに使・ｽp・ｽ・ｽ・ｽ・ｽ
    static bool kIsVictory;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾍ趣ｿｽ・ｽ・ｽ・ｽ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽA・ｽw・ｽi・ｽ竡ｩ・ｽ@・ｽ鞫懶ｿｽﾌ読み搾ｿｽ・ｽﾝゑｿｽs・ｽ・ｽ
    void Initialize() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽﾌ更・ｽV・ｽ・ｽ・ｽ・ｽﾑ、・ｽL・ｽ[・ｽ・ｽ・ｽﾍ（Z・ｽL・ｽ[・ｽj・ｽﾉゑｿｽ・ｽ^・ｽC・ｽg・ｽ・ｽ・ｽﾖの遷・ｽﾚ擾ｿｽ・ｽ・ｽ・ｽ・ｽs・ｽ・ｽ
    void Update() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽ・ｽs・ｽﾉ会ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽw・ｽi・ｽF・ｽA・ｽe・ｽL・ｽX・ｽg・ｽA・ｽ・ｽ・ｽ@・ｽ鞫懶ｿｽi・ｽs・ｽk・ｽ・ｽ・ｽﾍ暗転・ｽ・ｽ・ｽj・ｽA・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽ・ｽ`・ｽ謔ｷ・ｽ・ｽ
    void Draw() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽﾇみ搾ｿｽ・ｽｾ画像・ｽ・ｽ・ｽ\・ｽ[・ｽX・ｽ・ｽj・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
    void Finalize() override;

private:
    void UpdateVictory();
    void UpdateGameOver();
    void DrawVictory();
    void DrawGameOver();
    std::vector<ResultParticle> particles_; // ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾈどの会ｿｽ・ｽo・ｽp・ｽp・ｽ[・ｽe・ｽB・ｽN・ｽ・ｽ・ｽ・ｽﾇ暦ｿｽ・ｽ・ｽ・ｽ・ｽz・ｽ・ｽ
    int state_timer_;                        // ・ｽV・ｽ[・ｽ・ｽ・ｽJ・ｽn・ｽ・ｽ・ｽ・ｽﾌ経・ｽﾟ趣ｿｽ・ｽﾔゑｿｽv・ｽ・ｽ^・ｽC・ｽ}・ｽ[・ｽi・ｽ・ｽ・ｽ・ｽ・ｽﾌフ・ｽF・ｽ[・ｽh・ｽC・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾍ趣ｿｽt・ｽﾌ遅・ｽ・ｽ・ｽﾉ使・ｽp・ｽj
    int bg_graph_;                           // ・ｽw・ｽi・ｽ鞫懶ｿｽﾌグ・ｽ・ｽ・ｽt・ｽB・ｽb・ｽN・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽiDxLib・ｽp・ｽj
    int player_graph_;                       // ・ｽ・ｽ・ｽ@・ｽi・ｽv・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ[・ｽj・ｽ鞫懶ｿｽﾌグ・ｽ・ｽ・ｽt・ｽB・ｽb・ｽN・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ

    // [・ｽ・ｽ・ｽ・ｽ] x, y: ・ｽ`・ｽ・ｽ・ｽ・ｽW, str: ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ, color_: ・ｽ・ｽ・ｽ・ｽ・ｽF, outline_color: ・ｽ・ｽ・ｽF, font_handle: ・ｽt・ｽH・ｽ・ｽ・ｽg
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽw・ｽ閧ｳ・ｽ黷ｽ・ｽ・ｽ・ｽW・ｽﾉ会ｿｽ・ｽ・ｽ・ｽt・ｽ・ｽ・ｽﾌ包ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ`・ｽ謔ｷ・ｽ・ｽi・ｽ・ｽ・ｽF・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌゑｿｽ・ｽﾟのヘ・ｽ・ｽ・ｽp・ｽ[・ｽﾖ撰ｿｽ・ｽj
    void DrawOutlinedString(int x, int y, const char* str, unsigned int color_, unsigned int outline_color, int font_handle);
};
