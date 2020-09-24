#include <memory>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algortihm>
#include "EmapiSession.h"
#include "emapi.h"
#include "emapi_status.h"
#include "Transport.h"
#include "EmapiOal.h"
#include "Logger.h"
#include "EmapiSessionImpl.h"
#include "EmapiSessionDb.h"
#include "EmapiException.h"
#include "EmapiTagwireWrapper.h"
#include "TagwireDecoder.h"
#include "TagwireEncoder.h"

#define LLL printf("%s %s:%d \n", __FUNCTION__, __FILE__, __LINE__ );

void EmapiSessionImpl::threadMain()
{
	int tStatus = 0;
	
	tStatus = mSocket>0 ? tcpipRead( mSocket, tHeader.getBytes(), tHeader.getHeaderSize( )) : EMAPI_STS_CONNCLOSED;

	if ( tStatus ) {
		LLL
		return;
	}
	// check header
	if ( memcmp( EMAPI_MAGIC_SIGN, tHeader.getMagicSign(), strlen(AMAPI_MAGIC_SIGN)) != 0) {
		LLL	
		return;
	}
	int tSize = tHeader.getMEssageSize();
	std::auto_ptr<tByteArray> tByteArray = ByteArray(new ByteArray( tSize ));
	if (!tByteArray.get()) {
		return;
	}
	
	tStatus = tcpipRead( mSocket, tByteArray->getBytes(), tSize );
	if ( tStatus ) {
		return;
	}
	// decode message
	std::auto_ptr<TagwireDecoder> tDecoder;
	std::auto_ptr<EmapiTagwireWrapper> tWrapper;
	try {
		tDecoder.reset( new TagwireDecoder( tByteArray.get(), 0, tByteArray.get()->length( )));
		tWrapper.reset( new EmapiTagwireWrapper( ));
		if( !tDecoder.get() || !tWrapper.get( )) {
			throw RuntimeException( "no memory for", -1 );
		}
		tWrapper->unpack( *tDecoder.get( ));
	
	catch (const RuntimeException & e) {
		LLL
		return;
	}
	catch (const std::exception & e) {
		LLL		
		return;
	}
	catch (...) {
		LLL
		return;
	}





