/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_VIRTUAL_SHELL_H
#define C_VIRTUAL_SHELL_H

#define MAX_CMD_RET_LEN 1024*20

//#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "CommonUtil.h"

using namespace std;

struct CmdRet{
	bool ret;
	u8 data[MAX_CMD_RET_LEN];
	u32 len;
};

class CVirtualShell{
	public:
		static CVirtualShell* getInstance();

		bool doCmd(const string cmd);
		void doCmdWithResult(const string cmd, struct CmdRet* cmdRet);

	private:
		CVirtualShell();

		static CVirtualShell* pInstance;
		
};










































































#endif



























