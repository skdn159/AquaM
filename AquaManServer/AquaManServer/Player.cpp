#include "stdafx.h"
#include "Player.h"

Player::Player(ClientSession* client, int playerId, const std::string& playerName, Sex sex, int attractivePoint, int cleanPoint, int money):
m_Client(client), m_PlayerID(playerId), m_PlayerName(playerName), m_Sex(sex), m_AttractivePoint(attractivePoint), m_CleanPoint(cleanPoint), m_Money(money)
{

}
// Player::Player()
// {
// }


Player::~Player()
{
    //UnitListClear(); // UnitListClear�� �����س��� ������ ������ ����
}
