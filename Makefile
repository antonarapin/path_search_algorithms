OPTS = -Wall -g -pthread --std=c++11 

readGraph.o: readGraph.cc readGraph.h
	g++ ${OPTS} -c readGraph.cc

shortestPath.o: shortestPath.cc shortestPath.h BinaryHeap.h
	g++ ${OPTS} -c shortestPath.cc 

BinaryHeap.o: BinaryHeap.cc BinaryHeap.h
	g++ ${OPTS} -c BinaryHeap.cc

bellmanFord: bellmanFord.cc readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o bellmanFord bellmanFord.cc readGraph.o shortestPath.o BinaryHeap.o

currency: currency.cc readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o currency currency.cc readGraph.o shortestPath.o BinaryHeap.o

matrixDijkstra: matrixDijkstra.cc readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o matrixDijkstra matrixDijkstra.cc readGraph.o shortestPath.o BinaryHeap.o

parallelDijkstra: parallelDijkstra.cc readGraph.o shortestPath.o BinaryHeap.o
	g++ ${OPTS} -o parallelDijkstra parallelDijkstra.cc readGraph.o shortestPath.o BinaryHeap.o

listDijkstra: listDijkstra.cc readGraph.o shortestPath.o  BinaryHeap.o
	g++ ${OPTS} -o listDijkstra listDijkstra.cc readGraph.o shortestPath.o BinaryHeap.o

mapqueue: mapqueue.cc 
	g++ ${OPTS} -o mapqueue mapqueue.cc