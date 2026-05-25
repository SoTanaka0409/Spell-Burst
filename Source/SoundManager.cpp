#include "SoundManager.h"
#include <DxLib.h>

SoundManager::SoundManager() : m_currentBGMHandle(-1) {
}

SoundManager::~SoundManager() {
    ClearAll();
}

SoundManager* SoundManager::GetInstance() {
    static SoundManager instance;
    return &instance;
}

int SoundManager::GetSound(const std::string& path) {
    if (m_soundMap.find(path) == m_soundMap.end()) {
        int handle = LoadSoundMem(path.c_str());
        m_soundMap[path] = handle;
    }
    return m_soundMap[path];
}

void SoundManager::PlayBGM(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        // 現在のBGMが違う場合は止める
        if (m_currentBGMHandle != -1 && m_currentBGMHandle != handle) {
            StopSoundMem(m_currentBGMHandle);
        }
        
        // 再生されていない場合のみ再生開始
        if (CheckSoundMem(handle) == 0) {
            PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
            m_currentBGMHandle = handle;
        }
    }
}

void SoundManager::PlaySE(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::StopBGM() {
    if (m_currentBGMHandle != -1) {
        StopSoundMem(m_currentBGMHandle);
        m_currentBGMHandle = -1;
    }
}

void SoundManager::StopAll() {
    // 全てのサウンドの再生を停止
    for (auto& pair : m_soundMap) {
        if (pair.second != -1) {
            StopSoundMem(pair.second);
        }
    }
    m_currentBGMHandle = -1;
}

void SoundManager::ClearAll() {
    StopAll();
    for (auto& pair : m_soundMap) {
        if (pair.second != -1) {
            DeleteSoundMem(pair.second);
        }
    }
    m_soundMap.clear();
}
