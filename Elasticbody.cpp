#include "Elasticbody.h"


Elasticbody::Elasticbody(std::vector<Vector2D *> &controlPoints, long mass)
    : Physicalbody(mass)
    , _controlPoints(controlPoints)
{
}


Elasticbody::~Elasticbody()
{
}


//衝突判定後の位置移動
void Elasticbody::Integrate()
{
    if (!IsMovable())
        return;

    for (auto pos : _controlPoints)
        *pos += _move;
}


//現在の移動量分、位置を戻す
void Elasticbody::CancelIntegrate()
{
    if (!IsMovable())
        return;

    for (auto pos : _controlPoints)
        *pos -= _move;
}