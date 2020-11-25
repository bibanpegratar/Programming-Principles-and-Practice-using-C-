#include "Patron.h"

namespace Library_f::Patron
{
    Patron::Patron(std::string name, std::string card_number, int fee)
        :name_p{name}, card_number_p{card_number}, fees_p{fee}
    {
    };

    Patron::Patron(std::string name, std::string card_number)
        :name_p{name}, card_number_p{card_number}
    {
    };

    void Patron::set_fee(int fee)
    {
        fees_p = fee;
    }

    /*std::ostream &operator<< (std::ostream& out, const Patron& patron)
    {
        out << 'p';
        return oss;
    }*/
} // namespace Library::Patron
