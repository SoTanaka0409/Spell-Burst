#include "Player.h"
#include "ObjectManager.h"
#include <cmath>
#include <algorithm>
#include "InputManager.h"
#include "Bullet.h"
#include "CapsuleCollider.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"
#include "Utility.h"
#include "Enemy.h"
#include "Master.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "MeleeAttack.h"
#include "MasterSpark.h"
#include "RainbowWaveManager.h"
#include "SpellCardBullet.h"
#include "SpecialBullet.h"
#include "Barrier.h"
#include "ResourceManager.h"
#include "GameScene.h"
#include "SoundManager.h"
#include "DebugLog.h"

int Player::kSelectedCharacterType = 1;

/// @brief Player を生成する
Player::Player()
	: Character(Vector2((float)Utility::kScreenWidth / 2.0f, (float)Utility::kScreenHeight / 2.0f), 15, 5.0f)
{
	SetTag(kTag2dPlayer);
	Initialize();
}

/// @brief 破棄処理を行う
Player::~Player()
{
	if (auto b = barrier_.lock())
	{
		b->SetDeleteFlag(true);
		barrier_.reset();
	}
}

/// @brief 初期化処理を行う
void Player::Initialize()
{
	position_.x = (float)Utility::kScreenWidth / 2.0f;
	position_.y = (float)Utility::kScreenHeight / 2.0f;

	level_up_timer_ = 0;
	stun_timer_ = 0;
	attack_mode_ = kAttackModeMelee;
	special_cooldown_ = 0;
	attack_power_ = 1;
	attack_timer_ = 20;
	attack_interval_ = 0;
	attack_timer2_ = 60;
	barrier_count_ = 0;

	level_ = 1;
	xp_ = 0;
	xp_needed_ = 5;
	level_up_timer_ = 0;

	spell_gauge_ = 0;
	max_spell_gauge_ = 10;

	if (kSelectedCharacterType == 2)
	{
		speed_ = 7.0f;
		max_hp_ = 10;
		hp_ = max_hp_;
	}
	else if (kSelectedCharacterType == 3)
	{
		speed_ = 5.0f;
		max_hp_ = 10;
		hp_ = max_hp_;
		attack_power_ = 2;
	}
	else
	{
		speed_ = 5.0f;
		max_hp_ = 10;
		hp_ = max_hp_;
	}

	if (collider_) delete collider_;

	collider_ = new CapsuleCollider(this, position_, position_, 4.0f);
	barrier_ = ObjectManager::Instantiate<Barrier>(position_.x, position_.y, 60.0f, Object2D::kTag2dBarrierPlayer);
}

/// @brief 毎フレームの更新処理を行う
void Player::Update()
{
	Character::Update();

	if (level_up_timer_ > 0)
	{
		level_up_timer_--;
	}

	if (stun_timer_ > 0)
	{
		return;
	}

	HandleMovement();

	if (auto b = barrier_.lock())
	{
		b->SetPosition(position_);
	}

	if (InputManager::ActionDown(InputAction::kSwitchMode))
	{
		if (attack_mode_ == kAttackModeMelee) attack_mode_ = kAttackModeSpecial;
		else attack_mode_ = kAttackModeMelee;
	}

	Attack();
}

/// @brief 描画処理を行う
void Player::Draw()
{
	DrawBarrierAura();
	DrawStunEffect();
	DrawPlayerSprite();
}

/// @brief ダメージ処理を行う
/// @param damage damage の値
void Player::TakeDamage(int damage)
{
	Character::TakeDamage(damage);
	SoundManager::GetInstance()->PlaySE("SE_BTN1");

	GameScene* scene = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
	if (scene != nullptr)
	{
		scene->AddScreenShake(8, 6.0f);
		scene->AddDamageFlash(15, GetColor(255, 30, 30));
	}
}

/// @brief 死亡時の処理を行う
void Player::OnDeath()
{
	ResultScene::kIsVictory = false;
	Master::sceneManager->SetNextScene(SceneManager::kSceneResult);
}

