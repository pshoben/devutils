#ifndef FIELDS_HARNESS_SRC_HPP
#define FIELDS_HARNESS_SRC_HPP

namespace Test
{
	class SimpleType
	{
	public:
		int int_field;
		long long_field;
		char char_field;
		float float_field;
		double double_field;
		int int_arr2_field[2];
		long long_arr2_field[2];
		char char_arr2_field[2];
		float float_arr2_field[2];
		double double_arr2_field[2];

	};

	class ComplexType
	{
	public:
		int field;
	};
}

class MyClass {
public:
	using ComplexType = Test::ComplexType;

	MyClass(int val)
	:	field(val)
	,	const_field(field)
	,	pointer_field(&field)
	,	const_pointer_field(&field)
	,	const_pointer_const_field(&field)
	,	ref_field(field)
	,	const_ref_field(field)
	,	const_complex(complex)
	,	pointer_complex(&complex)
	,	const_pointer_complex(&complex)
	,	const_pointer_const_complex(&complex)
	,	ref_complex(complex)
	,	const_ref_complex(complex)
	{
	}

	int field;
	const int const_field;
	int* pointer_field;
	int const* const_pointer_field;
	int const* const const_pointer_const_field;
	int& ref_field;
	int const& const_ref_field;

	ComplexType complex;
	const ComplexType const_complex;
	ComplexType* pointer_complex;
	ComplexType const* const_pointer_complex;
	ComplexType const* const const_pointer_const_complex;
	ComplexType& ref_complex;
	ComplexType const& const_ref_complex;

protected:
	int protected_field;

private:
	int private_field;
};

#endif //FIELDS_SRC_HPP
