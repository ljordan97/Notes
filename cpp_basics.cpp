#include <iostream>
#include <cmath>
#include <chrono> //time

//HOW TO COMPILE: 
// $ g++ cpp_basics.cpp //generates an output file a.out

//HOW TO EXECUTE OUTPUT FILES
// $ ./a.out

//LINKING, when multiple C++ files are used
// $ g++ main.cpp my_functions.cpp

//including headers
#include "cpp_basics.hpp"

int main(){ //every program needs main, houses instructions

	//classes: defined in header

	//
	// objects
	//

	Song castaways;
	castaways.

	//standard input and output
	std::cout << "Hello World!\n"; //cout = character output stream

	std::cin >> password

	//convert type (dub to int requires truncation)
	double weight1;
	int weight2;

	weight1 = 154.49;
	weight2 = (int) weight1;

	//
	// Vectors
	//

	std::vector<int> calories_today;
	//vector of strings
	std::vector<std::string> last_jedi
	// pre-size
	std::vector<double> location(2);

	//declare and initialize
	std::vector<double> location = {42.651443, -73.749302};

	//add element to end of vector
	std::vector<std::string> dna = {"ATG", "ACG"};
	dna.push_back("GTG"); //{"ATG", "ACG", "GTG"}

	//remove element from end of vector
	dna.pop_back(); //{"ATG", "ACG"}, NO RETURN VALUE

	//get size of a vector
	dna.size();

	//
	//Arrays
	//

	int favoriteNums[] = {7, 9, 15, 16};
	int favoriteNums[4];

	//
	//math
	//

	//exponents
	double eight = pow(2, 3); //double base, double exp

	//random
	// This seeds the random number generator:
  	srand (time(NULL));

  	//
  	//functions
  	//

  	//inline, tells compiler to insert function def at function call
  	//always do this when putting function defs in headers
  	inline 
	void eat() {
	 
	  std::cout << "nom nom\n";
	 
	}

	//overloading, to accept different types of params
	void print_cat_ears(char let) {
	  std::cout << " " << let << "   " << let << " " << "\n";
	  std::cout << let << let << let << " " << let << let << let << "\n";
	}
	 
	void print_cat_ears(int num) {
	  std::cout << " " << num << "   " << num << " " << "\n";
	  std::cout << num << num << num << " " << num << num << num << "\n";
	}

	//templates --- entirely created in header files
	template <typename T>
	T get_smallest(T num1, T num2) {
	  
	  return num2 < num1? num2 : num1;
	  
	}

	//time
	// Measure time taken for goodnight1():
  	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	return 0; //optional
}