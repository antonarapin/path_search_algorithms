#include "shortestPath.h"
#include <iostream>
#include <limits>
#include "BinaryHeap.h"
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev){
	dist = new double[numVertices];
	prev = new int[numVertices];
	bool* in = new bool[numVertices];
	for (int i=0; i<numVertices; i++){
		dist[i]=numeric_limits<double>::infinity();
		prev[i]=std::numeric_limits<int>::quiet_NaN();
		in[i]=false;
	}
	dist[source]=0;
	in[source]=true;
	int cur_idx = source;
	for(int i=1; i<numVertices; i++){
		for(int j=0; j<numVertices; j++){
			if(!in[j] && (dist[cur_idx]+matrix[cur_idx][j])<dist[j]){
				dist[j]=dist[cur_idx]+matrix[cur_idx][j];
				prev[j]=cur_idx;
			}
		}
		double min = numeric_limits<double>::infinity();
		for(int j=0; j<numVertices;j++){
			if(!in[j] && dist[j]<min){
				cur_idx=j;
				min=dist[j];
			}
		}
		in[cur_idx]=true;
		
	}
	/*cout<<"************"<<endl;
	for(int t=0; t<numVertices;t++){
		cout<<t<<" "<<prev[t]<<endl;
	}
	cout<<"************"<<endl;*/
	delete[] in;
}

int getPath(int source, int dest, const int* prev, int*& path){
	int cur_idx=dest;
	int length=0;
	while(cur_idx!=source){
		//cout<<cur_idx<<endl;
		cur_idx=prev[cur_idx];
		length+=1;
	}
	path = new int[length+1];
	int acc=length-1;
	cur_idx=dest;
	path[length]=dest;
	while(cur_idx!=source){
		path[acc]=prev[cur_idx];
		cur_idx=prev[cur_idx];
		acc-=1;
	}
	//path[length]=dest;
	return length+1;
}

