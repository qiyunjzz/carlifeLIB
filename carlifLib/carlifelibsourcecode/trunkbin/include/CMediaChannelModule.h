/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_MEDIA_CHANNEL_MODULE
#define C_MEDIA_CHANNEL_MODULE
#include "CTranRecvPackageProcess.h"

class CMediaChannelModule{
	public:
		static CMediaChannelModule* getInstance();

		bool receiveMediaPackageHead();
		void mediaPackageHeadAnalysis();

		bool receiveMediaData();
		void mediaDataAnalysis();

		void mediaRegisterInit(void (*pFunc)(S_AUDIO_INIT_PARAMETER*));
		void mediaRegisterNormalData(void (*pFunc)(u8 *data, u32 len));
		void mediaRegisterStop(void (*pFunc)(void));
		void mediaRegisterPause(void (*pFunc)(void));
		void mediaRegisterResume(void (*pFunc)(void));
		void mediaRegisterSeek(void (*pFunc)(void));

	private:
		CMediaChannelModule():tranRecvPackageProcess(MEDIA_CHANNEL){
			}
		
		static CMediaChannelModule* pInstance;

		CTranRecvPackageProcess tranRecvPackageProcess;
};





































#endif








































