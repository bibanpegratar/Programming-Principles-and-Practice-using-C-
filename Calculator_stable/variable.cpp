#include "std_lib_facilities.h"
#include "variable.h"

double Symbol_table::get_value(string s)
{
	// return the value of the Variable named s
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;

	error("get: undefined variable ", s);
}

void Symbol_table::set_value(string s, double n)
{
	// set the variable named s to n
	for (Variable& v : var_table)
	{
		if (v.name == s && v.isConst == false)
		{
			v.value = n; //ARE YOU A ONE OR A ZERO?
			return;
		}
		else if (v.name == s && v.isConst) error("set_value: cannot change value of a constant variable");
	}
	error("set: undefined variable ", s);
}

bool Symbol_table::is_declared(string var)
{
	//is var in var_table already?
	for (const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}

double Symbol_table::define_variable(string var, double val, bool isConst)
{
	// add {var,val,isConst} to var_table
	if (is_declared(var)) error(var, " declared twice.");
	var_table.push_back(Variable{ var,val,isConst });
	return val;
}

void Symbol_table::show_variables(ostream& ostr)
{
	for (int i = 0; i < var_table.size(); ++i)
		ostr << var_table[i].name << " = " << var_table[i].value << "\n";
}
