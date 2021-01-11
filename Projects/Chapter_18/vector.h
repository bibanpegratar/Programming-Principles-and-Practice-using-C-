//This version of vector allocates memory in the constructor using std::allocator
//	- it has been observed that it is slightly slower than allocating memory directly on the free store but
//	- allows initialization for type T that doesnt have a default constructor, by letting the user specify the default value
//But does it make sense to provide this ? The user that defined T should provide a default constructor for that class if he wants to use it with a vector anyway, so there's 
//no point in doing all of this, except that classes with no default constructors cant be used to initialize a vector (except with {} notation )

//The vector_base class makes everything a bit more complicated to read, but we ensure RAII for vector
//Another solution would be to use smart pointers, will try that later
#include <initializer_list>
#include <algorithm>
#include <memory>

struct out_of_range {};

template<typename T, typename A>
struct vector_base
{
	A alloc; 	//allocator
	T* elem; 	//start of allocation
	int sz;  	//number of elements
	int space;  //amount of allocated space
	vector_base(int n)
		:elem{alloc.allocate(n)}, sz{n}, space{n} {}

	void construct(T def) {for (int i = 0; i < sz; i++) alloc.construct(&elem[i], def); }

	~vector_base() {alloc.deallocate(elem, space); }
};

template<typename T, typename A = std::allocator<T>> //requires Element<T>()
class vector : public vector_base<T,A>
{
	void reserve(int newspace);

public:
	
	vector (int size, T def = T())
		: vector_base<T,A>(size)
	{
		this->construct(def); // initialize each element to 0		
	}

	//{} initialization
 	vector (std::initializer_list<int> lst)
		:vector_base<T,A>(lst.size())
	{
		std::copy (lst.begin(), lst.end(), this->elem);
	}

	//destruction of elements is managed in vector_base

 	vector (const vector& arg); //copy constructor
	vector& operator= (const vector& arg); //copy assignment

	vector ( vector&& arg); //move constructor
	vector& operator= (vector&& arg); //move assignment

	//subscript operators
	T& operator[] (int n) { return this->elem[n]; }
	const T& operator[] (int n) const { return this->elem[n]; }

    T& at(int n);
    const T& at(int n) const;

	int size() const { return this->sz; }
	int capacity() const { return this->space; }

	void resize(int newspace, T def = T()); //growth
	void push_back(const T& d);
	void erase();
};

//copy constructor
template<typename T,typename A> 
vector<T,A>::vector (const vector& arg)
{
	this->sz = arg.sz;
	this->elem = new T[arg.size()];
	std::copy (arg.elem, arg.elem + arg.sz, this->elem);
}

//copy assignment
template<typename T,typename A> 
vector<T,A>& vector<T,A>::operator= (const vector& arg)
{
	if (this == &arg) return *this; //self-assignment, do nothing

	if (arg.sz <= this->space) // enough space, no need for extra allocation
	{
		for (int i = 0; i < arg.sz; i++) this->elem[i] = arg.elem[i]; //copy elements
		this->sz = arg.sz;
		return *this;
	}

	T* n = new T[arg.sz]; 
	for (int i = 0; i < arg.sz; i++) n[i] = arg.elem[i];  //copy all the elements from a to the newly allocated array
	delete[] this->elem; //delete the previous value held by elem (remember that it's an ASSIGNMENT, not an INITIALIZATION)
	this->space = arg.sz;
	this->sz = arg.sz;
	this->elem = n; //set the elem (of the current vector) to the argumen's elem
	return *this; //return a self-reference
}

template<typename T, typename A>
T& vector<T,A>::at(int n)
{
    if (n < 0 || n >= this->sz) throw out_of_range();
    return this->elem[n];
}

template<typename T, typename A>
const T& vector<T,A>::at(int n) const
{
    if (n < 0 || n >= this->sz) throw out_of_range();
    return this->elem[n];  
}

//move constructor
template<typename T,typename A> 
vector<T,A>::vector (vector&& arg)
{
	this->sz = arg.sz;
	this->elem = arg.elem;
	arg.sz = 0;
	arg.elem = nullptr;
}

//move assignment
template<typename T,typename A> 
vector<T,A>& vector<T,A>::operator= (vector&& arg)
{
	delete[] this->elem;
	this->elem = arg.elem;
	this->sz = arg.sz;
	arg.elem = nullptr;
	arg.sz = 0;
	return *this;

}

template<typename T,typename A> 
void vector<T,A>::reserve(int newspace)
{
	if(newspace <= this->space) return; //never allocate less memory
	T* p = this->alloc.allocate(newspace);
	for(int i = 0; i < this->sz; i++) this->alloc.construct(&p[i], this->elem[i]); //copy the elements from the old array to the new one
	for(int i = 0; i < this->sz; i++) this->alloc.destroy(&this->elem[i]);
	this->alloc.deallocate(this->elem, this->space);
	this->elem = p; //point elem to the newly allocated array p
	this->space = newspace;
}

template<typename T,typename A> 
void vector<T,A>::resize(int newspace, T def)
//make the vector have newsize elements
//initialize each new element with a default value 
//	-default T value 
//	-or a value d if specified
{
	reserve(newspace);
	for (int i = this->sz; i < newspace; i++) this->alloc.construct(&this->elem[i],def);
	this->sz = newspace;
}

template<typename T,typename A> 
void vector<T,A>::push_back(const T& d)
{
	if(this->space == 0) //if there's no space (default constructor)
		reserve(8); //reserve space for 8 elements

	else if (this->sz == this->space) //if the space is equal to the size
		reserve(this->space * 2); //double the space

	this->alloc.construct(&this->elem[this->sz], d); // add d at the end
	++this->sz; // increase size by 1
}