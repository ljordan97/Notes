//This file is meant to organize learning of C++ past the basics

//----------- 
// Keywords   
//----------- 

//auto: tells compiler to infer the type of a variable (type inference/deduction) [C++14]
auto dub{ 5.0 };                 //works with literals
auto sum { add(5, 6) };          //works with function returns
auto add(int x, int y) {}        //can be a return type (Avoid for maintainability)
auto add(int x, int y) -> int {} //trailing returns, for style 
			         //Pro(s): saves typing, styling
			         //Con(s): possible ambiguity
				 //NOTE: in C++20, auto on parameters serves as a template

//explicit
//case: a class has a constructor that has 2 arguments. both have defaults
	//unexpected result: the constructor can be called with just one argument
		//so it serves as an implicit type conversion for objects with just one arg
			//an implicit conversion could happen from any overloaded operator
	//how to prevent? make the constructor explicit
		//this means it wont allow implicit conversions
		//objects must be cast to be compatible

//extern

//virtual
//use when derived classes should have specifically defined versions of functions
//pure virtual: base has no definition. derived objects MUST have an implementation
	//note: these result in abstract classes (can't be instantiated)
		//intended only to be used as a base

//------------
// Operators
//------------

//unary plus: invokes an implicit int conversion
uint_8 not_a_char = 155;
std::cout << not_a_char; //compiler might convert this to ascii, but it's an int
std::cout << +not_a_char; //tells the compiler to implicitly convert to int


//------------
//  Casting
//------------

//important for Type Safety
//C casts can have unpredictable results, as they can apply several casts that you dont see
//prefer C++ casts
static_cast<int>      //converts between similar types i.e. pointers or numerics
const_cast<int>       //adds or removes const or volatile
reinterpret_cast<int> //converts between pointers or between integral types and pointers
dynamic_cast<int>     //converts between polymorph(?) pointers or references in the same class
std::move:            //converts to an rvalue reference(?)
std::forward:         //converts to an rvalue reference
gsl::narrow_cast:     //applies a static_cast
gsl::narrow:          //applies a static_cast

// (?) GSL = Guideline Support Library - auto checks the rules of C++ core guidelines & profiles

// (?) lvalue - an expression that yields an object reference e.g. variable name, 
//              array subscript reference, a dereferenced pointer, or a function call that
//              returns a reference
//              Always has a defined storage region, so you can take its address
//              Functions are also lvalues, but only used in calls or getting address
//              Consts are still lvalues even though they cant be the target of assignment
//              Arrays are lvalues, but an address is an rvalue
//              Operators that produce lvalues: [] *(deref) & ++ -- = += etc. 
//              If casting a reference, an lvalue is produced (other casts are rvalues)
//              Functions that retrun a reference, return an lvalue (rvalue otherwise)
//              lvalue can be implicitly converted to an rvalue, but not vice versa

//(?) rvalue  - an expression that is NOT an lvalue e.g. literals, results of most operators,
//              and function calls that return nonreferences
//              does not necessarily have storage associated with it

//------------
// Templates
//------------

//notes:
//static variables in template functions have a different scope for each specific type used
//mixing types of arguments i.e. an int and a double in a return_max(), will cause a compiler
	//error due to ambiguity
//literals can be passsed to templates, and should be treated as rhvalues (const)

//template metaprogramming (recall funstruct on geeksforgeeks)
//e.g. a literal passed to struct which calculates 2 times the result of calling the same 
//struct with the literal minus 1, and a special template for 0 which equals 1
//this will compute the max of a given bit width in binary
//CALCULATION IS DONE AT COMPILE TIME (hence the meta)
//template metaprogramming is turing complete (lol)

//class templates
    // This would go into a header file such as "Array.h"
    template<typename T>
    class Array {
    public:
      Array(int len=10)                : len_(len), data_(new T[len]) { }
     ~Array()                          { delete[] data_; }
      int len() const                  { return len_;     }
      const T& operator[](int i) const { return data_[check(i)]; }
      T&       operator[](int i)       { return data_[check(i)]; }
      Array(const Array<T>&);
      Array(Array<T>&&);
      Array<T>& operator= (const Array<T>&);
      Array<T>& operator= (Array<T>&&);
    private:
      int len_;
      T*  data_;
      int check(int i) const {
        assert(i >= 0 && i < len_);
        return i;
      }
    };

    int main()
    {
      Array<int>           ai; //must be explicit about parameters you're instantiating
      Array<float>         af; //not needed for template functions
      Array<char*>         ac;
      Array<std::string>   as;
      Array<Array<int>>    aai; //note for prior to C++11, need space to prevent >>
      // ...
    }

