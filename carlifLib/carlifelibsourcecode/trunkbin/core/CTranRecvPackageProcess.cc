/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CTranRecvPackageProcess.h"
#include "CConnectManager.h"
#include "CCarLifeLog.h"
#include <string>		
#include "CarlifeAccelerationProto.pb.h"
#include "CarlifeVideoEncoderInfoProto.pb.h"
#include "CarlifeMusicInitProto.pb.h"
#include "CarlifeBTPairInfoProto.pb.h"
#include "CarlifeCallRecordsListProto.pb.h"
#include "CarlifeCallRecordsProto.pb.h"
#include "CarlifeCarGpsProto.pb.h"
#include "CarlifeCarHardKeyCodeProto.pb.h"
#include "CarlifeCarSpeedProto.pb.h"
#include "CarlifeContactsListProto.pb.h"
#include "CarlifeContactsProto.pb.h"
#include "CarlifeDeviceInfoProto.pb.h"
#include "CarlifeGyroscopeProto.pb.h"
#include "CarlifeMediaInfoListProto.pb.h"
#include "CarlifeMediaInfoProto.pb.h"
#include "CarlifeProtocolVersionProto.pb.h"
#include "CarlifeTouchActionProto.pb.h"
#include "CarlifeTouchEventAllDeviceProto.pb.h"
#include "CarlifeTouchEventDeviceProto.pb.h"
#include "CarlifeTouchEventProto.pb.h"
#include "CarlifeTouchFlingProto.pb.h"
#include "CarlifeTouchScrollProto.pb.h"
#include "CarlifeTouchSinglePointProto.pb.h"
#include "CarlifeTTSInitProto.pb.h"
#include "CarlifeVideoFrameRateProto.pb.h"
#include "CarlifeProtocolVersionMatchStatusProto.pb.h"
#include "CarlifeStatisticsInfoProto.pb.h"
#include "CarlifeModuleStatusProto.pb.h"
#include "CarlifeGearInfoProto.pb.h"
#include "CarlifeVehicleInfoProto.pb.h"
#include "CarlifeVehicleInfoListProto.pb.h"
#include "CarlifeModuleStatusProto.pb.h"
#include "CarlifeModuleStatusListProto.pb.h"
#include "CarlifeNaviNextTurnInfoProto.pb.h"
#include "CarlifeMediaInfoProto.pb.h"
#include "CarlifeMediaProgressBarProto.pb.h"
#include "CarlifeConnectExceptionProto.pb.h"

#include "CarlifeAuthenRequestProto.pb.h"
#include "CarlifeAuthenResponseProto.pb.h"
#include "CarlifeAuthenResultProto.pb.h"
#include "CarlifeBTHfpConnectionProto.pb.h"
#include "CarlifeBTHfpIndicationProto.pb.h"
#include "CarlifeBTHfpRequestProto.pb.h"
#include "CarlifeBTHfpResponseProto.pb.h"
#include "CarlifeBTHfpStatusRequestProto.pb.h"
#include "CarlifeBTHfpStatusResponseProto.pb.h"
#include "CarlifeBTStartPairReqProto.pb.h"
#include "CarlifeNaviAssitantGuideInfoProto.pb.h"
#include "CarlifeSubscribeMobileCarLifeInfoListProto.pb.h"
#include "CarlifeSubscribeMobileCarLifeInfoProto.pb.h"

#include "CarlifeBTIdentifyResultIndProto.pb.h"
#include "CarlifeBTStartIdentifyReqProto.pb.h"
#include "CarlifeErrorCodeProto.pb.h"
#include "CarlifeFeatureConfigListProto.pb.h"
#include "CarlifeFeatureConfigProto.pb.h"

#include<coded_stream.h>
#include <utils/Log.h>



using namespace std;
using com::baidu::carlife::protobuf::CarlifeAcceleration;
using com::baidu::carlife::protobuf::CarlifeVideoEncoderInfo;
using com::baidu::carlife::protobuf::CarlifeMusicInit;
using com::baidu::carlife::protobuf::CarlifeBTPairInfo;
using com::baidu::carlife::protobuf::CarlifeCallRecordsList;
using com::baidu::carlife::protobuf::CarlifeCallRecords;
using com::baidu::carlife::protobuf::CarlifeCarGps;
using com::baidu::carlife::protobuf::CarlifeCarHardKeyCode;
using com::baidu::carlife::protobuf::CarlifeCarSpeed;
using com::baidu::carlife::protobuf::CarlifeContactsList;
using com::baidu::carlife::protobuf::CarlifeContacts;
using com::baidu::carlife::protobuf::CarlifeDeviceInfo;
using com::baidu::carlife::protobuf::CarlifeGyroscope;
using com::baidu::carlife::protobuf::CarlifeProtocolVersion;
using com::baidu::carlife::protobuf::CarlifeTouchAction;
using com::baidu::carlife::protobuf::CarlifeTouchEventAllDevice;
using com::baidu::carlife::protobuf::CarlifeTouchEventDevice;
using com::baidu::carlife::protobuf::CarlifeTouchEvent;
using com::baidu::carlife::protobuf::CarlifeTouchFling;
using com::baidu::carlife::protobuf::CarlifeTouchScroll;
using com::baidu::carlife::protobuf::CarlifeTouchSinglePoint;
using com::baidu::carlife::protobuf::CarlifeTTSInit;
using com::baidu::carlife::protobuf::CarlifeVideoFrameRate;
using com::baidu::carlife::protobuf::CarlifeProtocolVersionMatchStatus;

using com::baidu::carlife::protobuf::CarlifeStatisticsInfo;
using com::baidu::carlife::protobuf::CarlifeModuleStatus;
using com::baidu::carlife::protobuf::CarlifeGearInfo;
using com::baidu::carlife::protobuf::CarlifeVehicleInfo;
using com::baidu::carlife::protobuf::CarlifeVehicleInfoList;
using com::baidu::carlife::protobuf::CarlifeModuleStatus;
using com::baidu::carlife::protobuf::CarlifeModuleStatusList;
using com::baidu::carlife::protobuf::CarlifeNaviNextTurnInfo;
using com::baidu::carlife::protobuf::CarlifeMediaInfo;
using com::baidu::carlife::protobuf::CarlifeMediaProgressBar;
using com::baidu::carlife::protobuf::CarlifeConnectException;

using com::baidu::carlife::protobuf::CarlifeBTHfpRequest;
using com::baidu::carlife::protobuf::CarlifeBTHfpIndication;
using com::baidu::carlife::protobuf::CarlifeBTHfpConnection;
using com::baidu::carlife::protobuf::CarlifeSubscribeMobileCarLifeInfo;
using com::baidu::carlife::protobuf::CarlifeSubscribeMobileCarLifeInfoList;
using com::baidu::carlife::protobuf::CarlifeNaviAssitantGuideInfo;
using com::baidu::carlife::protobuf::CarlifeAuthenRequest;
using com::baidu::carlife::protobuf::CarlifeAuthenResponse;
using com::baidu::carlife::protobuf::CarlifeAuthenResult;
using com::baidu::carlife::protobuf::CarlifeBTStartPairReq;
using com::baidu::carlife::protobuf::CarlifeBTHfpResponse;
using com::baidu::carlife::protobuf::CarlifeBTHfpStatusRequest;
using com::baidu::carlife::protobuf::CarlifeBTHfpStatusResponse;

using com::baidu::carlife::protobuf::CarlifeBTIdentifyResultInd;
using com::baidu::carlife::protobuf::CarlifeBTStartIdentifyReq;
using com::baidu::carlife::protobuf::CarlifeErrorCode;
using com::baidu::carlife::protobuf::CarlifeFeatureConfigList;
using com::baidu::carlife::protobuf::CarlifeFeatureConfig;

CTranRecvPackageProcess::CTranRecvPackageProcess(E_CHANNEL_TYPE channelType){
	pCmdProtocolVersionMatchStatus=NULL;
	pCmdMDInfro=NULL;
	pCmdMDBTPairInfro=NULL;
	pCmdVideoEncoderInitDone=NULL;
	pCmdVideoEncoderFrameRateChangeDone=NULL;
	pCmdTelStateChangeIncoming=NULL;
	pCmdTelStateChangeOutGoing=NULL;
	pCmdTelStateChangeIdle=NULL;
	pCmdTelStateChangeInCalling=NULL;
	pCmdScreenOn=NULL;
	pCmdScreenOff=NULL;
	pCmdScreenUserPresent=NULL;
	pCmdForeground=NULL;
	pCmdBackground=NULL;
	pCmdGoToDeskTop=NULL;
	pCmdMicRecordWakeupStart=NULL;
	pCmdMicRecordEnd=NULL;
	pCmdMicRecordRecogStart=NULL;

	pCmdModuleStatus=NULL;
	pCmdNaviNextTurnInfo =NULL;
	pCmdCarDataSubscribe =NULL;
	pCmdCarDataSubscribeStart=NULL;
	pCmdCarDataSubscribeStop=NULL;
	pCmdMediaInfo =NULL;
	pCmdMediaProgressBar =NULL;
	pCmdConnectException =NULL;
	pCmdRequestGoToForeground=NULL;
	pCmdUIActionSound=NULL;

	pVideoDataReceive=NULL;
	pVideoHeartBeat=NULL;

	pMediaInit=NULL;
	pMediaNormalData=NULL;
	pMediaStop=NULL;
	pMediaPause=NULL;
	pMediaResume=NULL;
	pMediaSeek=NULL;

	pTTSInit=NULL;
	pTTSNormalData=NULL;
	pTTSStop=NULL;

	pVRInit=NULL;
	pVRNormalData=NULL;
	pVRStop=NULL;

	pCtrlUIActionSound=NULL;

	pCmdBtHfpRequest=NULL;
	pCmdCarLifeDataSubscribeDone=NULL;
	pCmdNaviAssistantGuideInfo=NULL;
	pCmdMdAuthenResponse=NULL;
	pCmdMdAuthenResult=NULL;
	pCmdGotoForgroundResponse=NULL;
	pCmdStartBtAutoPairRequest=NULL;
	pCmdBTHfpStatusRequest=NULL;

	pCmdFeatureConfigRequest=NULL;
	pCmdBTIdentifyResultInd=NULL;
	
	switch(channelType){
		case CMD_CHANNEL:
			channel= CMD_CHANNEL;
			recvPackage.packageHead= new u8[CMD_HEAD_LEN];
			recvPackage.packageData= new u8[CMD_DATA_SIZE];

			sendPackage.packageHead= new u8[CMD_HEAD_LEN];
			sendPackage.packageData= new u8[CMD_DATA_SIZE];
			break;

		case VIDEO_CHANNEL:
			channel= VIDEO_CHANNEL;
			recvPackage.packageHead= new u8[VIDEO_HEAD_LEN];
			recvPackage.packageData= new u8[VIDEO_DATA_SIZE];

			sendPackage.packageHead= new u8[VIDEO_HEAD_LEN];
			sendPackage.packageData= new u8[VIDEO_DATA_SIZE];
			break;

		case MEDIA_CHANNEL:
			channel= MEDIA_CHANNEL;

			recvPackage.packageHead= new u8[MEDIA_HEAD_LEN];
			recvPackage.packageData= new u8[MEDIA_DATA_SIZE];

			sendPackage.packageHead= new u8[MEDIA_HEAD_LEN];
			sendPackage.packageData= new u8[MEDIA_DATA_SIZE];
			break;

		case TTS_CHANNEL:
			channel= TTS_CHANNEL;

			recvPackage.packageHead= new u8[TTS_HEAD_LEN];
			recvPackage.packageData= new u8[TTS_DATA_SIZE];

			sendPackage.packageHead= new u8[TTS_HEAD_LEN];
			sendPackage.packageData= new u8[TTS_DATA_SIZE];
			break;

		case VR_CHANNEL:
			channel= VR_CHANNEL;

			recvPackage.packageHead= new u8[VR_HEAD_LEN];
			recvPackage.packageData= new u8[VR_DATA_SIZE];

			sendPackage.packageHead= new u8[VR_HEAD_LEN];
			sendPackage.packageData= new u8[VR_DATA_SIZE];
			break;

		case CTRL_CHANNEL:
			channel= CTRL_CHANNEL;

			recvPackage.packageHead= new u8[CTRL_HEAD_LEN];
			recvPackage.packageData= new u8[CTRL_DATA_SIZE];

			sendPackage.packageHead= new u8[CTRL_HEAD_LEN];
			sendPackage.packageData= new u8[CTRL_DATA_SIZE];
			break;

		default:
			recvPackage.packageHead= new u8[DEFAULT_HEAD_LEN];
			recvPackage.packageData= new u8[DEFAULT_DATA_SIZE];

			sendPackage.packageHead= new u8[DEFAULT_HEAD_LEN];
			sendPackage.packageData= new u8[DEFAULT_DATA_SIZE];
			break;
		}


	initModuleStatusMobileMemory();
	initVehicleInfoMemory();
	initSubscribeMobileCarLifeInfoMemory();
}

