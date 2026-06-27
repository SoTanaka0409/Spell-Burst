#include <memory>
#pragma once
#include "Scene.h"

// ゲーム全体のシーン遷移を管理するクラス
class SceneManager
{
public:
	enum SCENE_TYPE
	{
		SCENE_NONE = 0,
		SCENE_RESET,
		SCENE_NAME,
		SCENE_TITLE,
		SCENE_OPERATION,
		SCENE_RULE,
		SCENE_TUTORIAL,
		SCENE_LEVEL,
		SCENE_GAME,
		SCENE_3DHARD,
		SCENE_RESULT,
		SCENE_RESULTWIN,
		SCENE_NORMALRESULTSCENE,
		SCENE_3D
	};

public:
	SceneManager();
	~SceneManager();

    // [入力] なし
    // [出力] なし
    // [副作用] 最初のシーン（通常はTITLE等）のInitializeを呼び出し初期化する
	void Initialize();

    // [入力] なし
    // [出力] なし
    // [副作用] 現在のシーンのDraw関数を呼び出し、描画処理を委譲する
	void Draw();

    // [入力] なし
    // [出力] なし
    // [副作用] 現在のシーンのUpdate関数を呼び出す。また、次シーンが予約されていれば遷移処理を行う
	void Update();

    // [入力] なし
    // [出力] なし
    // [副作用] 現在のシーンのFinalizeを呼び出し、メモリを解放する
	void Finalize();

    // [入力] なし
    // [出力] なし
    // [副作用] mnNextSceneTypeが設定されている場合、旧シーンを破棄して新シーンを生成・初期化する
	void ChangeSceneIfNeeded();

    // [入力] next: 次に遷移したいシーンの種別列挙子
    // [出力] なし
    // [副作用] 次回Update時にシーン遷移が行われるようフラグ(nextSceneType)をセットする
	void SetNextScene(SCENE_TYPE next) { nextSceneType = next; }

	void SetSceneHard(bool Hard) { SceneHard = Hard; }
	bool GetSceneHard() { return SceneHard; }

	void SetSceneNormal(bool Normal) {SceneNormal=Normal; }
	bool GetSceneNormal() { return SceneNormal; }

	Scene* GetCurrentScene() { return currentScene.get(); }

private:
	SCENE_TYPE sceneType;     
	SCENE_TYPE nextSceneType;
	std::unique_ptr<Scene> currentScene;    
	

	bool SceneHard;
	bool SceneNormal;
};