#pragma once

// Frame-local snapshot of player intent, decoupled from the raw device. Move*
// fields are held states; the *Pressed/*Released fields are single-frame edges.
struct InputSnapshot {
    bool MoveRight;
    bool MoveLeft;
    bool MoveUp;
    bool MoveDown;
    bool ShootPressed;
    bool JumpPressed;
    bool JumpReleased;
    bool DashPressed;
    bool SpellPressed;
};

// Samples the current keyboard state into a snapshot for this frame.
InputSnapshot poll_input();
