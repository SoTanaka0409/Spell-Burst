#include "StageSelectScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "GameScene.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cstring>

/// @brief 初期化処理を行う
void StageSelectScene::Initialize()
{
	phase_ = 0;
	ui_button_graph_ = ResourceManager::GetInstance()->GetGraph("IMG_UI_BTN_BASE");
	wait_count_ = 0;
	SoundManager::GetInstance()->PlayBGM("BGM_169");
}

/// @brief 毎フレームの更新処理を行う
void StageSelectScene::Update()
{
	wait_count_++;

	if (wait_count_ < 60)
	{
		return;
	}

	static int prevMouseInput = 0;
	int currentMouseInput = GetMouseInput();
	bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
	prevMouseInput = currentMouseInput;

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (isLeftClicked && mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60)
	{
		SoundManager::GetInstance()->PlaySE("SE_BTN1");

		if (phase_ == 1)
		{
			phase_ = 0;
		}
		else
		{
			Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
		}
		return;
	}

	int cx = Utility::kScreenWidth / 2;
	int cy = Utility::kScreenHeight / 2;

	if (phase_ == 0)
	{
		UpdateCharacterSelect(mouseX, mouseY, isLeftClicked, cx, cy);
	}
	else if (phase_ == 1)
	{
		UpdateStageSelect(mouseX, mouseY, isLeftClicked, cx, cy);
	}
}

/// @brief UpdateCharacterSelect を実行する
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
/// @param isLeftClicked isLeftClicked の値
/// @param cx cx の値
/// @param cy cy の値
void StageSelectScene::UpdateCharacterSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy)
{
	int gap = 200;
	int charW = 120;
	int charH = 120;
	int charY = cy - 50;
	int char1X = cx - gap - charW / 2;
	int char2X = cx - charW / 2;
	int char3X = cx + gap - charW / 2;

	if (isLeftClicked)
	{
		if (mouseX >= char1X && mouseX <= char1X + charW && mouseY >= charY && mouseY <= charY + charH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Player::kSelectedCharacterType = 1;
			phase_ = 1;
		}
		else if (mouseX >= char2X && mouseX <= char2X + charW && mouseY >= charY && mouseY <= charY + charH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Player::kSelectedCharacterType = 2;
			phase_ = 1;
		}
		else if (mouseX >= char3X && mouseX <= char3X + charW && mouseY >= charY && mouseY <= charY + charH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Player::kSelectedCharacterType = 3;
			phase_ = 1;
		}
	}
}

/// @brief UpdateStageSelect を実行する
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
/// @param isLeftClicked isLeftClicked の値
/// @param cx cx の値
/// @param cy cy の値
void StageSelectScene::UpdateStageSelect(int mouseX, int mouseY, bool isLeftClicked, int cx, int cy)
{
	int btnW = 300;
	int btnH = 80;
	int btnX = cx - btnW / 2;
	int btnY1 = cy - 100;
	int btnY2 = btnY1 + 100;
	int btnY3 = btnY2 + 100;

	if (isLeftClicked)
	{
		if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			GameScene::current_stage_ = 1;
			Master::sceneManager->SetNextScene(SceneManager::kSceneGame);
		}
		else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			GameScene::current_stage_ = 2;
			Master::sceneManager->SetNextScene(SceneManager::kSceneGame);
		}
		else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			GameScene::current_stage_ = 3;
			Master::sceneManager->SetNextScene(SceneManager::kSceneGame);
		}

		wait_count_ = 0;
	}
}


/// @brief DrawButton を実行する
/// @param x x の値
/// @param y y の値
/// @param w w の値
/// @param h h の値
/// @param text text の値
/// @param hover hover の値
/// @param color color の値
/// @param font24 font24 の値
void StageSelectScene::DrawButton(int x, int y, int w, int h, const char* text, bool hover, int color, int font24)
{
	if (ui_button_graph_ != -1)
	{
		if (hover)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawExtendGraph(x, y, x + w, y + h, ui_button_graph_, TRUE);

			SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
			DrawBox(x, y, x + w, y + h, color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawExtendGraph(x, y, x + w, y + h, ui_button_graph_, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else
	{
		DrawBox(x, y, x + w, y + h, hover ? color : GetColor(50, 50, 50), TRUE);
		DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), FALSE);
	}

	if (text)
	{
		int tw = GetDrawStringWidthToHandle(text, (int)strlen(text), font24);
		DrawStringToHandle(x + (w - tw) / 2, y + (h - 24) / 2, text, GetColor(255, 255, 255), font24);
	}
}

/// @brief 描画処理を行う
void StageSelectScene::Draw()
{
	DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(20, 25, 40), TRUE);
	Scene::Draw();

	int titleFont = ResourceManager::GetInstance()->GetFont(48, 5);
	int subFont = ResourceManager::GetInstance()->GetFont(32, 4);
	int font24 = ResourceManager::GetInstance()->GetFont(24, 3);

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	bool hoverBack = (mouseX >= 20 && mouseX <= 120 && mouseY >= 20 && mouseY <= 60);
	DrawButton(20, 20, 100, 40, "戻る", hoverBack, GetColor(150, 150, 150), font24);

	int cx = Utility::kScreenWidth / 2;
	int cy = Utility::kScreenHeight / 2;

	if (phase_ == 0)
	{
		DrawCharacterSelect(cx, cy, mouseX, mouseY, font24, subFont);
	}
	else if (phase_ == 1)
	{
		DrawStageSelect(cx, cy, mouseX, mouseY, font24, titleFont);
	}

}

