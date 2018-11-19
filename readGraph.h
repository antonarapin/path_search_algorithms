#ifndef READ_GRAPH
#define READ_GRAPH
#include <limits>
#include <fstream>
#include <iostream>
using namespace std;
int readGraph(ifstream& fin, double**& matrix, string*& vLabels, string**& eLabels);
int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels);
int readGraph(ifstream& fin, int**& edgeList, double*& weights, int& numEdges, string*& vLabels, string*& eLabels);
#endif