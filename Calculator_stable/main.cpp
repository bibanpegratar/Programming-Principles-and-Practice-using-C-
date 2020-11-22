#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"
#include "calculator.h"

Token_stream ts;
Symbol_table st;
void initialize_custom_variables();

int main()
{
	initialize_custom_variables();
	intro_message();
	calculate(ts, st);
	return 0;
}

void initialize_custom_variables()
{
	st.define_variable("pi", 3.14159, true);
	st.define_variable("e",2.71828 , true);
}