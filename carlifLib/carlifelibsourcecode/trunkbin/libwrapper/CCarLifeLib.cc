/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CCarLifeLib.h"
#include <utils/Log.h>

CConnectionSetupModule* pCConnectionSetupModule=NULL;
CCmdChannelModule* pCCmdChannelModule=NULL;
CVideoChannelModule* pCVideoChannelModule=NULL;
CMediaChannelModule* pCMediaChannelModule=NULL;
CTTSChannelModule* pCTTSChannelModule=NULL;
CVRChannelModule* pCVRChannelModule=NULL;
CCtrlChannelModule* pCCtrlChannelModule=NULL;

CCarLifeLib* CCarLifeLib::pInstance=NULL;

CCarLifeLib::CCarLifeLib(){
	pCConnectionSetupModule=CConnectionSetupModule::getInstance();
	pCCmdChannelModule=CCmdChannelModule::getInstance();
	pCVideoChannelModule=CVideoChannelModule::getInstance();
	pCMediaChannelModule=CMediaChannelModule::getInstance();
	pCTTSChannelModule=CTTSChannelModule::getInstance();
	pCVRChannelModule=CVRChannelModule::getInstance();
	pCCtrlChannelModule=CCtrlChannelModule::getInstance();
}

CCarLifeLib::~CCarLifeLib(){
	delete pCConnectionSetupModule;
	pCConnectionSetupModule=NULL;

	delete pCCmdChannelModule;
	pCCmdChannelModule=NULL;
	
	delete pCVideoChannelModule;
	pCVideoChannelModule=NULL;
	
	delete pCMediaChannelModule;
	pCMediaChannelModule=NULL;
	
	delete pCTTSChannelModule;
	pCTTSChannelModule=NULL;
	
	delete pCVRChannelModule;
	pCVRChannelModule=NULL;
	
	delete pCCtrlChannelModule;
	pCCtrlChannelModule=NULL;

	CConnectManager *pCConnectManager=CConnectManager::getInstance();
	delete pCConnectManager;

	CVirtualShell *pCVirtualShell=CVirtualShell::getInstance();
	delete pCVirtualShell;
}

CCarLifeLib* CCarLifeLib::getInstance(){
	if(NULL==pInstance){
		pInstance=new CCarLifeLib();
		}

	return pInstance;
}

int CCarLifeLib::carLifeLibInit(){
	return 0;
}

void CCarLifeLib::carLifeLibDestory(){
	delete pInstance;
}

int CCarLifeLib::connectionSetup(){
	return pCConnectionSetupModule->connectionSetup();
}

int CCarLifeLib::connectionSetup(string mdIP){
	return pCConnectionSetupModule->connectionSetup(mdIP);
}

int CCarLifeLib::connectionSetup(string mdIP, string interfaceName){
	return pCConnectionSetupModule->connectionSetup(mdIP, interfaceName);
}

//
int CCarLifeLib::cmdHUProtoclVersion(S_HU_PROTOCOL_VERSION* version){
	return pCCmdChannelModule->cmdHUProtoclVersion(version);
}
int CCarLifeLib::cmdHUInfro(S_HU_INFO* huInfo){
	return pCCmdChannelModule->cmdHUInfro(huInfo);
}
int CCarLifeLib::cmdHUBTPairInfro(S_BT_PAIR_INFO* info){
	return pCCmdChannelModule->cmdHUBTPairInfro(info);
}
int CCarLifeLib::cmdVideoEncoderInit(S_VIDEO_ENCODER_INIT* initParam){
	return pCCmdChannelModule->cmdVideoEncoderInit(initParam);
}
int CCarLifeLib::cmdVideoEncoderStart(){
	return pCCmdChannelModule->cmdVideoEncoderStart();
}
int CCarLifeLib::cmdVideoEncoderPause(){
	return pCCmdChannelModule->cmdVideoEncoderPause();
}
int CCarLifeLib::cmdVideoEncoderReset(){
	return pCCmdChannelModule->cmdVideoEncoderReset();
}
int CCarLifeLib::cmdVideoEncoderFrameRateChange(S_VIDEO_ENCODER_FRAME_RATE_CHANGE* videoParam){
	return pCCmdChannelModule->cmdVideoEncoderFrameRateChange(videoParam);
}
int CCarLifeLib::cmdPauseMedia(){
	return pCCmdChannelModule->cmdPauseMedia();
}
int CCarLifeLib::cmdCarVelocity(S_CAR_VELOCITY* carVelocity){
	return pCCmdChannelModule->cmdCarVelocity(carVelocity);
}
int CCarLifeLib::cmdCarGPS(S_CAR_GPS* cps){
	return pCCmdChannelModule->cmdCarGPS(cps);
}
int CCarLifeLib::cmdCarGyroscope(S_CAR_GYROSCOPE* cyro){
	return pCCmdChannelModule->cmdCarGyroscope(cyro);
}
int CCarLifeLib::cmdCarAcceleration(S_CAR_ACCELERATION* acceleration){
	return pCCmdChannelModule->cmdCarAcceleration(acceleration);
}
int CCarLifeLib::cmdCarOil(){
	return pCCmdChannelModule->cmdCarOil();
}
int CCarLifeLib::cmdLaunchModeNormal(){
	return pCCmdChannelModule->cmdLaunchModeNormal();
}
int CCarLifeLib::cmdLaunchModePhone(){
	return pCCmdChannelModule->cmdLaunchModePhone();
}
int CCarLifeLib::cmdLaunchModeMap(){
	return pCCmdChannelModule->cmdLaunchModeMap();
}
int CCarLifeLib::cmdLaunchModeMusic(){
	return pCCmdChannelModule->cmdLaunchModeMusic();
}

