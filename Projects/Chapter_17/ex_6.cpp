#include <iostream>

void crash_computer(int speed)
//a simple funtion that will allocate memory on the free store untill there's no more memory
//shows what leaks can do to programs that have to run indefinitely
//if speed is set very high, it will allocate a lot of memory at once ==> BE AWARE that the computer might run out of memory real fast! stay close to CTRL+C
{
	int* arr = new int[speed];
	while(true)
	{
		arr = new int[speed];
	}
}

int main()
{
	//Iunno, just having fun :)))
	crash_computer(10000);
	return 0;
}