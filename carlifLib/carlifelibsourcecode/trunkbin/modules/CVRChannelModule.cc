/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CVRChannelModule.h"
#include<iostream>

using namespace std;

CVRChannelModule* CVRChannelModule::pInstance=NULL;

CVRChannelModule* CVRChannelModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CVRChannelModule();
		}

	return pInstance;
}

bool CVRChannelModule::receiveVRPackageHead(){
	return tranRecvPackageProcess.receivePackageHead();
}

void CVRChannelModule::vrPackageHeadAnalysis(){
	tranRecvPackageProcess.packageHeadAnalysis();
}

bool CVRChannelModule::receiveVRData(){
	return tranRecvPackageProcess.receivePackageData();
}

void CVRChannelModule::vrDataAnalysis(){
	tranRecvPackageProcess.packageDataAnalysis();
}

int CVRChannelModule::sendVRRecordData(u8* data, u32 size, u32 timeStamp){
	return tranRecvPackageProcess.sendMicData(data, size, timeStamp);
}

void CVRChannelModule::vrRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	tranRecvPackageProcess.vrRegisterInit(pFunc);
}

void CVRChannelModule::vrRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	tranRecvPackageProcess.vrRegisterNormalData(pFunc);
}
void CVRChannelModule::vrRegisterStop(void (*pFunc)(void)){
	tranRecvPackageProcess.vrRegisterStop(pFunc);
}



















