#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(ColliderShape *shape, Physicalbody *rigidbody, CollidableObject *obj)
    : _shape(shape)
    , _physicalbody(rigidbody)
    , _obj(obj)
{
    COLLISION_MGR->SetObjectToTree(this);
}


Collider::~Collider()
{
    COLLISION_MGR->RemoveObject(this);
    
    if (_shape != nullptr)
    {
        delete _shape;
        _shape = nullptr;
    }
    if (_physicalbody != nullptr)
    {
        delete _physicalbody;
        _physicalbody = nullptr;
    }
}


void Collider::SetShape(ColliderShape *shape)
{
    _shape = shape;
    COLLISION_MGR->SetObjectToTree(this);
}