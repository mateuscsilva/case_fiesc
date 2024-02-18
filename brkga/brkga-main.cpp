/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018
 * Rodrigo Franco Toso (rfrancotoso@gmail.com) and
 * Mauricio G.C. Resende
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>
#include <cmath>
#include "brkgaAPI/BRKGA.h"
#include "brkgaAPI/MTRand.h"

#include "tissueSolver.h"
#include "tissueDecoder.h"
#include "tissueInstance.h"
#include "tissueVerifier.h"



int main(int argc, char* argv[]) {
	//if(argc < 2) { std::cerr << "usage: <tissueLIB-file>" << std::endl; return -1; }

	//std::cout << "Welcome to the BRKGA API sample driver.\nFinding a (heuristic) minimizer for "
	//		<< " the tissue Number." << std::endl;

	double timeLimit = 10;
	double readPe = 0.15;
	double readPm = 0.1;
	double readRhoe = 0.7;
	int numThreads = 1;
	int numGenerations = INT_MAX;
	int numPopulations = 1;
	int populationFactor = 1;
	int seed = 100;
		
	const clock_t begin = clock();
	// Read the instance:
	tissueInstance instance; 	// initialize the instance
	//instance.readV0();
	//instance.readV1();
	instance.readV2();
	
	std::cout<<instance.getNumOps()<<std::endl;


	tissueDecoder decoder(instance);		// initialize the decoder

	const long unsigned rngSeed = seed;	// seed to the random number generator
	MTRand rng(rngSeed);					// initialize the random number generator

	//const unsigned n = instance.getNumOps()*2;		// size of chromosomes
	//const unsigned n = instance.getNumOps();
	const unsigned n = instance.getNumOps()*3;
	int populationSizeC = (int) populationFactor*n;
	const unsigned p = std::max(100, populationSizeC);		// size of population
	const double pe = readPe;		// fraction of population to be the elite-set
	const double pm = readPm;		// fraction of population to be replaced by mutants
	const double rhoe = readRhoe;	// probability that offspring inherit an allele from elite parent
	const unsigned K = numPopulations;		// number of independent populations
	const unsigned MAXT = numThreads;	// number of threads for parallel decoding

	// initialize the BRKGA-based heuristic
	BRKGA< tissueDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	// BRKGA inner loop (evolution) configuration: Exchange top individuals
	const unsigned X_INTVL = INT_MAX;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = numGenerations;	// run for 1000 gens

	// BRKGA evolution configuration: restart strategy
	unsigned relevantGeneration = 1;	// last relevant generation: best updated or reset called
	const unsigned RESET_AFTER = INT_MAX;
	std::vector< double > bestChromosome;
	double bestFitness = INT_MAX;
	
	std::vector<unsigned> relGenerations;
	std::vector<double> relGenerationsTime;
	// Print info about multi-threading:
	#ifdef _OPENMP
		std::cout << "Running for " << MAX_GENS << " generations using " << MAXT
				<< " out of " << omp_get_max_threads()
				<< " available thread units..." << std::endl;
	#endif
	#ifndef _OPENMP
		std::cout << "Running for " << MAX_GENS
				<< " generations without multi-threading..." << std::endl;
	#endif
	
	
	// Run the evolution loop:
	double execTime;
	unsigned generation = 1;		// current generation
	
	do {
		algorithm.evolve();	// evolve the population for one generation

		// Bookeeping: has the best solution thus far improved?
		//std::cout<<generation<< " " << algorithm.getBestFitness() << "\n";
		if(algorithm.getBestFitness() < bestFitness) {
			// Save the best solution to be used after the evolution chain:
			relevantGeneration = generation;
			bestFitness = algorithm.getBestFitness();
			bestChromosome = algorithm.getBestChromosome();
			
			clock_t actual_time = clock();
			execTime = ((double) (actual_time - begin)) / (CLOCKS_PER_SEC);
			relGenerations.push_back(relevantGeneration);
			relGenerationsTime.push_back(execTime);
			
			std::cout << "\t" << generation
					<< ") Improved best solution thus far: "
					<< bestFitness << std::endl;
			
		}

		//  Evolution strategy: restart
		if(generation - relevantGeneration > RESET_AFTER) {
			//algorithm.reset();	// restart the algorithm with random keys
			//relevantGeneration = generation;
			
			/*
			std::cout << "\t" << generation << ") Reset at generation "
					<< generation << std::endl;
			*/
		}

		// Evolution strategy: exchange top individuals among the populations
		if(generation % X_INTVL == 0 && relevantGeneration != generation) {
			//algorithm.exchangeElite(X_NUMBER);
			
			/*
			std::cout << "\t" << generation
					<< ") Exchanged top individuals." << std::endl;
			*/
		}

		//std::cout<<"generation "<<generation<<" "<<bestFitness<<std::endl;
		++generation;
		clock_t actual_time = clock();
		execTime = ((double) (actual_time - begin)) / (CLOCKS_PER_SEC);
	} while (generation < MAX_GENS && (execTime < timeLimit));
	
	// print the fitness of the top 10 individuals of each population:
	
	std::cout << "Fitness of the top 10 individuals of each population:" << std::endl;
	const unsigned bound = std::min(p, unsigned(10));	// makes sure we have 10 individuals
	for(unsigned i = 0; i < K; ++i) {
		std::cout << "Population #" << i << ":" << std::endl;
		for(unsigned j = 0; j < bound; ++j) {
			std::cout << "\t" << j << ") "
					<< algorithm.getPopulation(i).getFitness(j) << std::endl;
		}
	}
	

	// rebuild the best solution:
	//tissueSolver bestSolution(instance, bestChromosome);

	// print its distance:
	//std::cout << "Best solution found has objective value = "
	//<< bestSolution.getFitness() << std::endl;


	const clock_t end = clock();
	std::cout << "BRKGA run finished in " << (end - begin) / double(CLOCKS_PER_SEC) << " s." << std::endl;
	
	double executionTime = (end - begin) / double(CLOCKS_PER_SEC);

}