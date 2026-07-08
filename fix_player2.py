with open('Source/Player.cpp', 'r', encoding='utf-8') as f:
    content = f.read()

content = content.replace('if (barrier_) {\n        barrier_->SetDeleteFlag(true);\n        barrier_ = nullptr;\n    }', 'if (auto b = barrier_.lock()) {\n        b->SetDeleteFlag(true);\n        barrier_.reset();\n    }')

content = content.replace('barrier_ = new Barrier(Vector2(this->position_.x, this->position_.y));', 'barrier_ = ObjectManager::GetInstance()->Instantiate<Barrier>(Vector2(this->position_.x, this->position_.y));')

content = content.replace('if (barrier_ != nullptr) {\n                barrier_count_ = barrier_->GetHitCount();\n            }', 'if (auto b = barrier_.lock()) {\n                barrier_count_ = b->GetHitCount();\n            }')

content = content.replace('if (barrier_) {\n        barrier_->SetPosition(this->position_);\n    }', 'if (auto b = barrier_.lock()) {\n        b->SetPosition(this->position_);\n    }')

content = content.replace('if (barrier_ != nullptr && barrier_->IsDeployed() && barrier_->GetHitCount() > 0) {\n        int hitCount = barrier_->GetHitCount();', 'if (auto b = barrier_.lock()) {\n        if (b->IsDeployed() && b->GetHitCount() > 0) {\n            int hitCount = b->GetHitCount();')

content = content.replace('spell_gauge_ += hitCount * 2;\n    }', 'spell_gauge_ += hitCount * 2;\n        }\n    }')

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
