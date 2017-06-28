/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_TRAN_RECV_PACKAGE_PROCESS
#define C_TRAN_RECV_PACKAGE_PROCESS
#include "CommonUtil.h"
#include <string.h>

using namespace std;

/********************************************************
DEFINE
*********************************************************/
#define DEFAULT_HEAD_LEN 12
#define DEFAULT_DATA_SIZE 10*1024

#define CMD_HEAD_LEN 8
#define CMD_DATA_SIZE 40*1024//MSG_CMD_MEDIA_INFO<32k

#define VIDEO_HEAD_LEN 12
#define VIDEO_DATA_SIZE 600*1024//normally VIDEO_DATA_SIZE<300X1024

#define MEDIA_HEAD_LEN 12
#define MEDIA_DATA_SIZE 100*1024

#define TTS_HEAD_LEN 12
#define TTS_DATA_SIZE 50*1024//normally TTS_DATA_SIZE<10x1024

#define VR_HEAD_LEN 12
#define VR_DATA_SIZE 50*1024//normally VR_DATA_SIZE<10x1024

#define CTRL_HEAD_LEN 8
#define CTRL_DATA_SIZE 10*1024

/**********************************************************
ENUM
***********************************************************/
typedef enum EChannelType{
	CMD_CHANNEL=1,
	VIDEO_CHANNEL=2,
	MEDIA_CHANNEL=3,
	TTS_CHANNEL=4,
	VR_CHANNEL=5,
	CTRL_CHANNEL=6,
}E_CHANNEL_TYPE;

