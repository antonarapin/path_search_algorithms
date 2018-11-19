### This project contains six programs, including matrixDijkstra, listDijkstra, bellmanFord, parallelDijkstra, currency and mapqueue. Each program needs to be compiled individually using directions listed below.

## matrixDijkstra

To compile: `make matrixDijkstra`

To run: `./matrixDijkstra <filein> <fileout> <sourcevertex> <destinationvertex>`

The matrixDijkstra program takes in two filenames and two strings as command line arguments. First file <filein> is a textfile that contains a graph with vetrices and edges in a particular format, see graph.txt. Second file <fileout> is a textfile that matrixDijkstra outputs a generated path to. The first string argument <sourcevertex> is the name of the vertex in <filein> that is the source of the path search. The string argument <destinationvertex> is the name of the vertex in <filein> that is the destination of the path search. The matrixDijkstra program utilizes matrix-based Dijkstra's algorithm to find the shortest path from <sourcevertex> to <destinationvertex> in terms of the possible edges and their weights listed in <filein>. It writes the generated path to the <fileout> in the same format as in graph.txt. The matrixDijkstra program prints out to the terminal the total length of the path from <sourcevertex> to <destinationvertex> and time that it took for Dijkstra's algorithm to run in microseconds.

## listDijkstra

To compile: `make listDijkstra`

To run: `./listDijkstra <filein> <fileout> <sourcevertex> <destinationvertex>`

The listDijkstra program takes in two filenames and two strings as command line arguments. First file <filein> is a textfile that contains a graph with vetrices and edges in a particular format, see graph.txt. Second file <fileout> is a textfile that ListDijkstra outputs a generated path to. The first string argument <sourcevertex> is the name of the vertex in <filein> that is the source of the path search. The string argument <destinationvertex> is the name of the vertex in <filein> that is the destination of the path search. The listDijkstra program utilizes adjacency list -based Dijkstra's algorithm to find the shortest path from <sourcevertex> to <destinationvertex> in terms of the possible edges and their weights listed in <filein>. It writes the generated path to the <fileout> in the same format as in graph.txt. The listDijkstra program prints out to the terminal the total length of the path from <sourcevertex> to <destinationvertex> and time that it took for Dijkstra's algorithm to run in microseconds.

## bellmanFord

To compile: `make bellmanFord`

To run: `./bellmanFord <filein> <fileout> <sourcevertex> <destinationvertex>`

The bellmanFord program takes in two filenames and two strings as command line arguments. First file <filein> is a textfile that contains a graph with vetrices and edges in a particular format, see graph.txt. Second file <fileout> is a textfile that bellmanFord outputs a generated path to. The first string argument <sourcevertex> is the name of the vertex in <filein> that is the source of the path search. The string argument <destinationvertex> is the name of the vertex in <filein> that is the destination of the path search. The bellmanFord program utilizes Bellman-Ford algorithm to find the shortest path from <sourcevertex> to <destinationvertex> or to detect and find any negative cycles in the graph provided by <filein>. If there are no negative cycles, bellmanFord writes the shortest path from <sourcevertex> to <destinationvertex> to <fileout> in the appropriate format and print out to the terminal the message that no negative cycles were detected, the total weight of the path and the time in microseconds that it took for bellmanFord to run. If a negative cycle was detected, bellmanFord finds the negative cycles and writes the negative cycle with all vetrices and edges that belong to it to the <fileout> in the appropriate format. Also, bellmanFord program prints out the message that a negative cycle was detected, the total weight of the path and the time in microseconds that it took for bellmanFord to run.

## currency

To compile: `make currency`

To run: `./currency <filein> <fileout> <sourcevertex> <destinationvertex> <exchangefee>`

The currency function takes in two filenames, two strings and a double as command line arguments. First file <filein> is a textfile that contains a graph with vetrices and edges in a particular format, see exchangerates.txt. The second file <fileout> is a textfile that currency writes the found path to. The first string parameter <sourcevertex> is the name of the vertex (currency) which is being exchanged. The second string parameter <destinationvertex> is the vertex to which path should lead, in other words the currency to which money is being exchanged. The currency program finds the optiml exchange path with a given <exchangefee> from a given <sourcevertex> to <destinationvertex> using Bellman-Ford algorithm, it writes the found path to the <fileout> in the appropriate format. Also, currency prints out the total weight of the path with account for the exchange fee as an effective exchange and the total time it took for algorithm to run in microseconds. If There is a cycle in the exchange with a given <exchangefee>, there is an arbitrage opportunity. The currency program then finds the cycle with the arbitrage opportunity, writes it to <fileout> in the appropriate format, and prints out the warning to the terminal that arbitrage opportunity was detected, also printing out the total weight of the wound cycle and runtime of the algorithm in microseconds.

## parallelDijkstra

To compile: `make parallelDijkstra`

To run: `./parallelDijkstra <filein> <fileout> <sourcevertex> <destinationvertex> <numberthreads>`

The parallelDijkstra program takes in two filenames and two strings and an integer as command line arguments. First file <filein> is a textfile that contains a graph with vetrices and edges in a particular format, see graph.txt. Second file <fileout> is a textfile that parallelDijkstra outputs a generated path to. The first string argument <sourcevertex> is the name of the vertex in <filein> that is the source of the path search. The string argument <destinationvertex> is the name of the vertex in <filein> that is the destination of the path search. The <numberthreads> argument relates to the number of threads that parallelDijkstra uses to find the shortest path recursively. The parallelDijkstra program utilizes matrix-based Dijkstra's algorithm implemented recursively in parallel to find the shortest path from <sourcevertex> to <destinationvertex> in terms of the possible edges and their weights listed in <filein>. It writes the generated path to the <fileout> in the appropriate format. The parallelDijkstra program prints out to the terminal the total length of the path from <sourcevertex> to <destinationvertex>, CPU time and clock time that it took Dijkstra's algorithm to run in microseconds given the <numberthreads>.

## mapqueue

To compile: `make mapqueue`

To run: `./mapqueue <numberthreads>`

The mapqueue program take an integer <numberthreads> as a command line argument. The mapqueue program simulates the job queue, with each job taking some time to complete, and two types of threads, one of which creates a new job of random length every send and another type of threads is the threads that take jobs from the queue and simulate processing of each job for a time that corresponds to the length of a given job. The mapqueue program takes <numberthreads> argument as an integer value signifying the number of worker threads that would process jobs to create. Every time the job is added to the job queue the length of the new job and the current number of the jobs in the queue is printed to the terminal window. Also, every time a worker thread pops the job from the queue to process it, mapqueue prints out the number of the worker thread that popped the job and the remaining number of the jobs in the queue. Every time a worker thread finishes processing a job, map queue prints out the number of he worker thread and a message that it finished processing its job.
