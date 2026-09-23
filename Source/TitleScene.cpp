#include "TitleScene.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "Master.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>

/// @brief TitleScene を生成する
TitleScene::TitleScene() : bg_graph_(-1), bg_scroll_x_(0.0f), ui_button_graph_(-1)
{
}

/// @brief 破棄処理を行う
TitleScene::~TitleScene()
{
}

/// @brief 初期化処理を行う
void TitleScene::Initialize()
{
	bg_graph_ = ResourceManager::GetInstance()->GetGraph("IMG_BG_TITLE");
	ui_button_graph_ = ResourceManager::GetInstance()->GetGraph("IMG_UI_BTN_BASE");
	bg_scroll_x_ = 0.0f;
	SoundManager::GetInstance()->PlayBGM("BGM_096");
	Utility::LoadTimeRanking(rankings_);
}

/// @brief 毎フレームの更新処理を行う
void TitleScene::Update()
{
	static int prevMouseInput = 0;
	int currentMouseInput = GetMouseInput();
	bool isLeftClicked = (currentMouseInput & MOUSE_INPUT_LEFT) != 0 && (prevMouseInput & MOUSE_INPUT_LEFT) == 0;
	prevMouseInput = currentMouseInput;

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	int btnW = 300;
	int btnH = 70;
	int btnX = (Utility::kScreenWidth - btnW) / 2;
	int btnY1 = Utility::kScreenHeight / 2 - 100;
	int btnY2 = btnY1 + 90;
	int btnY3 = btnY2 + 90;
	int btnY4 = btnY3 + 90;

	if (isLeftClicked)
	{
		if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Master::sceneManager->SetNextScene(SceneManager::kSceneLevel);
		}
		else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Master::sceneManager->SetNextScene(SceneManager::kSceneRule);
		}
		else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Master::sceneManager->SetNextScene(SceneManager::kSceneConfig);
		}
		else if (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY4 && mouseY <= btnY4 + btnH)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			Master::sceneManager->SetNextScene(SceneManager::kSceneNone);
		}
	}

	bg_scroll_x_ += 1.0f * Utility::time_scale_;
	if (bg_scroll_x_ >= Utility::kScreenWidth)
	{
		bg_scroll_x_ -= Utility::kScreenWidth;
	}

	Scene::Update();
}

/// @brief DrawRankings を実行する
void TitleScene::DrawRankings()
{
	int rankFont = ResourceManager::GetInstance()->GetFont(32, 2);
	DrawStringToHandle(Utility::kScreenWidth - 320, 50, "タイムアタック 上位3記録", GetColor(200, 200, 255), rankFont);

	for (size_t i = 0; i < rankings_.size() && i < 3; ++i)
	{
		int totalMs = rankings_[i];
		int ms = totalMs % 1000;
		int totalSec = totalMs / 1000;
		int sec = totalSec % 60;
		int min = totalSec / 60;
		char rankStr[64];
		sprintf_s(rankStr, "%d. %02d:%02d.%03d", (int)i + 1, min, sec, ms);
		DrawStringToHandle(Utility::kScreenWidth - 300, 100 + static_cast<int>(i) * 50, rankStr, GetColor(255, 215, 0), rankFont);
	}
}

/// @brief DrawTitleLogo を実行する
void TitleScene::DrawTitleLogo()
{
	int titleFont = ResourceManager::GetInstance()->GetFont(60, 5);

	const char* titleText = "Spell Burst";
	int titleW = GetDrawStringWidthToHandle(titleText, (int)strlen(titleText), titleFont);
	DrawStringToHandle((Utility::kScreenWidth - titleW) / 2, Utility::kScreenHeight / 4 - 30, titleText, GetColor(255, 215, 0), titleFont);
}

/// @brief DrawButtons を実行する
/// @param mouseX mouseX の値
/// @param mouseY mouseY の値
void TitleScene::DrawButtons(int mouseX, int mouseY)
{
	int btnW = 300;
	int btnH = 70;
	int btnX = (Utility::kScreenWidth - btnW) / 2;
	int btnY1 = Utility::kScreenHeight / 2 - 100;
	int btnY2 = btnY1 + 90;
	int btnY3 = btnY2 + 90;
	int btnY4 = btnY3 + 90;
	int subFont = ResourceManager::GetInstance()->GetFont(32, 4);

	auto drawBtn = [&](int x, int y, const char* text, bool hover)
		{
			if (ui_button_graph_ != -1)
			{
				if (hover)
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawExtendGraph(x, y, x + btnW, y + btnH, ui_button_graph_, TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
					DrawBox(x, y, x + btnW, y + btnH, GetColor(0, 200, 255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else
				{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
					DrawExtendGraph(x, y, x + btnW, y + btnH, ui_button_graph_, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
			else
			{
				DrawBox(x, y, x + btnW, y + btnH, hover ? GetColor(100, 150, 100) : GetColor(50, 100, 50), TRUE);
				DrawBox(x, y, x + btnW, y + btnH, GetColor(255, 255, 255), FALSE);
			}

			int tw = GetDrawStringWidthToHandle(text, (int)strlen(text), subFont);
			DrawStringToHandle(x + (btnW - tw) / 2, y + (btnH - 32) / 2, text, GetColor(255, 255, 255), subFont);
		};

	bool hover1 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY1 && mouseY <= btnY1 + btnH);
	drawBtn(btnX, btnY1, "ゲーム開始", hover1);

	bool hover2 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY2 && mouseY <= btnY2 + btnH);
	drawBtn(btnX, btnY2, "ルール", hover2);

	bool hover3 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY3 && mouseY <= btnY3 + btnH);
	drawBtn(btnX, btnY3, "設定", hover3);

	bool hover4 = (mouseX >= btnX && mouseX <= btnX + btnW && mouseY >= btnY4 && mouseY <= btnY4 + btnH);
	drawBtn(btnX, btnY4, "終了", hover4);
}

/// @brief 描画処理を行う
void TitleScene::Draw()
{
	if (bg_graph_ != -1)
	{
		float sw = Utility::kScreenWidth;
		float sh = Utility::kScreenHeight;

		DrawExtendGraph(static_cast<int>(-bg_scroll_x_), 0, static_cast<int>(-bg_scroll_x_ + sw), static_cast<int>(sh), bg_graph_, FALSE);
		DrawExtendGraph(static_cast<int>(-bg_scroll_x_ + sw), 0, static_cast<int>(-bg_scroll_x_ + sw * 2), static_cast<int>(sh), bg_graph_, FALSE);
	}
	else
	{
		DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(15, 20, 30), TRUE);
	}
	Scene::Draw();

	DrawRankings();
	DrawTitleLogo();

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	DrawButtons(mouseX, mouseY);
}

/// @brief 終了処理を行う
void TitleScene::Finalize()
{
}
