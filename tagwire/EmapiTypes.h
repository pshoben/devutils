#ifndef EmapiTypes_H
#define EmapiTypes_H

#include <string>
#include <memory>
#include <vector>
#include "ByteArray.h"


namespace emapi 
{
typedef char byte;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define INT64_CONSTANT(val) (val##LL)
#define I64LIT(val) 	    (val##LL)
#define atoi64(val)	 	_atoi64(val)
#define	abs64(val)		_abs64(val)
#define I64FMT			"%lld"
#define UI64FMT			"%llu"

//template <typename T>
//T * copyAttribute(const T pValue) 
//{
//  T * x = new T;
//  *x = pValue;
//  return x;
//}
//bool * copyAttribute( const bool pValue );
//int8 * copyAttribute( const int8 pValue );
//int16 * copyAttribute( const int16 pValue );
//int32 * copyAttribute( const int32 pValue );
//uint8 * copyAttribute( const uint8 pValue );
//uint16 * copyAttribute( const uint16 pValue );
//uint32 * copyAttribute( const uint32 pValue );
//std::string * copyAttribute( const std::string &pValue );
//float * copyAttribute( const float pValue );
//double * copyAttribute( const double pValue );
//int64 * copyAttribute( const int64 pValue );

template <typename T>
T * copyAttribute(const T * pValue) 
{
  if( pValue == NULL) {
    return NULL;
  }
  T * x = new T;
  *x = *pValue;
  return x;
}
//bool * copyAttribute( const bool *pValue );
//int8 * copyAttribute( const int8 *pValue );
//int16 * copyAttribute( const int16 *pValue );
//int32 * copyAttribute( const int32 *pValue );
//uint8 * copyAttribute( const uint8 *pValue );
//uint16 * copyAttribute( const uint16 *pValue );
//uint32 * copyAttribute( const uint32 *pValue );
//std::string * copyAttribute( const std::string *pValue );
//float * copyAttribute( const float *pValue );
//double * copyAttribute( const double *pValue );
//int64 * copyAttribute( const int64 *pValue );
//ByteArray * copyAttribute( const ByteArray *pValue );

std::vector<bool > * copyArray( const std::vector< bool > *pArray);
std::vector<int8 > * copyArray( const std::vector< int8 > *pArray);
std::vector<int16 > * copyArray( const std::vector< int16 > *pArray);
std::vector<int32 > * copyArray( const std::vector< int32 > *pArray);
std::vector<uint8 > * copyArray( const std::vector< uint8 > *pArray);
std::vector<uint16 > * copyArray( const std::vector< uint16 > *pArray);
std::vector<uint32 > * copyArray( const std::vector< uint32 > *pArray);
std::vector<float > * copyArray( const std::vector< float > *pArray);
std::vector<double > * copyArray( const std::vector< double > *pArray);
std::vector<int64 > * copyArray( const std::vector< int64 > *pArray);

std::vector<const bool *> * copyArray( const std::vector<const bool *> *pArray);
std::vector<const int8 *> * copyArray( const std::vector<const int8 *> *pArray);
std::vector<const int16 *> * copyArray( const std::vector<const int16 *> *pArray);
std::vector<const int32 *> * copyArray( const std::vector<const int32 *> *pArray);
std::vector<const uint8 *> * copyArray( const std::vector<const uint8 *> *pArray);
std::vector<const uint16 *> * copyArray( const std::vector<const uint16 *> *pArray);
std::vector<const uint32 *> * copyArray( const std::vector<const uint32 *> *pArray);
std::vector<const std::string *> * copyArray( const std::vector<const std::string *> *pArray);
std::vector<const float *> * copyArray( const std::vector<const float *> *pArray);
std::vector<const double *> * copyArray( const std::vector<const double *> *pArray);
std::vector<const int64 *> * copyArray( const std::vector<const int64 *> *pArray);
std::vector<const ByteArray *> * copyArray( const std::vector<const ByteArray *> *pArray);

void deleteArray( std::vector<bool > ** pArray );
void deleteArray( std::vector<int8 > ** pArray );
void deleteArray( std::vector<int16 > ** pArray );
void deleteArray( std::vector<int32 > ** pArray );
void deleteArray( std::vector<uint8 > ** pArray );
void deleteArray( std::vector<uint16 > ** pArray );
void deleteArray( std::vector<uint32 > ** pArray );
void deleteArray( std::vector<float > ** pArray );
void deleteArray( std::vector<double > ** pArray );
void deleteArray( std::vector<int64 > ** pArray );

void deleteArray( std::vector<bool *> ** pArray );
void deleteArray( std::vector<int8 *> ** pArray );
void deleteArray( std::vector<int16 *> ** pArray );
void deleteArray( std::vector<int32 *> ** pArray );
void deleteArray( std::vector<uint8 *> ** pArray );
void deleteArray( std::vector<uint16 *> ** pArray );
void deleteArray( std::vector<uint32 *> ** pArray );
void deleteArray( std::vector<std::string *> ** pArray );
void deleteArray( std::vector<float *> ** pArray );
void deleteArray( std::vector<double *> ** pArray );
void deleteArray( std::vector<int64 *> ** pArray );
void deleteArray( std::vector<ByteArray * > ** pArray );

}
#endif
