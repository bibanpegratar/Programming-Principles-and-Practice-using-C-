/*
    Simple calculator
            By BIBAN
            part of book material : "Programming Principles and Practice with C++ by Bjarne Stroustrup"

        This program is a part of the mentioned book. Implements a simple calculator
        Input from cin. Output to cout.

            Grammar:
                Calculation:
                    Statement
                    Print
                    Quit
                    Calculation Statement

                Print:
                    print_key (variable)

                Quit
                    quit_key (variable)

                Statement:
                    Declaration
                    Expression
                
                Declaration:
                    "let" variable_name "=" Expression
                
                Expression:
                    Term
                    Expression + Term
                    Expression - Term
                
                Term:
                    Factorial
                    Term * Factorial
                    Term / Factorial
                    Term % Factorial
                
                Factorial:
                    Primary
                    Primary!

                Primary:
                    Number
                    (expression)
                    {expression}
            
            A token a sequence of characters that represents what we consider a unit, such as a number or an operator
                - here, Tokens can be - operators ('+','-','*', which represent themselves (have no value))
                                      - numbers (represented by type '8')
                                      - Variables (a user-type)
                                      - special characters (for qutting, printing the result etc)

            Input comes from cin through the Token_stream called ts.

    Revision history:
        8 nov 2020 - Done chapter 7 in the book
                   - added % (only for integers)
                   - added support for negative numbers
                   - improved "UI"
                   - improved code readablity and modularity
                   - improved error handling
                   - using keep_window_open() function for Windows systems
                   - removed most "magic constants"
                   - added more comments for better explanation

        9 nov 2020 - added variables and constants
                   - program doesn't quit anymore after finding an error

    NOTES:
        Cannnot implement {} fully
            - {} cannot be used inside (), but () can be used inside {}

    TO-DO LIST:
    
*/
#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

//Constant declarations and initializations-------------------------------------
constexpr char number = '8';    //representation of a number type for a Token
constexpr char let = 'L';       //represents the "let" them in declaration()
constexpr char quit_key = 'q';
constexpr char print_key = ';'; 
constexpr char name = 'a';      //name token

const string declkey = "let";   //declaration keyword
const string prompt = ">>";
const string result = "=";      //used to indicate that what follows is a result
const char recover = '~'; //used as an argument for the keep_window_open() functions in catch statements
//------------------------------------------------------------------------------

//Token implementation----------------------------------------------------------
class Token{
    public:
        char type;
        double value;
        string name;   // used for a Token of type name

    Token (char ch):type{ch}, value{0} {};
    Token (char ch, double val):type{ch}, value{val} {};
    Token (char ch, string n) :type{ch}, name{n} {};
};
//-------------------------------------------------------------------------------

//Token_stream implementation----------------------------------------------------
class Token_stream{
    public:
        Token_stream();
        Token get();
        void putback(Token t);
        void ignore(char c);

    private:
        bool isFull = false;
        Token buffer;
};

Token_stream::Token_stream() :isFull(false), buffer(0){}

Token Token_stream::get()
{
    if (isFull)
    {
        isFull = false;
        return buffer;
    }
    else
    {
        char ch;
        cin >> ch;
        switch(ch)
        {
            case '+': 
            case '-':
            case '!': 
            case '*': 
            case '/': 
            case '%':
            case '{': 
            case '}':
            case '(':
            case ')':
            case '=':  //for Variable definition
            case quit_key: 
            case print_key: 
                return Token(ch);

            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9':
                cin.putback(ch);
                double d;
                cin >> d;
                return Token(number,d);

            default:
                //test if the next token is a Variable name and return a Token with that variable
                if (isalpha(ch)) // is ch a letter ?
                { 
                    string s;
                    s += ch;
                    while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+= ch;
                    cin.putback(ch);
                    if (s == declkey) return Token{let};
                    return Token {name,s};  //Token of type name (for Variable) and value s(the name for the Variable)
                }
                runtime_error("Bad token."); 
        }
    }
}

void Token_stream::putback(Token t)
{
    if (isFull) runtime_error("buffer already full");
    isFull = true;
    buffer = t;
}

//Used to recover from errors by ignoring all characters, except char c
void Token_stream::ignore(char c) // c represents the type for the Token
{
    // look in buffer
    if (isFull && c == buffer.type)
    {
        isFull = false;
        return;
    }
    isFull = false;

    //search input
    char ch = 0;
    while (cin >> ch) if (ch == c) return;
}
//-------------------------------------------------------------------------------

//Variable implementation--------------------------------------------------------
class Variable
{
    public:
        string name;
        double value;
};

class Var_Opr 
{
    public:
        double get_value(string s);
        void set_value(string s, double n);
        bool is_declared(string var);
        double define_name(string var, double val);
}
//-------------------------------------------------------------------------------

//Declarations and Initializations-----------------------------------------------
vector <Variable> var_table; // used for storing Variables
Token_stream ts;
void calculate();
double statement();
double declaration();
double expression();
double term();
double factorial();
double secondary();
double primary();
void intro_message();
void cleanup();
//-------------------------------------------------------------------------------

