/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CCmdChannelModule.h"
#include<iostream>

using namespace std;

CCmdChannelModule* CCmdChannelModule::pInstance=NULL;

CCmdChannelModule* CCmdChannelModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CCmdChannelModule();
		}

	return pInstance;
}

bool CCmdChannelModule::receiveCmdPackageHead(){
	return tranRecvPackageProcess.receivePackageHead();
}

void CCmdChannelModule::cmdPackageHeadAnalysis(){
	tranRecvPackageProcess.packageHeadAnalysis();
}

bool CCmdChannelModule::receiveCmdData(){
	return tranRecvPackageProcess.receivePackageData();
}

void CCmdChannelModule::cmdDataAnalysis(){
	tranRecvPackageProcess.packageDataAnalysis();
}

int CCmdChannelModule::cmdHUProtoclVersion(S_HU_PROTOCOL_VERSION* version){
	return tranRecvPackageProcess.sendCmdHUProtoclVersion(version);
}
int CCmdChannelModule::cmdHUInfro(S_HU_INFO* huInfo){
	return tranRecvPackageProcess.sendCmdHUInfro(huInfo);
}
int CCmdChannelModule::cmdHUBTPairInfro(S_BT_PAIR_INFO* info){
	return tranRecvPackageProcess.cmdHUBTPairInfro(info);
}
int CCmdChannelModule::cmdVideoEncoderInit(S_VIDEO_ENCODER_INIT* initParam){
	return tranRecvPackageProcess.sendCmdVideoEncoderInit(initParam);
}
int CCmdChannelModule::cmdVideoEncoderStart(){
	return tranRecvPackageProcess.sendCmdVideoEncoderStart();
}
int CCmdChannelModule::cmdVideoEncoderPause(){
	return tranRecvPackageProcess.sendCmdVideoEncoderPause();
}
int CCmdChannelModule::cmdVideoEncoderReset(){
	return tranRecvPackageProcess.sendCmdVideoEncoderReset();
}
int CCmdChannelModule::cmdVideoEncoderFrameRateChange(S_VIDEO_ENCODER_FRAME_RATE_CHANGE* videoParam){
	return tranRecvPackageProcess.sendCmdVideoEncoderFrameRateChange(videoParam);
}
int CCmdChannelModule::cmdPauseMedia(){
	return tranRecvPackageProcess.sendCmdPauseMedia();
}
int CCmdChannelModule::cmdCarVelocity(S_CAR_VELOCITY* carVelocity){
	return tranRecvPackageProcess.sendCmdCarVelocity(carVelocity);
}
int CCmdChannelModule::cmdCarGPS(S_CAR_GPS* gps){
	return tranRecvPackageProcess.sendCmdCarGPS(gps);
}
int CCmdChannelModule::cmdCarGyroscope(S_CAR_GYROSCOPE* cyro){
	return tranRecvPackageProcess.sendCmdCarGyroscope(cyro);
}
int CCmdChannelModule::cmdCarAcceleration(S_CAR_ACCELERATION* acceleration){
	return tranRecvPackageProcess.sendCmdCarAcceleration(acceleration);
}
int CCmdChannelModule::cmdCarOil(){
	return tranRecvPackageProcess.sendCmdCarOil();
}
int CCmdChannelModule::cmdLaunchModeNormal(){
	return tranRecvPackageProcess.sendCmdLaunchModeNormal();
}
int CCmdChannelModule::cmdLaunchModePhone(){
	return tranRecvPackageProcess.sendCmdLaunchModePhone();
}
int CCmdChannelModule::cmdLaunchModeMap(){
	return tranRecvPackageProcess.sendCmdLaunchModeMap();
}
int CCmdChannelModule::cmdLaunchModeMusic(){
	return tranRecvPackageProcess.sendCmdLaunchModeMusic();
}

void CCmdChannelModule::cmdRegisterProtocolVersionMatchStatus(void (*pFunc)(S_PROTOCOL_VERSION_MATCH_SATUS*)){
	tranRecvPackageProcess.cmdRegisterProtocolVersionMatchStatus(pFunc);
}

void CCmdChannelModule::cmdRegisterMDInfro(void (*pFunc)(S_MD_INFO*)){
	tranRecvPackageProcess.cmdRegisterMDInfro(pFunc);
}

void CCmdChannelModule::cmdRegisterMDBTPairInfro(void (*pFunc)(S_BT_PAIR_INFO*)){
	tranRecvPackageProcess.cmdRegisterMDBTPairInfro(pFunc);
}

void CCmdChannelModule::cmdRegisterVideoEncoderInitDone(void (*pFunc)(S_VIDEO_ENCODER_INIT_DONE*)){
	tranRecvPackageProcess.cmdRegisterVideoEncoderInitDone(pFunc);
}

