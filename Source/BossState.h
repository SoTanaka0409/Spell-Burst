// BossState.h
// State Pattern for Boss behavior.
// Each concrete state handles its own attack timing and movement logic,
// making it easy to add new boss types without modifying Boss.cpp.
#pragma once

class Boss;

// Abstract base class for all Boss states
class BossState
{
public:
    virtual ~BossState() = default;

    // Called every frame when this state is active
    virtual void Update(Boss* boss) = 0;

    // Returns true if this state should transition to another state
    virtual bool ShouldTransition(Boss* boss) const { return false; }

    // Returns the next state (called when ShouldTransition returns true).
    // Caller takes ownership of the returned pointer.
    virtual BossState* GetNextState(Boss* boss) const { return nullptr; }
};