int CCarLifeLib::cmdReceiveOperation(){
	if(!pCCmdChannelModule->receiveCmdPackageHead()){
		return -1;
		}
	pCCmdChannelModule->cmdPackageHeadAnalysis();

	if(!pCCmdChannelModule->receiveCmdData()){
		return -1;
		}
	pCCmdChannelModule->cmdDataAnalysis();

	return 0;
}

void CCarLifeLib::cmdRegisterProtocolVersionMatchStatus(void (*pFunc)(S_PROTOCOL_VERSION_MATCH_SATUS*)){
	pCCmdChannelModule->cmdRegisterProtocolVersionMatchStatus(pFunc);
}

void CCarLifeLib::cmdRegisterMDInfro(void (*pFunc)(S_MD_INFO*)){
	pCCmdChannelModule->cmdRegisterMDInfro(pFunc);
}

void CCarLifeLib::cmdRegisterMDBTPairInfro(void (*pFunc)(S_BT_PAIR_INFO*)){
	pCCmdChannelModule->cmdRegisterMDBTPairInfro(pFunc);
}

void CCarLifeLib::cmdRegisterVideoEncoderInitDone(void (*pFunc)(S_VIDEO_ENCODER_INIT_DONE*)){
	pCCmdChannelModule->cmdRegisterVideoEncoderInitDone(pFunc);
}

void CCarLifeLib::cmdRegisterVideoEncoderFrameRateChangeDone(void (*pFunc)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*)){
	pCCmdChannelModule->cmdRegisterVideoEncoderFrameRateChangeDone(pFunc);
}

void CCarLifeLib::cmdRegisterTelStateChangeIncoming(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterTelStateChangeIncoming(pFunc);
}

void CCarLifeLib::cmdRegisterTelStateChangeOutGoing(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterTelStateChangeOutGoing(pFunc);
}

void CCarLifeLib::cmdRegisterTelStateChangeIdle(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterTelStateChangeIdle(pFunc);
}

void CCarLifeLib::cmdRegisterTelStateChangeInCalling(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterTelStateChangeInCalling(pFunc);
}

void CCarLifeLib::cmdRegisterScreenOn(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterScreenOn(pFunc);
}

void CCarLifeLib::cmdRegisterScreenOff(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterScreenOff(pFunc);
}

void CCarLifeLib::cmdRegisterScreenUserPresent(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterScreenUserPresent(pFunc);
}

void CCarLifeLib::cmdRegisterForeground(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterForeground(pFunc);
}

void CCarLifeLib::cmdRegisterBackground(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterBackground(pFunc);
}

void CCarLifeLib::cmdRegisterGoToDeskTop(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterGoToDeskTop(pFunc);
}

void CCarLifeLib::cmdRegisterMicRecordWakeupStart(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterMicRecordWakeupStart(pFunc);
}
void CCarLifeLib::cmdRegisterMicRecordEnd(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterMicRecordEnd(pFunc);
}

void CCarLifeLib::cmdRegisterMicRecordRecogStart(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterMicRecordRecogStart(pFunc);
}

