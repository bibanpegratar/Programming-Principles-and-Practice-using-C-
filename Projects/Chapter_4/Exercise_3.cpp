#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main(){
  vector <int> numbers;
  int n, median;

  while (cin >> n) numbers.push_back(n);
  sort(numbers);

  if (numbers.size() % 2 == 0)
    median = (numbers[numbers.size()/2-1] + numbers[numbers.size()/2]) / 2;
  else median = numbers[numbers.size()/2];

  for(int number : numbers) cout << number << " ";

  cout << "Median : " << median << "\n";
  return 0;
}
