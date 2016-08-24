#include "SpaceCell.h"

SpaceCell::SpaceCell() 
    : parantNode(nullptr)
{
}

SpaceCell::~SpaceCell()
{
    if (parantNode != nullptr)
        ResetLink(parantNode);
}

bool SpaceCell::Push(SpaceTreeAgent* ot, int key)
{
    //null�̓o�^, ���g�̓�d�o�^��h��
    if (ot == nullptr)
        return false;
    if (ot->cell == this)
        return false;

    if (parantNode == nullptr)
    {
        parantNode = ot;
    }
    else
    {
        //�e�m�[�h���X�V
        ot->next = parantNode;
        parantNode->prev = ot;
        parantNode = ot;
    }

    ot->cell = this;
    mKey = key;
    return true;
}

void SpaceCell::Pop(SpaceTreeAgent* ot)
{
    if (ot == nullptr)
        return;

    //���X�g���痣�E�A�����N�̎��̃I�u�W�F�N�g�ɂ����ւ�
    if (parantNode == ot)
        parantNode = parantNode->next;
}

//�����N��H����nullptr��ݒ肵�Ă���
void SpaceCell::ResetLink(SpaceTreeAgent* ot)
{
    if (ot->next != nullptr){
        ResetLink(ot->next);
    }
    ot = nullptr;
}