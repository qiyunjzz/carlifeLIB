/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CCarLifeLibWrapper.h"
#include "CarLifeLibTest.h"
#include<pthread.h>
#include<unistd.h>
#include <jni.h>
#include <utils/Log.h>

/****************************************
FUNCTIONS
*****************************************/
void *cmdReceiveThread(void *arg);
void *videoReceiveThread(void *arg);
void *mediaReceiveThread(void *arg);
void *ttsReceiveThread(void *arg);
void *vrReceiveThread(void *arg);

void cmdProtocolVersionMatchStatus(S_PROTOCOL_VERSION_MATCH_SATUS* status);
void cmdMDInfro(S_MD_INFO*);
void cmdMDBTPairInfro(BTPairInfo*);
void cmdVideoEncoderInitDone(S_VIDEO_ENCODER_INIT_DONE*);
void cmdVideoEncoderFrameRateChangeDone(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE*);
void setVideoFormat(int width,int height);

void cmdTelStateChangeIncoming();
void cmdTelStateChangeOutGoing();
void cmdTelStateChangeIdle();
void cmdTelStateChangeInCalling();
void cmdScreenOn();
void cmdScreenOff();
void cmdScreenUserPresent();
void cmdForeground();
void cmdBackground();
void cmdGoToDeskTop();
void cmdMicRecordWakeupStart();
void cmdMicRecordEnd();
void cmdMicRecordRecogStart();
//0x00010026
void cmdModuleStatus(S_MODULE_STATUS_LIST_MOBILE*);
//0x00010030
void cmdNaviNextTurnInfo(S_NAVI_NEXT_TURN_INFO*);
//0x00010031
void cmdCarDataSubscribe(S_VEHICLE_INFO_LIST*);	
//0x00010033
void cmdCarDataSubscribeStart(S_VEHICLE_INFO_LIST*);
//0x00010034
void cmdCarDataSubscribeStop(S_VEHICLE_INFO_LIST*);
//0x00010035
void cmdMediaInfo(S_MEDIA_INFO*);
//0x00010036
void cmdMediaProgressBar(S_MEDIA_PROGRESS_BAR*);
//0x00010037
void cmdRegisterConnectException(S_CONNECTION_EXCEPTION*);
//0x00010038
void cmdRegisterRequestGoToForeground(void);
//0x00010039
void cmdRegisterUIActionSound(void);

//0x00010049
void cmdRegisterMdAuthenResponse(S_AUTHEN_RESPONSE* response);

//0x00010051
void cmdRegisterFeatureConfigRequest();

void videoDataReceive(u8 *data, u32 len);
void videoHeartBeat();
void mediaInit(S_AUDIO_INIT_PARAMETER *initParam);
void mediaNormalData(u8 *data, u32 len);
void mediaStop();
void mediaPause();
void mediaResume();
void mediaSeek();
void ttsInit(S_AUDIO_INIT_PARAMETER *initParam);
void ttsNormalData(u8 *data, u32 len);
void ttsStop();
void vrInit(S_AUDIO_INIT_PARAMETER *initParam);
void vrNormalData(u8 *data, u32 len);
void vrStop();

void SendAudioRecordData(u8* data, u32 len);


/****************************************** 
INIT PARAMETER
*******************************************/
S_STATISTICS_INFO nfeStatisticsInfo={"1003","1.0",1,"20012101",1,1,10,""};
string cuid;
string versionName;
u32 versionCode;
string channel;
u32 connectCount;
u32 connectSuccessCount;
u32 connectTime;
string crashLog;

S_HU_PROTOCOL_VERSION huProtocolVersion={1,0};

S_VIDEO_ENCODER_INIT initVideoParam={768, 480,30};

u8 vrData[1024]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9};

S_TOUCH_ACTION touchAction={1, 12 ,34};

S_TOUCH_CAR_HARD_KEY_CODE touchCarHardKeyCode={0x00000010};//next song

