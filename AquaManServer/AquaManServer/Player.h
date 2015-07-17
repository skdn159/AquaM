#pragma once
#include "../PacketType.h"
#include "Unit.h"


typedef std::map<int, Unit*> UnitList;

class ClientSession;

class Player
{
public:
    Player(ClientSession* client, int playerId, const std::string& playerName, Sex sex, int attractivePoint, int cleanPoint, int money);
    ~Player();

    ClientSession*      GetClient() const{ return m_Client; }
    int                 GetPlayerID() const { return m_PlayerID; }
    const std::string&  GetPlayerName() const { return m_PlayerName; }
    Sex                 GetPlayerSex() const { return m_Sex; }
    int                 GetPlayerCleanPoint() const{ return m_CleanPoint; }
    int                 GetPlayerAttrPoint()const { return m_AttractivePoint; }
    int                 GetPlayerMoney()const { return m_Money; }
    float               GetPlayerRevivalTime()const { return m_RevivalTime; }
    const UnitList&     GetUnitList(){ return m_UnitList; }
    bool                GetPlayerReady() const { return m_IsReady; }
    int                 GetPlayerRommID() const { return m_RoomID; }

    void                SetPlayerCleanPoint(int cleanPoint){ m_CleanPoint = cleanPoint; }
    void                SetPlayerMoney(int money){ m_Money = money;}
    void                SetPlayerRevivalTime(float time) { m_RevivalTime = time; }
    void                SetPlayerReady(bool ready){ m_IsReady = ready; }
    void                SetPlayerRoomID(int roomId){ m_RoomID = roomId; }



    void                UnitListPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
    void                UnitListPop(int unitID);
    void                UnitListClear();

private:

    ClientSession*      m_Client          = nullptr;
    std::string         m_PlayerName      = "none";
    int                 m_PlayerID        = -1;
    Sex                 m_Sex             = SEX_NONE;
    
    int                 m_CleanPoint      = -1; 
    int                 m_AttractivePoint = -1;
    int                 m_Money           = -1;
    float               m_RevivalTime     = 300.0f;
    Unit*               m_Unit            = nullptr;
    UnitList            m_UnitList;

    bool                m_IsReady         = false;
    int                 m_RoomID          = -1;
    
    
    //item 가질것 ... 이건 기본적 게임 구현해놓고...
};

