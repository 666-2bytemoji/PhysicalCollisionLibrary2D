#pragma once
#include "Vector2D.h"

class Rigidbody
{
public:
    Rigidbody(Vector2D &center);
    ~Rigidbody();

    //衝突判定後の位置移動
    void Integrate();

    //現在の移動量分、位置を戻す
    void CancelIntegrate();

    Vector2D _move;

private:

    Vector2D &_center;
};

