#pragma once
#include "std_lib_facilities.h"

//Variable implementation--------------------------------------------------------
class Variable
{
public:
	std::string name;
	double value;
	bool isConst;

	Variable(std::string st, double v, bool b) : name{ st }, value{ v }, isConst{ b } {}
	Variable(std::string st, double v) : name{ st }, value{ v }, isConst{ false } {}
};

class Symbol_table
{
public:
	double get_value(std::string s);
	void set_value(std::string s, double n);
	bool is_declared(std::string var);
	double define_variable(std::string var, double val, bool isConst);
	void show_variables();

private:
	vector <Variable> var_table;
};