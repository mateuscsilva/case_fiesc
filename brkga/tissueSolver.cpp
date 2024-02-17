#include "tissueSolver.h"
#include <iostream>
#include <cmath>
#include <set>
#include <queue>  
#include <utility>
#include <string>

tissueSolver::tissueSolver(const tissueInstance& instance, const std::vector< double >& chromosome) : maxFinishTime(-1) 
	{
	
	//maxFinishTime = tissueSolverV0(instance, chromosome);
	maxFinishTime = tissueSolverV1(instance, chromosome);

}

int tissueSolver::tissueSolverV0(const tissueInstance& instance, const std::vector< double >& chromosome){
	std::pair <double, int> pairPriority;
	std::vector< std::vector<int> > machines;
	std::priority_queue<std::pair<double, int> > notSelectedOps;
	double positionSize = 1/instance.getNumMachines();

	machines.resize(instance.getNumMachines());
	int size = chromosome.size() / 2;

	for(int i = 0; i < instance.getNumOps(); i++){ 
		std::pair <double, int> pairChromPriority;
		pairChromPriority = std::make_pair(chromosome[i], i);
		notSelectedOps.push(pairChromPriority); 
	}

	while(!notSelectedOps.empty()){
		pairPriority = notSelectedOps.top();
		int op = pairPriority.second;
		if(chromosome[op+instance.getNumOps()] > 0.5){
			machines[0].push_back(op);
		}else{
			machines[1].push_back(op);
		}
		notSelectedOps.pop();
	}
	
	int maxTemp = 0;
	for(unsigned i = 0; i < instance.getNumMachines(); i++) {
		int finishTime = 0;
		for(unsigned j = 0; j < machines[i].size(); j++) {
			finishTime += instance.machineSetupTime[i][0];
			finishTime += instance.opTime[machines[i][j]][0];
		}
		if(maxTemp < finishTime){
			maxTemp = finishTime;
		}
	}

	return maxTemp;
}

int tissueSolver::tissueSolverV1(const tissueInstance& instance, const std::vector< double >& chromosome){
	std::pair <double, int> pairPriority;
	std::priority_queue<std::pair<double, int> > notSelectedOps;
	std::vector<int> solution;
	std::vector<int> foldTime;
	int size = chromosome.size();
	int cutMachineSetup = 4;

	for(int i = 0; i < instance.getNumOps(); i++){ 
		std::pair <double, int> pairChromPriority;
		pairChromPriority = std::make_pair(chromosome[i], i);
		notSelectedOps.push(pairChromPriority); 
	}

	while(!notSelectedOps.empty()){
		pairPriority = notSelectedOps.top();
		int op = pairPriority.second;
		solution.push_back(op);
		notSelectedOps.pop();
	}
	
	int maxTemp = 0;
	for(unsigned i = 0; i < instance.getNumOps(); i++) {
		foldTime.push_back(instance.opTime[solution[i]][0]+2+maxTemp);
		maxTemp = foldTime[i];
	}

	int time = foldTime[0] + cutMachineSetup + instance.opListCutTime[solution[0]][0];
	for(unsigned i = 1; i < instance.getNumOps(); i++) {
		if(foldTime[i] >= time){
			time = foldTime[i] + cutMachineSetup + instance.opListCutTime[solution[i]][0];
		}else{
			time = time + cutMachineSetup + instance.opListCutTime[solution[0]][0];
		}
	}

	return time;
}

int tissueSolver::tissueSolverV2(const tissueInstance& instance, const std::vector< double >& chromosome){
	
}

tissueSolver::~tissueSolver() {
}

tissueSolver::getFitness(){
	return maxFinishTime;
}