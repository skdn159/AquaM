#pragma once
#include "RegionChannel.h"
class AquaZone :
    public RegionChannel
{
public:
    AquaZone();
    ~AquaZone();

    void SetAquaZoneType(AquaZoneType azoneType){ m_AquaZoneType = azoneType;  }
    AquaZoneType GetAquaZoneTYpe()const { return m_AquaZoneType; }

private: 
    AquaZoneType m_AquaZoneType = AZONE_DEFAULT;
};

