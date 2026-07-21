#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define GAME_SCREEN_WIDTH 640
#define GAME_SCREEN_HEIGHT 360

// Physics
#define GRAVITY 2000.0f
#define MAX_FALL_SPEED 800.0f

// Movement
#define PLAYER_WALK_SPEED 260.0f
#define PLAYER_ACCEL 2200.0f
#define PLAYER_DECEL 3200.0f
#define AIR_CONTROL_FACTOR 0.55f
#define STOP_EPSILON 5.0f


// Jumping
#define PLAYER_JUMP_FORCE 600.0f
#define COYOTE_TIME 0.1f
#define JUMP_BUFFER_TIME 0.1f
#define VARIABLE_JUMP_HEIGHT 0.5f  // Reduce velocity by this % when jump released early

// Shooting
#define PLAYER_SHOOT_COOLDOWN_MAX 0.25f
#define PLAYER_SHOOT_BUFFER 0.10f

#define MAX_TRAVEL_DIST 1500.0f

#define MAX_PROJS 64
#define PROJ_SPEED 2000