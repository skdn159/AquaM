#pragma once
#include "Unit.h"

class Fisher : public Unit
{
public:
    Fisher();
    ~Fisher();

    void FisherShipMove();
    void BobberUp();
    void BobberDown();



private:
    FisherType  m_FisherType;
    BobberType  m_BobberType;
    ShipType    m_ShipType;
};

