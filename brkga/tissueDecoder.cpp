#include "tissueDecoder.h"

tissueDecoder::tissueDecoder(const tissueInstance& _instance) : 
	instance(_instance) {
}

tissueDecoder::~tissueDecoder() {
}

double tissueDecoder::decode(const std::vector< double >& chromosome) const {
	// 1) Solve the problem (i.e., create a tour out of this chromosome):
	// Avoids race conditions by making sure we have a single TSPSolver for each thread calling
	// ::decode (as long as TSPSolver does not make use of 'static' or other gimmicks):
	tissueSolver solver(instance, chromosome);

	// 2) Extract the fitness (tour distance):
	const unsigned fitness = solver.getFitness();

	// 3) Return:
	return double(fitness);
}