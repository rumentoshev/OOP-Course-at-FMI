#pragma once
#include "Row.h"
#include "OtherFunctions.h"
#include <fstream>
#include "Constants.h"


class Table
{
private:
	Row table[MAX_TABLE_ROWS];
	int numOfRows = 0;
	int numOfCols = 0 ;
	size_t aligment[MAX_COLS_IN_ROW] = {0,};
public:
	Table() = default;

	bool addRow(int index);//adds in the end
	bool addColInRowInTheEnd(int rowIndex, const char* data, bool headerToBe);//adds in the end of the row
	bool changeDataOfCell(int rowIndex, int colIndex, const char* dataToBe);
	bool changeHeaderOfCel(int rowIndex, int colIndex, bool headerToBe);//return true if change was made
	bool deleteRow(int rowIndex);
	
	int getNumOfCols() const;

	bool loadTableFromFile(const char* fileName);
	bool saveTableToFile(const char* fileName) const;
	void print() const;
private:
	//think
	bool isValidRowIndex(int index) const;
	bool fillDataInCell(Row& tempRow, char* str, bool headerToBe);
	void goToOpenCharAndGetTwoChars(std::ifstream& ifs, char* str) const;
	void getContentAndSaveIt(std::ifstream& ifs, char* str,bool header,Row& tempRow);
};
