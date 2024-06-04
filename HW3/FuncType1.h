#pragma once
#include "Constants.h"
#include "Pair.h"

class FuncType1
{
public:
	FuncType1(int32_t args[], size_t size);
	Pair operator()(int32_t num) const;
private:
	int32_t args[MAX_ARGS_NUM];
	size_t size = 0;
};