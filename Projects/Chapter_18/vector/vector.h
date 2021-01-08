#include <iostream>
#include <sstream>
class vector
{
	int sz;
	double* elem;

public:
	//constructor	
	explicit vector (int size)
		:sz{size}, elem{new double[size]}
	{
		for (int i = 0; i < size; i++)
			elem[i] = 0; // initialize each element to 0
	}

	//{} initialization
 	explicit vector (std::initializer_list<double> lst)
		:sz{lst.size()}, elem{new double[sz]}
	{
		std::copy (lst.begin(), lst.end(), elem);
	}

 	vector (const vector& arg); //copy constructor
	vector& operator= (const vector& arg); //copy assignment

	vector ( vector&& arg); //move constructor
	vector& operator= (vector&& arg); //move assignment

	double& operator[] (int n);
	double operator[] (int n) const;

	//destructor
	~vector()
	{
		delete[] elem;
	}

	int size() const { return sz; }
	//double* get_vector () const { return sz; }
	//friend std::ostream& operator<< (std::ostream& ostr, vector v);
};

std::ostream& operator<< (std::ostream& ostr, const vector& v);