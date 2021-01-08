#include <iostream>
#include <string>

bool palindrome_str (std::string n)
{
    int start = 0;
    int end = n.length() - 1;
    while (start < end) 
    {
        if (n[start] != n[end]) return false;
        start++;
        end--;
    }
    return true;
}

bool palindrome_arr (const char s[], int n)
{
    int start = 0;
    int end = n-1;
    while (start < end)
    {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

int main()
{
    std::cout << palindrome_arr("ff4",1);
    return 0;
}