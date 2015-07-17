#pragma once
#include "../PacketType.h"

class RegionChannel
{
public:
    RegionChannel();
    ~RegionChannel();

    void SetRegionType(RegionType regionType){ m_RegionType = regionType; }
    RegionType GetRegionType()const { return m_RegionType; }


private:
    RegionType m_RegionType = REGION_DEFAULT;
};

