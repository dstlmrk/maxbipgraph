# Maximum Bipartite Graph

This repo is part of my semester project for Parallel and Distributed Programming subject.
The main goal is looking for the maximal bipartite graph. Input is from the file
and output to stdout.

### Example of usage

Input is represented by number of nodes and adjacency matrix:
```
10
0100101011
1001111000
0000101100
0100101001
1111010111
0100101111
1111010000
0010110011
1000110100
1001110100
```

Usage with 4 cores (2 processes x 2 threads):
```
$ mpirun -np 2 ./cmake-build-debug/maxbipgraph 2 ./data/graph10_5.txt
[load] count of vertices: 10, edges: 25
[master] first solution: 18
[master] better solution: 19
[slave] done
[master] done
============================================================================
[result] colors of graph: 1011010100, number of edges: 19
 0 1 0 0 1 0 1 0 1 1
 1 0 0 1 0 1 0 0 0 0
 0 0 0 0 1 0 1 0 0 0
 0 1 0 0 1 0 1 0 0 1
 1 0 1 1 0 1 0 1 0 0
 0 1 0 0 1 0 1 0 1 1
 1 0 1 1 0 1 0 0 0 0
 0 0 0 0 1 0 0 0 1 1
 1 0 0 0 0 1 0 1 0 0
 1 0 0 1 0 1 0 1 0 0

Elapsed time is 2318 ms
Number of threads: 2
```

## Compilation

You should use `mpic++` compiler for MPI library. Other necessary options are `-std=c++11` and ` -fopenmp -O3` because of OpenMP.