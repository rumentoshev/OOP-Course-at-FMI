#include "FuncType0.h"


FuncType0::FuncType0(int32_t args1[], int32_t res1[], size_t size)
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
		res[i] = res1[i];
	}
}
Pair FuncType0::operator()(int32_t num) const
{
	if (size == 0)
	{
		return Pair{ false,num };
	}

	for (size_t i = 0; i < size && size != 0 ; i++)
	{
		if (num == args[i])
		{
			return Pair{ true,res[i] };
		}
	}

	return Pair{ false,num};
}