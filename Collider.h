#pragma once
#include "ColliderShape.h"
#include "Physicalbody.h"
#include "Elasticbody.h"
#include "Rigidbody.h"

/*
    ColliderShapeとPhysicalbodyの橋渡しをする
*/

class CollidableObject;

class Collider
{
    friend class CollisionManager;
public:
    Collider(ColliderShape *shape, Physicalbody *rigidbody, CollidableObject *obj);
    ~Collider();

    void SetShape(ColliderShape *shape);

    ColliderShape *_shape;
    Physicalbody *_physicalbody;

private:
    CollidableObject *_obj;
};

