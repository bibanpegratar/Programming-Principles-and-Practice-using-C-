#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

string parse_vector(vector <char> v);
constexpr int max_digits = 4;
constexpr char end_input = '|'; // character required to indicate that input is finished
constexpr char quit_program = 'q';

int main()
try{
    vector <char> number;
    string output;
    char c;

    //Program banner
    cout << "---------------------------------------\n"
         << "|Digits to integers+ - V0.0.1         |\n"
         << "|                             by BIBAN|\n"
         << "|Deconstruct a decimal number.        |\n"
         << "---------------------------------------\n\n"
         << ">> Enter a positive integer of maximum " << max_digits << " digits.\n"
         << ">> Use " << end_input << " after you entered the number.\n"
         << ">> Use " << quit_program << " to exit at anytime.\n"
         << ">> ";

    while (cin >> c){
        switch(c){
            //if it's a digit, put it into the vector
            case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
                number.push_back(c);
                break;
            
            case end_input:
                output = parse_vector(number);
                cout << ">> ";

                for (char digit : number) cout << digit;
                cout << " is " << output << "\n"
                     << ">> ";

                number = {}; //reset the vector and the output each time
                output = "";
                break;
            
            case quit_program: return 0;

            default:
                error("invalid input");
        }

    }
    return 0;
}
    
catch (exception& e){
    cerr << "error: " << e.what() << "\n";
    return 1;
}

string parse_vector(vector <char> v){
    
    int x = max_digits - v.size();
    string output;

    if (x < 0) error ("too many digits");

    for(int i = 0; i < v.size(); i++){
        output += v[i];
            switch(x+i){
                case 0: 
                    if (v[i] == '1') output += " hundread ";
                    else output += " hundreads ";
                    break;

                case 1:
                    if (v[i] == '1') output += " thousand ";
                    else output += " thousands "; 
                    break;

                case 2: 
                    if (v[i] == '1') output += " ten ";
                    else output += " tens ";
                    break;

                case 3: 
                    if (v[i] == '1') output += " one ";
                    else output += " ones ";
                    break;

                default:
                    cout << " sincer habar n-am ";
            }
    }
    return output;
}