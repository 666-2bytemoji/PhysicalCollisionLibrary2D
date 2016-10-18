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

    void AddAction(std::function<void()> action);
    virtual void Update();
    virtual void LateUpdate();

    virtual void CollisionWith(CollidableObject& obj, const Solver& solver);
    virtual void ContactWith(CollidableObject &obj);

    
    void SetPosition(Vector2D pos) { _position = pos; }
    void SetMove(Vector2D move) { _collider._physicalbody->_move = move; }

    void Inegrate() { _collider._physicalbody->Integrate(); }
    void ResetOnFrame();

    enum class Type
    {
        DEFAULT,
        PLAYER,
        BLOCK,
        
        TYPE_NUM
    };
    Type _type;
    Type GetType() const { return _type; }
    
    void SetCollidableFlag(Type type, Type opponentType, bool flag);
    static bool IsCollidable(Type type, Type opponentType);

    static void Debug()
    {
        for (auto table : _collidableBitTable)
            std::cout << table <<  " ";

        std::cout << std::endl;
    }
    
protected:

    Vector2D _position;
    Vector2D _direction;
    Collider _collider;

private:

    std::vector<std::function<void()>> _actions;
    static std::vector<int32_t> _collidableBitTable;
};

