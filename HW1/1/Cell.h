#pragma once
#include "Constants.h"


class Cell
{
public:
	char data[MAX_CELL_DATA_SIZE + 1] = "";
	bool header = false;
	size_t lenOfData = 0;
public:
	bool setData(const char* dataToBe);
	bool setHeader(bool headerCheck);//return true if change was made
	const char* getData() const;

	bool isHeader() const;
	bool isEmpty() const;

	size_t dataLen() const;
	void printData() const;
};