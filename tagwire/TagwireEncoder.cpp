#include "MessageDataIf.h"
#include "TagwireEncoder.h"
//#include "ByteArray.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace emapi {

		
TagwireEncoder::~TagwireEncoder()
{
		if (mBuffer)
			delete[] mBuffer;
}

unsigned char * TagwireEncoder::getBuffer() { return mBuffer; }
unsigned int * TagwireEncoder::getLength() { return &mIndex; }	


TagwireEncoder& TagwireEncoder::beginGroup()
{
	appendChar(TAGWIRE_OPEN);
	mPrecededByAttribute = false;
	return *this;
}
TagwireEncoder& TagwireEncoder::endGroup()
{
	appendChar(TAGWIRE_CLOSE);
	mPrecededByAttribute = true;
	return *this;			
}

TagwireEncoder& TagwireEncoder::appendBoolean (int pAttributeNumber, bool pValue)
{
		beginAttribute(pAttributeNumber);
		appendChar(pValue ? TAGWIRE_TRUE : TAGWIRE_FALSE);
		return *this;	
}

TagwireEncoder& TagwireEncoder::appendInteger (int pAttributeNumber, int32 pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<int32>(pValue);
		}
		return *this;			
}

TagwireEncoder& TagwireEncoder::appendLong (int pAttributeNumber, int64 pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<int64>(pValue);
		}
		return *this;			
}
	
TagwireEncoder& TagwireEncoder::appendByte (int pAttributeNumber, byte pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<byte>(pValue);
		}
		return *this;			
}
		

TagwireEncoder& TagwireEncoder::appendString (int pAttributeNumber, const string* pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			escapeAndAppendUtf8(pValue);
		}			
		return *this;			
}
	
TagwireEncoder& TagwireEncoder::appendBoolean (int pAttributeNumber, bool* pValue)
{
		beginAttribute(pAttributeNumber);
		appendChar(*pValue ? TAGWIRE_TRUE : TAGWIRE_FALSE);
		return *this;	
}
	
TagwireEncoder& TagwireEncoder::appendInteger (int pAttributeNumber, int32* pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<int32>(*pValue);
		}
		return *this;			
}
	
TagwireEncoder& TagwireEncoder::appendLong (int pAttributeNumber, int64* pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<int64>(*pValue);
		}
		return *this;			
}
	
TagwireEncoder& TagwireEncoder::appendByte (int pAttributeNumber, byte* pValue)
{
		if(pValue!=NULL) {
			beginAttribute(pAttributeNumber);
			appendInteger<byte>(*pValue);
		}
		return *this;			
}
	
void TagwireEncoder::appendIntegerInt8(const int8 pValue)
{
	if(pValue==0)
		appendChar('0');
	else {
		unsigned char tTmp[21];
		unsigned int tChars = 0;
		if( pValue>0) {
			int8 tTmpVal = pValue;
			while (tTmpVal >0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[tTmpVal%10];
				tTmpVal /=10;
			}
		} else {
			int8 tTmpVal = pValue;
			while(tTmpVal<0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[-tTmpVal % 10];
				tTmpVal /=10;
			}
			tTmp[tChars++] ='-';
		}
		ensureCapacity(tChars);
		while(tChars>0)
		{
			mBuffer[mIndex++] = tTmp[--tChars];
		}
	}
}
	
void TagwireEncoder::appendIntegerInt16(const int16 pValue)
{
	if(pValue==0)
		appendChar('0');
	else {
		unsigned char tTmp[21];
		unsigned int tChars = 0;
		if( pValue>0) {
			int16 tTmpVal = pValue;
			while (tTmpVal >0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[tTmpVal%10];
				tTmpVal /=10;
			}
		} else {
			int16 tTmpVal = pValue;
			while(tTmpVal<0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[-tTmpVal % 10];
				tTmpVal /=10;
			}
			tTmp[tChars++] ='-';
		}
		ensureCapacity(tChars);
		while(tChars>0)
		{
			mBuffer[mIndex++] = tTmp[--tChars];
		}
	}
}
	
void TagwireEncoder::appendIntegerInt32(const int32 pValue)
{
	if(pValue==0)
		appendChar('0');
	else {
		unsigned char tTmp[21];
		unsigned int tChars = 0;
		if( pValue>0) {
			int32 tTmpVal = pValue;
			while (tTmpVal >0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[tTmpVal%10];
				tTmpVal /=10;
			}
		} else {
			int32 tTmpVal = pValue;
			while(tTmpVal<0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[-tTmpVal % 10];
				tTmpVal /=10;
			}
			tTmp[tChars++] ='-';
		}
		ensureCapacity(tChars);
		while(tChars>0)
		{
			mBuffer[mIndex++] = tTmp[--tChars];
		}
	}
}
	