/// @brief Attack を実行する
void Player::Attack()
{
	int mouseInput = GetMouseInput();

	UpdateCooldowns();
	ShootNormalBullets();

	if (DebugOn)
	{
		HandleDebugAttacks(mouseInput);
	}

	HandleMeleeAndSpecialAttacks(mouseInput);
}

/// @brief UpdateCooldowns を実行する
void Player::UpdateCooldowns()
{
	attack_interval_++;
	attack_interval2_++;

	if (special_cooldown_ > 0)
	{
		special_cooldown_--;
	}
}

/// @brief HandleMeleeAndSpecialAttacks を実行する
/// @param mouseInput mouseInput の値
void Player::HandleMeleeAndSpecialAttacks(int mouseInput)
{
	if (mouseInput & MOUSE_INPUT_LEFT)
	{
		UseSpellCard();
	}
}

/// @brief AddXp を実行する
/// @param amount amount の値
void Player::AddXp(int amount)
{
	xp_ += amount;
	int oldGauge = spell_gauge_;
	spell_gauge_ += amount;

	if (spell_gauge_ >= max_spell_gauge_)
	{
		spell_gauge_ = max_spell_gauge_;
		if (oldGauge < max_spell_gauge_)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
		}
	}

	while (xp_ >= xp_needed_)
	{
		xp_ -= xp_needed_;
		level_++;
		SoundManager::GetInstance()->PlaySE("SE_BTN1");
		xp_needed_ = level_ * 5;

		hp_ = max_hp_;
		level_up_timer_ = 120;
	}
}

/// @brief 接触開始時の処理を行う
/// @param collider collider の値
/// @param check check の値
void Player::OnEnter(Collider* collider, Collider* check)
{
	if (check != nullptr && check->GetParentObject() != nullptr)
	{
		if (check->GetParentObject()->GetTag() == kTag2dEnemy)
		{
			Character* enemy = dynamic_cast<Character*>(check->GetParentObject());
			if (enemy != nullptr)
			{
				TakeDamage(1);
			}
		}
	}
}

/// @brief 接触中の処理を行う
/// @param collider collider の値
/// @param check check の値
void Player::OnTrigger(Collider* collider, Collider* check)
{
}

/// @brief 接触終了時の処理を行う
/// @param collider collider の値
/// @param check check の値
void Player::OnExit(Collider* collider, Collider* check)
{
}

/// @brief RunBarrierAttack を実行する
void Player::RunBarrierAttack()
{
}

/// @brief HandleMovement を実行する
void Player::HandleMovement()
{
	bool isFocus = InputManager::ActionPress(InputAction::kFocus);
	float currentSpeed = (isFocus ? 2.0f : speed_) * Utility::time_scale_;

	if (InputManager::ActionPress(InputAction::kMoveUp)) { position_.y -= currentSpeed; }
	if (InputManager::ActionPress(InputAction::kMoveDown)) { position_.y += currentSpeed; }
	if (InputManager::ActionPress(InputAction::kMoveLeft)) { position_.x -= currentSpeed; }
	if (InputManager::ActionPress(InputAction::kMoveRight)) { position_.x += currentSpeed; }

	position_.x = std::clamp(position_.x, 45.0f, Utility::kScreenWidth - 45.0f);
	position_.y = std::clamp(position_.y, 45.0f, Utility::kScreenHeight - 45.0f);
}

/// @brief ShootNormalBullets を実行する
void Player::ShootNormalBullets()
{
	if (attack_interval_ >= attack_timer_)
	{
		attack_interval_ = 0;

		int numBullets = level_;
		float spacing = 20.0f;
		float startX = position_.x - (numBullets - 1) * spacing / 2.0f;
		for (int i = 0; i < numBullets; ++i)
		{
			ObjectManager::Instantiate<Bullet>(startX + i * spacing, position_.y - 45.0f, static_cast<int>(attack_power_));
		}
	}
}

