/*
A program that reads, sorts and creates a new file for the format:
	index data
	index2 data2
	index3 data3
		- where index is an integer and data is a string
Helps with sorting out a list of numbered data in ALPHABETICAL ORDER, indipendent of the index

EX:
	input.txt:
		1 Zimbabue
		2 Alaska
		3 Poland
	
	output.txt
		2 Alaska
		3 Poland
		1 Zimbabue
		
NOTE : It helped me with a school homework where i had a list of number-ordered countries and I needed the countries in alphabetical order, along with their index */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> 

struct Reading
{
	int index;
	std::string data;
};

class Reading_parser
{
private:
    friend std::istream& operator>> (std::istream& istr, Reading_parser& pr);
    friend std::ostream& operator<< (std::ostream& ostr, Reading_parser& pr);
	std::vector <Reading> readings;

public:
    void sort();
};

std::istream& operator>> (std::istream& istr, Reading& r)
{
	std::string line;
	std::string data;
	char ch;
	std::getline(istr, line);
	std::istringstream istring{ line };

	while (istring.get(ch))
	{
		if (isdigit(ch))
		{
			istring.unget();
			istring >> r.index;
		}
		if (isalpha(ch) || ch == '.' || isspace(ch))
		{
			data += ch;
		}
	}
	r.data = data;
	std::cout << r.index << " " << r.data << std::endl;

	return istr;
}
std::istream& operator>> (std::istream& istr, Reading_parser& pr)
{
	Reading r;
	while (istr >> r)
	{
		pr.readings.push_back(r);
	}
	return istr;
}
bool operator< (Reading a, Reading b)
{
	return a.data < b.data;

}
void Reading_parser::sort()
{
    std::sort(readings.begin(), readings.end());
}

std::ostream& operator<< (std::ostream& ostr, Reading& r)
{
	ostr << r.index << " " << r.data << std::endl;
	return ostr;
}
std::ostream& operator<< (std::ostream& ostr, Reading_parser& pr)
{
	for (Reading r : pr.readings) ostr << r;
	return ostr;
}

int main()
{
	std::ifstream fin{"input.txt"};
	std::ofstream fout{"output.txt"};

	Reading_parser p;
	fin >> p;
    p.sort();
	fout << p;
	return 0;
}