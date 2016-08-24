#pragma once
#include "ColliderShape.h"
#include "Rigidbody.h"

/*
    ColliderShape‚ÆRigidbody‚Ì‹´“n‚µ‚ð‚·‚é
*/

class Collider
{
public:
    Collider(ColliderShape *shape, Rigidbody *rigidbody);
    ~Collider();

    void SetShape(ColliderShape *shape);

    ColliderShape *_shape;
    Rigidbody *_rigidbody;
};

