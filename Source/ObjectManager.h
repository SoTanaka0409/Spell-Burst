#pragma once
#include <list>
#include <vector>
#include "Object2D.h"

// 2Dオブジェクト全体のライフサイクルを統括する管理クラス
// 自機、敵、弾、エフェクトなどの全オブジェクトをリストで保持し、一括で更新・描画・削除を行う
class ObjectManager
{
public:
    // [入力] なし
    // [出力] なし
    // [副作用] リストの初期化を行う。デストラクタでは管理中の全オブジェクトのメモリを解放する
    ObjectManager();
    ~ObjectManager();

    // [入力] なし
    // [出力] なし
    // [副作用] リストに登録されている全てのオブジェクトのDraw関数を呼び出し、画面に描画する
    void Draw();

    // [入力] なし
    // [出力] なし
    // [副作用] リストに登録されている全てのオブジェクトのUpdate関数を呼び出し、座標や状態を更新する
    void Update();

    // [入力] object2D: 追加対象となるオブジェクトのポインタ
    // [出力] なし
    // [副作用] 生成されたオブジェクトを管理リスト(mObject2DList)に追加する
    void AddObject(Object2D* object2D);

    // [入力] なし
    // [出力] なし
    // [副作用] リスト内の全てのオブジェクトを強制的に破棄（delete）し、リストを空にする（シーン終了時などに使用）
    void DeleteAll2D();

    // [入力] なし
    // [出力] なし
    // [副作用] 削除フラグ（死亡・消滅状態など）が立っているオブジェクトをリストから探し出し、安全にメモリから破棄してリストから除外する
    void DeleteAll2DIfNeeded();

    // [入力] tag: 検索したいオブジェクトのタグ（Player, Enemy, Bulletなど）
    // [出力] Object2D*: 条件に一致した最初のオブジェクトのポインタ（見つからない場合はnullptr）
    // [副作用] なし
    Object2D* GetObject2DByTag(Object2D::Tag2D tag);

    // [入力] tag: 検索したいオブジェクトのタグ
    // [出力] std::vector<Object2D*>: 条件に一致した全てのオブジェクトのポインタを格納した配列
    // [副作用] なし
    std::vector<Object2D*> GetObject2DListByTag(Object2D::Tag2D tag);

    // --- ゲッター群 ---
    // 現在管理しているオブジェクトの総数を取得する
    size_t GetObjectCount() const { return mObject2DList.size(); }

    // オブジェクトのリスト全体への参照を取得する（衝突判定の総当たり処理などに使用）
    const std::list<Object2D*>& GetObjectList() const { return mObject2DList; }

private:
    std::list<Object2D*> mObject2DList;   // 稼働中の全2Dオブジェクトを保持するリスト（挿入・削除が高速なstd::listを使用）
    Object2D* m_player2D = nullptr;       // プレイヤーオブジェクトへのポインタ（高速アクセス用のキャッシュとして保持）
};