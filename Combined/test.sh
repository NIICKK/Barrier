#PBS -q cs6210
#PBS -l nodes=8:sixcore
#PBS -N combine

MPI_MCA_mpi_yield_when_idle=0

OUTPUT=$PBS_O_WORKDIR/combine.txt

for nprocs in 2 3 4 5 6 7 8
do
    echo "Number of Processes: $nprocs" >> $OUTPUT
    for nthreads in 2 3 4 5 6 7 8 9 10 11 12
    do 
        echo "Number of Threads: $nthreads">> $OUTPUT
        $(RUN) --hostfile $PBS_NODEFILE -np $nprocs ./testCombine $nthreads 100000 >> $OUTPUT
        echo " " >> $OUTPUT
    done
done