CTranRecvPackageProcess::~CTranRecvPackageProcess(){
	delete[] recvPackage.packageHead;
	delete[] recvPackage.packageData;

	delete[] sendPackage.packageHead;
	delete[] sendPackage.packageData;
}

bool CTranRecvPackageProcess::receivePackageHead(){
	switch(channel){
		case CMD_CHANNEL:
			if(!CConnectManager::getInstance()->readCmdData(recvPackage.packageHead,CMD_HEAD_LEN)){
				CCarLifeLog::carLifeLogLnWithPrefix("-> cmd package head is failed");
					return false;
			}

			CCarLifeLog::carLifeLogLnWithPrefix("-> cmd package head is received");
			break;

		case VIDEO_CHANNEL:
			if(!CConnectManager::getInstance()->readVideoData(recvPackage.packageHead,VIDEO_HEAD_LEN)){
				CCarLifeLog::carLifeLogLnWithPrefix("-> video package head is failed");
				return false;
			}
			CCarLifeLog::carLifeLogLnWithPrefix("-> video package head is received");
			break;

		case MEDIA_CHANNEL:
			if(!CConnectManager::getInstance()->readMediaData(recvPackage.packageHead,MEDIA_HEAD_LEN)){
				CCarLifeLog::carLifeLogLnWithPrefix("-> media package head is failed");
				return false;
			}
			CCarLifeLog::carLifeLogLnWithPrefix("-> media package head is received");
			break;

		case TTS_CHANNEL:
			if(!CConnectManager::getInstance()->readTTSData(recvPackage.packageHead,TTS_HEAD_LEN)){
				CCarLifeLog::carLifeLogLnWithPrefix("-> tts package head is failed");
				return false;
			}

			CCarLifeLog::carLifeLogLnWithPrefix("-> tts package head is received");
			break;

		case VR_CHANNEL:
			if(!CConnectManager::getInstance()->readVRData(recvPackage.packageHead,VR_HEAD_LEN)){
				CCarLifeLog::carLifeLogLnWithPrefix("-> vr package head is failed");
				return false;
			}

			CCarLifeLog::carLifeLogLnWithPrefix("-> vr package head is received");
			break;

		default:
			CCarLifeLog::carLifeLogLnWithPrefix("-> no receive channel is choosed!");
			break;
		}
	return true;
}

