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
                    Help
                    Calculation Statement

                Print:
                    print_key (variable)

                Quit
                    quit_key (variable)
                
                Help
                    help_key (variable)

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
                    Variable
                    (expression)
                    {expression}
                    sqrt(expression)
                    pow(expression, expression)
            
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
        
        12 nov 2020 - added sqrt() and pow() functions
                    - variable names can now contain '_' (underscores)
                    - variables can now be used in expressions
                    - variables can now either be constant or variable
                    - added the ability to use functions within expressions - pow(2,3) + 5 = 13
                        -- kinda implemented, but the functions are at the same level with a primary
        
        13 nov 2020 - added ability to display all variables
                    - removed some bugs
                    - modified grammar functions to use the Token_stream as a pass-by-reference

    NOTES:
        Cannnot implement {} fully
            - {} cannot be used inside (), but () can be used inside {}

    KNOWN BUGS:
        - if a variable name begins with a character (letter) that is used for quitting, display help message or print result, the program will display a variable definition error.
    
*/
#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

//Constant declarations and initializations-------------------------------------
constexpr char number = '8';    //representation of a number type for a Token
constexpr char sroot = 'S';
constexpr char let = 'L';       //represents the "let" term in declaration()
constexpr char name = 'a';      //name token
constexpr char power = 'P';
constexpr char vconst = 'C';


const string decl_key = "let";   //declaration keyword
const string sroot_key = "sqrt";    //keyword for calling sqare_root() function
const string power_key = "pow";     //keyword for calling power() function
const string constant_key = "const";

constexpr char quit_key = '@';
constexpr char print_key = ';';
constexpr char help_key = '$';
constexpr char show_vars = '&';

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
            case '=':  //for Variable declaration and assignment
            case ',':  //used for separating arguments in functions
            case quit_key: 
            case print_key: 
            case help_key:
            case show_vars:
                return Token(ch);

            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9':
                cin.putback(ch);
                double d;
                cin >> d;
                return Token(number,d);

            default:
                //test if the next token is a string and return a Token if it's valid
                if (isalpha(ch)) // is ch a letter ?
                { 
                    string s;
                    s += ch;
                    while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s+= ch;

                    cin.putback(ch);

                    if (s == decl_key) return Token{let};
                    if (s == sroot_key) return Token{sroot};
                    if (s == power_key) return Token{power};
                    if (s == constant_key) return Token{vconst};

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
        bool isConst;

        Variable (string st, double v, bool b): name{st}, value{v}, isConst{b} {}
        Variable (string st, double v): name{st}, value{v}, isConst{false} {}
};

class Symbol_table
{
    public:
        double get_value(string s);
        void set_value(string s, double n);
        bool is_declared(string var);
        double define_variable(string var, double val, bool isConst);
        void show_variables();

    private:
        vector <Variable> var_table;
};

double Symbol_table::get_value(string s)
{
    // return the value of the Variable named s
    for(const Variable& v : var_table)
        if (v.name == s) return v.value;

    error("get: undefined variable ", s);
}

void Symbol_table::set_value(string s, double n)
{
    // set the variable named s to n
    for(Variable& v : var_table)
    {
        if (v.name == s && v.isConst == false)
        {   
            v.value = n;
            return;
        }
        else if (v.name == s && v.isConst) error("set_value: cannot change value of a constant variable");
    }
    error("set: undefined variable ", s);
}

bool Symbol_table::is_declared(string var)
{
    //is var in var_table already?
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

double Symbol_table::define_variable(string var, double val, bool isConst)
{
    // add {var,val,isConst} to var_table
    if (is_declared(var)) error (var, " declared twice.");
    var_table.push_back(Variable{var,val,isConst});
    return val;
}

void Symbol_table::show_variables()
{
    for(int i = 0; i < var_table.size(); ++i)
        cout << var_table[i].name << " = " << var_table[i].value << "\n";
}
//-------------------------------------------------------------------------------

//Declarations and Initializations-----------------------------------------------
Symbol_table st; // used for storing Variables
Token_stream ts;
void calculate(Token_stream& ts);
double statement(Token_stream& ts);
double declaration(Token_stream& ts);
double user_function(Token_stream& ts);
double square_root(Token_stream& ts);
double powerf(Token_stream& ts);
double expression(Token_stream& ts);
double term(Token_stream& ts);
double factorial(Token_stream& ts);
double secondary(Token_stream& ts);
double primary(Token_stream& ts);
double variable(Token_stream& ts);
void intro_message();
void cleanup(Token_stream& ts);
//-------------------------------------------------------------------------------

// Handling all errors in calculate(), still handling in main() too, just for an extra layer of security.
//NOTE: If an error somehow reaches main(), the program will be terminated, with a proper error message
int main()
try{
    //predifined names
    st.define_variable("pi",3.1415926535, true);
    st.define_variable("e", 2.7182818284, true);

    intro_message();
    calculate(ts);
    return 0;
}
catch (exception& e)
{
    cerr << "error: " << e.what() << "\n";
    //keep_window_open(keep_window_open_key); //for some Windows environments
    return 1;
}
catch(...)
{
    cerr << "unhandled error\n";
    //keep_window_open(keep_window_open_key); //for some Windows environments
    return 2;
}

//-------------------------------------------------------------------------------

//Grammar implementation---------------------------------------------------------
void calculate(Token_stream& ts)
{
    //double val;
    while(cin)
    try{
        cout << prompt;
        Token t = ts.get();

        while (t.type == print_key) t = ts.get();      // "eat" print_key characters
        if (t.type == quit_key) return;                //NOTE : In void functions, you can do an empty return. 
        if (t.type == help_key) intro_message();
        if (t.type == show_vars) st.show_variables();
        else {
            ts.putback(t);
            cout << result << statement(ts) << "\n\n";
        }
        
        //ts.putback(t);
        //cout << result << statement() << "\n\n";
        //val = statement();
    }
    catch (exception& e)
    {
        cout.clear();
        cerr << "error: " << e.what() << "\n";
        cerr << "Enter " << recover << " to continue.\n";
        cleanup(ts);
    }
    catch(...)
    {
        cerr << "Unknown error.\n";
        cerr << "Enter " << recover << " to continue.\n";
    }
}

double statement(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.type)
    {
        case let:
            return declaration(ts);

        default:
            ts.putback(t);
            return expression(ts);
    }
}

