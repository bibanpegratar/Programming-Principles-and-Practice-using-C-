#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

struct Field
{
	int width;
	std::string field;
};

class Table
{
public:
	Table (std::vector <Field>& v);
	void add_entry (std::vector <std::string> values);
	std::vector <Field> first_row;
	std::vector <std::vector <Field>> entries;
};

std::ostream& operator<<(std::ostream& ost, const Table& t)
{
	for(Field f : t.first_row)
		ost << '|' << std::setw(f.width) << f.field;
	ost << "|\n";
    
    int ionel = 0;
    for (Field f : t.first_row) ionel += f.width;
    ionel += t.first_row.size() + 1;
    for (int i = 0; i < ionel; i++) ost << '-';
	ost << '\n';

	for (const std::vector <Field>& f : t.entries)
	{
		for (Field field: f)
			ost << '|' << std::setw(field.width) << field.field;
		ost << "|\n";
	}
	return ost;
}

Table::Table (std::vector <Field>& v)
	:first_row{v}
	{};

void Table::add_entry (std::vector <std::string> values)
{
	if (values.size() > first_row.size()) throw std::runtime_error("too many values provided");
	std::vector <Field> e;
	for (int i = 0; i < first_row.size(); i++)
		e.push_back({first_row[i].width, values[i]});

	entries.push_back(e);
}

Field lname {15, "Last Name"};
Field fname {15, "First Name"};
Field phone {10, "Phone"};
Field email {35, "Email"};

static std::vector <Field> first_row {lname, fname, phone, email};
Table t (first_row);


int main()
{
	t.add_entry({"Alex", "Ivan" , "0141551124", "asfefaefaef@gmail.com"});
	t.add_entry({"Marcel Ionel", "Costel" , "0141551434", "fefefwefwgqg@gmail.com"});
	std::cout << t;
}

