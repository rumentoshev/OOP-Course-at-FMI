#include <iostream>
#include <exception>
#include "PFCollection.h"


//Def Constr
PFCollection::PFCollection()
{
	capacity = 8;
	data = new PF * [capacity] {nullptr};
	size = 0;
}

//Copy & Move Constr
PFCollection::PFCollection(const PFCollection& other)
{
	copyFrom(other);
}
PFCollection::PFCollection(PFCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

//Operators=
PFCollection& PFCollection::operator= (const PFCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
PFCollection& PFCollection::operator=(PFCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

//Destr
PFCollection::~PFCollection() noexcept
{
	free();
}

//Helper Functions
void PFCollection::moveFrom(PFCollection&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	capacity = other.capacity;

	other.size = other.capacity = 0;
}
void PFCollection::copyFrom(const PFCollection& other)
{
	data = new PF * [other.capacity];

	for (int i = 0; i < other.size; i++)
		data[i] = other.data[i]->clone();

	size = other.size;
	capacity = other.capacity;
}
void PFCollection::free()
{
	for (int i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
}
void PFCollection::resize(size_t newCap)
{
	PF** newData = new PF * [newCap];
	for (int i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCap;
}
bool PFCollection::isValidIndex(size_t index) const
{
	return index < size;
}

//Other Functions
void PFCollection::addFunc(PF* func)
{
	if (size == capacity)
		resize(capacity * 2);
	data[size++] = func; 
	func = nullptr;
}
void PFCollection::addFunc(const PF& func)
{
	PF* cloned = func.clone();
	addFunc(cloned);
}

bool PFCollection::isDefinedFor(size_t index, int32_t num) const
{
	if (!isValidIndex(index))
	{
		return false;
	}

	return data[index]->isDefined(num);

}
bool PFCollection::isDefinedForAll(int32_t num) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!data[i]->isDefined(num))
		{
			return false;
		}
	}

	return true;
}
int32_t PFCollection::evalFor(size_t index, int32_t num) const
{
	if (!isValidIndex(index))
	{
		throw std::out_of_range("Invalid index");
	}

	try
	{
		int32_t temp = data[index]->operator()(num); // or (*data[index])(num);
		return temp;
	}
	catch (const std::logic_error& ex)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

//Getters
size_t PFCollection::getFuncsNum() const
{
	return size;
}