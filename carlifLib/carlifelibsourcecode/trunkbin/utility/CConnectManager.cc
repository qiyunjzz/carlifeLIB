/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include"CConnectManager.h"
#include"CVirtualShell.h"
#include"CCarLifeLog.h"
#include <utils/Log.h>


using namespace std;

CConnectManager* CConnectManager::pInstance=NULL;
CmdRet CConnectManager::cmdRet;

CConnectManager::CConnectManager(){
	cmdSocket=NULL;
	videoSocket=NULL;
	mediaSocket=NULL;
	ttsSocket=NULL;
	vrSocket=NULL;
	ctrlSocket=NULL;
}

CConnectManager::~CConnectManager(){
	delete cmdSocket;
	cmdSocket=NULL;

	delete videoSocket;
	videoSocket=NULL;

	delete mediaSocket;
	mediaSocket=NULL;

	delete ttsSocket;
	ttsSocket=NULL;

	delete vrSocket;
	vrSocket=NULL;

	delete ctrlSocket;
	ctrlSocket=NULL;
}

CConnectManager* CConnectManager::getInstance(){
	if(NULL==pInstance){
		pInstance=new CConnectManager();
		}

	return pInstance;
}

bool CConnectManager::startBdclServerAsRoot(){

	return true;
}

bool CConnectManager::execGetDeviceCmd(){
	return true;
}

bool CConnectManager::execSocketForward(){
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_CMD, &cmdRet);
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_VIDEO, &cmdRet);
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_MEDIA, &cmdRet);
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_TTS, &cmdRet);
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_VR, &cmdRet);
	CVirtualShell::getInstance()->doCmdWithResult(ADB_FORWARD_TOUCH, &cmdRet);

	//for testing
	/*
	CVirtualShell::getInstance()->doCmdWithResult("ps", &cmdRet);
	cout<<"ps return result: "<<endl;
	for(int i=0; i<cmdRet.len;i++){
		cout<<cmdRet.data[i]<<" ";
	}
	cout<<endl;
	*/
	
	return true;
}

bool CConnectManager::execGetPropCmd(){
	return true;
}

bool CConnectManager::execStartCarlife(){
	return true;
}

bool CConnectManager::execKillBdsc(){
	return true;
}

bool CConnectManager::execStartBdsc(){
	return true;
}

//cmd
bool CConnectManager::createCmdSocket(){
	cmdSocket=new CSocketConnector(LOCAL_IP_ADDR, CMD_SOCKET_PORT_HU, "");
	if(NULL == cmdSocket){
		ALOGD("new cmdSocket fail");
	}
	else
	{
		ALOGD("new cmdSocket success");
	}

	if(cmdSocket->connectToServer()){
		ALOGD("cmdSocket=TRUE;");
		return true;
	}else{
		delete cmdSocket;
		cmdSocket=NULL;
		ALOGD("cmdSocket=NULL;");
		return false;
	}
}

bool CConnectManager::createCmdSocket(string mdIPAddress){
	cmdSocket=new CSocketConnector(mdIPAddress, CMD_SOCKET_PORT_MD, "");

	if(cmdSocket->connectToServer()){
		return true;
	}else{
		delete cmdSocket;
		cmdSocket=NULL;
		return false;
	}
}

bool CConnectManager::createCmdSocket(string mdIPAddress, string interfaceName){
	cmdSocket=new CSocketConnector(mdIPAddress, CMD_SOCKET_PORT_MD, interfaceName);

	if(cmdSocket->connectToServer()){
		return true;
	}else{
		delete cmdSocket;
		cmdSocket=NULL;
		return false;
	}
}


//video
bool CConnectManager::createVideoSocket(){
	videoSocket=new CSocketConnector(LOCAL_IP_ADDR, VIDEO_SOCKET_PORT_HU, "");

	if(videoSocket->connectToServer()){
		return true;
	}else{
		delete videoSocket;
		videoSocket=NULL;
		return false;
	}
}
bool CConnectManager::createVideoSocket(string mdIPAddress){
	videoSocket=new CSocketConnector(mdIPAddress, VIDEO_SOCKET_PORT_MD, "");

	if(videoSocket->connectToServer()){
		return true;
	}else{
		delete videoSocket;
		videoSocket=NULL;
		return false;
	}
}

bool CConnectManager::createVideoSocket(string mdIPAddress, string interfaceName){
	videoSocket=new CSocketConnector(mdIPAddress, VIDEO_SOCKET_PORT_MD, interfaceName);

	if(videoSocket->connectToServer()){
		return true;
	}else{
		delete videoSocket;
		videoSocket=NULL;
		return false;
	}
}

//media
bool CConnectManager::createMediaSocket(){
	mediaSocket=new CSocketConnector(LOCAL_IP_ADDR, MEDIA_SOCKET_PORT_HU, "");

	if(mediaSocket->connectToServer()){
		return true;
	}else{
		delete mediaSocket;
		mediaSocket=NULL;
		return false;
	}
}
bool CConnectManager::createMediaSocket(string mdIPAddress){
	mediaSocket=new CSocketConnector(mdIPAddress, MEDIA_SOCKET_PORT_MD, "");

	if(mediaSocket->connectToServer()){
		return true;
	}else{
		delete mediaSocket;
		mediaSocket=NULL;
		return false;
	}
}

bool CConnectManager::createMediaSocket(string mdIPAddress, string interfaceName){
	mediaSocket=new CSocketConnector(mdIPAddress, MEDIA_SOCKET_PORT_MD, interfaceName);

	if(mediaSocket->connectToServer()){
		return true;
	}else{
		delete mediaSocket;
		mediaSocket=NULL;
		return false;
	}
}

