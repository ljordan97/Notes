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
// Templates
//------------



//------------
// Iterators
//------------

//Iterators are pointer like objects that point to elements within a container
//they handle functionality for moving through containers

//five categories of iterators
	//Random access:
		//Bidirectional
			//Forward
				//Input: can only be used in single-pass algorithms, each el accessed once
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

