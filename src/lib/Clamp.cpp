#include "Clamp.hpp"

namespace my
{
void clamp(unsigned int max, unsigned int min, unsigned int& value)
{
	if (value > max)
		value = max;
	else if (value <= min)
		value = min;
}

void clamp(unsigned int max, unsigned int min, float& value)
{
	if (value > max)
		value = max;
	else if (value <= min)
		value = min;
}
}