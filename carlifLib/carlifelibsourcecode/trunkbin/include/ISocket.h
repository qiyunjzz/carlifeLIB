/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#ifndef I_SOCKET_H
#define I_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "CommonUtil.h"

class ISocket
{
public:
    virtual bool create()=0;
	
    // Server initialization
    //virtual bool bind ( const u32 port )=0;
    //virtual bool listen() const=0;
    //virtual bool accept ( Socket& ) const=0;

    // Client initialization
    virtual bool connect ( const std::string host, const u32 port, std::string interfaceName )=0;

    // Data Transimission
    virtual u32 send ( const std::string ) const=0;

    virtual bool recv(u8* buf,u32 lenth) const=0;
    virtual bool send(u8* buf,u32 lenth) const=0;

    virtual void set_non_blocking ( const bool )=0;

    virtual bool is_valid() const=0;

};
#endif // SOCKET_H





















