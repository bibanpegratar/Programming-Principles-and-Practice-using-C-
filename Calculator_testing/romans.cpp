#include "romans.h"
#include "constants.h"

namespace Roman
{
    int roman_digit(char ch)
    {
        switch (ch)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return -1;
        }
    }
    void roman_to_int(Roman &r)
    {
        //std::cout << r.roman << "\n";
        for (int i = 0; i < r.roman.size(); i++)
        {
            if (i != r.roman.size() - 1) //if it's not the last character
            {
                if (roman_digit(r.roman[i]) < roman_digit(r.roman[i + 1]))
                {
                    r.interger += (roman_digit(r.roman[i + 1]) - roman_digit(r.roman[i]));
                    i++;
                }
                else
                    r.interger += (roman_digit(r.roman[i]));
            }
            else
                r.interger += (roman_digit(r.roman[i]));
        }
    }
} // namespace Roman
std::istream &operator>>(std::istream &ist, Roman::Roman &r)
{
    char ch;
    std::string str;

    while (ist.get(ch))
    {
        switch (ch)
        {
        case 'I':
        case 'V':
        case 'X':
        case 'L':
        case 'C':
        case 'D':
        case 'M':
            str += ch;
            break;

        case (Constants::print_key):
        {
            ist.unget(); //the end of reading character is managed by Token_stream::get()
            r.roman = str;
            roman_to_int(r);
            return ist;
        }
        default:
        {
            ist.unget();
            return ist;
        }
        }
    }
    return ist;
}
std::ostream &operator<<(std::ostream &ost, const Roman::Roman &r)
{
    ost << r.roman << '=' << r.interger;
    return ost;
}