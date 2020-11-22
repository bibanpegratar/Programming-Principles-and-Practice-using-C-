#include "Chrono.h"

int main()
try {
    Chrono::Date birthdate_niga (28, Chrono::Month::feb, 1900);
    Chrono::Date birthdate_john (27, Chrono::Month::feb, 1900);
    bool is_equal = birthdate_john != birthdate_niga;
    cout << is_equal << "\n";
    return 0;
}
catch(Chrono::Invalid& e)
{
    cerr << "invalid date" << "\n";
    return 1;
}