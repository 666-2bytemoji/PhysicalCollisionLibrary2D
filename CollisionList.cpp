#include "CollisionList.h"

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

void CollList::Write(Collider *obj1, Collider *obj2)
{
    /*
    if ((typeid(*(obj1->_shape)) == typeid(Triangle))
        && ((typeid(*(obj2->_shape)) == typeid(Triangle))))
        return;

    if ((typeid(*(obj1->_shape)) == typeid(Circle))
        && ((typeid(*(obj2->_shape)) == typeid(Circle))))
        return;
    */

    colVec.push_back(std::move(std::make_pair(obj1, obj2)));
    index++;
}

void CollList::Sort()
{
    using namespace std;

    sort(colVec.begin(), colVec.end(),
        [](const pair<Collider *, Collider *> &lPair,
        const pair<Collider *, Collider *> &rPair)
    {
        return (lPair.second->_shape->GetCenter()._y > rPair.second->_shape->GetCenter()._y);
    });
}

void CollList::Debug()
{
}