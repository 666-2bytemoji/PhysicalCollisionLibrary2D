#pragma once
#include "ColliderShape.h"
#include "Physicalbody.h"
#include "Elasticbody.h"
#include "Rigidbody.h"

/*
    ColliderShape��Physicalbody�̋��n��������
*/

class Collider
{
public:
    Collider(ColliderShape *shape, Physicalbody *rigidbody);
    ~Collider();

    void SetShape(ColliderShape *shape);

    ColliderShape *_shape;
    Physicalbody *_physicalbody;
};

