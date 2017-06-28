/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_CARLIFE_LIB_H
#define C_CARLIFE_LIB_H
#include"CConnectionSetupModule.h"
#include"CCmdChannelModule.h"
#include"CVideoChannelModule.h"
#include"CMediaChannelModule.h"
#include"CTTSChannelModule.h"
#include"CVRChannelModule.h"
#include"CCtrlChannelModule.h"
#include"CommonUtil.h"
#include"CConnectManager.h"
#include"CVirtualShell.h"

#include<iostream>
#include<string>
using namespace std;

/**********************************************************
CLASS
**********************************************************/
class CCarLifeLib{
public:
	~CCarLifeLib();
/*==============================================
				initialization process
===============================================*/
	static CCarLifeLib* getInstance();
	int carLifeLibInit();
	void carLifeLibDestory();
	
/*=====================================================
			connection between head unit and mobile phone
=======================================================*/
	int connectionSetup();
	int connectionSetup(string mdIP);
	int connectionSetup(string mdIP, string interfaceName);

/*==============================================================
		command channel: send method && receive call back register method
===============================================================*/
	int cmdHUProtoclVersion(S_HU_PROTOCOL_VERSION* version);
	int cmdHUInfro(S_HU_INFO* huInfo);
	int cmdHUBTPairInfro(S_BT_PAIR_INFO* info);
	int cmdVideoEncoderInit(S_VIDEO_ENCODER_INIT* initParam);
	int cmdVideoEncoderStart();
	int cmdVideoEncoderPause();
	int cmdVideoEncoderReset();
	int cmdVideoEncoderFrameRateChange(S_VIDEO_ENCODER_FRAME_RATE_CHANGE* videoParam);
	int cmdPauseMedia();
	int cmdCarVelocity(S_CAR_VELOCITY* carVelocity);
	int cmdCarGPS(S_CAR_GPS* cps);
	int cmdCarGyroscope(S_CAR_GYROSCOPE* cyro);
	int cmdCarAcceleration(S_CAR_ACCELERATION* acceleration);
	int cmdCarOil();
	int cmdLaunchModeNormal();
	int cmdLaunchModePhone();
	int cmdLaunchModeMap();
	int cmdLaunchModeMusic();
	int cmdReceiveOperation();
	void cmdRegisterProtocolVersionMatchStatus(void (*pFunc)(S_PROTOCOL_VERSION_MATCH_SATUS*));
	void cmdRegisterMDInfro(void (*pFunc)(S_MD_INFO*));
	void cmdRegisterMDBTPairInfro(void (*pFunc)(S_BT_PAIR_INFO*));
	void cmdRegisterVideoEncoderInitDone(void (*pFunc)(S_VIDEO_ENCODER_INIT_DONE*));
	void cmdRegisterVideoEncoderFrameRateChangeDone(void (*pFunc)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*));
	void cmdRegisterTelStateChangeIncoming(void (*pFunc)(void));
	void cmdRegisterTelStateChangeOutGoing(void (*pFunc)(void));
	void cmdRegisterTelStateChangeIdle(void (*pFunc)(void));
	void cmdRegisterTelStateChangeInCalling(void (*pFunc)(void));
	void cmdRegisterScreenOn(void (*pFunc)(void));
	void cmdRegisterScreenOff(void (*pFunc)(void));
	void cmdRegisterScreenUserPresent(void (*pFunc)(void));
	void cmdRegisterForeground(void (*pFunc)(void));
	void cmdRegisterBackground(void (*pFunc)(void));
	void cmdRegisterGoToDeskTop(void (*pFunc)(void));
	void cmdRegisterMicRecordWakeupStart(void (*pFunc)(void));
	void cmdRegisterMicRecordEnd(void (*pFunc)(void));
	void cmdRegisterMicRecordRecogStart(void (*pFunc)(void));

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

/*=============================================================
				video channel: receive call back register method
==============================================================*/
	int videoReceiveOperation();
	void videoRegisterDataReceive(void (*pFunc)(u8 *data, u32 len));
	void videoRegisterHeartBeat(void (*pFunc)(void));

/*=============================================================
				media channel: receive call back register method
==============================================================*/
	int mediaReceiveOperation();
	void mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
	void mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
	void mediaRegisterStop(void (*pFunc)(void));
	void mediaRegisterPause(void (*pFunc)(void));
	void mediaRegisterResume(void (*pFunc)(void));
	void mediaRegisterSeek(void (*pFunc)(void));
	
/*=============================================================
				tts channel: receive call back register method
==============================================================*/
	int ttsReceiveOperation();
	void ttsRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
	void ttsRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
	void ttsRegisterStop(void (*pFunc)(void));

/*=============================================================
				vr channel: send method
==============================================================*/
	int sendVRRecordData(u8* data, u32 size, u32 timeStamp);
	int vrReceiveOperation();
	void vrRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
	void vrRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
	void vrRegisterStop(void (*pFunc)(void));

/*=============================================================
				control channel: send method
==============================================================*/
	int ctrlTouchAction(S_TOUCH_ACTION* touchAction);
	int ctrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown);
	int ctrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp);
	int ctrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove);
	int ctrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick);
	int ctrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick);
	int ctrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress);
	int ctrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode);
	int ctrlReceiveOperation();
	void ctrlRegisterUIActionSound(void (*pFunc)(void));
private:
	CCarLifeLib();
	static CCarLifeLib* pInstance;

};


























#endif









