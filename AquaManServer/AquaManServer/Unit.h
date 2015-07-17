#pragma once
#include "..\..\PacketType.h"

class Player;

#define UNIT_SCALE 10.0f

class Unit
{
public:
    Unit();
    virtual ~Unit();


public:
    Player*             GetOwner()const { return m_Owner; }
    int                 GetUnitID() const { return m_UnitID;}
    int                 GetUnitMaxHP()const{ return m_MaxHp; }
    int                 GetUnitCurHp()const { return m_Hp; }
    bool                GetUnitSuperPower()const { return m_IsSuperPower; }
    const b2Vec2&       GetUnitCurPos()const { return m_CurPos; }
    UnitType            GetUnitType()const { return m_UnitType; }
    int                 GetUnitPriority()const { return m_Priority; }
    float               GetUnitMass()const { return m_Mass; }



    void                SetUnitType(UnitType unitType) { m_UnitType = unitType; }
    void                SetUnitMaxHP(int maxHp){ m_MaxHp = maxHp; }
    void                SetUnitCurHp(int curHp){ m_Hp = curHp; }
    void                SetUnitSuperPower(bool superPower) { m_IsSuperPower = superPower; }
    void                SetUnitSpeed(float speed){ m_Speed = speed; }
    void                SetUnitPriority(int priority){ m_Priority = priority; }
    void                SetUnitMass(float mass){ m_Mass = mass; }



protected:
    Player*     m_Owner         = nullptr; 
    int         m_UnitID        = -1;
    UnitType    m_UnitType      = UNIT_DEFAULT;
    int         m_MaxHp         = 0;
    int         m_Hp            = 0;
    bool        m_IsSuperPower  = false;
    float       m_Speed         = 0.0f;
    b2Vec2      m_CurPos        = { 0, 0 };
    int         m_Priority      = -1;
    float       m_Mass          = 0;
};

