#pragma once
#include "SpaceTreeAgent.h"

//�O���b�h(�i�q)�N���X
//�e�m�[�h�������A�m�[�h���H�郋�[�g���Ǘ�����

class SpaceTreeAgent;

class SpaceCell
{
public:
    bool Push(SpaceTreeAgent* ot, int key);
    void Pop(SpaceTreeAgent* ot);
    void ResetLink(SpaceTreeAgent* ot);

    SpaceCell();
    virtual ~SpaceCell();


    //��Ԃ��e�m�[�h��ێ�����
    SpaceTreeAgent *parantNode;
    SpaceTreeAgent *GetParentNode();

    //���[�g���ԍ�
    int mKey;
};