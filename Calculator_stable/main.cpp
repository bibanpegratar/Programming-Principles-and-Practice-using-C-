#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"
#include "calculator.h"

//NOTE: The Token_stream works with files, but not fully:
	//it reads from them, does the correct calculations, but then crashes with a a core dump error, double free or corruption (out)



Symbol_table st;
void initialize_custom_variables();

int main()
try{
	intro_message(cout);
	initialize_custom_variables();
	string choice;
	cout << "Choose where you want to give input from - keyboard or file:\n";
	cin >> choice;

	if(choice == "file")
	{
		string input_file, output_file;
		cout << "Enter the whole name of the input file : ";
		cin >> input_file;
		cout << "Enter the whole name of the output file : ";
		cin >> output_file;

		ifstream istr {input_file};
		ofstream ostr {output_file};
		Token_stream ts(istr);

		calculate(ts, st, ostr);

	}
	else if (choice == "keyboard")
	{
		Token_stream ts(cin); // console input
		calculate(ts, st, cout); // console output
	}
	else throw runtime_error("invalid choice");
	return 0;
}
catch(runtime_error& e)
{
	cerr << "error: main(): " << e.what() << "\n";
	return 1;
}
catch(...)
{
	cerr << "unhandled error\n";
	return 2;
}

void initialize_custom_variables()
{
	st.define_variable("pi", 3.14159, true);
	st.define_variable("e",2.71828 , true);
}