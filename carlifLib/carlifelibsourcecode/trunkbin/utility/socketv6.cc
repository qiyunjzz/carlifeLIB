/*******************************************************
	Author: 
		Liu Caiquan
	Date: 
		@17th-June-2016@

	CarLife Protocol version:
		@V1.0.12@
							Copyright (C) Under BaiDu, Inc.
*******************************************************/
#include "socketv6.h"
#include <iostream>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include<net/if.h>
#include "CommonUtil.h"
#include "CCarLifeLog.h"

using namespace std;

const int MAXCONNECTIONS = 10;

Socketv6::Socketv6() : m_sock ( -1 )
{
    memset(&m_addr, 0, sizeof ( m_addr ) );
}

Socketv6::~Socketv6()
{
    if ( is_valid() )::close ( m_sock );
}

bool Socketv6::create()
{
    m_sock = socket ( AF_INET6, SOCK_STREAM, 0 );
    if ( ! is_valid() )
        return false;
/*
    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return false;
*/
    return true;
}


/*
bool Socketv6::bind ( const u32 port )
{
    if ( ! is_valid() )
    {
        return false;
    }

    m_addr.sin6_family = AF_INET6;
    m_addr.sin6_addr = in6addr_any;
    m_addr.sin6_port = htons ( port );

    int bind_return = ::bind ( m_sock, ( struct sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( bind_return == -1 )
    {
        return false;
    }

    return true;
}

bool Socketv6::listen() const
{
    if ( ! is_valid() )
    {
        return false;
    }

    int listen_return = ::listen ( m_sock, MAXCONNECTIONS );

    if ( listen_return == -1 )
    {
        return false;
    }

    return true;
}
*/
/*
bool Socketv6::accept ( Socket& new_socket ) const
{
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        return false;
    else
        return true;
}
*/

u32 Socketv6::send ( const std::string s ) const
{
    return ::send ( m_sock, s.c_str(), s.size(), MSG_NOSIGNAL );
}


bool Socketv6::send(u8* buf,u32 len) const
{
    int number = 0;
    while( len > 0 )
    {
        //LOG_DEBUG(mformat("writeData(): begin write packet +++, fd = %d", client_s));
        number = ::send(m_sock, buf, len, MSG_NOSIGNAL);
        //LOG_DEBUG(mformat("writeData(): end write packet +++, fd = %d", client_s));
        if( number > 0 )
        {
            len -= number;
            buf += number;
        }
        else
        {
	     CCarLifeLog::carLifeLogWithPrefix("writeData(): fd = ");
	     CCarLifeLog::carLifeLog(m_sock);
	     CCarLifeLog::carLifeLog(", ret = ");
	     CCarLifeLog::carLifeLog(number);
	     CCarLifeLog::carLifeLog(", errno = ");
	     CCarLifeLog::carLifeLog(errno);
	     CCarLifeLog::carLifeLog(": ");
	     CCarLifeLog::carLifeLog(strerror(errno));
	     CCarLifeLog::carLifeLog("\n");
            
            if(number < 0 && (errno == EINTR)) continue;
            return false;
        }
    }
    return true;
}

bool Socketv6::recv(u8* buf,u32 len) const
{
    //memset ( buf, 0, lenth );
    int number = 0;

    while( len > 0 )
    {
         number = ::recv(m_sock, buf, len, 0);
        if(  number > 0 )
        {
            len -= number;
            buf += number;
        }
        else
        {
	     CCarLifeLog::carLifeLogWithPrefix("writeData(): fd = ");
	     CCarLifeLog::carLifeLog(m_sock);
	     CCarLifeLog::carLifeLog(", ret = ");
	     CCarLifeLog::carLifeLog(number);
	     CCarLifeLog::carLifeLog(", errno = ");
	     CCarLifeLog::carLifeLog(errno);
	     CCarLifeLog::carLifeLog(": ");
	     CCarLifeLog::carLifeLog(strerror(errno));
	     CCarLifeLog::carLifeLog("\n");
           
            if(number < 0 && (errno == EINTR)) continue;
            return false;
        }
    }

    return true;
}


bool Socketv6::connect ( const std::string host, const u32 port, string interfaceName )
{
    if ( ! is_valid() ){
		CCarLifeLog::carLifeLogLnWithPrefix("connect: is_valid failed");
		return false;
    }

    m_addr.sin6_family = AF_INET6;
    m_addr.sin6_port = htons ( port );


    if(interfaceName.size()!=0){
		m_addr.sin6_scope_id=if_nametoindex(interfaceName.c_str());
    }

    int status = inet_pton ( AF_INET6, host.c_str(), &m_addr.sin6_addr );

    if ( errno == EAFNOSUPPORT ){
		CCarLifeLog::carLifeLogLnWithPrefix("connect: errno == EAFNOSUPPORT failed");
		
		return false;
    }

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( status == 0 ){
        return true;
    }else{
       CCarLifeLog::carLifeLogWithPrefix("connect status= ");
	CCarLifeLog::carLifeLog(status);
	CCarLifeLog::carLifeLogLn(" :failed");
        return false;
    }
}

void Socketv6::set_non_blocking ( const bool b )
{
    int opts;

    opts = fcntl ( m_sock, F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock,F_SETFL,opts );
}
















