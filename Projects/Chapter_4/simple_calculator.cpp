#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

// The user inputs 2 doubles and an operator

double calculate (double a, double b, char oper){
    switch(oper){
      case '+':
        return a + b;
      case '-':
        return a - b;
      case ':': case '/':
        return a / b;
      case '*': case 'x':
        return a * b;
      default :
        simple_error("Unknown operator.");
        return 0;
    }
}

int main(){
  double a,b;
  char oper;

  cout << ">> Enter 2 numbers with an operator between : 2 + 2\n";
  cout << ">> CTRL + C to exit.\n";
  while(cin >> a >> oper >> b){
      cout << a << " " << oper << " " <<  b << " = " << calculate(a, b, oper) << "\n";
  }

  return 0;
}
