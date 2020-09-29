#define private public
#include "emapi.h"
#include "emapi.gen.hpp"
#undef private

#include <cstdio>
#include <iostream>
#include <sstream>

using namespace reflang;
using namespace std;

void to_yaml3(std::ostream& out, const Test::SimpleType3 * instance) 
{

	Class<Test::SimpleType3>::print_class_yaml(
	instance, "", 
	[&out](std::string indent, auto& name, auto value)
	{
		//out << indent << name << "\n";
		out << indent << name << value << "\n";
	});
}

void from_yaml3(std::istream& in, Test::SimpleType3 * instance) 
{

	Class<Test::SimpleType3>::read_class_yaml(
	instance, "", 
	[&in](std::string indent, const char * name, char * value )
	{
		char temp_buf[1024+1];
		memset(temp_buf,0,1024+1);
		in.getline(temp_buf,1024) ;

		char * ptr_last_space = strrchr( temp_buf, ' ');
		if( ptr_last_space ) {
			strcpy( value, ptr_last_space+1 );
		} else {
			//std::cout << "from_yaml3 setting *value=0\n";
			*value=0; // empty string
		}
		//std::cout << "from_yaml3 expecting " << "[" << indent << "] ... [" << name << "] ... tempbuf [" << ptr_last_space << "] got: [" << *value << "] str value addr = (" << value << ")\n";
	});
}

void test_read_simpletype3(void)
{
  printf("in %s:\n", __FUNCTION__);
  Test::SimpleType3 simple{ 456,(long)(1 << 31),'a',0.123, 0.3-0.1, 2 } ;

simple.psub1 = new Test::SimpleType2
{
556,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
};

simple.psubarray[0] = new Test::SimpleType2
 // SompleType[2]
{
656,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
};
simple.psubarray[1] = new Test::SimpleType2
{ 756,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {756,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
};

  simple.baseint_field = 99;
  simple.pbaseint_field = new int(199);


std::ostringstream string_out;
  to_yaml3(string_out, &simple);
  std::cout << string_out.str() ;

  std::istringstream string_in{string_out.str()};
   Test::SimpleType3 * psimple_copy = new Test::SimpleType3{};
  from_yaml3(string_in, psimple_copy);

  std::cout << "after copying...\n";

  to_yaml3(std::cout, psimple_copy);

  //Class<Test::SimpleType3>::print_class_yaml( &simple, nt, T lprint)
}


int main(void) {
  test_read_simpletype3();

}


