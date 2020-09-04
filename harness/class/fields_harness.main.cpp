#include "fields_harness.src.hpp"
#include "fields_harness.gen.hpp"

#include <cstdio>
#include <iostream>

using namespace reflang;
using namespace std;

using ComplexType = Test::ComplexType;

void RequireEquals(const MyClass& c, int i)
{
	printf("#0 %d == %d\n",c.field, i);
	//REQUIRE(c.field == i);
}

void RequireEquals(const MyClass& c, int const* const i)
{
	printf("#1 %d == %d\n",c.field, *i);
	//REQUIRE(c.field == *i);
}

void RequireEquals(const MyClass& c, const Test::ComplexType& i)
{
	printf("#2 %d == %d\n",c.complex.field, i.field);
	//REQUIRE(c.complex.field == i.field);
}

void RequireEquals(const MyClass& c, Test::ComplexType const* const i)
{	
	printf("#3 %d == %d\n",c.complex.field, i->field);
	//REQUIRE(c.complex.field == i->field);
}

void iterate_fields()
{
	int fields = Class<MyClass>::FieldCount;
	printf("got num fields %d\n", fields);

	MyClass instance(123);

	// non-const iteration.
	Class<MyClass>::IterateFields(
			instance,
			[&fields, &instance](auto& m)
			{
				RequireEquals(instance, m);
				--fields;
			});
}

void to_yaml(std::ostream& out, const MyClass* instance, std::string indent) 
{
	out << "test" << "\n";
	int fields = Class<MyClass>::FieldCount;
	// non-const iteration.
	Class<MyClass>::IterateFields(
			*instance,
			[&out, &indent](auto& m)
			{
				out << indent << &m <<  '\n'; // indent << "- " << m << '\n';
			});

}
void to_yaml(std::ostream& out, const MyClass& src, std::string indent) 
{
   to_yaml(out, &src, indent);
}

int main(void) {
  printf("in fields_harness\n");
  iterate_fields();
  MyClass c(123);
  to_yaml(std::cout, &c, "  ");
}