/// @brief HandleDebugAttacks を実行する
/// @param mouseInput mouseInput の値
void Player::HandleDebugAttacks(int mouseInput)
{
	if ((mouseInput & MOUSE_INPUT_LEFT) && attack_interval2_ >= attack_timer2_)
	{
		attack_interval2_ = 0;
		if (attack_mode_ == kAttackModeMelee)
		{
			ObjectManager::Instantiate<MeleeAttack>(position_.x, position_.y - 70.0f);
		}
		else if (attack_mode_ == kAttackModeSpecial)
		{
			if (special_cooldown_ == 0)
			{
				ObjectManager::Instantiate<SpecialBullet>(position_.x, position_.y - 90.0f);
				special_cooldown_ = 180;
			}
		}
	}
}

/// @brief UseSpellCard を実行する
void Player::UseSpellCard()
{
	if (spell_gauge_ >= max_spell_gauge_)
	{
		spell_gauge_ = 0;
		SoundManager::GetInstance()->PlaySE("SE_BTN1");

		if (kSelectedCharacterType == 1)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			ObjectManager::Instantiate<MasterSpark>(position_.x, position_.y);
		}
		else if (kSelectedCharacterType == 2)
		{
			SoundManager::GetInstance()->PlaySE("SE_BARRIER_HIT");
			ObjectManager::Instantiate<RainbowWaveManager>(position_.x, position_.y);
		}
		else if (kSelectedCharacterType == 3)
		{
			SoundManager::GetInstance()->PlaySE("SE_BTN1");
			ObjectManager::Instantiate<SpellCardBullet>(position_.x, position_.y - 90.0f);
		}

		GameScene* gs = dynamic_cast<GameScene*>(Master::sceneManager->GetCurrentScene());
		if (gs != nullptr)
		{
			gs->TriggerCutin();
		}
	}
}

/// @brief DrawBarrierAura を実行する
void Player::DrawBarrierAura()
{
	if (auto b = barrier_.lock())
	{
		if (b->IsDeployed() && b->GetHitCount() > 0)
		{
			int hit_count = b->GetHitCount();
			float ratio = static_cast<float>(hit_count) / 30.0f;

			SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(255 * ratio * 0.8f));

			int auraColor = (hit_count >= 30) ? GetColor(255, 255, 100) : GetColor(100, 200, 255);

			for (int i = 0; i < 5; i++)
			{
				float radiusBase = 60.0f + sinf(GetNowCount() * 0.005f + i) * 10.0f;
				DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), static_cast<int>(radiusBase - i * 5), auraColor, TRUE);
			}

			int time = GetNowCount();
			int numParticles = static_cast<int>(15 * ratio);
			for (int i = 0; i < numParticles; i++)
			{
				float angle = (time * 0.002f) + (i * DX_PI_F * 2.0f / numParticles);
				float dist = 40.0f + sinf(time * 0.005f + i * 1.5f) * 15.0f;
				int px = static_cast<int>(position_.x + cosf(angle) * dist);
				int py = static_cast<int>(position_.y + sinf(angle) * dist);
				DrawCircle(px, py, 6 + i % 3, auraColor, TRUE);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

/// @brief DrawStunEffect を実行する
void Player::DrawStunEffect()
{
	if (stun_timer_ > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 50, GetColor(0, 200, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/// @brief DrawPlayerSprite を実行する
void Player::DrawPlayerSprite()
{
	int playerGraphHandle = -1;
	if (kSelectedCharacterType == 1)
	{
		playerGraphHandle = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER1");
	}
	else if (kSelectedCharacterType == 2)
	{
		playerGraphHandle = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER2");
	}
	else if (kSelectedCharacterType == 3)
	{
		playerGraphHandle = ResourceManager::GetInstance()->GetGraph("IMG_CHARA_PLAYER3");
	}

	if (playerGraphHandle != -1)
	{
		DrawExtendGraph(
			static_cast<int>(position_.x - 45.0f),
			static_cast<int>(position_.y - 45.0f),
			static_cast<int>(position_.x + 45.0f),
			static_cast<int>(position_.y + 45.0f),
			playerGraphHandle,
			TRUE
		);
	}
	else
	{
		DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 45, GetColor(0, 255, 0), TRUE);
	}

	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 5, GetColor(255, 255, 255), TRUE);
	DrawCircle(static_cast<int>(position_.x), static_cast<int>(position_.y), 3, GetColor(255, 0, 0), TRUE);
}
