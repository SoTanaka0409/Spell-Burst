#pragma once
#include <map>
#include <string>

class ResourceManager
{
private:
    std::map<std::string, int> m_graphMap;

   

public:

    ResourceManager();
    ~ResourceManager();
    static ResourceManager* GetInstance();

    int GetGraph(const std::string& path);

    void ClearAll();
};
