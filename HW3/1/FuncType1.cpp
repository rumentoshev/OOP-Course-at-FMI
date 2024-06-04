#include "FuncType1.h"


FuncType1::FuncType1(int32_t args1[], size_t size)
{
	if (size > MAX_ARGS_NUM)
	{
		size = MAX_ARGS_NUM;
	}
	else
	{
		this->size = size;
	}

	for (size_t i = 0; i < size; i++)
	{
		args[i] = args1[i];
	}
}
Pair FuncType1::operator()(int32_t num) const
{
	if (size == 0)
	{
		return Pair{ true,num };
	}

	for (size_t i = 0; i < size && size != 0; i++)
	{
		if (num == args[i])
		{
			return Pair{ false,num};
		}
	}

	return Pair{ true,num };
}