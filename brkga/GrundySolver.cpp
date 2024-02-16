#include "GrundySolver.h"
#include <iostream>
#include <cmath>
#include <set>
#include <queue>  
#include <utility>
#include <string>

GrundySolver::GrundySolver(const GrundyInstance& instance, const std::vector< double >& chromosome,
	std::string solverTye) : color(0), nodesColor(instance.getNumNodes()) {
	
	if(solverTye.compare("grundyN") == 0){
		color = GrundySolverNormal(instance, chromosome, nodesColor);
	}else if(solverTye.compare("grundyNP") == 0){
		color = GrundySolverNormalPriority(instance, chromosome, nodesColor);
	}else if(solverTye.compare("grundyC") == 0){
		color = GrundySolverConnected(instance, chromosome, nodesColor);
	}else if(solverTye.compare("grundyCP") == 0){
		color = GrundySolverConnectedPriority(instance, chromosome, nodesColor);
	}else if(solverTye.compare("grundyNPB") == 0){
		color = GrundySolverNormalPriorityBins(instance, chromosome, nodesColor);
	}else{
		color = GrundySolverNormal(instance, chromosome, nodesColor);
	}

}

GrundySolver::~GrundySolver() {
}


int GrundySolver::GrundySolverNormal(const GrundyInstance& instance, 
	const std::vector< double >& chromosome, std::vector<int>& nodesColor){
	
	int color = 0;
	std::vector <int> colorNodes, notSelectedNodes;
	colorNodes.resize(instance.getNumNodes());

	for(int i = 0; i < instance.getNumNodes(); i++){ notSelectedNodes.push_back(i); }
	
	for(unsigned i = 0; i < chromosome.size(); i++) {
		int position = lround(chromosome[i]*(notSelectedNodes.size()-1));
		int vertex = notSelectedNodes[position];
		colorNodes[vertex] = chooseNodeColor(instance, colorNodes, vertex);
		notSelectedNodes.erase(notSelectedNodes.begin()+position);
		nodesOrder.push_back(vertex);

		if(colorNodes[vertex] > color){
			color = colorNodes[vertex];
		}
	}
	nodesColor = colorNodes;
	return color;
}

int GrundySolver::GrundySolverNormalPriority(const GrundyInstance& instance, 
	const std::vector< double >& chromosome, std::vector<int>& nodesColor){
	
	int color = 0;
	std::pair <double, int> pairPriorityVertex;
	std::vector <int> colorNodes;
	std::priority_queue<std::pair<double, int> > notSelectedNodes;
	
	colorNodes.resize(instance.getNumNodes());
	

	for(int i = 0; i < instance.getNumNodes(); i++){ 
		std::pair <double, int> pairChromPriority;
		pairChromPriority = std::make_pair(chromosome[i], i);
		notSelectedNodes.push(pairChromPriority); 
	}
	
	while(!notSelectedNodes.empty()) {
		pairPriorityVertex = notSelectedNodes.top();
		int vertex = pairPriorityVertex.second;
		colorNodes[vertex] = chooseNodeColor(instance, colorNodes, vertex);
		notSelectedNodes.pop();	
		nodesOrder.push_back(vertex);

		if(colorNodes[vertex] > color){
			color = colorNodes[vertex];
		}
	}
	nodesColor = colorNodes;
	return color;
}


int GrundySolver::GrundySolverNormalPriorityBins(const GrundyInstance& instance, 
	const std::vector< double >& chromosome, std::vector<int>& nodesColor){

	//nodesOrder.clear();
	int nodes = instance.getNumNodes();	
	int color = 0;
	std::pair <double, int> pairPriorityVertex;
	std::vector <int> colorNodes;
	std::priority_queue<std::pair<double, int> > notSelectedNodes;
	
	colorNodes.resize(instance.getNumNodes());

	std::vector<double> auxChromosome;
	for(int i = 0; i < chromosome.size(); i++){
		double binValue = chromosome[i]*(1 + instance.getMaxDegree() - instance.getNumberOfNeighbors(i));
		auxChromosome.push_back(binValue);
	}

	for(int i = 0; i < instance.getNumNodes(); i++){ 
		std::pair <double, int> pairChromPriority;
		pairChromPriority = std::make_pair(auxChromosome[i], i);
		notSelectedNodes.push(pairChromPriority); 
	}
	

	while(!notSelectedNodes.empty()) {
		pairPriorityVertex = notSelectedNodes.top();
		int vertex = pairPriorityVertex.second;
		colorNodes[vertex] = chooseNodeColor(instance, colorNodes, vertex);
		notSelectedNodes.pop();	
		nodesOrder.push_back(vertex);

		if(colorNodes[vertex] > color){
			color = colorNodes[vertex];
		}
	}
	nodesColor = colorNodes;
	//std::cout<<"nodesOrder = "<<nodesOrder.size()<<"\n";
	return color;
}


