#pragma once
#include <string>
#include <unordered_map>

class ResourceManager {
private:
    ResourceManager();
    ~ResourceManager();

public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager* GetInstance();

    int GetGraph(const std::string& path);
    
    int GetFont(int size, int thickness = -1);

    void ClearAll();

private:
    std::unordered_map<std::string, int> m_graphMap;
    std::unordered_map<int, int> m_fontMap;
};
