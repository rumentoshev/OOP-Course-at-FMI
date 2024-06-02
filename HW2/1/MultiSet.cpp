#include <iostream>
#include <fstream>
#include <exception>
#include "MultiSet.h"
#include "HelperFunctions.h"


unsigned MultiSet::getNeededBuckets() const
{
	return ((maxNum+1) * (unsigned)bitsNeeded) / 8 + ((((maxNum+1) * (unsigned)bitsNeeded) % 8) == 0 ? 0 : 1);
}

void MultiSet::setNeededBits(uint8_t bits)
{
	if (bits == 0 || bits > 8)
	{
		bitsNeeded = 8;
	}
	else
	{
		bitsNeeded = bits;
	}
}

MultiSet::MultiSet() :MultiSet(7, 2){}
MultiSet::MultiSet(unsigned maxNum, uint8_t bitsNeeded):maxNum(maxNum)
{
	setNeededBits(bitsNeeded);
	unsigned bucketsCount = getNeededBuckets();
	data = new uint8_t[bucketsCount]{ 0 };
}

void MultiSet::free()
{
	delete[] data;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	unsigned neededBuckets = other.getNeededBuckets();
	data = new uint8_t[neededBuckets];
	for (unsigned i = 0; i < neededBuckets; i++)
	{
		data[i] = other.data[i];
	}
	maxNum = other.maxNum;
	bitsNeeded = other.bitsNeeded;
}

void MultiSet::moveFrom(MultiSet&& other) noexcept
{
	bitsNeeded = other.bitsNeeded;
	maxNum = other.maxNum;
	data = other.data;
	other.data = nullptr;
}

