#pragma once
#include <functional>
#include <vector>
#include "../Vector2D.h"
#include "Collider.h"
#include <iostream>

class Solver;

class CollidableObject
{
public:
    CollidableObject(Vector2D pos, ColliderShape* shape, Physicalbody *rigidbody);
    virtual ~CollidableObject();

    virtual void Update();
    virtual void LateUpdate();

    virtual void CollisionWith(CollidableObject& obj, const Solver& solver);
    virtual void ContactWith(CollidableObject &obj);

    //派生クラスでユーザーが任意に設定できる衝突条件
    virtual bool IsCollidable(CollidableObject& obj) { return true; };
    
    Vector2D GetPosition() const { return _position; }
    void SetPosition(Vector2D pos) { _position = pos; }
    void SetMove(Vector2D move) { _collider._physicalbody->_move = move; }

    void Inegrate() { _collider._physicalbody->Integrate(); }
    void ResetOnFrame();

    enum class Type
    {
        DEFAULT,
        PLAYER,
        PLAYER_BULLET,
        PLAYER_BULLET_HYPER,
        PLAYER_BULLET_BEAM,
        BLOCK,
        ENEMY,
        ENEMY_BULLET,
        ENEMY_BULLET_BEAM,
        NONE,
        
        TYPE_NUM
    };
    Type _type;
    Type GetType() const { return _type; }
    
    static void SetCollidableFlag(Type type, Type opponentType, bool flag);
    static bool IsCollidablePair(Type type, Type opponentType);

    CollidableObject* GetParent() { return _parent; }
    void SetParent(CollidableObject* obj)
    {
        _parent = obj;
        obj->_children.push_back(this);
    }
    
    void SetChildren(CollidableObject* obj) { _children.push_back(obj); }
    std::vector<CollidableObject *>* GetChildren() { return &_children; }
    
protected:

    CollidableObject* _parent;
    std::vector<CollidableObject *> _children;
    
    Vector2D _position;
    Vector2D _direction;
    Collider _collider;

private:

    static std::vector<int32_t> _collidableBitTable;
};

