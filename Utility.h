#ifndef UTILITY_H
#define UTILITY_H

#include "baseTypes.h"

class Utility
{

public:
	// Returns a random number between parameters (inclusive of the parameter values)
	static int32_t getRandomNumber(int32_t minimumValue, int32_t maximumValue);

private:
	Utility() {};
	~Utility() {};
};

#endif UTILITY_H