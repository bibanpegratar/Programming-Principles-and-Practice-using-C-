#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

int main()
{
	int digit_count = 0;
	std::string f;
	std::cin >> f;
	for(char ch : f) if(isdigit(ch)) digit_count++;
       	std::cout << digit_count;	
}
