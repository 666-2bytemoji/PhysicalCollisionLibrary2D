#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(ColliderShape *shape, Physicalbody *rigidbody)
    : _shape(shape)
    , _physicalbody(rigidbody)
{
    COLLISION_MGR->SetObjectToTree(this);
}


Collider::~Collider()
{
}


void Collider::SetShape(ColliderShape *shape)
{
    _shape = shape;
    COLLISION_MGR->SetObjectToTree(this);
}