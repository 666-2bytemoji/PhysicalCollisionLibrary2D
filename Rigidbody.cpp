#include "Rigidbody.h"


Rigidbody::Rigidbody(Vector2D &center)
    : _center(center)
{
}


Rigidbody::~Rigidbody()
{
}


//�Փ˔����̈ʒu�ړ�
void Rigidbody::Integrate()
{
    _center += _move;
}


//���݂̈ړ��ʕ��A�ʒu��߂�
void Rigidbody::CancelIntegrate()
{
    _center -= _move;
}