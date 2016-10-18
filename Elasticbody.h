#pragma once
#include "Physicalbody.h"
#include "Vector2D.h"
#include <vector>

class Elasticbody : public Physicalbody
{
public:
    Elasticbody(std::vector<Vector2D *> &controlPoints, long mass = 1);
    ~Elasticbody();

    //衝突判定後の位置移動
    void Integrate() override;

    //現在の移動量分、位置を戻す
    void CancelIntegrate() override;


private:

    std::vector<Vector2D *> &_controlPoints;
};

