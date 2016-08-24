#include "CollidableObject.h"


CollidableObject::CollidableObject(Vector2D pos, ColliderShape *shape, Rigidbody *rigidbody)
    : _position(pos)
    , _collider(shape, rigidbody)
{
}


CollidableObject::~CollidableObject()
{
}


void CollidableObject::AddAction(std::function<void()> action)
{
    _actions.push_back(action);
}


void CollidableObject::ResetOnFrame()
{
    _collider._rigidbody->_move = Vector2D::zero;
}


void CollidableObject::Update()
{
    for (auto action : _actions)
    {
        action();
    }
}