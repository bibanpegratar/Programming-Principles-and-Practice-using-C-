#include <string>
#include <iostream>

namespace Library_f::Patron
{
    class Patron
    {
    public:
        std::string name() const { return name_p; }
        std::string card_number() const { return card_number_p; }
        bool has_fees() const { return fees_p != 0; }
        int fees() const { return fees_p; }
        void set_fee(int fee); // will SET a fee, not add to the existing one
        

        Patron(std::string name, std::string card_number, int fee);
        Patron(std::string name, std::string card_number);  //initializer with fee = 0

    private:
        std::string name_p;
        std::string card_number_p;
        int fees_p;
    };

    bool is_valid(std::string name, std::string card_number);
    std::ostream& operator<<(std::ostream& out, const Patron& p);

    //std::ostream& operator<< (std::ostream& os, const Patron& p);
}