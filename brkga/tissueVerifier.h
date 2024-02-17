#ifndef tissueVERIFIER_H
#define tissueVERIFIER_H

#include <iostream>
#include <algorithm>
#include "tissueInstance.h"

bool tissueSolutionVerifier(const tissueInstance& instance, std::vector<int> nodesOrder, 
	std::vector<int> nodesColor);

#endif