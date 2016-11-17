#include "ColliderShape.h"

ColliderShape::ColliderShape(Vector2D *center, Vector2D size)
    : _center(center)
    , _baseSize(size)
    , _scale(1, 1)
    , _isCrossed(false)
    , _isDetectionOnly(false)
    , _collider(nullptr)
{
    //CollisionManager::Regist(obj, this);
}


ColliderShape::~ColliderShape()
{
    //CollisionManager::Remove(this);
}


void ColliderShape::SetScale(Vector2D scale)
{
    _scale = scale; 
}