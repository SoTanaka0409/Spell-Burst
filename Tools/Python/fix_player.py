import re

with open('Source/Player.cpp', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix barrier smart pointer logic
content = re.sub(r'if \(barrier_ != nullptr\)\s*\{\s*barrier_->SetDeleteFlag\(true\);\s*barrier_ = nullptr;\s*\}',
                 'if (auto b = barrier_.lock()) {\n        b->SetDeleteFlag(true);\n        barrier_.reset();\n    }', content)

content = re.sub(r'barrier_ = ObjectManager::GetInstance\(\)->Instantiate<Barrier>\((.*?)\);',
                 r'barrier_ = ObjectManager::GetInstance()->Instantiate<Barrier>(\1);', content) # this is just a check, it might already be correct or return raw pointer previously

content = re.sub(r'if \(barrier_ != nullptr\)\s*\{\s*barrier_->SetPosition\(this->position_\);\s*\}',
                 'if (auto b = barrier_.lock()) {\n        b->SetPosition(this->position_);\n    }', content)

content = re.sub(r'if \(barrier_ != nullptr && barrier_->IsDeployed\(\) && barrier_->GetHitCount\(\) > 0\)\s*\{\s*int hitCount = barrier_->GetHitCount\(\);',
                 'if (auto b = barrier_.lock()) {\n        if (b->IsDeployed() && b->GetHitCount() > 0) {\n            int hitCount = b->GetHitCount();', content)
content = re.sub(r'spell_gauge_ \+= hitCount \* 2;\s*\}', r'spell_gauge_ += hitCount * 2;\n        }\n    }', content)

# Inject Config.h
content = content.replace('#include"DebugLog.h"', '#include"DebugLog.h"\n#include "Config.h"')

# Replace Magic Numbers
content = content.replace(': Character(Vector2((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f), 15, 5.0f)',
                          ': Character(Vector2((float)Utility::SCREEN_WIDTH / 2.0f, (float)Utility::SCREEN_HEIGHT / 2.0f), Config::kPlayerMaxHp, Config::kPlayerSpeed)')
content = content.replace('attack_timer_ = 20;', 'attack_timer_ = Config::kPlayerAttackInterval;')
content = content.replace('attack_timer2_ = 60;', 'attack_timer2_ = Config::kPlayerSpecialInterval;')
content = content.replace('xp_needed_ = 5;', 'xp_needed_ = Config::kPlayerXpNeeded;')
content = content.replace('speed_ = 5.0f;', 'speed_ = Config::kPlayerSpeed;')

with open('Source/Player.cpp', 'w', encoding='utf-8') as f:
    f.write(content)
