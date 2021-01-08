#include <iostream>

char* increase_array(char* arr, char ch)
//increase the size of arr with one and add ch to the end
{
	//get the size of arr
	int arr_size = 0;
	
	for (arr_size = 0; arr[arr_size]!= 0; arr_size++) {};
	std::cout << arr_size;

	char* n_arr = new char[arr_size+1]; // make space for ch and the 0 terminator
	
	//copy all chars from arr to n_arr
	for (int i = 0; i < arr_size; i++)
		n_arr[i] = arr[i];

	n_arr[arr_size] = ch; //put ch at the end of the new array
	//n_arr[arr_size+1] = 0; //add the terminator 0 specific for the C-type strings

	arr = new char [arr_size+1]; //create a new arr same size as n_arr

	//"fill" arr with characters from n_arr
	for(int i = 0; i < arr_size+1; i++)
	{
		arr[i] = n_arr[i];
	}
	//arr[arr_size] = 0; //add the terminator 0 specific for the C-type strings
	delete[] n_arr;
	return arr;
}

char* read_from_cin(char* arr)
{
	char ch;
	while (std::cin.get(ch))
	{
		if (ch == '!') return arr;

		arr = increase_array(arr,ch);
	}
	return arr;
}

int main()
{
	char* str = new char;
	str = read_from_cin(str);
	print_array(std::cout, str);
	std::cout << i;
	return 0;
}