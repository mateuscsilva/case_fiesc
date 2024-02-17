#ifndef tissueDECODER_H
#define tissueDECODER_H

#include "tissueSolver.h"
#include "tissueInstance.h"

class tissueDecoder {
public:
	tissueDecoder(const tissueInstance& instance);
	virtual ~tissueDecoder();

	double decode(const std::vector< double >& chromosome) const;

private:
	const tissueInstance& instance;
};

#endif