//anthorization
S_AUTHEN_REQUEST authenRequest={"CarLife_1.0.0"};

S_FEATURE_CONFIG_LIST configList;
S_FEATURE_CONFIG featureConfigFocusUI;

void setFocusUIConfig(int val){
	configList.cnt=1;
	configList.pFeatureConfig=&featureConfigFocusUI;
	featureConfigFocusUI.key="FOCUS_UI";
	featureConfigFocusUI.value=val;
	featureConfigFocusUI.pNext=NULL;
}

//connection pattern setting
#define ADB_CONNECTION 0
#define IOS_WIFI_CONNECTION 1
#define CONNECTION_PATTERN ADB_CONNECTION

//carlifestate: 1 start; 0 stop
static int carlifestate = 1;
JNIEnv *g_env = NULL;
JNIEnv *env = NULL;  
static JavaVM* jvm = NULL;
void* reserved = NULL; 
static int satus = 1;
int _connectState = -1;
//click event
S_TOUCH_ACTION_DOWN TouchActionDown={0,0};
S_TOUCH_ACTION_UP TouchActionUp={0,0};
S_TOUCH_ACTION_MOVE TouchActionMove={0,0};
S_TOUCH_SIGNAL_CLICK TouchSingleClick={0,0};
S_TOUCH_DOUBLE_CLICK TouchDoubleClick={0,0};
S_TOUCH_LONG_PRESS TouchLongPress={0,0};

int nfcarlifetest(){
	int ret;
	pthread_t id;
	int item;


	CCarLifeLib::getInstance()->carLifeLibInit();
	if(CONNECTION_PATTERN==ADB_CONNECTION){
	_connectState=CCarLifeLib::getInstance()->connectionSetup();
		if(0 == _connectState){
			ALOGD("command/video/media/tts/vr/control channel connection have been set up!");
		}else{
			ALOGD("connection set up faile!");
		}
	}

	CCarLifeLib::getInstance()->cmdStatisticInfo(&nfeStatisticsInfo);
	CCarLifeLib::getInstance()->cmdHUProtoclVersion(&huProtocolVersion);	
	CCarLifeLib::getInstance()->cmdVideoEncoderInit(&initVideoParam);
	setVideoFormat(initVideoParam.width,initVideoParam.height);
	CCarLifeLib::getInstance()->cmdVideoEncoderStart();



	ret=pthread_create(&id, NULL, cmdReceiveThread, NULL);
	if(ret!=0){
		ALOGD("cmdReceiveThread create failed!");
	}else{
		ALOGD("cmdReceiveThread create!");
	}

	ret=pthread_create(&id, NULL, mediaReceiveThread, NULL);
	if(ret!=0){
		ALOGD("mediaReceivThread create failed!");
	}else{
		ALOGD("mediaReceivThread create !");
	}

	ret=pthread_create(&id, NULL, ttsReceiveThread, NULL);
	if(ret!=0){
		ALOGD("ttsReceivThread create failed!");
	}else{
		ALOGD("ttsReceivThread create!");	
	}

	ret=pthread_create(&id, NULL, vrReceiveThread, NULL);
	if(ret!=0){
		ALOGD("vrReceivThread create failed!");
	}else{
		ALOGD("vrReceivThread create!");
	}

	CCarLifeLib::getInstance()->videoRegisterDataReceive(videoDataReceive);
	CCarLifeLib::getInstance()->videoRegisterHeartBeat(videoHeartBeat);

	while(1){
		if(-1==CCarLifeLib::getInstance()->videoReceiveOperation()){
			ALOGD("video channel receive thread exit!");
			break;
		}
	}

	//release CarLifeVehicleLib resources
	CCarLifeLib *pCCarLifeLib=CCarLifeLib::getInstance();
	pCCarLifeLib->carLifeLibDestory();
	
	return 0;
}


