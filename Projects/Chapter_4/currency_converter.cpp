#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

constexpr double yen_conversion = 0.0095661;
constexpr double kroner_conversion = 0.108633;
constexpr double pounds_conversion = 1.291574;

double convert_to_dollars(char currency, double dollars){
  switch (currency){
    case 'y': case 'Y':
      return dollars * yen_conversion;

    case 'k': case 'K':
      return dollars * kroner_conversion;

    case 'p': case 'P':
      return dollars * pounds_conversion;

    default:
      simple_error("Unknown currency.");
      return 0;
  }
}

int main()
{
  double money = 0;
  char currency;
  cout << ">> Input an amount of money in dollars : ";
  cin >> money;
  cout << ">> Choose currency to convert to:\n"
       << "y - yen\n" << "k - kroner\n" << "p - pounds\n"
       << ">> ";
  cin >> currency;
  cout << "Converted : " << convert_to_dollars(currency, money) << " " << currency << "\n";
}
