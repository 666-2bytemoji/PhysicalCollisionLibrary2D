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
    //nullの登録, 自身の二重登録を防ぐ
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
        //親ノードを更新
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

    //リストから離脱、リンクの次のオブジェクトにすげ替え
    if (parantNode == ot)
        parantNode = parantNode->next;
}

//リンクを辿ってnullptrを設定していく
void SpaceCell::ResetLink(SpaceTreeAgent* ot)
{
    if (ot->next != nullptr){
        ResetLink(ot->next);
    }
    ot = nullptr;
}