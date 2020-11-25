#include "Library.h"
#include "Exception.h"

namespace Library_f
{
    void Library::add_book(Book::Book b)
    {
        if(!duplicate_ISBN(b.ISBN())) books.push_back(b);
        else throw Exception::Exception("duplicate book");
    }

    void Library::add_patron(Patron::Patron p)
    {
        patrons.push_back(p);
    }

    void Library::check_out(std::string ISBN)
    {
        for(Book::Book book : books)
        {
            if(ISBN == book.ISBN()) book.check_out();
        }
        throw Exception::Exception("ISBN not found (" + ISBN + ")");
    }

    bool Library::duplicate_ISBN(std::string ISBN)
    {
        for(Book::Book& b : books)
        {
            if(b.ISBN() == ISBN) return true;
        }
        return false;
    }

}