void CCmdChannelModule::cmdRegisterVideoEncoderFrameRateChangeDone(void (*pFunc)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*)){
	tranRecvPackageProcess.cmdRegisterVideoEncoderFrameRateChangeDone(pFunc);
}

void CCmdChannelModule::cmdRegisterTelStateChangeIncoming(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterTelStateChangeIncoming(pFunc);
}

void CCmdChannelModule::cmdRegisterTelStateChangeOutGoing(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterTelStateChangeOutGoing(pFunc);
}

void CCmdChannelModule::cmdRegisterTelStateChangeIdle(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterTelStateChangeIdle(pFunc);
}

void CCmdChannelModule::cmdRegisterTelStateChangeInCalling(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterTelStateChangeInCalling(pFunc);
}

void CCmdChannelModule::cmdRegisterScreenOn(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterScreenOn(pFunc);
}

void CCmdChannelModule::cmdRegisterScreenOff(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterScreenOff(pFunc);
}

void CCmdChannelModule::cmdRegisterScreenUserPresent(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterScreenUserPresent(pFunc);
}

void CCmdChannelModule::cmdRegisterForeground(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterForeground(pFunc);
}

void CCmdChannelModule::cmdRegisterBackground(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterBackground(pFunc);
}

void CCmdChannelModule::cmdRegisterGoToDeskTop(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterGoToDeskTop(pFunc);
}

void CCmdChannelModule::cmdRegisterMicRecordWakeupStart(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterMicRecordWakeupStart(pFunc);
}

void CCmdChannelModule::cmdRegisterMicRecordEnd(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterMicRecordEnd(pFunc);
}

void CCmdChannelModule::cmdRegisterMicRecordRecogStart(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterMicRecordRecogStart(pFunc);
}

//added on 9th Semptember 2015
//0x00018025
int CCmdChannelModule::cmdGoToForeground(){
	return tranRecvPackageProcess.cmdGoToForeground();
}

//0x00010026
void CCmdChannelModule::cmdRegisterModuleStatus(void (*pFunc)(S_MODULE_STATUS_LIST_MOBILE*)){
	tranRecvPackageProcess.cmdRegisterModuleStatus(pFunc);
}

//0x00018027
int CCmdChannelModule::cmdStatisticInfo(S_STATISTICS_INFO* statisticsInfo){
	return tranRecvPackageProcess.cmdStatisticInfo(statisticsInfo);
}

//0x00018028
int CCmdChannelModule::cmdModuleControl(S_MODULE_STATUS_CONTROL* status){
	return tranRecvPackageProcess.cmdModuleControl(status);
}

//0x00018029
int CCmdChannelModule::cmdCarDataGear(S_GEAR_INFO* info){
	return tranRecvPackageProcess.cmdCarDataGear(info);
}

//0x00010030
void CCmdChannelModule::cmdRegisterNaviNextTurnInfo(void (*pFunc)(S_NAVI_NEXT_TURN_INFO*)){
	tranRecvPackageProcess.cmdRegisterNaviNextTurnInfo(pFunc);
}

//0x00010031
void CCmdChannelModule::cmdRegisterCarDataSubscribe(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	tranRecvPackageProcess.cmdRegisterCarDataSubscribe(pFunc);
}

//0x00018032
int CCmdChannelModule::cmdCarDataSubscribeDone(S_VEHICLE_INFO_LIST* list){
	return tranRecvPackageProcess.cmdCarDataSubscribeDone(list);
}

//0x00010033
void CCmdChannelModule::cmdRegisterCarDataSubscribeStart(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	tranRecvPackageProcess.cmdRegisterCarDataSubscribeStart(pFunc);
}

//0x00010034
void CCmdChannelModule::cmdRegisterCarDataSubscribeStop(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	tranRecvPackageProcess.cmdRegisterCarDataSubscribeStop(pFunc);
}

//0x00010035
void CCmdChannelModule::cmdRegisterMediaInfo(void (*pFunc)(S_MEDIA_INFO*)){
	tranRecvPackageProcess.cmdRegisterMediaInfo(pFunc);
}

//0x00010036
void CCmdChannelModule::cmdRegisterMediaProgressBar(void (*pFunc)(S_MEDIA_PROGRESS_BAR*)){
	tranRecvPackageProcess.cmdRegisterMediaProgressBar(pFunc);
}

//0x00010037
void CCmdChannelModule::cmdRegisterConnectException(void (*pFunc)(S_CONNECTION_EXCEPTION*)){
	tranRecvPackageProcess.cmdRegisterConnectException(pFunc);
}

//0x00010038
void CCmdChannelModule::cmdRegisterRequestGoToForeground(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterRequestGoToForeground(pFunc);
}

//0x00010039
void CCmdChannelModule::cmdRegisterUIActionSound(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterUIActionSound(pFunc);
}

//added on 5th January 2016
//0x00010040
void CCmdChannelModule::cmdRegisterBtHfpRequest(void (*pFunc)(S_BT_HFP_REQUEST*)){
	tranRecvPackageProcess.cmdRegisterBtHfpRequest(pFunc);
}

