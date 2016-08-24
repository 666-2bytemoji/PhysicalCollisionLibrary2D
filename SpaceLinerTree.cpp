#include "SpaceLinerTree.h"

SpaceLinerTree::SpaceLinerTree(double minX, double minY, double maxX, double maxY, unsigned int level)
{
    if (   (0 < maxX - minX)
        || (0 < maxY - minY) )
    {
        Init(minX, minY, maxX, maxY, level);
        return;
    }

    //��Ԃ̃T�C�Y
    _width = 0.0;
    _height = 0.0;

    _minX = 0.0;
    _minY = 0.0;

    //�ŏ��P�ʂ̕�
    _uWidth = 0.0;
    _uHeight = 0.0;
    //�ŉ����x��
    _maxLevel = 0;
    //�i�q�̐�
    _allGridNum = 0;
}

SpaceLinerTree::~SpaceLinerTree()
{

}

bool SpaceLinerTree::Init(double minX, double minY, double maxX, double maxY, unsigned int level)
{
    _minX = minX;
    _minY = minY;

    _width = maxX - minX;
    _height = maxY - minY;

    //�ŏ��P�ʂ̕��� ��ԃT�C�Y / �O���b�h���x��^2
    _uWidth = _width / (1 << level);
    _uHeight = _height / (1 << level);
    //�ŉ����x��
    _maxLevel = level;

    //�i�q�̐� = (4^(�K�w��+1) -1) /3 ��(4�̔{��-1)/3  
    _allGridNum = static_cast<unsigned long>((std::pow(4, level + 1) - 1) / 3);
    _cellArray.resize(_allGridNum, nullptr);

    return true;
}

void SpaceLinerTree::CreateNewGrid(unsigned long cellNum)
{
    while (!_cellArray[cellNum])
    {
        _cellArray[cellNum] = new SpaceCell();

        //�e��Ԃ��ꏏ�ɍ���Ă��܂�
        cellNum = (cellNum - 1) >> 2;
        if (_allGridNum <= cellNum)
            break;
    }
}

bool SpaceLinerTree::RegistColliderShape(SpaceTreeAgent *ot)
{
    auto shape = ot->obj->_shape;
    unsigned long cellNum = GetMortonNumber(
        shape->GetMinX(),
        shape->GetMinY(),
        shape->GetMaxX(),
        shape->GetMaxY());

    if (cellNum < _allGridNum){
        if (!_cellArray[cellNum])
            CreateNewGrid(cellNum);

        return _cellArray[cellNum]->Push(ot, cellNum);
    }

    return false;
}

void SpaceLinerTree::SetColList()
{
    _allCollision.Init();

    //���[�g��Ԃ�������΋�Ԃ��܂����݂��Ă��Ȃ��̂ŏI��
    if (_cellArray[0] == nullptr)
        return;

    //�Փ˃��X�g���쐬���ăX�^�[�g
    std::vector<Collider *>colStack;
    colStack.reserve(128);
    //�e��Ԃ������
    AddColList(0, std::move(colStack));
    _allCollision.Sort();
}

//�Փ˃��X�g�ɂǂ�ǂ�ǉ����Ă���
void SpaceLinerTree::AddColList(unsigned long cellNum, std::vector<Collider *> &cols)
{

    //1.�����̋�ԓ��̃I�u�W�F�N�g���s�̏Փ˃��X�g�����

    //�O���b�h�ɓo�^����Ă���ŏヌ�x���̃I�u�W�F�N�g����X�^�[�g
    SpaceTreeAgent* otParent = _cellArray[cellNum]->parantNode;
    while (otParent != nullptr)
    {
        //�e�m�[�h�ɓo�^���ꂽ���X�g��H���Ă���
        SpaceTreeAgent* otChild = otParent->next;

        //���X�g�̒[�ɒ������甲����
        while (otChild != nullptr)
        {
            //���������m��
            _allCollision.Write(otParent->obj, otChild->obj);
            //����Ƀ��X�g�̎���H��
            otChild = otChild->next;
        }

        //2.�Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
        for (auto sub_obj : cols)
            _allCollision.Write(otParent->obj, sub_obj);

        //���̐e�m�[�h��
        otParent = otParent->next;
    }

    //3.�q��Ԃ̏�����
    bool ChildFlag = false;
    unsigned long stackedNum = 0;

    //���ꂼ��̎q��Ԃɂ���
    for (int i = 0; i < 4; ++i)
    {
        //���̗v�f�ԍ��� �O���x���̍Ō��(�K�w*4 + 1) + ���̃��x���ԍ�
        unsigned long nextElem = cellNum * 4 + 1 + i;

        if (nextElem < _allGridNum
            && _cellArray[nextElem] != nullptr)
        {
            //�܂��q��Ԃ�������Ȃ�
            if (!ChildFlag)
            {
                //4.�o�^���ꂽ�I�u�W�F�N�g���X�^�b�N�ɐς�
                otParent = _cellArray[cellNum]->parantNode;
                while (otParent != nullptr)
                {
                    cols.push_back(otParent->obj);
                    otParent = otParent->next;
                    stackedNum++;
                }
            }

            //����t���OON            ChildFlag = true;
            AddColList(nextElem, cols);
        }
    }

    //5. �X�^�b�N����I�u�W�F�N�g���O��
    if (ChildFlag)
    {
        for (unsigned long i = 0; i < stackedNum; i++)
            cols.pop_back();
    }
}



// ���W�����Ԕԍ����Z�o
unsigned long SpaceLinerTree::GetMortonNumber(double left, double top, double right, double bottom)
{
    // �ŏ����x���ɂ�����e���ʒu���Z�o
    unsigned long LT = GetPointElem(left, top);
    unsigned long RB = GetPointElem(right, bottom);

    // ��Ԕԍ��̔r���I�_���a����
    // �������x�����Z�o
    unsigned long Def = RB ^ LT;
    unsigned int HiLevel = 0;

    for (unsigned int i = 0; i < _maxLevel; i++)
    {
        unsigned long Check = (Def >> (i * 2)) & 0x3;
        if (Check != 0)
            HiLevel = i + 1;
    }

    //�E���̏����ԍ�
    unsigned long spaceNum = RB >> (HiLevel * 2);
    unsigned long addNum = static_cast<unsigned long>(
        (std::pow(4, _maxLevel - HiLevel) - 1) / 3);
    spaceNum += addNum;

    //�O���b�h�����傫���Ȃ������O�Ȃ̂ŏI��
    if (_allGridNum < spaceNum)
        return 0xffffffff;

    //�O���b�h�ԍ�
    return spaceNum;
}