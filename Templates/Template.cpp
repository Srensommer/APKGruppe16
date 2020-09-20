#include "Template.h"
#include <iostream>

//Utility funcs
template <typename T, typename U>
T* myfind(T* first, T* last, const U& v) 
{
	for (;first != last; first++)
	{
		if (*first == v) return first;
	}
	return last;
}

//Exercise 2.2
template <typename T, typename V>
T** myfind(T** first, T** last, const V& v)
{
	for (; first != last; first++)
	{
		if (*first && **first == v) return first;
	}
	return last;
}



//Stupid stuff for debugging
template <typename T>
void PrintLortet(T* first, T* last)
{
	for (; first != last; first++)
	{
		std::cout << *first << std::endl;
	}
}


int main() 
{
	MyArray<int, 10> intArr;
	intArr.fill(3);
	std::cout << "Size of array is: " << intArr.size() << std::endl;
	std::cout << "Index 4's value: " << intArr[4] << std::endl;
	std::cout << "Looking for '3'? " << (myfind(intArr.begin(), intArr.end(), 3) 
		!= intArr.end() ? "found " : "sry no") << std::endl;
	//Code will work if we change 3 to 3.0, because it is then a double, and the compiler won't have to do any implicit conversions
	//This works because we changed the myfind interface and implementation to take another template parameter
	MyArray<double, 10> doubleArr;
	std::cout << "Looking for '3'? " << (myfind(doubleArr.begin(), doubleArr.end(), 3.0)
		!= doubleArr.end() ? "found " : "sry no") << std::endl;
	//Now implicitely casts the ints inserted with fill to doubles.
	
	//Ex. 1.4, this works, as the default copy constructor works on two arrays are same exact type
	//MyArray<int, 10> intArr;
	//MyArray<int, 10> _intArr(intArr);

	//We want to make this work
	intArr.fill(3);
	doubleArr = intArr;
	MyArray<double, 10> newArray = intArr;
	std::cout << "Looking for '3'? " << (myfind(doubleArr.begin(), doubleArr.end(), 3.0)
		!= doubleArr.end() ? "found " : "sry no") << std::endl;

	//This is done by making a "Fixed" copy constructor that implicitily converts from one to the other.
	//This is also desireable to be implemented in the overloaded assignment operator
	//Arrays that are not same lenght are also to be handled.
	
	//Exercise 2.2
	MyArray<std::string*, 6> my;
	my[5] = new std::string("Hello"); // Assuming that my is a MyArray of string pointers
	std::cout << *my[5] << std::endl;
	std::cout << " Looking for 'Hello'? " << (myfind(my.begin(), my.end(),
		std::string("Hello")) != my.end() ? " found " : "sry no") << std::endl;


	
	//Stupid stuff for debugging
	doubleArr[2] = 2;
	PrintLortet(doubleArr.begin(), doubleArr.end());
	PrintLortet(newArray.begin(), newArray.end());

}