//function templates
    template<typename T>
    void swap(T& x, T& y)
    {
      T tmp = x;
      x = y;
      y = tmp;
    }

    int main()
    {
      int         i,j;  /*...*/  swap(i,j);  // Instantiates a swap for int
      float       a,b;  /*...*/  swap(a,b);  // Instantiates a swap for float
      char        c,d;  /*...*/  swap(c,d);  // Instantiates a swap for char
      std::string s,t;  /*...*/  swap(s,t);  // Instantiates a swap for std::string
      // ...

      //for explicit function template calls (useful for promotions or no parameters)
        //alternative to this: promote the argument
        //also useful when mixing type of args
      swap<int>(i,j);          // type T will be int in this call
      swap<std::string>(s,t);  // type T will be std::string in this call
    }

//Notes: genericty = class template, parametrized type = class template (List<int>)
//don't use a template if observable behavior is different for different types

//template specialization: when implementation is different based on type, but observable 
//behavior is the same
    //can simply use a switch statement in the function
    switch (typeof(T)){
     case int:
         //yadda yadda
         break;
     case std::string
         //yadda yadda
         break;
     default:
         //normal yadda
            break;
    }

    //can also do this:
    template<typename T>
    void foo(const T& x)
    {
      // ...implementation details when T is not int
    }

    template<>
    void foo<int>(const int& x)
    {
      // ...implementation details when T is int
    }

     

//------------
// Iterators     [deprecated in C++17]
//------------

//Iterators are pointer like objects that point to elements within a container
//they handle functionality for moving through containers

//five categories of iterators
//useful because we dont need to worry about container size, which especially helps when changes
//useful for code reusability (e.g. changing a function from operating on a vectory (supports RA)
//to operating on a list (sequential only), because of iterator hierarchies, the same code can
//be used
//iterators are automatically changed when insertions are performed on the container
//or deletions
//useful functions
vector<int> ar = {1, 2, 3, 4, 5};
vector<int> ar1 = {10, 20, 30};
vector<int>::iterator ptr;

for (ptr = ar.begin(); ptr < ar.end(); ptr++){}
advance(ptr, 3) //increments iterator 3 times
auto it = next(ptr, 3) //returns iterator that would point to the position 3 ahead
auto it1 = prev(ptr, 3)
copy(first, last, d_first) //copies range defined by first to last, to new range starting at d
copy(ar1.begin(), ar1.end(), inserter(ar,ptr)); //inserter returns beginning of range to copy to
//given an array and an iterator

	//Random access:
	//useful for shuffling since arithmetic allowed
	//useful for accessing nth element
	//offset dereference allowed
	//relational operators allowed (they require arithmetic)
		//Bidirectional: similar to forward, but can be decremented
		//no arithmetic allowed, because these are still sequential only
                //still no lte or gte comparisons allowed
		//note: .end() returns a past then end element
		//useful for reverse copy
			//Forward: combination of input and output functionality
			//can be used in multipass
			//useful for copy/move functions that need LH and RH dereference
			//still unidirectional
			    //can increment
			    //cannot decrement
			    //no arithmetic (no offset dereference
				//Input: can only be used in single-pass algorithms, each el 
				//accessed once (these are constant)
				    //used for sequentially reading once each
				    //can be dereferenced
				    //can be incremented but not decremented
				    //pointed value can be swapped
                    		    //cannot be used to assign
				    //can check for equality but no lte or gte
				    //no arithmetic
InputIterator find (InputIterator first, InputIterator last, const T& val)
{
    while (first!=last) 
    {
        if (*first==val) return first;
        ++first;
    }
    return last;
}	
                		//Output: like Input iterators, cannot access values, but get 
				//assigned values    
				    //cannot access values, but can assign them
				    //for writing to containers
				    //single-pass only
				    //can be dereferenced as an LHV, to be assigned
				    // can be incremented
				    // can be swapped
				    //cannot be checked for equality
				    //for modifying existing containers
				    //no arithmetic

// Definition of std::move()
template 
OutputIterator move (InputIterator first, InputIterator last,
                     OutputIterator result)
{
    while (first!=last)
    {
        *result = std::move(*first);
        ++result;
        ++first;
    }
    return result;
}


std::vector<int> v = { 1, 2, 3 };
vector<int>::iterator i;
// Accessing the elements using iterators
    for (i = v.begin(); i != v.end(); ++i)
    {   
        cout << *i << " ";
    }   
//insert using iterator
i = v.insert(i, 5)
//erase using iterator
i = v.erase(i);
//increment the iterator position a specified number of times
advance(i, 3); 
//




//----------
// Vectors
//----------

vector<int> g1;

