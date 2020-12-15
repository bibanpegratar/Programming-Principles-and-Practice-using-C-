#include <iostream>

void print_array (std::ostream& ostr, char* a)
{
	for (int i = 0; a[i] != 0; i++) ostr << a[i];
}

void to_lower(char *s)
{
	int dif;
	for (int i = 0; s[i] != 0; i++)
	{
		dif = s[i] - 'a'; //difference between the letter and the smallest letter
		if( dif <= -7 && dif >= -32) // there's a difference of 7 between the last capital letter and first small letter
            s[i] = s[i] + 32; // 32 is the difference between a capital and small letter (AHCII)
	}
}

int main()
{
	char ll[] {"J K Rowling"};
	to_lower(ll);
	print_array(std::cout, ll);

}