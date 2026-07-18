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
     */
    int GetGraph(const std::string& path);
    /*
     */
    int GetFont(int size, int thickness);

    /*
     */
    void ClearAll();
};
