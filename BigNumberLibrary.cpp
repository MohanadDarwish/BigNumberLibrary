// BigNumberLibrary.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Log.h"
#include "BigNumUsingBitsClass.h"
#include <string>
#include <iostream>

#include "openssl\rand.h"
#include "openssl\bn.h"

using namespace std;

int main()
{
	cout << "main .."<< "\n"; 

	//system("Color 0A");	//light green F Black B
	system("Color 0B");		//light cyan F Black B
	//system("Color 09");	//light blue F Black B
/////////////////////////////////////
#ifdef BIG_NUMBER_VECTOR
string str, str1,str2;
	vector<int> digit_array;
	vector<int> digit_array2;
	vector<int> result;
	vector<int> bin_array;
	vector<int> quotient;
	size_t digit_array_size = 0, digit_array_size2 = 0 , digit_arr_pos = 0;
	//
	cout << "please enter number 1: ";
	cin >> str1;
	cout << "please enter number 2: ";
	cin >> str2;
	//
	BigNumberUsingBits n1(str1);
	BigNumberUsingBits n2(str2);
	BigNumberUsingBits res1;
	BigNumberUsingBits res2;
	BigNumberUsingBits res3;
	BigNumberUsingBits res4;
	BigNumberUsingBits res5;
	BigNumberUsingBits res6;
	BigNumberUsingBits res7;
	BigNumberUsingBits res8;
	BigNumberUsingBits res9;
	BigNumberUsingBits res10;
	BigNumberUsingBits res11;
	//
	n1.Print_number_in_binary_vector();
	n2.Print_number_in_binary_vector();
	cout << endl;
	cout << "result of addition :" << endl;
	res1 = n1.Add(n1, n2);
	//Print function reverse the vector so we can see the value in the correct order M in L 2(10)
	res1.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res1.ToDecimal() << endl << endl;
	//
	res2 = n1.Sub(n1, n2);
	cout << "result of subtraction :" << endl;
	res2.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res2.ToDecimal() << endl << endl;
	//
	res4 = n1.Mul(n1, n2);
	cout << "result of multiplication :" << endl;
	res4.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res4.ToDecimal() << endl << endl;
	//
	res5 = n1.Div(n1, n2);
	cout << "result of divsion  :" << endl;
	res5.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res5.ToDecimal() << endl << endl;
	//
	res6 = n1.Mod(n1, n2);
	cout << "result of Modulus  :" << endl;
	res6.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res6.ToDecimal() << endl << endl;
	//
	res7 = n1+n2;
	cout << "result of operator+  :" << endl;
	res7.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res7.ToDecimal() << endl << endl;
	//
	res8 = n1 - n2;
	cout << "result of operator-  :" << endl;
	res8.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res8.ToDecimal() << endl << endl;
	//
	res9 = n1 * n2;
	cout << "result of operator*  :" << endl;
	res9.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res9.ToDecimal() << endl << endl;
	//
	res10 = n1 / n2;
	cout << "result of operator/  :" << endl;
	res10.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res10.ToDecimal() << endl << endl;
	//
	res11 = n1 % n2;
	cout << "result of operator%  :" << endl;
	res11.Print_number_in_binary_vector();
	cout << "ToDecimal(): " << res11.ToDecimal() << endl << endl;
	//
	//
	cout << "result of operator> (n1 > n2) : " << (n1 > n2) << endl;
	//
	cout << "result of operator== (n1 == n2)  : " << (n1 == n2) << endl;
	//
	cout << "n1.ToHex(): " << n1.ToHex() << endl;
	//
	cout << "n1.ToString(): " << n1.ToString() << endl;
	//
	cout << "n1.ToDecimal(): " << n1.ToDecimal() << endl;
	cout << "n2.ToDecimal(): " << n2.ToDecimal() << endl << endl;
	//
	n1.Pow(n1, n2);
	cout << "pow done!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << " Pow(n1,n2).ToDecimal():= " << (n1.Pow(n1, n2)).ToDecimal() << endl;
	//
	BigNumberUsingBits trial;
	trial = "777";
	cout << " trial.ToDeimal():= " << trial.ToDecimal() << endl;
	cout << " trial.ToString():= " << trial.ToString() << endl;
	//
	//cout<< "n1.PowMod():= " << ( n1.PowMod ( BigNumberUsingBits("123") , BigNumberUsingBits("789") , BigNumberUsingBits("10") ) ).ToDecimal() <<endl;
#endif
	//using random from stl c++11
	BigNumberUsingBits a,b;
	a.generate_random_bignumber(8);
	cout << endl << "random number:= ";
	a.Print_number_in_decimal_vector();
	a.Print_number_in_binary_vector();

	cout << endl<< "prime number:= ";
	b.generate_prime_bignumber(8);
	b.Print_number_in_decimal_vector();
	b.Print_number_in_binary_vector();

    return 0;
}