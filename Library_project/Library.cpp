#include "Library.h"

namespace Library_f
{
    void Library::add_book(Book::Book b)
    {
        books.push_back(b);
    }

    void Library::add_patron(Patron::Patron p)
    {
        patrons.push_back(p);
    }

    void Library::check_out(Book::Book b)
    {
        // ? how do we hold account of each book in the library
        // i'm thinking of either using the ISBN as an unique identifer, or make our own
    }
    
}