#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <openssl\bn.h>

using namespace std;

typedef enum {	
	divsion = 0,
	modulus
}operation;

class BigNumberUsingBits
{
public:
	vector<char> decimal_vector;

private:
	vector<char> binary_vector;
	string BigNumberStr;
	bool negative_sign = false;

public:
	BigNumberUsingBits();
	BigNumberUsingBits(string number_string);
	BigNumberUsingBits(const BigNumberUsingBits& obj);
	~BigNumberUsingBits();
	
	bool operator>(const BigNumberUsingBits & num2);
	bool operator<(const BigNumberUsingBits & num2);
	bool operator==(const BigNumberUsingBits & num2);

	BigNumberUsingBits Add(const BigNumberUsingBits&num1, const BigNumberUsingBits&num2);
	BigNumberUsingBits operator+(const BigNumberUsingBits & num2 );
	
	BigNumberUsingBits Sub(const BigNumberUsingBits&num1, const BigNumberUsingBits&num2);
	BigNumberUsingBits operator-(const BigNumberUsingBits & num2);
	
	BigNumberUsingBits Mul(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2);
	BigNumberUsingBits operator*(const BigNumberUsingBits & num2);
	
	BigNumberUsingBits Div(const BigNumberUsingBits&num1, const BigNumberUsingBits&num2);
	BigNumberUsingBits operator/(const BigNumberUsingBits & num2);
	
	BigNumberUsingBits Mod(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2);
	BigNumberUsingBits operator%(const BigNumberUsingBits & num2);
	
	BigNumberUsingBits Pow(const BigNumberUsingBits & base, const BigNumberUsingBits & exponent);

	BigNumberUsingBits PowMod(const BigNumberUsingBits & base, const BigNumberUsingBits & exponent, const BigNumberUsingBits&modulus);
	
	void operator=(const string& value);
	void operator++(int);
	
	string ToHex(void);
	string ToDecimal(void);
	string ToString(void);

	//Print function reverse the vector so we can see the value in the correct order M in L 2(10)
	void Print_number_in_binary_vector();
	void Print_number_in_decimal_vector();
	int LongDivsion(vector<int>& int_array, vector<int>& quotient, int divisor);

	void generate_random_bignumber(unsigned long long length);
	void generate_prime_bignumber(unsigned long long length);

private:
	//convert the string to int array and return the size of the int_array
	size_t Convert_String_to_Decimal_vector(void);

	BigNumberUsingBits Div_Mod( const BigNumberUsingBits & num1, const BigNumberUsingBits & num2, operation mode);
	void Convert_Decimal_vector_to_Binary_vector();

	int Divide_Decimal_vector_by_Two(vector<char>& decimal_array, vector<char>& bin_array);
	bool Isgreater(const BigNumberUsingBits& num1, const BigNumberUsingBits& num2);
	bool IsEven(void);
	bool IsSmaller(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2);
	bool IsGreaterOrEqual(BigNumberUsingBits & num1, BigNumberUsingBits & num2);

	bool Check_vector_all_zeros(vector<int>& vec_under_test);
	bool GreaterOnly(const BigNumberUsingBits& num1, const BigNumberUsingBits& num2);
	bool IsEqual(const BigNumberUsingBits& num1, const BigNumberUsingBits& num2);
	void update_bcd_digit_value_coressponding_to_its_current_value( vector< vector<char> >& whole_num_bcd_vector);
	void shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector);
	
};