void TagwireEncoder::appendIntegerInt64(const int64 pValue)
{
	if(pValue==0)
		appendChar('0');
	else {
		unsigned char tTmp[21];
		unsigned int tChars = 0;
		if( pValue>0) {
			int64 tTmpVal = pValue;
			while (tTmpVal >0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[tTmpVal%10];
				tTmpVal /=10;
			}
		} else {
			int64 tTmpVal = pValue;
			while(tTmpVal<0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[-tTmpVal % 10];
				tTmpVal /=10;
			}
			tTmp[tChars++] ='-';
		}
		ensureCapacity(tChars);
		while(tChars>0)
		{
			mBuffer[mIndex++] = tTmp[--tChars];
		}
	}
}
	
TagwireEncoder& TagwireEncoder::appendArrayInt8(int pAttributeNumber, vector<const int8*>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<const int8*>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt8(**tIter);
			}
			endGroup();
		}
	}
	return *this;			
}	

TagwireEncoder& TagwireEncoder::appendArrayInt16(int pAttributeNumber, vector<const int16*>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<const int16*>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt16(**tIter);
			}
			endGroup();
		}
	}
	return *this;				
}	
TagwireEncoder& TagwireEncoder::appendArrayInt32(int pAttributeNumber, vector<const int32*>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<const int32*>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt32(**tIter);
			}
			endGroup();
		}
	}
	return *this;			
}		
TagwireEncoder& TagwireEncoder::appendArrayInt64(int pAttributeNumber, vector<const int64*>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<const int64*>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt64(**tIter);
			}
			endGroup();
		}
	}
	return *this;			
}		

TagwireEncoder& TagwireEncoder::appendArrayInt8(int pAttributeNumber, vector<const int8>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<int8>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt8(*tIter);
			}
			endGroup();
		}
	}
	return *this;			
}		
TagwireEncoder& TagwireEncoder::appendArrayInt16(int pAttributeNumber, vector<const int16>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<int16>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt16(*tIter);
			}
			endGroup();
		}
	}
	return *this;			
}		
TagwireEncoder& TagwireEncoder::appendArrayInt32(int pAttributeNumber, vector<const int32>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<int32>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt32(*tIter);
			}
			endGroup();
		}
	}
	return *this;		
}		
TagwireEncoder& TagwireEncoder::appendArrayInt64(int pAttributeNumber, vector<const int64>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(vector<int64>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendIntegerInt64(*tIter);
			}
			endGroup();
		}
	}
	return *this;			
}

TagwireEncoder& TagwireEncoder::appendMessage(int pAttributeNumber, const MessageDataIf* pValue)
{
	if(pValue!=NULL) {
		beginAttribute(pAttributeNumber);
		beginGroup();
		pValue->pack(*this);
		endGroup();
	}
	return *this;			
}

	void TagwireEncoder::beginAttribute(int pAttributeNumber)
{
	if(mPrecededByAttribute) {
		appendChar('|');
	} else {
		mPrecededByAttribute = true;
	}
	appendInteger<int>(pAttributeNumber);
	appendChar('=');
}
	

void TagwireEncoder::appendChar(unsigned char pChar)
{
	ensureCapacity(1);
	mBuffer[mIndex++]=pChar;
}
	

void TagwireEncoder::escapeAndAppendUtf8(const string* pString)
{
	unsigned int tLeft = (unsigned int) pString->length();
	if(tLeft==0){
		ensureCapacity(1);
		appendChar('\"');
		return;
	}
	ensureCapacity(tLeft);
	int tPos=0;
	while (tLeft>0) {
		// NYI escaping 
		char tChar = pString->at(tPos++);
		mBuffer[mIndex++]=tChar;
	}
	--tLeft;
}
	
void TagwireEncoder::ensureCapacity(unsigned int pSize)
{
	if( mCapacity< (mIndex+pSize))
	{
			unsigned int tNewSize = std::min<unsigned int>(mCapacity*2, pSize *2);
			unsigned char * tNewBuffer = new unsigned char[tNewSize];
			memcpy(tNewBuffer, mBuffer, sizeof(unsigned char) * mIndex);
			mBuffer = tNewBuffer;
			mCapacity = tNewSize;
	}
}
	
void TagwireEncoder::addMessageType(const string* pValue)
{
	
}

} // namespace

