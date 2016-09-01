#include "CollisionManager.h"
#include "Solver.h"


CollisionManager::CollisionManager()
    : _spaceTree(-3000, -3000, 3000, 3000, 4)
{
    _treeAgents.reserve(1024);
}


CollisionManager::~CollisionManager()
{
    for (auto oft : _treeAgents)
    {
        delete oft;
        oft = nullptr;
    }

    _treeAgents.clear();
}


void CollisionManager::SetObjectToTree(Collider *collider)
{
    if (collider->_shape == nullptr)
        return;

    _treeAgents.push_back(new SpaceTreeAgent(collider, _treeAgents.size()));
    _colliders.push_back(collider);
    _shapes.push_back(collider->_shape);
}


void CollisionManager::UpdateTree()
{
    for (auto agent : _treeAgents)
    {
        //一旦リストから外して
        agent->RemoveFromLink();
        //再登録する
        _spaceTree.RegistColliderShape(agent);

        agent->obj->_shape->_isCrossed = false;
    }
}


void CollisionManager::TestAllCollision()
{
    //分割した空間を回り衝突リストを作成
    _spaceTree.SetColList();

    //衝突リスト中のペアが本当に衝突するかチェック
    for (auto col : _spaceTree._allCollision.colVec)
    {
        auto colA = col.first->_shape;
        auto colB = col.second->_shape;
        auto bodyA = col.first->_physicalbody;
        auto bodyB = col.second->_physicalbody;

        //仮移動
        bodyA->Integrate();
        bodyB->Integrate();

        //衝突判定
        bool result = CollisionDetection(colA, colB);
        colA->_isCrossed = (result || colA->_isCrossed);
        colB->_isCrossed = (result || colB->_isCrossed);

        //当たっていたら、それぞれ相手と当たった時の処理をする
        //objA->CollisionWith(*objB);
        //objB->CollisionWith(*objA);

        if (!result)
        {
            bodyA->CancelIntegrate();
            bodyB->CancelIntegrate();
            continue;
        }

        //衝突応答オブジェクト作成
        Solver solver(col.first, col.second);

        //仮移動を取り消して
        bodyA->CancelIntegrate();
        bodyB->CancelIntegrate();

        //衝突応答処理
        solver.Solve();
        continue;
    }

    /*
    //衝突リスト中のペアが本当に衝突するかチェック
    auto colA = _colliders[0]->_shape;
    auto colB = _colliders[1]->_shape;
    auto bodyA = _colliders[0]->_physicalbody;
    auto bodyB = _colliders[1]->_physicalbody;

    //仮移動
    bodyA->Integrate();
    bodyB->Integrate();

    //衝突判定
    bool result = CollisionDetection(colA, colB);
    colA->_isCrossed = (result || colA->_isCrossed);
    colB->_isCrossed = (result || colB->_isCrossed);

    //当たっていたら、それぞれ相手と当たった時の処理をする
    //objA->CollisionWith(*objB);
    //objB->CollisionWith(*objA);

    if (!result)
    {
        bodyA->CancelIntegrate();
        bodyB->CancelIntegrate();
        return;
    }

    //衝突応答オブジェクト作成
    Solver solver(_colliders[1], _colliders[0]);

    //仮移動を取り消して
    bodyA->CancelIntegrate();
    bodyB->CancelIntegrate();

    //衝突応答処理
    solver.Solve();
    */
}


bool CollisionManager::CollisionDetection(ColliderShape *colA, ColliderShape *colB)
{
    return colA->CollisionWith(colB);
}


void CollisionManager::Debug()
{
    for (auto shape : _shapes)
    {
        shape->Draw();
        shape->DrawAABB();
    }
    for (auto agent : _treeAgents)
    {
        agent->Debug();
    }
    _spaceTree.Debug();
}