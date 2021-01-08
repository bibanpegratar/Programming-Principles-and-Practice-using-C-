#include <iostream>
#include <vector>

std::vector<int> gv {1,2,4,8,16,32,64,128,256,512};

void f(std::vector<int> v)
{
    std::vector<int> lv(v.size());
    lv = gv;
    for (int i : lv) std::cout << i << " ";
    std::cout << "\n";

    std::vector<int> lv2 = v;
    for (int i : lv2) std::cout << i << " ";

}

int main()
{
    f(gv);
    return 0;
}