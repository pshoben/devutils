
#include <string>
#include <memory>
#include <typeinfo>
#include "MessageDataIf.h"
#include "emapi.h"
#include "EmapiTypes.h"
//#include "MessageTrace.h"
#include "TagwireDecoder.h"
#include "EmapiTagwireWrapper.h"

using std::string;

namespace emapi {

EmapiTagwireWrapper::EmapiTagwireWrapper(){}
//EmapiTagwireWrapper::EmapiTagwireWrapper(ByteArray& pByteArray){}
EmapiTagwireWrapper::~EmapiTagwireWrapper(){}

EmapiTagwireWrapper * EmapiTagwireWrapper::clone() const
{	
	EmapiTagwireWrapper* tClone = new EmapiTagwireWrapper();
	tClone->mMessage = mMessage;
	return tClone;
}
void EmapiTagwireWrapper::unpack( TagwireDecoder& pDecoder) 
{	
	mMessage = pDecoder.parseMessage();
}
void EmapiTagwireWrapper::pack( TagwireEncoder& pEncoder) const 
{
	mMessage->pack(pEncoder);
}
const int EmapiTagwireWrapper::getClassId() const
{
	return 0 ; //trick
}

const string EmapiTagwireWrapper::getMessageName() const
{
	return "EmapiTagwireWrapper";
}

void EmapiTagwireWrapper::setWrappedMessage( MessageDataIf * pMessage) 
{
	mMessage = pMessage;
}
MessageDataIf * EmapiTagwireWrapper::getWrappedMessage()
{
	return mMessage;
}

const string EmapiTagwireWrapper::to_string( string indent ) const
{
	if( mMessage )
		return mMessage->to_string( indent );
	else
		return indent + string("EmapiTagwireWrapper::null");
}
const int EmapiTagwireWrapper::getMessageType() const
{
	return 1 ; //trick
}

//void EmapiTagwireWrapper::traceMessage( MessageTrace * pTrace, int pLevel) const 
//{
//	// TODO
//} 

}

