/*
 * CanSocketFactory.cpp
 *
 *  Created on: 24.09.2017
 *      Author: rauser
 */

#include "SocketCanFactory.h"

/*************************************************************************//***
 *
 * Includes
 * 
 * ***************************************************************************/
#include <stdexcept>

#ifdef __linux__
	#include "../linux/SocketCanLinux.h"
	#include "../linux/SocketCanInfoLinux.h"
	#include "../linux/SocketCanStatisticsLinux.h"
#else
	#error "No implementation found - Only Linux is implemented" 
#endif

#include "../buffer/CanBufferRegistry.h"

#include "logger.h"

namespace CanSocket
{

/*************************************************************************//***
 *
 * Main
 * 
 * ***************************************************************************/
#ifdef __linux__
	#define SocketCanCreate           SocketCanLinux
	#define SocketCanInfoCreate       SocketCanInfoLinux
	#define SocketCanStatisticsCreate SocketCanStatisticsLinux
#else
	#error "No implementation found - Only Linux is implemented."
#endif

SocketCanFactory::SocketCanFactory()
{
}

SocketCanFactory::~SocketCanFactory()
{
}

CanBufferPtr SocketCanFactory::createCanBuffer( const std::string& type, const unsigned int size  )
{
	if( CAN_BUFFER_REGISTRATION == nullptr )
	{
		throw std::runtime_error("Internal error: CanBuffer registration is not initialized");
	}
	
	std::string buffer_type = type;
	if( type == "default" )
	{
		buffer_type = "Queue";
	}
	
	if( !CAN_BUFFER_REGISTRATION->isRegisteredClass( buffer_type ) )
	{
		throw std::invalid_argument("CanBuffer type is unknown");
	}
	
	return CanBufferPtr( CAN_BUFFER_REGISTRATION->get( buffer_type, size ) );
}

SocketCanPtr SocketCanFactory::createSocketCan(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCan( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCan>(new SocketCanCreate(device));
}

SocketCanInfoPtr SocketCanFactory::createSocketCanInfo(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanInfo( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCanInfo>(new SocketCanInfoCreate(device));
}

SocketCanStatisticsPtr SocketCanFactory::createSocketCanStatistics(const std::string& device)
{
	LOGGER( SOCKETCAN_INFO, "SocketCanFactory::createSocketCanStatistics( %s )", device.c_str() );
	if (device.empty())
	{
		throw std::invalid_argument( "Device is empty" );
	}
	return std::shared_ptr<SocketCanStatistics>(new SocketCanStatisticsCreate(device));
}


} /* namespace CanSocket */
