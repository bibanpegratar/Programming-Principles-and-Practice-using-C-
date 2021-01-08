/* Se citesc n, număr natural nenul, n<=100 și n numere naturale, elemente ale unui tablou unidimensional a. Să se construiască tabloul unidimensional b în care b[i] este egal cu restul împărțirii lui a[i] 
la suma cifrelor lui a[i]. În fișierul date.txt se vor scrie, pe prima linie, în ordine, elementele tabloului a, separate prin câte un spațiu, iar pe a doua linie elementele tabloului b, separate prin câte un spațiu.

Exemplu:
pentru
     n=5 și 
     a: 27   316   96   1205   78

fișierul date.txt are următorul conținut:
    27   316   96   1205   78
    0   6   6   5   3 */

#include <iostream>
#include <fstream>

int main()
{
	int n;
	std::cin >> n;
	int* a = new int[n];
	int* b = new int[n];

	for (int i = 0; i < n; i++)
		std::cin >> a[i];

	for (int i = 0; i < n; i++)
	{
		int nr = a[i];
		int sum = 0;
		while(nr > 0)
		{
			sum += nr % 10;
			nr /= 10;
		}
		b[i] = a[i] % sum;
	} 

	std::ofstream fout {"date.txt"};

	for (int i = 0; i < n; i++)
	{
		fout << a[i] << " " << b[i] <<"\n";
	}

	delete[] a;
	delete[] b;
	return 0;
}