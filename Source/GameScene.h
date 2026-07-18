#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

class GameScene : public Scene
{
private:
	void DrawBackground();
	void DrawTimeAttackTimer();
	void DrawEffects();

	std::unique_ptr<EnemyManager> enemy_manager_;

	int cutin_timer_;
	int cutin_image_handle_;

	int screen_handle_;

	int shake_timer_;
	float shake_magnitude_;

	int hit_stop_timer_;

	int damage_flash_timer_;
	unsigned int damage_flash_color_;

public:
	static int current_stage_;
	static int play_frame_count_;
	static bool is_time_attack_active_;

	GameScene();
	virtual ~GameScene() override;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void TriggerCutin();

	EnemyManager* GetEnemyManager() const { return enemy_manager_.get(); }

	void AddScreenShake(int duration, float magnitude);

	void AddHitStop(int duration);

	void AddDamageFlash(int duration, unsigned int color);
};
