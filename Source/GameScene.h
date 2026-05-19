#pragma once
#include "Scene.h"

// 前方宣言
class ObjectManager;

// ゲーム本編画面クラス
class GameScene : public Scene {
private:
    ObjectManager* m_objectManager;
public:
    GameScene();
    ~GameScene();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize()override;
};
