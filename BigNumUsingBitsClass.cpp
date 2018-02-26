#include "stdafx.h"
#include "BigNumUsingBitsClass.h"
//#include <algorithm>

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
	this->Convert_String_to_Int_vector();
	this->Convert_int_vector_to_binary_vector();
}
BigNumberUsingBits::~BigNumberUsingBits()
{
}

BigNumberUsingBits BigNumberUsingBits::operator+(const BigNumberUsingBits & num2)
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

bool BigNumberUsingBits::operator>(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	bool comparison_result;

	comparison_result = result.GreaterOnly(*this, num2);
	return comparison_result;
}

bool BigNumberUsingBits::operator==(const BigNumberUsingBits & num2)
{
	BigNumberUsingBits result;
	bool equality_result;
	equality_result = result.IsEqual(*this, num2);
	return equality_result;
}

bool BigNumberUsingBits::GreaterOnly( const BigNumberUsingBits & num1, const BigNumberUsingBits & num2)
{
	bool greater_only = false;
	size_t j = num2.binary_vector.size() - 1;

	//check on size
	if (num1.binary_vector.size() > num2.binary_vector.size())
	{
		greater_only = true;
	}
	else if (num1.binary_vector.size() == num2.binary_vector.size())
	{
		for (j = num1.binary_vector.size(); j > 0; j--)
		{
			if (num1.binary_vector[j - 1] > num2.binary_vector[j - 1])
			{
				greater_only = true;
				break;
			}
			else if (num1.binary_vector[j - 1] < num2.binary_vector[j - 1])
			{
				break;
			}
		}
	}
	return greater_only;
}