int CCarLifeLib::videoReceiveOperation(){
	if(!pCVideoChannelModule->receiveVideoPackageHead()){
		return -1;
		}
	pCVideoChannelModule->videoPackageHeadAnalysis();

	if(!pCVideoChannelModule->receiveVideoData()){
		return -1;
		}
	pCVideoChannelModule->videoDataAnalysis();

	return 0;
}

void CCarLifeLib::videoRegisterDataReceive(void (*pFunc)(u8 *data, u32 len)){
	pCVideoChannelModule->videoRegisterDataReceive(pFunc);
}

void CCarLifeLib::videoRegisterHeartBeat(void (*pFunc)(void)){
	pCVideoChannelModule->videoRegisterHeartBeat(pFunc);
}

int CCarLifeLib::mediaReceiveOperation(){
	if(!pCMediaChannelModule->receiveMediaPackageHead()){
		return -1;
		}
	pCMediaChannelModule->mediaPackageHeadAnalysis();
	if(!pCMediaChannelModule->receiveMediaData()){
		return -1;
		}
	pCMediaChannelModule->mediaDataAnalysis();

	return 0;
}

void CCarLifeLib::mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pCMediaChannelModule->mediaRegisterInit(pFunc);
}

void CCarLifeLib::mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pCMediaChannelModule->mediaRegisterNormalData(pFunc);
}

void CCarLifeLib::mediaRegisterStop(void (*pFunc)(void)){
	pCMediaChannelModule->mediaRegisterStop(pFunc);
}
void CCarLifeLib::mediaRegisterPause(void (*pFunc)(void)){
	pCMediaChannelModule->mediaRegisterPause(pFunc);
}
void CCarLifeLib::mediaRegisterResume(void (*pFunc)(void)){
	pCMediaChannelModule->mediaRegisterResume(pFunc);
}
void CCarLifeLib::mediaRegisterSeek(void (*pFunc)(void)){
	pCMediaChannelModule->mediaRegisterSeek(pFunc);
}

int CCarLifeLib::ttsReceiveOperation(){
	if(!pCTTSChannelModule->receiveTTSPackageHead()){
		return -1;
		}
	pCTTSChannelModule->ttsPackageHeadAnalysis();

	if(!pCTTSChannelModule->receiveTTSData()){
		return -1;
		}
	pCTTSChannelModule->ttsDataAnalysis();

	return 0;
}

void CCarLifeLib::ttsRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pCTTSChannelModule->ttsRegisterInit(pFunc);
}

void CCarLifeLib::ttsRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pCTTSChannelModule->ttsRegisterNormalData(pFunc);
}

void CCarLifeLib::ttsRegisterStop(void (*pFunc)(void)){
	pCTTSChannelModule->ttsRegisterStop(pFunc);
}

int CCarLifeLib::sendVRRecordData(u8* data, u32 size, u32 timeStamp){
	return pCVRChannelModule->sendVRRecordData(data, size, timeStamp);
}

int CCarLifeLib::vrReceiveOperation(){
	if(!pCVRChannelModule->receiveVRPackageHead()){
		return -1;
		}
	pCVRChannelModule->vrPackageHeadAnalysis();

	if(!pCVRChannelModule->receiveVRData()){
		return -1;
		}
	pCVRChannelModule->vrDataAnalysis();

	return 0;
}

void CCarLifeLib::vrRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pCVRChannelModule->vrRegisterInit(pFunc);
}

void CCarLifeLib::vrRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pCVRChannelModule->vrRegisterNormalData(pFunc);
}

void CCarLifeLib::vrRegisterStop(void (*pFunc)(void)){
	pCVRChannelModule->vrRegisterStop(pFunc);
}

int CCarLifeLib::ctrlTouchAction(S_TOUCH_ACTION* touchAction){
	return pCCtrlChannelModule->ctrlTouchAction(touchAction);
}

int CCarLifeLib::ctrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown){
	return pCCtrlChannelModule->ctrlTouchActionDown(touchActionDown);
}

int CCarLifeLib::ctrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp){
	return pCCtrlChannelModule->ctrlTouchActionUp(touchActionUp);
}

int CCarLifeLib::ctrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove){
	return pCCtrlChannelModule->ctrlTouchActionMove(touchActionMove);
}

int CCarLifeLib::ctrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick){
	return pCCtrlChannelModule->ctrlTouchSigleClick(touchSingleClick);
}

int CCarLifeLib::ctrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick){
	return pCCtrlChannelModule->ctrlTouchDoubleClick(touchDoubleClick);
}

