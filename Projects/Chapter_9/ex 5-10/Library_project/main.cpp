#include "Library.h"
#include "Exception.h"
using namespace Library_f::Book;
using namespace Library_f::Patron;

const char continue_key = '~';
void add_data();
void do_stuff();

//File that just tests some functions and stuff

int main()

{
    add_data();
    int x;
    while(std::cin >> x)
    {
        do_stuff();
    }

}


void add_data()
{
    Book book_1 = {"0062641549", "Finn & Jake", "Rebecca Sugar", Genre::fiction, {10,Chrono::Month::aug, 2020}};
    Book book_2 = {"0062641522", "Harry Potter : The Prizoneer of Azkaban", "J.K.Rowling", Genre::fiction, {11,Chrono::Month::feb, 1999}};
    Book book_3 = {"6064400722", "Emotional Inteligence", "Daniel Goleman", Genre::nonfiction, {11,Chrono::Month::jan, 2010}};

    Patron p_1 = {"Alex Ivan", "1231312"};
    Patron p_2 = {"Ionel Marcel", "69696969"};
    Patron p_3 = {"Sandu Ceorba", "420420420"};

    lib.add_book(book_1);
    lib.add_book(book_2);
    lib.add_book(book_3);

    lib.add_patron(p_1);
    lib.add_patron(p_2);
    lib.add_patron(p_3);
}

void do_stuff()
try{
    std::cout << lib.book("0062641549") << "\n";
    //std::cout << lib.book("3414141443") << "\n";

    std::cout << lib.patron("Alex Ivan");
    lib.patron("Alex Ivan").set_fee(20);
    lib.book("6064400722").check_out();

    std::cout << lib.book("6064400722") << "\n";
    std::cout << lib.patron("Alex Ivan");
    
    std::cin.clear();
}
catch (Library_f::Exception::Exception &e)
{
    char c;
    std::cerr << "error: " << e.what() << "\n";
    std::cout << "Enter " << continue_key << " to continue.\n";
    while (std::cin >> c && c != '~') {};
    std::cin.clear();
    do_stuff();
}