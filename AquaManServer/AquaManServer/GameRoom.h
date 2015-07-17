#pragma once
#include "AquaZone.h"  
#include <string>

class GameRoom :
    public AquaZone
{
public:
    GameRoom();
    ~GameRoom();


    bool GetRoomPrivativity()const  { return m_IsPrivate; }
    std::string GetRoomPassword()const { return m_RoomPassword; }


    void SetRoomPrivacy(bool privacy) { m_IsPrivate = privacy; }
    void SetPrivateRoomPassword(std::string password){ m_RoomPassword = password; }

private:
    bool m_IsPrivate            = false;
    std::string m_RoomPassword  = "0000";


};

