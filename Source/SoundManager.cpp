#include "SoundManager.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

SoundManager::SoundManager() : currentBGMHandle(-1) {
}

SoundManager::~SoundManager() {
    ClearAll();
}

SoundManager* SoundManager::GetInstance() {
    static SoundManager instance;
    return &instance;
}

int SoundManager::GetSound(const std::string& path) {
    if (soundMap.find(path) == soundMap.end()) {
        int handle = LoadSoundMem(path.c_str());
        soundMap[path] = handle;
    }
    return soundMap[path];
}

void SoundManager::PlayBGM(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        // 現在のBGMが違う場合は止める
        if (currentBGMHandle != -1 && currentBGMHandle != handle) {
            StopSoundMem(currentBGMHandle);
        }
        
        // 再生されていない場合のみ再生開始
        if (CheckSoundMem(handle) == 0) {
            PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
            currentBGMHandle = handle;
        }
    }
}

void SoundManager::PlaySE(const std::string& path) {
    int handle = GetSound(path);
    if (handle != -1) {
        PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
    }
}

void SoundManager::StopBGM() 
{//ＢＧＭの停止
    if (currentBGMHandle != -1)
    {
        StopSoundMem(currentBGMHandle);
        currentBGMHandle = -1;
    }
}

void SoundManager::StopAll() {
    // 全てのサウンドの再生を停止
    for (auto& pair : soundMap) {
        if (pair.second != -1) {
            StopSoundMem(pair.second);
        }
    }
    currentBGMHandle = -1;
}

void SoundManager::ClearAll() 
{
    StopAll();
    for (auto& pair : soundMap) {
        if (pair.second != -1) {
            DeleteSoundMem(pair.second);
        }
    }
    soundMap.clear();
}