typedef enum EPackageHeadType{
	//--------------------Command channel-------------------------
       //command channel relative
	//--interactive message for initialization
	MSG_CMD_HU_PROTOCOL_VERSION = 0x00018001,
	MSG_CMD_PROTOCOL_VERSION_MATCH_STATUS = 0x00010002,
	MSG_CMD_HU_INFO = 0x00018003,
	MSG_CMD_MD_INFO = 0x00010004,
	MSG_CMD_HU_BT_PAIR_INFO = 0x00018005,
	MSG_CMD_MD_BT_PAIR_INFO = 0x00010006,

	//--video relative
	MSG_CMD_VIDEO_ENCODER_INIT = 0x00018007,
	MSG_CMD_VIDEO_ENCODER_INIT_DONE = 0x00010008,
	MSG_CMD_VIDEO_ENCODER_START = 0x00018009,
	MSG_CMD_VIDEO_ENCODER_PAUSE = 0x0001800A,
	MSG_CMD_VIDEO_ENCODER_RESET = 0x0001800B,
	MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE = 0x0001800C,
	MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE = 0x0001000D,

	//--audio relative
	MSG_CMD_PAUSE_MEDIA = 0x0001800E,

	//--vehicle infromation
	MSG_CMD_CAR_VELOCITY = 0x0001800F,
	MSG_CMD_CAR_GPS = 0x00018010,
	MSG_CMD_CAR_GYROSCOPE = 0x00018011,
	MSG_CMD_CAR_ACCELERATION = 0x00018012,
	MSG_CMD_CAR_OIL = 0x00018013,

	//--phone status
	MSG_CMD_TELE_STATE_CHANGE_INCOMING = 0x00010014,
	MSG_CMD_TELE_STATE_CHANGE_OUTGOING = 0x00010015,
	MSG_CMD_TELE_STATE_CHANGE_IDLE = 0x00010016,
	MSG_CMD_TELE_STATE_CHANGE_INCALLING = 0x00010017,

	//--mobile device status
	MSG_CMD_SCREEN_ON = 0x00010018,
	MSG_CMD_SCREEN_OFF = 0x00010019,
	MSG_CMD_SCREEN_USERPRESENT = 0x0001001A,
	MSG_CMD_FOREGROUND = 0x0001001B,
	MSG_CMD_BACKGROUND = 0x0001001C,
	
	//--launch mode
	MSG_CMD_LAUNCH_MODE_NORMAL = 0x0001801D,
	MSG_CMD_LAUNCH_MODE_PHONE = 0x0001801E,
	MSG_CMD_LAUNCH_MODE_MAP = 0x0001801F,
	MSG_CMD_LAUNCH_MODE_MUSIC = 0x00018020,
	MSG_CMD_GO_TO_DESKTOP = 0x00010021,
	
	//--vr relative
	MSG_CMD_MIC_RECORD_WAKEUP_START = 0x00010022,
	MSG_CMD_MIC_RECORD_END = 0x00010023,
	MSG_CMD_MIC_RECORD_RECOG_START = 0x00010024,

	MSG_CMD_GO_TO_FOREGROUND = 0x00018025,
       MSG_CMD_MODULE_STATUS = 0x00010026,
       MSG_CMD_STATISTIC_INFO = 0x00018027,
       MSG_CMD_MODULE_CONTROL = 0x00018028,


	//navi info
	MSG_CMD_GEAR_INFO=0x00010029,
	MSG_CMD_NAVI_NEXT_TURN_INFO=0x00010030,
	MSG_CMD_CAR_DATA_SUBSCRIBE=0x00010031,
	MSG_CMD_CAR_DATA_SUBSCRIBE_DONE=0x00010032,
	MSG_CMD_CAR_DATA_SUBSCRIBE_START=0x00010033,
	MSG_CMD_CAR_DATA_SUBSCRIBE_STOP=0x00010034,

       //music relative
       MSG_CMD_MEDIA_INFO = 0x00010035,
       MSG_CMD_MEDIA_PROGRESS_BAR = 0x00010036,

       MSG_CMD_CONNECT_EXCEPTION = 0x00010037,
       MSG_CMD_REQUEST_GO_TO_FOREGROUND = 0x00010038,

       MSG_CMD_UI_ACTION_SOUND = 0x00010039,

	MSG_CMD_BT_HFP_REQUEST=0x00010040,
	MSG_CMD_BT_HFP_INDICATION=0x00018041,
       MSG_CMD_BT_HFP_CONNECTION=0x00018042,

	MSG_CMD_CARLIFE_DATA_SUBSCRIBE=0x00018043,
	MSG_CMD_CARLIFE_DATA_SUBSCRIBE_DONE=0x00010044,
	MSG_CMD_CARLIFE_DATA_SUBSCRIBE_START=0x00018045,
	MSG_CMD_CARLIFE_DATA_SUBSCRIBE_STOP=0x00018046,
	MSG_CMD_NAVI_ASSITANTGUIDE_INFO=0x00010047,
	MSG_CMD_HU_AUTHEN_REQUEST=0x00018048,
	MSG_CMD_MD_AUTHEN_RESPONSE=0x00010049,
	MSG_CMD_HU_AUTHEN_RESULT=0x0001804A,
	MSG_CMD_MD_AUTHEN_RESULT=0x0001004B,
	MSG_CMD_GO_TO_FOREGROUND_RESPONSE=0x0001004C,
	MSG_CMD_START_BT_AUTOPAIR_REQUEST=0x0001004D,
	MSG_CMD_BT_HFP_RESPONSE=0x0001804E,
	MSG_CMD_BT_HFP_STATUS_REQUEST=0x0001004F,
	MSG_CMD_BT_HFP_STATUS_RESPONSE=0x00018050,

	MSG_CMD_MD_FEATURE_CONFIG_REQUEST=0x00010051,
       MSG_CMD_HU_FEATURE_CONFIG_RESPONSE=0x00018052,
	MSG_CMD_BT_START_IDENTIFY_REQ=0x00018053,
	MSG_CMD_BT_IDENTIFY_RESULT_IND=0x00010054,
	MSG_CMD_ERROR_CODE=0x00018055,

       //------------------------Video channel--------------------------------
	//video channel relative
	MSG_VIDEO_DATA = 0x00020001,
	MSG_VIDEO_HEARTBEAT = 0x00020002,

	//------------------------Media channel-------------------------------
	//media channel relative
	MSG_MEDIA_INIT = 0x00030001,
	MSG_MEDIA_STOP = 0x00030002,
	MSG_MEDIA_PAUSE = 0x00030003,
	MSG_MEDIA_RESUME_PLAY = 0x00030004,
	MSG_MEDIA_SEEK_TO = 0x00030005,
	MSG_MEDIA_DATA = 0x00030006,

	 //-------------------Navi TTS channel-----------------------------
	//tts channel relative
	MSG_TTS_INIT = 0x00040001,
	MSG_TTS_STOP = 0x00040002,
	MSG_TTS_DATA = 0x00040003,

	//-------------------VR channel----------------------
	//vr channel relative
	MSG_VR_MIC_DATA = 0x00058001,
	MSG_VR_INIT = 0x00050002,
	MSG_VR_DATA = 0x00050003,
	MSG_VR_STOP = 0x00050004,

	//-----------------Control channel--------------------
	//control channel relative
	MSG_TOUCH_ACTION = 0x00068001,
	MSG_TOUCH_ACTION_DOWN = 0x00068002,
	MSG_TOUCH_ACTION_UP = 0x00068003,
	MSG_TOUCH_ACTION_MOVE = 0x00068004,
	MSG_TOUCH_SINGLE_CLICK = 0x00068005,
	MSG_TOUCH_DOUBLE_CLICK = 0x00068006,
	MSG_TOUCH_LONG_PRESS = 0x00068007,
	MSG_TOUCH_CAR_HARD_KEY_CODE = 0x00068008,
	MSG_TOUCH_UI_ACTION_SOUND = 0x00060009,

	//hard key value
	KEYCODE_HOME = 0x00000001,
	KEYCODE_PHONE_CALL = 0x00000002,
	KEYCODE_PHONE_END = 0x00000003,
	KEYCODE_PHONE_END_MUTE = 0x00000004,
	KEYCODE_HFP = 0x00000005,
	KEYCODE_SELECTOR_NEXT = 0x00000006,
	KEYCODE_SELECTOR_PREVIOUS = 0x00000007,
	KEYCODE_SETTING = 0x00000008,
	KEYCODE_MEDIA = 0x00000009,
	KEYCODE_RADIO = 0x0000000A,
	KEYCODE_NAVI = 0x0000000B,
	KEYCODE_SRC = 0x0000000C,
	KEYCODE_MODE = 0x0000000D,
	KEYCODE_BACK = 0x0000000E,
	KEYCODE_SEEK_SUB = 0x0000000F,
	KEYCODE_SEEK_ADD = 0x00000010,
	KEYCODE_VOLUME_SUB = 0x00000011,
	KEYCODE_VOLUME_ADD = 0x00000012,
	KEYCODE_MUTE = 0x00000013,
	KEYCODE_OK = 0x00000014,
	KEYCODE_MOVE_LEFT = 0x00000015,
	KEYCODE_MOVE_RIGHT = 0x00000016,
	KEYCODE_MOVE_UP = 0x00000017,
	KEYCODE_MOVE_DOWN = 0x00000018,
	KEYCODE_MOVE_UP_LEFT = 0x00000019,
	KEYCODE_MOVE_UP_RIGHT = 0x0000001A,
	KEYCODE_MOVE_DOWN_LEFT = 0x0000001B,
	KEYCODE_MOVE_DOWN_RIGHT = 0x0000001C,
	KEYCODE_TEL = 0x0000001D,
	KEYCODE_MAIN = 0x0000001E,
}E_PACKAGE_HEAD_TYPE;

