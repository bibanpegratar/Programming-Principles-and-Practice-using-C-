#include "/home/luv/Documents/Principles and Practice using C++/std_lib_facilities.h"

int main()
{
  vector <string> words;
  vector <string> bad_words = {"Nigga", "nigga", "bitch", "slut", "gay"};
  const string replacement = "BLEEP";s

  for (string word; cin >> word; ){
    for (string bad_word : bad_words){
      if (bad_word == word) word = replacement;
    }
    words.push_back(word);
  }

  for (string word : words) cout << word << " ";
  return 0;
}
