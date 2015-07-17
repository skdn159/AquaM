#pragma once
#include "Unit.h"

class Diver : public Unit
{
public :
    Diver();
    ~Diver();

    void PickFish();


private:
    DIverType   m_DiverType;


};

