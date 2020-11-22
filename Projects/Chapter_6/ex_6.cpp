#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"

vector <string> nouns = {"birds", "cars", "children", "computers", "castles"};
vector <string> verbs = {"fly", "drive", "fly", "sleep", "compute", "is", "am"};
vector <string> conjunctions = {"and", "or"};
constexpr char end_sentence = '.';

bool sentence();
bool conjunction();
bool verb();
bool noun();

int main()
try{
    bool isTrue;
    while(true){
        cin.clear();

        if(sentence()) {
            cout << "OK\n";
        }
        else {
            cout << "NOT OK\n";
        }
    }
    return 0;
}
catch(exception& e){
    cerr << "error: " << e.what();
    return 69;
}

bool sentence(){
    char word;

    if (noun() == false) return false;
    if (verb() == false) return false;

    cin >> word;
    if (word != end_sentence){
        cin.putback(word);
        if(conjunction()) sentence();
        else return false;
    }
    else return true;
}

bool conjunction (){
    string word;
    cin >> word;
    for (string conj : conjunctions) if(word == conj) return true;
    return false;
}

bool noun(){
    string word;
    cin >> word;
    for (string n : nouns) if (word == n) return true;
    return false;
}

bool verb (){
    string word;
    cin >> word;
    for (string v : verbs) if (word == v) return true;
    return false;
}