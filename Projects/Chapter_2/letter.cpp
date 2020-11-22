#include "std_lib_facilities.h"

int main ()
{
  string first_name, target_first_name, friend_first_name;
  char friend_sex = 0;
  int target_age;

  cout << ">> What is your name ?\n" << ">> ";
  cin >> first_name;

  if (first_name == "Eliot")
  {
    cout << "kali@kali: Hello, friend.\nkali@kali: Are you ready to join fsociety and destroy Evil Corp once and for all ?\n";
    return 0;
  }

  cout << ">> What is the first name of the person you're writing to ?\n" << ">> ";
  cin >> target_first_name;

  cout << ">> A common friend's first name ?\n" << ">> ";
  cin >> friend_first_name;

  cout << ">> What sex is your friend ? Type in 'm' for male or 'f' for female.\n" << ">> ";
  cin >> friend_sex;

  cout << ">> How old is the person you're writing to ?\n" << ">> ";
  cin >> target_age;

  if (target_age <= 0 || target_age >= 110) simple_error("Invalid age range. ");

  cout << "       Hello, " << target_first_name << "\n\n"
       << "I know we haven't spoken in a while. How are you? How is your life going ?\n"
       << "Have you seen " << friend_first_name << " lately ? ";

  if (friend_sex == 'm') cout << "If you see " << friend_first_name << ", tell him to call me.\n";
  if (friend_sex == 'f') cout << "If you see " << friend_first_name << ", tell her to call me.\n";

  if (target_age <= 12) cout << "Next year you'll be " << target_age + 1 << ". Hooray! ";
  if (target_age == 17) cout << "Next year you'll be able to vote. ";
  if (target_age >= 70) cout << "You might just die tomorrow. ";

  cout << "It would be nice to hear back from you soon.\n"
       << "                       Sincerely, \n\n"
       << "                       " << first_name << " \n";
  return 0;
}
