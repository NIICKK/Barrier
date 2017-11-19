#PBS -q cs6210
#PBS -l nodes=1:sixcore
#PBS -N testCentralized

OUTPUT=$PBS_O_WORKDIR/centralized.txt

for nthreads in 2 3 4 5 6 7 8
do
	echo "Number of Threads: $nthreads" >> $OUTPUT
	./testCentralized $nthreads 10000 >> $OUTPUT
        echo " " >> $OUTPUT
done