double declaration(Token_stream& ts)
{
    // assume we already saw "let" (in statement())
    // handle: name = expression
    // declare a variable called "name" with initial value "expression"

    Token t = ts.get();
    bool isConst = false;
    if(t.type == vconst)
    {
        t = ts.get();
        isConst = true;
        if(t.type != name) error ("name expected in declaration");
        string var_name = t.name;    
    }

    else if(t.type != name) error ("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if(t2.type != '=') error("= missing in declaration of ",var_name);

    double d = expression(ts);
    st.define_variable(var_name,d,isConst);
    return d;
}

double square_root (Token_stream& ts) 
{
    // get a token, assuming that we've already used the string "sqrt" in get()
    Token t = ts.get();
    if(t.type != '(') error("sqrt: '(' expected");
    double e = expression(ts);
    if (e < 0) error ("sqrt: cannot calculate square root of negative number");
    
    t = ts.get();
    if(t.type != ')') error("sqrt: ')' expected");
    return sqrt(e); 
}

double powerf (Token_stream& ts)
{
    Token t = ts.get();
    if(t.type != '(') error("power: '(' expected");

    double t1 = expression(ts);

    t = ts.get();
    if(t.type != ',') error("power: arguments must be separated by a ','");

    double t2 = expression(ts);
    if(t2 < 0) error("power: negative exponent");

    t = ts.get();
    if(t.type != ')') error("power: ')' expected");
    return pow(t1, t2);
}

double expression(Token_stream& ts)
{
    double left = term(ts);
    Token t = ts.get();

    while(true)
    {
        switch(t.type)
        {

            case '+':
                left += term(ts);
                t = ts.get();
                break;

            case '-':
                left -= term(ts);
                t = ts.get();
                break;

            default:
                ts.putback(t);
                return left; // if there's no more + and -, return the result
        }
    }
    return left;
}

double term(Token_stream& ts)
{
    double left = factorial(ts);
    Token t = ts.get();

    while(true)
    {
        switch(t.type)
        {
            //ou de paste :)
            case '*':
                left *= factorial(ts);
                t = ts.get();
                break;

            case '/': 
            {
                double d = factorial(ts);
                if(d == 0) error("term: division: cannot divide by 0");
                left /= d;
                t = ts.get();
                break;
            }

            case '%': //Only works for integers
            {

                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(factorial(ts));

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

double factorial(Token_stream& ts)
{
    double left = primary(ts);
    Token t = ts.get();

    switch(t.type)
    {
        case '!':
        {
            int lcopy = narrow_cast<int>(left);
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

double primary(Token_stream& ts)
{
    Token t = ts.get();

    switch(t.type)
    {
        case '(':
        {
            double e = expression(ts);
            t = ts.get();
            if (t.type != ')') error("primary: ')' expected");
            return e;
        }

        case '{':
        {
            double e = expression(ts);
            Token b = ts.get();
            if (b.type != '}') error("primary: '}' expected");
            return e;
        }
        
        case '-':
            return -primary(ts);
        
        case '+':
            return primary(ts);

        case number:
            return t.value;
        
        case name:
            ts.putback(t);
            return variable(ts);

        case power:
            return powerf(ts);
        
        case sroot:
            return square_root(ts);

        default:
            error("primary expexted");
    }
}

double variable(Token_stream& ts){
    Token t = ts.get();
    switch (t.type)
    {
        case name:
        {
            Token t2 = t;
            t = ts.get();
            // check to see if it's an assignment or just a usage of the variable
            if (t.type == '=') 
            {
                double e = expression(ts);
                st.set_value(t2.name, e);
                return e;
            }
            else  
            {
                ts.putback(t);
               return st.get_value(t2.name);
            }
        }  
    }  
}
//-------------------------------------------------------------------------------

//Additional functions-----------------------------------------------------------
void intro_message() //print a custom "banner"
{  
    cout << "---------------------------------------\n"
         << "|Simple calculator - V1.0             |\n"
         << "|                             by BIBAN|\n"
         << "---------------------------------------\n\n"
         << "Supported operators : +, -, *, /, % (for ints only), (), !-factorial\n"
         << "Supported functions :\n"
         << "   - sqrt(expression) - calculates square root of any expression\n"
         << "   - pow(base, exponent) - calculate a base at the power of exponent\n"
         << "      --> base and exponent are expressions\n\n"
         << "Variables can be defined and used as expressions:\n"
         << "   - let variable_name = value - define a variable\n"
         << "   - let const constant_name = value - define a constant\n"
         << "   - variable_name = new_value - assign a new value to a non-constant variable\n"
         << "   - " << show_vars << " - display all variables\n\n"
         << "Use " << quit_key << " to quit the program, " << print_key << " to end an ecuation and " << help_key << " to display this message.\n"
         << "If an error occurs, type in " << recover << " to continue.\n\n";
}

void cleanup(Token_stream& ts)
{ //recover from an error
    ts.ignore(recover);
}
//-------------------------------------------------------------------------------