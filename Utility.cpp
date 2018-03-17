#include "Utility.h"
#include "baseTypes.h"

#include <cstdlib>

int32_t Utility::getRandomNumber(int32_t minimumValue, int32_t maximumValue)
{
	int32_t range = maximumValue - minimumValue;
	int32_t randomValue = rand() % (range + 1);
	randomValue += minimumValue;
	return randomValue;
}