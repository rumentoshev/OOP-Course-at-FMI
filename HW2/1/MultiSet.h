#pragma once
#include <cstdint>
#include <exception>
#include "Constants.h"

class MultiSet
{
public:

	MultiSet();
	MultiSet(unsigned maxNum, uint8_t bitsNeeded);
	MultiSet(const MultiSet& other);
	MultiSet(MultiSet&& other) noexcept;
	MultiSet& operator=(const MultiSet& other);
	MultiSet& operator=(MultiSet&& other) noexcept;
	~MultiSet();

	bool add(unsigned num);
	unsigned contains(unsigned num) const;
	void printAll() const;
	
	MultiSet complementMultiSet() const;

	friend MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet DiffOfSets(const MultiSet& lhs, const MultiSet& rhs);
	bool loadFromFile(const char* fileName);

	bool writeToFile(const char* fileName) const;

	void printBits() const;
	unsigned getMaxNum() const;
	uint8_t getNeededBits() const;

private:

	uint8_t bitsNeeded;
	uint8_t* data;
	unsigned maxNum;

	void free();
	void copyFrom(const MultiSet& other);
	void moveFrom(MultiSet&& other) noexcept;
	unsigned getNeededBuckets() const;
	void setNeededBits(uint8_t bits);

	bool isValidIndex(unsigned index) const;
	bool getBitAtIndex(unsigned index) const;

	unsigned getBucketIndex(unsigned index) const;
	unsigned getBitIndex(unsigned index) const;

	unsigned getLastIndexForNum(unsigned num) const;
	void modify(unsigned num, unsigned count);
	bool changeBit(unsigned index, bool value);

};
