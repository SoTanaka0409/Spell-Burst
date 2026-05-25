#pragma once
#include <string>
#include <unordered_map>

class SoundManager {
public:
    static SoundManager* GetInstance();
    
    void LoadBGM(const std::string& key, const std::string& path);
    void LoadSE(const std::string& key, const std::string& path);
    
    void PlayBGM(const std::string& key);
    void StopBGM();
    
    void PlaySE(const std::string& key);
    
    void StopAll();

private:
    SoundManager();
    ~SoundManager();
    
    static SoundManager* s_instance;
    
    std::unordered_map<std::string, int> m_bgms;
    std::unordered_map<std::string, int> m_ses;
    int m_currentBgmHandle;
};