// Handling all errors in calculate(), still handling in main() too, just for an extra layer of security.
//NOTE: If an error somehow reaches main(), the program will be terminated, with a proper error message
int main()
{
    //predifined names
    define_name("pi",3.1415926535);
    define_name("e", 2.7182818284);

    intro_message();
    calculate();
    return 0;
}
/*catch (exception& e){
    cerr << "error: " << e.what() << "\n";
    keep_window_open(keep_window_open_key); //for some Windows environments
    return 1;
}
catch(...){
    cerr << "unhandled error\n";
    keep_window_open(keep_window_open_key); //for some Windows environments
    return 2;
}
*/
//-------------------------------------------------------------------------------

//Grammar implementation---------------------------------------------------------
void calculate()
{
    //double val;
    while(cin)
    try{
        cout << prompt;
        Token t = ts.get();

        while (t.type == print_key) t = ts.get();      // "eat" print_key characters
        if (t.type == quit_key) return;                //NOTE : In void functions, you can do an empty return. 
        
        ts.putback(t);
        cout << result << statement() << "\n\n";
        //val = statement();
    }
    catch (exception& e)
    {
        cerr << "error: " << e.what() << "\n";
        cerr << "Enter " << recover << " to continue.\n";
        cleanup();
    }
}

double statement()
{
    Token t = ts.get();
    switch (t.type)
    {
        case let:
            return declaration();
        default:
            ts.putback(t);
            return expression();
    }
}

double declaration()
{
    // assume we already saw "let" (in statement())
    // handle: name = expression
    // declare a variable called "name" with initial value "expression"

    Token t = ts.get();
    if(t.type != name) error ("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if(t2.type != '=') error("= missing in declaration of ",var_name);

    double d = expression();
    define_name(var_name,d);
    return d;
}

double expression()
{
    double left = term();
    Token t = ts.get();

    while(true)
    {
        switch(t.type)
        {

            case '+':
                left += term();
                t = ts.get();
                break;

            case '-':
                left -= term();
                t = ts.get();
                break;

            default:
                ts.putback(t);
                return left; // if there's no more + and -, return the result
        }
    }
    return left;
}

double term()
{
    double left = factorial();
    Token t = ts.get();

    while(true)
    {
        switch(t.type)
        {
            //ou de paste :)
            case '*':
                left *= factorial();
                t = ts.get();
                break;

            case '/': 
            {
                double d = factorial();
                if(d == 0) error("term: division: cannot divide by 0");
                left /= d;
                t = ts.get();
                break;
            }

            case '%': //Only works for integers
            {

                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(factorial());

                if(i2 == 0) error("term: modulo: cannot divide by 0");

                left = i1 % i2;
                t = ts.get();
                break;
            }

            default:
                ts.putback(t);
                return left;
        }
    }
    return left;
}

double factorial()
{
    double left = primary();
    Token t = ts.get();

    switch(t.type)
    {
        case '!':
        {
            int lcopy = left;
            if (left == 0) return 1; // 0! = 1
            if (left < 0) error ("factorial: cannot calculate factorial of a negative number");
            while (lcopy > 1)
            {
                --lcopy;
                left *= lcopy;
            }
            t = ts.get();
            if (t.type == '!') error ("factorial: unexpected '!' operator");

        }
        default :
            ts.putback(t);
            return left;
    }

    return left;
}

double primary()
{
    Token t = ts.get();

    switch(t.type)
    {
        case '(':
        {
            double e = expression();
            t = ts.get();
            if (t.type != ')') error("primary: ')' expected");
            return e;
        }

        case '{':
        {
            double e = expression();
            Token b = ts.get();
            if (b.type != '}') error("primary: '}' expected");
            return e;
        }
        
        case '-':
            return -primary();
        
        case '+':
            return primary();

        case number:
            return t.value;

        default:
            error("primary expected");
    }
}
//-------------------------------------------------------------------------------

//Additional functions-----------------------------------------------------------
void intro_message() //print a custom "banner"
{  
    cout << "---------------------------------------\n"
         << "|Simple calculator - V0.0.1           |\n"
         << "|                             by BIBAN|\n"
         << "---------------------------------------\n\n"
         << "Please enter expressions using floating\n"
         << "point numbers. +, -, *, /, % (for ints only), (), !-factorial supported.\n"
         << "Use " << quit_key << " to quit the program and " << print_key << " to end an ecuation.\n"
         << "If an error occurs, type in " << recover << " to continue.\n\n";
}

void cleanup(){ //recover from an error
    ts.ignore(recover);
}
//-------------------------------------------------------------------------------

//Variable related functions definitions-----------------------------------------
double Var_opr::get_value(string s)
{
    // return the value of the Variable named s
    for(const Variable& v : var_table)
        if (v.name == s) return v.value;
        
    error("get: undefined variable ", s);
}

void Var_opr::set_value(string s, double n)
{
    // set the variable named s to n
    for(Variable& v : var_table)
        if (v.name == s)
        {
            v.value = n;
            return;
        }
    error("set: undefined variable ", s);
}

bool Var_opr::is_declared(string var)
{
    //is var in var_table already?
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

double Var_opr::define_name(string var, double val)
{
    // add {var,val} to var_table
    if (is_declared(var)) error (var, " declared twice.");
    var_table.push_back(Variable{var,val});
    return val;
}
//-------------------------------------------------------------------------------