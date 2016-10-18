#include "Rigidbody.h"


Rigidbody::Rigidbody(Vector2D &center, long mass)
    : Physicalbody(mass)
    , _center(center)
{
}


Rigidbody::~Rigidbody()
{
}


void Rigidbody::Integrate()
{
    if (IsMovable())
        _center += _move;
}


void Rigidbody::CancelIntegrate()
{
    if (IsMovable())
        _center -= _move;
}