#pragma once
#include <string>
#include <unordered_map>

/// @brief BGMと効果音を読み込み、キャッシュして再生するクラス
class SoundManager
{
private:
    /// @brief サウンド管理クラスを生成する
    SoundManager();

    /// @brief サウンド管理クラスを破棄する
    ~SoundManager();

public:
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    /// @brief サウンド管理クラスのインスタンスを取得する
    /// @return SoundManager* シングルトンインスタンス
    static SoundManager* GetInstance();

    /// @brief サウンドを取得する。未読み込みならロードする
    /// @param path 音声ファイルのパス
    /// @return int サウンドハンドル
    int GetSound(const std::string& path);

    /// @brief BGMをループ再生する
    /// @param path 音声ファイルのパス
    void PlayBGM(const std::string& path);

    /// @brief 効果音を一度だけ再生する
    /// @param path 音声ファイルのパス
    void PlaySE(const std::string& path);

    /// @brief 再生中のBGMを停止する
    void StopBGM();

    /// @brief 再生中の全サウンドを停止する
    void StopAll();

    /// @brief 読み込んだ全サウンドを解放する
    void ClearAll();

private:
    std::unordered_map<std::string, int> sound_map_; ///< 音声パスとサウンドハンドルの対応表
    int current_bgm_handle_;                         ///< 現在再生中のBGMハンドル
};