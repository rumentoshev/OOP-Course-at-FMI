#include <iostream>
#include <fstream>

void printTimeClear(size_t num)
{
	if (num < 10)
	{
		std::cout << "0" << num;
	}
	else
	{
		std::cout << num;
	}
}

//copied from: https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2003
size_t getFileSize(std::ifstream& f) {
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}