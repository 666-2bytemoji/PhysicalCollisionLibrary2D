#pragma once
#include "Physicalbody.h"
#include "Vector2D.h"

class Rigidbody : public  Physicalbody
{
public:
    Rigidbody(Vector2D &center, long mass = 1);
    ~Rigidbody();

    //衝突判定後の位置移動
    void Integrate() override;

    //現在の移動量分、位置を戻す
    void CancelIntegrate() override;

private:

    Vector2D &_center;
};

