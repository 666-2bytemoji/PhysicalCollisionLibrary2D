#pragma once
#include "DxLib.h"
#include "SpaceCell.h"
#include "Collider.h"

class SpaceCell;
class Collider;

//�I�u�W�F�N�g�̃c���[�o�^��S��
class SpaceTreeAgent
{
public:
    SpaceTreeAgent(Collider* shape, int id);
    virtual ~SpaceTreeAgent();

    bool RemoveFromLink();


    //���g�̓o�^���
    SpaceCell *cell;

    //���g�̓��蔻��
    Collider *obj;

    //�Փ˃��X�g�́A�O��̃I�u�W�F�N�g�����i�q�ւ̑o���������N
    SpaceTreeAgent *next, *prev;

    //���^�l���؂̃C���f�b�N�X
    int index;



    void Debug();
};