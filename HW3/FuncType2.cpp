#include "FuncType2.h"


FuncType2::FuncType2(int32_t args1[], size_t size)
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
Pair FuncType2::operator()(int32_t num) const
{
	if (size == 0)
	{
		return Pair{ true,0 };
	}

	for (size_t i = 0; i < size && size != 0; i++)
	{
		if (num == args[i])
		{
			return Pair{ true,1 };
		}
	}

	return Pair{ true,0 };
}