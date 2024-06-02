#include "MIF.h"
#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>

void MIF::copyFrom(const MIF& other)
{
	Pair* data = new Pair[ALL_NUMS_COUNT];
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		data[i] = other.data[i];
	}
}
void MIF::moveFrom(MIF&& other) noexcept
{
	data = other.data;
	other.data = nullptr;
}
void MIF::free()
{
	delete[] data;
	data = nullptr;
}

MIF::MIF() :MIF([](int16_t x) {return x;}){}

MIF::MIF(int16_t(*func)(int16_t num))
{
	Pair* data = new Pair[ALL_NUMS_COUNT];
	for (int i = INT16_MIN; i <= INT16_MAX ; i++)
	{
		if (i < 0)
		{
			data[-(i)+INT16_MAX].value = func(i);
		}
		else
		{
			data[i].value = func(i);
		}
	}

    //data -> 0 1 2 3.....-1 -2 .....
}

MIF::MIF(const MIF& other)
{
	copyFrom(other);
}
MIF::MIF(MIF&& other) noexcept
{
	moveFrom(std::move(other));
}

MIF& MIF::operator=(const MIF& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MIF& MIF::operator=(MIF&& other) noexcept
{
	if (this != &other) 
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

MIF::~MIF()
{
	free();
}

//Task functions

void MIF::modifyPointValue(int16_t num,int16_t newValue)
{
	if (num < 0)
	{
		data[-(num)+INT16_MAX].value = newValue;
	}
	else
	{
		data[num].value = newValue;
	}
}
void MIF::modifyPointStatus(int16_t num,bool status)
{
	if (num < 0)
	{
		data[-(num)+INT16_MAX].isActive = status;
	}
	else
	{
		data[num].isActive = status;
	}
}

int16_t MIF::eval(int16_t num) const
{
	if (num < 0)
	{
		if (data[-(num)+INT16_MAX].isActive)
		{
			return data[-(num)+INT16_MAX].value;
		}
		else
		{
			throw ("Point is deleted.");
		}
	}
	else
	{
		if (data[num].isActive)
		{
			return data[num].value;
		}
		else
		{
			throw ("Point is deleted.");
		}
	}
}

//Operators
MIF& MIF::operator+=(const MIF& other)
{
	for (int i = INT16_MIN; i <= INT16_MAX; i++)
	{
		if (i < 0)
		{
			if (data[-(i)+INT16_MAX].isActive && other.data[-(i)+INT16_MAX].isActive)
			{
				data[-(i)+INT16_MAX].value = data[-(i)+INT16_MAX].value + other.data[-(i)+INT16_MAX].value;
			}
			else
			{
				data[-(i)+INT16_MAX].isActive = false;
			}
		}
		else
		{
			if (data[i].isActive && other.data[i].isActive)
			{
				data[i].value = data[i].value + other.data[i].value;
			}
			else
			{
				data[i].isActive = false;
			}
		}
	}

	return *this;
}
MIF& MIF::operator-=(const MIF& other)
{
	for (int i = INT16_MIN; i <= INT16_MAX; i++)
	{
		if (i < 0)
		{
			if (data[-(i)+INT16_MAX].isActive && other.data[-(i)+INT16_MAX].isActive)
			{
				data[-(i)+INT16_MAX].value = data[-(i)+INT16_MAX].value - other.data[-(i)+INT16_MAX].value;
			}
			else
			{
				data[-(i)+INT16_MAX].isActive = false;
			}
		}
		else
		{
			if (data[i].isActive && other.data[i].isActive)
			{
				data[i].value = data[i].value - other.data[i].value;
			}
			else
			{
				data[i].isActive = false;
			}
		}
	}

	return *this;
}

MIF operator+(const MIF& lhs, const MIF& rhs)
{
	MIF result(lhs);
	result += rhs;

	return result;
}
MIF operator-(const MIF& lhs, const MIF& rhs)
{
	MIF result(lhs);
	result -= rhs;

	return result;
}

bool MIF::operator<(const MIF& other) const
{
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive && other.data[i].isActive)
		{
			if (data[i].value < other.data[i].value)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else if(other.data[i].isActive && (INT16_MIN < other.data[i].value))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}
bool MIF::operator>(const MIF& other) const
{
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive && other.data[i].isActive)
		{
			if (data[i].value > other.data[i].value)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else if (data[i].isActive && (data[i].value > INT16_MIN))
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}
bool MIF::operator>=(const MIF& other) const
{
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive && other.data[i].isActive)
		{
			if (data[i].value >= other.data[i].value)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else if (data[i].isActive)
		{
			continue;
		}
		else
		{
			if (other.data[i].value == INT16_MIN || other.data[i].isActive)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}
bool MIF::operator<=(const MIF& other) const
{
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive && other.data[i].isActive)
		{
			if (data[i].value <= other.data[i].value)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		else if (other.data[i].isActive)
		{
			continue;
		}
		else
		{
			if (data[i].value == INT16_MIN || data[i].isActive)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool MIF::operator||(const MIF& other) const
{
	double ratio = 0.0;
	bool ratioSet = false;

	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (!data[i].isActive && !other.data[i].isActive)
		{
			continue;
		}
		if (data[i].isActive && !other.data[i].isActive)
		{
			return false;
		}
		else if(!data[i].isActive && other.data[i].isActive)
		{
			return false;
		}

		//Copied from class task - NVector
		double currentRatio = data[i].value / other.data[i].value;
		if (!ratioSet)
		{
			ratio = currentRatio;
			ratioSet = true;
		}
		else if (std::abs(ratio - currentRatio) > 1e-6)
		{
			return false;
		}
	}

	return true;
}

MIF MIF::operator[](const MIF& other) const
{
	MIF result([](int16_t x) { return x; });
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive && other.data[i].isActive)
		{
			try
			{
				result.data[i].value = eval(other.eval(data[i].value));
			}
			catch (const char* str)
			{
				result.data[i].isActive = false;
			}
			catch (...)
			{
				throw;
			}
		}
	}

	return result;
}

MIF& MIF::operator^(unsigned num)
{
	MIF copyFunc(*this);
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (data[i].isActive)
		{
			for (unsigned i = 0; i < num; i++)
			{
				try
				{
					data[i].value = copyFunc.eval(num);
				}
				catch (const char* str)
				{
					data[i].isActive = false;
				}
				catch (...)
				{
					throw;
				}
			}
		}
		else
		{
			continue;
		}
	}

	return *this;
}

MIF MIF::operator~() const
{
	bool tempArr[ALL_NUMS_COUNT]{false};
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		int16_t tempValue = data[i].value;

		try
		{
			int16_t tempEvaluation = eval(tempValue);

			if (tempEvaluation < 0)
			{
				if (tempArr[-tempEvaluation + INT16_MAX])
				{
					throw ("it is not invertible");
				}
				else
				{
					tempArr[-tempEvaluation + INT16_MAX] = true;
				}
			}
			else
			{
				if (tempArr[tempEvaluation])
				{
					throw ("it is not invertible");
				}
				else
				{
					tempArr[tempEvaluation] = true;
				}
			}
		}
		catch (...)
		{
			throw;
		}
	}
}

