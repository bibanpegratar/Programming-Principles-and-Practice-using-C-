#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"
//using while
int main()
{
  char i = 'a';
  while (i <= 'z'){
    cout << i << " " << int(i) << "\n";
    ++i;
  }
  return 0;
}

//using for
#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main()
{
  char i = 'a';
  for (i = 'a'; i <= 'z'; i++){
    cout << i << " " << int(i) << "\n";
  }
  return 0;
}