int CCarLifeLib::ctrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress){
	return pCCtrlChannelModule->ctrlTouchLongPress(touchLongPress);
}

int CCarLifeLib::ctrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode){
	return pCCtrlChannelModule->ctrlTouchCarHardKeyCode(touchCarHardKeyCode);
}

int CCarLifeLib::ctrlReceiveOperation(){
	if(!pCCtrlChannelModule->receiveCtrlPackageHead()){
		return -1;
		}
	pCCtrlChannelModule->ctrlPackageHeadAnalysis();

	if(!pCCtrlChannelModule->receiveCtrlData()){
		return -1;
		}
	pCCtrlChannelModule->ctrlDataAnalysis();

	return 0;
}
	
void CCarLifeLib::ctrlRegisterUIActionSound(void (*pFunc)(void)){
	pCCtrlChannelModule->ctrlRegisterUIActionSound(pFunc);
}

//added on 9th Semptember 2015
//0x00018025
int CCarLifeLib::cmdGoToForeground(){
	return pCCmdChannelModule->cmdGoToForeground();
}

//0x00010026
void CCarLifeLib::cmdRegisterModuleStatus(void (*pFunc)(S_MODULE_STATUS_LIST_MOBILE*)){
	pCCmdChannelModule->cmdRegisterModuleStatus(pFunc);
}

//0x00018027
int CCarLifeLib::cmdStatisticInfo(S_STATISTICS_INFO* info){
	return pCCmdChannelModule->cmdStatisticInfo(info);
}

//0x00018028
int CCarLifeLib::cmdModuleControl(S_MODULE_STATUS_CONTROL* control){
	 return pCCmdChannelModule->cmdModuleControl(control);
}

//0x00018029
int CCarLifeLib::cmdCarDataGear(S_GEAR_INFO* info){
	return pCCmdChannelModule->cmdCarDataGear(info);
}

//0x00010030
void CCarLifeLib::cmdRegisterNaviNextTurnInfo(void (*pFunc)(S_NAVI_NEXT_TURN_INFO*)){
	pCCmdChannelModule->cmdRegisterNaviNextTurnInfo(pFunc);
}

//0x00010031
void CCarLifeLib::cmdRegisterCarDataSubscribe(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCCmdChannelModule->cmdRegisterCarDataSubscribe(pFunc);
}

//0x00018032
int CCarLifeLib::cmdCarDataSubscribeDone(S_VEHICLE_INFO_LIST* list){
	return pCCmdChannelModule->cmdCarDataSubscribeDone(list);
}

//0x00010033
void CCarLifeLib::cmdRegisterCarDataSubscribeStart(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCCmdChannelModule->cmdRegisterCarDataSubscribeStart(pFunc);
}

//0x00010034
void CCarLifeLib::cmdRegisterCarDataSubscribeStop(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCCmdChannelModule->cmdRegisterCarDataSubscribeStop(pFunc);
}

//0x00010035
void CCarLifeLib::cmdRegisterMediaInfo(void (*pFunc)(S_MEDIA_INFO*)){
	pCCmdChannelModule->cmdRegisterMediaInfo(pFunc);
}

//0x00010036
void CCarLifeLib::cmdRegisterMediaProgressBar(void (*pFunc)(S_MEDIA_PROGRESS_BAR*)){
	pCCmdChannelModule->cmdRegisterMediaProgressBar(pFunc);
}

//0x00010037
void CCarLifeLib::cmdRegisterConnectException(void (*pFunc)(S_CONNECTION_EXCEPTION*)){
	pCCmdChannelModule->cmdRegisterConnectException(pFunc);
}

//0x00010038
void CCarLifeLib::cmdRegisterRequestGoToForeground(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterRequestGoToForeground(pFunc);
}

//0x00010039
void CCarLifeLib::cmdRegisterUIActionSound(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterUIActionSound(pFunc);
}

//added on 5th January 2016
//0x00010040
void CCarLifeLib::cmdRegisterBtHfpRequest(void (*pFunc)(S_BT_HFP_REQUEST*)){
	pCCmdChannelModule->cmdRegisterBtHfpRequest(pFunc);
}

//0x00018041
int CCarLifeLib::cmdBtHfpIndication(S_BT_HFP_INDICATION* indicatioin){
	return pCCmdChannelModule->cmdBtHfpIndication(indicatioin);
}

