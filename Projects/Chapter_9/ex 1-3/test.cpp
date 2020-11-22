#include "name_pairs.h"

Name_pairs name_p;
int main()
try{
	cout << "Input names: \n";
	name_p.add_name();
	cout << "Input ages: \n";
	name_p.add_age();
	name_p.sort_v();
	cout << name_p;
	return 0;
}
catch (exception& e)
{
	char ch;
	cin.clear();

	cerr << "error: " << e.what() << "\n";
	cerr << "Enter " << Keycodes::continue_char << " to continue.\n";
	while (cin >> ch && ch != Keycodes::continue_char) { cin.clear(); }
	main();
}