unsigned MultiSet::getMaxNum() const
{
	return maxNum;
}
uint8_t MultiSet::getNeededBits() const
{
	return bitsNeeded;
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet::MultiSet(MultiSet&& other) noexcept
{
	moveFrom(std::move(other));
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

bool MultiSet::isValidIndex(unsigned index) const
{
	return (index < (getNeededBuckets()* BITS));
}

unsigned MultiSet::getLastIndexForNum(unsigned num) const
{
	return ((num * (unsigned)bitsNeeded) + (unsigned)bitsNeeded) - 1;
}
unsigned MultiSet::getBucketIndex(unsigned indexInData) const
{
	return indexInData / BITS;
}
unsigned MultiSet::getBitIndex(unsigned indexInData) const
{
	return indexInData % BITS;
}
bool MultiSet::getBitAtIndex(unsigned indexInData) const
{
	unsigned bucketIndex = getBucketIndex(indexInData);
	unsigned bitIndex = getBitIndex(indexInData);

	uint8_t mask = 1 << (7 - bitIndex);

	return data[bucketIndex] & mask;
}

bool MultiSet::changeBit(unsigned indexInData, bool value)
{
	if (!isValidIndex(indexInData))
		return false;

	unsigned bucketIndex = getBucketIndex(indexInData);
	unsigned bitIndex = getBitIndex(indexInData);

	bool bit = getBitAtIndex(indexInData);
	if (bit == value)
	{
		return true;
	}
	else
	{
		uint8_t mask = 1 << (7 - bitIndex);
		data[bucketIndex] ^= mask;
	}
	return true;
}
void MultiSet::modify(unsigned num, unsigned count)
{
	//bool numBits[BITS] ={0,};
	//fillBitsInArray(numBits, BITS, count);
	uint8_t bits = fillBitsFromNum(count);

	unsigned BitIndexForNum = getLastIndexForNum(num);

	for (unsigned i = 0; i < (unsigned)bitsNeeded; i++)
	{
		uint8_t mask = 1;
		bool bit = (bits & (mask << i));
		changeBit(BitIndexForNum, bit);
		BitIndexForNum--;

	}
	/*unsigned BitIndexForNum = getLastIndexForNum(num);
	for (unsigned i = 0; i < (unsigned)bitsNeeded; i++)
	{
		changeBit(BitIndexForNum, numBits[i]);
		BitIndexForNum--;
	}*/
}

bool MultiSet::add(unsigned num)
{
	if (num > maxNum)
	{
		return false;
	}
	unsigned countOfNum = contains(num);

	if (countOfNum == (pow(2,(unsigned)bitsNeeded) - 1))
	{
		return false;
	}

	++countOfNum;
	modify(num, countOfNum);
	return true;
}

unsigned MultiSet::contains(unsigned num) const
{
	if (num > maxNum)
	{
		return 0;
	}

	uint8_t bits = 0;
	unsigned BitIndexForNum = getLastIndexForNum(num);
	for (unsigned i = 0; i < (unsigned)bitsNeeded; i++)
	{
		bool bit = getBitAtIndex(BitIndexForNum);
		if (bit)
		{
			uint8_t mask = 1;
			bits = bits | (mask << i);
		}
		BitIndexForNum--;
	}
	unsigned countOfNumber = (unsigned)bits;
	
	return countOfNumber;
}

void MultiSet::printBits() const
{
	std::cout << "x are unused bits" << std::endl;
	std::cout << "| ";
	unsigned end = getNeededBuckets() * BITS;
	unsigned usedBits = (maxNum + 1) * (unsigned)bitsNeeded;
	
	for (unsigned i = 0; i < end; i++)
	{
		if (i > usedBits - 1)
		{
			std::cout << "x" << " ";
			if (i + 1 == end)
			{
				std::cout << "|";
			}
			continue;
		}
		std::cout << getBitAtIndex(i) << " ";
		if ((i + 1) % (unsigned)BITS == 0)
		{
			std::cout << "| ";
		}
	}
}

void MultiSet::printAll() const
{
	std::cout << "{ ";
	for (unsigned i = 0; i <= maxNum; i++)
	{
		unsigned tempCount = contains(i);
		std::cout << i << ":" << tempCount << " ";
	}
	std::cout << "}";
}


MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	//A = { a a a c d d}
	//B = { a a b c c }
	// A ë B = { a a c } (min from both set)

	unsigned tempMaxNumSmaller = std::min(lhs.maxNum, rhs.maxNum);
	int8_t tempBitsNeeded = std::min(lhs.bitsNeeded, rhs.bitsNeeded);

	MultiSet result(tempMaxNumSmaller, tempBitsNeeded);

	for (unsigned i = 0; i <= tempMaxNumSmaller; i++)
	{
		unsigned lhsCount = lhs.contains(i);
		unsigned rhsCount = rhs.contains(i);
		
		result.modify(i, std::min(lhsCount, rhsCount));
	}

	return result;
}

MultiSet DiffOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	//A = { a a a b b c d d e}
	//B = { a a b b b c c d d f }
	// A ë B = { a e } (element count from A - element count from B, if negative -> 0)

	MultiSet result(lhs);

	for (unsigned i = 0; i <= lhs.maxNum; i++)
	{
		unsigned lhsCount = lhs.contains(i);
		unsigned rhsCount = rhs.contains(i);

		if (rhsCount >= lhsCount)
		{
			result.modify(i, 0);
		}
		else
		{
			result.modify(i, (lhsCount - rhsCount));
		}
	}

	return result;
}

MultiSet MultiSet::complementMultiSet() const
{
	MultiSet complement(this->maxNum,this->bitsNeeded);

	unsigned maxCount = (pow(2, (unsigned)bitsNeeded) - 1);

	for (unsigned i = 0; i <= maxNum; i++)
	{
		unsigned complimentCount = maxCount - this->contains(i);
		complement.modify(i, complimentCount);
	}

	return complement;
}


bool MultiSet::writeToFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open())
	{
		return false;
	}

	ofs.write((const char*)&maxNum, sizeof(unsigned));
	ofs.write((const char*)&bitsNeeded, sizeof(uint8_t));
	unsigned tempBucketsCount = getNeededBuckets();
	ofs.write((const char*)data, tempBucketsCount * sizeof(uint8_t));

	ofs.close();
	return true;
}

bool MultiSet::loadFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::out | std::ios::binary);

	if (!ifs.is_open())
	{
		return false;
	}

	free();
	unsigned tempMaxNum;
	uint8_t tempBitsNeeded;
	ifs.read((char*)&tempMaxNum, sizeof(unsigned));
	ifs.read((char*)&tempBitsNeeded, sizeof(uint8_t));

	bitsNeeded = tempBitsNeeded;
	maxNum = tempMaxNum;

	unsigned bucketsCount = getNeededBuckets();
	data = new uint8_t[bucketsCount]{ 0 };

	ifs.read((char*)data, tempBitsNeeded * sizeof(uint8_t));

	ifs.close();
	
	return true;
}