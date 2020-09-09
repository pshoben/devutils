#ifndef TagwireUtil_H
#define TagwireUtil_H

//#include "EmapiTypes.h"

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long int64;


#define NULL 0
#define	TAGWIRE_OPEN			0x5b 	// [
#define	TAGWIRE_CLOSE			0x5d 	// ]
#define	TAGWIRE_EQUALS			0x3d 	// =
#define	TAGWIRE_SEPARATOR		0x7c	// |
#define	TAGWIRE_QUOTE			0x22 	//"
#define	TAGWIRE_ESCAPE			0x25	// %
#define	TAGWIRE_TRUE			0x54 	// T
#define	TAGWIRE_FALSE			0x46	// F
#define	TAGWIRE_NEGATIVE		0x2d	// -
#define	TAGWIRE_0	0x30
#define	TAGWIRE_1	0x31
#define TAGWIRE_2	0x32
#define	TAGWIRE_3	0x33
#define	TAGWIRE_4	0x34
#define	TAGWIRE_5	0x35
#define	TAGWIRE_6	0x36
#define	TAGWIRE_7	0x37
#define	TAGWIRE_8	0x38
#define	TAGWIRE_9	0x39


namespace emapi {


union FLOAT_UNION
{		
		float f;
			uint8 b[4];
};
union DOUBLE_UNION
{
	double d;
	uint8 b[8];
};
static const unsigned char TAGWIRE_DIGITS[10] = {
	TAGWIRE_0,
	TAGWIRE_1,
	TAGWIRE_2,
	TAGWIRE_3,
	TAGWIRE_4,
	TAGWIRE_5,
	TAGWIRE_6,
	TAGWIRE_7,
	TAGWIRE_8,
	TAGWIRE_9};
}
#endif

