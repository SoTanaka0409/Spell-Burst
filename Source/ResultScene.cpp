#include "ResultScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Master.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Utility.h"
#include "GameScene.h"
#include "Player.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

bool ResultScene::kIsVictory = false;

void ResultScene::Initialize()
{
	state_timer_ = 0;
	particles_.clear();

	if (kIsVictory)
	{
		SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-115.mp3");
		bg_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/bg_phase1.png");

		Utility::SaveTimeRanking((GameScene::play_frame_count_ * 1000) / 60);
	}
	else
	{
		SoundManager::GetInstance()->PlayBGM("Resource/BGM/MusMus-BGM-112.mp3");
		bg_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/bg_phase3.png");
	}

	if (Player::kSelectedCharacterType == 2)
	{
		player_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/player2.png");
	}
	else if (Player::kSelectedCharacterType == 3)
	{
		player_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/player3.png");
	}
	else
	{
		player_graph_ = ResourceManager::GetInstance()->GetGraph("Resource/player.png");
	}
}

void ResultScene::Update()
{
	state_timer_++;

	if (InputManager::CheckDownKey(KEY_INPUT_RETURN) || InputManager::CheckDownKey(KEY_INPUT_Z) ||
		(GetMouseInput() & MOUSE_INPUT_LEFT))
	{
		if (state_timer_ > 60)
		{
			SoundManager::GetInstance()->PlaySE("Resource/SE/se_button1.mp3");
			Master::sceneManager->SetNextScene(SceneManager::kSceneTitle);
		}
	}

	if (kIsVictory)
	{
		UpdateVictory();
	}
	else
	{
		UpdateGameOver();
	}

	particles_.erase(
		std::remove_if(particles_.begin(), particles_.end(),
			[this](ResultParticle& p)
			{
				p.x += p.vx_;
				p.y += p.vy_;
				p.angle_ += p.rot_speed_;
				if (kIsVictory)
				{
					p.vx_ += std::sin(state_timer_ * 0.05f + p.y * 0.01f) * 0.1f;
				}
				p.life_--;
				return p.life_ <= 0 || p.y > Utility::kScreenHeight + 100 || p.y < -100;
			}),
		particles_.end());

	Scene::Update();
}

void ResultScene::UpdateVictory()
{
	if (state_timer_ % 2 == 0)
	{
		ResultParticle p;
		p.x = static_cast<float>(rand() % Utility::kScreenWidth);
		p.y = -50.0f;
		p.vx_ = (rand() % 100 - 50) / 20.0f;
		p.vy_ = (rand() % 100 + 50) / 20.0f;
		p.size_ = 5.0f + (rand() % 15);
		p.angle_ = 0.0f;
		p.rot_speed_ = (rand() % 100 - 50) / 200.0f;

		int r = 150 + rand() % 105;
		int g = 150 + rand() % 105;
		int b = 50 + rand() % 105;
		p.color_ = GetColor(r, g, b);
		p.life_ = 300;
		particles_.push_back(p);
	}
}

void ResultScene::UpdateGameOver()
{
	if (state_timer_ % 3 == 0)
	{
		ResultParticle p;
		p.x = static_cast<float>(rand() % Utility::kScreenWidth);
		p.y = Utility::kScreenHeight + 50.0f;
		p.vx_ = (rand() % 100 - 50) / 30.0f;
		p.vy_ = -(rand() % 100 + 50) / 30.0f;
		p.size_ = 3.0f + (rand() % 10);
		p.angle_ = 0.0f;
		p.rot_speed_ = 0.0f;

		p.color_ = GetColor(150 + rand() % 105, 0, 0);
		p.life_ = 300;
		particles_.push_back(p);
	}
}

void ResultScene::DrawOutlinedString(int x, int y, const char* str, unsigned int color, unsigned int outlineColor, int fontHandle)
{
	DrawStringToHandle(x - 2, y - 2, str, outlineColor, fontHandle);
	DrawStringToHandle(x + 2, y - 2, str, outlineColor, fontHandle);
	DrawStringToHandle(x - 2, y + 2, str, outlineColor, fontHandle);
	DrawStringToHandle(x + 2, y + 2, str, outlineColor, fontHandle);
	DrawStringToHandle(x, y, str, color, fontHandle);
}

