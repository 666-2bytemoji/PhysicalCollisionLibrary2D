#pragma once
#include "Vector2D.h"

class Rigidbody
{
public:
    Rigidbody(Vector2D &center);
    ~Rigidbody();

    //Õ“Ë”»’èŒã‚ÌˆÊ’uˆÚ“®
    void Integrate();

    //Œ»İ‚ÌˆÚ“®—Ê•ªAˆÊ’u‚ğ–ß‚·
    void CancelIntegrate();

    Vector2D _move;

private:

    Vector2D &_center;
};

