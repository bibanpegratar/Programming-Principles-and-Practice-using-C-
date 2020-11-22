#include <iostream>
#include <vector>
using namespace std;

void print_v(string label, const vector <int>& v);
void fibonacci(int x,int y, vector<int>& v, int n);
void reverse_v_ref(vector <int>& v);
vector<int> reverse_v(vector <int> v);
void reverse_v_ref(vector <string>& v);
vector<string> reverse_v(vector <string> v);

int main()
try{
    vector <int> v;
    fibonacci (1, 2, v, 4);
    reverse_v_ref (v);
    reverse_v (v);
    print_v ("fibonacci", v);
    return 0;
}
catch(runtime_error& e)
{
    cerr << "runtime error: " << e.what() << '\n';
    return 1;
}


void print_v(string label, const vector <int>& v)
//print vector
{
    cout << label << " vector: ";
    for (const int& e : v) cout << e << " ";
    cout << '\n';
}

void fibonacci(int x,int y, vector <int>& v, int n)
//create a vector of fibonacci numbers starting with x and y, having n elements
{
    int increment, value;
    if (x > y) increment = x-y;
    else if (x < y) increment = y-x;
    else runtime_error("fibonacci: x and y can't be equal");

    value = x;

    for (int i = 0; i < n; i++)
    {
        value += increment;
        v.push_back(value);
    }
    return;
}

void reverse_v_ref(vector <int>& v)
//reverses the vector given as argument, changes the argument
{
    for (int i = 0; i < v.size()/2; i++)
    {
        swap(v[i], v[v.size()-(i+1)]);
    }
}

vector<int> reverse_v(vector <int> v)
//returns a reversed vector, doesn't change the argument
{
    for (int i = 0; i < v.size()/2; i++)
    {
        swap(v[i], v[v.size()-(i+1)]);
    }
    return v;
}

void reverse_v_ref(vector <string>& v)
//reverses the vector given as argument, changes the argument
{
    for (int i = 0; i < v.size()/2; i++)
    {
        swap(v[i], v[v.size()-(i+1)]);
    }
}

vector<string> reverse_v(vector <string> v)
//returns a reversed vector, doesn't change the argument
{
    for (int i = 0; i < v.size()/2; i++)
    {
        swap(v[i], v[v.size()-(i+1)]);
    }
    return v;
}