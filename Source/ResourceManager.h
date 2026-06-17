#pragma once
#include <map>
#include <string>

class ResourceManager
{
private:
    std::map<std::string, int> m_graphMap;
    std::map<std::pair<int, int>, int> m_fontMap;

public:
    ResourceManager();
    ~ResourceManager();
    static ResourceManager* GetInstance();

    int GetGraph(const std::string& path);
    int GetFont(int size, int thickness);

    void ClearAll();
};