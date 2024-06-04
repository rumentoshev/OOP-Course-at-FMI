#pragma once
#include "Constants.h"
#include "Pair.h"

class FuncType0
{
public:
	FuncType0(int32_t args[], int32_t res[],size_t size);
	Pair operator()(int32_t num) const;
private:
	int32_t args[MAX_ARGS_NUM];
	int32_t res[MAX_ARGS_NUM];
	size_t size = 0;
}; 