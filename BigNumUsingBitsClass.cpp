#include "stdafx.h"
#include "BigNumUsingBitsClass.h"
#include <algorithm>

BigNumberUsingBits::BigNumberUsingBits()
{
}
BigNumberUsingBits::BigNumberUsingBits(const BigNumberUsingBits& obj)
{
	this->BigNumberStr = obj.BigNumberStr;
	this->negative_sign = obj.negative_sign;

	for (size_t size = 0 ; size < obj.binary_vector.size() ; size++)
	{
		this->binary_vector.push_back( obj.binary_vector[size] );
	}

	for (size_t size = 0 ; size < obj.number_vector.size() ; size++) 
	{
		this->number_vector.push_back( obj.number_vector[size] );
	}
}
BigNumberUsingBits::BigNumberUsingBits(string number_string)
{
	this->BigNumberStr = number_string;
	this->Convert_String_to_Int_vector(number_string, number_vector);
	this->Convert_int_vector_to_binary_vector(number_vector, binary_vector);
}
BigNumberUsingBits::~BigNumberUsingBits()
{
}

//result caclculated in Add not-reveresed Most in Least
BigNumberUsingBits BigNumberUsingBits::Add(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2)//, BigNumberUsingBits & result)
{
	BigNumberUsingBits result;
	int i = 0, j = 0;
	int carry = 0;

	while ((i < num1.binary_vector.size()) || (j < num2.binary_vector.size()))//loop on the 1st number till ends
	{
		if (i >= num1.binary_vector.size())
		{
			result.binary_vector.insert(result.binary_vector.begin(), ((num2.binary_vector[j] + carry) % 2 ));
			carry = (num2.binary_vector[j]+carry) / 2;
		}
		else if (j >= num2.binary_vector.size())
		{
			result.binary_vector.insert(result.binary_vector.begin(), ((num1.binary_vector[i] + carry) % 2 ));
			carry = (num1.binary_vector[i] + carry) / 2;
		}
		else
		{
			result.binary_vector.insert(result.binary_vector.begin(), ((num1.binary_vector[i] + num2.binary_vector[j] + carry) % 2 ));
			carry = (num1.binary_vector[i] + num2.binary_vector[j]+carry) / 2;
		}
		i++; j++;
	}

	//handling the possible carry case
	if (carry) 
	{
		result.binary_vector.insert(result.binary_vector.begin(), carry);
	}
	reverse(result.binary_vector.begin(), result.binary_vector.end());
	return result;
}

BigNumberUsingBits BigNumberUsingBits::operator+( const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	result = result.Add(*this, num2);
	return result;
}

BigNumberUsingBits BigNumberUsingBits::operator-(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	result = result.Sub(*this, num2);
	return result;
}

BigNumberUsingBits BigNumberUsingBits::operator*(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	result = result.Mul(*this, num2);
	return result;
}

BigNumberUsingBits BigNumberUsingBits::operator/(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	result = result.Div(*this, num2);
	return result;
}

BigNumberUsingBits BigNumberUsingBits::operator%(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	result = result.Mod(*this, num2);
	return result;
}

//result caclculated in Sub (Least in Least)
BigNumberUsingBits BigNumberUsingBits::Sub(const BigNumberUsingBits& num1, const BigNumberUsingBits& num2)
{
	BigNumberUsingBits result;
	BigNumberUsingBits number1copy = num1;
	BigNumberUsingBits number2copy = num2;
	int num1_count = 0, num2_count = 0, borrow = 0;
	int number1_current_bit = 0 , number2_current_bit = 0;

	//check which number is the smallest so we subtract the bigger one from the smaller
	if (Isgreater(number1copy, number2copy))
	{
		number1copy.binary_vector.swap(number2copy.binary_vector);
		result.negative_sign = true;
	}
	//
	while( num1_count < number1copy.binary_vector.size() || num2_count < number2copy.binary_vector.size() )
	{
		if (num1_count >= number1copy.binary_vector.size())
		{
			number1_current_bit = 0;
		}
		else
		{
			number1_current_bit = number1copy.binary_vector[num1_count];
		}
		////
		if (num2_count >= number2copy.binary_vector.size())
		{
			number2_current_bit = 0;
		}
		else
		{
			number2_current_bit = number2copy.binary_vector[num2_count];
		}
		////
		if (number1_current_bit - number2_current_bit - borrow > 0) 
		{
			result.binary_vector.insert(result.binary_vector.begin(),(number1_current_bit - number2_current_bit - borrow) );
			borrow = 0;
		}
		else if (number1_current_bit - number2_current_bit - borrow < 0) 
		{
			if (number1_current_bit - number2_current_bit - borrow == -2) {
				result.binary_vector.insert(result.binary_vector.begin(), 0);
			}
			if (number1_current_bit - number2_current_bit - borrow == -1) {
				result.binary_vector.insert(result.binary_vector.begin(), 1);
			}
			borrow = 1;
		}
		else  if (number1_current_bit - number2_current_bit - borrow == 0)
		{
			result.binary_vector.insert(result.binary_vector.begin(), 0 );
			borrow = 0;
		}
		num1_count++; num2_count++;
	}
	//loop to erase the leading zeros in the result number
	while ( (result.binary_vector[0] == 0) && (result.binary_vector.size() > 1) )
	{
		result.binary_vector.erase(result.binary_vector.begin());
	}
	reverse(result.binary_vector.begin(), result.binary_vector.end());
	return result;
}

