#include <iostream>
#include "MultiSet.h"


int main()
{
	std::cout << "DEMO" << std::endl;
	MultiSet a(4, 6);
	a.add(0);
	a.add(0);
	a.add(0);
	a.add(1);
	a.add(1);
	a.add(2);
	a.add(3);
	a.add(3);
	a.add(4);
	std::cout << "Multi set a in the memory:" << std::endl;
	a.printBits();
	std::cout << "   Numbers in a ->";
	a.printAll();
	std::cout << std::endl;
	MultiSet b(6, 3);
	b.add(0);
	b.add(0);
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(2);
	b.add(2);
	b.add(3);
	b.add(3);
	b.add(5);
	std::cout << "Multi set b in the memory:" << std::endl;
	b.printBits();
	std::cout << "   Numbers in b ->";
	b.printAll();
	std::cout << std::endl;
	std::cout << std::endl;
	// 2 2 4 2 1 0 1
	MultiSet result = DiffOfSets(a, b);
	std::cout << "Multi set result (diff of a and b) in the memory:" << std::endl;
	result.printBits();
	std::cout << "   Numbers in result ->";
	result.printAll();
	std::cout << std::endl;
	std::cout << std::endl;

	MultiSet result2 = IntersectionOfSets(a, b);
	std::cout << "Multi set result2 (intersection of a and b) in the memory:" << std::endl;
	result2.printBits();
	std::cout << "   Numbers in intersection ->";
	result2.printAll();
	std::cout << std::endl;
	std::cout << std::endl;
	
	a.writeToFile("test");
	MultiSet r3;
	r3.loadFromFile("test");
	std::cout << "Multi set r3 (read from file and same as a) in the memory:" << std::endl;
	r3.printBits();
	std::cout << "   Numbers in r3 ->";
	r3.printAll();
	std::cout << std::endl;
	std::cout << std::endl;

	MultiSet comp = r3.complementMultiSet();
	std::cout << "Multi set compliment (compliment set of r3) in the memory:" << std::endl;
	comp.printBits();
	std::cout << "   Numbers in compliment ->";
	comp.printAll();
	std::cout << std::endl;
	
	return 0;
}