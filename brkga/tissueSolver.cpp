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
	//maxFinishTime = tissueSolverV1(instance, chromosome);
	maxFinishTime = tissueSolverV2(instance, chromosome);

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
	std::pair <double, int> pairPriority;
	std::priority_queue<std::pair<double, int> > notSelectedOps;
	std::vector<int> solution;
	std::vector< std::vector<int> > foldTime;
	std::vector< std::vector<int> > machines;
	std::vector< job > table1;
	std::vector< job > table2;
	job auxTuple;
	int size = instance.getNumOps();
	int cutMachineSetup = 4;
	int tableSize = 10;
	int ocSpacetable1 = 0;
	int ocSpacetable2 = 0;
	int BigM = 100000;
	int timeLimit = 1000;

	machines.resize(instance.getNumMachines());
	foldTime.resize(instance.getNumMachines());

	for(int i = 0; i < instance.getNumOps(); i++){ 
		std::pair <double, int> pairChromPriority;
		pairChromPriority = std::make_pair(chromosome[i], i);
		notSelectedOps.push(pairChromPriority); 
	}

	while(!notSelectedOps.empty()){
		pairPriority = notSelectedOps.top();
		int op = pairPriority.second;
		if(chromosome[op+size] > 0.5){
			machines[0].push_back(op);
		}else{
			machines[1].push_back(op);
		}	
		notSelectedOps.pop();
	}

	for(int i = 0; i < instance.getNumMachines(); i++) {
		int maxTemp = 0;
		for(int j = 0; j < machines[i].size(); j++){
			foldTime[i].push_back(instance.opTime[machines[i][j]][0]+ instance.machineSetupTime[i][0] + maxTemp);
			maxTemp = foldTime[i][j];
		}
	}

	int time = 0;
	int setup1 = 0;
	int setup2 = 0;
	int position1 = 0;
	int position2 = 0;
	bool folding1 = false;
	bool folding2 = false;
	int posCutElementMachine = 0;
	int cutSetup = 0;
	int timeChangeTable = 0;
	int cutTime = 0;
	bool isCutting = false;
	bool isChangingTable = false;
	bool machineTable1 = true;
	bool cutTable1 = false;

	while(time < timeLimit){

		if(position1 >= machines[0].size() && position2 >= machines[1].size()){
			break;
		}

		std::cout<<position1<<" "<<position2<<"\n";
		if(isChangingTable && timeChangeTable>=instance.cutMachineTableChange){
			timeChangeTable=0;
			isChangingTable=false;
		}

		//std::cout<<"2\n";
		if(table1.size() > 0 && table1[table1.size()-1].time == time){
			table1[table1.size()-1].complet = true;
			folding1=false;
			setup1=0;
		}

		//std::cout<<"3\n";
		if(table2.size() > 0 && table2[table2.size()-1].time == time){
			table2[table2.size()-1].complet = true;
			folding2=false;
			setup2=0;
		}

		//std::cout<<"4\n";
		if(isCutting && cutTime == time){
			isCutting = false;
			if(cutTable1){
				ocSpacetable1 = ocSpacetable1 - instance.opSize[table1[0].op][0];
				table1.erase(table1.begin());
				std::cout<<"CUT TABLE1\n";
			}else{
				ocSpacetable2 = ocSpacetable2 - instance.opSize[table2[0].op][0];
				table2.erase(table2.begin());
				std::cout<<"CUT TABLE2\n";
			}
			posCutElementMachine++;
		}

		//std::cout<<"5\n";
		if(cutSetup >= instance.cutMachineSetup && !isChangingTable && !isCutting){
			if((table1.size() > 0 && table1[0].complet) | (table2.size() > 0 && table2[0].complet)){
				if(chromosome[posCutElementMachine+2*size] > 0.5 && (table1.size() > 0 && table1[0].complet)){
					isCutting = true;
					cutTime = time + instance.opListCutTime[table1[0].op][0];
					cutTable1 = true;
				}else if(table2.size() > 0 && table2[0].complet){
					isCutting = true;
					cutTime = time + instance.opListCutTime[table2[0].op][0];
					cutTable1 = false;
				}
			}
		}

		//std::cout<<"6\n";
		if(((table1.size() > 0 && table1[0].complet) | (table2.size() > 0 && table2[0].complet))
			&& cutSetup < instance.cutMachineSetup && !isChangingTable && !isCutting){
					if(chromosome[posCutElementMachine+2*size] > 0.5){
						if(machineTable1){
							cutSetup++;
						}else{
							isChangingTable=true;
							machineTable1=false;
						}
					}else{
						if(!machineTable1){
							cutSetup++;
						}else{
							isChangingTable=true;
							machineTable1=true;
						}
					}	
		}

		//std::cout<<"7\n";
		if(isChangingTable && timeChangeTable<instance.cutMachineTableChange){
			timeChangeTable++;
		}

		//std::cout<<"8\n";
		//std::cout<<folding1<<" "<<setup1<<" " << instance.machineSetupTime[0][0] << "\n";
		//std::cout<<position1<<" "<<machines[0].size()<<" " << ocSpacetable1 << "\n";
		//std::cout<<instance.opSize[machines[0][position1]][0]<<" "<<tableSize<< "\n";
		if(!folding1 && setup1 < instance.machineSetupTime[0][0] && position1 < machines[0].size() && 
			ocSpacetable1 + instance.opSize[machines[0][position1]][0] <= tableSize){
			setup1++;
		}
		
		//std::cout<<"9\n";
		if(!folding1 && setup2 < instance.machineSetupTime[1][0] && position2 < machines[1].size() && 
			ocSpacetable2 + instance.opSize[machines[1][position2]][0] <= tableSize){
			setup2++;
		}

		//std::cout<<"10\n";
		if(setup1 >= instance.machineSetupTime[0][0] &&  position1 < machines[0].size() && 
			ocSpacetable1 + instance.opSize[machines[0][position1]][0] <= tableSize){
			ocSpacetable1 += instance.opSize[machines[0][position1]][0];
			auxTuple.op=machines[0][position1];
			auxTuple.time=time+instance.opTime[machines[0][position1]][0];
			auxTuple.complet=false;
			table1.push_back(auxTuple);
			folding1 = true;
			position1++;
		}
		
		//std::cout<<"11\n";
		if(setup2 >= instance.machineSetupTime[1][0] && position2 < machines[1].size() && 
			ocSpacetable2 + instance.opSize[machines[1][position2]][0] <= tableSize){
			//std::cout<<"11a"<<machines[1][position2]<<"\n";
			ocSpacetable2 += instance.opSize[machines[1][position2]][0];
			//std::cout<<"11b\n";
			//std::cout<<"11c\n";
			auxTuple.op=machines[1][position2];
			//std::cout<<"11d"<<machines[1][position2]<<"\n";
			auxTuple.time=time+instance.opTime[machines[1][position2]][0];
			//std::cout<<"11e\n";
			auxTuple.complet=false;
			//std::cout<<"11f\n";
			table2.push_back(auxTuple);
			//std::cout<<"11g\n";
			folding2 = true;
			//std::cout<<"11h\n";
			position2++;
		}
		time++;
		//std::cout<<"AQUUUI = "<<time<<"\n";
	}

	//std::cout<<"FIIIIIIIIMMM = "<<time<<"\n";
	return time;


}

tissueSolver::~tissueSolver() {
}

tissueSolver::getFitness(){
	return maxFinishTime;
}