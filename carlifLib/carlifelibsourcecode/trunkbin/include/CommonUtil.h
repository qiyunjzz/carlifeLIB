/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H
#include <string>
using namespace std;

/*******************************************************
DEFINE
*******************************************************/
#define LIB_LOG_SWITCH 

/*******************************************************
TYPEDEF
*******************************************************/
typedef unsigned char u8;
typedef unsigned int u32;

/*******************************************************
STRUCT
*******************************************************/
//struct for cmd channel
typedef struct HUProtocolVersion{
	u32 majorVersion;
    	u32 minorVersion;

}S_HU_PROTOCOL_VERSION;

typedef struct ProtocolVersionMatchStatus{
	u32 matchStatus;
}S_PROTOCOL_VERSION_MATCH_SATUS;

typedef struct HUInfo{
	string os;
	string board ;
	string bootloader ;
	string brand;
	string cpu_abi;
	string cpu_abi2 ;
	string device ;
	string display ;
	string fingerprint ;
	string hardware ;
	string host ;
	string cid ;
	string manufacturer ;
	string model ;
	string product ;
	string serial;
	string codename ;
	string incremental;
	string release ;
	string sdk ;
	u32 sdk_int;
	string token;

}S_HU_INFO;

typedef struct MDInfo{
	string os;
	string board ;
	string bootloader ;
	string brand;
	string cpu_abi;
	string cpu_abi2 ;
	string device ;
	string display ;
	string fingerprint ;
	string hardware ;
	string host ;
	string cid ;
	string manufacturer ;
	string model ;
	string product ;
	string serial;
	string codename ;
	string incremental;
	string release ;
	string sdk ;
	u32 sdk_int;

}S_MD_INFO;

typedef struct BTPairInfo{
	string address ;
	string passKey ;
	string hash ;
	string randomizer;
	string uuid;
	string name;
	u32 status;
}S_BT_PAIR_INFO;

typedef struct VideoEncoderInit{
	u32 width ;
	u32 height ;
	u32 frameRate;
}S_VIDEO_ENCODER_INIT;

typedef struct VideoEncoderInitDone{
	u32 width ;
	u32 height ;
	u32 frameRate;
}S_VIDEO_ENCODER_INIT_DONE;

typedef struct VideoEncoderFrameRateChange{
	u32 frameRate;
}S_VIDEO_ENCODER_FRAME_RATE_CHANGE;

typedef struct VideoEncoderFrameRateChangeDone{
	u32 frameRate;
}S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE;

typedef struct CarVelocity{
	u32 speed;
}S_CAR_VELOCITY;

typedef struct CarGPS{
	u32 antennaState;
	u32 signalQuality;
	// dBHz
	u32 latitude;
	// 1/1,000,000 degrees
	u32 longitude;
	// 1/1,000,000 degrees
	u32 height ;
	// 0.1 meters
	u32 speed ;
	// 0.01 km/h units
	u32 heading;
	// 0.1 degrees
	u32 year;
	u32 month;
	u32 day;
	u32 hrs ;
	u32 min ;
	u32 sec ;
	u32 fix;
	u32 hdop;
	// units 0.1
	u32 pdop ;
	// units 0.1
	u32 vdop ;
	// units 0.1
	u32 satsUsed ;
	u32 satsVisible;
	u32 horPosError ;
	u32 vertPosError;
	u32 northSpeed;
	// 0.01m/s
	u32 eastSpeed;
	// 0.01m/s
	u32 vertSpeed; 
	// 0.01m/s
}S_CAR_GPS;

typedef struct CarGyroscope{
	u32 samplesCount;
	u32 xAxisGyroSum;
	//degree/second
	u32 yAxisGyroSum;
	//degree/second
	u32 zAxisGyroSum ;
	//degree/second
}S_CAR_GYROSCOPE;

typedef struct CarAcceleration{
	u32 samplesCount ;
	u32 xAxisAcceSum ;
	// 1024 = 9.8meter/second squared
	u32 yAxisAcceSum ;
	// 1024 = 9.8meter/second squared
	u32 zAxisAcceSum ;
	// 1024 = 9.8meter/second squared

}S_CAR_ACCELERATION;

typedef struct CarOil{
	//reserved
}S_CAR_OIL;

//struct for media && tts channel
typedef struct AudioInitParameter{
	u32 sampleRate;
	u32 channelConfig;
	u32 sampleFormat;
}S_AUDIO_INIT_PARAMETER;

//struct for ctrl channel
typedef struct TouchAction{
	u32 action;
	u32 x ;
	u32 y ;

}S_TOUCH_ACTION;

typedef struct TouchActionDown{
	u32 x ;
	u32 y ;
}S_TOUCH_ACTION_DOWN;

typedef struct TouchActionUp{
	u32 x ;
	u32 y ;
}S_TOUCH_ACTION_UP;

typedef struct TouchActionMove{
	u32 x ;
	u32 y ;
}S_TOUCH_ACTION_MOVE;

typedef struct TouchSingleClick{
	u32 x;
	u32 y;
}S_TOUCH_SIGNAL_CLICK;

typedef struct TouchDoubleClick{
	u32 x;
	u32 y;
}S_TOUCH_DOUBLE_CLICK;

typedef struct TouchLongPress{
	u32 x;
	u32 y;
}S_TOUCH_LONG_PRESS;

typedef struct TouchCarHardkeyCode{
	u32 keycode;
}S_TOUCH_CAR_HARD_KEY_CODE;

