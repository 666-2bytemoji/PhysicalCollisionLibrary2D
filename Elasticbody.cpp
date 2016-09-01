#include "Elasticbody.h"


Elasticbody::Elasticbody(std::vector<Vector2D *> &controlPoints)
    : _controlPoints(controlPoints)
{
}


Elasticbody::~Elasticbody()
{
}


//�Փ˔����̈ʒu�ړ�
void Elasticbody::Integrate()
{
    for (auto pos : _controlPoints)
        *pos += _move;
}


//���݂̈ړ��ʕ��A�ʒu��߂�
void Elasticbody::CancelIntegrate()
{
    for (auto pos : _controlPoints)
        *pos -= _move;
}