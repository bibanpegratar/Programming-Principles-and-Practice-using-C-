#include "Patron.h"
#include "Book.h"
#include <vector>

namespace Library_f
{
    
    struct Trasnsaction
    {
        Book::Book book;
        Patron::Patron patron;
        Chrono::Date date;
    };

    std::vector <Trasnsaction> transactions;

    class Library
    {
    public:
        void add_book(Book::Book b);
        void add_patron(Patron::Patron p);
        void check_out(Book::Book b);

    private:
        std::vector <Book::Book> books;
        std::vector <Patron::Patron> patrons;
    };

    
}
