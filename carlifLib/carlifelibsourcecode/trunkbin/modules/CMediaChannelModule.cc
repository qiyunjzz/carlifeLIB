/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CMediaChannelModule.h"
#include "CConnectManager.h"
#include<iostream>

using namespace std;

CMediaChannelModule* CMediaChannelModule::pInstance=NULL;

CMediaChannelModule* CMediaChannelModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CMediaChannelModule();
		}

	return pInstance;
}

bool CMediaChannelModule::receiveMediaPackageHead(){
	return tranRecvPackageProcess.receivePackageHead();
}

void CMediaChannelModule::mediaPackageHeadAnalysis(){
	tranRecvPackageProcess.packageHeadAnalysis();
}

bool CMediaChannelModule::receiveMediaData(){
	return tranRecvPackageProcess.receivePackageData();
}

void CMediaChannelModule::mediaDataAnalysis(){
	tranRecvPackageProcess.packageDataAnalysis();
}

void CMediaChannelModule::mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*)){
	tranRecvPackageProcess.mediaRegisterInit(pFunc);
}

void CMediaChannelModule::mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len)){
	tranRecvPackageProcess.mediaRegisterNormalData(pFunc);
}
void CMediaChannelModule::mediaRegisterStop(void (*pFunc)(void)){
	tranRecvPackageProcess.mediaRegisterStop(pFunc);
}
void CMediaChannelModule::mediaRegisterPause(void (*pFunc)(void)){
	tranRecvPackageProcess.mediaRegisterPause(pFunc);
}
void CMediaChannelModule::mediaRegisterResume(void (*pFunc)(void)){
	tranRecvPackageProcess.mediaRegisterResume(pFunc);
}
void CMediaChannelModule::mediaRegisterSeek(void (*pFunc)(void)){
	tranRecvPackageProcess.mediaRegisterSeek(pFunc);
}


















