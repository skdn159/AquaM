#pragma once

#include <map>
#include <WinSock2.h>
#include "Config.h"
#include "..\..\PacketType.h"
#include "CircularBuffer.h"
#include "ObjectPool.h"
#include "RefCountable.h"


class ClientSession ;
class ClientManager ;
struct DatabaseJobContext ;
class Player;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO() : mObject(nullptr)
	{}

	ClientSession* mObject ;
} ;

class ClientSession : public RefCountable, public ObjectPool<ClientSession>
{
public:
	ClientSession(SOCKET sock)
		: mConnected(false), mLogon(false), mSocket(sock), mPlayerId(-1), mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE)
		, mPosX(0), mPosY(0)
	{
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN)) ;
		memset(mPlayerName, 0, sizeof(mPlayerName)) ;
	}
	virtual ~ClientSession() {}

public:
	int	    GetPlayerId() const	{ return mPlayerId; }
	const char* GetPlayerName() const { return mPlayerName;  }
	SOCKET  GetSocketKey() const { return mSocket;  }
	void    SetPosition(float x, float y) { mPosX = x; mPosY = y; }

	//void	LoginDone(int pid, float x, float y, const char* name);
    //void	UpdateDone();


public: 
	bool	IsConnected() const { return mConnected; }
	void	OnTick();
    //void	OnDbUpdate(); ///< 주기적으로 데이터베이스에 업데이트

	template <class PKT_TYPE>
	bool ParsePacket(PKT_TYPE& pkt)	{return mRecvBuffer.Read((char*)&pkt, pkt.mSize);}

	void	OnRead(size_t len) ;
	void	OnWriteComplete(size_t len) ;
	bool	OnConnect(SOCKADDR_IN* addr) ;
	bool	PostRecv() ;
	bool	SendRequest(PacketHeader* pkt) ;
	bool	Broadcast(PacketHeader* pkt) ;
	void	Disconnect() ;
	bool	SendFlush(); ///< Send요청 중인것들 모아서 보냄
    //void	DatabaseJobDone(DatabaseJobContext* result);


    ////////////////////////////////////////
    //인자값 갱신할것
    void    JoinRegionChannel();
    void    OutRegionChannel();
    void    JoinAquaZone();
    void    OutAquaZone();
    void    JoinGameRoom();
    void    OutGameRoom();






    /////////////////////////////////////////
    void    ShipMoveBroadCast(int playerId, int unitId, const b2Vec2& curPos, ShipMoveKey shipMove);
    void    BobberActionBroadCast(int playerId, int unitId, const b2Vec2& curPos, BobberActionKey bobberAction);
    void    FishActionBroadCast(int playerId, int unitId, const b2Vec2& curPos, FishActionKey fishAction);



private:
	float			mPosX ;
	float			mPosY ;
	char			mPlayerName[MAX_NAME_LEN] ;
    Player*         mPlayer = nullptr;

private:
	bool			mConnected ;
	bool			mLogon ;
	SOCKET			mSocket ;

	int				mPlayerId ;
	SOCKADDR_IN		mClientAddr ;

	CircularBuffer	mSendBuffer ;
	CircularBuffer	mRecvBuffer ;

	OverlappedIO	mOverlappedSend ;
	OverlappedIO	mOverlappedRecv ;

	friend class ClientManager ;
} ;


void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
