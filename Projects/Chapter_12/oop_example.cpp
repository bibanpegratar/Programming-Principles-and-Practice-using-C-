#include <iostream>
using namespace std;
class Shape
{
    std::string name_p;

public:
    Shape (std::string name) : name_p{name} {};
    virtual ~Shape () {};
    
    void set_name (std::string name) { name_p = name; }
    std::string get_name () const { return name_p; }

    virtual double area() = 0;
};

class Circle : public Shape
{
    double* radius_p;
    constexpr double static pi = 3.143;

public:
    Circle (std::string name, double radius) : Shape(name), radius_p{new double(radius)} {}
    ~Circle() {delete radius_p;}
    double area() { return *radius_p * *radius_p * pi; }

};

int main()
{
    Shape* sh = new Circle{"circle1", 14}; //a pointer to a Shape; Circle is a Shape, so it works
    cout << sh->area(); //calling Circle's area()
    return 0;
}