//navi tts
bool CConnectManager::createTTSSocket(){
	ttsSocket=new CSocketConnector(LOCAL_IP_ADDR, TTS_SOCKET_PORT_HU, "");

	if(ttsSocket->connectToServer()){
		return true;
	}else{
		delete ttsSocket;
		ttsSocket=NULL;
		return false;
	}
}
bool CConnectManager::createTTSSocket(string mdIPAddress){
	ttsSocket=new CSocketConnector(mdIPAddress, TTS_SOCKET_PORT_MD, "");

	if(ttsSocket->connectToServer()){
		return true;
	}else{
		delete ttsSocket;
		ttsSocket=NULL;
		return false;
	}
}

bool CConnectManager::createTTSSocket(string mdIPAddress, string interfaceName){
	ttsSocket=new CSocketConnector(mdIPAddress, TTS_SOCKET_PORT_MD, interfaceName);

	if(ttsSocket->connectToServer()){
		return true;
	}else{
		delete ttsSocket;
		ttsSocket=NULL;
		return false;
	}
}

//vr
bool CConnectManager::createVRSocket(){
	vrSocket=new CSocketConnector(LOCAL_IP_ADDR, VR_SOCKET_PORT_HU, "");

	if(vrSocket->connectToServer()){
		return true;
	}else{
		delete vrSocket;
		vrSocket=NULL;
		return false;
	}
}
bool CConnectManager::createVRSocket(string mdIPAddress){
	vrSocket=new CSocketConnector(mdIPAddress, VR_SOCKET_PORT_MD, "");

	if(vrSocket->connectToServer()){
		return true;
	}else{
		delete vrSocket;
		vrSocket=NULL;
		return false;
	}
}

bool CConnectManager::createVRSocket(string mdIPAddress, string interfaceName){
	vrSocket=new CSocketConnector(mdIPAddress, VR_SOCKET_PORT_MD, interfaceName);

	if(vrSocket->connectToServer()){
		return true;
	}else{
		delete vrSocket;
		vrSocket=NULL;
		return false;
	}
}

//toutch
bool CConnectManager::createTouchSocket(){
	ctrlSocket=new CSocketConnector(LOCAL_IP_ADDR, TOUCH_SOCKET_PORT_HU, "");

	if(ctrlSocket->connectToServer()){
		return true;
	}else{
		delete ctrlSocket;
		ctrlSocket=NULL;
		return false;
	}
}
bool CConnectManager::createTouchSocket(string mdIPAddress){
	ctrlSocket=new CSocketConnector(mdIPAddress, TOUCH_SOCKET_PORT_MD, "");

	if(ctrlSocket->connectToServer()){
		return true;
	}else{
		delete ctrlSocket;
		ctrlSocket=NULL;
		return false;
	}
}

bool CConnectManager::createTouchSocket(string mdIPAddress, string interfaceName){
	ctrlSocket=new CSocketConnector(mdIPAddress, TOUCH_SOCKET_PORT_MD, interfaceName);

	if(ctrlSocket->connectToServer()){
		return true;
	}else{
		delete ctrlSocket;
		ctrlSocket=NULL;
		return false;
	}
}

bool CConnectManager::readCmdData(u8* data, u32 len){
	if(NULL==cmdSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("cmdSocket is null!");
		return false;
		}
	
	if(!cmdSocket->iSockset->recv(data,  len)){
		cmdSocket->setConnectStatus(false);

		CCarLifeLog::carLifeLogLnWithPrefix("socket.recv is failed!");
		return false;
		}

	return true;
}
bool CConnectManager::writeCmdData(u8* data, u32 len){
	if(NULL==cmdSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("cmdSocket is null!");
		return false;
		}
	
	if(!cmdSocket->iSockset->send(data,  len)){
		cmdSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.send is failed!");
		return false;
		}

	return true;
}

bool CConnectManager::readVideoData(u8*data, u32 len){
	if(NULL==videoSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("videoSocket is null!");
		return false;
		}
	
	if(!videoSocket->iSockset->recv(data,  len)){

		videoSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.recv is failed!");
		return false;
		}

	return true;
}

bool CConnectManager::readMediaData(u8*data, u32 len){
	if(NULL==mediaSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("mediaSocket is null!");
		return false;
		}
	bool tmp;
	tmp = mediaSocket->iSockset->recv(data,  len);
	if(!tmp){
		mediaSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.recv is failed!");
		return false;
		}
	
	return true;
}

bool CConnectManager::readTTSData(u8*data, u32 len){
	if(NULL==ttsSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("ttsSocket is null!");
		return false;
		}
	
	if(!ttsSocket->iSockset->recv(data,  len)){
		ttsSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.recv is failed!");
		return false;
		}

	return true;
}

bool CConnectManager::readVRData(u8*data, u32 len){
	if(NULL==vrSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("vrSocket is null!");
		return false;
		}
	
	if(!vrSocket->iSockset->recv(data,  len)){
		vrSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.recv is failed!");
		return false;
		}

	return true;
}

bool CConnectManager::writeVRData(u8*data, u32 len){
	if(NULL==vrSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("vrSocket is null!");
		return false;
		}
	
	if(!vrSocket->iSockset->send(data,  len)){
		vrSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.send is failed!");
		return false;
		}

	return true;
}

bool CConnectManager::writeCtrlData(u8*data, u32 len){
	if(NULL==ctrlSocket){
		CCarLifeLog::carLifeLogLnWithPrefix("ctrlSocket is null!");
		return false;
		}
	
	if(!ctrlSocket->iSockset->send(data,  len)){
		ctrlSocket->setConnectStatus(false);
		CCarLifeLog::carLifeLogLnWithPrefix("socket.send is failed!");
		return false;
		}

	return true;
}





















