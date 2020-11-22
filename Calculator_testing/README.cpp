/*
	Simple calculator - v1.1.01 - testing branch
			By BIBAN
			part of book material : "Programming Principles and Practice with C++ by Bjarne Stroustrup"

		This program is a part of the mentioned book. Implements a simple calculator
		Input from cin. Output to cout.

			Grammar:
				Calculation:
					Statement
					Print
					Quit
					Help
					Calculation Statement

				Print:
					print_key (variable)

				Quit
					quit_key (variable)

				Help
					help_key (variable)

				Statement:
					Declaration
					Expression

				Declaration:
					"let" variable_name "=" Expression

				Expression:
					Term
					Expression + Term
					Expression - Term

				Term:
					Factorial
					Term * Factorial
					Term / Factorial
					Term % Factorial

				Factorial:
					Primary
					Primary!

				Primary:
					Number
					Variable
					(expression)
					{expression}
					sqrt(expression)
					pow(expression, expression)

			A token a sequence of characters that represents what we consider a unit, such as a number or an operator
				- here, Tokens can be - operators ('+','-','*', which represent themselves (have no value))
									  - numbers (represented by type '8')
									  - Variables (a user-type)
									  - special characters (for qutting, printing the result etc)

			Input comes from cin through the Token_stream called ts.

	Revision history:
		8 nov 2020 - Done chapter 7 in the book
				   - added % (only for integers)
				   - added support for negative numbers
				   - improved "UI"
				   - improved code readablity and modularity
				   - improved error handling
				   - using keep_window_open() function for Windows systems
				   - removed most "magic constants"
				   - added more comments for better explanation

		9 nov 2020 - added variables and constants
				   - program doesn't quit anymore after finding an error

		12 nov 2020 - added sqrt() and pow() functions
					- variable names can now contain '_' (underscores)
					- variables can now be used in expressions
					- variables can now either be constant or variable
					- added the ability to use functions within expressions - pow(2,3) + 5 = 13
						-- kinda implemented, but the functions are at the same level with a primary

		13 nov 2020 - added ability to display all variables
					- removed some bugs
					- modified grammar functions to use the Token_stream as a pass-by-reference

		17 nov 2020 - restructured the code using headers and source files
						- still not perfect, but it's better
						- compilation times got larger, but I prefer this over less structured code
						- found a problem with the Vector defined in std_lib_facilities.h provided by Bjarne Stroustup
					- introduced another Token_stream that uses a reference to an istream; I don't know how that's gonna work (yet)

	NOTES:
		Cannnot implement {} fully
			- {} cannot be used inside (), but () can be used inside {}

	KNOWN BUGS:
		- if a variable name begins with a character (letter) that is used for quitting, display help message or print result, the program will display a variable definition error.

*/