#ifndef MessageTrace_H
#define MessageTrace_H

#include <stdio.h>
#include <memory>
#include <string.h>
#include <string>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include "EmapiTypes.h"
#include "ByteArray.h"
//#include "MessageDataIf.h"

namespace emapi
{
class MessageDataIf;
class MessageTrace
{
private:
	char *mBuffer;
	int mSize;
	int mPos;
	void ensureSpace( int pSize );
	void reallocOutBuffer();
	void addSpace( int pCount );
	void copyBuffer( int8 *pBuffer );
	void dumpByteArray( const ByteArray *pByteArray, int pLevel );

public:
	MessageTrace();
	~MessageTrace();

	void trace( const int8 * pAttrName, const bool *pValue, int pLevel );
	void trace( const int8 * pAttrName, const bool pValue, int pLevel );

	void trace( const int8 * pAttrName, const int32 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const int32 pValue, int pLevel );

	void trace( const int8 * pAttrName, const uint32 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const uint32 pValue, int pLevel );

	void trace( const int8 * pAttrName, const int8 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const int8 pValue, int pLevel );

	void trace( const int8 * pAttrName, const uint8 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const uint8 pValue, int pLevel );

	void trace( const int8 * pAttrName, const int16 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const int16 pValue, int pLevel );

	void trace( const int8 * pAttrName, const uint16 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const uint16 pValue, int pLevel );

	void trace( const int8 * pAttrName, const int64 *pValue, int pLevel );
	void trace( const int8 * pAttrName, const int64 pValue, int pLevel );

	void trace( const int8 * pAttrName, const float *pValue, int pLevel );
	void trace( const int8 * pAttrName, const float pValue, int pLevel );

	void trace( const int8 * pAttrName, const double *pValue, int pLevel );
	void trace( const int8 * pAttrName, const double pValue, int pLevel );

	void trace( const int8 * pAttrName, const std::string *pValue, int pLevel );
	void trace( const int8 * pAttrName, const std::string &pValue, int pLevel );

	void trace( const int8 * pAttrName, const ByteArray *pByteArray, int pLevel );

	//traceMessage( const int8 * pStringName, const MessageDataIf *pMessage, const int8 * pAttrName, int32 pLevel );
	//traceAddString( int32 pLevel, const int * pFormat, ... );
	
	int getLength();
	char * toString();
};
}
#endif

