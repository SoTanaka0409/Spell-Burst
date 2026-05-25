#pragma once
#include "Scene.h"

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
		SCENE_RULE,// ・ｽ^・｜C・ｽg・ｸ・ｽ
		SCENE_TUTORIAL,
		SCENE_LEVEL,
		SCENE_GAME,    // ・｜Q・｜[・｜・s
		SCENE_3DHARD,
		SCENE_RESULT,   // ・｜｜｜｜｜｜｜ｽｽｽｸg
		SCENE_RESULTWIN,
		SCENE_NORMALRESULTSCENE,// ・｜Q・｜[・｜・ｽ・ｲI・ｽ[・｜・｜]
		SCENE_3D

	};
public:
	SceneManager();
	
	~SceneManager();


	void Initialize();

	void Draw();

	void Update();

	void Finalize();
	// ・SV・S
	void ChangeSceneIfNeeded();
	// ・Su・su・suno transfer source・su・su・su・su J・slezukusosu・su・su・su V・su [・su・su・su・su installation resistance source
	// note: ・SV・S[・S・S・SJ 
	void SetNextScene(SCENE_TYPE next) { mnNextSceneType = next; }

	void SetSceneHard(bool Hard) { SceneHard = Hard; }
	bool GetSceneHard() { return SceneHard; }

	void SetSceneNormal(bool Normal) {SceneNormal=Normal; }
	bool GetSceneNormal() { return SceneNormal; }


	// ・S・S・Sun's ・S・S・S
	Scene* GetCurrentScene() { return mpCurrentScene; }

private:
	SCENE_TYPE mnSceneType;     // ・S・S・SUN's S・S[・S・S・Sfuta・SC・Sv
	SCENE_TYPE mnNextSceneType;// ・s・s・sufushi・s [・s・s・sufta・sc・sv
	Scene* mpCurrentScene;    // ・S・S・S・S
	Scene* mp;

	bool SceneHard;
	bool SceneNormal;

};