#pragma once
#include <string>
#include <unordered_map>

class SoundManager {
private:
    SoundManager();
    ~SoundManager();

public:
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static SoundManager* GetInstance();

    // サウンドハンドルを取得（無ければロードする）
    int GetSound(const std::string& path);

    // BGMの再生（ループ）
    void PlayBGM(const std::string& path);
    
    // SEの再生（単発）
    void PlaySE(const std::string& path);

    // BGMの停止
    void StopBGM();

    // すべての音を停止
    void StopAll();

    // すべての音のメモリ解放
    void ClearAll();

private:
    std::unordered_map<std::string, int> m_soundMap;
    int m_currentBGMHandle;
};
