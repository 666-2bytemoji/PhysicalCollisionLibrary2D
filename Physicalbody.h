#pragma once
#include "Vector2D.h"

class Physicalbody
{
public:
    Physicalbody();
    virtual ~Physicalbody() = 0;

    //Õ“Ë”»’èŒã‚ÌˆÊ’uˆÚ“®
    virtual void Integrate() = 0;

    //Œ»İ‚ÌˆÚ“®—Ê•ªAˆÊ’u‚ğ–ß‚·
    virtual void CancelIntegrate() = 0;

    Vector2D _move;

private:

};

