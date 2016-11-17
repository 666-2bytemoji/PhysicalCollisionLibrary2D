#pragma once
#include "ColliderShape.h"
#include "Physicalbody.h"
#include "Elasticbody.h"
#include "Rigidbody.h"
#include <vector>

/*
    ColliderShapeとPhysicalbodyの橋渡しをする
*/

class CollidableObject;

class Collider
{
    friend class CollisionManager;
    friend class CollList;
public:
    Collider(ColliderShape *shape, Physicalbody *rigidbody, CollidableObject *obj);
    Collider(CollidableObject *obj);
    ~Collider();

    void SetShape(ColliderShape *shape);
    std::vector<ColliderShape *>* GetShapesPtr() { return &_shapes; }

    Physicalbody *_physicalbody;

private:
    std::vector<ColliderShape *> _shapes;
    CollidableObject *_obj;
};

