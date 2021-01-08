#include "std_lib_facilities.h"
#include "token.h"
#include "constants.h"
#include "romans.h"

using namespace Constants;
Token_stream::Token_stream(istream &istr)
	: isFull{false}, buffer{0}, istr_p{istr} {};

Token Token_stream::get()
{
	if (isFull)
	{
		isFull = false;
		return buffer;
	}
	else
	{
		char ch;
		istr_p >> ch;
		switch (ch)
		{
		case '+':
		case '-':
		case '!':
		case '*':
		case '/':
		case '%':
		case '{':
		case '}':
		case '(':
		case ')':
		case '=': //for Variable declaration and assignment
		case ',': //used for separating arguments in functions
		case quit_key:
		case print_key:
		case help_key:
		case show_vars:
			return Token(ch);

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			istr_p.putback(ch);
			double d;
			istr_p >> d;
			return Token(number, d);
		}

		case 'I':
		case 'V':
		case 'X':
		case 'L':
		case 'C':
		case 'D':
		case 'M':
		{
			istr_p.putback(ch);
			Roman::Roman r;
			istr_p >> r;
			return Token(number, r.interger);
		}

		default:
			//test if the next token is a string and return a Token if it's valid
			if (isalpha(ch)) // is ch a letter ?
			{
				string s;
				s += ch;
				while (istr_p.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
					s += ch;

				istr_p.putback(ch);

				if (s == decl_key)
					return Token{let};
				if (s == sroot_key)
					return Token{sroot};
				if (s == power_key)
					return Token{power};
				if (s == constant_key)
					return Token{vconst};
				if (s == prow_key)
					return Token{prow};

				return Token{name, s}; //Token of type name (for Variable) and value s(the name for the Variable)
			}
			runtime_error("Bad token.");
		}
	}
}

void Token_stream::putback(Token t)
{
	if (isFull)
		runtime_error("buffer already full");
	isFull = true;
	buffer = t;
}

//Used to recover from errors by ignoring all characters, except char c
void Token_stream::ignore(char c) // c represents the type for the Token
{
	// look in buffer
	if (isFull && c == buffer.type)
	{
		isFull = false;
		return;
	}
	isFull = false;

	//search input
	char ch = 0;
	while (istr_p >> ch)
		if (ch == c)
			return;
}
//-------------------------------------------------------------------------------