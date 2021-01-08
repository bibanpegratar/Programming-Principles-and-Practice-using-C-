#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"
#include "constants.h"
#include "calculator.h"

//Grammar implementation---------------------------------------------------------
using namespace Constants;

void calculate(Token_stream& ts, Symbol_table& st, ostream& ostr)
{
	//double val;
	while (true)
		try {
		ostr << prompt;
		Token t = ts.get();

		while (t.type == print_key) t = ts.get();      // "eat" print_key characters
		if (t.type == quit_key) return;                //NOTE : In void functions, you can do an empty return. 
		if (t.type == help_key) intro_message(ostr);
		if (t.type == show_vars) st.show_variables(ostr);
		else {
			ts.putback(t);
			ostr << result << statement(ts, st) << "\n\n";
		}

		//ts.putback(t);
		//cout << result << statement() << "\n\n";
		//val = statement();
	}
	catch (exception& e)
	{
		cout.clear();
		cerr << "error: " << e.what() << "\n";
		cerr << "Enter " << recover << " to continue.\n";
		cleanup (ts);
	}
	catch (...)
	{
		cerr << "Unknown error.\n";
		cerr << "Enter " << recover << " to continue.\n";
	}
}

double statement(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	switch (t.type)  //HELLO, FRIEND.
	{
	case let:
		return declaration(ts, st);

	default:
		ts.putback(t);
		return expression(ts, st);
	}
}

double declaration(Token_stream& ts, Symbol_table& st)
{
	// assume we already saw "let" (in statement())
	// handle: name = expression
	// declare a variable called "name" with initial value "expression"

	Token t = ts.get();
	bool isConst = false;
	if (t.type == vconst)
	{
		t = ts.get();
		isConst = true;
		if (t.type != name) error("name expected in declaration");
		string var_name = t.name;
	}

	else if (t.type != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.type != '=') error("= missing in declaration of ", var_name);

	double d = expression(ts, st);
	st.define_variable(var_name, d, isConst);
	return d;
}

double square_root(Token_stream& ts, Symbol_table& st)
{
	// get a token, assuming that we've already used the string "sqrt" in get()
	Token t = ts.get();
	if (t.type != '(') error("sqrt: '(' expected");
	double e = expression(ts, st);
	if (e < 0) error("sqrt: cannot calculate square root of negative number");

	t = ts.get();
	if (t.type != ')') error("sqrt: ')' expected");
	return sqrt(e);
}

double powerf(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();
	if (t.type != '(') error("power: '(' expected");

	double t1 = expression(ts, st);

	t = ts.get();
	if (t.type != ',') error("power: arguments must be separated by a ','");

	double t2 = expression(ts, st);
	if (t2 < 0) error("power: negative exponent");

	t = ts.get();
	if (t.type != ')') error("power: ')' expected");
	return pow(t1, t2);
}

double expression(Token_stream& ts, Symbol_table& st)
{
	double left = term(ts, st);
	Token t = ts.get();

	while (true)
	{
		switch (t.type)
		{

		case '+':
			left += term(ts, st);
			t = ts.get();
			break;

		case '-':
			left -= term(ts, st);
			t = ts.get();
			break;

		default:
			ts.putback(t);
			return left; // if there's no more + and -, return the result
		}
	}
	return left;
}

double term(Token_stream& ts, Symbol_table& st)
{
	double left = factorial(ts, st);
	Token t = ts.get();

	while (true)
	{
		switch (t.type)
		{
			//ou de paste :)
		case '*':
			left *= factorial(ts, st);
			t = ts.get();
			break;

		case '/':
		{
			double d = factorial(ts, st);
			if (d == 0) error("term: division: cannot divide by 0");
			left /= d;
			t = ts.get();
			break;
		}

		case '%': //Only works for integers
		{

			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(factorial(ts, st));

			if (i2 == 0) error("term: modulo: cannot divide by 0");

			left = i1 % i2;
			t = ts.get();
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
	return left;
}

double factorial(Token_stream& ts, Symbol_table& st)
{
	double left = primary(ts, st);
	Token t = ts.get();

	switch (t.type)
	{
	case '!':
	{
		int lcopy = narrow_cast<int>(left);
		if (left == 0) return 1; // 0! = 1
		if (left < 0) error("factorial: cannot calculate factorial of a negative number");
		while (lcopy > 1)
		{
			--lcopy;
			left *= lcopy;
		}
		t = ts.get();
		if (t.type == '!') error("factorial: unexpected '!' operator");

	}
	default:
		ts.putback(t);
		return left;
	}

	return left;
}

double primary(Token_stream& ts, Symbol_table& st)
{
	Token t = ts.get();

	switch (t.type)
	{
	case '(':
	{
		double e = expression(ts, st);
		t = ts.get();
		if (t.type != ')') error("primary: ')' expected");
		return e;
	}

	case '{':
	{
		double e = expression(ts, st);
		Token b = ts.get();
		if (b.type != '}') error("primary: '}' expected");
		return e;
	}

	case '-':
		return -primary(ts, st);

	case '+':
		return primary(ts, st);

	case number:
		return t.value;

	case name:
		ts.putback(t);
		return variable(ts, st);

	case power:
		return powerf(ts, st);

	case sroot:
		return square_root(ts, st);

	default:
		error("primary expexted");
	}
}

double variable(Token_stream& ts, Symbol_table& st) {
	Token t = ts.get();
	switch (t.type)
	{
	case name:
	{
		Token t2 = t;
		t = ts.get();
		// check to see if it's an assignment or just a usage of the variable
		if (t.type == '=')
		{
			double e = expression(ts, st);
			st.set_value(t2.name, e);
			return e;
		}
		else
		{
			ts.putback(t);
			return st.get_value(t2.name);
		}
	}
	}
}
//-------------------------------------------------------------------------------

//Additional functions-----------------------------------------------------------
void intro_message(ostream& ostr) //print a custom "banner"
{
	ostr<< "--------------------------------------\n"
		<< "|Simple calculator - V1.1             |\n"
		<< "|                             by BIBAN|\n"
		<< "---------------------------------------\n\n"
		<< "Supported operators : +, -, *, /, % (for ints only), (), !-factorial\n"
		<< "Supported functions :\n"
		<< "   - sqrt(expression) - calculates square root of any expression\n"
		<< "   - pow(base, exponent) - calculate a base at the power of exponent\n"
		<< "      --> base and exponent are expressions\n\n"
		<< "Variables can be defined and used as expressions:\n"
		<< "   - let variable_name = value - define a variable\n"
		<< "   - let const constant_name = value - define a constant\n"
		<< "   - variable_name = new_value - assign a new value to a non-constant variable\n"
		<< "   - " << show_vars << " - display all variables\n\n"
		<< "Use " << quit_key << " to quit the program, " << print_key << " to end an ecuation and " << help_key << " to display this message.\n"
		<< "If an error occurs, type in " << recover << " to continue.\n"
		<< "!!!!! WARNING : Do not forget to add the quit program key (" << quit_key << ") at the end of the input file. !!!!!\n\n";
}

void cleanup(Token_stream& ts)
{ //recover from an error
	ts.ignore(recover);
}
//-------------------------------------------------------------------------------