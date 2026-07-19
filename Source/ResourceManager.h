#pragma once
#include <map>
#include <string>

class ResourceManager
{
private:
    std::map<std::string, int> graph_map_;
    std::map<std::pair<int, int>, int> font_map_;
    std::map<std::string, std::string> asset_paths_;

public:
    ResourceManager();
    ~ResourceManager();
    static ResourceManager* GetInstance();

    // アセットCSVを読み込み、IDとパスの対応表を作成する
    bool LoadCSV(const std::string& csv_path);

    // アセットIDから実際のファイルパスを取得する
    std::string GetAssetPath(const std::string& id);

    /*
     */
    int GetGraph(const std::string& id);
    /*
     */
    int GetFont(int size, int thickness);

    /*
     */
    void ClearAll();
};
