#include "Library.h"
using namespace Library_f::Book;
using namespace Library_f::Patron;

int main()
try
{
    Book book_1 = {"007462542X", "Warrior Cats : Ice and Fire", "Codrin Bradea - Satana", Genre::nonfiction, {10, Chrono::Month::jan, 2020}};
    // Book book_2 = {isbn_2, "Warrior Cats : Vanzatorii de Lebenita", "Codrin Bradea - Satana", {11,Chrono::Month::feb, 1999}};
    std::cout << book_1;

    Patron patron_1 = {"Ivan Alexandru", "12345678", 50};
    std::cout << patron_1.name() << "\n";
    patron_1.set_fee(70);
    std::cout << patron_1.fees() << "\n";

    return 0;
}
catch (Invalid &e)
{
    std::cerr << "error: invalid book\n";
    return 1;
}