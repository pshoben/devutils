#ifndef FIELDS_HARNESS_SRC_HPP
#define FIELDS_HARNESS_SRC_HPP

#include <cstddef>

namespace Test
{

	struct SimpleType2 {
		int int_field;
		long long_field;
		char char_field;
		float float_field;
		double double_field;
		int int_arr_field[2];
		long long_arr_field[2];
		char char_arr_field[2];
		float float_arr_field[2];
		double double_arr_field[2];
	};

	class SimpleType
	{
	public:
		int int_field;
		long long_field;
		char char_field;
		float float_field;
		double double_field;
		int int_arr_field[2];
		long long_arr_field[2];
		char char_arr_field[2];
		
		float float_arr_field[2];
		double double_arr_field[2];
		SimpleType2 sub1;
		SimpleType2 subarray[2];
	};
	class BaseType
	{
	public:
		int baseint_field;
		int * pbaseint_field;

		BaseType()
		: baseint_field(0)
		, pbaseint_field(new int(0))
		{}
		BaseType(int baseint_field, int pbaseint_field) 
		: baseint_field(baseint_field)
		, pbaseint_field(new int(pbaseint_field)) 
		{}
	};

	class SimpleType3 : public BaseType
	{
	public:
		SimpleType3()
		: BaseType() 
		{
			pint_field = new int(0);
			plong_field = new long(0);
			pchar_field = new char('x');
			pfloat_field = new float(0);
			pdouble_field = new double(0);
			for( auto i = 0 ; i < 2 ; ++i ) {
				pint_arr_field[i] = new int(0);
				plong_arr_field[i] = new long(0);
				pchar_arr_field[i] = new char('x');
				pfloat_arr_field[i] = new float(0);
				pdouble_arr_field[i] =  new double(0);
			}
		 	psub1 = new SimpleType2();
			psubarray[0] = new SimpleType2();
			psubarray[1] = new SimpleType2();
		}
		SimpleType3(int int_field,
		long long_field,
		char char_field,
		float float_field,
		double double_field,
		size_t arr_len) : BaseType( 0, 100) 
		{
			pint_field = new int(int_field);
			plong_field = new long(long_field);
			pchar_field = new char(char_field);
			pfloat_field = new float(float_field);
			pdouble_field = new double(double_field);
			for( auto i = 0 ; i < arr_len ; ++i ) {
				pint_arr_field[i] = new int(int_field);
				plong_arr_field[i] = new long(long_field);
				pchar_arr_field[i] = new char(char_field);
				pfloat_arr_field[i] = new float(float_field);
				pdouble_arr_field[i] = new double(double_field);
			}
		 	psub1 = NULL;
			psubarray[0] = NULL;
			psubarray[1] = NULL;
		}
		~SimpleType3() { /* TODO RAII */ }
		SimpleType2 * psub1;
		SimpleType2 * psubarray[2];
	//private:
		int * pint_field;
		long * plong_field;
		char * pchar_field;
		float * pfloat_field;
		double * pdouble_field;
		int * pint_arr_field[2];
		long * plong_arr_field[2];
		char * pchar_arr_field[2];
		float * pfloat_arr_field[2];
		double * pdouble_arr_field[2];
	};
/*
	class ComplexType
	{
	public:
		int field;
	};
*/
}
/*
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
*/

#endif //FIELDS_SRC_HPP
