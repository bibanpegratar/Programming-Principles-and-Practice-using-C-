#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main()
{
  int a,b;
  double c,d;
  cin >> a >> b;

  a = double(a); // this will still be an int, as a and b are ints, so the double() function narrows its value
  b = double(b);

  c = double(a); // this is OK, c and d are doubles
  d = double(b);

  cout << a / b << "\n"; // this will be an int operation
  cout << c / d << "\n"; // this will be a floating point operation

  return 0;
}
