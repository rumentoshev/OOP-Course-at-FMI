#include "Cell.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

const char* Cell::getData() const
{
	return data;
}

bool Cell::setData(const char* dataToBe)
{
	size_t dataToBeLen = strlen(dataToBe);
	if (dataToBeLen > MAX_CELL_DATA_SIZE)
	{
		return false;
	}

	strcpy(data, dataToBe);
	lenOfData = dataToBeLen;
	return true;
}

bool Cell::setHeader(bool headerToBe)
{
	if (header == headerToBe)
	{
		return false;
	}

	header = headerToBe;
	return true;
	
}

bool Cell::isHeader() const
{
	return header;
}

bool Cell::isEmpty() const
{
	return lenOfData == 0;
}

size_t Cell::dataLen() const
{
	return lenOfData;
}

void Cell::printData() const
{
	std::cout << data;
}