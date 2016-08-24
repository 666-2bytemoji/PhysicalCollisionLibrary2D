#pragma once
#include <vector>
#include "SpaceCell.h"
#include "SpaceTreeAgent.h"
#include "CollisionList.h"

#include "DxLib.h"

//��Ԑ��`�l����
class SpaceLinerTree
{
public:
    SpaceLinerTree(double minX, double minY, double maxX, double maxY, unsigned int level);
    virtual ~SpaceLinerTree();

    bool Init(double minX, double minY, double maxX, double maxY, unsigned int level);

    bool RegistColliderShape(SpaceTreeAgent *ot);

    void CreateNewGrid(unsigned long cellNum);

    //�Փ˃��X�g�쐬
    void SetColList();
    //	void SetColList(CollList *colList);

    //�Փ˃��X�g�ɂǂ�ǂ�ǉ����Ă���
    void AddColList(unsigned long cellNum, std::vector<Collider *> &cols);

    unsigned long GetCollNum() const { return _allCollision.GetPairNum(); }


    // ���W�����Ԕԍ����Z�o
    unsigned long GetMortonNumber(double left, double top, double right, double bottom);

    // �r�b�g�����֐�
    unsigned long BitSeparate32(unsigned long n)
    {
        n = (n | (n << 8)) & 0x00ff00ff;
        n = (n | (n << 4)) & 0x0f0f0f0f;
        n = (n | (n << 2)) & 0x33333333;
        return (n | (n << 1)) & 0x55555555;
    }

    // 2D���[�g����Ԕԍ��Z�o�֐�
    unsigned short Get2DMortonNumber(unsigned short x, unsigned short y)
    {
        return (unsigned short)(BitSeparate32(x) | (BitSeparate32(y) << 1));
    }

    // ���W�����`4���ؗv�f�ԍ��ϊ��֐�
    unsigned long GetPointElem(double posX, double posY)
    {
        return Get2DMortonNumber(
            static_cast<unsigned short>((posX - _minX) / _uWidth),
            static_cast<unsigned short>((posY - _minY) / _uHeight)
            );
    }

    //�Փ˃��X�g�̎���
    CollList _allCollision;

    void Debug()
    {
        //		DrawFormatString(0, 300, GetColor(0xff, 0x00, 0x00), "coll:%d", allCollision.colVec.size());
        //		DrawFormatString(0, 300, GetColor(0xff, 0x00, 0x00), "coll:%d", allCollision.colVec.size());
        _allCollision.Debug();
    };

private:
    //��Ԃ̃T�C�Y
    double _width, _height;
    double _minX, _minY;

    //�ŏ��P�ʂ̕�
    double _uWidth, _uHeight;
    //�ŉ����x��
    unsigned int _maxLevel;
    //�i�q�̐�
    unsigned long _allGridNum;

    //�i�q�̐��`�|�C���^�z��
    std::vector<SpaceCell *> _cellArray;
};