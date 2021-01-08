#include "vector.h"

//copy constructor
vector::vector (const vector& arg)
	:sz{arg.sz}, elem{new double[sz]}
{
	std::copy (arg.elem, arg.elem + arg.sz, elem);
}

//copy assignment
vector& vector::operator= (const vector& arg)
{
	double* n = new double[arg.sz]; 
	std::copy (arg.elem, arg.elem + arg.sz, n); //copy all the elements from a to the newly allocated array
	delete[] elem; //delete the previous value held by elem (remember that it's an ASSIGNMENT, not an INITIALIZATION)
	elem = n; //set the elem (of the current vector) to the argumen's elem
	sz = arg.sz;
	return *this; //return a self-reference
}

//move constructor
vector::vector (vector&& arg)
	:sz{arg.sz}, elem{arg.elem}
{
	arg.sz = 0;
	arg.elem = nullptr;
}

//move assignment
vector& vector::operator= (vector&& arg)
{
	delete[] elem;
	elem = arg.elem;
	sz = arg.sz;
	arg.elem = nullptr;
	arg.sz = 0;
	return *this;

}

double& vector::operator[] (int n)
{
	if(n < sz && n >= 0) return elem[n];
	else throw std::runtime_error("vector: index out of range ([] operator)");
}

double vector::operator[] (int n) const
{
	if(n < sz && n >= 0) return elem[n];
	else throw std::runtime_error("vector: index out of range (const[] operator)");
}

std::ostream& operator<< (std::ostream& ostr, const vector& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		ostr << v[i] << " ";
	}
	return ostr;
}

int main()
try{
	vector a(6);
	for (int i = 0; i < a.size(); i++)
		a[i] = i;
	
	std::cout << a << "size: " << a.size();
}
catch(std::exception& e)
{
	std::cerr << "error: " << e.what() << "\n";
	return 1;
}
catch(...)
{
	std::cerr << "unknown error" << "\n";
	return 2;
}
