#ifndef TagwireDecoder_H
#define TagwireDecoder_H

#include "MessageDataIf.h"
#include "ParseException.h"
#include "TagwireUtil.h"
//#include "ByteArray.h"
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

namespace emapi {

class TagwireDecoder
{
private:
	const unsigned char * mBuffer;
	unsigned int 	mIndex;
	unsigned int mEndIndex;
	bool mPrecededByAttribute;
	
public:
		TagwireDecoder();
		TagwireDecoder(const unsigned char * pBuffer, unsigned int pOffset, unsigned int pLength);	
		//TagwireDecoder(ByteArray * pBuffer, unsigned int pOffset, unsigned int pLength);			
		virtual ~TagwireDecoder();

		void setDataStore(const unsigned char * pBuffer, unsigned int pOffset, unsigned int pLength);	
		MessageDataIf* parseMessage() noexcept(false); // throw (ParseException);
		bool hasMoreTags();
		int getNextTag();
		void skipUnknownTag();
		
		TagwireDecoder& readBoolean (bool& pField);
		TagwireDecoder& readInteger (int32& pField);		
		TagwireDecoder& readLong (int64& pField);
		TagwireDecoder& readByte (int8& pField);				

		TagwireDecoder& readString (string*& pField);
		TagwireDecoder& readBoolean (bool*& pField);		
		TagwireDecoder& readInteger (int32*& pField);
		TagwireDecoder& readLong (int64*& pField);		
		TagwireDecoder& readByte (int8*& pField);

		template<class T>
		TagwireDecoder& readArray(vector<T>*& pField);	
		
		vector<const int8*>* readArrayInt8(vector<const int8*>* pArray);		
		vector<const int16*>* readArrayInt16(vector<const int16*>* pArray);		
		vector<const int32*>* readArrayInt32(vector<const int32*>* pArray);		
		vector<const int64*>* readArrayInt64(vector<const int64*>* pArray);		

		vector< int8>* readArrayInt8(vector< int8>* pArray);		
		vector< int16>* readArrayInt16(vector< int16>* pArray);		
		vector< int32>* readArrayInt32(vector< int32>* pArray);		
		vector< int64>*  readArrayInt64(vector< int64>* pArray);	

		template<class T>
		TagwireDecoder& readMessage(const T*& pField);		
		
private:		
		template<class T>
		T parseInteger();	

		template<class T>
		const T* parseValue(const T*& pVal);	

		const string * parseValue(const string*& pVal);	
		bool parseValue(bool& pField);	
		int8 parseValue(int8& pField);
		int32 parseValue(int32& pField);
		int64 parseValue(int64& pField);

		void ensureCapacity(int pChars);
		string* parseString();
};

template<class T>
TagwireDecoder& TagwireDecoder::readMessage(const T*& pField)
{
	if (mBuffer[mIndex]=='\"')
		return *this; // empty tag trick

	ensureCapacity(1);
	if (mBuffer[mIndex++]!='[') {
		throw ParseException("expecting [");
	}
	pField = new T();
	pField->unpack(*this);
	ensureCapacity(1);
	if (mBuffer[mIndex++]!=']') {
		throw ParseException("expecting ]");
	}		
	return *this;
}

template<class T>
TagwireDecoder& TagwireDecoder::readArray(vector<T>*& pField)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]=='\"')
		return *this; // empty tag trick
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(pField)
		delete pField;
	pField = new vector<T>;
	bool tMore = true;
	bool tSeparatorExpected = false;
	do {
		ensureCapacity(1);
		switch(mBuffer[mIndex])
		{
		case ']':
			tMore = false;
			++mIndex;
			break;
		case '|':
			if(!tSeparatorExpected)
				throw ParseException("not expecting |");
			tSeparatorExpected = false;
			++mIndex;
			break;
		default:
			if(tSeparatorExpected)
				throw ParseException("expecting |");
			T tType;
			pField->push_back(parseValue(tType));
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return *this;
}

		
template<class T>
inline const T * TagwireDecoder::parseValue(const T*& pVal)
{	
	T * tTmp = new T();
	readMessage(tTmp);
	return tTmp;
}
	

template<class T>
T TagwireDecoder::parseInteger()
{
	T tVal=0;
	bool tFirstDigit = true;
	bool tNegative = false;
	bool tMore = true;
	do {
		ensureCapacity(1);
		switch(mBuffer[mIndex])
		{
		case '\"':
			if(mIndex+3 > mEndIndex)
				return false;
			mIndex+=2;
			return tVal;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			tVal = (tVal*10) + (mBuffer[mIndex]-'0');
			break;
		case '-':
			if (tFirstDigit)
			{
				tNegative = true;
				break;
			} // else fallthrough
		default:
			if(tFirstDigit)
				throw ParseException("expecting digit");
			tMore = false;
			break;
		}
		tFirstDigit=false;
	} while (tMore && (++mIndex < mEndIndex));
	return tNegative ? 0-tVal : tVal;			
}

}

#endif