void *cmdReceiveThread(void *arg){
	//register call back
	CCarLifeLib::getInstance()->cmdRegisterProtocolVersionMatchStatus(cmdProtocolVersionMatchStatus);
	CCarLifeLib::getInstance()->cmdRegisterMDInfro(cmdMDInfro);
	CCarLifeLib::getInstance()->cmdRegisterMDBTPairInfro(cmdMDBTPairInfro);
	CCarLifeLib::getInstance()->cmdRegisterVideoEncoderInitDone(cmdVideoEncoderInitDone);
	CCarLifeLib::getInstance()->cmdRegisterVideoEncoderFrameRateChangeDone(cmdVideoEncoderFrameRateChangeDone);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeIncoming(cmdTelStateChangeIncoming);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeOutGoing(cmdTelStateChangeOutGoing);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeIdle(cmdTelStateChangeIdle);
	CCarLifeLib::getInstance()->cmdRegisterTelStateChangeInCalling(cmdTelStateChangeInCalling);
	CCarLifeLib::getInstance()->cmdRegisterScreenOn(cmdScreenOn);
	CCarLifeLib::getInstance()->cmdRegisterScreenOff(cmdScreenOff);
	CCarLifeLib::getInstance()->cmdRegisterScreenUserPresent(cmdScreenUserPresent);
	CCarLifeLib::getInstance()->cmdRegisterForeground(cmdForeground);
	CCarLifeLib::getInstance()->cmdRegisterBackground(cmdBackground);
	CCarLifeLib::getInstance()->cmdRegisterGoToDeskTop(cmdGoToDeskTop);

	
	CCarLifeLib::getInstance()->cmdRegisterMicRecordWakeupStart(cmdMicRecordWakeupStart);
	CCarLifeLib::getInstance()->cmdRegisterMicRecordEnd(cmdMicRecordEnd);
	CCarLifeLib::getInstance()->cmdRegisterMicRecordRecogStart(cmdMicRecordRecogStart);

	
	//0x00010026
	CCarLifeLib::getInstance()->cmdRegisterModuleStatus(cmdModuleStatus);
	//0x00010030
	CCarLifeLib::getInstance()->cmdRegisterNaviNextTurnInfo(cmdNaviNextTurnInfo);
	//0x00010031
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribe(cmdCarDataSubscribe);	
	//0x00010033
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribeStart(cmdCarDataSubscribeStart);
	//0x00010034
	CCarLifeLib::getInstance()->cmdRegisterCarDataSubscribeStop(cmdCarDataSubscribeStop);
	//0x00010035
	CCarLifeLib::getInstance()->cmdRegisterMediaInfo(cmdMediaInfo);
	//0x00010036
	CCarLifeLib::getInstance()->cmdRegisterMediaProgressBar(cmdMediaProgressBar);
	//0x00010037
	CCarLifeLib::getInstance()->cmdRegisterConnectException(cmdRegisterConnectException);
	//0x00010038
	CCarLifeLib::getInstance()->cmdRegisterRequestGoToForeground(cmdRegisterRequestGoToForeground);
	//0x00010039
	CCarLifeLib::getInstance()->cmdRegisterUIActionSound(cmdRegisterUIActionSound);


	//0x00010049 
	CCarLifeLib::getInstance()->cmdRegisterMdAuthenResponse(cmdRegisterMdAuthenResponse);

	//0x00010051
	CCarLifeLib::getInstance()->cmdRegisterFeatureConfigRequest(cmdRegisterFeatureConfigRequest);


	while(1){
		//receive data from command channel
		if(-1==CCarLifeLib::getInstance()->cmdReceiveOperation()){

			cout<<"command channel receive thread exit!"<<endl;
				
			break;
			}
	}
	return NULL;

}



