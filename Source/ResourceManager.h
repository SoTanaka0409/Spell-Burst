#pragma once
#include <map>
#include <string>

/// @brief 画像、フォント、アセットパスを読み込み・キャッシュするクラス
class ResourceManager
{
private:
    std::map<std::string, int> graph_map_;              ///< 画像IDとグラフィックハンドルの対応表
    std::map<std::pair<int, int>, int> font_map_;       ///< フォントサイズ・太さとフォントハンドルの対応表
    std::map<std::string, std::string> asset_paths_;    ///< アセットIDと実ファイルパスの対応表

public:
    /// @brief リソース管理クラスを生成する
    ResourceManager();

    /// @brief リソース管理クラスを破棄する
    ~ResourceManager();

    /// @brief リソース管理クラスのインスタンスを取得する
    /// @return ResourceManager* シングルトンインスタンス
    static ResourceManager* GetInstance();

    /// @brief アセットCSVを読み込む
    /// @param csv_path CSVファイルのパス
    /// @return bool 読み込みに成功したらtrue
    bool LoadCSV(const std::string& csv_path);

    /// @brief アセットIDから実ファイルパスを取得する
    /// @param id アセットID
    /// @return std::string 実ファイルパス
    std::string GetAssetPath(const std::string& id);

    /// @brief 画像ハンドルを取得する
    /// @param id アセットIDまたはファイルパス
    /// @return int グラフィックハンドル
    int GetGraph(const std::string& id);

    /// @brief フォントハンドルを取得する
    /// @param size フォントサイズ
    /// @param thickness フォントの太さ
    /// @return int フォントハンドル
    int GetFont(int size, int thickness);

    /// @brief 読み込んだ全リソースを解放する
    void ClearAll();
};