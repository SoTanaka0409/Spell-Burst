#include "SoundManager.h"
#include <DxLib.h>

SoundManager* SoundManager::s_instance = nullptr;

SoundManager* SoundManager::GetInstance() {
    if (!s_instance) {
        s_instance = new SoundManager();
    }
    return s_instance;
}

SoundManager::SoundManager() : m_currentBgmHandle(-1) {
}

SoundManager::~SoundManager() {
    StopAll();
    for (auto& pair : m_bgms) {
        DeleteSoundMem(pair.second);
    }
    for (auto& pair : m_ses) {
        DeleteSoundMem(pair.second);
    }
}

void SoundManager::LoadBGM(const std::string& key, const std::string& path) {
    if (m_bgms.find(key) == m_bgms.end()) {
        m_bgms[key] = LoadSoundMem(path.c_str());
    }
}

void SoundManager::LoadSE(const std::string& key, const std::string& path) {
    if (m_ses.find(key) == m_ses.end()) {
        m_ses[key] = LoadSoundMem(path.c_str());
    }
}

void SoundManager::PlayBGM(const std::string& key) {
    LoadBGM(key, key);
    if (m_bgms.find(key) != m_bgms.end()) {
        if (m_currentBgmHandle != -1) {
            StopSoundMem(m_currentBgmHandle);
        }
        m_currentBgmHandle = m_bgms[key];
        PlaySoundMem(m_currentBgmHandle, DX_PLAYTYPE_LOOP);
    }
}

void SoundManager::StopBGM() {
    if (m_currentBgmHandle != -1) {
        StopSoundMem(m_currentBgmHandle);
        m_currentBgmHandle = -1;
    }
}

void SoundManager::PlaySE(const std::string& key) {
    LoadSE(key, key);
    if (m_ses.find(key) != m_ses.end()) {
        PlaySoundMem(m_ses[key], DX_PLAYTYPE_BACK);
    }
}

void SoundManager::StopAll() {
    StopBGM();
}
