
#include "TagwireDecoder.h"
//#include "emapi.h"

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

namespace emapi {
	
TagwireDecoder::TagwireDecoder()
	:mBuffer(NULL)
	,mIndex(0)
	,mEndIndex(0)
	,mPrecededByAttribute(false) {}

TagwireDecoder::TagwireDecoder(const unsigned char * pBuffer, unsigned int pOffset, unsigned int pLength)
	:mBuffer(pBuffer)
	,mIndex(pOffset)
	,mEndIndex(pOffset+pLength)
	,mPrecededByAttribute(false) {}

//TagwireDecoder::TagwireDecoder(ByteArray * pBuffer, unsigned int pOffset, unsigned int pLength)
//	:mIndex(pOffset)
//	,mEndIndex(pOffset+pLength)
//	,mPrecededByAttribute(false) 
//{
//	mBuffer = (new ByteArray(*pByteArray))->getBytes();
//}

TagwireDecoder::~TagwireDecoder()
{
//	if (mBuffer)
//		delete mBuffer;
}

void TagwireDecoder::setDataStore(const unsigned char * pBuffer, unsigned int pOffset, unsigned int pLength)
{
	mBuffer = pBuffer;
	mIndex = pOffset;
	mEndIndex = pOffset+pLength;
}

MessageDataIf* TagwireDecoder::parseMessage() noexcept(false) // throw (ParseException)
{
	int tTag = parseInteger<int>();
	ensureCapacity(1);
	if (mBuffer[mIndex++]!='=') 
		throw ParseException("expecting =");
	
	MessageDataIf* tMsg = emapi::getMessageClass(tTag);
	if(tMsg==NULL) 
		throw ParseException("Emapi::getMessageClass failed");

	ensureCapacity(1);
	if (mBuffer[mIndex++]!='[') 
		throw ParseException("expecting [");
	
	tMsg->unpack(*this);
	ensureCapacity(1);			
	if (mBuffer[mIndex]=='\"')
		mIndex++; // empty message trick
	ensureCapacity(1);
	if (mBuffer[mIndex++]!=']') 
		throw ParseException("expecting ]");
	
	if (mIndex!=mEndIndex) 
		throw ParseException("mIndex!=mEndIndex");
	
	return tMsg;
}
		
bool TagwireDecoder::hasMoreTags()
{
	ensureCapacity(1);
	while( mBuffer[mIndex] == '|') {
		++mIndex;
		ensureCapacity(1);
	}
	switch(mBuffer[mIndex])
	{	
	case '-':
	case '\"':
		if(mIndex+3 > mEndIndex)
			return false;
		mIndex+=2;
		// fallthrough
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
		return true;
	case ']':
		return false;
	default:
		throw ParseException("hasMoreTags default");
	}			
}

int TagwireDecoder::getNextTag()
{
	int tTag = parseInteger<int>();
	ensureCapacity(1);
	if( mBuffer[mIndex++] != '=')
		throw ParseException("expecting =");
	return tTag;
}

void TagwireDecoder::skipUnknownTag()
{
	// NYI
}
		
TagwireDecoder& TagwireDecoder::readBoolean (bool& pField)
{
	ensureCapacity(1);
	switch(mBuffer[mIndex])
	{
	case 'T':
		pField = true;
		break;
	case 'F':
	case '\"': // empty field trick
		pField = false;
		break;
	default:
		throw ParseException("readBoolean default");
	}			
	++mIndex;
	return *this;
}		

TagwireDecoder& TagwireDecoder::readInteger (int32& pField)
{
	pField = parseInteger<int32>();
	return *this;
}		

TagwireDecoder& TagwireDecoder::readLong (int64& pField)
{
	pField = parseInteger<int64>();
	return *this;
}		

TagwireDecoder& TagwireDecoder::readByte (int8& pField)
{
	pField = parseInteger<byte>();
	return *this;
}		

			
TagwireDecoder& TagwireDecoder::readString (string*& pField)
{
	pField = parseString();
	return *this;
}		

TagwireDecoder& TagwireDecoder::readBoolean (bool*& pField)
{
	pField = new bool();
	readBoolean(*pField);
	return *this;
}		

TagwireDecoder& TagwireDecoder::readInteger (int32*& pField)
{
	pField = new int32();
	readInteger(*pField);
	return *this;
}

TagwireDecoder& TagwireDecoder::readLong (int64*& pField)
{
	pField = new int64();
	readLong(*pField);
	return *this;
}		

TagwireDecoder& TagwireDecoder::readByte (int8*& pField)
{
	pField = new int8();
	readByte(*pField);
	return *this;
}		

const string * TagwireDecoder::parseValue(const string*& pVal)
{
	return pVal = parseString();
}

bool TagwireDecoder::parseValue(bool& pVal)
{
	ensureCapacity(1);
	switch(mBuffer[mIndex++])
	{
	case 'T':
		pVal = true;
		break;
	case 'F':
	case '\"': // empty field trick
		pVal = false;
		break;
	default:
		throw ParseException("parseValue bool default");
	}			
	return pVal;
}

int8 TagwireDecoder::parseValue(int8& pField)
{
	return parseInteger<int8>();
}

int32 TagwireDecoder::parseValue(int32& pField)
{
	return parseInteger<int32>();
}

int64 TagwireDecoder::parseValue(int64& pField)
{
	return parseInteger<int64>();
}

vector<const int8*>* TagwireDecoder::readArrayInt8(vector<const int8*>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector<const  int8*>();
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
			int8 tField = parseInteger<int8>();
			const int8* tResult = new int8(tField);
			pArray->push_back(tResult);
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}

vector<const int16*>* TagwireDecoder::readArrayInt16(vector<const int16*>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector<const  int16*>();
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
			int16 tField = parseInteger<int16>();
			const int16* tResult = new int16(tField);
			pArray->push_back(tResult);
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
vector<const int32*>* TagwireDecoder::readArrayInt32(vector<const int32*>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector<const  int32*>();
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
			int32 tField = parseInteger<int32>();
			const int32* tResult = new int32(tField);
			pArray->push_back(tResult);
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
vector<const int64*>* TagwireDecoder::readArrayInt64(vector<const int64*>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector<const int64*>();
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
			int64 tField = parseInteger<int64>();
			const int64* tResult = new int64(tField);
			pArray->push_back(tResult);
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
vector< int8>* TagwireDecoder::readArrayInt8(vector< int8>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector< int8>();
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
			const int8 * tField = new int8;
			pArray->push_back(parseInteger<int8>());
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
vector< int16>* TagwireDecoder::readArrayInt16(vector< int16>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector< int16>();
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
			const int16 * tField = new int16;
			pArray->push_back(parseInteger<int16>());
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}

vector< int32>* TagwireDecoder::readArrayInt32(vector< int32>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector< int32>();
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
			const int32 * tField = new int32;
			pArray->push_back(parseInteger<int32>());
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
vector< int64>*  TagwireDecoder::readArrayInt64(vector< int64>* pArray)
{
	ensureCapacity(1);
	if (mBuffer[mIndex]!='[') {
		throw ParseException("expecting [");
	}
	++mIndex;
	if(!pArray)
		pArray = new vector< int64>();
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
			const int64 * tField = new int64;
			pArray->push_back(parseInteger<int64>());
			tSeparatorExpected = true;
			break;	
		}
	}
	while (tMore && (mIndex < mEndIndex));
	return pArray;
}
	
void TagwireDecoder::ensureCapacity(int pChars)
{
	if (mIndex + pChars > mEndIndex)
		throw ParseException("end of buffer");
}

string* TagwireDecoder::parseString()
{
	ensureCapacity(1);
	if( mBuffer[mIndex] == '\"') {
		++mIndex;
		return new string("");
	}
	std::stringstream tBuf;
	bool tEndFound = false;
	while( mIndex < mEndIndex )
	{
		switch(mBuffer[mIndex])
		{
		case ']':
		case '|':
			tEndFound = true;
			break;
		case '[':
		case '=':
		case '\"':
			throw ParseException("parseString not expecting [=\" ");

		case TAGWIRE_ESCAPE:
			++mIndex;
			ensureCapacity(1);
			switch(mBuffer[mIndex])		
			{
			case '1':
				tBuf << (unsigned char) TAGWIRE_EQUALS;
				break;
			case '2':
				tBuf << (unsigned char) TAGWIRE_OPEN;
				break;
			case '3':
				tBuf << (unsigned char) TAGWIRE_CLOSE;
				break;
			case '4':
				tBuf << (unsigned char) TAGWIRE_SEPARATOR;
				break;
			case '5':
				tBuf << (unsigned char) TAGWIRE_QUOTE;
				break;
			case TAGWIRE_ESCAPE:
				tBuf << (unsigned char) TAGWIRE_ESCAPE;
				break;
			case ']':
				return new string("");
			default:
				throw ParseException("parseString expecting 12345% after %");
			}
			break;
		default:
			tBuf << mBuffer[mIndex];
			break;
		}	
		if(tEndFound)
			return new string(tBuf.str());
		++mIndex;
	}
	throw ParseException("parseStringunexpected eob" );
}

}


	

		
