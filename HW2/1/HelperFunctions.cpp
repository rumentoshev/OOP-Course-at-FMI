#include "HelperFunctions.h"
#include <cstdint>
#include "Constants.h"


uint8_t fillBitsFromNum(unsigned num)
{
	uint8_t result = 0;
	unsigned shifter = 0;
	while (num > 0 || shifter == 8)
	{
		if (num % 2)
		{
			uint8_t mask = 1;
			result = result | (mask << shifter);
			shifter++;
		}
		else
		{
			shifter++;
		}
		num /= 2;
	};
	return result;
}
