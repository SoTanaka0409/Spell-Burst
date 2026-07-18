// InputAction.cpp
#include "InputAction.h"
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "DxLib.h"

std::unordered_map<int, int> InputBinding::bindings_;

void InputBinding::Initialize()
{
    bindings_[static_cast<int>(InputAction::kMoveUp)]     = KEY_INPUT_W;
    bindings_[static_cast<int>(InputAction::kMoveDown)]   = KEY_INPUT_S;
    bindings_[static_cast<int>(InputAction::kMoveLeft)]   = KEY_INPUT_A;
    bindings_[static_cast<int>(InputAction::kMoveRight)]  = KEY_INPUT_D;
    bindings_[static_cast<int>(InputAction::kFocus)]      = KEY_INPUT_LSHIFT;
    bindings_[static_cast<int>(InputAction::kAttack)]     = KEY_INPUT_Z;
    bindings_[static_cast<int>(InputAction::kSwitchMode)] = KEY_INPUT_Q;
    bindings_[static_cast<int>(InputAction::kPause)]      = KEY_INPUT_ESCAPE;
    bindings_[static_cast<int>(InputAction::kConfirm)]    = KEY_INPUT_RETURN;
    bindings_[static_cast<int>(InputAction::kCancel)]     = KEY_INPUT_X;
}

int InputBinding::GetKey(InputAction action)
{
    auto it = bindings_.find(static_cast<int>(action));
    if (it != bindings_.end())
    {
        return it->second;
    }
    return -1;
}

void InputBinding::Rebind(InputAction action, int keyCode)
{
    bindings_[static_cast<int>(action)] = keyCode;
}
