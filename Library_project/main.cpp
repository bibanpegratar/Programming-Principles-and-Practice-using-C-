#include "Library.h"
#include "Exception.h"
using namespace Library_f::Book;
using namespace Library_f::Patron;

//File that just tests some functions and stuff

Library_f::Library lib;

int main()
try
{
    Book book_1 = {"0357108294", "Warrior Cats : Ice and Fire", "Codrin Bradea - Satana", Genre::nonfiction, {10, Chrono::Month::jan, 2020}};
    Book book_2 = {"007462542X", "Warrior Cats : Ice and Fire", "Codrin Bradea - Satana", Genre::nonfiction, {10, Chrono::Month::jan, 2020}};

    // Book book_2 = {isbn_2, "Warrior Cats : Vanzatorii de Lebenita", "Codrin Bradea - Satana", {11,Chrono::Month::feb, 1999}};

    lib.add_book(book_1);
    lib.add_book(book_2);

    //std::cout << lib.books[0] << ',' << lib.books[0].is_checked_out()<< "\n";
    //std::cout << lib.books[1] << ',' << lib.books[1].is_checked_out()<< "\n";

    //lib.books[0].check_out();

    //std::cout << lib.books[0] << ',' << lib.books[0].is_checked_out()<< "\n";
    //std::cout << lib.books[1] << ',' << lib.books[1].is_checked_out()<< "\n";


    return 0;
}
catch (Library_f::Exception::Exception &e)
{
    std::cerr << "error: " << e.what() << "\n";
    return 1;
}