//0x00018041
int CCmdChannelModule::cmdBtHfpIndication(S_BT_HFP_INDICATION* indication){
	return tranRecvPackageProcess.cmdBtHfpIndication(indication);
}

//0x00018042
int CCmdChannelModule::cmdBtHfpConnection(S_BT_HFP_CONNECTION* connection){
	return tranRecvPackageProcess.cmdBtHfpConnection(connection);
}

//0x00018043 
int CCmdChannelModule::cmdCarLifeDataSubscribe(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return tranRecvPackageProcess.cmdCarLifeDataSubscribe(list);
}

//0x00010044 
void CCmdChannelModule::cmdRegisterCarLifeDataSubscribeDone(void (*pFunc)(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*)){
	tranRecvPackageProcess.cmdRegisterCarLifeDataSubscribeDone(pFunc);
}

//0x00018045 
int CCmdChannelModule::cmdCarLifeDataSubscribeStart(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return tranRecvPackageProcess.cmdCarLifeDataSubscribeStart(list);
}

//0x00018046 
int CCmdChannelModule::cmdCarLifeDataSubscribeStop(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	return tranRecvPackageProcess.cmdCarLifeDataSubscribeStop(list);
}

//0x00010047 
void CCmdChannelModule::cmdRegisterNaviAssistantGuideInfo(void (*pFunc)(S_NAVI_ASSITANT_GUIDE_INFO*)){
	return tranRecvPackageProcess.cmdRegisterNaviAssistantGuideInfo(pFunc);
}

//0x00018048 
int CCmdChannelModule::cmdHuAuthenRequest(S_AUTHEN_REQUEST* req){
	return tranRecvPackageProcess.cmdHuAuthenRequest(req);
}

//0x00010049 
void CCmdChannelModule::cmdRegisterMdAuthenResponse(void (*pFunc)(S_AUTHEN_RESPONSE*)){
	tranRecvPackageProcess.cmdRegisterMdAuthenResponse(pFunc);
}

//0x0001804A 
int CCmdChannelModule::cmdHuAuthenResult(S_HU_AUTHEN_RESULT* result){
	return tranRecvPackageProcess.cmdHuAuthenResult(result);
}

//0x0001804B
void CCmdChannelModule::cmdRegisterMdAuthenResult(void (*pFunc)(S_MD_AUTHEN_RESULT*)){
	tranRecvPackageProcess.cmdRegisterMdAuthenResult(pFunc);
}

//0x0001004C 
void CCmdChannelModule::cmdRegisterGotoForgroundResponse(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterGotoForgroundResponse(pFunc);
}

//0x0001004D 
void CCmdChannelModule::cmdRegisterStartBtAutoPairRequest(void (*pFunc)(S_BT_START_PAIR_REQ*)){
	tranRecvPackageProcess.cmdRegisterStartBtAutoPairRequest(pFunc);
}

//0x0001804E
int CCmdChannelModule::cmdBTHfpResponse(S_BT_HFP_RESPONSE* rep){
	return tranRecvPackageProcess.cmdBTHfpResponse(rep);
}

//0x0001004F
void CCmdChannelModule::cmdRegisterBTHfpStatusRequest(void (*pFunc)(S_BT_HFP_STATUS_REQUEST*)){
	tranRecvPackageProcess.cmdRegisterBTHfpStatusRequest(pFunc);
}

//0x00018050
int CCmdChannelModule::cmdBTHfpStatusResponse(S_BT_HFP_STATUS_RESPONSE* rep){
	return tranRecvPackageProcess.cmdBTHfpStatusResponse(rep);
}

//added on 3th March 2016
//0x00010051
void CCmdChannelModule::cmdRegisterFeatureConfigRequest(void (*pFunc)(void)){
	tranRecvPackageProcess.cmdRegisterFeatureConfigRequest(pFunc);
}

//0x00018052
int CCmdChannelModule::cmdFeatureConfigResponse(S_FEATURE_CONFIG_LIST* list){
	return tranRecvPackageProcess.cmdFeatureConfigResponse(list);
}

//0x00018053
int CCmdChannelModule::cmdBTStartIdentifyReq(S_BT_START_IDENTIFY_REQ* req){
	return tranRecvPackageProcess.cmdBTStartIdentifyReq(req);
}

//0x00010054
void CCmdChannelModule::cmdRegisterBTIdentifyResultInd(void (*pFunc)(S_BT_INDENTIFY_RESULT_IND*)){
	tranRecvPackageProcess.cmdRegisterBTIdentifyResultInd(pFunc);
}

//0x00018055
int CCmdChannelModule::cmdErrorCode(S_ERROR_CODE* errorCode){
	return tranRecvPackageProcess.cmdErrorCode(errorCode);
}






