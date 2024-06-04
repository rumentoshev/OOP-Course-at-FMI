#pragma once
#include <iostream>
#include <cstdint>
#include <exception>
#include "Pair.h"

class PF
{
public:
	virtual bool isDefined(int32_t) const = 0;
	virtual int32_t operator()(int32_t num) const = 0;

	virtual PF* clone() const = 0;
	~PF() = default;
};