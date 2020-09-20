#include "SharedPtr.h"
#include <iostream>

class TestClass
{
private:
	int _x;
public:
	TestClass(int x) 
	{ 
		_x = x;
		std::cout << "TestClass just got made!" << std::endl; 
	}
	~TestClass() { std::cout << "TestClass just got destroyed!" << std::endl; }
	int const getX() { return _x; }
	void setX(int x) { _x = x; }
};


int main() 
{
	TestClass *a = new TestClass(2);
	TestClass *b = new TestClass(3);
	sharedPointerNamespace::SharedPtr<TestClass> sharedPtrTest(a);
	sharedPointerNamespace::SharedPtr<TestClass> sharedPtrTest2(sharedPtrTest);
	//Test af == operator
	if (sharedPtrTest == sharedPtrTest2)
	{
		std::cout << "Nonono this shouldn't be printed!" << std::endl;
	}
	std::cout << sharedPtrTest.count() << std::endl;
	return 0;
}