int GrundySolver::GrundySolverConnected(const GrundyInstance& instance, 
	const std::vector< double >& chromosome, std::vector<int>& nodesColor){
	
	int color = 0;
	std::vector <int> colorNodes;
	std::set<int> notSelectedNodes;
	std::set<int>::iterator it;

	colorNodes.resize(instance.getNumNodes());

	int firstVertex = lround(chromosome[0]*(instance.getNumNodes()-1)); 
	colorNodes[firstVertex] = 1;
	nodesOrder.push_back(firstVertex);

	for(int i = 0; i < instance.nodes[firstVertex].size(); i++){
		notSelectedNodes.insert(instance.nodes[firstVertex][i]);
	}	

	for(unsigned i = 1; i < chromosome.size(); i++) {
		int position = lround(chromosome[i]*(notSelectedNodes.size()-1));
		it = notSelectedNodes.begin();
		for(int iter = 0; iter < position; iter++){ it++; }

		int vertex = *it;
		colorNodes[vertex] = chooseNodeColor(instance, colorNodes, vertex);
		
		notSelectedNodes.erase(it);
		nodesOrder.push_back(vertex);

		for(int j = 0; j < instance.nodes[vertex].size(); j++){
			if(colorNodes[instance.nodes[vertex][j]] == 0){
				notSelectedNodes.insert(instance.nodes[vertex][j]);
			}
		}

		if(colorNodes[vertex] > color){
			color = colorNodes[vertex];
		}
	}
	nodesColor = colorNodes;
	return color;
}


int GrundySolver::GrundySolverConnectedPriority(const GrundyInstance& instance, 
	const std::vector< double >& chromosome, std::vector<int>& nodesColor){
	
	int bestColor = 0, countColoredVertex = 0;
	std::pair <double, int> pairPriorityVertex;
	std::vector <int> colorNodes;
	std::priority_queue<std::pair<double, int> > notSelectedNodes;
	std::vector<int> alreadyEnqueued;
	
	colorNodes.resize(instance.getNumNodes());
	alreadyEnqueued.resize(instance.getNumNodes());

	while(countColoredVertex < instance.getNumNodes()){
		int color = 0;
		int maxValue = -1;
		int maxValuePos = 0;
		for(int i = 0; i < chromosome.size(); i++){ 
			if(maxValue < chromosome[i] && alreadyEnqueued[i] == 0){
				maxValuePos = i;
				maxValue = chromosome[i];	
			}
		}

		int firstVertex = maxValuePos; 
		colorNodes[firstVertex] = 1;
		alreadyEnqueued[firstVertex] = 1;
		countColoredVertex++;
		nodesOrder.push_back(firstVertex);
		
		for(int i = 0; i < instance.nodes[firstVertex].size(); i++){
			std::pair <double, int> pairChromPriority;
			pairChromPriority = std::make_pair(chromosome[instance.nodes[firstVertex][i]], 
			instance.nodes[firstVertex][i]);
			notSelectedNodes.push(pairChromPriority); 
			alreadyEnqueued[instance.nodes[firstVertex][i]] = 1;
		}

		while(!notSelectedNodes.empty()) {
			pairPriorityVertex = notSelectedNodes.top();
			int vertex = pairPriorityVertex.second;
			colorNodes[vertex] = chooseNodeColor(instance, colorNodes, vertex);
			countColoredVertex++;
			notSelectedNodes.pop();	
			nodesOrder.push_back(vertex);

			for(int j = 0; j < instance.nodes[vertex].size(); j++){
				if(alreadyEnqueued[instance.nodes[vertex][j]] == 0){
					std::pair <double, int> pairChromPriority;
					pairChromPriority = std::make_pair(chromosome[instance.nodes[vertex][j]], 
					instance.nodes[vertex][j]);
					notSelectedNodes.push(pairChromPriority); 
					alreadyEnqueued[instance.nodes[vertex][j]] = 1;
				}
			}

			if(colorNodes[vertex] > color){
				color = colorNodes[vertex];
			}
		}

		if(bestColor < color){
			bestColor = color;
		}	
	}

	nodesColor = colorNodes;
	return bestColor;
}


unsigned GrundySolver::getHighestColor() const { return color; }


int GrundySolver::chooseNodeColor(const GrundyInstance& instance, const std::vector< int >& colorNodes,
 	int vertex) const {
	
	int actualColor = 0;
	bool isChoosedColor = false;
	while(!isChoosedColor){
		actualColor++;
		isChoosedColor = true;
		for(int i=0; i < instance.nodes[vertex].size(); i++){
			if(actualColor == colorNodes[instance.nodes[vertex][i]]){
				isChoosedColor = false;
				break;
			}
		}
	}
	return actualColor; 
}

std::vector<int> GrundySolver::getNodesColor() const{
	return nodesColor;
}

std::vector<int> GrundySolver::getNodesOrder() const{
	return nodesOrder;
}