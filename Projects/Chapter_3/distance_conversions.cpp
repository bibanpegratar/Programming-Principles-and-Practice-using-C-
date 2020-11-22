#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main()
{
  double kg_to_lbs = 2.2046226218488;
  double lbs_to_kg = 0.45359237;

  char unit;
  float weight;

  cout << ">> Choose unit : kilograms (k) or lbs(l). \n>> ";
  cin >> unit;
  cout << "Input your weight :\n>> "; // cout with no modifications can only display 6 digits
  cin >> weight;

  if(unit == 'l' || unit == 'L')
  {
    weight *= lbs_to_kg;
    cout << ">> Converted weight : " << weight << " kg.\n";
  }
  else if (unit =='k' || unit == 'K')
  {
    weight *= kg_to_lbs;
    cout << ">> Converted weight : " << weight << " lbs.\n";
  }
  else simple_error("Unknown unit.");

  return 0;
}
