#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

constexpr double kelvin_conversion = 273.15;

double celsius_to_kelvin(double t, char unit){
  // The temperature in kelvin should be bigger than 0.
  switch(unit){
    case 'k': case 'K':
      if (t <= 0) throw runtime_error("Temperature bellow absloute 0.\n");
      return t - kelvin_conversion;

    case 'c': case 'C':
      if (t + kelvin_conversion <= 0) throw runtime_error("Temperature bellow absloute 0.");
      return t + kelvin_conversion;

    default:
      throw runtime_error("Unknown unit.");
  }
}

int main()
try{
  double t = 0;
  double converted = 0;
  char unit;

  cout << ">> Enter a temperature, followed by a unit: C(celsius) or K(kelvin).\n>> ";
  cin >> t >> unit;
  if (!cin) throw runtime_error("Provided value not a number.\n");
  converted = celsius_to_kelvin(t, unit);
  cout << ">> Temperature : " << converted << "\n";
  return 0;
}

catch(runtime_error& e){
  cerr << "error: " << e.what();
  return 1;
}
catch(...){
  cerr << "Unknown error.\n";
  return 1;
}