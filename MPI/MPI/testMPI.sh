#PBS -q cs6210
#PBS -l nodes=1:sixcore
#PBS -N testDisseminationMPI

MPI_MCA_mpi_yield_when_idle=0

OUTPUT=$PBS_O_WORKDIR/mpi.txt

for nprocs in 2 3 4 5 6 7 8 9 10 11 12
do
	echo "Number of Processes: $nprocs" >> $OUTPUT
	mpirun --hostfile $PBS_NODEFILE -np $nprocs ./testMPI >> $OUTPUT
        echo " " >> $OUTPUT
done
