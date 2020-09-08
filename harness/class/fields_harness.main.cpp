#include "fields_harness.src.hpp"
#include "fields_harness.gen.hpp"

#include <cstdio>
#include <iostream>

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
//
//	// non-const iteration.
//	Class<MyClass>::IterateFields(
//			instance,
//			[&fields, &instance](auto& m)
//			{
//				RequireEquals(instance, m);
//				--fields;
//			});
//}

void to_yaml(std::ostream& out, const Test::SimpleType * instance, std::string indent) 
{
	Class<Test::SimpleType>::IterateFieldsAndValues(
		*instance,
		[&out](auto& name, auto& value)
		{
			out << name << value << "\n";
		});

	//for( auto field_name : field_names ) {
//		out << field_name << ": " << '\n'; 
//	}
}
void to_yaml(std::ostream& out, const Test::SimpleType& src, std::string indent) 
{
   to_yaml(out, &src, indent);
}

int main(void) {
  printf("in fields_harness\n");
  //iterate_fields();
  //MyClass c(123);
  Test::SimpleType simple{ 456,(long)(1 << 31),'a',0.123, 0.3-0.1, 
			   {456,789},
			   {(long)(1 << 31),(long)(1<<31)},
			   "abc",
			   {0.123,0.456},
			   { 0.3-0.1, 0.3-0.2},
{
556,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "abc",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
},

{ // SompleType[2]
{
656,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {556,789},
   {(long)(1 << 31),(long)(1<<31)},
   "abc",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
},
{ 756,(long)(1 << 31),'a',0.123, 0.3-0.1, 
  {756,789},
   {(long)(1 << 31),(long)(1<<31)},
   "abc",
   {1.123,0.456},
   { 1.3-0.1, 0.3-0.2}
}
}
				};

  to_yaml(std::cout, &simple, "  ");
}

