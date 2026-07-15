#include <memory>
#pragma once
#include "Scene.h"

class EnemyManager;

// 繝｡繧､繝ｳ繧ｲ繝ｼ繝騾ｲ陦後ｒ邂｡逅・☆繧九す繝ｼ繝ｳ繧ｯ繝ｩ繧ｹ
// 逕ｻ髱｢謠ｺ繧後ｄ繝偵ャ繝医せ繝医ャ繝礼ｭ峨・蜈ｨ菴薙お繝輔ぉ繧ｯ繝育憾諷九ｂ菴ｵ縺帙※邂｡逅・☆繧・
class GameScene : public Scene
{
private:
    void DrawBackground();
    void DrawTimeAttackTimer();
    void DrawEffects();

    std::unique_ptr<EnemyManager> enemy_manager_;   // 謨ｵ縺ｮ逕滓・繧・ｲ陦後ヵ繧ｧ繝ｼ繧ｺ繧堤ｮ｡逅・☆繧九・繝阪・繧ｸ繝｣繝ｼ縺ｮ繝昴う繝ｳ繧ｿ

    int cutin_timer_;               // 繧ｫ繝・ヨ繧､繝ｳ貍泌・・亥､ｧ謚逋ｺ蜍墓凾縺ｪ縺ｩ・峨・騾ｲ陦悟ｺｦ繧呈ｸｬ繧九ち繧､繝槭・
    int cutin_image_handle_;         // 繧ｫ繝・ヨ繧､繝ｳ逕ｨ逕ｻ蜒上・繧ｰ繝ｩ繝輔ぅ繝・け繝上Φ繝峨Ν・・xLib逕ｨ・・

    int screen_handle_;             // 繧ｪ繝輔せ繧ｯ繝ｪ繝ｼ繝ｳ謠冗判・育判髱｢謠ｺ繧檎ｭ峨・繝昴せ繝医お繝輔ぉ繧ｯ繝育畑・峨・逕ｻ蜒上ワ繝ｳ繝峨Ν

    int shake_timer_;               // 逕ｻ髱｢謠ｺ繧鯉ｼ医せ繧ｯ繝ｪ繝ｼ繝ｳ繧ｷ繧ｧ繧､繧ｯ・峨・谿九ｊ繝輔Ξ繝ｼ繝謨ｰ
    float shake_magnitude_;         // 逕ｻ髱｢謠ｺ繧後・蠑ｷ縺包ｼ医ヴ繧ｯ繧ｻ繝ｫ蟷・↑縺ｩ・・

    int hit_stop_timer_;             // 繝偵ャ繝医せ繝医ャ繝暦ｼ井ｸ譎ら噪縺ｪ譎る俣蛛懈ｭ｢貍泌・・峨・谿九ｊ繝輔Ξ繝ｼ繝謨ｰ

    int damage_flash_timer_;         // 繝繝｡繝ｼ繧ｸ繝輔Λ繝・す繝･縺ｮ谿九ｊ繝輔Ξ繝ｼ繝謨ｰ
    unsigned int damage_flash_color_; // 繝繝｡繝ｼ繧ｸ繝輔Λ繝・す繝･縺ｮ濶ｲ

public:
    // --- 髱咏噪・・tatic・峨Γ繝ｳ繝仙､画焚 ---
    static int currentStage;         // 迴ｾ蝨ｨ繝励Ξ繧､荳ｭ縺ｮ繧ｹ繝・・繧ｸ逡ｪ蜿ｷ
    static int playFrameCount;       // 繝励Ξ繧､髢句ｧ九°繧峨・邨碁℃繝輔Ξ繝ｼ繝謨ｰ・医せ繧ｳ繧｢險育ｮ励ｄ繧ｿ繧､繝繧｢繧ｿ繝・け逕ｨ・・
    static bool isTimeAttackActive;  // 繧ｿ繧､繝繧｢繧ｿ繝・け繝｢繝ｼ繝峨′譛牙柑縺九←縺・°縺ｮ繝輔Λ繧ｰ

