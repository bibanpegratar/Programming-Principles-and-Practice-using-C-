#include "Book.h"

namespace Library_f::Book
{
  Book::Book(std::string ISBN, std::string title, std::string author, Genre genre, Chrono::Date copyright, bool checked_out)
      : ISBN_p{ISBN},
        title_p{title},
        author_p{author},
        genre_p{genre},
        copyright_p{copyright},
        checked_out_p{checked_out}
  {
    if (!is_valid(ISBN, author))
      throw Invalid{};
  }

  Book::Book(std::string ISBN, std::string title, std::string author, Genre genre, Chrono::Date copyright)
      : ISBN_p{ISBN},
        title_p{title},
        author_p{author},
        genre_p{genre},
        copyright_p{copyright},
        checked_out_p{false} // initialized book is, by default, checked in
  {
    if (!is_valid(ISBN, author))
      throw Invalid{};
  }

  bool is_valid(const std::string &ISBN, const std::string &author)
  {
    return is_isbn(ISBN);
    //check author
  }

  bool is_isbn(const std::string &ISBN)
  {
    int sum = 0;
    int pow = 10;

    if (ISBN.size() != 10)
      return false;
    for (int i = 0; i < 9; i++)
    {
      if (isdigit(ISBN[i]))
      {
        sum += (ISBN[i] - '0') * pow;
        pow--;
      }
    }
    sum += (ISBN[9] == 'X') ? 10 : (ISBN[9] - '0');
    return (sum % 11 == 0);
  }

  bool operator==(const Book &a, const Book &b)
  {
    return a.ISBN() == b.ISBN();
  }

  bool operator!=(const Book &a, const Book &b)
  {
    return a.ISBN() != b.ISBN();
  }

  std::ostream &operator<<(std::ostream &os, const Book &book)
  {
    os << "Author: " << book.author() << "\n"
       << "Title: " << book.title() << "\n"
       << "ISBN: " << book.ISBN() << "\n";

    return os;
  }
}
