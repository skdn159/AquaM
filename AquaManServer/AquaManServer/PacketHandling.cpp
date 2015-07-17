#include "stdafx.h"
#include "ClientSession.h"
// #include "DatabaseJobContext.h"
// #include "DatabaseJobManager.h"

//@{ Handler Helper

typedef void (*HandlerFunc)(ClientSession* session);

static HandlerFunc HandlerTable[PKT_MAX];

static void DefaultHandler(ClientSession* session)
{
	printf("[DEBUG] Invalid packet handler", session->GetPlayerId());
	session->Disconnect();
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for (int i = 0; i < PKT_MAX; ++i)
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler
{
	RegisterHandler(int pktType, HandlerFunc handler)
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(ClientSession* session); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(ClientSession* session)

//@}

///////////////////////////////////////////////////////////////////////////
/*
연결된 클라이언트와 패킷 받고 보내는 작업 완료하는 콜백 함수들
*/
///////////////////////////////////////////////////////////////////////////

void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	/// 받은 데이터 처리
	fromClient->OnRead(cbTransferred);

	/// 다시 받기
	if (false == fromClient->PostRecv())
	{
		fromClient->Disconnect();
		return;
	}
}


void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	fromClient->OnWriteComplete(cbTransferred);

}

///////////////////////////////////////////////////////////////////////////
/*
보내기 완료한 패킷을 출력버퍼에서 제거하는 함수
*/
///////////////////////////////////////////////////////////

void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len);

	/// 패킷 파싱하고 처리
	while (true)
	{
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader header;
		if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			return;

		/// 패킷 완성이 되는가? 
		if (mRecvBuffer.GetStoredSize() < (size_t) header.mSize)
			return;


		if (header.mType >= PKT_MAX || header.mType <= PKT_NONE)
		{
			printf("[DEBUG] Invalid packet type", GetPlayerId());
			Disconnect();
			return;
		}

		/// packet dispatch...
		HandlerTable[header.mType](this);
	}
}
///////////////////////////////////////////////////////////////////////////
/*
패킷 타입에 따라 파싱을 완료하고 작업을 처리하는 핸들러들
*/
/////////////////////////////////////////////////////////
REGISTER_HANDLER(PKT_CS_LOGIN)
{
	LoginRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error", inPacket.mType);
		return;
	}

// 	LoadPlayerDataContext* newDbJob = new LoadPlayerDataContext(session->GetSocketKey(), inPacket.mPlayerId);
// 	GDatabaseJobManager->PushDatabaseJobRequest(newDbJob);

}

REGISTER_HANDLER(PKT_CS_CHAT)
{
	ChatBroadcastRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error", inPacket.mType);
		return;
	}

	if (inPacket.mPlayerId != session->GetPlayerId())
	{
		printf("[DEBUG] PKT_CS_CHAT: invalid player ID", session->GetPlayerId());
		return;
	}

	/// chatting의 경우 여기서 바로 방송
	
	ChatBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	strcpy_s(outPacket.mName, session->GetPlayerName());
	strcpy_s(outPacket.mChat, inPacket.mChat);

	/// 채팅은 바로 방송 하면 끝
	if (!session->Broadcast(&outPacket))
	{
		session->Disconnect();
	}
}


REGISTER_HANDLER(PKT_CS_MOVE)
{
	MoveRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error", inPacket.mType);
		return;
	}

	if (inPacket.mPlayerId != session->GetPlayerId())
	{
		printf("[DEBUG] PKT_CS_MOVE: invalid player ID", session->GetPlayerId());
		return;
	}

	/// 플레이어 좌표 업데이트하고 바로 방송하면 끝
	session->SetPosition(inPacket.mPosX, inPacket.mPosY);

	MoveBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mPosX = inPacket.mPosX;
	outPacket.mPosY = inPacket.mPosY;

	if (!session->Broadcast(&outPacket))
	{
		session->Disconnect();
	}

}

void ClientSession::ShipMoveBroadCast(int playerId, int unitId, const b2Vec2& curPos, ShipMoveKey shipMove)
{

}

void ClientSession::BobberActionBroadCast(int playerId, int unitId, const b2Vec2& curPos, BobberActionKey bobberAction)
{

}

void ClientSession::FishActionBroadCast(int playerId, int unitId, const b2Vec2& curPos, FishActionKey fishAction)
{

}




