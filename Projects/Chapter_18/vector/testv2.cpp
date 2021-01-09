#include <iostream>
#include "vector.h"
#include <vector>

struct Foo
{
    int data1;
    char data2;
    Foo() : data1{0}, data2{'c'} {}
    Foo(int d, char c) : data1{d}, data2{c} {}
};

void foo()
{
    vector <Foo> f(5);
    
    for(int i = 0; i < 10; i++)
    {
        f.push_back(Foo(4,'e'));
        std::cout << f[i].data1 << "\n";
    }

    f.erase();
    std::cout << "size: " << f.size() << "\n";
    
}

int main()
{
    foo();
    return 0;
}