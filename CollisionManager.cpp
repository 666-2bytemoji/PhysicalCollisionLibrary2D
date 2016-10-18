#include "CollisionManager.h"
#include "CollidableObject.h"
#include "Solver.h"


CollisionManager::CollisionManager()
    : _spaceTree(-1500, -1500, 1500, 1500, 8)
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


void CollisionManager::SetObjectToTree(Collider *collider)
{
    if (collider->_shape == nullptr)
        return;

    _treeAgents.Add(new SpaceTreeAgent(collider, _treeAgents._objects.size()));
    _colliders.Add(collider);
}


void CollisionManager::RemoveObject(Collider *collider)
{
    if (collider->_shape == nullptr)
        return;
    
    for(size_t i=0; i< _treeAgents._objects.size(); ++i)
    {
        if (_treeAgents._objects[i]->obj->_shape == collider->_shape)
        {
            _treeAgents.Remove(_treeAgents._objects[i]);
            _treeAgents._objects[i]->RemoveFromLink();
        }
    }
    
    _colliders.Remove(collider);
}


void CollisionManager::UpdateTree()
{
    _colliders.Update();
    _treeAgents.Update();
    
    for (auto agent : _treeAgents._objects)
    {
        //空間分割木の接続を一旦解除して
        agent->RemoveFromLink();
        //再構築
        _spaceTree.RegistColliderShape(agent);

        agent->obj->_shape->_isCrossed = false;
    }
}


void CollisionManager::TestAllCollision()
{
    //空間分割木を構築
    _spaceTree.SetColList();

    //空間分割で衝突してるかも、と判断されたペアだけ判定
    for (auto col : _spaceTree._allCollision.colVec)
    {
        auto objA = col.first->_obj;
        auto objB = col.second->_obj;

        //衝突しないタイプどうしだったら判定しない
        if (!CollidableObject::IsCollidable(objA->GetType(), objB->GetType()))
            continue;
            
        auto colA = col.first->_shape;
        auto colB = col.second->_shape;
        auto bodyA = col.first->_physicalbody;
        auto bodyB = col.second->_physicalbody;

        //仮どうして
        bodyA->Integrate();
        bodyB->Integrate();

        //衝突判定
        bool result = CollisionDetection(colA, colB);
        colA->_isCrossed = (result || colA->_isCrossed);
        colB->_isCrossed = (result || colB->_isCrossed);

        //当たってなければ仮移動をキャンセルして終了
        if (!result)
        {
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        //衝突判定のみ行う設定なら、接触時のイベントを発生させて終了
        if (colA->_isDetectionOnly || colB->_isDetectionOnly)
        {
            objA->ContactWith(*objB);
            objB->ContactWith(*objA);
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        //境界ボリュームの交差を解消する設定をする
        Solver solver(col.first, col.second);

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
    for (auto collider : _colliders._objects)
    {
        collider->_shape->Draw();
        collider->_shape->DrawAABB();
    }
    for (auto agent : _treeAgents._objects)
    {
        agent->Debug();
    }
    _spaceTree.Debug();
}