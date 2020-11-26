#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"
#include "calculator.h"

//NOTE: The Token_stream works with files, but not fully:
	//it reads from them, does the correct calculations, but then crashes with a a core dump error, double free or corruption (out)
ifstream istr;
ofstream ostr;

Token_stream ts(istr);
Symbol_table st;
void initialize_custom_variables();

int main()
{
	istr.open("input.txt");
	ostr.open("output.txt");
	initialize_custom_variables();
	intro_message(cout);
	calculate(ts, st, ostr);
	istr.close();
	return 0;
}

void initialize_custom_variables()
{
	st.define_variable("pi", 3.14159, true);
	st.define_variable("e",2.71828 , true);
}