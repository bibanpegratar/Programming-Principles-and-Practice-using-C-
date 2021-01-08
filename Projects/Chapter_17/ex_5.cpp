#include <iostream>

char* findx(const char* s, char* x)
//find the first occurance of x in C-style string s
{
	int len_x = 0;
	int len_found = 0;
	for (int i = 0; x[i]!=0; i++) len_x++;
	for (int i = 0; s[i]!=0; i++)
	{
		if(s[i] == *x)
		{
			for (int j = 0; x[j]!=0; j++)
			{
				if (x[j] == s[i]) 
				{
					i++;
					len_found++;
				}
				else break;
			}
			if(len_found == len_x) return x;
			len_found = 0;
		}
	}
	return nullptr;
}

int main()
{
	
/* 	std::ifstream ifst {"~/input.txt"};
	if(!ifst) throw std::runtime_error("cant open input file");

	int i = 0;
	char ch;
	for(i = 0; ifst >> ch; i++) {}

	char* string = new char[i];
	ifst.clear();
	ifst.seekg(0);

	for (i = 0; ifst >> ch; i++) string[i] = ch;  */

	char* name = findx("Yamaha YBR is a great bike.", "YBR");
	//delete[] string;
	print_array(std::cout,name);
	return 0;
}