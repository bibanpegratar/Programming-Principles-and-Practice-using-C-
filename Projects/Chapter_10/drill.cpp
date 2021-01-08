#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Point
{
    int x;
    int y;
};

std::ostream& operator<< (std::ostream& ost, const Point& p)
{
    ost << p.x << " " << p.y;
    return ost;
}

std::istream& operator>> (std::istream& ist, Point& p)
{
    ist >> p.x >> p.y;
    return ist;
}

bool operator== (const Point a, const Point b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!= (const Point a, const Point b)
{
    return !(a == b);
}


int main()
try{
    std::string input_file, output_file;

    std::cout << "Enter input filename: ";
    std::cin >> input_file;
    std::ifstream fin {input_file};
    if(!fin) throw std::runtime_error("input_file: cannot open file " + input_file);

    output_file = "mydata";
    std::ofstream fout {output_file};

    std::vector <Point> original_points;
    while(true)
    {
        Point p;
        if (!(fin >> p)) break;
        original_points.push_back(p);
    }

    for (Point p : original_points) fout << p << "\n";

    fout.close();
    std::ifstream fin2 {output_file};

    std::vector <Point> processed_points;
    while(true)
    {
        Point p;
        if (!(fin2 >> p)) break;
        processed_points.push_back(p);
    }

    for (int i = 0; i < original_points.size(); i++)
    {
        if (!(original_points[i] == processed_points[i])) throw std::runtime_error("Something's wrong!");
    }
    return 0;
}
catch (std::runtime_error& e)
{
    std::cerr << "error: " << e.what();
    return 1;
}
