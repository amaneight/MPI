# MPI program for implementing averaging algorithm for distributed clock synchronisation on any number of (even or odd) processors.

When processes are deployed on multiple processors and they run concurrently, it is economical to share system resources. As sharing can be cooperative or competetive it's essential that the communicataion between these processes takes place in correct order and for this clocks of all the processors should be synchronized. Each clock has its own drift and if clocks go out of sync then it will become difficult for processes to interact with each other.

The averaging algorithm is a decentralized algorithm which divides time into resynchronization interval called R. All the processors broadcast their time to each other and by averaging all the timestamps, they set their local time.

The program displays
1. Δt value for each processor
2. Synchronised time for every processor

This also demonstrates clock synchronisation for different clock drifts values among the processors.

Note: MPI process may be represented as a physical processor.

## To compile the code:
1. Using make command compile the file containing code, present in src directory.
2. On successful compilation, the binary file will be stored in build directory (create build directory).
3. Run the following command to execute the program for 4 processes. 

### mpirun - np 4 build / mpiAvgTimeAlgo
