#include "std_lib_facilities.h"

namespace Chrono
{
    class Invalid {}; // class used when throwing errors
    
    enum class Month
    {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    enum class Day 
    {
        monday, tuesday, wednesday, thursday, friday, saturday, sunday
    };

    class Date // format : int d, Month m, int y
    {
    public:
        //Inline functions
        int day() const {return d;}
        Month month() const {return m;}
        int year() const {return y;}

        //Constructors
        Date(int dd, Month mm, int yy);
        Date(); //default constructor

        //Essential functions
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int d;
        Month m;
        int y;       
    };

    //Helper functions
    bool is_date (int d, Month m, int y); // check if the date is valid; used in constructors
    bool leapyear(int y); // check if year y is a leapyear
    Day day_of_week(const Date& d); // get the day of the week from a Date
    Date next_Sunday(const Date d); // get the next sunday after Date d
    Date next_weekday(const Date& d); // get the next weekday after Date d

    //Overloaded operators
    ostream& operator<< (ostream& os, const Date& dd);
    istream& operator>> (istream& is, Date& dd);

    bool operator== (const Date& a, const Date& b);
    bool operator!= (const Date& a, const Date& b);
}