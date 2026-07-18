#pragma once
#include <string>
#include <unordered_map>

// BGMと効果音を読み込み、キャッシュして再生するクラス
class SoundManager
{
private:
    SoundManager();
    ~SoundManager();

public:
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static SoundManager* GetInstance();

    /*
     * サウンドを取得する。未読み込みならロードする。
     * [入力] path: 音声ファイルのパス
     * [出力] サウンドハンドル
     * [副作用] 音声データがキャッシュに登録される
     */
    int GetSound(const std::string& path);

    /*
     * BGMをループ再生する。
     * [入力] path: 音声ファイルのパス
     * [出力] なし
     * [副作用] 現在のBGMを止め、新しいBGMを再生する
     */
    void PlayBGM(const std::string& path);

    /*
     * 効果音を一度だけ再生する。
     * [入力] path: 音声ファイルのパス
     * [出力] なし
     * [副作用] SEが再生される
     */
    void PlaySE(const std::string& path);

    void StopBGM();

    void StopAll();

    void ClearAll();

private:
    std::unordered_map<std::string, int> sound_map_;
    int current_bgm_handle_;
};