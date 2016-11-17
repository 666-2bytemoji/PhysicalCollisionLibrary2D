#include "CollisionList.h"
#include "CollidableObject.h"

CollList::CollList()
: index(0)
, collCapacity(1000)
{
    colVec.reserve(1000);
}

CollList::~CollList()
{
    Init();
}

void CollList::Init()
{
    colVec.clear();
    colVec.resize(0);
    index = 0;
}

void CollList::Reflesh()
{
}

void CollList::ResetPos()
{
    index = 0;
}

void CollList::Write(ColliderShape *shape1, ColliderShape *shape2)
{
    auto objA = shape1->GetColliderPtr()->_obj;
    auto objB = shape2->GetColliderPtr()->_obj;
    
     //自分の衝突判定オブジェクトと判定しそうになっていたら終了
     if (shape1->GetColliderPtr() == shape2->GetColliderPtr())
         return;
    
    //衝突しないタイプどうしだったら判定しない
    if (!CollidableObject::IsCollidablePair(objA->GetType(), objB->GetType()))
        return;
    
    //ユーザー定義の条件で衝突しない設定なら判定しない
    if (!objA->IsCollidable(*objB)
        || !objB->IsCollidable(*objA))
        return;
    
    
    colVec.push_back(std::move(std::make_pair(shape1, shape2)));
    index++;
}

void CollList::Sort()
{
    using namespace std;
    
    sort(colVec.begin(), colVec.end(),
         [](const pair<ColliderShape *, ColliderShape *> &lPair,
            const pair<ColliderShape *, ColliderShape *> &rPair)
         {
             return (lPair.second->GetCenter()._y > rPair.second->GetCenter()._y);
         });
}

void CollList::Debug()
{
    
}