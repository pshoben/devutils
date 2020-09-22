#define private public
#include "fields_harness.src.hpp"
#include "fields_harness.gen.hpp"
#undef private

#include <cstdio>
#include <iostream>
#include <sstream>

using namespace reflang;
using namespace std;

//using ComplexType = Test::ComplexType;

//void RequireEquals(const MyClass& c, int i)
//{
//	printf("#0 %d == %d\n",c.field, i);
//	//REQUIRE(c.field == i);
//}
//
//void RequireEquals(const MyClass& c, int const* const i)
//{
//	printf("#1 %d == %d\n",c.field, *i);
//	//REQUIRE(c.field == *i);
//}
//
//void RequireEquals(const MyClass& c, const Test::ComplexType& i)
//{
//	printf("#2 %d == %d\n",c.complex.field, i.field);
//	//REQUIRE(c.complex.field == i.field);
//}
//
//void RequireEquals(const MyClass& c, Test::ComplexType const* const i)
//{	
//	printf("#3 %d == %d\n",c.complex.field, i->field);
//	//REQUIRE(c.complex.field == i->field);
//}
//
//void iterate_fields()
//{
//	int fields = Class<MyClass>::FieldCount;
//	printf("got num fields %d\n", fields);
//
//	MyClass instance(123);
////
////	// non-const iteration.
////	Class<MyClass>::IterateFields(
////			instance,
////			[&fields, &instance](auto& m)
////			{
////				RequireEquals(instance, m);
////				--fields;
////			});
////}
//
//void to_yaml(std::ostream& out, const Test::SimpleType * instance, std::string indent) 
//{
//	Class<Test::SimpleType>::IterateFieldsAndValues(
//		*instance,
//		[&out](auto& name, auto& value)
//		{
//			out << name << value << "\n";
//		});
//}
//void to_yaml(std::ostream& out, const Test::SimpleType& src, std::string indent) 
//{
//   to_yaml(out, &src, indent);
//}

void to_yaml(std::ostream& out, const Test::SimpleType * instance) 
{
	Class<Test::SimpleType>::print_class_yaml(
		instance, "",
		[&out](std::string indent, auto& name, auto& value)
		{
			out << "..." << indent << name << value << "\n";
		});
}


void test_simpletype(void)
{
  printf("in %s:\n", __FUNCTION__);
  //iterate_fields();
  //MyClass c(123);
  Test::SimpleType simple{ 456,(long)(1 << 31),'a',0.123, 0.3-0.1, 
			   {456,789},
			   {(long)(1 << 31),(long)(1<<31)},
			   "a",
			   {0.123,0.456},
			   { 0.3-0.1, 0.3-0.2},
{
556,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
},

{ // SompleType[2]
{
656,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
},
{ 756,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {756,789},
   {(long)(1 << 31),(long)(1<<31)},
   "a",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
}
}
				};

  to_yaml(std::cout, &simple);
}

//template<typename T>
//class Print {
//	std::ostream & out;
//public:
//	Print(std::ostream & out):out(out)
//	{}
//	void print(std::string indent, auto&name, auto&value) 
//	{
//		out << "4.." << indent << name << value << "\n";
//	}
//	void operator()(std::string indent, auto&name, auto&value) 
//	{
//		print( indent, name, value);
//	}
//}

void to_yaml3(std::ostream& out, const Test::SimpleType3 * instance) 
{
//	Print<Test::SimpleType3>::print(std::cout);
//	Class<Test::SimpleType3>::print_class_yaml( instance, "", print );

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
//	Print<Test::SimpleType3>::print(std::cout);
//	Class<Test::SimpleType3>::print_class_yaml( instance, "", print );

	Class<Test::SimpleType3>::read_class_yaml(
	instance, "", 
	[&in](std::string indent, const char * name, char * value )
	{
//		char value_buf[64];
//		memset(value_buf,0,sizeof(value_buf));
//		in.getline(value_buf,sizeof(value_buf));

//		std::cout << "got line [" << value_buf << "]" << std::endl;

		// read and discard the indent and the name fields
		//int skip_num = indent.size() + strlen(name);
		//std::cout << "skip_num " << skip_num << "]\n";

		//char skip_buf[ skip_num + 1 ];
		//in.get( skip_buf, skip_num );
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

void test_simpletype3(void)
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

  to_yaml3(std::cout, &simple);
  //Class<Test::SimpleType3>::print_class_yaml( &simple, nt, T lprint)
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
  //test_simpletype();
  //test_simpletype3();
  test_read_simpletype3();

}


