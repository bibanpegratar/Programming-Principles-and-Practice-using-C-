#include "Chrono.h"

namespace Chrono
{
    Date::Date(int dd, Month mm, int yy)
        : d{dd}, m{mm}, y{yy}
    {
        if(!is_date(dd, mm, yy)) throw Invalid{}; // check for valid date
    }

    Date::Date()
        : d{1}, m{Month::jan}, y{2000} // default date : 1 jan 2000
    {
    }

    void Date::add_year(int n)
    {
        if (m==Month::feb && d==29 && !leapyear(y+n)) // beware of leap years!
        { 
            m = Month::mar; // use March 1 instead of February 29
            d = 1;
        }

        y+=n;
    }

    bool is_date (int d, Month m, int y)
    {
        if(d < 0) return false;  // day can't be negative
        if(m < Month::jan || m > Month::dec ) return false;

        int days_in_month = 31; // most months have 31 days
        switch(m)
        {
            case Month::feb:
            {
                days_in_month = (leapyear(y))?29:28; // check for leapyear
                break;
            }

            case Month::apr: case Month::jun: case Month::sep: case Month::nov: // months with 30 days
            {
                days_in_month = 30;
                break;
            }
        }
        if (d > days_in_month) return false;
        return true;
    }

    bool leapyear (int y)   
    {
        if(y % 4 == 0) 
        {
            if(y % 100 != 0) return true;
            else if (y % 400 == 0) return true;
        }
        return false;
    }

    ostream& operator<< (ostream& os, const Date& dd)
    // output format : (day.month.year)
    {
        return os << '(' << dd.day()
               << '.' << int(dd.month())
               << '.' << dd.year() << ')';
    }

    istream& operator>> (istream& is, Date& dd)
    // input format : (day.month.year)
    {
        int d, m, y;
        char ch1, ch2, ch3, ch4;

        is >> ch1 >> d >> ch2 >> m >> ch3 >> y >> ch4;
        if (!is) return is;

        if (ch1!= '(' || ch2!='.' || ch3!='.' || ch4!=')') // check for bad formatting
        { 
            is.clear(ios_base::failbit); // set the fail bit. dunno wtf this does
            return is;
        }
        dd = Date(d, Month(m),y); // update dd
        return is;
    }

    bool operator== (const Date& a, const Date& b)
    {
        return a.day() == b.day() && 
               int(a.month()) == int(b.month()) &&
               a.year() == b.year();
    }

    bool operator!= (const Date& a, const Date& b)
    {
        return !(a==b);
    }
}