/// @brief DrawCharacterSelect を実行する
/// @param cx cx の値
/// @param cy cy の値
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
/// @param font24 font24 の値
/// @param subFont subFont の値
void StageSelectScene::DrawCharacterSelect(int cx, int cy, int mouseX, int mouseY, int font24, int subFont)
{
	const char* titleTxt = "キャラクターを選んでください";
	int tw = GetDrawStringWidthToHandle(titleTxt, (int)strlen(titleTxt), subFont);
	DrawStringToHandle((Utility::kScreenWidth - tw) / 2, cy - 150, titleTxt, GetColor(200, 200, 200), subFont);

	int tex1 = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER1");
	int tex2 = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER2");
	int tex3 = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER3");

	int gap = 200;
	int charW = 120;
	int charH = 120;
	int charY = cy - 50;
	int char1X = cx - gap - charW / 2;
	int char2X = cx - charW / 2;
	int char3X = cx + gap - charW / 2;

	bool hover1 = (mouseX >= char1X && mouseX <= char1X + charW && mouseY >= charY && mouseY <= charY + charH);
	DrawButton(char1X, charY, charW, charH, nullptr, hover1, GetColor(100, 100, 255), font24);
	int s1 = hover1 ? 55 : 45;
	DrawExtendGraph(char1X + charW / 2 - s1, charY + charH / 2 - s1, char1X + charW / 2 + s1, charY + charH / 2 + s1, tex1, TRUE);
	const char* charName1 = "標準タイプ";
	int cw1 = GetDrawStringWidthToHandle(charName1, (int)strlen(charName1), font24);
	DrawStringToHandle(char1X + (charW - cw1) / 2, charY + charH + 10, charName1, GetColor(200, 200, 255), font24);
	if (hover1) DrawStringToHandle(char1X - 45, charY + charH + 40, "必殺技：極太レーザー", GetColor(255, 255, 0), font24);

	bool hover2 = (mouseX >= char2X && mouseX <= char2X + charW && mouseY >= charY && mouseY <= charY + charH);
	DrawButton(char2X, charY, charW, charH, nullptr, hover2, GetColor(255, 100, 100), font24);
	int s2 = hover2 ? 55 : 45;
	DrawExtendGraph(char2X + charW / 2 - s2, charY + charH / 2 - s2, char2X + charW / 2 + s2, charY + charH / 2 + s2, tex2, TRUE);
	const char* charName2 = "拡散タイプ";
	int cw2 = GetDrawStringWidthToHandle(charName2, (int)strlen(charName2), font24);
	DrawStringToHandle(char2X + (charW - cw2) / 2, charY + charH + 10, charName2, GetColor(255, 200, 200), font24);
	if (hover2) DrawStringToHandle(char2X - 45, charY + charH + 40, "必殺技：虹色ウェーブ", GetColor(255, 255, 0), font24);

	bool hover3 = (mouseX >= char3X && mouseX <= char3X + charW && mouseY >= charY && mouseY <= charY + charH);
	DrawButton(char3X, charY, charW, charH, nullptr, hover3, GetColor(100, 255, 100), font24);
	int s3 = hover3 ? 55 : 45;
	DrawExtendGraph(char3X + charW / 2 - s3, charY + charH / 2 - s3, char3X + charW / 2 + s3, charY + charH / 2 + s3, tex3, TRUE);
	const char* charName3 = "追尾タイプ";
	int cw3 = GetDrawStringWidthToHandle(charName3, (int)strlen(charName3), font24);
	DrawStringToHandle(char3X + (charW - cw3) / 2, charY + charH + 10, charName3, GetColor(200, 255, 200), font24);
	if (hover3) DrawStringToHandle(char3X - 35, charY + charH + 40, "必殺技：桜吹雪", GetColor(255, 255, 0), font24);
}
/// @brief DrawStageSelect を実行する
/// @param cx cx の値
/// @param cy cy の値
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
/// @param font24 font24 の値
/// @param titleFont titleFont の値
void StageSelectScene::DrawStageSelect(int cx, int cy, int mouseX, int mouseY, int font24, int titleFont)
{
	const char* titleTxt = "難易度を選んでください";
	int tw = GetDrawStringWidthToHandle(titleTxt, (int)strlen(titleTxt), titleFont);
	DrawStringToHandle((Utility::kScreenWidth - tw) / 2, cy - 200, titleTxt, GetColor(255, 255, 255), titleFont);

	int btnW = 300;
	int btnH = 80;
	int btnX = cx - btnW / 2;
	int btnY1 = cy - 100;
	int btnY2 = btnY1 + 100;
	int btnY3 = btnY2 + 100;

	bool hover1 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH);
	DrawButton(btnX, btnY1, btnW, btnH, "ステージ1：ふつう", hover1, GetColor(150, 255, 150), font24);

	bool hover2 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH);
	DrawButton(btnX, btnY2, btnW, btnH, "ステージ2：むずかしい", hover2, GetColor(255, 200, 100), font24);

	bool hover3 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH);
	DrawButton(btnX, btnY3, btnW, btnH, "ステージ3：とてもむずかしい", hover3, GetColor(255, 100, 100), font24);
}

/// @brief 終了処理を行う
void StageSelectScene::Finalize()
{
}
