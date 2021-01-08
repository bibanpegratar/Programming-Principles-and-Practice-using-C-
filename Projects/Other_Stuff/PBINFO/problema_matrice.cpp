
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
istream& operator>> (istream& istr, vector< vector <int>>& v);
ostream& operator<< (ostream& ostr, const vector< vector <int>>& v);
int cmmdc(int a, int b);
int cmmdc_line(const vector<vector <int>> &v, int index);


int main()
try{
    ifstream fin {"input.txt"};
    if(!fin) throw runtime_error("failed to open input file");

    ofstream fout {"output.txt"};
    if(!fout) throw runtime_error("failed to open output file");

    int n, m;
    fin >> n >> m;
    vector <vector<int> > matrix (n, vector<int>(m,0));

    fin >> matrix;

    for(int i = 0; i < matrix.size(); i++)
        fout << cmmdc_line(matrix, i) << endl;

    return 0;
}
catch(runtime_error& e)
{
    cerr << "error: " << e.what() << "\n";
    return 69;
}

istream& operator>> (istream& istr, vector< vector <int>>& v)
{
    for(int a = 0; a < v.size(); a++)
    {
        for (int b = 0; b < v[a].size(); b++)
        {
            istr >> v[a][b];
        }
    }
    return istr;
}

ostream& operator<< (ostream& ostr, const vector< vector <int>>& v)
{
    for(int a = 0; a < v.size(); a++)
    {
        for (int b = 0; b < v[a].size(); b++)
        {
            ostr << v[a][b] << " ";
        }
        ostr << '\n';
    }
    return ostr;
}

int cmmdc_line(const vector<vector <int>> &v, int index)
{
    int c = v[index][0];
    for (int i = 1; i < v[index].size(); i++)
    {
        c = cmmdc(c, v[index][i]);
    }
    return c;
}

int cmmdc(int a, int b)
{
    while(a != b)
    {
        if(a > b) a = a - b;
        else b = b - a;
    }
    return a;
}
