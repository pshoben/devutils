#ifndef ByteArray_H
#define ByteArray_H

#include <stdio.h>
#include <memory>
#include <string.h>
#include <string>
#include <memory.h>

namespace emapi
{
class ByteArray
{
public:
	ByteArray() : mBuffer(NULL), mLength(0)
	{}
	ByteArray(const ByteArray &pArray) : mBuffer(NULL), mLength(0)
	{
		mBuffer = new unsigned char[pArray.mLength];
		memcpy(mBuffer,pArray.mBuffer,pArray.mLength);
		mLength = pArray.mLength;
	}
 	ByteArray(const unsigned char *pData, size_t pLength) : mBuffer(NULL), mLength(0)
	{
		mBuffer = new unsigned char[pLength];
		memcpy(mBuffer,pData,pLength);
		mLength = pLength;
	}
	explicit ByteArray(size_t pLength) : mBuffer(NULL), mLength(0)
	{
		resize(pLength);
	}
	~ByteArray()
	{
		delete[] mBuffer;
		mBuffer = NULL;
	}
	unsigned char& operator[](size_t pIndex) const
	{
		return mBuffer[pIndex];
	}
	unsigned char * getBytes() const
	{
		return mBuffer;
	}
	unsigned char * releaseBuffer()
	{
		unsigned char *ptr = mBuffer;
		mBuffer = NULL;
		return ptr;
	}
	unsigned char * getBytes(size_t &pLength)
	{
		pLength = mLength;
		return mBuffer;
	}

	size_t length() const
	{
		return mLength;
	}
	bool isNull() const
	{
		return (mLength==0);
	}
	unsigned char& at(size_t pIndex)
	{
		return mBuffer[pIndex];
	}
	void assign(const unsigned char *pBytes, size_t pLength)
	{
		delete[] mBuffer;
		mLength = pLength;
		mBuffer = new unsigned char[pLength];
		memcpy(mBuffer, pBytes, pLength);
	}
	void setLength(size_t pNewLength)
	{
		resize(pNewLength);
	}
	void resize(size_t pNewLength)
	{
		if (pNewLength < mLength)
		{
			mLength = pNewLength;
			return;
		}
		delete[] mBuffer;
		mBuffer = new unsigned char[pNewLength];
		memset(mBuffer, 0, pNewLength);
		mLength = pNewLength;
	}
	bool equals(const ByteArray &pArray) const
	{
		if (pArray.mLength != mLength)
		{
			return false;
		}
		return (memcmp(pArray.mBuffer,mBuffer,mLength)==0);
	}
	static ByteArray *toByteArray(const std::string	 & pStr)
	{
		return new ByteArray( reinterpret_cast<unsigned char *>(
					const_cast<char *>( pStr.c_str( ))),
					static_cast<int>( pStr.length( )));
	}
private:
	ByteArray& operator= (const ByteArray &pArray);
	ByteArray* operator= (const ByteArray *pArray);
	mutable unsigned char *mBuffer;
	size_t mLength;
};

//typedef std::auto_ptr<ByteArray> AutoByteArray;
}
#endif

