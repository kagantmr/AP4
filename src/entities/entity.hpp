#ifndef ENTITY_GENERIC_H
#define ENTITY_GENERIC_H

#include <raylib.h>

// Base class for every in-game object. Holds the common spatial state and
// exposes a virtual update so derived entities can define their own behaviour.
class Entity {
public:
    Vector2 position{0, 0};
    Vector2 velocity{0, 0};
    Vector2 size{0, 0};
    bool active{false};

    Entity() = default;
    Entity(Vector2 position, Vector2 size)
        : position(position), size(size) {}
    virtual ~Entity() = default;

    virtual void update(float dt) { (void)dt; }

    Rectangle bounds() const {
        return Rectangle{position.x, position.y, size.x, size.y};
    }
};

#endif // ENTITY_GENERIC_H
