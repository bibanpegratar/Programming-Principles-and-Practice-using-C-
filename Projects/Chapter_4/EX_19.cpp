#include "/home/luv/Documents/Books/Principles and Practice using C+++/std_lib_facilities.h"
//An exercise from Bjarne's beginner C++ book
/*19. Write a program where you first enter a set of name-and-value pairs, such
as Joe 17 and Barbara 22 . For each pair, add the name to a vector called
names and the number to a vector called scores (in corresponding po-
sitions, so that if names[7]=="Joe" then scores[7]==17 ). Terminate input
with NoName 0 . Check that each name is unique and terminate with an
error message if a name is entered twice. Write out all the (name,score)
pairs, one per line.
20. Modify the program from exercise 19 so that when you enter a name, the
program will output the corresponding score or name not found .
21. Modify the program from exercise 19 so that when you enter an integer,
the program will output all the names with that score or score not found . */

class Name_value{
  public:
    string name;
    int score;
    Name_value(): name(""), score(0) {};
};

vector <Name_value> nv;
const string quit = "|";


void read_pairs(string quit);
void repeating_names(vector <Name_value> names);
void print_start_message();
int get_score_by_name(string name);
void display_score(vector <Name_value> nv, string quit);


int main(){
  print_start_message();
  char x;

  while (cin >> x){
    switch(x){
      case '1':
        read_pairs(quit);
        break;
      case '2':
        display_score(nv, quit);
        break;
      case '3':
        //call function to get score by name
        cout << "Not implemented yet !";
        break;
      case '|':
        return 0;
        break;
      default:
        cout << "Unknown function.\n";
        print_start_message();
        break;
    }
    print_start_message();
  }

/* read_pairs(quit);
  repeating_names(names);
  for (int i = 0; i < names.size(); i++){
    cout << ">> " << names[i] << " - score " << scores[i] << "\n";
  } */

  return 0;
}

void print_start_message(){
  cout << ">> 1 - read name score pairs\n"
       << ">> 2 - get a name by a score\n"
       << ">> 3 - get a score by a name\n"
       << ">> " << quit << " - exit program or current application\n";
}

void read_pairs(string quit){
  cout << ">> Input some nicknames followed by a score. Enter | at anytime to exit.\n";
  Name_value namev;

  while (cin >> namev.name && namev.name != quit){
    cin >> namev.score;
    nv.push_back(namev);
  }

  cout << ">>Exiting....\n\n\n";
}

void repeating_names(vector <Name_value> names){
  vector <string> names_copy;
  for (Name_value pair : names){
    names_copy.push_back(pair.name);
  }
  sort(names_copy);

  for (int i = 0; i < names_copy.size(); i++){
    if (i != 0 && names_copy[i] == names_copy[i-1] && names_copy.size() > 1){
      simple_error("Identic names!");
    }
  }
}

int get_score_by_name(string name){
  for (int i = 0; i < nv.size(); i++){
    if (name == nv[i].name) return nv[i].score;
  }
  return -1;
}

void display_score(vector <Name_value> nv, string quit){
  if (nv.size() != 0){
    string name;
    cout << ">> Input a name: ";

    while (cin >> name){
      if (name != quit){
        int score = get_score_by_name(name);
        if (score != -1 ) cout << ">> Score: " << score << '\n';
        else cout << "Invalid name!\n";
        cout << ">> Input a name: ";
      }
      else cout << "Exiting...\n";
    }
  }
  else cout << "No names provided. Please first enter names.\n\n";

}
