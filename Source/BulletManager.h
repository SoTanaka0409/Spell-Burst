#pragma once
#include <vector>

class Bullet;

// 画面上に存在する全ての弾オブジェクトを管理するクラス
// (現在未使用または旧仕様の可能性があるが、存在する場合はリスト管理を行う)
class BulletManager {
private:
    std::vector<Bullet*> m_bullets; 

public:
    BulletManager();
    ~BulletManager();

    // [入力] なし
    // [出力] なし
    // [副作用] 管理しているすべての弾を破棄しリストを空にする
    void Initialize();

    // [入力] なし
    // [出力] なし
    // [副作用] 各弾のUpdateを呼び、無効(isActive == false)な弾をリストから除外してdeleteする
    void Update();

    // [入力] なし
    // [出力] なし
    // [副作用] 生存しているすべての弾のDraw関数を呼び出す
    void Draw();

    // [入力] x, y: 生成座標
    // [出力] なし
    // [副作用] 新しい弾を生成し、管理リストに追加する
    void SpawnBullet(float x, float y);

    const std::vector<Bullet*>& GetBullets() const { return m_bullets; }
};