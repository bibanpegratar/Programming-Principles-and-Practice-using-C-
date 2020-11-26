#include "std_lib_facilities.h"
#include "keycodes.h"
class Name_age
{
public:
	Name_age(string nn);
	Name_age(string nn, int aa);

	string name() const { return n; }
	int age() const { return a; }
	bool has_age() const { return has_Age; }
	void add_age(int aa) { a = aa; }

private:
	string n; //name
	int a; //age
	bool has_Age;
};

class Name_pairs
{
public:
	void add_name();
	void add_age();
	void sort_v() { sort(na); }
	int size() const { return na.size(); }
	string name(int index) const { return na[index].name(); }
	int age(int index) const { return na[index].age(); }

private:
	vector <Name_age> na;
};

ostream& operator<<(ostream& os, const Name_pairs& np);
bool operator<(const Name_age& a, const Name_age& b); //overloaded comparison operator for sort() function usage