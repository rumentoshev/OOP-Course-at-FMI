#include<iostream>
#include "Table.h"
#include "OtherFunctions.h"
#include "Constants.h"
#pragma warning(disable : 4996)



int main()
{
	Table t;
	std::cout << "Enter file name to load table." << '\n';
	char fileName[MAX_FILENAME_LEN];
	std::cin.getline(fileName, MAX_FILENAME_LEN);

	if (t.loadTableFromFile(fileName))
	{
		std::cout << "//loaded" << "\n";
	}
	else
	{
		std::cout << "//failed to load" << "\n";
	}


	int command;
	do
	{
		std::cout << "OPTIONS" << "\n";
		std::cout << "----------------------------" << "\n";
		std::cout << "To add row, press: 1" << "\n";
		std::cout << "To remove row, press: 2" << "\n";
		std::cout << "To change cell in the table, press: 3" << "\n";
		std::cout << "To print the table, press: 4" << "\n";
		std::cout << "To save to file, press: 5" << "\n";
		std::cout << "To exit, press: 0" << "\n";
		std::cout << "----------------------------" << "\n";

		std::cin >> command;
		
		if (command == 1)
		{
			std::cout << "Plese enter the index of the row." << "\n";
			int tempRowIndex;
			std::cin >> tempRowIndex;

			t.addRow(tempRowIndex);
			for (int i = 1; i <= t.getNumOfCols(); i++)
			{
				std::cout << "Plese enter the header status of the cell [1 or 0] for the " << i<< " cell"<<"\n";
				bool tempHeader;
				std::cin >> tempHeader;
				std::cin.ignore();
				std::cout << "Plese enter the data of the cell" << "\n";
				char tempData[MAX_CELL_DATA_SIZE];
				std::cin.getline(tempData, MAX_CELL_DATA_SIZE);
				if (t.changeDataOfCell(tempRowIndex, i, tempData))
				{
					std::cout << "//OK" << "\n";
				}
				else
				{
					std::cout << "//Failed" << "\n";
				}
				t.changeHeaderOfCel(tempRowIndex, i, tempData);
			}
		}
		else if (command == 2)
		{
			std::cout << "Plese enter the index of the row you want to remove." << "\n";
			int tempIndex;
			std::cin >> tempIndex;
			if (t.deleteRow(tempIndex))
			{
				std::cout << "//OK" << "\n";
			}
			else
			{
				std::cout << "//Failed" << "\n";
			}
		}
		else if (command == 3)
		{
			std::cout << "Plese enter the index of the row." << "\n";
			int tempRowIndex;
			std::cin >> tempRowIndex;
			std::cout << "Plese enter the index of the col." << "\n";
			int tempColIndex;
			std::cin >> tempColIndex;
			std::cout << "Plese enter the header status of the cell [1 or 0]." << "\n";
			bool tempHeader;
			std::cin >> tempHeader;
			std::cin.ignore();
			std::cout << "Plese enter the data of the cell" << "\n";
			char tempData[MAX_CELL_DATA_SIZE];
			std::cin.getline(tempData, MAX_CELL_DATA_SIZE);
			if (t.changeDataOfCell(tempRowIndex, tempColIndex, tempData))
			{
				std::cout << "//OK" << "\n";
			}
			else
			{
				std::cout << "//Failed" << "\n";
			}
			t.changeHeaderOfCel(tempRowIndex,tempColIndex,tempData);
		}
		else if (command == 4)
		{
			t.print();
		}
		else if (command == 5)
		{
			if (t.saveTableToFile(fileName))
			{
				std::cout << "//Saved" << "\n";
			}
			else
			{
				std::cout << "//Failed" << "\n";
			}
		}

	} while (command != 0);

	return 0;
}