void CTranRecvPackageProcess::packageHeadAnalysis(){
	u32 dataHH=0;
	u32 dataHL=0;
	u32 dataLH=0;
	u32 dataLL=0;
	//analyzedHead.packageDataSize
	if(CMD_CHANNEL==channel ||CTRL_CHANNEL==channel){
		dataHH = (recvPackage.packageHead[0] & 0xff);
		dataHL = (recvPackage.packageHead[1] & 0xff);

		analyzedHead.packageDataSize= ((dataHH << 8) & 0x0000ff00) | ((dataHL) & 0x000000ff);
		}else{
				dataHH = (recvPackage.packageHead[0] & 0xff);
				dataHL = (recvPackage.packageHead[1] & 0xff);
				dataLH = (recvPackage.packageHead[2] & 0xff);
				dataLL = (recvPackage.packageHead[3] & 0xff);
	
				analyzedHead.packageDataSize= ((dataHH << 24) & 0xff000000) | ((dataHL << 16) & 0x00ff0000)
						| ((dataLH << 8) & 0x0000ff00) | ((dataLL) & 0x000000ff);
			}
		CCarLifeLog::carLifeLogWithPrefix("analyzedHead.packageDataSize: ");
		CCarLifeLog::carLifeLog(analyzedHead.packageDataSize);
		CCarLifeLog::carLifeLog("\n");
		
	//analyzedHead.packageDataTimeStamp(for cmd and ctrl channel, this field is reserved )
	if(CMD_CHANNEL==channel ||CTRL_CHANNEL==channel){
		analyzedHead.packageDataTimeStamp=0;
		}else{
				dataHH = (recvPackage.packageHead[4] & 0xff);
				dataHL = (recvPackage.packageHead[5] & 0xff);
				dataLH = (recvPackage.packageHead[6] & 0xff);
				dataLL = (recvPackage.packageHead[7] & 0xff);

				analyzedHead.packageDataTimeStamp= ((dataHH << 24) & 0xff000000) | ((dataHL << 16) & 0x00ff0000)
						| ((dataLH << 8) & 0x0000ff00) | ((dataLL) & 0x000000ff);
			}
		CCarLifeLog::carLifeLogWithPrefix("analyzedHead.packageDataTimeStamp: ");
		CCarLifeLog::carLifeLog(analyzedHead.packageDataTimeStamp);
		CCarLifeLog::carLifeLog("\n");

	//analyzedHead.packageHeadType
	u32 type;
	if(CMD_CHANNEL==channel ||CTRL_CHANNEL==channel){
		dataHH = (recvPackage.packageHead[4] & 0xff);
		dataHL = (recvPackage.packageHead[5] & 0xff);
		dataLH = (recvPackage.packageHead[6] & 0xff);
		dataLL = (recvPackage.packageHead[7] & 0xff);
		}else{
				dataHH = (recvPackage.packageHead[8] & 0xff);
				dataHL = (recvPackage.packageHead[9] & 0xff);
				dataLH = (recvPackage.packageHead[10] & 0xff);
				dataLL = (recvPackage.packageHead[11] & 0xff);
			}
	

	type = ((dataHH << 24) & 0xff000000) | ((dataHL << 16) & 0x00ff0000)
			| ((dataLH << 8) & 0x0000ff00) | ((dataLL) & 0x000000ff);

	switch (type) {
		//cmd channel
		case MSG_CMD_PROTOCOL_VERSION_MATCH_STATUS:
			analyzedHead.packageHeadType=MSG_CMD_PROTOCOL_VERSION_MATCH_STATUS;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_PROTOCOL_VERSION_MATCH_STATUS");
			break;

		case MSG_CMD_MD_INFO:
			analyzedHead.packageHeadType=MSG_CMD_MD_INFO;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MD_INFO");
			break;

		case MSG_CMD_MD_BT_PAIR_INFO:
			analyzedHead.packageHeadType=MSG_CMD_MD_BT_PAIR_INFO;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MD_BT_PAIR_INFOs");
			break;

		case MSG_CMD_VIDEO_ENCODER_INIT_DONE:
			analyzedHead.packageHeadType=MSG_CMD_VIDEO_ENCODER_INIT_DONE;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_VIDEO_ENCODER_INIT_DONE");
			break;

		case MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE:
			analyzedHead.packageHeadType=MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE");

			break;

		case MSG_CMD_TELE_STATE_CHANGE_INCOMING:
			analyzedHead.packageHeadType=MSG_CMD_TELE_STATE_CHANGE_INCOMING;

			//invoke registered callback function
			if(pCmdTelStateChangeIncoming!=NULL){
				pCmdTelStateChangeIncoming();
				}
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_TELE_STATE_CHANGE_INCOMING");
			break;

		case MSG_CMD_TELE_STATE_CHANGE_OUTGOING:
			analyzedHead.packageHeadType=MSG_CMD_TELE_STATE_CHANGE_OUTGOING;

			//invoke registered callback function
			if(pCmdTelStateChangeOutGoing!=NULL){
				pCmdTelStateChangeOutGoing();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_TELE_STATE_CHANGE_OUTGOING");
			break;

		case MSG_CMD_TELE_STATE_CHANGE_IDLE:
			analyzedHead.packageHeadType=MSG_CMD_TELE_STATE_CHANGE_IDLE;

			//invoke registered callback function
			if(pCmdTelStateChangeIdle!=NULL){
				pCmdTelStateChangeIdle();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_TELE_STATE_CHANGE_IDLE");
			break;

		case MSG_CMD_TELE_STATE_CHANGE_INCALLING:
			analyzedHead.packageHeadType=MSG_CMD_TELE_STATE_CHANGE_INCALLING;

			//invoke registered callback function
			if(pCmdTelStateChangeInCalling!=NULL){
				pCmdTelStateChangeInCalling();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_TELE_STATE_CHANGE_INCALLING");
			break;

		case MSG_CMD_SCREEN_ON:
			analyzedHead.packageHeadType=MSG_CMD_SCREEN_ON;

			//invoke registered callback function
			if(pCmdScreenOn!=NULL){
				pCmdScreenOn();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_SCREEN_ON");
			break;

		case MSG_CMD_SCREEN_OFF:
			analyzedHead.packageHeadType=MSG_CMD_SCREEN_OFF;

			//invoke registered callback function
			if(pCmdScreenOff!=NULL){
				pCmdScreenOff();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_SCREEN_OFF");
			break;

		case MSG_CMD_SCREEN_USERPRESENT:
			analyzedHead.packageHeadType=MSG_CMD_SCREEN_USERPRESENT;

			//invoke registered callback function
			if(pCmdScreenUserPresent!=NULL){
				pCmdScreenUserPresent();
				}
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_SCREEN_USERPRESENT");
			break;

		case MSG_CMD_FOREGROUND:
			analyzedHead.packageHeadType=MSG_CMD_FOREGROUND;

			//invoke registered callback function
			if(pCmdForeground!=NULL){
				pCmdForeground();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_FOREGROUND");
			break;

		case MSG_CMD_BACKGROUND:
			analyzedHead.packageHeadType=MSG_CMD_BACKGROUND;

			//invoke registered callback function
			if(pCmdBackground!=NULL){
				pCmdBackground();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_BACKGROUND");
			break;

		case MSG_CMD_GO_TO_DESKTOP:
			analyzedHead.packageHeadType=MSG_CMD_GO_TO_DESKTOP;
			
			//invoke registered callback function
			if(pCmdGoToDeskTop!=NULL){
				pCmdGoToDeskTop();
				}
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_GO_TO_DESKTOP");
			break;

		case MSG_CMD_MIC_RECORD_WAKEUP_START:
			analyzedHead.packageHeadType=MSG_CMD_MIC_RECORD_WAKEUP_START;

			//invoke registered callback function
			if(pCmdMicRecordWakeupStart!=NULL){
				pCmdMicRecordWakeupStart();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MIC_RECORD_WAKEUP_START");
			break;

		case MSG_CMD_MIC_RECORD_END:
			analyzedHead.packageHeadType=MSG_CMD_MIC_RECORD_END;

			//invoke registered callback function
			if(pCmdMicRecordEnd!=NULL){
				pCmdMicRecordEnd();
				}
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MIC_RECORD_END");
			break;

		case MSG_CMD_MIC_RECORD_RECOG_START:
			analyzedHead.packageHeadType=MSG_CMD_MIC_RECORD_RECOG_START;

			//invoke registered callback function
			if(pCmdMicRecordRecogStart!=NULL){
				pCmdMicRecordRecogStart();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MIC_RECORD_RECOG_START");
			break;

		//added on 10th September 2015
		case MSG_CMD_MODULE_STATUS:
			analyzedHead.packageHeadType=MSG_CMD_MODULE_STATUS;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MODULE_STATUS");
			break;
		case MSG_CMD_STATISTIC_INFO:
			analyzedHead.packageHeadType=MSG_CMD_STATISTIC_INFO;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_STATISTIC_INFO");
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE:
			analyzedHead.packageHeadType=MSG_CMD_CAR_DATA_SUBSCRIBE;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_CAR_DATA_SUBSCRIBE");
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE_START:
			analyzedHead.packageHeadType=MSG_CMD_CAR_DATA_SUBSCRIBE_START;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_CAR_DATA_SUBSCRIBE_START");
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE_STOP:
			analyzedHead.packageHeadType=MSG_CMD_CAR_DATA_SUBSCRIBE_STOP;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_CAR_DATA_SUBSCRIBE_STOP");
			break;
		case MSG_CMD_MEDIA_INFO:
			analyzedHead.packageHeadType=MSG_CMD_MEDIA_INFO;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MEDIA_INFO");
			break;
		case MSG_CMD_MEDIA_PROGRESS_BAR:
			analyzedHead.packageHeadType=MSG_CMD_MEDIA_PROGRESS_BAR;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MEDIA_PROGRESS_BAR");
			break;
		case MSG_CMD_CONNECT_EXCEPTION:
			analyzedHead.packageHeadType=MSG_CMD_CONNECT_EXCEPTION;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_CONNECT_EXCEPTION");
			break;
		case MSG_CMD_REQUEST_GO_TO_FOREGROUND:
			analyzedHead.packageHeadType=MSG_CMD_REQUEST_GO_TO_FOREGROUND;

			//invoke registered callback function
			if(pCmdRequestGoToForeground!=NULL){
				pCmdRequestGoToForeground();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_REQUEST_GO_TO_FOREGROUND");
			break;

		case MSG_CMD_UI_ACTION_SOUND:
			analyzedHead.packageHeadType=MSG_CMD_UI_ACTION_SOUND;

			//invoke registered callback function
			if(pCmdUIActionSound!=NULL){
				pCmdUIActionSound();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_UI_ACTION_SOUND");
			break;

		//added on 6th January 2016
		//0x00010040
		case MSG_CMD_BT_HFP_REQUEST:
			analyzedHead.packageHeadType=MSG_CMD_BT_HFP_REQUEST;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_BT_HFP_REQUEST");
			break;

		//0x00010044
		case MSG_CMD_CARLIFE_DATA_SUBSCRIBE_DONE:
			analyzedHead.packageHeadType=MSG_CMD_CARLIFE_DATA_SUBSCRIBE_DONE;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_CARLIFE_DATA_SUBSCRIBE_DONE");
			break;

		//0x00010047
		case MSG_CMD_NAVI_ASSITANTGUIDE_INFO:
			analyzedHead.packageHeadType=MSG_CMD_NAVI_ASSITANTGUIDE_INFO;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_NAVI_ASSITANTGUIDE_INFO");
			break;

		//0x00010049
		case MSG_CMD_MD_AUTHEN_RESPONSE:
			analyzedHead.packageHeadType=MSG_CMD_MD_AUTHEN_RESPONSE;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MD_AUTHEN_RESPONSE");
			break;

		//0x0001804B
		case MSG_CMD_MD_AUTHEN_RESULT:
			analyzedHead.packageHeadType=MSG_CMD_MD_AUTHEN_RESULT;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MD_AUTHEN_RESULT");
			break;

		//0x0001004C
		case MSG_CMD_GO_TO_FOREGROUND_RESPONSE:
			analyzedHead.packageHeadType=MSG_CMD_GO_TO_FOREGROUND_RESPONSE;

			//invoke registered callback function
			if(pCmdGotoForgroundResponse!=NULL){
				pCmdGotoForgroundResponse();
				}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_GO_TO_FOREGROUND_RESPONSE");
			break;

		//0x0001004D
		case MSG_CMD_START_BT_AUTOPAIR_REQUEST:
			analyzedHead.packageHeadType=MSG_CMD_START_BT_AUTOPAIR_REQUEST;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_START_BT_AUTOPAIR_REQUEST");
			break;

		//0x0001004F
		case MSG_CMD_BT_HFP_STATUS_REQUEST:
			analyzedHead.packageHeadType=MSG_CMD_BT_HFP_STATUS_REQUEST;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_BT_HFP_STATUS_REQUEST");
			break;
			
		//0x00018051
		case MSG_CMD_MD_FEATURE_CONFIG_REQUEST:
			analyzedHead.packageHeadType=MSG_CMD_MD_FEATURE_CONFIG_REQUEST;

			if(pCmdFeatureConfigRequest!=NULL){
				pCmdFeatureConfigRequest();
			}
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_MD_FEATURE_CONFIG_REQUEST");
			break;

		//0x00010054
		case MSG_CMD_BT_IDENTIFY_RESULT_IND:
			analyzedHead.packageHeadType=MSG_CMD_BT_IDENTIFY_RESULT_IND;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_CMD_BT_IDENTIFY_RESULT_IND");
			break;
		
		//=============video channel============
		case MSG_VIDEO_DATA:
			analyzedHead.packageHeadType=MSG_VIDEO_DATA;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_VIDEO_DATA");
			break;

		case MSG_VIDEO_HEARTBEAT:
			analyzedHead.packageHeadType=MSG_VIDEO_HEARTBEAT;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_VIDEO_HEARTBEAT");
			//invoke registered callback function
			if(NULL!=pVideoHeartBeat){
				pVideoHeartBeat();
			}
			
			break;
		
		//media channel
		case MSG_MEDIA_INIT:
			analyzedHead.packageHeadType=MSG_MEDIA_INIT;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_INIT");
			break;

		case MSG_MEDIA_STOP:
			analyzedHead.packageHeadType=MSG_MEDIA_STOP;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_STOP");
			//invoke registered callback function
			if(NULL!=pMediaStop){
				pMediaStop();
			}
			
			break;

		case MSG_MEDIA_PAUSE:
			analyzedHead.packageHeadType=MSG_MEDIA_PAUSE;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_PAUSE");
			//invoke registered callback function
			if(NULL!=pMediaPause){
				pMediaPause();
			}
			
			break;

		case MSG_MEDIA_RESUME_PLAY:
			analyzedHead.packageHeadType=MSG_MEDIA_RESUME_PLAY;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_RESUME_PLAY");
			//invoke registered callback function
			if(NULL!=pMediaResume){
				pMediaResume();
			}
			
			break;

		case MSG_MEDIA_SEEK_TO:
			analyzedHead.packageHeadType=MSG_MEDIA_SEEK_TO;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_SEEK_TO");
			//invoke registered callback function
			if(NULL!=pMediaSeek){
				pMediaSeek();
			}
			
			break;

		case  MSG_MEDIA_DATA:
			analyzedHead.packageHeadType=MSG_MEDIA_DATA;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_MEDIA_DATA");
			break;

		//tts channel
		case MSG_TTS_INIT:
			analyzedHead.packageHeadType=MSG_TTS_INIT;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_TTS_INIT");
			break;

		case MSG_TTS_STOP:
			analyzedHead.packageHeadType=MSG_TTS_STOP;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_TTS_STOP");
			//invoke registered callback function
			if(NULL!=pTTSStop){
				pTTSStop();
			}
			
			break;

		case  MSG_TTS_DATA:
			analyzedHead.packageHeadType=MSG_TTS_DATA;
			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_TTS_DATA");
			break;

		//vr channel
		case MSG_VR_INIT:
			analyzedHead.packageHeadType=MSG_VR_INIT;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_VR_INIT");
			
			break;

		case MSG_VR_STOP:
			analyzedHead.packageHeadType=MSG_VR_STOP;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_VR_STOP");
			//invoke registered callback function
			if(NULL!=pVRStop){
				pVRStop();
			}
			
			break;

		case  MSG_VR_DATA:
			analyzedHead.packageHeadType=MSG_VR_DATA;

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_VR_DATA");
			break;

		case MSG_TOUCH_UI_ACTION_SOUND:
			//invoke registered callback function
			if(NULL!=pCtrlUIActionSound){
				pCtrlUIActionSound();
			}

			CCarLifeLog::carLifeLogLnWithPrefix("package type: MSG_TOUCH_UI_ACTION_SOUND");
			break;

		default:
			CCarLifeLog::carLifeLogLnWithPrefix("package type: unrecognized: ");
			
			break;
	}
}

bool CTranRecvPackageProcess::receivePackageData(){
	if(analyzedHead.packageDataSize>0){

		
		switch(channel){
		case CMD_CHANNEL:
			if(analyzedHead.packageDataSize>CMD_DATA_SIZE){
				CCarLifeLog::carLifeLogLnWithPrefix("CMD channel receive data length >CMD_DATA_SIZE !");
				return false;
			}
			
			if(CConnectManager::getInstance()->readCmdData(recvPackage.packageData, analyzedHead.packageDataSize)){
				CCarLifeLog::carLifeLogLnWithPrefix("->cmd package data is received");
			}else{
				CCarLifeLog::carLifeLogLnWithPrefix("->cmd package data receive failed!");
				return false;
			}
			
			break;

		case VIDEO_CHANNEL:
			if(analyzedHead.packageDataSize>VIDEO_DATA_SIZE){
				CCarLifeLog::carLifeLogLnWithPrefix("VIDEO channel receive data length >VIDEO_DATA_SIZE !");
				return false;
			}
			
			if(CConnectManager::getInstance()->readVideoData(recvPackage.packageData, analyzedHead.packageDataSize)){
				CCarLifeLog::carLifeLogLnWithPrefix("->video package data is received");
			}else{
				CCarLifeLog::carLifeLogLnWithPrefix("->video package data receive failed !");
				return false;
			}
			
			break;

		case MEDIA_CHANNEL:
			if(analyzedHead.packageDataSize>MEDIA_DATA_SIZE){
				CCarLifeLog::carLifeLogLnWithPrefix("MEDIA channel receive data length >MEDIA_DATA_SIZE !");
				return false;
			}
			
			if(CConnectManager::getInstance()->readMediaData(recvPackage.packageData, analyzedHead.packageDataSize)){
				CCarLifeLog::carLifeLogLnWithPrefix("->media package data is received");
			}else{
				CCarLifeLog::carLifeLogLnWithPrefix("->media package data receive failed !");
				return false;
			}
			
			break;

		case TTS_CHANNEL:
			if(analyzedHead.packageDataSize>TTS_DATA_SIZE){
				CCarLifeLog::carLifeLogLnWithPrefix("TTS channel receive data length >TTS_DATA_SIZE !");
				return false;
			}
			
			if(CConnectManager::getInstance()->readTTSData(recvPackage.packageData, analyzedHead.packageDataSize)){
				CCarLifeLog::carLifeLogLnWithPrefix("->tts package data is received");
			}else{
				CCarLifeLog::carLifeLogLnWithPrefix("->tts package data receive failed !");
				return false;
			}
			
			break;

		case VR_CHANNEL:
			if(analyzedHead.packageDataSize>VR_DATA_SIZE){
				CCarLifeLog::carLifeLogLnWithPrefix("VR channel receive data length >VR_DATA_SIZE !");
				return false;
			}
			
			if(CConnectManager::getInstance()->readVRData(recvPackage.packageData, analyzedHead.packageDataSize)){
				CCarLifeLog::carLifeLogLnWithPrefix("->vr package data is received");
			}else{
				CCarLifeLog::carLifeLogLnWithPrefix("->vr package data receive failed !");
				return false;
			}
			break;

		case CTRL_CHANNEL:
			break;

		default:
			CCarLifeLog::carLifeLogLnWithPrefix("no receive channel is choosed!");
			return false;
			
			break;
		}
		
		}

	return true;
}

void CTranRecvPackageProcess::packageDataAnalysis(){
	if(0==analyzedHead.packageDataSize){
		return;
		}

	CCarLifeLog::carLifeLogLnWithPrefix("analysis received package data");

	switch(analyzedHead.packageHeadType){
		//cmd package
		case MSG_CMD_PROTOCOL_VERSION_MATCH_STATUS:
			{
				//PB parse:S_PROTOCOL_VERSION_MATCH_SATUS protocolVersionMatchstatus
				CarlifeProtocolVersionMatchStatus protocolVersionMatchStatus;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				protocolVersionMatchStatus.MergePartialFromCodedStream(&input);

				protocolVersionMatchstatus.matchStatus=protocolVersionMatchStatus.matchstatus();

				//invoke registered callback function
				if(pCmdProtocolVersionMatchStatus!=NULL){
					pCmdProtocolVersionMatchStatus(&protocolVersionMatchstatus);
					}				
			}

			break;

		case MSG_CMD_MD_INFO:
			{
				//PB parse: S_MD_INFO mdInfo
				CarlifeDeviceInfo deviceInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				deviceInfo.MergePartialFromCodedStream(&input);

				mdInfo.os=deviceInfo.os();
				mdInfo.board=deviceInfo.board();
				mdInfo.bootloader=deviceInfo.bootloader();
				mdInfo.brand=deviceInfo.brand();
				mdInfo.cpu_abi=deviceInfo.cpu_abi();
				mdInfo.cpu_abi2=deviceInfo.cpu_abi2();
				mdInfo.device=deviceInfo.device();
				mdInfo.display=deviceInfo.display();
				mdInfo.fingerprint=deviceInfo.fingerprint();
				mdInfo.hardware=deviceInfo.hardware();
				mdInfo.host=deviceInfo.host();
				mdInfo.cid=deviceInfo.cid();
				mdInfo.manufacturer=deviceInfo.manufacturer();
				mdInfo.model=deviceInfo.model();
				mdInfo.product=deviceInfo.product();
				mdInfo.serial=deviceInfo.serial();
				mdInfo.codename=deviceInfo.codename();
				mdInfo.incremental=deviceInfo.incremental();
				mdInfo.release=deviceInfo.release();
				mdInfo.sdk=deviceInfo.sdk();
				mdInfo.sdk_int=deviceInfo.sdk_int();

				//invoke registered callback function
				if(pCmdMDInfro!=NULL){
					pCmdMDInfro(&mdInfo);
					}				
			}
			
			break;

		case MSG_CMD_MD_BT_PAIR_INFO:
			{
				//PB parse
				CarlifeBTPairInfo carlifeBTPairInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeBTPairInfo.MergePartialFromCodedStream(&input);

				btPairInfo.address=carlifeBTPairInfo.address();
				btPairInfo.passKey=carlifeBTPairInfo.passkey();
				btPairInfo.hash=carlifeBTPairInfo.hash();
				btPairInfo.randomizer=carlifeBTPairInfo.randomizer();
				btPairInfo.uuid=carlifeBTPairInfo.uuid();
				btPairInfo.name=carlifeBTPairInfo.name();
				btPairInfo.status=carlifeBTPairInfo.status();

				//invoke registered callback function
				if(pCmdMDBTPairInfro!=NULL){
					pCmdMDBTPairInfro(&btPairInfo);
					}
			}

			break;

		case MSG_CMD_VIDEO_ENCODER_INIT_DONE:
			{
				//PB parse: S_VIDEO_ENCODER_INIT_DONE videoEncoderInitDone
				CarlifeVideoEncoderInfo carLifeVideoEncoderInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carLifeVideoEncoderInfo.MergePartialFromCodedStream(&input);

				videoEncoderInitDone.width=carLifeVideoEncoderInfo.width();
				videoEncoderInitDone.height=carLifeVideoEncoderInfo.height();
				videoEncoderInitDone.frameRate=carLifeVideoEncoderInfo.framerate();

				//invoke registered callback function
				if(pCmdVideoEncoderInitDone!=NULL){
					pCmdVideoEncoderInitDone(&videoEncoderInitDone);
					}
			}
			break;

		case MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE:
			{
				//PB parse: S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE videoEncoderFrameRateChangeDone
				CarlifeVideoFrameRate videoFrameRate;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				videoFrameRate.MergePartialFromCodedStream(&input);

				videoEncoderFrameRateChangeDone.frameRate=videoFrameRate.framerate();

				//invoke registered callback function
				if(pCmdVideoEncoderFrameRateChangeDone!=NULL){
					pCmdVideoEncoderFrameRateChangeDone(&videoEncoderFrameRateChangeDone);
					}
			}

			break;
		//added on 10th September 2015
		case MSG_CMD_MODULE_STATUS:
			{
				//PB parse
				int cnt;
				CarlifeModuleStatus carlifeModuleStatus;
				S_MODULE_STATUS_MOBILE* pModuleStatus;
				
				CarlifeModuleStatusList carlifeModuleStatusList;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeModuleStatusList.MergePartialFromCodedStream(&input);
				
				cnt=carlifeModuleStatusList.cnt();

				if(cnt>moduleStatusMobileNum){
					CCarLifeLog::carLifeLogLnWithPrefix("moduleStatusMobile memory is low!!");

					cnt=moduleStatusMobileNum;
				}

				moduleStatusListMobile.cnt=cnt;
				pModuleStatus=moduleStatusListMobile.moduleStatus;

				for(int i=0;i<cnt;i++){
					carlifeModuleStatus=carlifeModuleStatusList.modulestatus(i);
					pModuleStatus->moduleID=carlifeModuleStatus.moduleid();
					pModuleStatus->statusID=carlifeModuleStatus.statusid();

					if(i!=cnt-1){
						pModuleStatus=pModuleStatus->next;
					}
				}

				//invoke registered callback function
				if(pCmdModuleStatus!=NULL){
					pCmdModuleStatus(&moduleStatusListMobile);
				}
			}
			break;
		case MSG_CMD_NAVI_NEXT_TURN_INFO:
			{
				//PB parse
				CarlifeNaviNextTurnInfo carlifeNaviNextTurnInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeNaviNextTurnInfo.MergePartialFromCodedStream(&input);

				naviNextTurnInfo.action=carlifeNaviNextTurnInfo.action();
				naviNextTurnInfo.nextTurn=carlifeNaviNextTurnInfo.nextturn();
				naviNextTurnInfo.roadName=carlifeNaviNextTurnInfo.roadname();
				naviNextTurnInfo.totalDistance=carlifeNaviNextTurnInfo.totaldistance();
				naviNextTurnInfo.remainDistance=carlifeNaviNextTurnInfo.remaindistance();
				naviNextTurnInfo.time=carlifeNaviNextTurnInfo.time();
				

				//invoke registered callback function
				if(pCmdNaviNextTurnInfo!=NULL){
					pCmdNaviNextTurnInfo(&naviNextTurnInfo);
					}
			}
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE:
			{
				//PB parse
				int cnt;
				CarlifeVehicleInfo carlifeVehicleInfo;
				S_VEHICLE_INFO* pVehicleInfo;
				
				CarlifeVehicleInfoList carlifeVehicleInfoList;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeVehicleInfoList.MergePartialFromCodedStream(&input);
				
				cnt=carlifeVehicleInfoList.cnt();

				if(cnt>vehicleInfoNum){
					CCarLifeLog::carLifeLogLnWithPrefix("vehicle info memory is low!!");

					cnt=vehicleInfoNum;
				}

				vehicleInfoList.cnt=cnt;
				pVehicleInfo=vehicleInfoList.pVehicleInfo;

				for(int i=0;i<cnt;i++){
					carlifeVehicleInfo=carlifeVehicleInfoList.vehicleinfo(i);
					pVehicleInfo->moduleID=carlifeVehicleInfo.moduleid();
					pVehicleInfo->supportFlag=carlifeVehicleInfo.supportflag();
					pVehicleInfo->frequency=carlifeVehicleInfo.frequency();

					if(i!=cnt-1){
						pVehicleInfo=pVehicleInfo->pNext;
					}
				}

				//invoke registered callback function
				if(pCmdCarDataSubscribe!=NULL){
					pCmdCarDataSubscribe(&vehicleInfoList);
				}
			}
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE_START:
			{
				//PB parse
				int cnt;
				CarlifeVehicleInfo carlifeVehicleInfo;
				S_VEHICLE_INFO* pVehicleInfo;
				
				CarlifeVehicleInfoList carlifeVehicleInfoList;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeVehicleInfoList.MergePartialFromCodedStream(&input);
				
				cnt=carlifeVehicleInfoList.cnt();

				if(cnt>vehicleInfoNum){
					CCarLifeLog::carLifeLogLnWithPrefix("vehicle info memory is low!!");

					cnt=vehicleInfoNum;
				}

				vehicleInfoList.cnt=cnt;
				pVehicleInfo=vehicleInfoList.pVehicleInfo;

				for(int i=0;i<cnt;i++){
					carlifeVehicleInfo=carlifeVehicleInfoList.vehicleinfo(i);
					pVehicleInfo->moduleID=carlifeVehicleInfo.moduleid();
					pVehicleInfo->supportFlag=carlifeVehicleInfo.supportflag();
					pVehicleInfo->frequency=carlifeVehicleInfo.frequency();

					if(i!=cnt-1){
						pVehicleInfo=pVehicleInfo->pNext;
					}
				}

				//invoke registered callback function
				if(pCmdCarDataSubscribeStart!=NULL){
					pCmdCarDataSubscribeStart(&vehicleInfoList);
				}
			}
			break;
		case MSG_CMD_CAR_DATA_SUBSCRIBE_STOP:
			{
				//PB parse
				int cnt;
				CarlifeVehicleInfo carlifeVehicleInfo;
				S_VEHICLE_INFO* pVehicleInfo;
				
				CarlifeVehicleInfoList carlifeVehicleInfoList;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeVehicleInfoList.MergePartialFromCodedStream(&input);
				
				cnt=carlifeVehicleInfoList.cnt();

				if(cnt>vehicleInfoNum){
					CCarLifeLog::carLifeLogLnWithPrefix("vehicle info memory is low!!");

					cnt=vehicleInfoNum;
				}

				vehicleInfoList.cnt=cnt;
				pVehicleInfo=vehicleInfoList.pVehicleInfo;

				for(int i=0;i<cnt;i++){
					carlifeVehicleInfo=carlifeVehicleInfoList.vehicleinfo(i);
					pVehicleInfo->moduleID=carlifeVehicleInfo.moduleid();
					pVehicleInfo->supportFlag=carlifeVehicleInfo.supportflag();
					pVehicleInfo->frequency=carlifeVehicleInfo.frequency();

					if(i!=cnt-1){
						pVehicleInfo=pVehicleInfo->pNext;
					}
				}

				//invoke registered callback function
				if(pCmdCarDataSubscribeStop!=NULL){
					pCmdCarDataSubscribeStop(&vehicleInfoList);
				}
			}
			break;
		case MSG_CMD_MEDIA_INFO:
			{
				//PB parse
				CarlifeMediaInfo carlifeMediaInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeMediaInfo.MergePartialFromCodedStream(&input);

				
				mediaInfo.source=carlifeMediaInfo.source();
				mediaInfo.song=carlifeMediaInfo.song();
				mediaInfo.artist=carlifeMediaInfo.artist();
				mediaInfo.album=carlifeMediaInfo.album();
				mediaInfo.albumArt=carlifeMediaInfo.albumart();
				mediaInfo.duration=carlifeMediaInfo.duration();
				mediaInfo.playlistNum=carlifeMediaInfo.playlistnum();
				mediaInfo.songId=carlifeMediaInfo.songid();
				mediaInfo.mode=carlifeMediaInfo.mode();

				//invoke registered callback function
				if(pCmdMediaInfo!=NULL){
					pCmdMediaInfo(&mediaInfo);
					}
			}
			break;
		case MSG_CMD_MEDIA_PROGRESS_BAR:
			{
				//PB parse
				CarlifeMediaProgressBar carlifeMediaProgressBar;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeMediaProgressBar.MergePartialFromCodedStream(&input);

				
				mediaProgressBar.progressBar=carlifeMediaProgressBar.progressbar();

				//invoke registered callback function
				if(pCmdMediaProgressBar!=NULL){
					pCmdMediaProgressBar(&mediaProgressBar);
					}
			}
			break;
		case MSG_CMD_CONNECT_EXCEPTION:
			{
				//PB parse
				CarlifeConnectException carlifeConnectException;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeConnectException.MergePartialFromCodedStream(&input);

				
				connectionException.exceptionType=carlifeConnectException.exceptiontype();

				//invoke registered callback function
				if(pCmdConnectException!=NULL){
					pCmdConnectException(&connectionException);
				}
			}
			break;

		//0x00010040
		case MSG_CMD_BT_HFP_REQUEST:
			{
				//PB parse		
				CarlifeBTHfpRequest carlifeBTHfpRequest;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeBTHfpRequest.MergePartialFromCodedStream(&input);

				bTHfpRequest.command=carlifeBTHfpRequest.command();
				bTHfpRequest.phoneNum=carlifeBTHfpRequest.phonenum();
				bTHfpRequest.dtmfCode=carlifeBTHfpRequest.dtmfcode();

				//invoke registered callback function
				if(pCmdBtHfpRequest!=NULL){
					pCmdBtHfpRequest(&bTHfpRequest);
				}
			}
			break;

		//0x00010044
		case MSG_CMD_CARLIFE_DATA_SUBSCRIBE_DONE:
			{
				//PB parse
				int cnt;
				CarlifeSubscribeMobileCarLifeInfo carlifeSubscribeMobileCarLifeInfo;
				S_MOBILE_CARLIFE_INFO *pMobileCarLifeInfo;

				CarlifeSubscribeMobileCarLifeInfoList carlifeSubscribeMobileCarLifeInfoList;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeSubscribeMobileCarLifeInfoList.MergePartialFromCodedStream(&input);
				
				cnt=carlifeSubscribeMobileCarLifeInfoList.cnt();

				if(cnt>subscribeMobileCarLifeInfoNum){
					CCarLifeLog::carLifeLogLnWithPrefix("subscribeMobileCarLifeInfo memory is low!!");

					cnt=subscribeMobileCarLifeInfoNum;
				}

				subscribeMobileCarLifeInfoList.cnt=cnt;
				pMobileCarLifeInfo=subscribeMobileCarLifeInfoList.pMobileCarLifeInfo;

				for(int i=0;i<cnt;i++){
					carlifeSubscribeMobileCarLifeInfo=carlifeSubscribeMobileCarLifeInfoList.subscribemobilecarlifeinfo(i);
					pMobileCarLifeInfo->moduleID=carlifeSubscribeMobileCarLifeInfo.moduleid();
					pMobileCarLifeInfo->supportFlag=carlifeSubscribeMobileCarLifeInfo.supportflag();

					if(i!=cnt-1){
						pMobileCarLifeInfo=pMobileCarLifeInfo->pNext;
					}
				}

				//invoke registered callback function
				if(pCmdCarLifeDataSubscribeDone!=NULL){
					pCmdCarLifeDataSubscribeDone(&subscribeMobileCarLifeInfoList);
				}
			}
			break;

		//0x00010047
		case MSG_CMD_NAVI_ASSITANTGUIDE_INFO:
			{
				//PB parse		
				CarlifeNaviAssitantGuideInfo carlifeNaviAssitantGuideInfo;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeNaviAssitantGuideInfo.MergePartialFromCodedStream(&input);

				naviAssitantGuideInfo.action=carlifeNaviAssitantGuideInfo.action();
				naviAssitantGuideInfo.assistantType=carlifeNaviAssitantGuideInfo.assistanttype();
				naviAssitantGuideInfo.trafficSignType=carlifeNaviAssitantGuideInfo.trafficsigntype();
				naviAssitantGuideInfo.totalDistance=carlifeNaviAssitantGuideInfo.totaldistance();
				naviAssitantGuideInfo.remainDistance=carlifeNaviAssitantGuideInfo.remaindistance();
				naviAssitantGuideInfo.cameraSpeed=carlifeNaviAssitantGuideInfo.cameraspeed();

				//invoke registered callback function
				if(pCmdNaviAssistantGuideInfo!=NULL){
					pCmdNaviAssistantGuideInfo(&naviAssitantGuideInfo);
				}
			}
			break;

		//0x00010049
		case MSG_CMD_MD_AUTHEN_RESPONSE:
			{
				//PB parse		
				CarlifeAuthenResponse carlifeAuthenResponse;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeAuthenResponse.MergePartialFromCodedStream(&input);

				authenResponse.encryptValue=carlifeAuthenResponse.encryptvalue();

				//invoke registered callback function
				if(pCmdMdAuthenResponse!=NULL){
					pCmdMdAuthenResponse(&authenResponse);
				}
			}
			break;

		//0x0001804B
		case MSG_CMD_MD_AUTHEN_RESULT:
			{
				//PB parse		
				CarlifeAuthenResult carlifeAuthenResult;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeAuthenResult.MergePartialFromCodedStream(&input);

				mDAuthenResult.authenResult=carlifeAuthenResult.authenresult();

				//invoke registered callback function
				if(pCmdMdAuthenResult!=NULL){
					pCmdMdAuthenResult(&mDAuthenResult);
				}
			}
			break;

		//0x0001004D
		case MSG_CMD_START_BT_AUTOPAIR_REQUEST:
			{
				//PB parse		
				CarlifeBTStartPairReq carlifeBTStartPairReq;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeBTStartPairReq.MergePartialFromCodedStream(&input);

				bTStartPairReq.osType=carlifeBTStartPairReq.ostype();
				bTStartPairReq.address=carlifeBTStartPairReq.address();

				//invoke registered callback function
				if(pCmdStartBtAutoPairRequest!=NULL){
					pCmdStartBtAutoPairRequest(&bTStartPairReq);
				}
			}
			break;

		//0x0001004F
		case MSG_CMD_BT_HFP_STATUS_REQUEST:
			{
				//PB parse		
				CarlifeBTHfpStatusRequest carlifeBTHfpStatusRequest;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeBTHfpStatusRequest.MergePartialFromCodedStream(&input);

				bTHfpStatusRequest.type=carlifeBTHfpStatusRequest.type();

				//invoke registered callback function
				if(pCmdBTHfpStatusRequest!=NULL){
					pCmdBTHfpStatusRequest(&bTHfpStatusRequest);
				}
			}
			break;
		//0x00010054
		case MSG_CMD_BT_IDENTIFY_RESULT_IND:
			{
				//PB parse		
				CarlifeBTIdentifyResultInd carlifeBTIdentifyResultInd;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carlifeBTIdentifyResultInd.MergePartialFromCodedStream(&input);

				btIndentifyResultInd.address=carlifeBTIdentifyResultInd.address();
				btIndentifyResultInd.status=carlifeBTIdentifyResultInd.status();

				//invoke registered callback function
				if(pCmdBTIdentifyResultInd!=NULL){
					pCmdBTIdentifyResultInd(&btIndentifyResultInd);
				}
			}
			break;
			
		//==========video package=============
		case MSG_VIDEO_DATA:
			//invoke registered callback function
			if(NULL!=pVideoDataReceive){
				pVideoDataReceive(recvPackage.packageData, analyzedHead.packageDataSize);
			}
			
			break;
			
		//media package
		case MSG_MEDIA_INIT:
			{
				//PB parse: S_AUDIO_INIT_PARAMETER audioInitParameter
				CarlifeMusicInit carLifeMusicInit;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carLifeMusicInit.MergePartialFromCodedStream(&input);

				audioInitParameter.sampleRate=carLifeMusicInit.samplerate();
				audioInitParameter.channelConfig=carLifeMusicInit.channelconfig();
				audioInitParameter.sampleFormat=carLifeMusicInit.sampleformat();

				//invoke registered callback function
				if(NULL!=pMediaInit){
				pMediaInit(&audioInitParameter);
				}
			}

		break;

		case MSG_MEDIA_DATA:
			//invoke registered callback function
			if(NULL!=pMediaNormalData){
				pMediaNormalData(recvPackage.packageData, analyzedHead.packageDataSize);
			}
			break;

		//tts package
		case MSG_TTS_INIT:
			{
				//PB parse: S_AUDIO_INIT_PARAMETER audioInitParameter
				CarlifeMusicInit carLifeMusicInit;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carLifeMusicInit.MergePartialFromCodedStream(&input);

				audioInitParameter.sampleRate=carLifeMusicInit.samplerate();
				audioInitParameter.channelConfig=carLifeMusicInit.channelconfig();
				audioInitParameter.sampleFormat=carLifeMusicInit.sampleformat();

				//invoke registered callback function
				if(NULL!=pTTSInit){
				pTTSInit(&audioInitParameter);
				}
			}

		break;

		case MSG_TTS_DATA:
			//invoke registered callback function
			if(NULL!=pTTSNormalData){
				pTTSNormalData(recvPackage.packageData, analyzedHead.packageDataSize);
			}
			
		break;

		//vr package
		case MSG_VR_INIT:
			{
				//PB parse: S_AUDIO_INIT_PARAMETER audioInitParameter
				CarlifeMusicInit carLifeMusicInit;
				::google::protobuf::io::CodedInputStream input((const ::google::protobuf::uint8*)recvPackage.packageData, analyzedHead.packageDataSize);
				carLifeMusicInit.MergePartialFromCodedStream(&input);

				audioInitParameter.sampleRate=carLifeMusicInit.samplerate();
				audioInitParameter.channelConfig=carLifeMusicInit.channelconfig();
				audioInitParameter.sampleFormat=carLifeMusicInit.sampleformat();

				//invoke registered callback function
				if(NULL!=pVRInit){
				pVRInit(&audioInitParameter);
				}
			}

		break;

		case MSG_VR_DATA:
			//invoke registered callback function
			if(NULL!=pVRNormalData){
				pVRNormalData(recvPackage.packageData, analyzedHead.packageDataSize);
			}
			
		break;

		default:
			break;
		}
}
void CTranRecvPackageProcess::setPackageHeadDataSize(u32 size){
	if(CMD_CHANNEL==channel ||CTRL_CHANNEL==channel){
		sendPackage.packageHead[0] = (u8) ((size >> 8) & 0xff);
		sendPackage.packageHead[1] = (u8) (size & 0xff);
		}else{
				sendPackage.packageHead[0] = (u8) ((size >> 24) & 0xff);
				sendPackage.packageHead[1] = (u8) ((size >> 16) & 0xff);
				sendPackage.packageHead[2] = (u8) ((size >> 8) & 0xff);
				sendPackage.packageHead[3] = (u8) (size & 0xff);
			}
}

void CTranRecvPackageProcess::setPackageHeadType(u32 type){
	if(CMD_CHANNEL==channel ||CTRL_CHANNEL==channel){
		sendPackage.packageHead[4] = (u8) ((type >> 24) & 0xff);
		sendPackage.packageHead[5] = (u8) ((type >> 16) & 0xff);
		sendPackage.packageHead[6] = (u8) ((type >> 8) & 0xff);
		sendPackage.packageHead[7] = (u8) (type & 0xff);
		}else{
				sendPackage.packageHead[8] = (u8) ((type >> 24) & 0xff);
				sendPackage.packageHead[9] = (u8) ((type >> 16) & 0xff);
				sendPackage.packageHead[10] = (u8) ((type >> 8) & 0xff);
				sendPackage.packageHead[11] = (u8) (type & 0xff);
			}
}

void CTranRecvPackageProcess::setPackageHeadTimeStamp(u32 timeStamp){
	sendPackage.packageHead[4] = (u8) ((timeStamp >> 24) & 0xff);
	sendPackage.packageHead[5] = (u8) ((timeStamp >> 16) & 0xff);
	sendPackage.packageHead[6] = (u8) ((timeStamp >> 8) & 0xff);
	sendPackage.packageHead[7] = (u8) (timeStamp & 0xff);
}

void CTranRecvPackageProcess::setPackageDataFiled(u8* data, u32 size){
	for(int i=0;i<size;i++){
		sendPackage.packageData[i]=data[i];
		}
}
//=================cmd channel======================
int CTranRecvPackageProcess::sendCmdHUProtoclVersion(S_HU_PROTOCOL_VERSION* version){
	//PB encapsulation
	CarlifeProtocolVersion protocolVersion;
	protocolVersion.set_majorversion(version->majorVersion);
	protocolVersion.set_minorversion(version->minorVersion);

	//set package head type
	setPackageHeadType(MSG_CMD_HU_PROTOCOL_VERSION);

	//set package data length
	setPackageHeadDataSize(protocolVersion.ByteSize());

	//set package data filed
	protocolVersion.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, protocolVersion.ByteSize())){
		return -1;
		}
	
	return 0;
}
int CTranRecvPackageProcess::sendCmdHUInfro(S_HU_INFO* huInfo){
	//PB encapsulation
	CarlifeDeviceInfo deviceInfo;
	deviceInfo.set_os(huInfo->os);
	deviceInfo.set_board(huInfo->board);
	deviceInfo.set_bootloader(huInfo->bootloader);
	deviceInfo.set_brand(huInfo->brand);
	deviceInfo.set_cpu_abi(huInfo->cpu_abi);
	deviceInfo.set_cpu_abi2(huInfo->cpu_abi2);
	deviceInfo.set_display(huInfo->display);
	deviceInfo.set_fingerprint(huInfo->fingerprint);
	deviceInfo.set_hardware(huInfo->hardware);
	deviceInfo.set_host(huInfo->host);
	deviceInfo.set_cid(huInfo->cid);
	deviceInfo.set_manufacturer(huInfo->manufacturer);
	deviceInfo.set_model(huInfo->model);
	deviceInfo.set_product(huInfo->product);
	deviceInfo.set_serial(huInfo->serial);
	deviceInfo.set_codename(huInfo->codename);
	deviceInfo.set_incremental(huInfo->incremental);
	deviceInfo.set_release(huInfo->release);
	deviceInfo.set_sdk(huInfo->sdk);
	deviceInfo.set_sdk_int(huInfo->sdk_int);
	deviceInfo.set_token(huInfo->token);

	//set package head type
	setPackageHeadType(MSG_CMD_HU_INFO);

	//set package data length
	setPackageHeadDataSize(deviceInfo.ByteSize());

	//set package data filed
	deviceInfo.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, deviceInfo.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::cmdHUBTPairInfro(S_BT_PAIR_INFO* info){
	//PB encapsulation
	CarlifeBTPairInfo carlifeBTPairInfo;
	carlifeBTPairInfo.set_address( info->address);
	carlifeBTPairInfo.set_passkey(info->passKey);
	carlifeBTPairInfo.set_hash( info->hash);
	carlifeBTPairInfo.set_randomizer(info->randomizer);
	carlifeBTPairInfo.set_uuid(info->uuid);
	carlifeBTPairInfo.set_name(info->name);
	carlifeBTPairInfo.set_status(info->status);

	//set package head type
	setPackageHeadType(MSG_CMD_HU_BT_PAIR_INFO);
	

	//set package data length
	setPackageHeadDataSize(carlifeBTPairInfo.ByteSize());

	//set package data filed
	carlifeBTPairInfo.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTPairInfo.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdVideoEncoderInit(S_VIDEO_ENCODER_INIT* initParam){
	//PB encapsulation
	CarlifeVideoEncoderInfo carLifeVideoEncoderInfo;
	carLifeVideoEncoderInfo.set_width(initParam->width);
	carLifeVideoEncoderInfo.set_height(initParam->height);
	carLifeVideoEncoderInfo.set_framerate(initParam->frameRate);

	//set package head type
	setPackageHeadType(MSG_CMD_VIDEO_ENCODER_INIT);

	//set package data length
	setPackageHeadDataSize(carLifeVideoEncoderInfo.ByteSize());

	//set package data filed
	carLifeVideoEncoderInfo.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carLifeVideoEncoderInfo.ByteSize())){
		return -1;
		}

	return 0;
	
}
int CTranRecvPackageProcess::sendCmdVideoEncoderStart(){
	//set package head type
	setPackageHeadType(MSG_CMD_VIDEO_ENCODER_START);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdVideoEncoderPause(){
	//set package head type
	setPackageHeadType(MSG_CMD_VIDEO_ENCODER_PAUSE);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdVideoEncoderReset(){
	//set package head type
	setPackageHeadType(MSG_CMD_VIDEO_ENCODER_RESET);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdVideoEncoderFrameRateChange(S_VIDEO_ENCODER_FRAME_RATE_CHANGE* videoParam){
	//PB encapsulation
	CarlifeVideoFrameRate videoFrameRate;
	videoFrameRate.set_framerate(videoParam->frameRate);

	//set package head type
	setPackageHeadType(MSG_CMD_VIDEO_ENCODER_FRAME_RATE_CHANGE);
	

	//set package data length
	setPackageHeadDataSize(videoFrameRate.ByteSize());

	//set package data filed
	videoFrameRate.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, videoFrameRate.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdPauseMedia(){
	//set package head type
	setPackageHeadType(MSG_CMD_PAUSE_MEDIA);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdCarVelocity(S_CAR_VELOCITY* carVelocity){
	//PB encapsulation
	CarlifeCarSpeed carSpeed;
	carSpeed.set_speed(carVelocity->speed);

	//set package head type
	setPackageHeadType(MSG_CMD_CAR_VELOCITY);
	

	//set package data length
	setPackageHeadDataSize(carSpeed.ByteSize());

	//set package data filed
	carSpeed.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carSpeed.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdCarGPS(S_CAR_GPS* gps){
	//PB encapsulation
	CarlifeCarGps carGps;
	carGps.set_antennastate(gps->antennaState);
	carGps.set_signalquality(gps->signalQuality);
	carGps.set_latitude(gps->latitude);
	carGps.set_longitude(gps->longitude);
	carGps.set_height(gps->height);
	carGps.set_speed(gps->speed);
	carGps.set_heading(gps->heading);
	carGps.set_year(gps->year);
	carGps.set_month(gps->month);
	carGps.set_day(gps->day);
	carGps.set_hrs(gps->hrs);
	carGps.set_min(gps->min);
	carGps.set_sec(gps->sec);
	carGps.set_fix(gps->fix);
	carGps.set_hdop(gps->hdop);
	carGps.set_pdop(gps->pdop);
	carGps.set_vdop(gps->vdop);
	carGps.set_satsused(gps->satsUsed);
	carGps.set_satsvisible(gps->satsVisible);
	carGps.set_horposerror(gps->horPosError);
	carGps.set_vertposerror(gps->vertPosError);
	carGps.set_northspeed(gps->northSpeed);
	carGps.set_eastspeed(gps->eastSpeed);
	carGps.set_vertspeed(gps->vertSpeed);

	//set package head type
	setPackageHeadType(MSG_CMD_CAR_GPS);
	

	//set package data length
	setPackageHeadDataSize(carGps.ByteSize());

	//set package data filed
	carGps.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carGps.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdCarGyroscope(S_CAR_GYROSCOPE* cyro){
	//PB encapsulation
	CarlifeGyroscope cyroScope;
	cyroScope.set_samplescount(cyro->samplesCount);
	cyroScope.set_xaxisgyrosum(cyro->xAxisGyroSum);
	cyroScope.set_yaxisgyrosum(cyro->yAxisGyroSum);
	cyroScope.set_zaxisgyrosum(cyro->zAxisGyroSum);

	//set package head type
	setPackageHeadType(MSG_CMD_CAR_GYROSCOPE);
	

	//set package data length
	setPackageHeadDataSize(cyroScope.ByteSize());

	//set package data filed
	cyroScope.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, cyroScope.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdCarAcceleration(S_CAR_ACCELERATION* acceleration){
	//PB encapsulation
	CarlifeAcceleration carlifeAcceleration;
	carlifeAcceleration.set_samplescount(acceleration->samplesCount);
	carlifeAcceleration.set_xaxisaccesum(acceleration->xAxisAcceSum);
	carlifeAcceleration.set_yaxisaccesum(acceleration->yAxisAcceSum);
	carlifeAcceleration.set_zaxisaccesum(acceleration->zAxisAcceSum);

	//set package head type
	setPackageHeadType(MSG_CMD_CAR_ACCELERATION);

	//set package data length
	setPackageHeadDataSize(carlifeAcceleration.ByteSize());

	//set package data filed
	carlifeAcceleration.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeAcceleration.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdCarOil(){
	//reserved

	return 0;
}
int CTranRecvPackageProcess::sendCmdLaunchModeNormal(){
	//set package head type
	setPackageHeadType(MSG_CMD_LAUNCH_MODE_NORMAL);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdLaunchModePhone(){
	//set package head type
	setPackageHeadType(MSG_CMD_LAUNCH_MODE_PHONE);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdLaunchModeMap(){
	//set package head type
	setPackageHeadType(MSG_CMD_LAUNCH_MODE_MAP);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCmdLaunchModeMusic(){
	//set package head type
	setPackageHeadType(MSG_CMD_LAUNCH_MODE_MUSIC);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}

void CTranRecvPackageProcess::cmdRegisterProtocolVersionMatchStatus(void (*pCmd)(S_PROTOCOL_VERSION_MATCH_SATUS*)){
	pCmdProtocolVersionMatchStatus=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterMDInfro(void (*pCmd)(S_MD_INFO*)){
	pCmdMDInfro=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterMDBTPairInfro(void (*pCmd)(S_BT_PAIR_INFO*)){
	pCmdMDBTPairInfro=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterVideoEncoderInitDone(void (*pCmd)(S_VIDEO_ENCODER_INIT_DONE*)){
	pCmdVideoEncoderInitDone=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterVideoEncoderFrameRateChangeDone(void (*pCmd)(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*)){
	pCmdVideoEncoderFrameRateChangeDone=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterTelStateChangeIncoming(void (*pCmd)(void)){
	pCmdTelStateChangeIncoming=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterTelStateChangeOutGoing(void (*pCmd)(void)){
	pCmdTelStateChangeOutGoing=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterTelStateChangeIdle(void (*pCmd)(void)){
	pCmdTelStateChangeIdle=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterTelStateChangeInCalling(void (*pCmd)(void)){
	pCmdTelStateChangeInCalling=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterScreenOn(void (*pCmd)(void)){
	pCmdScreenOn=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterScreenOff(void (*pCmd)(void)){
	pCmdScreenOff=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterScreenUserPresent(void (*pCmd)(void)){
	pCmdScreenUserPresent=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterForeground(void (*pCmd)(void)){
	pCmdForeground=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterBackground(void (*pCmd)(void)){
	pCmdBackground=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterGoToDeskTop(void (*pCmd)(void)){
	pCmdGoToDeskTop=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterMicRecordWakeupStart(void (*pCmd)(void)){
	pCmdMicRecordWakeupStart=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterMicRecordEnd(void (*pCmd)(void)){
	pCmdMicRecordEnd=pCmd;
}

void CTranRecvPackageProcess::cmdRegisterMicRecordRecogStart(void (*pCmd)(void)){
	pCmdMicRecordRecogStart=pCmd;
}

//added on 9th Semptember 2015
//0x00018025
int CTranRecvPackageProcess::cmdGoToForeground(){
	//set package head type
	setPackageHeadType(MSG_CMD_GO_TO_FOREGROUND);

	//set package data length
	setPackageHeadDataSize(0);

	//send package
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	return 0;
}

//0x00010026
void CTranRecvPackageProcess::cmdRegisterModuleStatus(void (*pFunc)(S_MODULE_STATUS_LIST_MOBILE*)){
	pCmdModuleStatus=pFunc;
}

//0x00018027
int CTranRecvPackageProcess::cmdStatisticInfo(S_STATISTICS_INFO* info){
	//PB encapsulation
	CarlifeStatisticsInfo carlifeStatisticsInfo;
	carlifeStatisticsInfo.set_cuid(info->cuid);
	carlifeStatisticsInfo.set_versionname(info->versionName);
	carlifeStatisticsInfo.set_versioncode(info->versionCode);
	carlifeStatisticsInfo.set_channel(info->channel);
	carlifeStatisticsInfo.set_connectcount(info->connectCount);
	carlifeStatisticsInfo.set_connectsuccesscount(info->connectSuccessCount);
	carlifeStatisticsInfo.set_connecttime(info->connectTime);
	carlifeStatisticsInfo.set_crashlog(info->crashLog);

	//set package head type
	setPackageHeadType(MSG_CMD_STATISTIC_INFO);
	

	//set package data length
	setPackageHeadDataSize(carlifeStatisticsInfo.ByteSize());

	//set package data filed
	carlifeStatisticsInfo.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeStatisticsInfo.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00018028
int CTranRecvPackageProcess::cmdModuleControl(S_MODULE_STATUS_CONTROL* status){
	//PB encapsulation
	CarlifeModuleStatus carlifeModuleStatus;
	carlifeModuleStatus.set_moduleid(status->moduleID);
	carlifeModuleStatus.set_statusid(status->statusID);

	//set package head type
	setPackageHeadType(MSG_CMD_MODULE_CONTROL);
	

	//set package data length
	setPackageHeadDataSize(carlifeModuleStatus.ByteSize());

	//set package data filed
	carlifeModuleStatus.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeModuleStatus.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00018029
int CTranRecvPackageProcess::cmdCarDataGear(S_GEAR_INFO* info){
	//PB encapsulation
	CarlifeGearInfo carlifeGearInfo;
	carlifeGearInfo.set_gear(info->gear);

	//set package head type
	setPackageHeadType(MSG_CMD_GEAR_INFO);
	

	//set package data length
	setPackageHeadDataSize(carlifeGearInfo.ByteSize());

	//set package data filed
	carlifeGearInfo.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeGearInfo.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010030
void CTranRecvPackageProcess::cmdRegisterNaviNextTurnInfo(void (*pFunc)(S_NAVI_NEXT_TURN_INFO*)){
	pCmdNaviNextTurnInfo=pFunc;
}

//0x00010031
void CTranRecvPackageProcess::cmdRegisterCarDataSubscribe(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCmdCarDataSubscribe=pFunc;
}

//0x00018032
int CTranRecvPackageProcess::cmdCarDataSubscribeDone(S_VEHICLE_INFO_LIST*  list){
	//PB encapsulation
	CarlifeVehicleInfo* carlifeVehicleInfo;
	CarlifeVehicleInfoList carlifeVehicleInfoList;
	carlifeVehicleInfoList.set_cnt(list->cnt);

	VehicleInfo* pVehicleInfo=list->pVehicleInfo;

	for(int i=0;i<list->cnt;i++){
		carlifeVehicleInfo=carlifeVehicleInfoList.add_vehicleinfo();
		carlifeVehicleInfo->set_moduleid(pVehicleInfo->moduleID);
		carlifeVehicleInfo->set_supportflag(pVehicleInfo->supportFlag);
		carlifeVehicleInfo->set_frequency(pVehicleInfo->frequency);
		pVehicleInfo=pVehicleInfo->pNext;
	}

	//set package head type
	setPackageHeadType(MSG_CMD_CAR_DATA_SUBSCRIBE_DONE);
	

	//set package data length
	setPackageHeadDataSize(carlifeVehicleInfoList.ByteSize());

	//set package data filed
	carlifeVehicleInfoList.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeVehicleInfoList.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010033
void CTranRecvPackageProcess::cmdRegisterCarDataSubscribeStart(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCmdCarDataSubscribeStart=pFunc;
}

//0x00010034
void CTranRecvPackageProcess::cmdRegisterCarDataSubscribeStop(void (*pFunc)(S_VEHICLE_INFO_LIST*)){
	pCmdCarDataSubscribeStop=pFunc;
}

//0x00010035
void CTranRecvPackageProcess::cmdRegisterMediaInfo(void (*pFunc)(S_MEDIA_INFO*)){
	pCmdMediaInfo=pFunc;
}

//0x00010036
void CTranRecvPackageProcess::cmdRegisterMediaProgressBar(void (*pFunc)(S_MEDIA_PROGRESS_BAR*)){
	pCmdMediaProgressBar=pFunc;
}

//0x00010037
void CTranRecvPackageProcess::cmdRegisterConnectException(void (*pFunc)(S_CONNECTION_EXCEPTION*)){
	pCmdConnectException=pFunc;
}

//0x00010038
void CTranRecvPackageProcess::cmdRegisterRequestGoToForeground(void (*pFunc)(void)){
	pCmdRequestGoToForeground=pFunc;
}

//0x00010039
void CTranRecvPackageProcess::cmdRegisterUIActionSound(void (*pFunc)(void)){
	pCmdUIActionSound=pFunc;
}

//added on 5th January 2016
//0x00010040
void CTranRecvPackageProcess::cmdRegisterBtHfpRequest(void (*pFunc)(S_BT_HFP_REQUEST*)){
	pCmdBtHfpRequest=pFunc;
}

//0x00018041
int CTranRecvPackageProcess::cmdBtHfpIndication(S_BT_HFP_INDICATION* indication){
	//PB encapsulation
	CarlifeBTHfpIndication carlifeBTHfpIndication;
	carlifeBTHfpIndication.set_state(indication->state);
	carlifeBTHfpIndication.set_phonenum(indication->phoneNum);
	carlifeBTHfpIndication.set_phonename( indication->name);
	carlifeBTHfpIndication.set_address(indication->address);

	//set package head type
	setPackageHeadType(MSG_CMD_BT_HFP_INDICATION);
	

	//set package data length
	setPackageHeadDataSize(carlifeBTHfpIndication.ByteSize());

	//set package data filed
	carlifeBTHfpIndication.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTHfpIndication.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00018042
int CTranRecvPackageProcess::cmdBtHfpConnection(S_BT_HFP_CONNECTION* connection){
	//PB encapsulation
	CarlifeBTHfpConnection carlifeBTHfpConnection;
	carlifeBTHfpConnection.set_state(connection->state);
	carlifeBTHfpConnection.set_address( connection->address);
	carlifeBTHfpConnection.set_name(connection->name);

	//set package head type
	setPackageHeadType(MSG_CMD_BT_HFP_CONNECTION);
	

	//set package data length
	setPackageHeadDataSize(carlifeBTHfpConnection.ByteSize());

	//set package data filed
	carlifeBTHfpConnection.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTHfpConnection.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00018043 
int CTranRecvPackageProcess::cmdCarLifeDataSubscribe(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	//PB encapsulation
	CarlifeSubscribeMobileCarLifeInfo* carLifeSubscribeMobileCarLifeInfo;
	CarlifeSubscribeMobileCarLifeInfoList carlifeSubscribeMobileCarLifeInfoList;
	carlifeSubscribeMobileCarLifeInfoList.set_cnt(list->cnt);

	S_MOBILE_CARLIFE_INFO* pMobileCarLifeInfo=list-> pMobileCarLifeInfo;

	for(int i=0;i<list->cnt;i++){
		carLifeSubscribeMobileCarLifeInfo=carlifeSubscribeMobileCarLifeInfoList.add_subscribemobilecarlifeinfo();
		carLifeSubscribeMobileCarLifeInfo->set_moduleid(pMobileCarLifeInfo->moduleID);
		pMobileCarLifeInfo=pMobileCarLifeInfo->pNext;
	}

	//set package head type
	setPackageHeadType(MSG_CMD_CARLIFE_DATA_SUBSCRIBE);
	

	//set package data length
	setPackageHeadDataSize(carlifeSubscribeMobileCarLifeInfoList.ByteSize());

	//set package data filed
	carlifeSubscribeMobileCarLifeInfoList.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeSubscribeMobileCarLifeInfoList.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010044 
void CTranRecvPackageProcess::cmdRegisterCarLifeDataSubscribeDone(void (*pFunc)(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST*)){
	pCmdCarLifeDataSubscribeDone=pFunc;
}

//0x00018045 
int CTranRecvPackageProcess::cmdCarLifeDataSubscribeStart(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	//PB encapsulation
	CarlifeSubscribeMobileCarLifeInfo* carlifeSubscribeMobileCarLifeInfo;
	CarlifeSubscribeMobileCarLifeInfoList carlifeSubscribeMobileCarLifeInfoList;
	carlifeSubscribeMobileCarLifeInfoList.set_cnt(list->cnt);

	S_MOBILE_CARLIFE_INFO* pMobileCarLifeInfo=list-> pMobileCarLifeInfo;

	for(int i=0;i<list->cnt;i++){
		carlifeSubscribeMobileCarLifeInfo=carlifeSubscribeMobileCarLifeInfoList.add_subscribemobilecarlifeinfo();
		carlifeSubscribeMobileCarLifeInfo->set_moduleid(pMobileCarLifeInfo->moduleID);
		pMobileCarLifeInfo=pMobileCarLifeInfo->pNext;
	}

	//set package head type
	setPackageHeadType(MSG_CMD_CARLIFE_DATA_SUBSCRIBE_START);
	

	//set package data length
	setPackageHeadDataSize(carlifeSubscribeMobileCarLifeInfoList.ByteSize());

	//set package data filed
	carlifeSubscribeMobileCarLifeInfoList.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeSubscribeMobileCarLifeInfoList.ByteSize())){
		return -1;
		}

	return 0;

}

//0x00018046 
int CTranRecvPackageProcess::cmdCarLifeDataSubscribeStop(S_SUBSCRIBE_MOBILE_CARLIFE_INFO_LIST* list){
	//PB encapsulation
	CarlifeSubscribeMobileCarLifeInfo* carlifeSubscribeMobileCarLifeInfo;
	CarlifeSubscribeMobileCarLifeInfoList carlifeSubscribeMobileCarLifeInfoList;
	carlifeSubscribeMobileCarLifeInfoList.set_cnt(list->cnt);

	S_MOBILE_CARLIFE_INFO* pMobileCarLifeInfo=list-> pMobileCarLifeInfo;

	for(int i=0;i<list->cnt;i++){
		carlifeSubscribeMobileCarLifeInfo=carlifeSubscribeMobileCarLifeInfoList.add_subscribemobilecarlifeinfo();
		carlifeSubscribeMobileCarLifeInfo->set_moduleid(pMobileCarLifeInfo->moduleID);
		pMobileCarLifeInfo=pMobileCarLifeInfo->pNext;
	}

	//set package head type
	setPackageHeadType(MSG_CMD_CARLIFE_DATA_SUBSCRIBE_STOP);
	

	//set package data length
	setPackageHeadDataSize(carlifeSubscribeMobileCarLifeInfoList.ByteSize());

	//set package data filed
	carlifeSubscribeMobileCarLifeInfoList.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeSubscribeMobileCarLifeInfoList.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010047 
void CTranRecvPackageProcess::cmdRegisterNaviAssistantGuideInfo(void (*pFunc)(S_NAVI_ASSITANT_GUIDE_INFO*)){
	pCmdNaviAssistantGuideInfo=pFunc;
}

//0x00018048 
int CTranRecvPackageProcess::cmdHuAuthenRequest(S_AUTHEN_REQUEST* req){
	//PB encapsulation
	CarlifeAuthenRequest carlifeAuthenRequest;
	carlifeAuthenRequest.set_randomvalue(req->randomValue);

	//set package head type
	setPackageHeadType(MSG_CMD_HU_AUTHEN_REQUEST);
	

	//set package data length
	setPackageHeadDataSize(carlifeAuthenRequest.ByteSize());

	//set package data filed
	carlifeAuthenRequest.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeAuthenRequest.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010049 
void CTranRecvPackageProcess::cmdRegisterMdAuthenResponse(void (*pFunc)(S_AUTHEN_RESPONSE*)){
	pCmdMdAuthenResponse=pFunc;
}

//0x0001804A 
int CTranRecvPackageProcess::cmdHuAuthenResult(S_HU_AUTHEN_RESULT* result){
	//PB encapsulation
	CarlifeAuthenResult carlifeAuthenResult;
	carlifeAuthenResult.set_authenresult(result->authenResult);

	//set package head type
	setPackageHeadType(MSG_CMD_HU_AUTHEN_RESULT);
	

	//set package data length
	setPackageHeadDataSize(carlifeAuthenResult.ByteSize());

	//set package data filed
	carlifeAuthenResult.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeAuthenResult.ByteSize())){
		return -1;
		}

	return 0;
}

//0x0001804B
void CTranRecvPackageProcess::cmdRegisterMdAuthenResult(void (*pFunc)(S_MD_AUTHEN_RESULT*)){
	pCmdMdAuthenResult=pFunc;
}
	
//0x0001004C 
void CTranRecvPackageProcess::cmdRegisterGotoForgroundResponse(void (*pFunc)(void)){
	pCmdGotoForgroundResponse=pFunc;
}

//0x0001004D 
void CTranRecvPackageProcess::cmdRegisterStartBtAutoPairRequest(void (*pFunc)(S_BT_START_PAIR_REQ*)){
	pCmdStartBtAutoPairRequest=pFunc;
}

//0x0001804E
int CTranRecvPackageProcess::cmdBTHfpResponse(S_BT_HFP_RESPONSE* rep){
	//PB encapsulation
	CarlifeBTHfpResponse carlifeBTHfpResponse;
	carlifeBTHfpResponse.set_status(rep->status);
	carlifeBTHfpResponse.set_cmd(rep->cmd);
	carlifeBTHfpResponse.set_dtmfcode(rep->dtmfCode);

	//set package head type
	setPackageHeadType(MSG_CMD_BT_HFP_RESPONSE);
	

	//set package data length
	setPackageHeadDataSize(carlifeBTHfpResponse.ByteSize());

	//set package data filed
	carlifeBTHfpResponse.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTHfpResponse.ByteSize())){
		return -1;
		}

	return 0;

}

//0x0001004F
void CTranRecvPackageProcess::cmdRegisterBTHfpStatusRequest(void (*pFunc)(S_BT_HFP_STATUS_REQUEST*)){
	pCmdBTHfpStatusRequest=pFunc;
}

//0x00018050
int CTranRecvPackageProcess::cmdBTHfpStatusResponse(S_BT_HFP_STATUS_RESPONSE* rep){
	//PB encapsulation
	CarlifeBTHfpStatusResponse carlifeBTHfpStatusResponse;
	carlifeBTHfpStatusResponse.set_status(rep->status);
	carlifeBTHfpStatusResponse.set_type(rep->type);

	//set package head type
	setPackageHeadType(MSG_CMD_BT_HFP_STATUS_RESPONSE);
	

	//set package data length
	setPackageHeadDataSize(carlifeBTHfpStatusResponse.ByteSize());

	//set package data filed
	carlifeBTHfpStatusResponse.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTHfpStatusResponse.ByteSize())){
		return -1;
		}

	return 0;
}

//added on 3th March 2016
//0x00010051
void CTranRecvPackageProcess::cmdRegisterFeatureConfigRequest(void (*pFunc)(void)){
	pCmdFeatureConfigRequest=pFunc;
}

//0x00018052
int CTranRecvPackageProcess::cmdFeatureConfigResponse(S_FEATURE_CONFIG_LIST* pList){
	//PB encapsulation
	CarlifeFeatureConfig *carlifeFeatureConfig;
	CarlifeFeatureConfigList carlifeFeatureConfigList;
	carlifeFeatureConfigList.set_cnt(pList->cnt);

	S_FEATURE_CONFIG *pFeatureConfig=pList->pFeatureConfig;	

	for(int i=0; i<pList->cnt; i++){
		carlifeFeatureConfig=carlifeFeatureConfigList.add_featureconfig();
		carlifeFeatureConfig->set_key(pFeatureConfig->key);
		carlifeFeatureConfig->set_value(pFeatureConfig->value);
		pFeatureConfig=pFeatureConfig->pNext;
	}

	//set package head type
	setPackageHeadType(MSG_CMD_HU_FEATURE_CONFIG_RESPONSE);
	
	//set package data length
	setPackageHeadDataSize(carlifeFeatureConfigList.ByteSize());

	//set package data filed
	carlifeFeatureConfigList.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeFeatureConfigList.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00018053
int CTranRecvPackageProcess::cmdBTStartIdentifyReq(S_BT_START_IDENTIFY_REQ* req){
	//PB encapsulation
	CarlifeBTStartIdentifyReq carlifeBTStartIdentifyReq;
	carlifeBTStartIdentifyReq.set_address( req->address);

	//set package head type
	setPackageHeadType(MSG_CMD_BT_START_IDENTIFY_REQ);

	//set package data length
	setPackageHeadDataSize(carlifeBTStartIdentifyReq.ByteSize());

	//set package data filed
	carlifeBTStartIdentifyReq.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeBTStartIdentifyReq.ByteSize())){
		return -1;
		}

	return 0;
}

//0x00010054
void CTranRecvPackageProcess::cmdRegisterBTIdentifyResultInd(void (*pFunc)(S_BT_INDENTIFY_RESULT_IND*)){
	pCmdBTIdentifyResultInd=pFunc;
}

//0x00018055
int CTranRecvPackageProcess::cmdErrorCode(S_ERROR_CODE* errorCode){
	//PB encapsulation
	CarlifeErrorCode carlifeErrorCode;
	carlifeErrorCode.set_errorcode( errorCode->errorCode);

	//set package head type
	setPackageHeadType(MSG_CMD_ERROR_CODE);

	//set package data length
	setPackageHeadDataSize(carlifeErrorCode.ByteSize());

	//set package data filed
	carlifeErrorCode.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageHead, CMD_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCmdData(sendPackage.packageData, carlifeErrorCode.ByteSize())){
		return -1;
		}

	return 0;
}

//==============Video channel================
void CTranRecvPackageProcess::videoRegisterDataReceive(void (*pVideo)(u8 *data, u32 len)){
	pVideoDataReceive=pVideo;
}

void CTranRecvPackageProcess::videoRegisterHeartBeat(void (*pFunc)(void)){
	pVideoHeartBeat=pFunc;
}

//==============Audio channel===================
void CTranRecvPackageProcess::mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pMediaInit=pFunc;
}

void CTranRecvPackageProcess::mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pMediaNormalData=pFunc;
}
void CTranRecvPackageProcess::mediaRegisterStop(void (*pFunc)(void)){
	pMediaStop=pFunc;
}
void CTranRecvPackageProcess::mediaRegisterPause(void (*pFunc)(void)){
	pMediaPause=pFunc;
}
void CTranRecvPackageProcess::mediaRegisterResume(void (*pFunc)(void)){
	pMediaResume=pFunc;
}
void CTranRecvPackageProcess::mediaRegisterSeek(void (*pFunc)(void)){
	pMediaSeek=pFunc;
}

void CTranRecvPackageProcess::ttsRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pTTSInit=pFunc;
}

void CTranRecvPackageProcess::ttsRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pTTSNormalData=pFunc;
}
void CTranRecvPackageProcess::ttsRegisterStop(void (*pFunc)(void)){
	pTTSStop=pFunc;
}

//=============VR channel===============
//vr channel [HU->MD]
int CTranRecvPackageProcess::sendMicData(u8* data, u32 size, u32 timeStamp){
	//set package head type
	setPackageHeadType(MSG_VR_MIC_DATA);

	//set package data length
	setPackageHeadDataSize(size);

	//set package time stamp
	setPackageHeadTimeStamp(timeStamp);

	//send package head
	if(!CConnectManager::getInstance()->writeVRData(sendPackage.packageHead, VR_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeVRData(data, size)){
		return -1;
		}

	return 0;
}

void CTranRecvPackageProcess::vrRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	pVRInit=pFunc;
}

void CTranRecvPackageProcess::vrRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	pVRNormalData=pFunc;
}
void CTranRecvPackageProcess::vrRegisterStop(void (*pFunc)(void)){
	pVRStop=pFunc;
}

//=============Control channel===========
void CTranRecvPackageProcess::ctrlRegisterUIActionSound(void (*pFunc)(void)){
	pCtrlUIActionSound=pFunc;
}

//ctrol channel [HU->MD]
int CTranRecvPackageProcess::sendCtrlTouchAction(S_TOUCH_ACTION* touchAction){
	//PB encapsulation
	CarlifeTouchAction action;
	action.set_action(touchAction->action);
	action.set_x(touchAction->x);
	action.set_y(touchAction->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_ACTION);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field	
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown){
	//PB encapsulation
	//ALOGD("sendCtrlTouchActionDown--------------------1");
	CarlifeTouchSinglePoint action;
	action.set_x(touchActionDown->x);
	action.set_y(touchActionDown->y);
	//ALOGD("sendCtrlTouchActionDown--------------------2");

	//set package head type
	setPackageHeadType(MSG_TOUCH_ACTION_DOWN);
	
	//ALOGD("sendCtrlTouchActionDown--------------------3");

	//set package data length
	setPackageHeadDataSize(action.ByteSize());
	//ALOGD("sendCtrlTouchActionDown--------------------4");

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);
	//ALOGD("sendCtrlTouchActionDown--------------------5");

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}
	//ALOGD("sendCtrlTouchActionDown--------------------6");

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp){
	//PB encapsulation
	CarlifeTouchSinglePoint action;
	action.set_x(touchActionUp->x);
	action.set_y(touchActionUp->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_ACTION_UP);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove){
	//PB encapsulation
	CarlifeTouchSinglePoint action;
	action.set_x(touchActionMove->x);
	action.set_y(touchActionMove->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_ACTION_MOVE);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick){
	//PB encapsulation
	CarlifeTouchSinglePoint action;
	action.set_x(touchSingleClick->x);
	action.set_y(touchSingleClick->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_SINGLE_CLICK);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick){
	//PB encapsulation
	CarlifeTouchSinglePoint action;
	action.set_x(touchDoubleClick->x);
	action.set_y(touchDoubleClick->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_DOUBLE_CLICK);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head 
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress){
	//PB encapsulation
	CarlifeTouchSinglePoint action;
	action.set_x(touchLongPress->x);
	action.set_y(touchLongPress->y);

	//set package head type
	setPackageHeadType(MSG_TOUCH_LONG_PRESS);
	

	//set package data length
	setPackageHeadDataSize(action.ByteSize());

	//set package data filed
	action.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data field
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, action.ByteSize())){
		return -1;
		}

	return 0;
}
int CTranRecvPackageProcess::sendCtrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode){
	//PB encapsulation
	CarlifeCarHardKeyCode hardKey;
	hardKey.set_keycode(touchCarHardKeyCode->keycode);

	//set package head type
	setPackageHeadType(MSG_TOUCH_CAR_HARD_KEY_CODE);
	

	//set package data length
	setPackageHeadDataSize(hardKey.ByteSize());

	//set package data filed
	hardKey.SerializeWithCachedSizesToArray(sendPackage.packageData);

	//send package head
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageHead, CTRL_HEAD_LEN)){
		return -1;
		}

	//send package data filed
	if(!CConnectManager::getInstance()->writeCtrlData(sendPackage.packageData, hardKey.ByteSize())){
		return -1;
		}

	return 0;
}

//=========Utilities===============
void CTranRecvPackageProcess::initModuleStatusMobileMemory(){
	moduleStatusMobileNum=10;
	moduleStatusListMobile.moduleStatus=&moduleStatusMobile1;

	moduleStatusMobile1.next=&moduleStatusMobile2;
	moduleStatusMobile2.next=&moduleStatusMobile3;
	moduleStatusMobile3.next=&moduleStatusMobile4;
	moduleStatusMobile4.next=&moduleStatusMobile5;
	moduleStatusMobile5.next=&moduleStatusMobile6;
	moduleStatusMobile6.next=&moduleStatusMobile7;
	moduleStatusMobile7.next=&moduleStatusMobile8;
	moduleStatusMobile8.next=&moduleStatusMobile9;
	moduleStatusMobile9.next=&moduleStatusMobile10;
	moduleStatusMobile10.next=NULL;
}

void CTranRecvPackageProcess::initVehicleInfoMemory(){
	vehicleInfoNum=10;
	vehicleInfoList.pVehicleInfo=&vehicleInfo1;

	vehicleInfo1.pNext=&vehicleInfo2;
	vehicleInfo2.pNext=&vehicleInfo3;
	vehicleInfo3.pNext=&vehicleInfo4;
	vehicleInfo4.pNext=&vehicleInfo5;
	vehicleInfo5.pNext=&vehicleInfo6;
	vehicleInfo6.pNext=&vehicleInfo7;
	vehicleInfo7.pNext=&vehicleInfo8;
	vehicleInfo8.pNext=&vehicleInfo9;
	vehicleInfo9.pNext=&vehicleInfo10;
	vehicleInfo10.pNext=NULL;
}

void CTranRecvPackageProcess::initSubscribeMobileCarLifeInfoMemory(){
	subscribeMobileCarLifeInfoNum=10;
	subscribeMobileCarLifeInfoList.pMobileCarLifeInfo=&mobileCarLifeInfo1;

	mobileCarLifeInfo1.pNext=&mobileCarLifeInfo2;
	mobileCarLifeInfo2.pNext=&mobileCarLifeInfo3;
	mobileCarLifeInfo3.pNext=&mobileCarLifeInfo4;
	mobileCarLifeInfo4.pNext=&mobileCarLifeInfo5;
	mobileCarLifeInfo5.pNext=&mobileCarLifeInfo6;
	mobileCarLifeInfo6.pNext=&mobileCarLifeInfo7;
	mobileCarLifeInfo7.pNext=&mobileCarLifeInfo8;
	mobileCarLifeInfo8.pNext=&mobileCarLifeInfo9;
	mobileCarLifeInfo9.pNext=&mobileCarLifeInfo10;
	mobileCarLifeInfo10.pNext=NULL;
}