/*******************************************************
STRUCT
*******************************************************/
//struct for package(include head and data body)
typedef struct Package{
	u8* packageHead;
	u8* packageData;
}S_PACKAGE;

//struct for analyzed head
typedef struct analyzedHead{
	u32 packageDataSize;
	u32 packageDataTimeStamp;
	E_PACKAGE_HEAD_TYPE packageHeadType;
}S_ANALYZED_HEAD;

/**********************************************************
CLASS
**********************************************************/
class CTranRecvPackageProcess{
	public:
		CTranRecvPackageProcess(E_CHANNEL_TYPE channelType);
		~CTranRecvPackageProcess();

		//get package and analysis
		bool receivePackageHead();
		void packageHeadAnalysis();

		bool receivePackageData();
		void packageDataAnalysis();

		//===============command channel [HU->MD]=================
		int sendCmdHUProtoclVersion(S_HU_PROTOCOL_VERSION* version);
		int sendCmdHUInfro(S_HU_INFO* huInfo);
		int cmdHUBTPairInfro(S_BT_PAIR_INFO* info);
		int sendCmdVideoEncoderInit(S_VIDEO_ENCODER_INIT* initParam);
		int sendCmdVideoEncoderStart();
		int sendCmdVideoEncoderPause();
		int sendCmdVideoEncoderReset();
		int sendCmdVideoEncoderFrameRateChange(S_VIDEO_ENCODER_FRAME_RATE_CHANGE* videoParam);
		int sendCmdPauseMedia();
		int sendCmdCarVelocity(S_CAR_VELOCITY* carVelocity);
		int sendCmdCarGPS(S_CAR_GPS* cps);
		int sendCmdCarGyroscope(S_CAR_GYROSCOPE* cyro);
		int sendCmdCarAcceleration(S_CAR_ACCELERATION* acceleration);
		int sendCmdCarOil();
		int sendCmdLaunchModeNormal();
		int sendCmdLaunchModePhone();
		int sendCmdLaunchModeMap();
		int sendCmdLaunchModeMusic();

