#ifndef SHORTEST_PATH
#define SHORTEST_PATH
#include <limits>
#include <iostream>

using namespace std;

void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev);
int getPath(int source, int dest, const int* prev, int*& path);
void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev);
int bellmanFord(const int* const * edges, const double* weights, int numVertices, int numEdges, int source, double*& dist, int*& prev);
int getCycle(int vertex, const int* prev, int*& cycle);
void getMinVertex(double* dist, int* prev, bool* in, int numThreads, int start, int end, int* min);
void initialize(double* dist, int* prev, bool* in, int numThreads, int start, int end);
void updateDistances(const double* const * matrix,double* dist, int* prev, bool* in, int numThreads, int start, int end, int cur_idx);
void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev, int numThreads);

#endif