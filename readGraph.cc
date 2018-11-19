#include "readGraph.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

int readGraph(ifstream& fin, double**& matrix, string*& vLabels, string**& eLabels){
	int numVert;
	int numEdge;
	fin>>numVert;
	fin>>numEdge;
	//cout<<"num vert "<<numVert<<endl;
	//cout<<"num edge "<<numEdge<<endl;
	vLabels=new string[numVert];
	for(int i=0; i<numVert; i++){
		fin>>vLabels[i];
	}
	/*for(int i = 0; i<numVert; i++){
		cout<<vLabels[i]<<endl;
	}*/

	eLabels=new string*[numVert];
	for(int i=0; i<numVert; i++){
		eLabels[i]=new string[numVert];
		for(int j=0; j<numVert; j++){
			eLabels[i][j]="";
				
		}
	}
	matrix=new double*[numVert];
	for(int i=0; i<numVert; i++){
		matrix[i]=new double[numVert];
		for(int j=0; j<numVert; j++){
			if(i==j){
				matrix[i][j]=0;
			} else{
				matrix[i][j]=numeric_limits<double>::infinity();
			}	
		}
	}

	for(int i =0; i<numEdge;i++){
		int source;
		int destination;
		double weight;
		string label;
		fin>>source;
		fin>>destination;
		fin>>weight;
		fin>>label;
		eLabels[source][destination]=label;
		matrix[source][destination]=weight;
	}
	/*for(int i =0; i<numVert; i++){
		for(int j=0;j<numVert;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return numVert;
}

int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels){
	int numVert;
	int numEdge;
	fin>>numVert;
	fin>>numEdge;
	vLabels=new string[numVert];
	for(int i=0; i<numVert; i++){
		fin>>vLabels[i];
	}
	lengths = new int[numVert];
	for(int i=0; i<numVert; i++){
		lengths[i]=0;
	}
	//vector<int> sources(numEdge);
	vector<int> adjacent_verts(numEdge);
	vector<string> adjacent_names(numEdge);
	vector<double> adjacent_weights(numEdge);

	for(int i =0; i<numEdge; i++){
		int from;
		int to;
		double weight;
		string name;
		fin>>from;
		fin>>to;
		fin>>weight;
		fin>>name;
		lengths[from]+=1;
		//sources[i]=from;
		adjacent_verts[i]=to;
		adjacent_weights[i]=weight;
		adjacent_names[i]=name;
	}

	adj=new int*[numVert];
	for(int i=0; i<numVert; i++){
		adj[i]=new int[lengths[i]];
	}
	weights=new double*[numVert];
	for(int i=0; i<numVert; i++){
		weights[i]=new double[lengths[i]];
	}
	eLabels=new string*[numVert];
	for(int i=0; i<numVert; i++){
		eLabels[i]=new string[lengths[i]];
	}
	int edge_iter=0;
	for(int i=0; i<numVert; i++){
		for(int j=0; j<lengths[i];j++){
			adj[i][j]=adjacent_verts[edge_iter];
			weights[i][j]=adjacent_weights[edge_iter];
			eLabels[i][j]=adjacent_names[edge_iter];
			edge_iter+=1;
		}

	}

	/*cout<<" adjs "<<endl;
	for(int i =0; i<numVert; i++){
		cout<<i<<":  ";
		for(int j=0; j<lengths[i];j++){
			cout<<adj[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<" weights "<<endl;
	for(int i =0; i<numVert; i++){
		cout<<i<<":  ";
		for(int j=0; j<lengths[i];j++){
			cout<<weights[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<" names "<<endl;
	for(int i =0; i<numVert; i++){
		cout<<i<<":  ";
		for(int j=0; j<lengths[i];j++){
			cout<<eLabels[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return numVert;

}
int readGraph(ifstream& fin, int**& edgeList, double*& weights, int& numEdges, string*& vLabels, string*& eLabels){
	int numVert;
	fin>>numVert;
	fin>>numEdges;
	vLabels=new string[numVert];
	for(int i=0; i<numVert; i++){
		fin>>vLabels[i];
	}
	eLabels=new string[numEdges];
	weights=new double[numEdges];
	edgeList = new int*[numEdges];
	for(int i=0; i<numEdges; i++){
		int from;
		int to;
		double weight;
		string name;
		fin>>from;
		fin>>to;
		fin>>weight;
		fin>>name;
		int* cell = new int[2];
		cell[0]=from;
		cell[1]=to;
		edgeList[i]=cell;
		eLabels[i]=name;
		weights[i]=weight;
	}
	return numVert;
}







