#pragma once
#include <map>
#include <string>

class ResourceManager
{
private:
    std::map<std::string, int> graphMap;
    std::map<std::pair<int, int>, int> fontMap;

public:
    ResourceManager();
    ~ResourceManager();
    static ResourceManager* GetInstance();

    int GetGraph(const std::string& path);
    int GetFont(int size_, int thickness);

    void ClearAll();
};