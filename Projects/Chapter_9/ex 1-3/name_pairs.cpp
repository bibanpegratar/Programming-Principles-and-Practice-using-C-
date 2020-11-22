#include "name_pairs.h"

Name_age::Name_age(string nn)
	: n{ nn }, a{ 0 }, has_Age{ false }
{
}

Name_age::Name_age(string nn, int aa)
	: n{ nn }, a{ aa }, has_Age{ true }
{
}

void Name_pairs::add_name()
//Input names followed by , and end the i
{
	char ch;
	string name;
	while (true)
	{
		cin >> ch;
		switch (ch)
		{
		case Keycodes::end_of_input :
			if (name != "") na.push_back({ name });
			name = "";
			return;

		case Keycodes::end_of_value :
			if (name != "") na.push_back({ name });
			name = "";
			break;

		default:
			if (isalpha(ch))
			{
				name += ch;
			}
			else throw runtime_error("invalid name");
			break;
		}
	}
}

void Name_pairs::add_age() 
// add age value for each Name_age object in vector that doesn't have one ( has_age == false )
{
	int age;
	for (int i = 0; i < na.size(); i++)
	{
		cout << na[i].name() << ": ";
		cin >> age;
		na[i].add_age(age);
	}
}

ostream& operator<<(ostream& os, const Name_pairs& np)
{
	for (int i = 0; i < np.size(); i++)
	{
		os << "Name: " << np.name(i) << ", Age: " << np.age(i) <<"\n";
	}
	return os;
}

bool operator<(const Name_age& a, const Name_age& b)// a Name_age pair is ordered by name
{
	return a.name() < b.name();
}