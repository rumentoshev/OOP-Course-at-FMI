#include "MAXPF.h"

MAXPF::MAXPF(const PFCollection& functions):functions(functions){}

bool MAXPF::isDefined(int32_t num) const
{
	return functions.isDefinedForAll(num);
}
int32_t MAXPF::operator()(int32_t num) const
{
	if (!isDefined(num))
	{
		throw std::logic_error("Not Defined");
	}

	int32_t res = INT32_MIN;
	size_t numberOfFunctions = functions.getFuncsNum();

	for (size_t i = 0; i < numberOfFunctions; i++)
	{
		int32_t resultForI= functions.evalFor(i, num);
		if (res < resultForI)
		{
			res = resultForI;
		}
	}

	return res;
}

PF* MAXPF::clone() const
{
	return new MAXPF(*this);
}