#include "CollisionManager.h"
#include "CollidableObject.h"
#include "Solver.h"

CollisionManager::CollisionManager()
    : _spaceTree(-1500, -1500, 1500, 1500, 8)
    , _detectionCount(0)
{
    _treeAgents._objects.reserve(1024);
}


CollisionManager::~CollisionManager()
{
    Clear();
}


void CollisionManager::Clear()
{
    for (auto oft : _treeAgents._objects)
    {
        oft->RemoveFromLink();
        delete oft;
        oft = nullptr;
    }

    _treeAgents.Clear();
    _colliders.Clear();
}


void CollisionManager::SetObjectToTree(ColliderShape *shape)
{
    if (shape == nullptr)
        return;

    _treeAgents.Add(new SpaceTreeAgent(shape, _treeAgents._objects.size()));
    _colliders.Add(shape);
}


void CollisionManager::RemoveObject(ColliderShape *shape)
{
    if (shape == nullptr)
        return;
    
    for(size_t i=0; i< _treeAgents._objects.size(); ++i)
    {
        //Remove依頼のあったものと一致していたら削除
        if (_treeAgents._objects[i]->_shape == shape)
        {
            _treeAgents.Remove(_treeAgents._objects[i]);
            _treeAgents._objects[i]->RemoveFromLink();
        }
    }
    
    _colliders.Remove(shape);
}


void CollisionManager::UpdateTree()
{
    _detectionCount = 0;
    _colliders.Update();
    _treeAgents.Update();
    
    for (auto agent : _treeAgents._objects)
    {
        //空間分割木の接続を一旦解除して
        agent->RemoveFromLink();
        //再構築
        _spaceTree.RegistColliderShape(agent);

        agent->_shape->_isCrossed = false;
    }
}


void CollisionManager::TestAllCollision()
{
    //空間分割木を構築
    _spaceTree.SetColList();

    //空間分割で衝突してるかも、と判断されたペアだけ判定
    for (auto col : _spaceTree._allCollision.colVec)
    {
        auto shapeA = col.first;
        auto shapeB = col.second;
        auto colA = shapeA->_collider;
        auto colB = shapeB->_collider;
        auto objA = colA->_obj;
        auto objB = colB->_obj;
        auto bodyA = colA->_physicalbody;
        auto bodyB = colB->_physicalbody;

        //仮移動して
        bodyA->Integrate();
        bodyB->Integrate();

        //衝突判定
        bool result = CollisionDetection(shapeA, shapeB);
        shapeA->_isCrossed = (result || shapeA->_isCrossed);
        shapeB->_isCrossed = (result || shapeB->_isCrossed);

        //当たってなければ仮移動をキャンセルして終了
        if (!result)
        {
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        _detectionCount++;

        //衝突判定のみ行う設定なら、接触時のイベントを発生させて終了
        if (shapeA->_isDetectionOnly || shapeB->_isDetectionOnly)
        {
            objA->ContactWith(*objB);
            objB->ContactWith(*objA);
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        //境界ボリュームの交差を解消する設定をする
        Solver solver(shapeA, shapeB, bodyA, bodyB);

        //衝突のイベントを発生させる
        objA->CollisionWith(*objB, solver);
        objB->CollisionWith(*objA, solver);

        //仮移動をキャンセルする
        bodyA->CancelIntegrate();
        bodyB->CancelIntegrate();

        //交差した分を解消するように移動量をさらに加える
        solver.Solve();
        continue;
    }
}


bool CollisionManager::CollisionDetection(ColliderShape *colA, ColliderShape *colB)
{
    return colA->CollisionWith(colB);
}


void CollisionManager::Debug()
{
    for (auto shape : _colliders._objects)
    {
        shape->Draw();
        shape->DrawAABB();
    }
    for (auto agent : _treeAgents._objects)
    {
        agent->Debug();
    }
    _spaceTree.Debug();

    //fk_Window::printf("count : %d", _detectionCount);
}