    // 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ / 繝・せ繝医Λ繧ｯ繧ｿ
    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 繧ｪ繝悶ず繧ｧ繧ｯ繝医・逕滓・繝ｻ遐ｴ譽・ｒ陦後≧・亥ｮ滄圀縺ｮ蛻晄悄蛹門・逅・・Initialize縺ｧ螳溯｡鯉ｼ・
    GameScene();
    virtual ~GameScene() override;

    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 繝槭ロ繝ｼ繧ｸ繝｣繝ｼ鬘槭・逕滓・縲∝推遞ｮ繝ｪ繧ｽ繝ｼ繧ｹ・育判蜒上ｄ繧ｵ繧ｦ繝ｳ繝会ｼ峨・遒ｺ菫昴√ち繧､繝槭・縺ｮ蛻晄悄蛹悶ｒ陦後≧
    void Initialize() override;

    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 繝偵ャ繝医せ繝医ャ繝鈴撼驕ｩ逕ｨ譎ゅ・蜷・が繝悶ず繧ｧ繧ｯ繝茨ｼ郁・讖溘∵雰縲∝ｼｾ縺ｪ縺ｩ・峨・迥ｶ諷九ｒ譖ｴ譁ｰ縺励∬｡晉ｪ∝愛螳壹ｒ蜃ｦ逅・☆繧・
    void Update() override;

    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 繧ｪ繝輔せ繧ｯ繝ｪ繝ｼ繝ｳ(screen_handle_)縺ｫ荳蠎ｦ謠冗判縺励◆蠕後∫判髱｢謠ｺ繧・繧ｷ繧ｧ繧､繧ｯ)縺ｮ繧ｺ繝ｬ繧貞刈蜻ｳ縺励※繝｡繧､繝ｳ逕ｻ髱｢縺ｸ霆｢騾√☆繧・
    void Draw() override;

    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 遒ｺ菫昴＠縺溘・繝阪・繧ｸ繝｣繝ｼ繧・Μ繧ｽ繝ｼ繧ｹ繧堤ｴ譽・＠縲√Γ繝｢繝ｪ繝ｪ繝ｼ繧ｯ繧帝亟縺・
    void Finalize() override;

    // [蜈･蜉嫋 縺ｪ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 繝懊せ縺ｮ繧ｹ繝壹Ν繧ｫ繝ｼ繝臥匱蜍墓凾繧・・讖溘・繝逋ｺ蜍墓凾縺ｪ縺ｩ縺ｮ繧ｫ繝・ヨ繧､繝ｳ貍泌・繧ｿ繧､繝槭・繧定ｵｷ蜍輔☆繧・
    void TriggerCutin();

    // 謨ｵ繝槭ロ繝ｼ繧ｸ繝｣繝ｼ縺ｮ繝昴う繝ｳ繧ｿ繧貞叙蠕励☆繧・
    EnemyManager* GetEnemyManager() const { return enemy_manager_.get(); }

    // [蜈･蜉嫋 duration: 謠ｺ繧峨☆繝輔Ξ繝ｼ繝謨ｰ, magnitude: 謠ｺ繧後・蠑ｷ縺・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 逕ｻ髱｢謠ｺ繧後ち繧､繝槭・繧定ｨｭ螳壹＠縲∫樟蝨ｨ縺ｮ貍泌・繧剃ｸ頑嶌縺阪・驕ｩ逕ｨ縺吶ｋ・郁｢ｫ蠑ｾ譎ゅｄ辷・匱譎ゅ↓菴ｿ逕ｨ・・
    void AddScreenShake(int duration, float magnitude);

    // [蜈･蜉嫋 duration: 蛛懈ｭ｢繝輔Ξ繝ｼ繝謨ｰ
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 蠑ｷ縺・判謦・′蠖薙◆縺｣縺滄圀縺ｪ縺ｩ縲√ご繝ｼ繝蜈ｨ菴薙・譖ｴ譁ｰ蜃ｦ逅・ｒ荳譎ょ●豁｢・医ヲ繝・ヨ繧ｹ繝医ャ繝暦ｼ峨＆縺帙∵遠謦・─繧呈ｼ泌・縺吶ｋ
    void AddHitStop(int duration);

    // [蜈･蜉嫋 duration: 繝輔Λ繝・す繝･縺吶ｋ繝輔Ξ繝ｼ繝謨ｰ, color: 繝輔Λ繝・す繝･濶ｲ・・etColor遲峨〒謖・ｮ夲ｼ・
    // [蜃ｺ蜉嫋 縺ｪ縺・
    // [蜑ｯ菴懃畑] 逕ｻ髱｢繧呈欠螳夊牡縺ｧ繝輔Λ繝・す繝･縺輔○縲√ム繝｡繝ｼ繧ｸ繧・・逋ｺ縺ｮ隕冶ｦ夂噪繝輔ぅ繝ｼ繝峨ヰ繝・け繧呈署萓帙☆繧・
    void AddDamageFlash(int duration, unsigned int color);
};
