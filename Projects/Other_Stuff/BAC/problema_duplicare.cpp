#include <iostream>
#include <math.h> 

using namespace std; // only for ease of readability of the code

void duplicare (int n, int &d)
{
    int x;
    d = 0;
    double power = 1.0;
    while (n > 0)
    {
        x = n % 10;
        if (n % 2 != 0)
        {
            if(power == 1) 
            {
                d += x*10.0 + x;
                power += 2;
            }

            else 
            {
                d = d + x * pow(10.0,power) + x*pow(10.0,power-1);
                power += 2;
            }
        }
        else
        {
            if (x == 0) {power ++;}
            else 
            {
                d = d + x*pow(10.0,power-1);
                power ++;
            }

            
        }
        n /= 10;
    }
}

int main()
{
    int d;
    duplicare(2019,d);
    cout << d;
    return 0;
}