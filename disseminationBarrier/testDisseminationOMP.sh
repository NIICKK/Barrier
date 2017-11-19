#PBS -q cs6210
#PBS -l nodes=1:fourcore
#PBS -N testCentralized

OUTPUT=$PBS_O_WORKDIR/disseminationMP.txt

for nthreads in 2 3 4 5 6 7 8
do
	echo "Number of Threads: $nthreads" >> $OUTPUT
	./testDisseminationMP $nthreads 100000 >> $OUTPUT
        echo " " >> $OUTPUT
done
