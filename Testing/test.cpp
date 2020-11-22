/*


Un număr natural se numește aproape prim dacă poate fi scris ca produs de două numere naturale prime distincte.
Cerinţa

Se citește un număr natural n și apoi n numere naturale. Să se determine cel mai mare număr aproape prim dintre cele date, și de câte ori apare.
Date de intrare

Programul citește de la tastatură numărul n, și apoi n numere naturale.
Date de ieşire

Programul afișează pe ecran numere M și C, separate prin exact un spațiu, reprezentând cel mai mare număr aproape prim dintre cele date și numărul său de apariții.

*/
#include <iostream>
#include <vector>
using namespace std;

/*
    citesc n
    cat timp n > 0 
        citesc nr
        is_aproape_prim()
        daca e aproape prim,
            verifica care e cel mai mare numar
            contor pt de cate ori apare
        
*/


int main()
{
    int n, nr;
    vector <int> aproape_prime ;
    cin >> n;
    while(nr > 0)
    {
        cin >> nr;
        if(is_aproape_prim(nr))
        {
            
        }

        nr--;
    }
    return 0;
}

bool is_aproape_prim(int n, vector <int>& aproape_prime)
{
    int copie = n;
    int div = 2;
    int prime_div_count = 0;
    if (copie == 1) return false;
    while (copie > 1)
    {
        if (copie % div == 0)
        {
            ++prime_div_count;
            while (copie % div == 0) n /= div;
        }
        div++;
    }
    cout << prime_div_count '\n';
    if (prime_div_count == 2) 
    {
        aproape_prime.push_back(n)
        return true;
    }
    else return false;

}

bool biggest_prime(vector <int>& aproape_prime )
{
    sort(aproape_prime);
}
