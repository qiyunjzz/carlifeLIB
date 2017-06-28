/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CCtrlChannelModule.h"
#include<iostream>

using namespace std;

CCtrlChannelModule* CCtrlChannelModule::pInstance=NULL;

CCtrlChannelModule* CCtrlChannelModule::getInstance(){
	if(NULL==pInstance){
		pInstance= new CCtrlChannelModule();
		}

	return pInstance;
}

bool CCtrlChannelModule::receiveCtrlPackageHead(){
	return tranRecvPackageProcess.receivePackageHead();
}
void CCtrlChannelModule::ctrlPackageHeadAnalysis(){
	tranRecvPackageProcess.packageHeadAnalysis();
}

bool CCtrlChannelModule::receiveCtrlData(){
	return tranRecvPackageProcess.receivePackageData();
}

void CCtrlChannelModule::ctrlDataAnalysis(){
	tranRecvPackageProcess.packageDataAnalysis();
}

int CCtrlChannelModule::ctrlTouchAction(S_TOUCH_ACTION* touchAction){
	return tranRecvPackageProcess.sendCtrlTouchAction(touchAction);
}
int CCtrlChannelModule::ctrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown){
	return tranRecvPackageProcess.sendCtrlTouchActionDown(touchActionDown);
}
int CCtrlChannelModule::ctrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp){
	return tranRecvPackageProcess.sendCtrlTouchActionUp(touchActionUp);
}
int CCtrlChannelModule::ctrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove){
	return tranRecvPackageProcess.sendCtrlTouchActionMove(touchActionMove);
}
int CCtrlChannelModule::ctrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick){
	return tranRecvPackageProcess.sendCtrlTouchSigleClick(touchSingleClick);
}
int CCtrlChannelModule::ctrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick){
	return tranRecvPackageProcess.sendCtrlTouchDoubleClick(touchDoubleClick);
}
int CCtrlChannelModule::ctrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress){
	return tranRecvPackageProcess.sendCtrlTouchLongPress(touchLongPress);
}
int CCtrlChannelModule::ctrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode){
	return tranRecvPackageProcess.sendCtrlTouchCarHardKeyCode(touchCarHardKeyCode);
}
void CCtrlChannelModule::ctrlRegisterUIActionSound(void (*pFunc)(void)){
	tranRecvPackageProcess.ctrlRegisterUIActionSound(pFunc);
}






















