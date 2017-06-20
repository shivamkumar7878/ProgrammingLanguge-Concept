// A simple lexical analyzer for C/C++-style variable declarations.
// The grammar for the declarations is as follows:
//
// <declaration> 	::= 	<type>  <var> ’;’ | <type> <var> ’=’ <number> ’;’
// <type> 		::= 	int | float
// <var> 		::= 	A | B | C | D | E
// <number> 	::= 	<integer> | <float>
// <integer> 	::= 	<integer> <digit> | <digit>
// <digit> 		::= 	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
// <float> 		::= 	<integer> ‘.’ <integer>
// 
// The task of this exercise is to write a lexical analyzer (or 
// scanner) for the tokens used in the above grammar. The following
// is the regular expression that defines the tokens:
//
//		= | ; | int | float | A | B | C | D | E | [0-9]+ | [0-9]+\.[0-9]+
//
// The program will read a declaration from the keyboard, and the
// scanner you design should recognize and print out all tokens
// included in the input. For example, given the following declaration:
//
//		int A = 123;
//
// your program should print:
//
// int
// A
// =
// 123
// ;
//
// Make sure your program print out the token one per line in the order 
// they appear in the input. Once an erroneous token is encountered, your
// scanner should print out an error message and stopped scanning. For
// example, given the following input:
//
//		int A = 0#;
//
// your program should print:
//
// int
// A
// =
// 0
// #: Error: Unrecognizable token
//
// Note that tokens may NOT be separated by spaces. For example, the above
// input:
//
//		int A = 123;
//
// does not have a space to separate 123 and ;. Also, the following inputs
// are also legal and generate the same output:
//
//		int A=123;
//		intA=123;
// 
// However, a whole token cannot be separated by spaces. For example, the
// following input will cause 12 and 3 to be regarded as two distinct tokens.
//
//		int A = 12 3;
//
// The ouput will look like:
// int
// A
// =
// 12
// 3
// ;
//
// Also note that the scanner doesn't check for syntactic errors. Therefore the
// above input is legal to this program.
//
// Important!!! Save your GetToken program. We are going to use it in future 
// labs.


//#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string GetToken();

int main() {
	string token;

	cout << "Please enter a declaration in format "
		<< "<type> <variable> [= number];" << endl;

	cout << "The following are the tokens in the input:" << endl;

	token = GetToken();

	while (token != "") {
		cout << token << endl;
		token = GetToken();
	}

	cout << "Done!" << endl;

	cin.get();
	return 0;
}

string GetToken() {
	string token;
	string error;
	bool goToken = true;
	char ch;

	// Write the code here. Read the next token and store it in variable "token".
	// The token must be read character by character. Use the regular expression
	// defined above to extract tokens from the input.
	// 
	// To read a character from keyboard, use:
	//
	//		cin.get(ch);
	//
	// where "ch" is a character variable.

	while (goToken == true)
	{
		cin.get(ch);

		while (ch == ' ')
		{
			cin.get(ch);
		}

		if (isdigit(ch))
		{
			while (isdigit(ch))
			{
				token = token + ch;
				cin.get(ch);

				if (ch == '.')
				{
					token = token + ch;
					cin.get(ch);
				}

				if (ch == ';')
				{
					token = token + '\n' + ch;
				}

				if (ch == '#')
				{
					token = token + '\n' + ch + ':' + " Error: Unrecognizable token";
				}
			}

			goToken = false;
		}
		else
		{
			token = token + ch;

			if (token == "i")
			{
				goToken = true;
			}
			else if (token == "in")
			{
				goToken = true;
			}
			else if (token == "int")
			{
				goToken = false;
			}
			else if (token == "f")
			{
				goToken = true;
			}
			else if (token == "fl")
			{
				goToken = true;
			}
			else if (token == "flo")
			{
				goToken = true;
			}
			else if (token == "floa")
			{
				goToken = true;
			}
			else if (token == "float")
			{
				goToken = false;
			}

			//variable
			else if (token == "A" || token == "B" || token == "C" || token == "D" || token == "E")
			{
				goToken = false;
			}
			//equal
			else if (token == "=")
			{
				goToken = false;
			}
			//semicolon
			else if (token == ";")
			{
				goToken = false;
			}
			//enter
			else if (token == "\n")
			{
				token = "";
				goToken = false;
			}
			else
			{
				token = token + ':' + " Error: Unrecognizable token";
				goToken = false;
			}
		}

	}
	return token;
}