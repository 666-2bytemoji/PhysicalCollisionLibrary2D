#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(ColliderShape *shape, Rigidbody *rigidbody)
    : _shape(shape)
    , _rigidbody(rigidbody)
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