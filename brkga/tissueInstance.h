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
	std::vector< std::vector<int> > opSize;
	int cutMachineSetup;
	int cutMachineTableChange;
	
	// Getters:
	void readV0();
	void readV1();
	void readV2();
	int getNumOps() const;
	int getNumMachines() const;
	int getCutMachineSetup() const;
	
private:

	int numOp;
	int numMachines;

	//void read();
	//std::vector<double> convertToChromossome(std::vector<int> nodesOrder);
};

#endif