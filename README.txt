______________________________________________________________________________________
openMP
--------------------------------------------------------------------------------------
Centralized Barrier

Compile: make testCentralized

Usage:   ./testCentralzied [number of threads] [number of rounds of experiment]

--------------------------------------------------------------------------------------
Dissemination Barrier

Compile: make testDissemination

Usage:   ./testDissemination [number of threads] [number of rounds of experiment]

_____________________________________________________________________________________
MPI
-------------------------------------------------------------------------------------
Dissemination Barrier

Compile: make testDisseminationMPI

Usage:  mpirun -np [number of processes] ./testDisseminationMPI

-------------------------------------------------------------------------------------
Tournament Barrier

Compile: make testTournament

Usage:  mpirun -np [number of processes] ./testTournament

-------------------------------------------------------------------------------------
Combined Barrier

Compile: make testCombine

Usage: mpirun -np [number of processes] ./testCombine [number of threads] [number of rounds of experiment]


NOTE:

For MPI barriers and combined barriers, you probably need to change the MPICC in makefile due to 
version difference.