/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CVirtualShell.h"
#include"CCarLifeLog.h"
#include<utils/Log.h>

CVirtualShell* CVirtualShell::pInstance=NULL;

CVirtualShell::CVirtualShell(){
}

CVirtualShell* CVirtualShell::getInstance(){
	if(NULL==pInstance){
		pInstance=new CVirtualShell();
		}

	return pInstance;
}

bool CVirtualShell::doCmd(const string cmd){
	if(""==cmd){
		CCarLifeLog::carLifeLogLnWithPrefix("please input valid command!");	
		return false;
		}

	FILE *file=popen(cmd.c_str(), "r");

	if(NULL==file){
		CCarLifeLog::carLifeLogLnWithPrefix("popen() excute failed!");
		
		return false;
		}

	//char retData[MAX_CMD_RET_LEN];
	//fread(retData, sizeof(char), MAX_CMD_RET_LEN-1, file);
	//retData[MAX_CMD_RET_LEN-1]='\0';

	//CCarLifeLog::carLifeLogLn(retData);
	
	return (pclose(file)==0);
}

void CVirtualShell::doCmdWithResult(const string cmd, CmdRet * cmdRet){
	if(NULL!=cmdRet){
		memset(cmdRet, '\0', sizeof(CmdRet));
		}else{
		CCarLifeLog::carLifeLogLnWithPrefix("cmdRet is NULL");
		ALOGD("cmdRet is NULL");
		return;
			}

		if(""==cmd){
			cmdRet->ret=false;
			CCarLifeLog::carLifeLogLnWithPrefix("cmd is empty!");
			ALOGD("cmd is empty!");
			return;
			}

		FILE* file=popen(cmd.c_str(), "r");

		if(NULL==file){
			cmdRet->ret=false;
			CCarLifeLog::carLifeLogLnWithPrefix("popen() is failed!");
			ALOGD("popen() is failed!");
			return;
			}
		
		cmdRet->len=fread(cmdRet->data, sizeof(char), MAX_CMD_RET_LEN-1, file);

		CCarLifeLog::carLifeLogWithPrefix("doCmdWithResult return len: ");
		CCarLifeLog::carLifeLogLn(cmdRet->len);

		cmdRet->ret=(pclose(file)==0);
		ALOGD("popen() is success");
}


























