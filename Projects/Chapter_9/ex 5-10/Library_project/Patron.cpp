#include "Patron.h"

namespace Library_f::Patron
{
    Patron::Patron(std::string name, std::string card_number, int fee)
        :name_p{name}, card_number_p{card_number}, fees_p{fee}
    {
    };

    Patron::Patron(std::string name, std::string card_number)
        :name_p{name}, card_number_p{card_number}, fees_p{0}
    {
    };

    void Patron::set_fee(int fee)
    {
        fees_p = fee;
    }

    std::ostream& operator<<(std::ostream& out, const Patron& p)
    {
        out << "Name: " << p.name() << "\n"
            << "Card number: " << p.card_number() << "\n"
            << "Fees: " << p.fees() << "\n";

        return out;
    }
} // namespace Library::Patron
