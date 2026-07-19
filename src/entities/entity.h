#ifndef ENTITY_GENERIC_H
#define ENTITY_GENERIC_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    bool active;
} Entity;
 
#endif // ENTITY_GENERIC_H