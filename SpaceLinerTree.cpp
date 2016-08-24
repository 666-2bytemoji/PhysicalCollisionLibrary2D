#include "SpaceLinerTree.h"

SpaceLinerTree::SpaceLinerTree(double minX, double minY, double maxX, double maxY, unsigned int level)
{
    if (   (0 < maxX - minX)
        || (0 < maxY - minY) )
    {
        Init(minX, minY, maxX, maxY, level);
        return;
    }

    //空間のサイズ
    _width = 0.0;
    _height = 0.0;

    _minX = 0.0;
    _minY = 0.0;

    //最小単位の幅
    _uWidth = 0.0;
    _uHeight = 0.0;
    //最下レベル
    _maxLevel = 0;
    //格子の数
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

    //最小単位の幅は 空間サイズ / グリッドレベル^2
    _uWidth = _width / (1 << level);
    _uHeight = _height / (1 << level);
    //最下レベル
    _maxLevel = level;

    //格子の数 = (4^(階層数+1) -1) /3 ←(4の倍数-1)/3  
    _allGridNum = static_cast<unsigned long>((std::pow(4, level + 1) - 1) / 3);
    _cellArray.resize(_allGridNum, nullptr);

    return true;
}

void SpaceLinerTree::CreateNewGrid(unsigned long cellNum)
{
    while (!_cellArray[cellNum])
    {
        _cellArray[cellNum] = new SpaceCell();

        //親空間も一緒に作ってしまう
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

    //ルート空間が無ければ空間がまだ存在していないので終了
    if (_cellArray[0] == nullptr)
        return;

    //衝突リストを作成してスタート
    std::vector<Collider *>colStack;
    colStack.reserve(128);
    //親空間からつくる
    AddColList(0, std::move(colStack));
    _allCollision.Sort();
}

//衝突リストにどんどん追加していく
void SpaceLinerTree::AddColList(unsigned long cellNum, std::vector<Collider *> &cols)
{

    //1.自分の空間内のオブジェクト同市の衝突リストを作る

    //グリッドに登録されている最上レベルのオブジェクトからスタート
    SpaceTreeAgent* otParent = _cellArray[cellNum]->parantNode;
    while (otParent != nullptr)
    {
        //親ノードに登録されたリストを辿っていく
        SpaceTreeAgent* otChild = otParent->next;

        //リストの端に着いたら抜ける
        while (otChild != nullptr)
        {
            //メモリを確保
            _allCollision.Write(otParent->obj, otChild->obj);
            //さらにリストの次を辿る
            otChild = otChild->next;
        }

        //2.衝突スタックとの衝突リスト作成
        for (auto sub_obj : cols)
            _allCollision.Write(otParent->obj, sub_obj);

        //次の親ノードへ
        otParent = otParent->next;
    }

    //3.子空間の処理へ
    bool ChildFlag = false;
    unsigned long stackedNum = 0;

    //それぞれの子空間について
    for (int i = 0; i < 4; ++i)
    {
        //次の要素番号は 前レベルの最後尾(階層*4 + 1) + 今のレベル番号
        unsigned long nextElem = cellNum * 4 + 1 + i;

        if (nextElem < _allGridNum
            && _cellArray[nextElem] != nullptr)
        {
            //まだ子空間が未巡回なら
            if (!ChildFlag)
            {
                //4.登録されたオブジェクトをスタックに積む
                otParent = _cellArray[cellNum]->parantNode;
                while (otParent != nullptr)
                {
                    cols.push_back(otParent->obj);
                    otParent = otParent->next;
                    stackedNum++;
                }
            }

            //巡回フラグON            ChildFlag = true;
            AddColList(nextElem, cols);
        }
    }

    //5. スタックからオブジェクトを外す
    if (ChildFlag)
    {
        for (unsigned long i = 0; i < stackedNum; i++)
            cols.pop_back();
    }
}



// 座標から空間番号を算出
unsigned long SpaceLinerTree::GetMortonNumber(double left, double top, double right, double bottom)
{
    // 最小レベルにおける各軸位置を算出
    unsigned long LT = GetPointElem(left, top);
    unsigned long RB = GetPointElem(right, bottom);

    // 空間番号の排他的論理和から
    // 所属レベルを算出
    unsigned long Def = RB ^ LT;
    unsigned int HiLevel = 0;

    for (unsigned int i = 0; i < _maxLevel; i++)
    {
        unsigned long Check = (Def >> (i * 2)) & 0x3;
        if (Check != 0)
            HiLevel = i + 1;
    }

    //右下の所属番号
    unsigned long spaceNum = RB >> (HiLevel * 2);
    unsigned long addNum = static_cast<unsigned long>(
        (std::pow(4, _maxLevel - HiLevel) - 1) / 3);
    spaceNum += addNum;

    //グリッド数より大きくなったら例外なので終了
    if (_allGridNum < spaceNum)
        return 0xffffffff;

    //グリッド番号
    return spaceNum;
}