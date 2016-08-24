#include "Rigidbody.h"


Rigidbody::Rigidbody(Vector2D &center)
    : _center(center)
{
}


Rigidbody::~Rigidbody()
{
}


//Õ“Ë”»’èŒã‚ÌˆÊ’uˆÚ“®
void Rigidbody::Integrate()
{
    _center += _move;
}


//Œ»İ‚ÌˆÚ“®—Ê•ªAˆÊ’u‚ğ–ß‚·
void Rigidbody::CancelIntegrate()
{
    _center -= _move;
}