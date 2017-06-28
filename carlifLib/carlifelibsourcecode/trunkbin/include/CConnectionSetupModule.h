/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_CONNECTION_SETUP_MODULE
#define C_CONNECTION_SETUP_MODULE
#include "CTranRecvPackageProcess.h"

class CConnectionSetupModule{
	public:
		static CConnectionSetupModule* getInstance();

		int connectionSetup();
		int connectionSetup(string mdIPAddress);
		int connectionSetup(string mdIPAddress, string interfaceName);

	private:
		CConnectionSetupModule();
		
		static CConnectionSetupModule* pInstance;
};


































#endif

