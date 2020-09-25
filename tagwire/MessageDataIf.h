#ifndef MessageDataIf_H
#define MessageDataIf_H

#define LIBEXPORT

#include <string>

//#include "MessageTrace.h"

using std::string;

namespace emapi {
	class TagwireEncoder;
	class TagwireDecoder;
	class LIBEXPORT MessageDataIf
	{
		public:
		virtual ~MessageDataIf() {}
		virtual void pack(TagwireEncoder& pEncode) const = 0;
		virtual void unpack(TagwireDecoder& pDecode) = 0;	
		virtual const int getClassId() const = 0;
		virtual const string getMessageName() const = 0;
		//virtual const string toString() const = 0;
		virtual const int getMessageType() const = 0;
		virtual const string to_string( string indent ) const = 0 ;
		//virtual void traceMessage( MessageTrace *pTrace, int pLevel ) const = 0;
		//virtual MessageDataIf* clone()  const = 0;
	};
	MessageDataIf * getMessageClass(int tag);
}

#endif
	
