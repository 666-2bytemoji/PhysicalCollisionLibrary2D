#pragma once
#include "Physicalbody.h"
#include "Vector2D.h"
#include <vector>

class Elasticbody : public Physicalbody
{
public:
    Elasticbody(std::vector<Vector2D *> &controlPoints);
    ~Elasticbody();

    //�Փ˔����̈ʒu�ړ�
    void Integrate() override;

    //���݂̈ړ��ʕ��A�ʒu��߂�
    void CancelIntegrate() override;


private:

    std::vector<Vector2D *> &_controlPoints;
};

