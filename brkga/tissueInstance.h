#ifndef tissueINSTANCE_H
#define tissueINSTANCE_H

#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

class tissueInstance {
public:
	typedef std::runtime_error Error;

	tissueInstance();
	virtual ~tissueInstance();

	std::vector< std::vector<int> > opTime;
	std::vector< std::vector<int> > machineSetupTime;
	std::vector< std::vector<int> > opListCutTime;
	
	// Getters:
	int getNumOps() const;
	int getNumMachines() const;
	int getCutMachineSetup() const;
	
private:

	int numOp;
	int numMachines;
	int cutMachineSetup;

	//void read();
	//std::vector<double> convertToChromossome(std::vector<int> nodesOrder);
};

#endif