bool MIF::checkIjective() const
{
	bool seenValues[ALL_NUMS_COUNT]{ false };
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		if (seenValues[data[i].value])
		{
			return false;
		}
		else
		{
			seenValues[data[i].value] = true;
		}
	}

	return true;
}
bool MIF::checkSurjective() const
{
	for (size_t i = 0; i < ALL_NUMS_COUNT; i++)
	{
		int16_t tempValue = data[i].value;

		if (tempValue<0)
		{
			if (data[-tempValue + INT16_MAX].isActive)
			{
				continue;
			}
			else
			{
				false;
			}
		}
		else
		{
			if (data[tempValue].isActive)
			{
				continue;
			}
			else
			{
				false;
			}
		}
	}

	return true;
}
bool MIF::checkBijection() const
{
	return checkIjective() && checkSurjective();
}

bool MIF::writeToFile(const char* fileName) const
{
	std::ofstream file (fileName,std::ios::binary);
	if (!file.is_open()) {
		return false;
	}

	file.write((const char*)data, ALL_NUMS_COUNT * sizeof(Pair));
}
bool MIF::readFromFile(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		return false;
	}

	//the data array is always with the same size, so there is no need to free the array, just change the values
	//but if we want to be sure
	//we can free() and alocate data (data = new Pair[All_NUMS_COUNT]);
	file.read((char*)data, ALL_NUMS_COUNT * sizeof(Pair));
}

void MIF::printGraphics() const
{
	int16_t arr[20];

	for (int i = 0; i < 20; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < 20; j++)
		{
			if (data[j].isActive)
			{
				if (data[j].value == 20 - i)
				{
					std::cout << "o ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			else
			{
				std::cout << "  ";
			}

		}
	}

	std::cout << "----------------------------------------" << std::endl;
	std::cout << "0                                     20" << std::endl;
}