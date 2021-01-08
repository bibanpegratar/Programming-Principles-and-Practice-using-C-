#include <iostream>

int ga[10] = {1,2,4,8,16,32,64,128,256,512};

void f(int arr[], int sz)
{
    int la [10];
    std::copy(ga, ga + sizeof(ga)/sizeof(int), la);
    for (int i = 0; i < sizeof(ga)/sizeof(int); i++) std::cout << la[i] << " ";

    std::cout << "\n";

    int* p = new int[sz];
    std::copy(arr, arr + sz, p);
    for (int i = 0; i < sz; i++) std::cout << p[i] << " ";
    delete[] p;

}
int main()
{
    f(ga,sizeof(ga)/sizeof(int));
    std::cout << "\n";
    int aa[10];
    aa[0] = 1; // the first factorial value is 1

    //fill aa with the first 10 factorial values
    for (int i = 1; i < sizeof(aa)/sizeof(int); i++)
        aa[i] = aa[i-1] * (i+1);

    f(aa,sizeof(aa)/sizeof(int));

    return 0;
}