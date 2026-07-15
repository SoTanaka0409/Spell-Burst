#pragma once
#include "Scene.h"

// ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ窿具ｿｽ[・ｽ・ｽ・ｽi・ｽ`・ｽ・ｽ・ｽ[・ｽg・ｽ・ｽ・ｽA・ｽ・ｽ・ｽj・ｽ・ｽX・ｽ・ｽ・ｽC・ｽh・ｽ`・ｽ・ｽ・ｽﾅ表・ｽ・ｽ・ｽ・ｽ・ｽ・ｽV・ｽ[・ｽ・ｽ・ｽN・ｽ・ｽ・ｽX
class RuleScene : public Scene
{
public:
    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽe・ｽX・ｽ・ｽ・ｽC・ｽh・ｽi・ｽ鞫懶ｿｽj・ｽ・ｽﾇみ搾ｿｽ・ｽﾝ配・ｽ・ｽﾉ格・ｽ[・ｽ・ｽ・ｽ・ｽ
    void Initialize() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽ・ｽE・ｽL・ｽ[・ｽﾅス・ｽ・ｽ・ｽC・ｽh・ｽ・ｽﾘゑｿｽﾖゑｿｽ・ｽAZ・ｽL・ｽ[・ｽﾜゑｿｽ・ｽﾍ最終・ｽX・ｽ・ｽ・ｽC・ｽh・ｽ・ｽ・ｽy・ｽ[・ｽW・ｽ・ｽStageSelectScene・ｽﾖ遷・ｽﾚゑｿｽ・ｽ・ｽ
    void Update() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽ・ｽ・ｽﾝ選・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ驛具ｿｽ[・ｽ・ｽ・ｽﾌス・ｽ・ｽ・ｽC・ｽh・ｽ鞫懶ｿｽ・ｽ・ｽ・ｽﾑ、・ｽ・ｽ・ｽ・ｽ・ｽﾌナ・ｽr・ｽQ・ｽ[・ｽV・ｽ・ｽ・ｽ・ｽ・ｽe・ｽL・ｽX・ｽg・ｽ・ｽ`・ｽ謔ｷ・ｽ・ｽ
    void Draw() override;

    // [・ｽ・ｽ・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽo・ｽ・ｽ] ・ｽﾈゑｿｽ
    // [・ｽ・ｽ・ｽ・ｽp] ・ｽﾇみ搾ｿｽ・ｽｾ全・ｽﾄのス・ｽ・ｽ・ｽC・ｽh・ｽ鞫懶ｿｽ・ｽj・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
    void Finalize() override;
private:
    void DrawRuleText(int titleFont, int font24);
    void DrawNavigationButtons(int mouseX, int mouseY, int font24);

    int rule_graphs_[6];
    int current_slide_;
};
