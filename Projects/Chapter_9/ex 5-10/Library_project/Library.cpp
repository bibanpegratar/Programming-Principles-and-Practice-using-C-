#include "Library.h"
#include "Exception.h"

namespace Library_f
{
    void Library::add_book(Book::Book b)
    {
        if(!duplicate_ISBN(b.ISBN())) books.push_back(b);
        else throw Exception::Exception("Library: add_book(): duplicate book");
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
        throw Exception::Exception("Library: check_out(): ISBN not found (" + ISBN + ")");
    }

    bool Library::duplicate_ISBN(std::string ISBN)
    {
        for(const Book::Book& b : books)
        {
            if(b.ISBN() == ISBN) return true;
        }
        return false;
    }

    Patron::Patron& Library::patron (std::string name)
    {
        for(Patron::Patron& p : patrons)
        {
            if(name == p.name()) return p;
        }
        throw Exception::Exception("Library: patron(): patron with specified name not found");
    }

    Book::Book& Library::book (std::string ISBN)
    {
        for(Book::Book& b : books)
        {
            if(ISBN == b.ISBN()) return b;
        }
        throw Exception::Exception("Library: book(): book with specified name not found");
    }

}