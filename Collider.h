#pragma once
#include "ColliderShape.h"
#include "Rigidbody.h"

/*
    ColliderShape��Rigidbody�̋��n��������
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

