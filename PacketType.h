#pragma once

#define MAX_CHAT_LEN	256

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

enum PacketTypes
{
    PKT_NONE	= 0,
    
    PKT_CS_LOGIN	= 1,
    PKT_SC_LOGIN	= 2,
    
    PKT_CS_CHAT		= 11,
    PKT_SC_CHAT		= 12,

    PKT_CS_MOVE		= 21,
    PKT_SC_MOVE		= 22,

    PKT_MAX	= 1024
} ;
enum ZoneType
{
    ZONE_DEFAULT,
    //ZONE_CHUNGGAECHUN...
};

// enum RoomType
// {
//     ROOM_DEFAULT,
//     //ROOM_AQUA 
//     //etc...
// };

enum MapType
{
    MAP_DEFAULT,
    MAP_DEEPSEA,
    MAP_SMALLSTREAM,
    MAP_SMALLISLAND,
    MAP_HAWAII,

};

enum RegionType
{
    REGION_DEFAULT,
    REGION_SEOUL,
    REGION_KYUNGKI_N,
    REGION_KYUNGKI_S,
    REGION_BUSAN,

    //..
};
enum AquaZoneType
{
    AZONE_DEFAULT,
    AZONE_HANGANG,
    AZONE_CHUNGKYE,
    AZONE_AHNYANGCHUN,


};

enum Sex
{
    SEX_NONE,
    SEX_MALE,
    SEX_FEMALE,

};


enum UnitType
{
    UNIT_DEFAULT,
    UNIT_FISH,
    UNIT_DIVER,
    UNIT_FISHER,
    UNIT_EGG,



};

enum FishType
{
    FISH_DEFAULT,
   


};

enum DIverType
{
    DIVER_DEFAULT,
};

enum FisherType
{
    FISHER_DEFAULT,
    FISHER_PRINCESS,
    FISHER_RABBIT,
    FISHER_BEAR,
    FISHER_PIG,
    FISHER_FOX,
    FISHER_PUPPY, //강아지는 더 세분화할 필요
    FISHER_CAT,
    FISHER_RACOON,
    FISHER_HAMSTER,
    FISHER_HUMAN,


};

enum BobberType
{
    BOBBER_DEFAULT,
    BOBBER_HEART,
    

};

enum ShipType
{
    SHIP_DEFAULT,
    SHIP_BOAT,
    SHIP_PAPERSHIP,

};

enum ShipMoveKey
{
    SHIP_MOVE_NONE,
    SHIPMOVE_L,
    SHIPMOVE_R,
};

enum BobberActionKey
{
    BOBBER_U,
    BOBBER_D,
    BOBBER_L,
    BOBBER_R,


};

enum FishActionKey
{
    FISH_MOVE_NONE,
    FISH_PICK,
    FISH_BITE,
    FISH_MOVE_L,
    FISH_MOVE_R,
    FISH_MOVE_D, //다르게 표현해야할듯..
    FISH_MOVE_U, //다르게 표현해야할듯..


};

enum DiverActionKey
{
    DIVER_MOVE_NONE,
    DIVER_PICK,
    DIVER_MOVE_L,
    DIVER_MOVE_R,
    //DIVER_MOVE_D,
    //DIVER_MOVE_U,


};

enum EggActionKey
{
    EGG_ACTION_NONE,
    EGG_MOVE_U,
    EGG_MOVE_D,
    EGG_MOVE_L,
    EGG_MOVE_R,

    EGG_REVIVAL,
};



#pragma pack(push, 1)

struct PacketHeader
{
    PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
    short mSize ;
    short mType ;
} ;

struct Coord
{
    float x;
    float y;
};

struct RegionInfo
{
    RegionInfo()
    {
        mRegionNum = 0;
        mMaxRegionNum = 0;
        mCurZoneNum = 0;
        mMaxRegionNum = 0;
    }
    int mRegionNum;
    int mMaxRegionNum;
    int mCurZoneNum;
    int mMaxZoneNum;
};

struct AquaZoneInfo
{
    AquaZoneInfo()
    {
        mCurRoomNum = 0;
        mMaxRoomNum = 0;
    }

    int mCurRoomNum;
    int mMaxRoomNum;
};


struct RoomInfo
{
    RoomInfo()
    {
       //mRoomNum = 0;
        mCurPlayerNum = 0;
        mMaxPlayerNum = 0;
        //mRoomType = ROOM_DEFAULT;
        mMapType = MAP_DEFAULT;
        mIsStart = false; // 필요한가??
    }
    //int mRoomNum;
    int mCurPlayerNum;
    int mMaxPlayerNum;
    MapType mMapType;
    //RoomType mRoomType;
    bool mIsStart; // 필요한가??
};


struct LoginRequest : public PacketHeader
{
    LoginRequest()
    {
        mSize = sizeof(LoginRequest) ;
        mType = PKT_CS_LOGIN ;
        mPlayerId = -1 ;
    }

    int	mPlayerId ;
} ;

struct LoginResult : public PacketHeader
{
    LoginResult()
    {
        mSize = sizeof(LoginResult) ;
        mType = PKT_SC_LOGIN ;
        mPlayerId = -1 ;
        memset(mName, 0, MAX_NAME_LEN) ;
    }

    int		mPlayerId ;
    float	mPosX ;
    float	mPosY ;
    char	mName[MAX_NAME_LEN] ;

} ;

struct ChatBroadcastRequest : public PacketHeader
{
    ChatBroadcastRequest()
    {
        mSize = sizeof(ChatBroadcastRequest) ;
        mType = PKT_CS_CHAT ;
        mPlayerId = -1 ;
    
        memset(mChat, 0, MAX_CHAT_LEN) ;
    }

    int	mPlayerId ;
    char mChat[MAX_CHAT_LEN] ;
} ;

struct ChatBroadcastResult : public PacketHeader
{
    ChatBroadcastResult()
    {
        mSize = sizeof(ChatBroadcastResult) ;
        mType = PKT_SC_CHAT ;
        mPlayerId = -1 ;
        
        memset(mName, 0, MAX_NAME_LEN) ;
        memset(mChat, 0, MAX_CHAT_LEN) ;
    }
    
    int	mPlayerId ;
    char mName[MAX_NAME_LEN] ;
    char mChat[MAX_CHAT_LEN] ;
} ;


struct MoveRequest : public PacketHeader
{
    MoveRequest()
    {
        mSize = sizeof(MoveRequest);
        mType = PKT_CS_MOVE;
        mPlayerId = -1;
        mPosX = 0;
        mPosY = 0;
    }

    int		mPlayerId;
    float	mPosX;
    float	mPosY;
};

struct MoveBroadcastResult : public PacketHeader
{
    MoveBroadcastResult()
    {
        mSize = sizeof(MoveBroadcastResult);
        mType = PKT_SC_MOVE;
        mPlayerId = -1;
        mPosX = 0;
        mPosY = 0;
    }

    int		mPlayerId;
    float	mPosX;
    float	mPosY;
};



#pragma pack(pop)