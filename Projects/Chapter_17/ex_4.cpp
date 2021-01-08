#include <iostream>

void print_array (std::ostream& ostr, const char* a)
{
	for (int i = 0; a[i] != 0; i++) ostr << a[i];
}

char* strdup(const char* c)
{
	int len = 0;
	while (c[len]!=0) len++;
	char* ch = new char[len];
	for (int i = 0; i < len; i++) ch[i] = c[i];
	return ch;
}
int main()
{
	const char* name = strdup("name");
	//delete[] name;
	print_array(std::cout, name);
	return 0;
}