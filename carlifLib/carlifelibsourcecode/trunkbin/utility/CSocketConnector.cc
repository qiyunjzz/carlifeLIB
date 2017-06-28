/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "CSocketConnector.h"
#include "CCarLifeLog.h"
#include <utils/Log.h>

using namespace std;

CSocketConnector::CSocketConnector(string serverIP, u32 port, string interfaceName)
{
	ALOGD("serverIP = %s,port = %d,interfaceName = %s",serverIP.c_str(),port,interfaceName.c_str());

    if(serverIP.find(":",0)!=string::npos){
	CCarLifeLog::carLifeLogLnWithPrefix("iSockset=&socketv6");
	iSockset=&socketv6;
    }else{
    	CCarLifeLog::carLifeLogLnWithPrefix("iSockset=&socket");
    	iSockset=&socket;
    }
	
    setConnectStatus(false);

    mdServerIP = serverIP;
    mdServerPort = port;
    networkCardInterfaceName=interfaceName;
}
CSocketConnector::~CSocketConnector()
{

}

bool CSocketConnector::getConnectStatus()
{
    return isConnected;
}

bool CSocketConnector::connectToServer()
{
    if ( ! iSockset->create() )
    {
	CCarLifeLog::carLifeLogLnWithPrefix("socket.create fail!");
	ALOGD("socket.create fail!");
        return false;
    }

    if ( ! iSockset->connect ( mdServerIP, mdServerPort, networkCardInterfaceName ) )
    {	
	CCarLifeLog::carLifeLogWithPrefix("mdServerIP: ");
	CCarLifeLog::carLifeLog(mdServerIP);
	CCarLifeLog::carLifeLog(" mdServerPort: ");
	CCarLifeLog::carLifeLog(mdServerPort);
	CCarLifeLog::carLifeLog("\n");
	
	CCarLifeLog::carLifeLogLnWithPrefix("socket.connect fail!");
	ALOGD("socket.connect fail!");
        return false;
    }
    setConnectStatus(true);
    return true;
}

























