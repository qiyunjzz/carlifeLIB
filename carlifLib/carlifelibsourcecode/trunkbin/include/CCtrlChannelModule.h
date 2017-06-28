/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_CTRL_CHANNEL_MODULE_H
#define C_CTRL_CHANNEL_MODULE_H

#include "CTranRecvPackageProcess.h"

class CCtrlChannelModule{
	public:
		static CCtrlChannelModule* getInstance();

		bool receiveCtrlPackageHead();
		void ctrlPackageHeadAnalysis();

		bool receiveCtrlData();
		void ctrlDataAnalysis();

		int ctrlTouchAction(S_TOUCH_ACTION* touchAction);
		int ctrlTouchActionDown(S_TOUCH_ACTION_DOWN* touchActionDown);
		int ctrlTouchActionUp(S_TOUCH_ACTION_UP* touchActionUp);
		int ctrlTouchActionMove(S_TOUCH_ACTION_MOVE* touchActionMove);
		int ctrlTouchSigleClick(S_TOUCH_SIGNAL_CLICK* touchSingleClick);
		int ctrlTouchDoubleClick(S_TOUCH_DOUBLE_CLICK* touchDoubleClick);
		int ctrlTouchLongPress(S_TOUCH_LONG_PRESS* touchLongPress);
		int ctrlTouchCarHardKeyCode(S_TOUCH_CAR_HARD_KEY_CODE* touchCarHardKeyCode);
		void ctrlRegisterUIActionSound(void (*pFunc)(void));

	private:
		CCtrlChannelModule():tranRecvPackageProcess(CTRL_CHANNEL){
			}
		
		static CCtrlChannelModule* pInstance;

		CTranRecvPackageProcess tranRecvPackageProcess;
};

























































#endif
































