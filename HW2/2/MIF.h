#pragma once
#include <cstdint>
#include <exception>
#include "Constants.h"

class MIF
{
public:

	//Big 6
	MIF();
	MIF(int16_t (*func)(int16_t num));
	MIF(const MIF& other);
	MIF(MIF&& other) noexcept;

	MIF& operator=(const MIF& other);
	MIF& operator=(MIF&&) noexcept;

	~MIF();

	//Task functions
	void modifyPointValue(int16_t num,int16_t newValue);
	void modifyPointStatus(int16_t num,bool status);

	int16_t eval(int16_t num) const;

	//Operators
	MIF& operator+=(const MIF& other);
	MIF& operator-=(const MIF& other);

	bool operator<(const MIF& other) const;
	bool operator>(const MIF& other) const;
	bool operator<=(const MIF& other) const;
	bool operator>=(const MIF& other) const;

	bool operator||(const MIF& ohter) const;

	MIF operator[](const MIF& other) const;
	MIF& operator^(unsigned num);

	MIF operator~() const;

	bool checkIjective() const;
	bool checkSurjective() const;
	bool checkBijection() const;

	//Function for files
	bool writeToFile(const char* fileName) const;
	bool readFromFile(const char* fileName);

	//print
	void printGraphics() const;

private:

	struct Pair
	{
		int16_t value = 0;
		bool isActive = true;
	};

	Pair* data = nullptr;

	//functions for Big6
	void copyFrom(const MIF& other);
	void moveFrom(MIF&& other) noexcept;
	void free();
};


MIF operator+(const MIF& lhs, const MIF& rhs);
MIF operator-(const MIF& lhs, const MIF& rhs);