#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

//Later, try rewriting this using the calculator code. Try and write multiple ways of getting input ( from files, from vectors etc ). 
//All these methods could call the get(char c) method that will return a token depending on input.
//This will allow code modularity and reusage
//For now, the Permutation, Combination and factorial operations will be hard-coded.

int factorial (int n);
int permutations (int a, int b);
int combinations (int a, int b);
constexpr char quit_char = 'e';

int main()
try{
    int a,b;
    char opr;
    cout << "--------------------------------------\n"
        << "|Permutations                         |\n"
        << "|                             by BIBAN|\n"
        << "---------------------------------------\n\n"
        << "Enter 2 numbers:\n"
        << "    - number of numbers to use for combinations\n"
        << "    - number of numbers per combination\n"
        << "then select the operation : c (combinations) or p (permutations)"
        << "Use '" << quit_char << "' to quit.\n";

    while (true){
        cout << "\n";
        cout << ">> Number of possible numbers : ";
        cin >> a;
        if (!cin) error("cannot read number");

        cout << ">> Numbers per combination : ";
        cin >> b;
        if (!cin) error("cannot read number");
    
        cout << ">> Choose operation : c (Combinations) or p (permutations) : ";
        cin >> opr;

        switch (opr){
            case 'c': case 'C':
                cout << ">> Maximum combinations: " << combinations(a,b) << "\n";
                break;

            case 'p': case 'P':
                cout << ">> Maximum permutations: " << permutations(a,b) << "\n";
                break;

            case quit_char: 
                return 0;

            default :
                error("unknown character");
        }

    }
    return 0;
}
catch(exception& e){
    cerr << "error: " << e.what() << "\n";
    return 69;
}
catch(...){
    cerr << "unknown error";
    return 69;
}

int factorial(int n){
    if (n < 0) error ("factorial parameter can't be smaller than 0");
    int copy = n;
    while (copy > 1){
        copy--;
        n *= copy;
    }
    return n;
}

int permutations (int a, int b){
    if (a <=0 || b <= 0) error("invalid number. Must be > 0");
    return factorial(a) / factorial(a-b);
}

int combinations (int a, int b){
    if (a <=0 || b <= 0) error("invalid number. Must be > 0");
    return permutations(a,b) / factorial(b);
}