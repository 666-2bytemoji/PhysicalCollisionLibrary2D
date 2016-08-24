#include "Rigidbody.h"


Rigidbody::Rigidbody(Vector2D &center)
    : _center(center)
{
}


Rigidbody::~Rigidbody()
{
}


//衝突判定後の位置移動
void Rigidbody::Integrate()
{
    _center += _move;
}


//現在の移動量分、位置を戻す
void Rigidbody::CancelIntegrate()
{
    _center -= _move;
}