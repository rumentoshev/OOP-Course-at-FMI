#pragma once
#include "PF.h"

//Most of the code [in the .h and .cpp file] is from Angeld55 GitHub [Object-oriented_programming_FMI/Week 12/Polymorphic containters/ShapeCollection/]
class PFCollection
{
public:
	PFCollection();

	PFCollection(const PFCollection& other);
	PFCollection(PFCollection&& other) noexcept;

	PFCollection& operator=(const PFCollection&);
	PFCollection& operator=(PFCollection&&) noexcept;

	~PFCollection() noexcept;
	
	void addFunc(PF* func);
	void addFunc(const PF& func);

	bool isDefinedFor(size_t index, int32_t num) const;
	bool isDefinedForAll(int32_t num) const;
	int32_t evalFor(size_t index, int32_t num) const;

	size_t getFuncsNum() const;
	
private:
	void resize(size_t newCap);
	void moveFrom(PFCollection&& other);
	void copyFrom(const PFCollection& other);
	void free();
	bool isValidIndex(size_t index) const;

	PF** data = nullptr;
	size_t capacity = 0;
	size_t size = 0;;
};