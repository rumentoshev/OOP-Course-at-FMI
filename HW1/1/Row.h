#pragma once
#include "Cell.h"

#include "Constants.h"

class Row {
private:
	Cell row[MAX_COLS_IN_ROW];
	int numOfCols = 0;
public:

	bool changeColumnData(int index, const char* newData);
	bool changeColumnHeader(int index, bool headerToBe);
	bool addColumn(const char* data, bool headerToBe);//adds column(cell) in the end
	bool setNumOfCols(int numOfColsToBe);

	int getNumOfCols() const;
	void printRow(size_t aligment) const;
	void printCol(size_t index, size_t alignment) const;
	
	bool isCellAHeader(int index) const;
	const char* getDataAtIndex(int index) const;
private:
	bool isValidColIndex(int index) const;
};
