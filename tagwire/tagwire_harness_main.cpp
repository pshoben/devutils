#include <cstdio>
#include <iostream>

#include "emapi.h"
#include <sstream>

#include "EmapiTagwireWrapper.h"

using namespace emapi;
using std::string;
using std::stringstream;
using std::cout;

EmapiTagwireWrapper tpl_req;

void test_tpl() 
{
	stringstream ss;
	ss  << EmapiMessageType_EmapiTaxPreLogonReq << "=[" 
		<< "1=T"
		<< "|2=member"
		<< "|3=user"
		<< "|4=1"
		<< "|5=2"
		<< "|6=3"
		<< "]";
	string tpl_str{ss.str()};
	TagwireDecoder decoder{ (const unsigned char *)tpl_str.c_str(),
				0,(unsigned int) tpl_str.size()};  

	cout << "test string : \"" << tpl_str << "\"\n";
	tpl_req.unpack(decoder);
	cout << "wrapper\n" << tpl_req.to_string("");

	TagwireEncoder encoder{};
	tpl_req.pack(encoder);

	cout << "packed: " << encoder.getBuffer() << "\n";

}

int main(void) 
{
	test_tpl();
   printf("tagwire harness\n");	
	return 0;
}
