// InputAction.h
// Command pattern for input abstraction.
// Maps game actions (Move_Up, Attack, etc.) to key codes,
// allowing key rebinding from a single location.
#pragma once
#include <unordered_map>

// Enum representing in-game actions (intent)
enum class InputAction
{
    kMoveUp,
    kMoveDown,
    kMoveLeft,
    kMoveRight,
    kFocus,         // Slow movement (LShift)
    kAttack,        // Normal attack (Z key / Mouse left)
    kSwitchMode,    // Switch attack mode (Q)
    kPause,         // Pause (Escape)
    kConfirm,       // Confirm (Enter / Z)
    kCancel,        // Cancel (X / Escape)
};

// Manages key bindings: InputAction -> DxLib KeyCode
class InputBinding
{
public:
    // Initialize with default key bindings
    static void Initialize();

    // Get the key code for a given action
    static int GetKey(InputAction action);

    // Rebind an action to a new key code
    static void Rebind(InputAction action, int keyCode);

private:
    static std::unordered_map<int, int> bindings_;
};
