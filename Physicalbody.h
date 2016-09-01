#pragma once
#include "Vector2D.h"

class Physicalbody
{
public:
    Physicalbody();
    virtual ~Physicalbody() = 0;

    //衝突判定後の位置移動
    virtual void Integrate() = 0;

    //現在の移動量分、位置を戻す
    virtual void CancelIntegrate() = 0;

    Vector2D _move;

private:

};

