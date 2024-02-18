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

	int tissueSolverV0(const tissueInstance& instance, const std::vector< double >& chromosome);
	int tissueSolverV1(const tissueInstance& instance, const std::vector< double >& chromosome);
	int tissueSolverV2(const tissueInstance& instance, const std::vector< double >& chromosome);
	int getFitness();
	
private:
	unsigned maxFinishTime;
	struct job {
		int op;
		int time;
		bool complet;
	};
};

#endif