//Vectors are containers which are able to resize themselves automatically upon insert/delete
//elements are placed in contiguous storage
//data inserted at the end
	//the time it takes to do this varies
		//sometimes the array must be extended
	//deleting at the end is constant time
	//inserting / deleting in the middle is constant time
//useful functions
begin()
end()    //returns past-the-end element
rbegin() //reverse begin, returns a reverse iterator at last element
rend()   //reverse end, returns a reverse iterator pointing to before-the-end
cbegin() //constant iter pointing to first element in the vector
cend()   //constant iter pointing to past-the-end element
crbegin()
crend()
size()
max_size // max # of elements the vector could hold
capacity() // returns current storage space currently allocated (# of elements)
resize(n) //change size of vector to fit n elements
empty()  //bool return, true if vector is empty
shrink_to_fit() // reduces size to fit capacity, destroys elements past capacity
			//useful after a resize()? why would there be elements past
reserve()  // requests that the vector capacity be at least enough to contain n elements
		//this should be more optimized than allowing dynamic, 
			//and should be used if the theoretical max capacity is known beforehand
		//when vectors are resized, all elements are copied to new contiguous space
			//this can save SECONDS at 1e6
at(g) //returns reference to element at position g in the vector
front() //returns reference to first element in the vector
back() //returns reference to last element in the vector
data() //returns a direct point to memory array used by vector
insert(position, val) //inserts new elements before specified position
assign(arr, arr + size) //assigns array to a vector, from beginning to size specified
assign(InputIterator first, InputIterator last) //operates on itself,
assign(size_type n, const value_type& val) // initializes first n elements to val
v1.swap(v2)
emplace(const_iterator position, element) //insert element at position, reallocate if needed
//emplace can construct an object in the vector (strongly typed based on vector)
//as opposed to insert, which just copies objects into a vector (temp needed)
v.emplace(someIterator, 42, 3.1416);
v.insert(someIterator, Foo(42, 3.1416));




//-------
// Maps
//-------

#include <map>

//A type of associative container (like a python dictionary)
//Keys must be unique

map<int, int> gquiz1;
gquiz1.insert(pair<int, int>(1, 40));

map<int, int>::iterator itr; 
key = itr->first;
mapped = itr->second;

// assigning the elements from gquiz1 to gquiz2
map<int, int> gquiz2(gquiz1.begin(), gquiz1.end());

//useful functions
pair_insert(keyvalue, mapvalue)
erase(iterator position)
erase(const g) //remove by keyvalue g
find(key) //returns position of key value
upper_bound(key) // return closest iterator above
lower_bound(key) // return closest iterator below




//---------
// Arrays
//---------

#include <array>

//A container type for constant sized arrays, wraps around fixed size arrays
//Doesn't lose information of its length when decayed to a pointer (?)

// construction uses aggregate initialization
  // double-braces required
  array<int, 5> ar1{{3, 4, 5, 1, 2}};
  array<int, 5> ar2 = {1, 2, 3, 4, 5};
  array<string, 2> ar3 = {{string("a"), "b"}};

for (auto i : ar1)
    cout << i << ' ';

//useful functions
fill(val) //replaces every element with the given value




//--------//
// Loops  //
//--------//

//Range-based for loop (since C++11, changed in C++20)
// Iterating over whole array
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    for (auto i : v)
        std::cout << i << ' ';

// the initializer may be a braced-init-list
    for (int n : {0, 1, 2, 3, 4, 5})
        std::cout << n << ' ';

// Printing string characters
    std::string str = "Geeks";
    for (char c : str) 
        std::cout << c << ' ';

// Printing keys and values of a map
    std::map <int, int> MAP({{1, 1}, {2, 2}, {3, 3}});
    for (auto i : MAP)
        std::cout << '{' << i.first << ", " 
                  << i.second << "}\n";
//types of range based for iterators
	//normal iterators
		//temp variables that get handed elements by value
	for (int my_iterator : my_iterable) {
		my_iterator += 1;   		//only changes temp copy bc
		cout << my_iterator << " ";     //normal iterators are passed by value
	}

	//reference iterator
		//the iterator is a reference variable, so changes propagate
	for (int& my_iterator : my_iterable) {
		cout << my_iterator << " ";
	}

	//const iterators (passed by reference to const)
	for (const int& my_iterator : my_iterable) {
		cout << my_iterator << " ";
		//my_iterator += 1; //would cause an error
	}




//-----------------
// Smart Pointers
//-----------------

//instrumental to the RAII idiom (Resource Allocation Is Initialization)
    //objects on the stack own resources, which they must manage the memory of
	//smart pointers are deleted when they go out of scope
