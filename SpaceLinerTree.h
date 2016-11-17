#pragma once
#include <vector>
#include "SpaceCell.h"
#include "SpaceTreeAgent.h"
#include "CollisionList.h"

//空間線形四分木
class SpaceLinerTree
{
public:
    SpaceLinerTree(double minX, double minY, double maxX, double maxY, unsigned int level);
    virtual ~SpaceLinerTree();

    bool Init(double minX, double minY, double maxX, double maxY, unsigned int level);

    bool RegistColliderShape(SpaceTreeAgent *ot);

    void CreateNewGrid(unsigned long cellNum);

    //衝突リスト作成
    void SetColList();
    //	void SetColList(CollList *colList);

    //衝突リストにどんどん追加していく
    void AddColList(unsigned long cellNum, std::vector<ColliderShape *> &cols);

    unsigned long GetCollNum() const { return _allCollision.GetPairNum(); }


    // 座標から空間番号を算出
    unsigned long GetMortonNumber(double left, double top, double right, double bottom);

    // ビット分割関数
    unsigned long BitSeparate32(unsigned long n)
    {
        n = (n | (n << 8)) & 0x00ff00ff;
        n = (n | (n << 4)) & 0x0f0f0f0f;
        n = (n | (n << 2)) & 0x33333333;
        return (n | (n << 1)) & 0x55555555;
    }

    // 2Dモートン空間番号算出関数
    unsigned short Get2DMortonNumber(unsigned short x, unsigned short y)
    {
        return (unsigned short)(BitSeparate32(x) | (BitSeparate32(y) << 1));
    }

    // 座標→線形4分木要素番号変換関数
    unsigned long GetPointElem(double posX, double posY)
    {
        return Get2DMortonNumber(
            static_cast<unsigned short>((posX - _minX) / _uWidth),
            static_cast<unsigned short>((posY - _minY) / _uHeight)
            );
    }

    //衝突リストの実体
    CollList _allCollision;

    void Debug()
    {
         _allCollision.Debug();
    };

private:
    //空間のサイズ
    double _width, _height;
    double _minX, _minY;

    //最小単位の幅
    double _uWidth, _uHeight;
    //最下レベル
    unsigned int _maxLevel;
    //格子の数
    unsigned long _allGridNum;

    //格子の線形ポインタ配列
    std::vector<SpaceCell *> _cellArray;
};