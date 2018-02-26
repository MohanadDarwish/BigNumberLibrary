﻿// BigNumberLibrary.cpp : Defines the entry point for the console application.
//
//***** This is a demo on how to use the library and the outputs ******//

#include "stdafx.h"
#include "Log.h"
#include "BigNumUsingBitsClass.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	//system("Color 0A");	//light green F Black B
	system("Color 0B");		//light cyan F Black B
	//system("Color 09");	//light blue F Black B
	
#ifdef TEST_CODE
	BigNumber a;
	Log print;
	print.SetLevel(none);
	print.Debug_L0("Debug level0", 0);
	print.Debug_L1("Debug level1", 1);
	print.Debug_L2("Debug level2", 2);
	print.Warning("Warning", 3);
	print.Error("Error", 4);
	while (1)
	{
		cout << "Please enter 2 big numbers to be added: " << endl;
		cin >> n1 >> n2;
		cout << "Result of invoking Add(a,b): " << a.Add(n1, n2) << endl;
	}
#endif // TEST_CODE
/////////////////////////////////////
#ifdef BIG_NUMBER_VECTOR
string str, str1,str2;
	vector<int> digit_array;
	vector<int> digit_array2;
	vector<int> result;
	vector<int> bin_array;
	vector<int> quotient;
	size_t digit_array_size = 0, digit_array_size2 = 0 , digit_arr_pos = 0;

	cout << "please enter number 1: ";
	cin >> str1;
	cout << "please enter number 2: ";
	cin >> str2;

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
	
	n1.Print_number_in_binary();
	n2.Print_number_in_binary();
	cout << "result of addition :" << endl;
	res1 = n1.Add(n1, n2);
	//Print function reverse the vector so we can see the value in the correct order M in L 2(10)
	res1.Print_number_in_binary();
	//
	res2 = n1.Sub(n1, n2);
	cout << "result of subtraction :" << endl;
	res2.Print_number_in_binary();
	//
	res4 = n1.Mul(n1, n2);
	cout << "result of multiplication :" << endl;
	res4.Print_number_in_binary();
	//
	res5 = n1.Div(n1, n2);
	cout << "result of divsion  :" << endl;
	res5.Print_number_in_binary();
	//
	res6 = n1.Mod(n1, n2);
	cout << "result of Modulus  :" << endl;
	res6.Print_number_in_binary();
	//
	res7 = n1+n2;
	cout << "result of operator+  :" << endl;
	res7.Print_number_in_binary();
	//
	res8 = n1 - n2;
	cout << "result of operator-  :" << endl;
	res8.Print_number_in_binary();
	//
	res9 = n1 * n2;
	cout << "result of operator*  :" << endl;
	res9.Print_number_in_binary();
	//
	res10 = n1 / n2;
	cout << "result of operator/  :" << endl;
	res10.Print_number_in_binary();
	//
	res11 = n1 % n2;
	cout << "result of operator%  :" << endl;
	res11.Print_number_in_binary();
	//
	cout << "result of operator> (n1 > n2) :" << (n1 > n2) << endl;
	//
	cout << "result of operator== (n1 == n2)  :" << (n1 == n2) << endl;
	//
	cout << "n1.ToHex(): " << n1.ToHex() << endl;
	//
	cout << "n1.ToString(): " << n1.ToString() << endl;
	//
	cout << "n1.ToDecimal(): " << n1.ToDecimal() << endl;
	
#endif
    return 0;
}
