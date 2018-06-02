#ifndef _UTILITY_CPP
#define _UTILITY_CPP
#include "Utility.h"

LinkedList<int> extractIntegers(std::string str)
{
	LinkedList<int> result;

	unsigned currOff = 0;

	while (currOff < str.size())
	{
		if (std::isdigit(str.at(currOff)))
		{
			int num = std::stoi(str.substr(currOff));
			result.push_back(num);

			currOff += std::to_string(num).size();
			continue;
		}

		++currOff;
	}
	return result;
}

#endif