void ResultScene::Draw()
{
	Scene::Draw();

	if (bg_graph_ != -1)
	{
		DrawExtendGraph(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, bg_graph_, FALSE);
		if (!kIsVictory)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
			DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(30, 0, 0), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else
	{
		DrawBox(0, 0, Utility::kScreenWidth, Utility::kScreenHeight, GetColor(0, 10, 20), TRUE);
	}

	if (player_graph_ != -1)
	{
		int w, h;
		GetGraphSize(player_graph_, &w, &h);
		float scale = 2.5f;
		int drawW = (int)(w * scale);
		int drawH = (int)(h * scale);

		int targetX = kIsVictory ? 150 : Utility::kScreenWidth / 2 - drawW / 2;
		int startX = kIsVictory ? -500 : Utility::kScreenWidth / 2 - drawW / 2;
		int targetY = Utility::kScreenHeight - drawH - 50;
		int startY = kIsVictory ? targetY : Utility::kScreenHeight + 200;

		float t = (state_timer_ > 60) ? 1.0f : (state_timer_ / 60.0f);
		t = 1.0f - std::pow(1.0f - t, 3.0f);

		int drawX = startX + (int)((targetX - startX) * t);
		int drawY = startY + (int)((targetY - startY) * t);

		if (!kIsVictory)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		}
		DrawExtendGraph(drawX, drawY, drawX + drawW, drawY + drawH, player_graph_, TRUE);
		if (!kIsVictory)
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	for (const auto& p : particles_)
	{
		if (kIsVictory)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (p.life_ > 200) ? 255 : p.life_);
			int s = static_cast<int>(p.size_);
			int cx = static_cast<int>(p.x);
			int cy = static_cast<int>(p.y);
			DrawCircle(cx, cy, s, p.color_, TRUE);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (p.life_ > 100) ? 150 : p.life_);
			DrawCircle(static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(p.size_), p.color_, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int promptFont = ResourceManager::GetInstance()->GetFont(32, 2);

	if (kIsVictory)
	{
		DrawVictory();
	}
	else
	{
		DrawGameOver();
	}

	if (state_timer_ > 90)
	{
		int alpha = (int)(128 + 127 * std::sin(state_timer_ / 10.0f));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawOutlinedString(350, 600, "Press ENTER / Click to return to Title", GetColor(255, 255, 255), GetColor(0, 0, 0), promptFont);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ResultScene::DrawVictory()
{
	int titleFont = ResourceManager::GetInstance()->GetFont(96, 8);
	int subFont = ResourceManager::GetInstance()->GetFont(48, 4);

	float textT = (state_timer_ > 40) ? 1.0f : (state_timer_ / 40.0f);
	textT = 1.0f - std::pow(1.0f - textT, 4.0f);
	int titleY = -100 + (int)(250 * textT);

	DrawOutlinedString(500, titleY, "GAME CLEAR!!", GetColor(255, 255, 0), GetColor(255, 100, 0), titleFont);
	if (state_timer_ > 60)
	{
		DrawOutlinedString(550, titleY + 120, "THANK YOU FOR PLAYING", GetColor(255, 255, 255), GetColor(0, 0, 100), subFont);
	}
}

void ResultScene::DrawGameOver()
{
	int titleFont = ResourceManager::GetInstance()->GetFont(96, 8);
	int subFont = ResourceManager::GetInstance()->GetFont(48, 4);
	float textT = (state_timer_ > 40) ? 1.0f : (state_timer_ / 40.0f);
	textT = 1.0f - std::pow(1.0f - textT, 4.0f);
	int titleY = -100 + (int)(250 * textT);

	DrawOutlinedString(350, titleY, "GAME OVER", GetColor(255, 50, 50), GetColor(50, 0, 0), titleFont);
	if (state_timer_ > 60)
	{
		DrawOutlinedString(400, titleY + 120, "TRY AGAIN...", GetColor(200, 200, 200), GetColor(50, 50, 50), subFont);
	}
}

void ResultScene::Finalize()
{
}
