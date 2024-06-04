#include <iostream>
#include <fstream>
#include "Task.h"


int main()
{

	char fileName[MAX_BUFFER_SIZE];
	std::cout << "Please enter file name for the task!" << std::endl;
	std::cin.getline(fileName, MAX_BUFFER_SIZE);

	try
	{
		Task task(fileName);
		std::cout << "successfully loaded function" << std::endl;

		size_t option;
		while (true)
		{
			std::cout << "If you want to print row of nums, press 1." << std::endl;
			std::cout << "If you want to generate next defined num, press 2." << std::endl;
			std::cout << "If you want to exit, press 0." << std::endl;

			std::cin >> option;
			if (option == 1)
			{
				int32_t A, B;
				std::cout << "Plese enter the starting-from num and the ending-to num!" << std::endl;
				std::cout << "Enter A:";
				std::cin >> A;
				std::cout << std::endl << "Enter B:";
				std::cin >> B;

				task.printFromAtoB(A, B);

			}
			else if (option == 2)
			{
				task.generateNextNum();
			}
			else
			{
				break;
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "Wrong File Name" << std::endl;;
	}
	catch (...)
	{
		std::cout << "Error while creating the function" << std::endl;
	}

	
	return 0;
}
