//This file is meant to organize learning of C++ past the basics

//----------- 
// Keywords   
//----------- 

//auto: tells compiler to infer the type of a variable (type inference/deduction) [C++14]
audo dub{ 5.0 };                 //works with literals
auto sum { add(5, 6) };          //works with function returns
auto add(int x, int y) {}        //can be a return type (Avoid for maintainability)
auto add(int x, int y) -> int {} //trailing returns, for style 
			         //Pro(s): saves typing, styling
			         //Con(s): possible ambiguity
				 //NOTE: in C++20, auto on parameters serves as a template
//extern



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
	//Random access:
		//Bidirectional
			//Forward
				//Input: can only be used in single-pass algorithms, each el accessed once
				    //used for sequential input operations
                    //cannot be used to assign
                //Output: like Input iterators, cannot access values, but get assigned values    
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
    
