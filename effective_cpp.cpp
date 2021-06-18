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

//ITEM 5
//Know what functions C++ silently calls
//Empty classes are not really empty
//C++ generates a constructor, destructor, and copy constructor, and a copy assignment operator
//if needed
class Empty{};
Empty eq; //constructor generated (and also destructor)
Empty e2(e1); //copy constructor generated
e2 = e1; //copy assignment operator generated

//the generated destructor is non-virtual (unless formed for inherited class whose base-class 
//itself has declared a virtual destructor)

//the generated copy constructor and operator simply copy each non-static data member
//the generated copy constructor will initialize each member based on that member type's 
//constructor
	//i.e. objects with fields that are strings will call the string constructor
	//for integral types, bits are just copied from object 1 to object 2
//compiler can refuse to generate the operator if it doesnt make sense
//i.e. when member data is const, or a reference, or copy assignment operator is inherited from a base class which made it private

//ITEM 6
//explicitly dis-allow the use of compiler-generated functions you do not want
//implicitly defined copy constructors don't always make sense
//what if each object is supposed to be unique?
//how to fix this?
//declare the copy constructor and copy assignment operator private
	//they wont be generated automatically, and wont be accessible to new objects
		//unless they are member and friend functions
//TRUE FIX: declare them private, and do not define them
	//but then must be aware that errors from calls are actually attmempted copying
//you can also create an uncopyable class with a constructor and destructor, then privately 
//define the copy constructor and copy assignment operator 
	//make your class inherit from uncopyable
		//this moves the error up from link time to compile time!

//ITEM 7
//declare destructors virtual for polymorphic base classes
	//base classes with many derived types
//when a derived class object is deleted through a base class pointer, results are undefined
//the derived part of the object is never destroyed (makes sense)

//e.g. factory function in base class, returns a base class pointer to derived object
//factory function is called, and in the same scope deleted
//since it is a base class pointer, the base class destructor will run
//i.e. the derived destructor will never run
//the derived bits will be left over, i.e. a partially destroyed object
//easy way to leak, and/or corrupt data structures

//very easy to avoid this, just make the base class destructor virtual
//but if extending a class, look for virtual functions
	//if they aren't there, the class probably isn't meant to function as a base
		//having a virtual destructor in thiscase is probably a bad idea
//derived objects should carry info about which virtual functions are needed
	//this happens at runtime
	//this info lives in a vptr, "virtual table pointer"
		//points to an array of function pointers called the vtbl "virtual table"
		//each class with virtual functions has a vtbl
			//this increases the size of each object by 32 bits on 32b arch
				//by 64bits on a 64b arch
	//if an unintended base class had objects that were 64 bits, they could fit in a single
	//register, and easily passed between languages, to C or FORTRAN
		//these don't have the vptr, and so cannot receive objects naturally
			//would need to compensate for the vptr (unportable)
//rule of thumb: declare a base-class destructor virtual if and only if there's at least one 
//virtual function


//note: extending string bad, it doesn't have a virtual destructor or any virtual functions
//NOTE: all STL containers lack a virtual destructor
//there should be a way to restrict inheritance..is it possible to have a private constructor?
	//answer, yes it is, but friends can still use it
	//named constructor idiom
		//all varying constructors listed as private or protected, and are accessed
		//by calling a public static function
	//if using a pure virtual destructor, MUST have a definition for it
	//note on destructors: most-derived is called first, then goes down to base
		//this is why pure virtuals still need a definition

//ITEM 8
//Prevent exceptions from leaving destructors
//case: a vector of Widget objects is destroyed, so a destructor is called for each Widget
//suppose one destructor call throws an exception, and a second one throws too 
//C++ does not allow multiple exceptions. execution will either terminate or be undefined
	//can try-catch destructors to terminate the program
