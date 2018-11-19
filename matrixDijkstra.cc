#include "readGraph.h"
#include "shortestPath.h"
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
	double** mat;
	string* verts;
	string** edges;
	ifstream f(graph_file);
	int numV=readGraph(f,mat,verts,edges);
	for(int i=0; i<numV; i++){
		if(verts[i]==source_string){
			source = i;
		}
		if(verts[i]==destination_string){
			destination = i;
		}
	}
	double* dist;
	int* prev;
	auto t_s = chrono::system_clock::now();
	dijkstra(mat,numV,source,dist,prev);
	auto t_f = chrono::system_clock::now();
	auto dur=t_f-t_s;
	auto durationMS = chrono::duration_cast<chrono::microseconds>(dur);
	int* path;
	int path_l=getPath(source,destination,prev,path);
	ofstream ff(output_file);
	ff<<numV<<" "<<path_l-1<<endl;
	for(int i=0; i<numV; i++){
		ff<<verts[i]<<endl;
	}
	int idx1=0;
	int idx2=1;
	while(path[idx1]!=destination){		
		ff<<path[idx1]<<" "<<path[idx2]<<" "<<mat[path[idx1]][path[idx2]]<<" "<<edges[path[idx1]][path[idx2]]<<endl;
		idx1+=1;
		idx2+=1;
	}

	/*for(int i=0;i<path_l+1;i++){
		cout<<path[i]<<endl;
	}*/
	cout<<"Total weight of the path: "<<dist[destination]<<endl;
	cout<<"Number of microseconds it takes for Dijkstra's algorithm to run: "<<(durationMS.count())<<endl;
	delete[] path;
	delete[] dist;
	delete[] prev;
	for(int i=0; i<numV; i++){
		delete[] edges[i];
		delete[] mat[i];
	}
	delete[] edges;
	delete[] mat;
	delete[] verts;
	return 0;
}