void *mediaReceiveThread(void *arg){
		CCarLifeLib::getInstance()->mediaRegisterInit(mediaInit);
		CCarLifeLib::getInstance()->mediaRegisterNormalData(mediaNormalData);
		CCarLifeLib::getInstance()->mediaRegisterPause(mediaPause);
		CCarLifeLib::getInstance()->mediaRegisterResume(mediaResume);
		CCarLifeLib::getInstance()->mediaRegisterSeek(mediaSeek);
		CCarLifeLib::getInstance()->mediaRegisterStop(mediaStop);


		while(1){
			if(-1==CCarLifeLib::getInstance()->mediaReceiveOperation()){
				ALOGD("media channel thread exit!");
				break;
			}
		}
		return NULL;

}

void *ttsReceiveThread(void *arg){

	CCarLifeLib::getInstance()->ttsRegisterInit(ttsInit);	
	CCarLifeLib::getInstance()->ttsRegisterNormalData(ttsNormalData);
	CCarLifeLib::getInstance()->ttsRegisterStop(ttsStop);


	while(1){
		if(-1==CCarLifeLib::getInstance()->ttsReceiveOperation()){
			ALOGD("tts channel thread exit!");
			break;
		}
	}
	return NULL;
	
}


void *vrReceiveThread(void *arg){
	CCarLifeLib::getInstance()->vrRegisterInit(vrInit);
	CCarLifeLib::getInstance()->vrRegisterNormalData(vrNormalData);
	CCarLifeLib::getInstance()->vrRegisterStop(vrStop);


	while(1){
		if(-1==CCarLifeLib::getInstance()->vrReceiveOperation()){
			ALOGD("vr channel thread exit!");
			break;
		}
	}
	return NULL;
}



int ClickDownEvent(int x,int y){
	TouchActionDown.x = x;
	TouchActionDown.y = y;
	
	if(x < 0 || y < 0)
		return 0;
		
	int i ;//= CCarLifeLib::getInstance()->ctrlTouchActionDown(&TouchActionDown);
	return i;
}

int ClickUpEvent(int x,int y){
	TouchActionUp.x = x;
	TouchActionUp.y = y;
	
	if(x < 0 || y < 0)
		return 0;

			
	int i ;//= CCarLifeLib::getInstance()->ctrlTouchActionUp(&TouchActionUp);	
	return i;
} 
	
int OnClickEvent(int x,int y){
	TouchSingleClick.x = x;
	TouchSingleClick.y = y;

	if(x < 0 || y < 0 )
		return 0;

	int i = CCarLifeLib::getInstance()->ctrlTouchSigleClick(&TouchSingleClick);
	return i;
}	

		
int DoubleClickEvent(int x,int y){
	TouchDoubleClick.x = x;
	TouchDoubleClick.y = y;

	if(x < 0 || y < 0 )
		return 0;


	int i = CCarLifeLib::getInstance()->ctrlTouchDoubleClick(&TouchDoubleClick);
	return i;
}

int HoldOnEvent(int x,int y){
	TouchLongPress.x = x;
	TouchLongPress.y = y;
	if(x < 0 || y < 0 )
		return 0;

	int i = CCarLifeLib::getInstance()->ctrlTouchLongPress(&TouchLongPress);
	return i;
}

int MoveEvnet(int x,int y){
	TouchActionMove.x = x;
	TouchActionMove.y 

	= y;
	if(x < 0 || y < 0 )
		return 0;
	
	int i;// = CCarLifeLib::getInstance()->ctrlTouchActionMove(&TouchActionMove);
	return i;
} 	
	
