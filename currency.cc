#include <iostream>
#include "shortestPath.h"
#include "readGraph.h"
#include <chrono>
#include <cmath>

using namespace std;
int main(int argc, char* argv[]){
	string graph_file=argv[1];
	string output_file=argv[2];
	string source_string = argv[3];
	string destination_string = argv[4];
	double exchange_rate = atof(argv[5]);

	int source;
	int destination;
	string* vLabels;
	string* eLabels;
	int** edgeList;
	double* weights;
	int numEdges;
	ifstream f(graph_file);
	int numVertices = readGraph(f, edgeList, weights, numEdges, vLabels, eLabels);
	for(int i=0; i<numVertices; i++){
		if(vLabels[i]==source_string){
			source = i;
		}
		if(vLabels[i]==destination_string){
			destination = i;
		}
	}
	for( int i=0; i<numEdges; i++){
		weights[i]=-log(weights[i]*(1-exchange_rate));
	}
	int* prev;
	double* dist;
	/*cout<<"all weights before bellf"<<endl;
	for( int i=0; i<numEdges; i++){
		cout<<exp(-weights[i])<<endl;
	}
	cout<<"done"<<endl;*/
	auto t_s = chrono::system_clock::now();
	int bellmanFord_result = bellmanFord(edgeList, weights, numVertices, numEdges, source, dist,prev);
	auto t_f = chrono::system_clock::now();
	//cout<<bellmanFord_result<<endl;
	auto dur=t_f-t_s;
	auto durationMS = chrono::duration_cast<chrono::microseconds>(dur);
	ofstream out_f(output_file);
	/*cout<<"all weights after bellf"<<endl;
	for( int i=0; i<numEdges; i++){
		cout<<exp(-weights[i])<<endl;
	}
	cout<<"done"<<endl;*/



	if(bellmanFord_result==-1){
		//cout<<"No negative cycles!"<<endl;
		
		int* path;
		int path_l=getPath(source,destination,prev,path);
		out_f<<numVertices<<" "<<path_l-1<<endl;
		for(int i=0; i<numVertices; i++){
			out_f<<vLabels[i]<<endl;
			//cout<<path[i]<<endl;
		}
		int idx1=0;
		int idx2=1;
		double total_w = 0;
		while(idx2!=path_l){
			for(int i=0; i<numEdges; i++){
				if(edgeList[i][0]==path[idx1] && edgeList[i][1]==path[idx2]){
					total_w+=weights[i];
					out_f<<path[idx1]<<" "<<path[idx2]<<" "<<exp(-weights[i])<<" "<<eLabels[i]<<endl;
				}
			}
			idx1+=1;
			idx2+=1;
		}
		cout<<"Effective Exchange Rate: "<<exp(-total_w)<<endl;
		cout<<"Runtime in microseconds: "<<(durationMS.count())<<endl;
		delete[] path;
		for (int i=0; i<numEdges; i++){
			delete[] edgeList[i];
		}
		delete[] dist;
		delete[] prev;
		delete[] vLabels;
		delete[] eLabels;
		delete[] edgeList;
		delete[] weights;
		//delete[] cycle;
		return 0;
	}

	int* cycle;
	int length_of_cycle=getCycle(bellmanFord_result, prev, cycle);
	out_f<<numVertices<<" "<<length_of_cycle-1<<endl;
	
	
	for(int i=0; i<length_of_cycle-1; i++){
		out_f<<vLabels[cycle[i]]<<endl;
	}

	//int start_vert=cycle[length_of_cycle-1];
	int idx1=0;
	int idx2=1;
	double total_w = 0;
	while(idx2!=length_of_cycle){
		for(int i=0; i<numEdges; i++){
			if(edgeList[i][0]==cycle[idx1] && edgeList[i][1]==cycle[idx2]){
				total_w+=weights[i];
				out_f<<cycle[idx1]<<" "<<cycle[idx2]<<" "<<exp(-weights[i])<<" "<<eLabels[i]<<endl;
			}
		}
		idx1+=1;
		idx2+=1;
	}
	cout<<"Arbitrage Opportunity Detected!"<<endl;
	cout<<"Toatal weight: "<<exp(-total_w)<<endl;
	cout<<"Runtime in microseconds: "<<(durationMS.count())<<endl;

	for (int i=0; i<numEdges; i++){
		delete[] edgeList[i];
	}
	delete[] dist;
	delete[] prev;
	delete[] vLabels;
	delete[] eLabels;
	delete[] edgeList;
	delete[] weights;
	delete[] cycle;
	return 0;

}