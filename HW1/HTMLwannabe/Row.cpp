#include "Row.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)


bool Row::setNumOfCols(int columnsToBe)
{
	if (columnsToBe < 0  || columnsToBe > MAX_COLS_IN_ROW)
	{
		return false;
	}

	numOfCols = columnsToBe;
	return true;
}

int Row::getNumOfCols() const
{
	return numOfCols;
}

void Row::printRow(size_t alignment) const
{
	if (numOfCols > 0)
	{
		std::cout << "|";
	}
	for (size_t i = 0; i < numOfCols; i++)
	{
		printCol(i + 1,alignment);
	}
	std::cout<<std::endl;
}

bool Row::addColumn(const char* dataToBe, bool headerToBe)
{
	if (numOfCols == MAX_COLS_IN_ROW)
	{
		return false;
	}

	row[numOfCols].setData(dataToBe);
	row[numOfCols++].setHeader(headerToBe);

	return true;
}

bool Row::changeColumnData(int index, const char* newData)//index ->[0;29]
{
	//index in [1, 15];
	if (!isValidColIndex(index))
	{
		return false;
	}

	return row[index - 1].setData(newData);
}

bool Row::changeColumnHeader(int index, bool headerToBe)
{
	if (!isValidColIndex(index))
	{
		return false;
	}

	return row[index - 1].setHeader(headerToBe);
}

bool Row::isValidColIndex(int index) const
{
	//index is in [1,15]
	if (index > numOfCols || index < 1)
	{
		return false;
	}
	return true;
}

void Row::printCol(size_t index, size_t alignment) const
{
	if (!isValidColIndex(index))
	{
		return;
	}
	size_t curCellLen = row[index - 1].dataLen();
	size_t tempAlignment = alignment;
	if (curCellLen > tempAlignment)	//just in case
	{
		tempAlignment = curCellLen;
	}
	if (row[index - 1].isHeader())
	{
		std::cout << "*";
	}
	else
	{
		std::cout << " ";
	}
	row[index - 1].printData();
	tempAlignment = tempAlignment - row[index - 1].dataLen();
	for (size_t a = 0; a < tempAlignment; a++)
	{
		std::cout << " ";
	}
	if (row[index - 1].isHeader())
	{
		std::cout << "*";
	}
	else
	{
		std::cout << " ";
	}
	std::cout << "|";

}

bool Row::isCellAHeader(int index) const
{
	if (!isValidColIndex(index))
	{
		return false;
	}

	return row[index - 1].isHeader();
}

const char* Row::getDataAtIndex(int index) const
{

	if (!isValidColIndex(index))
	{
		return "";
	}

	return row[index - 1].getData();
}