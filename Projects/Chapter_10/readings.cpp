#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
This program parses readings of temperatures from a file
a reading = (int_day int_hour double_temp)

a day = a vector that holds 24 doubles (temperatures), one / hour.
    - the vector's elements are initialized with an invalid (not_a_temperature) value

a month = a vector of 32 days ( day[0] will be ignored for ease of implementation ) + a month identifier (int)
    - structure : {month month_identifier day_0 day_1 day_2 ... day_32 }

a year = a vector of 12 months + a year identifier (int)
    - structure : {year year_identifer month_0 month_1 ... month_2 }
*/

const double not_a_reading = -777; // marker for an empty temperature entry
const int not_a_month = -1; // marker for an empty month
const double min_temp = -200;
const double max_temp = 200;
const std::string month_key = "month";
const std::string year_key = "year";

std::vector <std::string> month_input_tbl =
{
    "jan", "feb", "mar", "apr", "may", "jun", "jul",
    "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(std::string s)
{
    for (int i = 0; i < month_input_tbl.size(); i++)
        if (month_input_tbl[i] == s) return i;
    return not_a_month;
}

std::vector <std::string> month_output_tbl =
{
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

std::string int_to_month(int m)
{
    for (int i = 0; i < month_output_tbl.size(); i++)
    {
        if (i == m) return month_output_tbl[i];
    }
}

struct Day
{
    std::vector <double> hour{ std::vector <double>(24, not_a_reading) }; // a vector of 24 doubles for a reading / hour
};

struct Month
{
    int month{ not_a_month }; // initialize month as empty
    std::vector <Day> day{ 32 }; // a month has maximum 31 days (days[0] is ignored)
};

struct Year
{
    int year;
    std::vector <Month> month{ 12 }; // a year has 12 months
};

struct Reading
{
    int day;
    int hour;
    double temperature;
};

bool is_valid(Reading& r);
void end_of_loop(std::istream& ist, char ch, const std::string& error_message);
bool has_readings(std::vector <double>& readings);

std::istream& operator>> (std::istream& ist, Reading& r)
{
    char ch;
    ist >> ch;
    if (ch != '(') //this is fail()
    {
        // set the stream state to fail and return istream, might be used by something else
        ist.unget();
        ist.clear(std::ios_base::failbit);
        return ist;
    }

    char ch2;
    int day, hour;
    double temperature;
    ist >> day >> hour >> temperature >> ch2;
    if (ch2 != ')' || !ist) throw std::runtime_error("reading: invalid reading"); //this is bad()
    //this is good()
    r.day = day;
    r.hour = hour;
    r.temperature = temperature;
    return ist;
}

std::ostream& operator<< (std::ostream& ost, Day& d)
{
    for (int i = 0; i < d.hour.size(); i++)
    {
        if (d.hour[i] != not_a_reading)
        {
            ost << "\t\t- " << "h: " << i << ", t: " << d.hour[i] << "\n";
        }

    }
    return ost;
}

std::istream& operator>> (std::istream& ist, Month& m)
{
    char ch = 0;
    ist >> ch;
    if (ch != '{') //this is fail()
    {
        // set the stream state to fail and return istream, might be used by something else
        ist.unget();
        ist.clear(std::ios_base::failbit);
        return ist;
    }

    std::string month, mm;
    ist >> month >> mm;
    if (!ist || month != month_key) throw std::runtime_error("month: bad start"); // this is bad()
    m.month = month_to_int(mm);

    int duplicates = 0;
    int invalids = 0;

    for (Reading r; ist >> r; )
    {
        // check for duplicates and invalid readings, then add them to the vector
        if (is_valid(r)) // TODO : implement
        {
            if (m.day[r.day].hour[r.hour] != not_a_reading) duplicates++;
            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else invalids++;
    }
    if (invalids) throw std::runtime_error("month: invalid readings, " + invalids); //this is bad()
    if (duplicates) throw std::runtime_error(" month: duplicate readings, " + duplicates); //this is bad()
    end_of_loop(ist, '}', "month: invaild end");
    //this is good()
    return ist;
}

std::ostream& operator<< (std::ostream& ost, Month& m)
{
    ost << int_to_month(m.month) << "\n";
    for (int i = 1; i < m.day.size(); i++)
    {
        if (has_readings(m.day[i].hour)) ost << "\t\tday " << i << "\n" << m.day[i];
        /*for (int x = 0; x < m.day[i].hour.size(); x++)
        {
            
        }*/
    }
    return ost;
}

std::istream& operator>> (std::istream& ist, Year& y)
{
    char ch;
    ist >> ch;
    if (ch != '{') //this is fail()
    {
        ist.unget();
        ist.clear(std::ios_base::failbit);
        return ist;
    }

    std::string year;
    int yy;
    ist >> year >> yy;
    if (year != year_key || !ist) throw std::runtime_error("year: bad start"); //this is bad()

    y.year = yy;
    while (true)
    {
        Month m;
        if (!(ist >> m)) break;
        y.month[m.month] = m;
    }

    end_of_loop(ist, '}', "year: invaild end");
    //this is good()
    return ist;
}

std::ostream& operator<< (std::ostream& ost, Year& y)
{
    ost << "Year " << y.year << "\n";
    for (Month& m : y.month)
    {
        if (m.month != not_a_month) ost << "\t" << m;
    }
    ost << "\n";
    return ost;
}

bool is_valid(Reading& r)
{
    if (r.temperature > max_temp || r.temperature < min_temp) return false;
    if (r.day < 1 || r.day > 31) return false;
    if (r.hour < 0 || r.hour > 23) return false;
    return true;
}

void end_of_loop(std::istream& ist, char term, const std::string& error_message)
//handles an istream in a fail() state, looks for terminator character
{
    if (ist.fail())
    {
        ist.clear();
        char ch2;
        if (ist >> ch2 && ch2 == term) return;
        throw std::runtime_error(error_message);
    }
}

bool has_readings(std::vector <double>& readings)
{
    for (double d : readings)
    {
        if (d != not_a_reading) return true;
    }
    return false;
}

int main()
try {

    std::ifstream fin{ "input" };
    if (!fin) throw std::runtime_error("cannot open input file");
    //fin.exceptions(fin.exceptions() | std::ios_base::badbit);

    std::ofstream fout{ "output" };

    std::vector <Year> years;

    while (true)
    {
        Year y;
        if (!(fin >> y)) break;
        years.push_back(y);
    }
    for (Year& y : years) fout << y;
    std::cout << "done\n";

    return 0;
}
catch (std::runtime_error& e)
{
    std::cerr << "error: " << e.what() << "\n";
    return 1;
}