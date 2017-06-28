/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CConnectionSetupModule.h"
#include "CConnectManager.h"
#include "CCarLifeLog.h"
#include <utils/Log.h>


using namespace std;

CConnectionSetupModule* CConnectionSetupModule::pInstance;

CConnectionSetupModule::CConnectionSetupModule(){
	CConnectionSetupModule::pInstance=NULL;
}

CConnectionSetupModule* CConnectionSetupModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CConnectionSetupModule();
		}

	return pInstance;
}

int CConnectionSetupModule::connectionSetup(){
	ALOGD("start execSocketForward");
	//adb forward for video, media, tts, vr, touch channels
	CConnectManager::getInstance()->execSocketForward();
	
	ALOGD("start createCmdSocket");
	//create socket for channels
	if(CConnectManager::getInstance()->createCmdSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create successfully!");
		ALOGD("cmd channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create failed!");
		ALOGD("cmd channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVideoSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create successfully!");	
		ALOGD("video channel socket create");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create failed!");
		ALOGD("video channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createMediaSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create successfully!");
		ALOGD("media channel socket create");
		}else{
		ALOGD("media channel socket create failed!");
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTTSSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVRSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTouchSocket()){
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create failed!");
		return -1;
			}

	return 0;
}

int CConnectionSetupModule::connectionSetup(string mdIPAddress){
	//create socket for channels
	if(CConnectManager::getInstance()->createCmdSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVideoSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createMediaSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTTSSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVRSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTouchSocket(mdIPAddress)){
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create failed!");
		return -1;
			}

	return 0;
}

int CConnectionSetupModule::connectionSetup(string mdIPAddress, string interfaceName){
	//create socket for channels
	if(CConnectManager::getInstance()->createCmdSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("cmd channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVideoSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("video channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createMediaSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("media channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTTSSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("tts channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createVRSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("vr channel socket create failed!");
		return -1;
			}
	if(CConnectManager::getInstance()->createTouchSocket(mdIPAddress, interfaceName)){
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create successfully!");
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("ctrl channel socket create failed!");
		return -1;
			}

	return 0;
}




































