#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Roman
{
    struct Roman
    {
        int interger = 0;
        std::string roman;
    };

    int roman_digit(char ch);
    void roman_to_int(Roman &r);
} // namespace Roman

std::istream &operator>>(std::istream &ist, Roman::Roman &r);
std::ostream &operator<<(std::ostream &ost, const Roman::Roman &r);
