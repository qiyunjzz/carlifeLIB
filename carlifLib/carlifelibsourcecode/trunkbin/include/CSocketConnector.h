/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef C_SOCKET_CONNECTOR_H
#define C_SOCKET_CONNECTOR_H

#include"socket.h"
#include"socketv6.h"
#include <string>
#include "CommonUtil.h"
#include "ISocket.h"

using namespace std;

class CSocketConnector{
public:
	CSocketConnector(string, u32, string);
	~CSocketConnector();
	
    	bool connectToServer();

   	 bool getConnectStatus();
  	 void setConnectStatus(bool status) { isConnected = status;}

public:
	ISocket *iSockset;
       Socket socket;
	Socketv6 socketv6;
	   
private:
   	 string mdServerIP;
   	 u32 mdServerPort;
	 string networkCardInterfaceName;
   	 bool isConnected;
};

























































#endif






















