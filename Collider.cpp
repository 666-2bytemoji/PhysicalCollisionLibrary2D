#include "Collider.h"
#include "CollisionManager.h"
#include "CollidableObject.h"

Collider::Collider(ColliderShape *shape, Physicalbody *rigidbody, CollidableObject *obj)
    :  _physicalbody(rigidbody)
    , _obj(obj)
{
    if (shape == nullptr)
        return;

    SetShape(shape);
}


Collider::~Collider()
{
    for (size_t i = 0; i < _shapes.size(); ++i)
    {
        COLLISION_MGR->RemoveObject(_shapes[i]);

        if (_shapes[i] != nullptr)
            delete _shapes[i];
        if (_physicalbody != nullptr)
            delete _physicalbody;
    }
}


void Collider::SetShape(ColliderShape *shape)
{
    _shapes.push_back(shape);
    shape->SetCollider(this);
    COLLISION_MGR->SetObjectToTree(shape);
}