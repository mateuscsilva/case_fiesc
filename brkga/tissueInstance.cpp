#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "tissueInstance.h"

tissueInstance::tissueInstance(): numOp(4), numMachines(2), cutMachineSetup(4), cutMachineTableChange(5){

		
}

void tissueInstance::readV0(){
	numMachines = 2;
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

void tissueInstance::readV1(){
	numMachines = 1;
	opTime.resize(numOp);
	opTime[1-1].push_back(18); 
	opTime[2-1].push_back(14);
	opTime[3-1].push_back(12);
	opTime[4-1].push_back(6);

	machineSetupTime.resize(numMachines);	
	machineSetupTime[0].push_back(2);

	opListCutTime.resize(numOp);
	opListCutTime[1-1].push_back(4);
	opListCutTime[2-1].push_back(4);
	opListCutTime[3-1].push_back(6);
	opListCutTime[4-1].push_back(6);
} 

void tissueInstance::readV2(){
	numOp=9;
	opTime.resize(numOp);
	opTime[1-1].push_back(18); 
	opTime[2-1].push_back(14);
	opTime[3-1].push_back(12);
	opTime[4-1].push_back(6);
	opTime[5-1].push_back(36); 
	opTime[6-1].push_back(9);
	opTime[7-1].push_back(9);
	opTime[8-1].push_back(12);
	opTime[9-1].push_back(12);

	machineSetupTime.resize(numMachines);	
	machineSetupTime[0].push_back(2);
	machineSetupTime[1].push_back(3);

	opListCutTime.resize(numOp);
	opListCutTime[1-1].push_back(4);
	opListCutTime[2-1].push_back(4);
	opListCutTime[3-1].push_back(6);
	opListCutTime[4-1].push_back(6);
	opListCutTime[5-1].push_back(12);
	opListCutTime[6-1].push_back(6);
	opListCutTime[7-1].push_back(2);
	opListCutTime[8-1].push_back(2);
	opListCutTime[9-1].push_back(4);

	opSize.resize(numOp);
	opSize[1-1].push_back(3);
	opSize[2-1].push_back(3);
	opSize[3-1].push_back(4);
	opSize[4-1].push_back(4);
	opSize[5-1].push_back(8);
	opSize[6-1].push_back(6);
	opSize[7-1].push_back(2);
	opSize[8-1].push_back(2);
	opSize[9-1].push_back(4);
} 

int tissueInstance::getNumOps() const { return numOp; }
int tissueInstance::getNumMachines() const { return numMachines; }
int tissueInstance::getCutMachineSetup() const { return cutMachineSetup; }


tissueInstance::~tissueInstance() { }