BigNumberUsingBits BigNumberUsingBits::Mul(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2)
{
	BigNumberUsingBits multiplicand = num1;
	BigNumberUsingBits multiplier = num2;
	BigNumberUsingBits product;
	//looping on the binary_vector
	for (size_t size = 0 ; size < multiplier.binary_vector.size() ; size++ )
	{
		if (multiplier.binary_vector[size] == 1) 
		{
			multiplicand.binary_vector.insert(multiplicand.binary_vector.begin() , size , 0);
			product = product.Add(product, multiplicand);
			multiplicand = num1;
		}
	}
	return product;
}

BigNumberUsingBits BigNumberUsingBits::Div(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2 )
{
	return Div_Mod(num1, num2, divsion);
}

BigNumberUsingBits BigNumberUsingBits::Mod(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2)
{
	return Div_Mod(num1, num2, modulus);
}

size_t BigNumberUsingBits::Convert_String_to_Int_vector(string number_str, vector<int>& int_array)
{
	size_t str_pos = 0;
	for (str_pos = 0 ; str_pos < number_str.size() ; str_pos++)
	{
		int_array.push_back(number_str[str_pos] - '0');
	}
	return str_pos;
}

//converting a vector representing a big unsigned int number into a vector
//have the binary representation to the same number returning vector (MSB in Least)
void BigNumberUsingBits::Convert_int_vector_to_binary_vector(vector<int>& int_vector, vector<int>& bin_vector)
{
	vector<int> temp(int_vector);
	vector<int> buffer;
	int remainder = 0;
	while (temp.size() >= 1)
	{
		remainder = Divide_int_vector_by_two(temp, buffer);
		if (remainder)
		{
			bin_vector.push_back(1);//Least in Least
		}
		else
		{
			bin_vector.push_back(0);//Least in Least
		}
		temp = buffer;
		buffer.clear();
	}
}

//Divide a big uint number by 2 takes int vector and quotient vector to be filled and returns the result remainder
int BigNumberUsingBits::Divide_int_vector_by_two(vector<int>& int_array, vector<int>& quotient)
{
	//converting a decimal number having each digit in a different vector element
	//to another binary vector having each bit from the binary representation of the int vector 
	//in a different element
	//consider it divide by 2
	int digit_pos = 0;
	int temp_dividend = 0;

	for ( digit_pos = 0 ; digit_pos < int_array.size() ; digit_pos++)
	{
		//get the new remainder and concat a new digit from our int_array
		temp_dividend = (temp_dividend % 2) * 10 + int_array[digit_pos];
		//put new digit to the result
		if (digit_pos != 0 || (temp_dividend / 2) != 0)
		{
			quotient.push_back(temp_dividend / 2);
		}
	}
	return (temp_dividend % 2);
}

//starting from the MSB to LSB comparing this function works on binary representation (Least in Least)e.g. "2"="01" working on vectors (LSB in Least)
//checks is num2 is greater than num1
bool BigNumberUsingBits::Isgreater(BigNumberUsingBits & num1, BigNumberUsingBits & num2)
{
	bool greater = false;
	size_t j = num2.binary_vector.size()-1;

	//check on size
	if( num2.binary_vector.size() > num1.binary_vector.size() ) 
	{
		greater = true;
	}
	else if (num2.binary_vector.size() == num1.binary_vector.size())
	{
		for (j = num2.binary_vector.size() ; j > 0; j--)
		{
			if (num2.binary_vector[j-1] > num1.binary_vector[j-1])
			{
				greater = true;
				break;
			}
			else if (num2.binary_vector[j-1] < num1.binary_vector[j-1])
			{
				break;
			}
		}
	}
	return greater;
}

