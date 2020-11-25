#include "Book.h"
#include "Exception.h"
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
    if (!is_valid(ISBN))
      throw Exception::Exception("ISBN not valid");
  }

  Book::Book(std::string ISBN, std::string title, std::string author, Genre genre, Chrono::Date copyright)
      : ISBN_p{ISBN},
        title_p{title},
        author_p{author},
        genre_p{genre},
        copyright_p{copyright},
        checked_out_p{false} // initialized book is, by default, checked in
  {
    if (!is_valid(ISBN))
      throw Exception::Exception("ISBN not valid");
  }

  bool is_valid(const std::string &ISBN)
  {
    return is_isbn(ISBN);
    //check author ?
  }

  bool is_isbn(const std::string &ISBN)
  /*
  An ISBN (10-digit version here) is correct if the the sum of the ten digits, each multiplied by its (integer) weight, descending from 10 to 1, is a multiple of 11. 
  That is, if xi is the ith digit, then x10 must be chosen.
  The last digit can be X, which is equal to 10.
  */
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
  
  //ISBN is the criteria used for comparison
  bool operator==(const Book &a, const Book &b)
  {
    return a.ISBN() == b.ISBN();
  }

  //ISBN is the criteria used for comparison
  bool operator!=(const Book &a, const Book &b)
  {
    return a.ISBN() != b.ISBN();
  }

  //output operator overloading
  std::ostream &operator<<(std::ostream &os, const Book &book)
  {
    os << "Author: " << book.author() << "\n"
       << "Title: " << book.title() << "\n"
       << "ISBN: " << book.ISBN() << "\n";

    return os;
  }
}
