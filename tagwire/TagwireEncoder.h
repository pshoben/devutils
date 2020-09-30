#ifndef TagwireEncoder_H
#define TagwireEncoder_H

#include "MessageDataIf.h"
#include "TagwireUtil.h"
//#include "ByteArray.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace emapi {

typedef char byte;
class TagwireEncoder
{
	private:
	unsigned char * mBuffer;
	unsigned int mCapacity;
	unsigned int 	mIndex;
	bool mPrecededByAttribute;
	
	public:
		TagwireEncoder();
		TagwireEncoder(int pMessageType);		
		virtual ~TagwireEncoder();
		
		unsigned char * getBuffer();
		unsigned int * getLength();		

		TagwireEncoder& beginGroup();
		TagwireEncoder& endGroup();
		
		TagwireEncoder& appendBoolean (int pAttributeNumber, bool pValue);
		TagwireEncoder& appendInteger (int pAttributeNumber, int32 pValue);		
		TagwireEncoder& appendLong (int pAttributeNumber, int64 pValue);
		TagwireEncoder& appendByte (int pAttributeNumber, byte pValue);				

		TagwireEncoder& appendString (int pAttributeNumber, const string* pValue);
		TagwireEncoder& appendBoolean (int pAttributeNumber, bool* pValue);		
		TagwireEncoder& appendInteger (int pAttributeNumber, int32* pValue);
		TagwireEncoder& appendLong (int pAttributeNumber, int64* pValue);		
		TagwireEncoder& appendByte (int pAttributeNumber, byte* pValue);
		
		void appendIntegerInt8(const int8 pValue);
		void appendIntegerInt16(const int16 pValue);
		void appendIntegerInt32(const int32 pValue);
		void appendIntegerInt64(const int64 pValue);
		
		template<class T>
		TagwireEncoder& appendArray(int pAttributeNumber, const vector< T>* pValues);
		
		TagwireEncoder& appendArrayInt8(int pAttributeNumber, vector<int8*>* pValues);		
		TagwireEncoder& appendArrayInt16(int pAttributeNumber, vector<int16*>* pValues);		
		TagwireEncoder& appendArrayInt32(int pAttributeNumber, vector<int32*>* pValues);		
		TagwireEncoder& appendArrayInt64(int pAttributeNumber, vector<int64*>* pValues);		

		TagwireEncoder& appendArrayInt8(int pAttributeNumber, vector<int8>* pValues);		
		TagwireEncoder& appendArrayInt16(int pAttributeNumber, vector<int16>* pValues);		
		TagwireEncoder& appendArrayInt32(int pAttributeNumber, vector<int32>* pValues);		
		TagwireEncoder& appendArrayInt64(int pAttributeNumber, vector<int64>* pValues);	

		TagwireEncoder& appendMessage(int pAttributeNumber, const MessageDataIf* pValue);	

private:		
	void beginAttribute(int pAttributeNumber);

		template<class T>
		void appendInteger(T pValue);	

		template<class T>
		void appendValue(const T& pValue);	

		template<class T>
		void appendValue(const T* pValue);			

		void appendValue(const string* pString);	
		void appendChar(unsigned char pChar);	

		void escapeAndAppendUtf8(const string* pString);
		
		void ensureCapacity(unsigned int pSize);
		void addMessageType(const string* pValue);
};

template <class T>
TagwireEncoder& TagwireEncoder::appendArray(int pAttributeNumber, const vector<T>* pValues)
{
	if(pValues!=NULL) {
		beginAttribute(pAttributeNumber);
		if (pValues->empty())
		{
			appendChar('\"');
		} else {
			beginGroup();
			bool tFirst = true;
			for(typename vector<T>::const_iterator tIter = pValues->begin(); tIter != pValues->end(); ++tIter) 
			{
				if(tFirst)
					tFirst=false;
				else
					appendChar('|');
				appendValue(*tIter);
			}
			endGroup();
		}
	}
	return *this;			
}	

void inline TagwireEncoder::appendValue(const string* pValue)
{
	escapeAndAppendUtf8(pValue);
}

template<class T>
void TagwireEncoder::appendValue(const T* pValue)
{
	if (pValue != NULL)
	{
		pValue->pack(*this);
	}
}


template<>
void inline TagwireEncoder::appendValue(const bool& pValue)
{
	appendChar(pValue ? 'T':'F');
}	

template<class T>
void TagwireEncoder::appendValue(const T& pValue)
{
		appendInteger(pValue);
}

template<class T>
void TagwireEncoder::appendInteger(T pValue)
{
	if(pValue==0)
		appendChar('0');
	else {
		unsigned char tTmp[21];
		unsigned int tChars = 0;
		if( pValue>0) {
			T tTmpVal = pValue;
			while (tTmpVal >0)
			{
				tTmp[tChars++] = TAGWIRE_DIGITS[tTmpVal%10];
				tTmpVal /=10;
			}
		} else {
			T tTmpVal = pValue;
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
}
#endif

