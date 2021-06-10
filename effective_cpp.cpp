#include <iostream>

//
// BACKGROUND / misc
//

std::size_t numDigits(int number);
//size_t = unsigned type used to count, used by operator[] funcs in vector
//...deque, and string
//the signature of numDigits is std::size_t (int)
//i.e. "function taking an int and returning a size_t

//for structs and classes, initialization is performed by constructors
//default constructor = no arguments (no param or all default params)

//use explicit for constructors, prevents unexpected type conversions
//when implicit conversion gains bid width = promotion e.g. float to double, int to long
long{ 34 };
//integral promotion: convert data shorter than int to an int (if possible) or unsigned int
//floating point promotion: convert float to double
//promotion is always safe, no data loss

//numeric conversion: converting longer type to shorter type, or between different types
double d{ 3 }; //different types
short s{ 2 }; //larger to smaller within same family
//may result in data loss, or overflow
//note: float can support about 7 sigfigs, double can support about 9

//copy constructor
class W{
    public:
        explicit W();
        W(const W& rhs); //copy constructor, inits obj by using diff obj of same type
	W& operator=(const W& rhs); //copy assignment operator, assigns obj a val of another obj
};

W w1;
W w2(w1); //invoke copy constructor
w1 = w2; //invoke copy operator assignment
W w3 = w2; //! NOT ASSIGNMENT invokes copy constructor bc a new obj is created
	//copy constructors are important for passing obj by value to function
	//function must copy the arg, and will use the CC to do so
	    //NOTE: usually not good to pass user defined types by value, pass by ref to const

//STL = standard template library, devoted to containers such as vector, list, set, map
//...iterators (vector<int>::iterator, set<string>::iterator
//...algorithms (for_each, find, sort, etc. 
//...and related functionalities (objs that act like functions, bc they overload operator())

//interface: a function's signature OR the accessible members of a class OR valid expressions
//...for a templates type parameter

//client: direct user of code, could also be whatever makes a function call or uses a class

//ctor = constructor
//dtor = destructor




//
// CHAPTER 1 NOTES
//

//ITEM 1
//C++ has many paradigms of programming that can be very different
//thus, its best to think of it as a federation of sublanguages. Be aware of the boundaries
//between them, and when you cross those boundaries, because they each have their own set of 
//rules

//sublanguages:
//C: blocks, statements, preprocessor, built-in types, arrays, pointers, etc.
//Object oriented C++: classes, polymorphism, inheritance, encapsulation, virtual funtions
//Template C++: introduce new paradigm: template metaprogramming
//The STL: it is for templates, but has particular implementations, with conventions to follow

//ITEM 2
//preprocessor bad, const, enums, and inlines good
//why? #deinfes are replaced by their values, and make tracking errors with them very difficult
	//especially when using headers you didnt write
	//also, they don't get entered into the symbol table
//instead of #DEFINE ASPECT_RATIO 1.653, use const double AspectRatio = 1.653
	//does the same thing, and will be entered into the symbol table, and seen by compiler
	//will also limit the number of copies of 1.653 to 1, saving mem
//special considerations:
	//case: need constant pointer and constant value in a header
		const char * const authorName = "Scott Meyers";
			//Note: prefer const std::string over a char array
	
	//case: need constant within class (for encapsulation purposes)
		//to limit copies made, must use static const 
		//in class definition, could put (in GamePlayer class)
		static const int NumTurns = 5;
			//this declaration is ok without a definition bc consts are given value
			//at their declaration
			//if compiler complains, use:
				const int GamePlayer::NumTurns;
		//may not work for older compilers, in which case declare in header, define in
		//...implementation (used to be illegal to provide initial value for static 
		//...class member in its declaration)
		//NOTE: in-class declaration is only for constant, integral types
		//but if you need value of const at compile time of the class, use the enum hack
	//enum hack:
		//values of enumerated type can be used as ints (lol)
		//in class def, 
		private:
		     enum { NumTurns = 5 }; 
			//not legal to take address of enum, just like #DEFINE
		        //is legal to take address of a const, what cases need constraint??
			//NOTE: constants are not reserved memory unless referenced or ptr
				//bad compilers might do this, if they do, use the enum hack 
		    int scores[NumTurns];
