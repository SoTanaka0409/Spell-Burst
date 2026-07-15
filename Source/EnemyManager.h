#pragma once
#include <vector>
#include <memory>

class Enemy;
class Boss;

// ・ｽG・ｽL・ｽ・ｽ・ｽ・ｽ・ｽN・ｽ^・ｽ[・ｽﾌ撰ｿｽ・ｽ・ｽ・ｽE・ｽi・ｽs・ｽt・ｽF・ｽ[・ｽY・ｽ搖・ｽ・ｽ・ｽ・ｽ・ｽﾇ暦ｿｽ・ｽN・ｽ・ｽ・ｽX
// ・ｽ{・ｽX・ｽo・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌ監趣ｿｽ・ｽ・ｽA・ｽ・ｽ・ｽﾝのフ・ｽF・ｽ[・ｽY・ｽi・ｽE・ｽF・ｽ[・ｽu・ｽj・ｽﾉ会ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽG・ｽﾌス・ｽ|・ｽ[・ｽ・ｽ・ｽｧ御す・ｽ・ｽ
class EnemyManager
{
private:
    int spawn_timer_;              // GoiX|[jﾔ隔v^C}[
    int defeated_count_;           // vC[|Gﾌ累計itF[Yisﾌ硝使pj
    bool boss_spawned_;            // ﾝのフF[YﾅボXﾉ出ﾇのフO

    int current_phase_;            // ﾝの進stF[YiEF[ujﾔ・
    int required_kills_;           // ﾌフF[Yﾖの移行AﾜはボXoﾉ必vﾈ敵ﾌ・
    std::weak_ptr<Boss> current_boss_;           // ﾝ出ﾄ・XIuWFNgﾖのポC^ionullptrjﾄ・XIuWFNgﾖのポC^ionullptrj

public:
    // RXgN^ / fXgN^
    // [] ﾈ・
    // [o] ﾈ・
    // [p] IuWFNgﾌ職js
    EnemyManager();
    ~EnemyManager();

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽt・ｽF・ｽ[・ｽY・ｽ笂｢・ｽ・ｽ・ｽ・ｽ・ｽA・ｽ^・ｽC・ｽ}・ｽ[・ｽﾈどの進・ｽs・ｽｵゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽi・ｽ・ｽ・ｽZ・ｽb・ｽg・ｽj・ｽ・ｽ・ｽ・ｽ
    void Initialize();

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ^・ｽC・ｽ}・ｽ[・ｽﾉ会ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽG・ｽﾌ撰ｿｽ・ｽ・ｽ・ｽA・ｽ{・ｽX・ｽﾌ出・ｽ・ｽ・ｽ・ｽ・ｽ・ｽA・ｽt・ｽF・ｽ[・ｽY・ｽﾚ行・ｽ・ｽ・ｽ・ｽ・ｽﾈどゑｿｽs・ｽ・ｽ
    void Update();

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽﾊ擾ｿｽﾉ趣ｿｽ・ｽﾌフ・ｽF・ｽ[・ｽY・ｽﾜでの要・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽA・ｽ{・ｽX・ｽo・ｽ・ｽ・ｽ・ｽ・ｽﾌ警・ｽ・ｽUI・ｽﾈどゑｿｽ`・ｽ謔ｷ・ｽ・ｽ
    void Draw();

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽI・ｽu・ｽW・ｽF・ｽN・ｽg・ｽ・ｽ・ｽX・ｽg・ｽ・ｽ・ｽ・ｽｵ、・ｽ・ｽ・ｽS・ｽ・ｽﾔ（・ｽL・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾏみ）・ｽﾌ敵・ｽ・ｽ・ｽ・ｽS・ｽﾉ・ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ尞懶ｿｽ・ｽ・ｽ・ｽ
    void DeleteEnemy();

private:
    void SpawnPhaseEnemies();
    void HandleBossTransition();
    void HandleMidBossSpawn();

public:

    // [・ｽ・ｽ・ｽ・ｽ] x, y: ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽW
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽw・ｽ閧ｳ・ｽ黷ｽ・ｽ・ｽ・ｽW・ｽﾉ奇ｿｽ{・ｽI・ｽﾈ敵・ｽI・ｽu・ｽW・ｽF・ｽN・ｽg・ｽｶ撰ｿｽ・ｽ・ｽ・ｽA・ｽQ・ｽ[・ｽ・ｽ・ｽV・ｽ[・ｽ・ｽ・ｽi・ｽ・ｽ・ｽX・ｽg・ｽ・ｽ・ｽj・ｽﾉ登・ｽ^・ｽ・ｽ・ｽ・ｽ
    void SpawnEnemy(float x, float y);

    // [・ｽ・ｽ・ｽ・ｽ] x, y: ・ｽ・ｽ・ｽ・ｽ・ｽ譓・ｽ・ｽ・ｽW, spawnnum: ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ髏・
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽv・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ[・ｽ・ｽﾇ費ｿｽ・ｽ・ｽ・ｽ・ｽ^・ｽC・ｽv・ｽA・ｽﾜゑｿｽ・ｽﾍ難ｿｽ・ｽ・ｽp・ｽ^・ｽ[・ｽ・ｽ・ｽﾅ難ｿｽ・ｽ・ｽ・ｽG・ｽ｡撰ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽV・ｽ[・ｽ・ｽ・ｽﾉ登・ｽ^・ｽ・ｽ・ｽ・ｽ
    void SpawnEnemy_Target(float x, float y, int spawnnum);

    // --- ・ｽQ・ｽb・ｽ^・ｽ[・ｽE・ｽZ・ｽb・ｽ^・ｽ[・ｽQ ---

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] int: ・ｽ・ｽ・ｽ{・ｽX・ｽi・ｽ・ｽ・ｽ・ｽ^・ｽC・ｽv・ｽﾌ敵・ｽj・ｽ・ｽ・ｽ・ｽ・ｽﾝ会ｿｽﾊ擾ｿｽﾉゑｿｽ・ｽ髏・
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽﾈゑｿｽ
    int GetMidBossCount() const;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽG・ｽ・ｽ|・ｽ・ｽ・ｽ・ｽ・ｽJ・ｽE・ｽ・ｽ・ｽg(defeated_count_)・ｽ・ｽ1・ｽ・ｽ・ｽZ・ｽ・ｽ・ｽ・ｽi・ｽG・ｽﾌ趣ｿｽ・ｽS・ｽ・ｽ・ｽﾉ呼ばゑｿｽ・ｽz・ｽ・ｽj
    void AddDefeatedCount() { defeated_count_++; }

    int GetDefeatedCount() const { return defeated_count_; }   // ・ｽ・ｽ・ｽﾝの敵・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ謫ｾ
    int GetRequiredKills() const { return required_kills_; }   // ・ｽ{・ｽX・ｽo・ｽ・ｽ・ｽ・ｽ・ｽﾉ必・ｽv・ｽﾈ目標・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ謫ｾ
    bool IsBossSpawned() const { return boss_spawned_; }       // ・ｽ{・ｽX・ｽ・ｽ・ｽ・ｽ・ｽﾉ出・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ驍ｩ・ｽ・ｽ謫ｾ
    int GetCurrentPhase() const { return current_phase_; }     // ・ｽ・ｽ・ｽﾝのフ・ｽF・ｽ[・ｽY・ｽﾔ搾ｿｽ・ｽ・ｽ謫ｾ
};
