/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CCarLifeLog.h"
#include"CommonUtil.h"

#define LOG_PREFIX "####CarLifeLog: "

void CCarLifeLog::carLifeLogWithPrefix(string log){
#ifdef LIB_LOG_SWITCH
	cout<<LOG_PREFIX<<log;
#endif
}

void CCarLifeLog::carLifeLog(string log){
#ifdef LIB_LOG_SWITCH
	cout<<log;
#endif
}

void CCarLifeLog::carLifeLogWithPrefix(int value){
#ifdef LIB_LOG_SWITCH
	cout<<LOG_PREFIX<<value;
#endif
}

void CCarLifeLog::carLifeLog(int value){
#ifdef LIB_LOG_SWITCH
	cout<<value;
#endif
}

void CCarLifeLog::carLifeLogLnWithPrefix(string log){
#ifdef LIB_LOG_SWITCH
	cout<<LOG_PREFIX<<log<<endl;
#endif
}

void CCarLifeLog::carLifeLogLn(string log){
#ifdef LIB_LOG_SWITCH
	cout<<log<<endl;
#endif
}

void CCarLifeLog::carLifeLogLnWithPrefix(int value){
#ifdef LIB_LOG_SWITCH
	cout<<LOG_PREFIX<<value<<endl;
#endif
}

void CCarLifeLog::carLifeLogLn(int value){
#ifdef LIB_LOG_SWITCH
	cout<<value<<endl;
#endif
}
















