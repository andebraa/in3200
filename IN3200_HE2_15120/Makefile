CFLAGS = -Wall -g -O2
LDFLAGS = -lm 

FILES  = serial_main.c count_friends_of_ten.c count_friends_of_ten.h 
FILES_MPI = mpi_main.c mpi_count_friends_of_ten.c mpi_count_friends_of_ten.h


halvard: $(FILES)
	gcc $(CFLAGS) -o halvard $(FILES) $(LDFLAGS)

mpi: $(FILES_MPI)
	mpicc $(CFLAGS) -o halvard_mpi $(FILES_MPI) $(LDFLAGS)


clean:
	rm -f halvard	
	rm -f halvard_mpi
