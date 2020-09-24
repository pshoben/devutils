#ifndef EmapiTagwireWrapper_H
#define EmapiTagwireWrapper_H

#include <string>
#include <memory>
#include <typeinfo>
#include "MessageDataIf.h"
#include "emapi.h"
#include "EmapiTypes.h"
//#include "MessageTrace.h"

using std::string;

namespace emapi {

class EmapiTagwireWrapper : public MessageDataIf
{
public:
	EmapiTagwireWrapper();
	EmapiTagwireWrapper(ByteArray& pByteArray);
	virtual ~EmapiTagwireWrapper();

	virtual const string toString() const;
	virtual const int getMessageType() const;

	virtual void pack( TagwireEncoder& pEncoder) const ;
	virtual void unpack( TagwireDecoder& pDecoder) ;
	
	virtual const int getClassId() const;
	virtual const string getMessageName() const;
	//virtual void traceMessage( MessageTrace * pTrace, int pLevel) const ; 
	virtual EmapiTagwireWrapper * clone() const;

	void setWrappedMessage( MessageDataIf * pMessage) ;
	MessageDataIf * getWrappedMessage();

private:
	MessageDataIf * mMessage;
};

}

#endif