//inline functions will give all the efficient of a function-like macro, but with more 
//predictale behavior, and the ability to control scope

//ITEM 3
//make use of const as much as possible
//unique in that it can communicate to compilers and programmers that a value should not change
//ensures that your design constraint is enforced
const int * pti; //what's pointed to is constant
int const * pti2; //what's pointed to i constant
int * const pti3; //the pointer itself (address) is constant
int const * const pti4 // the address and value are both constant
//note for the STL: iterators act like T* pointers (they are modeled on them)
//so a const iterator like is like a constant pointer instead of a pointer to constant
const std::vector<int>::iterator iter; // address will not change
//if you want to make sure the value doesnt change, use this
std::vector<int>::const_iterator; //value cannot change
//consts can be used for any part of a function, but usually not for returns
//there are cases when const returns make sense, like operator*
//if return was not constant, the user could do this
(a * b) = c //efffectively reassigning the result of multiplication to another var

//Const member functions
int getValue() const { return value; } 
//when objects in the class are const, only const member functions can be used with it
//they ensure to not modify the state of the object
//can also overload functions based on const-ness
//they also enable the use of pass-by-reference-to-const
//remain careful to check for logical constness
//e.g. a const object has a const pointer member, the pointed value gets changed
	//this object retains bitwise constness, but not logical
	//i.e. be careful with pointers in const objects
		//e.g. textblock-like class that stores start of array
//logical constness says its ok to modify the bits of an object as long as the client cant detec
//but compilers wont allow this
//UNLESS: you use mutable on non-static data members in a const class
class CTextBlock {
	public:
		std::size_t length() const; //return length of text block (must change length)
	private:
		char *pText;
		mutable std::size_t textLength;
		mutable bool lengthIsValid;
};

std::size_t length() const{
	if(!lengthIsValid){
		textLength = std::strlen(pText); //only fine with mutable
		lenghtIsValid = true; //only fine with mutable
	}
}
//overloaded member functions for const support: avoiding duplication
//for the code that is reused for both const and non const,
//simply cast the non const to const, call the member function inside the non-const def
//and then un cast the return value. use
const_cast<char&>(static_cast<const TextBlock&>(*this)[position])

//ITEM 4
//initialize objects before use!
//easy for non-member objects
//for member objects, make sure the constructor intializes every value!
//assignment != initialization
	//assigning member data based on constructor arguments is not guaranteed to init
	//use member initialization lists instead
		//std::string name; calls a default constructor for string
			//this will be simply reassigned in the class constructor (waste)
		//using member init lists avoid the default call, much more efficient
		//doesn't really make a difference for built in types
//for classes with multiple constructors, and lots of member data
	//not unreasonable to have constructors call a private function that does assignment
		//for data members where assignment works well
//base classes are initializaed before derived
//data members are initialized in the order they are declared
	// (no matter the order of member init list) don't do this though
//can't define the relative order of initialization of non-local static objects in different
//translation units. 
//i.e. static objects outside function scope in different object files
//translation unit = source code giving rise to a single object file
//e.g. FileSystem class object tfs declared at global scope
//client creates Directory class in another file (diff translation unit)
//Dir class will use the tfs object, which may not have been defined yet at runtime
//solution: move non-local static objects into its own function, and declare it static there
//then return a reference to that object, and have clients use that function
//this makes sure the object is initialized (Dir class use of tfs will call function)
//lends itself to singleton pattern, as only 1 tfs object should be used by any and all clients
//bonus: if the function for the static object isn't used, it never gets created (and wont need
// to be destroyed
//such functions make good inline candidates due to their simplicity
//create a class object, return ref to it
//there is still possible initialization issues if this were multithreaded,
//but this can be solved by calling all ref functions in the single thread init part
