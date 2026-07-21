#include "blob.hpp"
#include "consts.hpp"

Blob::Blob(Vector2 spawn_pos) 
    : Enemy(spawn_pos, {40.0f, 30.0f}, 50.0f) // Or pass parameters up if Enemy has a constructor
{
    this->position = spawn_pos;
    this->size = (Vector2){40.0f, 30.0f};
    this->hp = 50.0f;
}

void Blob::update(const InputSnapshot &input, float dt) {
    (void)input; // Enemies don't use player input

    if (is_dead || !active) return;

    // 1. Apply gravity (adjust 900.0f to match your player's gravity feel)
    velocity.y += GRAVITY * dt;

    // 2. Simple horizontal pacing movement (e.g., moving left or right)
    // You can use velocity.x to drive its speed
    velocity.x = 50.0f; // Positive for right, negative for left

    // 3. Move position based on velocity
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // TODO: Add your platform collision resolution here 
    // so the blob stops falling when it hits a floor block!
}

void Blob::take_damage(float amount)  {
    
}
void Blob::draw() const {

}