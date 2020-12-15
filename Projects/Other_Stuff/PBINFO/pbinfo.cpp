//Se citesc două numere naturale n m cu exact două cifre fiecare. Să se decidă dacă cele două numere au cifre comune.

#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main()
{
  int n,m;
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

  cin >> n >> m;
  if (n > 99 || n < 0 || m > 99 || m < 0) return 0;

  a = n % 10;
  b = n / 10;

  c = m % 10;
  d = m / 10;

  if (a == c || a == d || b == c || b == d){
    cout << "Numerele au cifre comune.\n";
  }
  else cout << "Numerele nu au cifre comune.\n";
  return 0;
}
