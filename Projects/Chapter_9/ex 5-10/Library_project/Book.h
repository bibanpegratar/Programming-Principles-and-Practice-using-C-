#include <iostream>
#include <string>
#include "Chrono.h"
#include "Exception.h"

namespace Library_f::Book
{
    enum class Genre
    {
        fiction, nonfiction, periodical, biography, children, other
    };

    class Book
    {
    public:
        //inline functions for returning the private members
        std::string ISBN() const { return ISBN_p; }
        std::string title() const { return title_p; }
        std::string author() const { return author_p; }
        Genre genre() const { return genre_p; }
        Chrono::Date copyright_date() const { return copyright_p; }
        bool is_checked_out() const { return checked_out_p; }

        void check_in() { checked_out_p = false; }
        void check_out() { checked_out_p = true; }

        //constructors
        Book(std::string ISBN, std::string title, std::string author, Genre genre, Chrono::Date copyright, bool checked_out);
        Book(std::string ISBN, std::string title, std::string author, Genre genre, Chrono::Date copyright);

    private:
        std::string ISBN_p;
        std::string title_p;
        std::string author_p;
        Genre genre_p;
        Chrono::Date copyright_p;
        bool checked_out_p;
    };

    bool is_valid(const std::string &ISBN);
    bool operator==(const Book &a, const Book &b); //compare ISBN numbers
    bool operator!=(const Book &a, const Book &b); //compare ISBN numbers
    bool is_isbn(const std::string &ISBN);
    std::ostream &operator<<(std::ostream &os, const Book &book);
}
