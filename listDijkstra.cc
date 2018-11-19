#include "readGraph.h"
#include "shortestPath.h"
#include "BinaryHeap.h"
#include <iostream>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]){
	string graph_file=argv[1];
	string output_file=argv[2];
	string source_string = argv[3];
	string destination_string = argv[4];
	int source;
	int destination;
	int** adj;
	double** weights;
	int* lengths;
	string* vLabels;
	string** eLabels;
	ifstream f(graph_file);
	int numV = readGraph(f, adj, weights, lengths, vLabels, eLabels);
	for(int i=0; i<numV; i++){
		if(vLabels[i]==source_string){
			source = i;
		}
		if(vLabels[i]==destination_string){
			destination = i;
		}
	}
	double* dist;
	int* prev;

	auto t_s = chrono::system_clock::now();
	dijkstra(adj, weights, lengths, numV, source, dist, prev);	
	auto t_f = chrono::system_clock::now();
	auto dur=t_f-t_s;
	auto durationMS = chrono::duration_cast<chrono::microseconds>(dur);
	int* path;

	int path_l=getPath(source,destination,prev,path);
	ofstream ff(output_file);
	ff<<numV<<" "<<path_l-1<<endl;
	for(int i=0; i<numV; i++){
		ff<<vLabels[i]<<endl;
	}
	int idx1=0;
	int idx2=1;
	while(path[idx1]!=destination){	
		int adj_idx;
		bool found=false;
		int i=0;
		while(!found && i<lengths[path[idx1]]){
			if(adj[path[idx1]][i]==path[idx2]){
				adj_idx=i;
			}
			i+=1;
		}	
		ff<<path[idx1]<<" "<<path[idx2]<<" "<<weights[path[idx1]][adj_idx]<<" "<<eLabels[path[idx1]][adj_idx]<<endl;
		idx1+=1;
		idx2+=1;
	}

	cout<<"Total weight of the path: "<<dist[destination]<<endl;
	cout<<"Number of microseconds it takes for Dijkstra's algorithm to run: "<<(durationMS.count())<<endl;
	delete[] path;
	delete[] dist;
	delete[] prev;
	delete[] lengths;
	for(int i=0; i<numV; i++){
		delete[] adj[i];
		delete[] weights[i];
		delete[] eLabels[i];
	}
	delete[] adj;
	delete[] weights;
	delete[] eLabels;
	delete[] vLabels;
	return 0;
}