#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "tissueInstance.h"

tissueInstance::tissueInstance(): numOp(4), numMachines(2), cutMachineSetup(5){

	opTime.resize(numOp);
	opTime[1-1].push_back(12); 
	opTime[2-1].push_back(10);
	opTime[3-1].push_back(8);
	opTime[4-1].push_back(4);

	machineSetupTime.resize(numMachines);	
	machineSetupTime[0].push_back(2);
	machineSetupTime[1].push_back(3);

	opListCutTime.resize(numOp);
	opListCutTime[1-1].push_back(4);
	opListCutTime[2-1].push_back(4);
	opListCutTime[3-1].push_back(6);
	opListCutTime[4-1].push_back(6);	
}

int tissueInstance::getNumOps() const { return numOp; }
int tissueInstance::getNumMachines() const { return numMachines; }
int tissueInstance::getCutMachineSetup() const { return cutMachineSetup; }


tissueInstance::~tissueInstance() { }