//0x00018042
int CCarLifeLib::cmdBtHfpConnection(S_BT_HFP_CONNECTION* connection){
	return pCCmdChannelModule->cmdBtHfpConnection(connection);
}

//0x00018043 
int CCarLifeLib::cmdCarLifeDataSubscribe(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return pCCmdChannelModule->cmdCarLifeDataSubscribe(list);
}

//0x00010044 
void CCarLifeLib::cmdRegisterCarLifeDataSubscribeDone(void (*pFunc)(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*)){
	pCCmdChannelModule->cmdRegisterCarLifeDataSubscribeDone(pFunc);
}

//0x00018045 
int CCarLifeLib::cmdCarLifeDataSubscribeStart(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return pCCmdChannelModule->cmdCarLifeDataSubscribeStart(list);
}

//0x00018046 
int CCarLifeLib::cmdCarLifeDataSubscribeStop(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return pCCmdChannelModule->cmdCarLifeDataSubscribeStop(list);
}

//0x00010047 
void CCarLifeLib::cmdRegisterNaviAssistantGuideInfo(void (*pFunc)(S_NAVI_ASSITANT_GUIDE_INFO*)){
	pCCmdChannelModule->cmdRegisterNaviAssistantGuideInfo(pFunc);
}

//0x00018048 
int CCarLifeLib::cmdHuAuthenRequest(S_AUTHEN_REQUEST* req){
	return pCCmdChannelModule->cmdHuAuthenRequest(req);
}

//0x00010049 
void CCarLifeLib::cmdRegisterMdAuthenResponse(void (*pFunc)(S_AUTHEN_RESPONSE*)){
	pCCmdChannelModule->cmdRegisterMdAuthenResponse(pFunc);
}

//0x0001804A 
int CCarLifeLib::cmdHuAuthenResult(S_HU_AUTHEN_RESULT* result){
	return pCCmdChannelModule->cmdHuAuthenResult(result);
}

//0x0001804B
void CCarLifeLib::cmdRegisterMdAuthenResult(void (*pFunc)(S_MD_AUTHEN_RESULT*)){
	pCCmdChannelModule->cmdRegisterMdAuthenResult(pFunc);
}

//0x0001004C 
void CCarLifeLib::cmdRegisterGotoForgroundResponse(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterGotoForgroundResponse(pFunc);
}

//0x0001004D 
void CCarLifeLib::cmdRegisterStartBtAutoPairRequest(void (*pFunc)(S_BT_START_PAIR_REQ*)){
	pCCmdChannelModule->cmdRegisterStartBtAutoPairRequest(pFunc);
}

//0x0001804E
int CCarLifeLib::cmdBTHfpResponse(S_BT_HFP_RESPONSE* rep){
	return pCCmdChannelModule->cmdBTHfpResponse(rep);
}

//0x0001004F
void CCarLifeLib::cmdRegisterBTHfpStatusRequest(void (*pFunc)(S_BT_HFP_STATUS_REQUEST*)){
	pCCmdChannelModule->cmdRegisterBTHfpStatusRequest(pFunc);
}

//0x00018050
int CCarLifeLib::cmdBTHfpStatusResponse(S_BT_HFP_STATUS_RESPONSE* rep){
	return pCCmdChannelModule->cmdBTHfpStatusResponse(rep);
}

//added on 3th March 2016
//0x00010051
void CCarLifeLib::cmdRegisterFeatureConfigRequest(void (*pFunc)(void)){
	pCCmdChannelModule->cmdRegisterFeatureConfigRequest(pFunc);
}

//0x00018052
int CCarLifeLib::cmdFeatureConfigResponse(S_FEATURE_CONFIG_LIST* list){
	return pCCmdChannelModule->cmdFeatureConfigResponse(list);
}

//0x00018053
int CCarLifeLib::cmdBTStartIdentifyReq(S_BT_START_IDENTIFY_REQ* req){
	return pCCmdChannelModule->cmdBTStartIdentifyReq(req);
}

//0x00010054
void CCarLifeLib::cmdRegisterBTIdentifyResultInd(void (*pFunc)(S_BT_INDENTIFY_RESULT_IND*)){
	pCCmdChannelModule->cmdRegisterBTIdentifyResultInd(pFunc);
}

//0x00018055
int CCarLifeLib::cmdErrorCode(S_ERROR_CODE* errorCode){
	return pCCmdChannelModule->cmdErrorCode(errorCode);
}