		void cmdRegisterProtocolVersionMatchStatus(void (*pCmd)(S_PROTOCOL_VERSION_MATCH_SATUS*));
		void cmdRegisterMDInfro(void (*pCmd)(S_MD_INFO*));
		void cmdRegisterMDBTPairInfro(void (*pCmd)(S_BT_PAIR_INFO*));
		void cmdRegisterVideoEncoderInitDone(void (*pCmd)(S_VIDEO_ENCODER_INIT_DONE*));
		void cmdRegisterVideoEncoderFrameRateChangeDone(void (*pCmd)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*));
		void cmdRegisterTelStateChangeIncoming(void (*pCmd)(void));
		void cmdRegisterTelStateChangeOutGoing(void (*pCmd)(void));
		void cmdRegisterTelStateChangeIdle(void (*pCmd)(void));
		void cmdRegisterTelStateChangeInCalling(void (*pCmd)(void));
		void cmdRegisterScreenOn(void (*pCmd)(void));
		void cmdRegisterScreenOff(void (*pCmd)(void));
		void cmdRegisterScreenUserPresent(void (*pCmd)(void));
		void cmdRegisterForeground(void (*pCmd)(void));
		void cmdRegisterBackground(void (*pCmd)(void));
		void cmdRegisterGoToDeskTop(void (*pCmd)(void));
		void cmdRegisterMicRecordWakeupStart(void (*pCmd)(void));
		void cmdRegisterMicRecordEnd(void (*pCmd)(void));
		void cmdRegisterMicRecordRecogStart(void (*pCmd)(void));

		//added on 9th Semptember 2015
		//0x00018025
		int cmdGoToForeground();

		//0x00010026
		void cmdRegisterModuleStatus(void (*pFunc)(S_MODULE_STATUS_LIST_MOBILE*));

		//0x00018027
		int cmdStatisticInfo(S_STATISTICS_INFO*);

		//0x00018028
		int cmdModuleControl(S_MODULE_STATUS_CONTROL*);

		//0x00018029
		int cmdCarDataGear(S_GEAR_INFO*);

		//0x00010030
		void cmdRegisterNaviNextTurnInfo(void (*pFunc)(S_NAVI_NEXT_TURN_INFO*));

		//0x00010031
		void cmdRegisterCarDataSubscribe(void (*pFunc)(S_VEHICLE_INFO_LIST*));

		//0x00018032
		int cmdCarDataSubscribeDone(S_VEHICLE_INFO_LIST*);

		//0x00010033
		void cmdRegisterCarDataSubscribeStart(void (*pFunc)(S_VEHICLE_INFO_LIST*));

		//0x00010034
		void cmdRegisterCarDataSubscribeStop(void (*pFunc)(S_VEHICLE_INFO_LIST*));

		//0x00010035
		void cmdRegisterMediaInfo(void (*pFunc)(S_MEDIA_INFO*));

		//0x00010036
		void cmdRegisterMediaProgressBar(void (*pFunc)(S_MEDIA_PROGRESS_BAR*));

		//0x00010037
		void cmdRegisterConnectException(void (*pFunc)(S_CONNECTION_EXCEPTION*));

		//0x00010038
		void cmdRegisterRequestGoToForeground(void (*pFunc)(void));

		//0x00010039
		void cmdRegisterUIActionSound(void (*pFunc)(void));

		//added on 5th January 2016
		//0x00010040
		void cmdRegisterBtHfpRequest(void (*pFunc)(S_BT_HFP_REQUEST*));

		//0x00018041
		int cmdBtHfpIndication(S_BT_HFP_INDICATION*);

		//0x00018042
		int cmdBtHfpConnection(S_BT_HFP_CONNECTION*);

		//0x00018043 
		int cmdCarLifeDataSubscribe(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*);

		//0x00010044 
		void cmdRegisterCarLifeDataSubscribeDone(void (*pFunc)(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*));

		//0x00018045 
		int cmdCarLifeDataSubscribeStart(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*);

		//0x00018046 
		int cmdCarLifeDataSubscribeStop(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*);

		//0x00010047 
		void cmdRegisterNaviAssistantGuideInfo(void (*pFunc)(S_NAVI_ASSITANT_GUIDE_INFO*));

		//0x00018048 
		int cmdHuAuthenRequest(S_AUTHEN_REQUEST*);

		//0x00010049 
		void cmdRegisterMdAuthenResponse(void (*pFunc)(S_AUTHEN_RESPONSE*));

		//0x0001804A 
		int cmdHuAuthenResult(S_HU_AUTHEN_RESULT*);

		//0x0001804B
		void cmdRegisterMdAuthenResult(void (*pFunc)(S_MD_AUTHEN_RESULT*));

		//0x0001004C 
		void cmdRegisterGotoForgroundResponse(void (*pFunc)(void));

		//0x0001004D 
		void cmdRegisterStartBtAutoPairRequest(void (*pFunc)(S_BT_START_PAIR_REQ*));

		//0x0001804E
		int cmdBTHfpResponse(S_BT_HFP_RESPONSE*);

		//0x0001004F
		void cmdRegisterBTHfpStatusRequest(void (*pFunc)(S_BT_HFP_STATUS_REQUEST*));
		
		//0x00018050
		int cmdBTHfpStatusResponse(S_BT_HFP_STATUS_RESPONSE*);

		//added on 3th March 2016
		//0x00010051
		void cmdRegisterFeatureConfigRequest(void (*pFunc)(void));

		//0x00018052
		int cmdFeatureConfigResponse(S_FEATURE_CONFIG_LIST*);

		//0x00018053
		int cmdBTStartIdentifyReq(S_BT_START_IDENTIFY_REQ*);

		//0x00010054
		void cmdRegisterBTIdentifyResultInd(void (*pFunc)(S_BT_INDENTIFY_RESULT_IND*));

		//0x00018055
		int cmdErrorCode(S_ERROR_CODE*);

		//video channel [MD->HU]
		void videoRegisterDataReceive(void (*pCmd)(u8 *data, u32 len));
		void videoRegisterHeartBeat(void (*pFunc)(void));

		//============media channel [MD->HU]=============
		void mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
		void mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
		void mediaRegisterStop(void (*pFunc)(void));
		void mediaRegisterPause(void (*pFunc)(void));
		void mediaRegisterResume(void (*pFunc)(void));
		void mediaRegisterSeek(void (*pFunc)(void));

		//============tts channel [MD->HU]===========
		void ttsRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
		void ttsRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
		void ttsRegisterStop(void (*pFunc)(void));

		//=============vr channel [HU->MD]===========
		int sendMicData(u8* data, u32 size, u32 timeStamp);
		void vrRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
		void vrRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
		void vrRegisterStop(void (*pFunc)(void));

		//==========ctrol channel [HU->MD]=============
		int sendCtrlTouchAction(S_TOUCH_ACTION* touchAction);
		int sendCtrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown);
		int sendCtrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp);
		int sendCtrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove);
		int sendCtrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick);
		int sendCtrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick);
		int sendCtrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress);
		int sendCtrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode);
		void ctrlRegisterUIActionSound(void (*pFunc)(void));

	private:
		E_CHANNEL_TYPE channel;

		//package
		S_PACKAGE sendPackage;
		S_PACKAGE recvPackage;

		//analyzed head
		S_ANALYZED_HEAD analyzedHead;

		//cmd parameter
		S_PROTOCOL_VERSION_MATCH_SATUS protocolVersionMatchstatus;
		S_MD_INFO mdInfo;
		S_BT_PAIR_INFO btPairInfo;
		S_VIDEO_ENCODER_INIT_DONE videoEncoderInitDone;
		S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE videoEncoderFrameRateChangeDone;

		//added 10th Semptember
		int moduleStatusMobileNum;
		S_MODULE_STATUS_MOBILE moduleStatusMobile1;
		S_MODULE_STATUS_MOBILE moduleStatusMobile2;
		S_MODULE_STATUS_MOBILE moduleStatusMobile3;
		S_MODULE_STATUS_MOBILE moduleStatusMobile4;
		S_MODULE_STATUS_MOBILE moduleStatusMobile5;
		S_MODULE_STATUS_MOBILE moduleStatusMobile6;
		S_MODULE_STATUS_MOBILE moduleStatusMobile7;
		S_MODULE_STATUS_MOBILE moduleStatusMobile8;
		S_MODULE_STATUS_MOBILE moduleStatusMobile9;
		S_MODULE_STATUS_MOBILE moduleStatusMobile10;
		S_MODULE_STATUS_LIST_MOBILE moduleStatusListMobile;

		S_NAVI_NEXT_TURN_INFO naviNextTurnInfo;

		int vehicleInfoNum;
		S_VEHICLE_INFO vehicleInfo1;
		S_VEHICLE_INFO vehicleInfo2;
		S_VEHICLE_INFO vehicleInfo3;
		S_VEHICLE_INFO vehicleInfo4;
		S_VEHICLE_INFO vehicleInfo5;
		S_VEHICLE_INFO vehicleInfo6;
		S_VEHICLE_INFO vehicleInfo7;
		S_VEHICLE_INFO vehicleInfo8;
		S_VEHICLE_INFO vehicleInfo9;
		S_VEHICLE_INFO vehicleInfo10;
		S_VEHICLE_INFO_LIST vehicleInfoList;

		S_MEDIA_INFO mediaInfo;

		S_MEDIA_PROGRESS_BAR mediaProgressBar;

		S_CONNECTION_EXCEPTION connectionException;

		//added on 6th January 2016
		//0x00010040
		S_BT_HFP_REQUEST bTHfpRequest;

		//0x00010044
		int subscribeMobileCarLifeInfoNum;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo1;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo2;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo3;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo4;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo5;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo6;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo7;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo8;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo9;
		S_MOBILE_CARLIFE_INFO mobileCarLifeInfo10;
		S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST subscribeMobileCarLifeInfoList;

		//0x00010047
		S_NAVI_ASSITANT_GUIDE_INFO naviAssitantGuideInfo;

		//0x00010049
		S_AUTHEN_RESPONSE authenResponse;

		//0x0001804B
		S_MD_AUTHEN_RESULT mDAuthenResult;

		//0x0001004D
		S_BT_START_PAIR_REQ bTStartPairReq;

		//0x0001004F
		S_BT_HFP_STATUS_REQUEST bTHfpStatusRequest;

		//0x00010054
		S_BT_INDENTIFY_RESULT_IND btIndentifyResultInd;

		//media && tts parameter
		S_AUDIO_INIT_PARAMETER audioInitParameter;

		//set package head information
		void setPackageHeadDataSize(u32 size);
		void setPackageHeadType(u32 type);
		void setPackageHeadTimeStamp(u32);

		//set package data infromation
		void setPackageDataFiled(u8* data, u32 size);

		//command channel
		void (*pCmdProtocolVersionMatchStatus)(S_PROTOCOL_VERSION_MATCH_SATUS*);
		void (*pCmdMDInfro)(S_MD_INFO*);
		void (*pCmdMDBTPairInfro)(S_BT_PAIR_INFO*);
		void (*pCmdVideoEncoderInitDone)(S_VIDEO_ENCODER_INIT_DONE*);
		void (*pCmdVideoEncoderFrameRateChangeDone)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*);
		void (*pCmdTelStateChangeIncoming)(void);
		void (*pCmdTelStateChangeOutGoing)(void);
		void (*pCmdTelStateChangeIdle)(void);
		void (*pCmdTelStateChangeInCalling)(void);
		void (*pCmdScreenOn)(void);
		void (*pCmdScreenOff)(void);
		void (*pCmdScreenUserPresent)(void);
		void (*pCmdForeground)(void);
		void (*pCmdBackground)(void);
		void (*pCmdGoToDeskTop)(void);
		void (*pCmdMicRecordWakeupStart)(void);
		void (*pCmdMicRecordEnd)(void);
		void (*pCmdMicRecordRecogStart)(void);

		void (*pCmdModuleStatus)(S_MODULE_STATUS_LIST_MOBILE*);
		void (*pCmdNaviNextTurnInfo)(S_NAVI_NEXT_TURN_INFO*);
		void (*pCmdCarDataSubscribe)(S_VEHICLE_INFO_LIST*);
		void (*pCmdCarDataSubscribeStart)(S_VEHICLE_INFO_LIST*);
		void (*pCmdCarDataSubscribeStop)(S_VEHICLE_INFO_LIST*);
		void (*pCmdMediaInfo)(S_MEDIA_INFO*);
		void (*pCmdMediaProgressBar)(S_MEDIA_PROGRESS_BAR*);
		void (*pCmdConnectException)(S_CONNECTION_EXCEPTION*);
		void (*pCmdRequestGoToForeground)();
		void (*pCmdUIActionSound)();

		//added 6th January
		//0x00010040
		void(*pCmdBtHfpRequest)(S_BT_HFP_REQUEST*);
		//0x00010044
		void (*pCmdCarLifeDataSubscribeDone)(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*);
		//0x00010047
		void (*pCmdNaviAssistantGuideInfo)(S_NAVI_ASSITANT_GUIDE_INFO*);
		//0x00010049
		void(*pCmdMdAuthenResponse)(S_AUTHEN_RESPONSE*);
		//0x0001804B
		void (*pCmdMdAuthenResult)(S_MD_AUTHEN_RESULT*);
		//0x0001004C
		void (*pCmdGotoForgroundResponse)(void);
		//0x0001004D
		void (*pCmdStartBtAutoPairRequest)(S_BT_START_PAIR_REQ*);
		//0x0001004F
		void (*pCmdBTHfpStatusRequest)(S_BT_HFP_STATUS_REQUEST*);

		//0x00010051
		void(*pCmdFeatureConfigRequest)(void);
		//0x00010054
		void(*pCmdBTIdentifyResultInd)(S_BT_INDENTIFY_RESULT_IND*);

		//video channel
		void (*pVideoDataReceive)(u8 *data, u32 len);
		void (*pVideoHeartBeat)(void);

		//media channel
		void (*pMediaInit)(S_AUDIO_INIT_PARAMETER*);
		void (*pMediaNormalData)(u8 *data, u32 len);
		void (*pMediaStop)(void);
		void (*pMediaPause)(void);
		void (*pMediaResume)(void);
		void (*pMediaSeek)(void);

		//tts channel
		void (*pTTSInit)(S_AUDIO_INIT_PARAMETER*);
		void (*pTTSNormalData)(u8 *data, u32 len);
		void (*pTTSStop)(void);

		//vr channel
		void (*pVRInit)(S_AUDIO_INIT_PARAMETER*);
		void (*pVRNormalData)(u8 *data, u32 len);
		void (*pVRStop)(void);

		//control channel
		void (*pCtrlUIActionSound)(void);

		//utilities
		void initModuleStatusMobileMemory();
		void initVehicleInfoMemory();

		//used by 0x00010044
		void initSubscribeMobileCarLifeInfoMemory();
};





































#endif








































