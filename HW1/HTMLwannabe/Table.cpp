#include "Table.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma warning(disable : 4996)

int Table::getNumOfCols() const
{
	return numOfCols;
}

bool Table::isValidRowIndex(int index) const
{
	//inedx is in [1,100]
	if (index > numOfRows || index < 1)
	{
		return false;
	}

	return true;
}
bool Table::addRow(int index)
{
	if (numOfRows == MAX_TABLE_ROWS)
	{
		return false;
	}

	if (index <= numOfCols + 1)
	{
		table[numOfRows].setNumOfCols(numOfCols);
		numOfRows++;
		for (int i = numOfRows - 1; i > index - 1; i--)
		{
			table[i] = table[i - 1];
		}
		Row temp;
		table[index - 1] = temp;
		table[index - 1].setNumOfCols(numOfCols);
		return true;
	}
	return false;
}

bool Table::addColInRowInTheEnd(int rowIndex, const char* dataToBe, bool headerToBe)
{
	if (!isValidRowIndex(rowIndex))
	{
		return false;
	}

	if (!table[rowIndex - 1].addColumn(dataToBe, headerToBe))
	{
		return false;
	}

	int indexOfCurCol = table[rowIndex - 1].getNumOfCols();
	size_t tempLen = strlen(dataToBe);
	if (aligment[indexOfCurCol - 1] <= tempLen)
	{
		aligment[indexOfCurCol - 1] = tempLen;
	}

	if (numOfCols < indexOfCurCol)
	{
		numOfCols = indexOfCurCol;
	}
	return true;
}

bool Table::changeDataOfCell(int rowIndex, int colIndex, const char* dataToBe)
{
	if (!isValidRowIndex(rowIndex))
	{
		return false;
	}

	if (!table[rowIndex - 1].changeColumnData(colIndex, dataToBe))
	{
		return false;
	}

	size_t tempLen = strlen(dataToBe);
	if (aligment[colIndex - 1] <= tempLen)
	{
		aligment[colIndex - 1] = tempLen;
	}

	return true;
}

bool Table::changeHeaderOfCel(int rowIndex, int colIndex, bool headerToBe)
{
	if (!isValidRowIndex(rowIndex))
	{
		return false;
	}

	if (!table[rowIndex - 1].changeColumnHeader(colIndex,headerToBe))
	{
		return false;
	}
	return true;
}

bool Table::deleteRow(int rowIndex)
{
	if (!isValidRowIndex(rowIndex))
	{
		return false;
	}

	for (int i = rowIndex - 1; i < numOfRows - 1; i++)
	{
		table[i] = table[i + 1];
	}

	numOfRows--;
	return true;
}

void Table::print() const
{
	for (int i = 0; i < numOfRows; i++)
	{
		if (numOfCols > 0)
		{
			std::cout << "|";
		}
		for (int j = 0; j < numOfCols; j++)
		{
			table[i].printCol(j + 1, aligment[j]);
		}
		std::cout << std::endl;
	}
}

bool Table::fillDataInCell(Row& tempRow,char* str, bool headerToBe)//here we take care of the aligment
{
	removeSpaces(str);
	changeChars(str);

	if (tempRow.addColumn(str, headerToBe))
	{
		size_t strLen = strlen(str);
		if (aligment[tempRow.getNumOfCols() - 1] < strLen)
		{
			aligment[tempRow.getNumOfCols() - 1] = strLen;
		}
		return true;
	}

	return false;
}

void Table::goToOpenCharAndGetTwoChars(std::ifstream& ifs, char* str) const
{
	ifs.getline(str, BUFFER, '<');
	str[0] = ifs.get();
	str[1] = ifs.get();
	str[2] = '\0';
}

void Table::getContentAndSaveIt(std::ifstream& ifs, char* str,bool header, Row& tempRow)
{
	ifs.getline(str, BUFFER, '>'); //find end
	ifs.getline(str, BUFFER, '<');
	ifs.seekg(-1, std::ios::cur);
	fillDataInCell(tempRow, str, header);
	ifs.getline(str, BUFFER, '>');
}
bool Table::loadTableFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return false;
	}

	bool inTable = false;
	bool inRow = false;

	char strBuffer[BUFFER];
	Row tempRow;
	while (!ifs.eof())
	{
		if (!inTable)
		{

			ifs.getline(strBuffer, BUFFER, '>'); //find end of table
			inTable = true;
			continue;
			
		}
		else
		{
			if (!inRow) //find <tr
			{
				goToOpenCharAndGetTwoChars(ifs, strBuffer);
				if (!strcmp(strBuffer, "tr")) //skip to > of <tr ...>
				{
					ifs.getline(strBuffer, BUFFER, '>'); //find end
					inRow = true;
					continue;
				}
				else if (!strcmp(strBuffer, "/t"))
				{
					break;
				}
			}
			else
			{
				goToOpenCharAndGetTwoChars(ifs, strBuffer);
				if (!strcmp(strBuffer, "th")) //skip to > of <tr ...>
				{
					getContentAndSaveIt(ifs, strBuffer, true, tempRow);
					continue;
				}
				else if (!strcmp(strBuffer, "td")) //skip to > of <tr ...>
				{
					getContentAndSaveIt(ifs, strBuffer, false, tempRow);
					continue;
				}
				else if (!strcmp(strBuffer, "/t")) //skip to > of <tr ...>
				{
					ifs.getline(strBuffer, BUFFER, '>'); //find end
					inRow = false;
					table[numOfRows++] = tempRow;
					int tempNumOfCols = tempRow.getNumOfCols();
					if (numOfCols < tempNumOfCols)
					{
						numOfCols = tempNumOfCols;
					}
					tempRow.setNumOfCols(0);
					continue;
				}
			}
		}
	}

	//setting all rows to have equal number of columns
	for (int i = 0; i < numOfRows; i++)
	{
		table[i].setNumOfCols(numOfCols);
	}
	ifs.close();
	return true;
}

bool Table::saveTableToFile(const char* fileName) const
{
	std::ofstream file(fileName);  

	if (!file.is_open()) {
		return false;
	}

	file << "<table>" << '\n';
	for (int i = 0; i < numOfRows; i++)
	{
		file << " <tr>" << '\n';
		for (int j = 1; j <= numOfCols; j++)
		{
			if (table[i].isCellAHeader(j))
			{
				file << "  <th>" << table[i].getDataAtIndex(j) << "</th>"<<'\n';
			}
			else
			{
				file << "  <td>" << table[i].getDataAtIndex(j)<<"</td>"<<'\n';
			}
		}
		file << " </tr>" << '\n';
	}
	file << "</table>" << '\n';

	file.close();
	return true;
}
