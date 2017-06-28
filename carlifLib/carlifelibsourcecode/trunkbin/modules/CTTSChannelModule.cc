/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CTTSChannelModule.h"
#include "CConnectManager.h"
#include<iostream>

using namespace std;

CTTSChannelModule* CTTSChannelModule::pInstance=NULL;

CTTSChannelModule* CTTSChannelModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CTTSChannelModule();
		}

	return pInstance;
}

bool CTTSChannelModule::receiveTTSPackageHead(){
	return tranRecvPackageProcess.receivePackageHead();
}

void CTTSChannelModule::ttsPackageHeadAnalysis(){
	tranRecvPackageProcess.packageHeadAnalysis();
}

bool CTTSChannelModule::receiveTTSData(){
	return tranRecvPackageProcess.receivePackageData();
}

void CTTSChannelModule::ttsDataAnalysis(){
	tranRecvPackageProcess.packageDataAnalysis();
}

void CTTSChannelModule::ttsRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	tranRecvPackageProcess.ttsRegisterInit(pFunc);
}

void CTTSChannelModule::ttsRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	tranRecvPackageProcess.ttsRegisterNormalData(pFunc);
}
void CTTSChannelModule::ttsRegisterStop(void (*pFunc)(void)){
	tranRecvPackageProcess.ttsRegisterStop(pFunc);
}






















