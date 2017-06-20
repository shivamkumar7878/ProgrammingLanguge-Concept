
// CS4303 Programming Language Concepts
// Lab exercise - Scanner
//
// Name ______________________ ID _____________________
//
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

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

vector<string>* GetToken(string input);
static void SkipWhiteSpace(string input, unsigned int& i);
static void ReportTrash(string input, unsigned int i, vector<string>* output);
static void ReportTrash(string input, string trash, unsigned int i, vector<string>* output);

int main()
{
	vector<string>* tokenVec;
	string input;
	cout << "Please enter a declaration in format "
		<< "<type> <variable> [= number];" << endl;
	getline(cin, input);
	cout << "The following are the tokens in the input:" << endl;

	tokenVec = GetToken(input);
	for (unsigned int i = 0; i < tokenVec->size(); i++)
	{
		cout << tokenVec->at(i) << endl;
	}
	cout << "Done!" << endl;
	delete tokenVec;
	cin.get();
	return 0;
}

vector<string>* GetToken(string input)
{
	vector<string>* output = new vector<string>();
	//if variable type isn't float or int, report and return
	if (input[0] != 'i' && input[0] != 'f')
	{
		ReportTrash(input, 0, output);
	}
	else
	{
		bool isFloat = false;
		unsigned int i = 0;
		if (input[i] == 'i')
		{
			string intString = "";
			while (i < input.length() && isalpha(input[i]) && input[i] != toupper(input[i]))
			{
				intString += input[i];
				i++;
			}
			//if variable type isn't int and starts with 'i'
			if (intString != "int")
			{
				ReportTrash(input, intString, i, output);
				return output;
			}
			else
			{
				output->push_back(intString);
			}
		}
		else if (input[i] == 'f')
		{
			string floatString = "";
			while (i < input.length() && isalnum(input[i]) && input[i] != toupper(input[i]))
			{
				floatString += input[i];
				i++;
			}
			//if variable type isn't float and starts with float
			if (floatString != "float")
			{
				ReportTrash(input, floatString, i, output);
				return output;
			}
			else
			{
				isFloat = true;
				output->push_back(floatString);
			}
		}

		SkipWhiteSpace(input, i);
		//if next char isn't a alphabetical char, report and return
		if (i < input.length() && !isalpha(input[i]))
		{
			ReportTrash(input, i, output);
			return output;
		}
		//else read variable name
		
		while (isalpha(input[i]) && input[i] == toupper(input[i]))
		{
			string varName = "";
			while (i < input.length() && isalpha(input[i]))
			{
				varName += input[i];
				//if a char is read that isn't in the accepted set, report and return
				if (input[i] != 'A' && input[i] != 'B' && input[i] != 'C' && input[i] != 'D' && input[i] != 'E')
				{
					ReportTrash(input, varName, i, output);
					return output;
				}
				i++;
			}
			output->push_back(varName);

			SkipWhiteSpace(input, i);
		}
		//if terminates with ';'
		if (input[i] == ';')
		{
			output->push_back(";");
			i++;
			//if chars exist after ';', report
			if (i < input.length())
			{
				ReportTrash(input, i, output);
			}
			return output;
		}
		//if statement continues
		else if (input[i] == '=')
		{
			output->push_back("=");
			i++;
		}
		//char read after variable name isn't valid, report and return
		else
		{
			ReportTrash(input, -1, output);
			return output;
		}

		SkipWhiteSpace(input, i);

		//if char after '=' isn't a digit, report and return 
		if (!isdigit(input[i]) && (input[i] == '.' && !isFloat))
		{
			ReportTrash(input, i, output);
			return output;
		}
		else
		{
			short decimalCount = 0;
			while (isdigit(input[i]) || (decimalCount == 0 && input[i] == '.'))
			{
				string val = "";
				while (i < input.length() && (isdigit(input[i]) || (decimalCount == 0 && input[i] == '.')))
				{
					if (input[i] == '.')
					{
						decimalCount++;
					}
					val += input[i];
					if (!isFloat && decimalCount > 0)
					{
						ReportTrash(input, val, i, output);
						return output;
					}
					i++;
				}
				output->push_back(val);

				SkipWhiteSpace(input, i);
			}
		}
		//if there is remaining char(s)
		if (i < input.length())
		{
			//if ends statement with semicolon
			if (input[i] == ';')
			{
				output->push_back(";");
				i++;
			}
			//if doesn't end in a semicolon
			else
			{
				ReportTrash(input, i, output);
				return output;
			}
		}
		else
		{
			ReportTrash(input, -1, output);
			return output;
		}
		//to catch trash chars after final semicolon
		if (i < input.length())
		{
			ReportTrash(input, i, output);
		}
	}
	return output;
}
static void SkipWhiteSpace(string input, unsigned int& i)
{
	while (input[i] == ' ')
	{
		i++;
	}
}
static void ReportTrash(string input, unsigned int i, vector<string>* output)
{
	if (i == -1)
	{
		string trashString = "Error: Entry not terminated with ';'";
		output->push_back(trashString);
	}
	else
	{
		string trashString = "";
		trashString += input[i];
		trashString += " Error: Unrecognizable token";
		output->push_back(trashString);
	}
}
static void ReportTrash(string input, string trash, unsigned int i, vector<string>* output)
{
	trash += " Error: Unrecognizable token";
	output->push_back(trash);
}