DBConn::~DBConn()
{
    try{ db.close(); }
    catch(...) {
	//make log entry that call to close failed
	std::abort(); //make sure the program terminates
    }

	//can swallow the exception (bad idea in general)
	//same as above, but without the abort
	//can have a derived function to close the base object (resource manager)
	//it can keep track of if the close was successful, and report it to client
	
	//transfer responsiblilty of closing base object from the derived destructor, to the 
	//client
		//but have backup sub-destructor in case they dont
	
//summary: try not to have destructors that throw exceptions
	//if functions are used that can throw, make sure to try-catch them
		//then swallow or terminate
	//move sub-destruction to regular member function, so client can react to errors

//ITEM 9
//don't call virtual functions during construction or destruction
//they don't do what you think when inside constructors or destructors

//case: you have a base class Transactions for all types of stock transactions
//all transactions must be auditable, so create a logTransaction function
	//this is virtual because its type-dependent
//if one wanted to log the creation of an object, they'd do it in the constructor,
	//resulting in a call to a virtual function inside a constructor
//when creating a derived object, it will call the base constructor first
	//which then calls the virtual log function, but the object is of base type atm
//same logic applies to destructors, because derived members get deleted, then the 
//base constructor is called - it's just a base object at that point

//if virtual functionality is needed at construction, simply make the necessary function 
//non-virtual, but have it require information from the derived class
//in the constructor of the derived class, when the base constructor is called, invoke the 
//function, and have it return into the args of the base constructor, so that it may use 
//the derived information
//i.e. have a private, static, helper function to pass info to the base constructor


//ITEM 10
//Have assigment operators return a reference to *this
//case: 
int x, y, z;
x = y = z = 15;
//is the same as
x = (y = (z = 15));
//assignments are "right-associative", returing a reference to their left-hand argument

//we should follow this convention when implementing assignment operators on user-defined types
Widget& operator=(const Widget& rhs)
{
    ...
    return *this; //return the left-hand object (left hand invokes operator)
}

//ITEM 11
//handle assignment to self in operator=
//"this looks silly, but is legal, so rest assured clients will do it"
//assignment isn't always easily recognizable
//remember base class references could point to a derived class object

//case: a resource-managing class for a bitmap
//it holds a raw pointer to a Bitmap object
class Widget {
    ...
private:
    Bitmap *pb;
};

//when assignment happens, the member data needs to be overwritten, but what happens during self assignment?
Widget& Widget::operator=(const Widget& rhs)
{
    delete pb;                 //if self assignment is happening, the result is a pointer to a deleted object!
    pb = new Bitmap(*rhs.pb);
    return *this;
}

//how to fix? Throw in an identity test in the assignment operator definition
//new assignment
Widget& Widget::operator=(const Widget& rhs)
{
    if(this==&rhs) return *this; //simply self assign 
    delete pb; //now safe
    pb = new Bitmap(*rhs.pb); //potentially unsafe (if excpetion thrown), pb will still hold a pointer to a deleted object
			      //like if there's not enough memory to allocate
			      //here, a new Bitmap object is created, and then assigned to another value
				//this invokes Bitmap's copy constructor, which could also throw an exception
			      //this creates a toxic pointer, which can't be safely deleted or even read
    return *this;
}

//how to fix? luckily, excpetion safe copy assignment is usually self-assignment safe as well
Widget& Widget::operator=(const Widget& rhs)
{
   Bitmap *pOrig = pb;       //save old copy
   pb = new Bitmap(*rhs.pb); //even if an exception is thrown here, pb remains unchanged
   delete pOrig;             //delete only after info has been copied
   return *this;
}

//this result is totally safe, but not super efficient (neither is the identity test)
//judge the frequency with which self assignment could occur, and choose the best option from there

//an alternative
class Widget {
   ...
   void swap(Widget& rhs); //swap *this' and rhs' data
   ...
};

Widget& Widget::operator=(const Widget& rhs)
{
   Widget temp(rhs); //note: this would happen implicitly if the parameter was pass-by-value, instead of const
   swap(temp); //swap this and rhs 
   return *this; //return invoking object\

}


//ITEM 12
//Copy all parts of an object

//only two functions *should* copy objects: the copy constructor, and copy assignment operator
//we know that these can be auto-generated if ommitted from class definitions
//the auto-generated versions copy all member data of an object

//if you are declaring your own copy functions, the compiler will not know if you don't copy all member data

//case: you define a copy constructor and copy assignment operator, and they copy all member data
//when you add a data member, these don't update automatically, and the compiler won't let you know 

//conclusion: UPDATE COPY FUNCTIONS ANY TIME A DATA MEMBER IS ADDED
	//update the constructor too

//insidious way to run into this problem: 
//an inherited class' copy constructor does not call the base class copy constructor first
//so unless all base member data is copied in the derived class' copy constructor, not all member data is being copied

//good idea: call the base class copy constructor inside the derived class' copy constructor (member init list)

//also make sure to call the base class constructor inside the derived class constructor (or member init list)
//otherwise, the base object will be constructed with default arguments

//note: though tempting, DON'T have one copy function call the other
	//can avoid duplication by having a private init function that both can call