//media channel callback functions
void mediaInit(S_AUDIO_INIT_PARAMETER *initParam){

	JNIEnv *env;
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
		
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("mediaInit fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"setMediaFormat","(III)V");
	if(javaCallback == NULL)
	{
		ALOGD("mediaInit fail to find method nativeCallback");
		return; 
	}
	if(NULL == initParam)
		return;
	else
		env->CallVoidMethod(g_obj,javaCallback,initParam->sampleRate,initParam->channelConfig,initParam->sampleFormat);	

}

void mediaNormalData(u8 *data, u32 len){
	//ALOGD("mediaNormadata--------------->");
 	JNIEnv *env;

	//get env from g_JavaVM
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("mediaNormalData fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"getmedia","([BI)V");
	if(javaCallback == NULL)
	{
		ALOGD("mediaNormalData fail to find method nativeCallback");
		return; 
	}

   jbyteArray array = env->NewByteArray(len);
   
    if(array == NULL){  
        ALOGD("receive_callback: NewCharArray error.");  
        return;   
    }  
  	if(NULL == data)
		return;
    else
		env->SetByteArrayRegion(array,0,len,(jbyte*)data); 
	env->CallVoidMethod(g_obj,javaCallback,array,len); 

 	env->DeleteLocalRef(array);  
	// env->DeleteGlobalRef(g_obj);
	 env->DeleteLocalRef(javaClass);
	

	
}
void cmdVideoEncoderInitDone(S_VIDEO_ENCODER_INIT_DONE* videoEncoderInitDone){

}
void setVideoFormat(int width,int height){

	JNIEnv *env;

	//get env from g_JavaVM
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("setvideoformat fail to find javaClass");
		return; 
	}
	
	jmethodID javaCallback = env->GetMethodID(javaClass,"setVideoFormat","(II)V");
	if(javaCallback == NULL)
	{
		ALOGD("setvideoformat fail to find method nativeCallback");
		return; 
	}

	env->CallVoidMethod(g_obj,javaCallback,width,height);	
	
}



//video channel callback functions
void videoDataReceive(u8 *data, u32 len){

	JNIEnv *env;

	//get env from g_JavaVM
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("videoDataReceive fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"getVideo","([BI)V");
	if(javaCallback == NULL)
	{
		ALOGD("videoDataReceive fail to find method nativeCallback");
		return; 
	}

   jbyteArray array = env->NewByteArray(len);
   
    if(array == NULL){  
        ALOGD("receive_callback: NewCharArray error.");  
        return;   
    }  
  	if(NULL ==  data)
		return;
    else
		env->SetByteArrayRegion(array,0,len,(jbyte*)data); 
	env->CallVoidMethod(g_obj,javaCallback,array,len); 

 	env->DeleteLocalRef(array);  
	// env->DeleteGlobalRef(g_obj);
	 env->DeleteLocalRef(javaClass);  

}


void ttsNormalData(u8 *data, u32 len){
	 JNIEnv *env;
	
	 //get env from g_JavaVM
	 if(NULL ==  g_JavaVM)
	 	return;
	 else
	 	g_JavaVM->AttachCurrentThread(&env,NULL);
	 
	 //get class
	 jclass javaClass = env->GetObjectClass(g_obj);
	 if(javaClass == NULL)
	 {
		 ALOGD("ttsNormalData fail to find javaClass");
		 return; 
	 }
	
	 jmethodID javaCallback = env->GetMethodID(javaClass,"getTTS","([BI)V");
	 if(javaCallback == NULL)
	 {
		 ALOGD("ttsNormalData fail to find method nativeCallback");
		 return; 
	 }
	
	jbyteArray array = env->NewByteArray(len);
	
	 if(array == NULL){  
		 ALOGD("receive_callback: NewCharArray error.");  
		 return;   
	 }	
	if(NULL == data)
		return;
	 else
	 	env->SetByteArrayRegion(array,0,len,(jbyte*)data); 
	 env->CallVoidMethod(g_obj,javaCallback,array,len); 
	
	 env->DeleteLocalRef(array);  
	 // env->DeleteGlobalRef(g_obj);
	  env->DeleteLocalRef(javaClass);
 
  
}


//tts channel callback functions
void ttsInit(S_AUDIO_INIT_PARAMETER *initParam){

	JNIEnv *env;
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("ttsInit fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"setTTSFormat","(III)V");
	if(javaCallback == NULL)
	{
		ALOGD("ttsInit fail to find method nativeCallback");
		return; 
	}
	if(NULL == initParam)
		return;
	else
		env->CallVoidMethod(g_obj,javaCallback,initParam->sampleRate,initParam->channelConfig,initParam->sampleFormat);	

}

void vrNormalData(u8 *data, u32 len){
	JNIEnv *env;
	   
		//get env from g_JavaVM
		if(NULL ==	g_JavaVM)
		   return;
		else
		   g_JavaVM->AttachCurrentThread(&env,NULL);
		
		//get class
		jclass javaClass = env->GetObjectClass(g_obj);
		if(javaClass == NULL)
		{
			ALOGD("vrNormalData fail to find javaClass");
			return; 
		}
	   
		jmethodID javaCallback = env->GetMethodID(javaClass,"getVR","([BI)V");
		if(javaCallback == NULL)
		{
			ALOGD("vrNormalData fail to find method nativeCallback");
			return; 
		}
	   
	   jbyteArray array = env->NewByteArray(len);
	   
		if(array == NULL){	
			ALOGD("receive_callback: NewCharArray error.");  
			return;   
		}  
	   if(NULL == data)
		   return;
		else
		   env->SetByteArrayRegion(array,0,len,(jbyte*)data); 
		env->CallVoidMethod(g_obj,javaCallback,array,len); 
	   
		env->DeleteLocalRef(array);  
		// env->DeleteGlobalRef(g_obj);
		 env->DeleteLocalRef(javaClass);

}

//vr channel callback functions
void vrInit(S_AUDIO_INIT_PARAMETER *initParam){
	JNIEnv *env;
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("vrInit fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"setVRFormat","(III)V");
	if(javaCallback == NULL)
	{
		ALOGD("vrInit fail to find method nativeCallback");
		return; 
	}
	if(NULL == initParam)
		return;
	else
		env->CallVoidMethod(g_obj,javaCallback,initParam->sampleRate,initParam->channelConfig,initParam->sampleFormat);

}


//command channel callback functions
void cmdProtocolVersionMatchStatus(S_PROTOCOL_VERSION_MATCH_SATUS* status){
	cout<<"cmdProtocolVersionMatchStatus() is invoked"<<endl;
	cout<<"\tprotocol version match status: "<<status->matchStatus<<endl;
}

void cmdMDInfro(S_MD_INFO* mdInfro){
	cout<<"cmdMDInfro() is invoked"<<endl;
	cout<<"\tos: "<<mdInfro->os<<endl;
	cout<<"\tboard: "<<mdInfro->board<<endl;
	cout<<"\tbootloader: "<<mdInfro->bootloader<<endl;
	cout<<"\tbrand: "<<mdInfro->brand<<endl;
	cout<<"\tcpu_abi: "<<mdInfro->cpu_abi<<endl;
	cout<<"\tcpu_abi2: "<<mdInfro->cpu_abi2<<endl;
	cout<<"\tdevice: "<<mdInfro->device<<endl;
	cout<<"\tdisplay: "<<mdInfro->display<<endl;
	cout<<"\tfingerprint: "<<mdInfro->fingerprint<<endl;
	cout<<"\thardware: "<<mdInfro->hardware<<endl;
	cout<<"\thost: "<<mdInfro->host<<endl;
	cout<<"\tcid: "<<mdInfro->cid<<endl;
	cout<<"\tmanufacturer: "<<mdInfro->manufacturer<<endl;
	cout<<"\tmodel: "<<mdInfro->model<<endl;
	cout<<"\tproduct: "<<mdInfro->product<<endl;
	cout<<"\tserial: "<<mdInfro->serial<<endl;
	cout<<"\tcodename: "<<mdInfro->codename<<endl;
	cout<<"\tincremental: "<<mdInfro->incremental<<endl;
	cout<<"\trelease: "<<mdInfro->release<<endl;
	cout<<"\tsdk: "<<mdInfro->sdk<<endl;
	cout<<"\tsdk_int: "<<mdInfro->sdk_int<<endl;
	
}

void cmdMDBTPairInfro(BTPairInfo* info){
	cout<<"cmdMDBTPairInfro() is invoked"<<endl;
	cout<<"/taddress: "<<info->address<<endl;
	cout<<"/tpassKey: "<<info->passKey<<endl;
	cout<<"/thash: "<<info->hash<<endl;
	cout<<"/trandomizer: "<<info->randomizer<<endl;
	cout<<"/tuuid: "<<info->uuid<<endl;
	cout<<"/tname: "<<info->name<<endl;
	cout<<"/tstatus: "<<info->status<<endl;
}

void cmdVideoEncoderFrameRateChangeDone(S_VIDEO_ENCODER_FRAME_RATE_CHANGE_DONE* videoEncoderFrameRateChangeDone){
	cout<<"cmdVideoEncoderFrameRateChangeDone() is invoked"<<endl;
	cout<<"\tframeRate: "<<videoEncoderFrameRateChangeDone->frameRate<<endl;
}

void cmdTelStateChangeIncoming(){
	cout<<"cmdTelStateChangeIncoming() is invoked"<<endl;
}

void cmdTelStateChangeOutGoing(){
	cout<<"cmdTelStateChangeOutGoing() is invoked"<<endl;
}

void cmdTelStateChangeIdle(){
	cout<<"cmdTelStateChangeIdle() is invoked"<<endl;
}
void cmdTelStateChangeInCalling(){
	cout<<"cmdTelStateChangeInCalling() is invoked"<<endl;
}

void cmdScreenOn(){
	cout<<"cmdScreenOn() is invoked"<<endl;
}
void cmdScreenOff(){
	cout<<"cmdScreenOff() is invoked"<<endl;
}
void cmdScreenUserPresent(){
	cout<<"cmdScreenUserPresent() is invoked"<<endl;
}

void cmdForeground(){
	cout<<"cmdForeground() is invoked"<<endl;
}

void cmdBackground(){
	cout<<"cmdBackground() is invoked"<<endl;
}

void cmdGoToDeskTop(){
	cout<<"cmdGoToDeskTop() is invoked"<<endl;
}

void cmdMicRecordWakeupStart(){
	ALOGD("cmdMicRecordWakeupStart() is invoked");
}
void cmdMicRecordEnd(){

			JNIEnv *env;
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("setvideoformat fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"stopAudiorecord","()V");
	if(javaCallback == NULL)
	{
		ALOGD("setvideoformat fail to find method nativeCallback");
		return; 
	}

	env->CallVoidMethod(g_obj,javaCallback);
}

void cmdMicRecordRecogStart(){
	//ALOGD("cmdMicRecordRecogStart() is invoked");

		JNIEnv *env;
	if(NULL == g_JavaVM)
		return;
	else
		g_JavaVM->AttachCurrentThread(&env,NULL);
	
	//get class
	jclass javaClass = env->GetObjectClass(g_obj);
	if(javaClass == NULL)
	{
		ALOGD("setvideoformat fail to find javaClass");
		return; 
	}

	jmethodID javaCallback = env->GetMethodID(javaClass,"wakeUpAudiorecord","()V");
	if(javaCallback == NULL)
	{
		ALOGD("setvideoformat fail to find method nativeCallback");
		return; 
	}

	env->CallVoidMethod(g_obj,javaCallback);
	
}

void SendAudioRecordData(u8* data, int len)
{
	CCarLifeLib::getInstance()->sendVRRecordData(data, len,0);
}


//0x00010026
void cmdModuleStatus(S_MODULE_STATUS_LIST_MOBILE*){
	cout<<"cmdModuleStatus is invoked"<<endl;
}

//0x00010030
void cmdNaviNextTurnInfo(S_NAVI_NEXT_TURN_INFO*){
	cout<<"cmdNaviNextTurnInfo is invoked"<<endl;
}

//0x00010031
void cmdCarDataSubscribe(S_VEHICLE_INFO_LIST*){
	cout<<"cmdCarDataSubscribe is invoked"<<endl;
}

//0x00010033
void cmdCarDataSubscribeStart(S_VEHICLE_INFO_LIST*){	
	cout<<"cmdCarDataSubscribeStart is invoked"<<endl;
}

//0x00010034
void cmdCarDataSubscribeStop(S_VEHICLE_INFO_LIST*){
	cout<<"cmdCarDataSubscribeStop is invoked"<<endl;
}

//0x00010035
void cmdMediaInfo(S_MEDIA_INFO* info){
	cout<<"cmdMediaInfo is invoked"<<endl;
	
	cout<<"	`= "<<info->source<<endl;
	cout<<"song= "<<info->song<<endl;
	cout<<"artist= "<<info->artist<<endl;
	cout<<"album= "<<info->album<<endl;
	//cout<<"albumArt= "<<info->albumArt<<endl;
	cout<<"duration= "<<info->duration<<endl;
	cout<<"playlistNum= "<<info->playlistNum<<endl;
	cout<<"songId= "<<info->songId<<endl;
	cout<<"mode= "<<info->mode<<endl;
	
	
}

//0x00010036
void cmdMediaProgressBar(S_MEDIA_PROGRESS_BAR*){
	cout<<"cmdMediaProgressBar is invoked"<<endl;
}

//0x00010037
void cmdRegisterConnectException(S_CONNECTION_EXCEPTION*){
	cout<<"cmdRegisterConnectException is invoked"<<endl;
}

//0x00010038
void cmdRegisterRequestGoToForeground(void){
	cout<<"cmdRegisterRequestGoToForeground is invoked"<<endl;
}

//0x00010039
void cmdRegisterUIActionSound(void){
	cout<<"cmdRegisterUIActionSound is invoked"<<endl;
}

//0x00010049
void cmdRegisterMdAuthenResponse(S_AUTHEN_RESPONSE* response){
	S_HU_AUTHEN_RESULT result;

	cout<<"cmdRegisterMdAuthenResponse is invoked"<<endl;
	cout<<"encryptValue= "<<response->encryptValue<<endl;
	result.authenResult=true;
  CCarLifeLib::getInstance()->cmdHuAuthenResult(&result);


}

//0x00010051
void cmdRegisterFeatureConfigRequest(){
	cout<<"cmdRegisterFeatureConfigRequest is invoked"<<endl;

	setFocusUIConfig(1);
	//0x00018052
	CCarLifeLib::getInstance()->cmdFeatureConfigResponse(&configList);
}


void videoHeartBeat(){
	cout<<"videoHeartBeat() is invoked"<<endl;
	cout<<"\tvideo heart beat received!";
}


void mediaStop(){
	cout<<"mediaStop() is invoked"<<endl;
	cout<<"\tmedia stop status received!"<<endl;
}

void mediaPause(){
	cout<<"mediaPause() is invoked"<<endl;
	cout<<" \tmedia pause status received!"<<endl;
}

void mediaResume(){
	cout<<"mediaResume() is invoked"<<endl;
	cout<<"\tmedia resume status received!"<<endl;
}

void mediaSeek(){
	cout<<"mediaSeek() is invoked"<<endl;
	cout<<"\tmedia seek status received!"<<endl;
}




void ttsStop(){
	cout<<"ttsStop() is invoked"<<endl;
	cout<<"\ttts stop status received!"<<endl;
}




void vrStop(){
	cout<<"vrStop() is invoked"<<endl;
	cout<<"\tvr stop status received!"<<endl;
}