bool BigNumberUsingBits::IsEqual(const BigNumberUsingBits & num1, const BigNumberUsingBits & num2)
{
	bool is_equal = true;
	size_t j = num2.binary_vector.size() - 1;

	//check on size
	if (num1.binary_vector.size() == num2.binary_vector.size())
	{
		for (j = num1.binary_vector.size(); j > 0; j--)
		{
			if (num1.binary_vector[j - 1] != num2.binary_vector[j - 1])
			{
				is_equal = false;
				break;
			}
		}
	}
	else
	{
		is_equal = false;
	}
	return is_equal;
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

size_t BigNumberUsingBits::Convert_String_to_Int_vector()
{
	size_t str_pos = 0;
	for (str_pos = 0; str_pos < this->BigNumberStr.size(); str_pos++)
	{
		this->number_vector.push_back(this->BigNumberStr[str_pos] - '0');
	}
	return str_pos;
}

//converting a vector representing a big unsigned int number into a vector
//have the binary representation to the same number returning vector (MSB in Least)
void BigNumberUsingBits::Convert_int_vector_to_binary_vector()
{
	vector<int> temp(this->number_vector);
	vector<int> buffer;
	int remainder = 0;
	while (temp.size() >= 1)
	{
		remainder = Divide_int_vector_by_two(temp, buffer);
		if (remainder)
		{
			this->binary_vector.push_back(1);//Least in Least
		}
		else
		{
			this->binary_vector.push_back(0);//Least in Least
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
		cout << static_cast<int>(this->binary_vector[i]);
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

string BigNumberUsingBits::ToHex()
{
	string converted_string;
	size_t remaining_vector_elements;//must be >=4
	char temp_hex_char = 0;
	//
	for (size_t vector_pos = 0 ; vector_pos < this->binary_vector.size() ; vector_pos+=4)
	{
		remaining_vector_elements = this->binary_vector.size() - vector_pos;
		if (remaining_vector_elements < 4)
		{
			for (size_t i = 0; i < remaining_vector_elements; i++) 
			{
				if (i == 0) 
				{
					temp_hex_char += (this->binary_vector[vector_pos]);
				}
				else 
				{
					temp_hex_char += (this->binary_vector[vector_pos + i] * (i * 2));
				}
				
			}
			vector_pos = this->binary_vector.size();
		}
		else
		{
			temp_hex_char = (this->binary_vector[vector_pos + 0]	) +
							(this->binary_vector[vector_pos + 1] * 2) +
							(this->binary_vector[vector_pos + 2] * 4) +
							(this->binary_vector[vector_pos + 3] * 8) ;
		}
		//
		if (temp_hex_char >= 0 && temp_hex_char < 10)
		{
			temp_hex_char += '0';
		}
		else
		{
			temp_hex_char = (temp_hex_char - 10) + 'A';
		}
		//
		converted_string.insert(converted_string.begin(), temp_hex_char);
		temp_hex_char = 0;
	}

	return converted_string;
}

string BigNumberUsingBits::ToDecimal()
{
	//local variables
	char temp_hex_char = 0;
	int shift_counter = 0;
	string converted_string;
	size_t decimal_digit_place = 0;
	//a copy of the this->binary_vector so we don't alter the binary_vector of the calling object.
	vector<char> num_binary_vector_copy(this->binary_vector);
	//4 element char vector used to initialize the whole vectors a muliplte of push_back(digit_bcd_vector)
	vector<char> digit_bcd_vector(4, 0);
	//whole num bcd vector should hold the bdc representation of the inputed binary vector
	vector< vector<char> > whole_num_bcd_vector;
	//temp obj i use to call some class methods
	BigNumberUsingBits obj;

	//double dabble alg.
	//take the last bit in binary_vector to last pos in whole_num_bcd_vector  
	whole_num_bcd_vector.push_back(digit_bcd_vector);

	size_t bin_vec_copy_pos = num_binary_vector_copy.size()+1;

	while ( num_binary_vector_copy.size() )
	{	
		//shift whole_num_bcd_vector to left aka [0]<-..[n-1]<-[n]
		shift_whole_num_bcd_vector_left(whole_num_bcd_vector);
		
		//new bit
		whole_num_bcd_vector[0][3] = num_binary_vector_copy[num_binary_vector_copy.size() - 1];

		shift_counter++;

		num_binary_vector_copy.pop_back();
		if (shift_counter < this->binary_vector.size())
		{
			//check the current digit if >4 ? add 3 : move on()
			update_bcd_digit_value_coressponding_to_its_current_value( whole_num_bcd_vector );
		}
		//
		if (whole_num_bcd_vector[decimal_digit_place].front())
		{
			whole_num_bcd_vector.push_back(digit_bcd_vector);//pushing back zeros in packs of 4 corresponding to the expected bcd decimals outputed
			decimal_digit_place++;
		}
	}
	//checking if there are a leading zeroes (an inner vector extra full of zeroes not needed)
	if (! (    whole_num_bcd_vector[whole_num_bcd_vector.size() - 1 ][ 0 ] && whole_num_bcd_vector[ whole_num_bcd_vector.size() - 1 ][ 1 ]
			&& whole_num_bcd_vector[whole_num_bcd_vector.size() - 1 ][ 2 ] && whole_num_bcd_vector[ whole_num_bcd_vector.size() - 1 ][ 3 ]) ) {
		whole_num_bcd_vector.pop_back();
	}
	///////////////////////////////////	
	for (size_t vector_pos = whole_num_bcd_vector.size(); vector_pos > 0 ; vector_pos--)
	{
		temp_hex_char = ( whole_num_bcd_vector[vector_pos-1][0] * 8) +
						( whole_num_bcd_vector[vector_pos-1][1] * 4) +
						( whole_num_bcd_vector[vector_pos-1][2] * 2) +
						( whole_num_bcd_vector[vector_pos-1][3] * 1) ;
		//
		if (temp_hex_char >= 0 && temp_hex_char < 10)
		{
			temp_hex_char += '0';
		}
		//converted_string.insert(converted_string.begin(), temp_hex_char);
		converted_string.push_back(temp_hex_char);
		temp_hex_char = 0;
	}
	return converted_string;
}

void BigNumberUsingBits::update_bcd_digit_value_coressponding_to_its_current_value( vector< vector<char> >& whole_num_bcd_vector )
{
	for (size_t whole_size = 0; whole_size < whole_num_bcd_vector.size(); whole_size++)
	{
		char temp_hex_char = 0;
		//check the current digit if >4 ? add 3 : move on()
		temp_hex_char = (whole_num_bcd_vector[whole_size][3]    ) +
						(whole_num_bcd_vector[whole_size][2] * 2) +
						(whole_num_bcd_vector[whole_size][1] * 4) +
						(whole_num_bcd_vector[whole_size][0] * 8) ;
		if (temp_hex_char > 4)
		{
			//	temp_hex_char += 3;
			switch (temp_hex_char)
			{
			case 5://0101 + 11 = 1000
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			case 6://0110 + 11 = 1001
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 1;
				break;
			case 7://0111 + 11 = 1010
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 1; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			case 8://1000 + 11 = 1011
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 0;
				whole_num_bcd_vector[whole_size][2] = 1; whole_num_bcd_vector[whole_size][3] = 1;
				break;
			case 9://1001 + 11 = 1100
				whole_num_bcd_vector[whole_size][0] = 1; whole_num_bcd_vector[whole_size][1] = 1;
				whole_num_bcd_vector[whole_size][2] = 0; whole_num_bcd_vector[whole_size][3] = 0;
				break;
			}
		}
		temp_hex_char = 0;
	}
}

void BigNumberUsingBits::shift_whole_num_bcd_vector_left(vector< vector<char> >& whole_num_bcd_vector)
{
 	size_t number_of_bcd_digits = whole_num_bcd_vector.size();
	size_t number_of_transitions_between_inner_vectors = whole_num_bcd_vector.size() - 1;

	//loop from the end of whole_num_bcd_vector to first element
	for (size_t whole_pos = number_of_bcd_digits ; whole_pos > 0; whole_pos--)//size-1 --> size-2 --> size-3 ..-->0
	{
		//three small shifting arrows
		whole_num_bcd_vector[whole_pos - 1][0] = whole_num_bcd_vector[whole_pos - 1][1];
		whole_num_bcd_vector[whole_pos - 1][1] = whole_num_bcd_vector[whole_pos - 1][2];
		whole_num_bcd_vector[whole_pos - 1][2] = whole_num_bcd_vector[whole_pos - 1][3];
		whole_num_bcd_vector[whole_pos - 1][3] = 0;
		//
		if ( (number_of_transitions_between_inner_vectors > 0) )
		{
			//the big shifting arrow from an inner vector[0] to the next inner vector[3]
			whole_num_bcd_vector[whole_pos-1][3] = whole_num_bcd_vector[whole_pos-2][0];
			whole_num_bcd_vector[whole_pos-2][0] = 0;
			number_of_transitions_between_inner_vectors--;
		}		
	}
}

string BigNumberUsingBits::ToString()
{
	string converted_string;

	char temp_hex_char = 0;
	//
	for (size_t vector_pos = 0 ; vector_pos < this->binary_vector.size() ; vector_pos++)
	{
		temp_hex_char = this->binary_vector[vector_pos];
		//
		temp_hex_char += '0';
		//
		converted_string.insert(converted_string.begin() , temp_hex_char);
		temp_hex_char = 0;
	}
	return converted_string;
}
