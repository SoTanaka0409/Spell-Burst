#pragma once
#include <map>
#include <string>

class ResourceManager
{
private:
    std::map<std::string, int> graph_map_;
    std::map<std::pair<int, int>, int> font_map_;

public:
    ResourceManager();
    ~ResourceManager();
    static ResourceManager* GetInstance();

    /*
     * 画像のグラフィックハンドルを取得する（キャッシュになければロードする）。
     * [入力] path: 画像ファイルのパス
     * [出力] グラフィックハンドル
     * [副作用] メモリに画像データがロードされ、マップに登録される
     */
    int GetGraph(const std::string& path);
    /*
     * 指定されたサイズと太さのフォントハンドルを取得する（なければ作成する）。
     * [入力] size: フォントのサイズ, thickness: フォントの太さ
     * [出力] フォントハンドル
     * [副作用] 新しいフォントが作成され、マップに登録される
     */
    int GetFont(int size, int thickness);

    /*
     * ロード済みのすべての画像・フォントメモリを解放する。
     * [入力] なし
     * [出力] なし
     * [副作用] すべてのハンドルが削除され、マップが空になる
     */
    void ClearAll();
};
