#include "MINPF.h"

MINPF::MINPF(const PFCollection& functions) :functions(functions) {}

bool MINPF::isDefined(int32_t num) const
{
	return functions.isDefinedForAll(num);
}
int32_t MINPF::operator()(int32_t num) const //This function will not throw; index is always correct
{
	if (!isDefined(num))
	{
		throw std::logic_error("Not Defined");
	}

	int32_t res = INT32_MAX;
	size_t numberOfFunctions = functions.getFuncsNum();

	for (size_t i = 0; i < numberOfFunctions; i++)
	{
		int32_t resultForI = functions.evalFor(i, num);
		if (res > resultForI)
		{
			res = resultForI;
		}
	}

	return res;
}

PF* MINPF::clone() const
{
	return new MINPF(*this);
}