typedef struct TouchUIActionSound{
	//reserved
}S_TOUCH_UI_ACTION_SOUND;

//0x00018025

//0x00010026
typedef struct ModuleStatusMobile{
	u32 moduleID;
	u32 statusID;
	struct ModuleStatusMobile* next;
}S_MODULE_STATUS_MOBILE;

typedef struct ModuleStatusListMobile{
	u32	cnt ;
	S_MODULE_STATUS_MOBILE* moduleStatus;
}S_MODULE_STATUS_LIST_MOBILE;

//0x00018027
typedef struct StatisticsInfo{
	string cuid;
	string versionName;
	u32 versionCode;
	string channel;
	u32 connectCount;
	u32 connectSuccessCount;
	u32 connectTime;
	string crashLog;
}S_STATISTICS_INFO;

//0x00018028
typedef struct ModuleStatusControl{
	u32 moduleID;
        u32 statusID;
}S_MODULE_STATUS_CONTROL;

//0x00018029
typedef struct GearInfo
{
	u32 gear;
}S_GEAR_INFO;

//0x00010030
typedef struct NaviNextTurnInfo
{
	u32 action ;
	u32 nextTurn;
	string roadName ;
	u32 totalDistance ;
	u32 remainDistance ;
	u32 time;
}S_NAVI_NEXT_TURN_INFO;

//0x00010031
//0x00010032
//0x00010033s
//0x00010034
typedef struct VehicleInfo{
	u32 moduleID;
	bool supportFlag;
	u32 frequency;

	struct VehicleInfo* pNext;
}S_VEHICLE_INFO;

typedef struct VehicleInfoList{
	u32	cnt ;
	S_VEHICLE_INFO* pVehicleInfo;
}S_VEHICLE_INFO_LIST;

//0x00010035
typedef struct MediaInfo
{
	string source ;
	string song ;
	string artist ;
	string album ;
	string albumArt ;
	u32 duration ;
	u32 playlistNum ;
	string songId ;
	u32 mode ;
}S_MEDIA_INFO;

//0x00010036
typedef struct MediaProgressBar{
	u32 progressBar;
}S_MEDIA_PROGRESS_BAR;

//0x00010037
typedef struct ConnectException
{
	u32 exceptionType;
}S_CONNECTION_EXCEPTION;	

//0x00010038

//0x00010039

//0x00010040
typedef struct BTHfpRequest{
	u32 command;
	string phoneNum;
	u32 dtmfCode;
}S_BT_HFP_REQUEST;

//0x00018041
typedef struct BTHfpIndication{
	u32 state;
	string phoneNum;
	string name;
	string address;
}S_BT_HFP_INDICATION;

//0x00018042
typedef struct BTHfpConnection{
	u32 state;
	string address;
	string name;
}S_BT_HFP_CONNECTION;

//0x00018043
//0x00010044
//0x00018045
//0x00018046
typedef struct MobileCarLifeInfo{
	u32 moduleID;
	bool supportFlag;
	u32 frequency;

	struct MobileCarLifeInfo *pNext; 
}S_MOBILE_CARLIFE_INFO;

typedef struct SubscribeMobileCarLifeInfoList{
	u32 cnt;
	S_MOBILE_CARLIFE_INFO *pMobileCarLifeInfo;
}S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST;

//0x00010047
typedef struct NaviAssitantGuideInfo{
	u32 action;
	u32 assistantType;
	u32 trafficSignType;
	u32 totalDistance;
	u32 remainDistance;
	u32 cameraSpeed;
}S_NAVI_ASSITANT_GUIDE_INFO;

//0x00018048
typedef struct AuthenRequest{
	string randomValue;
}S_AUTHEN_REQUEST;

//0x00010049
typedef struct AuthenResponse{
	string encryptValue;
}S_AUTHEN_RESPONSE;

//0x0001004A
typedef struct HUAuthenResult{
	bool authenResult;
}S_HU_AUTHEN_RESULT;

//0x0001804B
typedef struct MDAuthenResult{
	bool authenResult;
}S_MD_AUTHEN_RESULT;

//0x0001004C
//none

//0x0001004D
typedef struct BTStartPairReq{
	u32 osType;
	string address;
}S_BT_START_PAIR_REQ;

//0x0001804E
typedef struct BTHfpResponse{
	u32 status;
	u32 cmd;
	u32 dtmfCode;
}S_BT_HFP_RESPONSE;

//0x0001004F
typedef struct BTHfpStatusRequest{
	u32 type;
}S_BT_HFP_STATUS_REQUEST;

//0x00018050
typedef struct BTHfpStatusResponse{
	u32 status;
	u32 type;
}S_BT_HFP_STATUS_RESPONSE;

//0x00018051
//none

//0x00018052
typedef struct FeatureConfig{
	string key;
	u32 value;

	struct FeatureConfig *pNext;
}S_FEATURE_CONFIG;

typedef struct FeatureConfigList{
	u32 cnt;

	S_FEATURE_CONFIG *pFeatureConfig;
}S_FEATURE_CONFIG_LIST;

//0x00018053
typedef struct BTStartIdentifyReq{
	string address;
}S_BT_START_IDENTIFY_REQ;

//0x00010054
typedef struct BTIdentifyResultInd{
	u32 status;
	string address;
}S_BT_INDENTIFY_RESULT_IND;

//0x00018055
typedef struct ErrorCode{
	string errorCode;
}S_ERROR_CODE;

























































#endif