void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev){
	dist = new double[numVertices];
	prev = new int[numVertices];
	for (int i=0; i<numVertices; i++){
		dist[i]=numeric_limits<double>::infinity();
		prev[i]=std::numeric_limits<int>::max();
	}
	BinaryHeap bheap(dist,numVertices);
	bheap.decreasePriority(source,0);
	
	int n=bheap.getMin();

	bheap.popMin();
	dist[n]=0;
	prev[n]=n;
	for(int i=0; i<numVertices-1;i++){
		
		for(int j=0; j<lengths[n];j++){
			
			
			if (bheap.contains(adj[n][j]) && (dist[n]+weights[n][j])<bheap.getPriority(adj[n][j])){
				bheap.decreasePriority(adj[n][j],(dist[n]+weights[n][j]));
				int tmp=n;
				prev[adj[n][j]]=tmp;
				
			}
			
			
		}
		n=bheap.getMin();
		
		dist[n]=bheap.getPriority(n);
		
		
		bheap.popMin();
		//bheap.printHeap();
		

	}
	/*cout<<"************"<<endl;
	for(int t=0; t<numVertices;t++){
		cout<<t<<" "<<prev[t]<<endl;
	}
	cout<<"************"<<endl;*/
}
int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev){
	dist = new double[numVertices];
	prev = new int[numVertices];
	for(int i=0; i<numVertices;i++){
		dist[i]=numeric_limits<double>::infinity();
		prev[i]=numeric_limits<int>::quiet_NaN();
	}
	dist[source]=0;
	for(int i=0; i<(numVertices+1); i++){
		for(int j=0; j<numEdges;j++){
			const int* const cur_edge=edges[j];
			if((dist[cur_edge[0]] + weights[j])<dist[cur_edge[1]]){
				dist[cur_edge[1]] = dist[cur_edge[0]] + weights[j]; 
				prev[cur_edge[1]] = cur_edge[0];
				if(i==(numVertices)){
					//cout<<"neg cyc"<<endl;
					return cur_edge[1];
				}
			}
		}
	}
	//cout<<"no neg cyc"<<endl;
	return -1;
}
int getCycle(int vertex, const int* prev, int*& cycle){
	
	vector<int> vert_v;
	vert_v.push_back(vertex);
	int cycle_length=1;
	bool done = false;
	int cur_idx = vertex;
	while(!done){
		cur_idx = prev[cur_idx];
		if(cur_idx>vert_v.size()){
			for(int c=0; c<cur_idx-vert_v.size();c++){
				vert_v.push_back(false);
			}
			vert_v[cur_idx]=true;
		} else{
			if(vert_v[cur_idx]==true){
				done=true;
			}else{
				vert_v[cur_idx]=false;
			}
		}
		
	}
	done=false;
	int cycle_start=cur_idx;
	while(!done){
		cycle_length+=1;
		cur_idx = prev[cur_idx];
		if(cur_idx==cycle_start){
			done=true;
		}
	}
	cycle = new int[cycle_length];
	for(int i=0; i<cycle_length; i++){
		cycle[cycle_length-1-i]=cur_idx;
		cur_idx=prev[cur_idx];
	}
	return cycle_length;

}
void getMinVertex(double* dist, int* prev, bool* in, int numThreads, int start, int end, int* min){
	
	if(end==start+1){
		*min=start;
		
		
		//cout<<"value at "<<start<<" = "<<dist[start];
	} else{
		int lmin;
		int rmin;
		if(numThreads==1){
			int mid = (start+end)/2;
			getMinVertex(dist,prev,in,1,start,mid,&lmin);
			getMinVertex(dist,prev,in,1,mid,end,&rmin);
		} else{
			int halfnumthreads = numThreads/2;
			int mid = start+halfnumthreads*((end-start)/numThreads);
			thread otherThread(getMinVertex, dist,prev,in,halfnumthreads,start,mid,&lmin);
			getMinVertex(dist,prev,in,halfnumthreads,mid,end,&rmin);
			otherThread.join();
		}
		//if nothing is in tree, then handle
		if(in[lmin] && !in[rmin]){
			*min=rmin;
		} else if(in[rmin] && !in[lmin]){
			*min=lmin;
		} else if(in[lmin] && in[rmin]){
			*min=lmin;
		} else{
			*min=lmin;
			if(dist[rmin]<dist[lmin]){
				*min=rmin;
			}
		}
	}
	
}
void initialize(double* dist, int* prev, bool* in, int numThreads, int start, int end){
	if(end==start+1){
		dist[start]=numeric_limits<double>::infinity();
		prev[start]=std::numeric_limits<int>::quiet_NaN();
		in[start]=false;
	} else{
		if (numThreads==1){
			int mid = (start+end)/2;
			initialize(dist, prev,in, 1, start,mid);
			initialize(dist, prev,in, 1,mid, end);
		} else{
			int halfnumthreads = numThreads/2;
			int mid = start + halfnumthreads*((end-start)/numThreads);
			thread otherThread(initialize,dist, prev, in, halfnumthreads,start, mid);
			initialize(dist,prev,in,numThreads-halfnumthreads,mid, end);
			otherThread.join();
		}
	}
}
void updateDistances(const double* const * matrix, double* dist, int* prev, bool* in, int numThreads, int start, int end, int cur_idx){
	if(end==start+1){
		if(!in[start] && (dist[cur_idx]+matrix[cur_idx][start])<dist[start]){
			dist[start]=dist[cur_idx]+matrix[cur_idx][start];
			prev[start]=cur_idx;
		}
	} else{
		if (numThreads==1){
			int mid = (start+end)/2;
			updateDistances(matrix,dist, prev,in, 1, start,mid,cur_idx);
			updateDistances(matrix,dist, prev,in, 1,mid, end,cur_idx);
		} else{
			int halfnumthreads = numThreads/2;
			int mid = start + halfnumthreads*((end-start)/numThreads);
			thread otherThread(updateDistances,matrix,dist, prev, in, halfnumthreads,start, mid,cur_idx);
			updateDistances(matrix,dist,prev,in,numThreads-halfnumthreads,mid, end,cur_idx);
			otherThread.join();
		}
	}
	/*for(int j=0; j<numVertices; j++){
			if(!in[j] && (dist[cur_idx]+matrix[cur_idx][j])<dist[j]){
				dist[j]=dist[cur_idx]+matrix[cur_idx][j];
				prev[j]=cur_idx;
			}
		}*/
}
void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev, int numThreads){
	dist = new double[numVertices];
	prev = new int[numVertices];
	bool* in = new bool[numVertices];
	initialize(dist,prev,in,numThreads,0,numVertices);
	dist[source]=0;
	in[source]=true;
	int cur_idx = source;
	for(int i=1; i<numVertices; i++){
		int minidx;
		getMinVertex(dist,prev,in,numThreads, 0, numVertices, &minidx);
		if(dist[minidx]!=numeric_limits<double>::infinity()){
			in[minidx]=true;
			cur_idx=minidx;
		}
		

		updateDistances(matrix,dist,prev,in,numThreads,0,numVertices,cur_idx);

		
	}
	/*cout<<"************"<<endl;
	for(int t=0; t<numVertices;t++){
		cout<<t<<" "<<prev[t]<<endl;
	}
	cout<<"************"<<endl;*/

	delete[] in;
}




