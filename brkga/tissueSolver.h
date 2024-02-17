#ifndef tissueSOLVER_H
#define tissueSOLVER_H

#include <list>
#include <limits>
#include <vector>
#include <algorithm>
#include "tissueInstance.h"

class tissueSolver {
public:
	
	tissueSolver(const tissueInstance& instance, const std::vector< double >& chromosome);
	virtual ~tissueSolver();

	//int tissueSolverN(const tissueInstance& instance, const std::vector< double >& chromosome);
	int getFitness();
	
private:
	unsigned maxFinishTime;
};

#endif