//This version of vector allocates memory in the constructor using std::allocator
//	- it has been observed that it is slightly slower than allocating memory directly on the free store but
//	- allows initialization for type T that doesnt have a default constructor, by letting the user specify the default value
//But does it make sense to provide this ? The user that defined T should provide a default constructor for that class if he wants to use it with a vector anyway, so there's 
//no point in doing all of this, except that classes with no default constructors cant be used to initialize a vector (except with {} notation )
#include <initializer_list>
#include <algorithm>
#include <memory>

struct out_of_range {};

template<typename T, typename A = std::allocator<T>> //requires Element<T>()
class vector
{
	A alloc;
	int sz; //number of elements in the vector
	T* elem;
	int space; //the maximum number of elements the vector can hold

	void reserve(int newspace);

public:
	
	//constructors
	vector() : sz{0}, elem{nullptr}, space{0} {}

	vector (int size, T def = T()) :sz{size}, elem{alloc.allocate(size)}, space{size}
	{
		for (int i = 0; i < size; i++) alloc.construct(&elem[i], def); // initialize each element to 0		
	}

	//{} initialization
 	vector (std::initializer_list<int> lst)
		:sz{lst.size()}, elem{alloc.allocate(lst.size())}, space{lst.size()}
	{
		std::copy (lst.begin(), lst.end(), elem);
	}

	//destructor
	~vector()
	{
		for(int i = 0; i < sz; i++) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);
	}

 	vector (const vector& arg); //copy constructor
	vector& operator= (const vector& arg); //copy assignment

	vector ( vector&& arg); //move constructor
	vector& operator= (vector&& arg); //move assignment

	//subscript operators
	T& operator[] (int n) { return elem[n]; }
	const T& operator[] (int n) const { return elem[n]; }

    T& at(int n);
    const T& at(int n) const;

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newspace, T def = T()); //growth
	void push_back(const T& d);
	void erase();
};

//copy constructor
template<typename T,typename A> 
vector<T,A>::vector (const vector& arg)
	:sz{arg.sz}, elem{new T[sz]}
{
	std::copy (arg.elem, arg.elem + arg.sz, elem);
}

//copy assignment
template<typename T,typename A> 
vector<T,A>& vector<T,A>::operator= (const vector& arg)
{
	if (this == &arg) return *this; //self-assignment, do nothing

	if (arg.sz <= space) // enough space, no need for extra allocation
	{
		for (int i = 0; i < arg.sz; i++) elem[i] = arg.elem[i]; //copy elements
		sz = arg.sz;
		return *this;
	}

	T* n = new T[arg.sz]; 
	for (int i = 0; i < arg.sz; i++) n[i] = arg.elem[i];  //copy all the elements from a to the newly allocated array
	delete[] elem; //delete the previous value held by elem (remember that it's an ASSIGNMENT, not an INITIALIZATION)
	space = arg.sz;
	sz = arg.sz;
	elem = n; //set the elem (of the current vector) to the argumen's elem
	return *this; //return a self-reference
}

template<typename T, typename A>
T& vector<T,A>::at(int n)
{
    if (n < 0 || n >= sz) throw out_of_range();
    return elem[n];
}

template<typename T, typename A>
const T& vector<T,A>::at(int n) const
{
    if (n < 0 || n >= sz) throw out_of_range();
    return elem[n];  
}

//move constructor
template<typename T,typename A> 
vector<T,A>::vector (vector&& arg)
	:sz{arg.sz}, elem{arg.elem}
{
	arg.sz = 0;
	arg.elem = nullptr;
}

//move assignment
template<typename T,typename A> 
vector<T,A>& vector<T,A>::operator= (vector&& arg)
{
	delete[] elem;
	elem = arg.elem;
	sz = arg.sz;
	arg.elem = nullptr;
	arg.sz = 0;
	return *this;

}

template<typename T,typename A> 
void vector<T,A>::reserve(int newspace)
{
	if(newspace <= space) return; //never allocate less memory
	T* p = alloc.allocate(newspace);
	for(int i = 0; i < sz; i++) alloc.construct(&p[i], elem[i]); //copy the elements from the old array to the new one
	for(int i = 0; i < sz; i++) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	elem = p; //point elem to the newly allocated array p
	space = newspace;
}

template<typename T,typename A> 
void vector<T,A>::resize(int newspace, T def)
//make the vector have newsize elements
//initialize each new element with a default value 
//	-default T value 
//	-or a value d if specified
{
	reserve(newspace);
	for (int i = sz; i < newspace; i++) alloc.construct(&elem[i],def);
	sz = newspace;
}

template<typename T,typename A> 
void vector<T,A>::push_back(const T& d)
{
	if(space == 0) //if there's no space (default constructor)
		reserve(8); //reserve space for 8 elements

	else if (sz == space) //if the space is equal to the size
		reserve(space * 2); //double the space

	alloc.construct(&elem[sz], d); // add d at the end
	++sz; // increase size by 1
}