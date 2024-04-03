#include <iostream>
#include <cstring>
#include "Constants.h"
#pragma warning(disable : 4996)


bool checkIfCharIsSpace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
	{
		return true;
	}

	return false;
}
void removeSpaces(char* str)
{
	int index = 0;
	char tempStr[buffer1];
	int tempStrIndex = 0;

	bool spaceFlag = false;
	while (str[index] != '\0')
	{
		if (checkIfCharIsSpace(str[index]) && spaceFlag == false)
		{
			tempStr[tempStrIndex++] = ' ';
			spaceFlag = true;
			index++;
		}
		else if (checkIfCharIsSpace(str[index]) && spaceFlag)
		{
			index++;
		}
		else
		{
			tempStr[tempStrIndex++] = str[index++];
			spaceFlag = false;
		}
	}

	tempStr[tempStrIndex] = '\0';
	strcpy(str, tempStr);
}
int myAtoi(const char* str)
{
	int index = 0;
	int result = 0;

	while (str[index] != '\0')
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}

	return result;
}
void changeChars(char* str)
{
	int index = 0;
	char tempStr[buffer1];
	int tempStrIndex = 0;

	bool ampsFlag = false;
	while (str[index] != '\0')
	{
		if (str[index] != '&')
		{
			tempStr[tempStrIndex++] = str[index++];
			continue;
		}

		if (str[index] == '&')
		{
			ampsFlag = true;
			index = index + 2;
			char code[NUM_BUFFER];
			int codeIndex = 0;
			while (str[index] >= '0' && str[index] <= '9')
			{
				code[codeIndex++] = str[index++];
			}
			code[codeIndex] = '\0';

			tempStr[tempStrIndex++] = myAtoi(code);
		}
	}

	tempStr[tempStrIndex] = '\0';
	strcpy(str, tempStr);
}