//starting from the MSB to LSB comparing this function works on binary representation (Least in Least)e.g. "2"="01" working on vectors (LSB in Least)
//checks is num2 is greater than num1
bool BigNumberUsingBits::IsGreaterOrEqual(BigNumberUsingBits & num1, BigNumberUsingBits & num2)//divisor--dividend
{
	bool greater_or_equal = false;
	size_t j = num2.binary_vector.size() - 1;
	//check on size
	if (num2.binary_vector.size() > num1.binary_vector.size())
	{
		greater_or_equal = true;
	}
	else if (num2.binary_vector.size() == num1.binary_vector.size())
	{	
		//check on the 1st different bit if num1[i] is 1 and num2[i] is 0 then num1 is greater
		for (j= num2.binary_vector.size(); j > 0 ; j-- )
		{
			if (num2.binary_vector[j-1] >= num1.binary_vector[j-1])
			{
				greater_or_equal = true;
			}
			else if (num2.binary_vector[j-1] < num1.binary_vector[j-1])
			{
				greater_or_equal = false;
				break;
			}
		}
	}
	return greater_or_equal;
}

//this function only implements diving a big int on normal int
int BigNumberUsingBits::LongDivsion(vector<int>& int_array, vector<int>& quotient, int divisor)
{
	int digit_pos = 0;
	int temp_dividend = int_array[digit_pos];
	int remainder;
	
	//handling the case when diving 0 on anything
	if (!Check_vector_all_zeros(int_array))
	{
		return -1;//-1 here means infinity 0/anything = infinity
	}
	
	//handling the case when diving anything on 0
	if (!divisor) 
	{
		return -1;//-1 here means infinity anything/0 = infinity
	}
	
	//looping on the dividend till we get a number that is fit to be divided on the divisor starting from the Most Significant Digit
	while ( (temp_dividend < divisor) && (digit_pos < int_array.size()-1 ) )
	{
		temp_dividend = temp_dividend * 10 + int_array[++digit_pos];
	}
	
	//looping on the dividend number starting from the digit position that we got from the above loop
	//diving the temp_sub_dividend and getting a new digit from the original dividend
	while ( digit_pos < int_array.size())
	{
		//put new digit to the result
		quotient.push_back(temp_dividend / divisor);

		//handling the case of when we reach the end of our dividend and we don't need to get a new temp_dividend
		//and also we have no more vector elements in int_array to refrence
		if (digit_pos == int_array.size() - 1)
		{
			break;
		}
		//get the new remainder and concat a new digit from our int_array
		temp_dividend = ((temp_dividend % divisor) * 10) + int_array[++digit_pos];
	}
	remainder = temp_dividend % divisor;
	return remainder;
}

//printing the binary vector in BigNumberUsingBits object from Least to Most i=0 i++
void BigNumberUsingBits::Print_number_in_binary()
{
	if (this->negative_sign == true)
	{
		cout << "-";
	}
	for (size_t i = 0; i < this->binary_vector.size() ; i++)
	{
		cout << this->binary_vector[i];
	}
	cout << endl;
}

bool BigNumberUsingBits::Check_vector_all_zeros(vector<int>& vec_under_test)
{
	bool all_zero_flag = true;
	int pos = 0;

	while (pos < vec_under_test.size())
	{
		if (vec_under_test[pos++] != 0)
		{
			all_zero_flag = false;
		}
	}
	return all_zero_flag;
}

BigNumberUsingBits BigNumberUsingBits::Div_Mod(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2, operation mode)
{
	BigNumberUsingBits dividend = num1;
	BigNumberUsingBits divisor = num2;
	BigNumberUsingBits quotient("0");
	BigNumberUsingBits result("1");
	BigNumberUsingBits one("1");
	BigNumberUsingBits remainder("0");

	size_t dividend_n_divisor_size_difference = 0;
	if (Isgreater(dividend, divisor)) {
		return dividend;
	}
	//
	while (IsGreaterOrEqual(divisor, dividend))
	{
		dividend_n_divisor_size_difference = dividend.binary_vector.size() - divisor.binary_vector.size();
		divisor.binary_vector.insert(divisor.binary_vector.begin(), dividend_n_divisor_size_difference, 0);//y>>size
		result.binary_vector.insert(result.binary_vector.begin(), dividend_n_divisor_size_difference, 0);//result=(1<<size)																	
		if (Isgreater(dividend, divisor) && dividend_n_divisor_size_difference > 0) //if(y>x)
		{
			result.binary_vector.clear();
			result.binary_vector.insert(result.binary_vector.begin(), 1);
			divisor.binary_vector.erase(divisor.binary_vector.begin());//y>>1
			dividend_n_divisor_size_difference -= 1;
			result.binary_vector.insert(result.binary_vector.begin(), dividend_n_divisor_size_difference, 0);//result=(1<<size)
			quotient = quotient.Add(quotient, result);
		}
		else
		{
			quotient = quotient.Add(quotient, result);
		}
		//
		dividend = dividend.Sub(dividend, divisor);
		divisor = num2;
		result.binary_vector.clear();
		result.binary_vector.insert(result.binary_vector.begin(), 1);
	}
	remainder = dividend;
	//
	if (mode == divsion) {
		return quotient;
	}
	else{
		return remainder;
	}
}