
SERIAL CODE:
matrix size dimentions must be altered manually on line 10 & 11 in 'serial_main.c'. The matrix is randomly generated using rand(). 

PARALLEL CODE:
matrix dimentions must be manually altered on line 17 & 18 in 'mpi_main.c'. Again, the matrix is randomly generated using rand().


MAKEFILE USAGE IN TERMINAL:

:$ make
- - - -makes 'halvard.exe' which must be run by './halvard'

:$ make mpi
- - - -makes 'halvard_mpi.exe' which must be run by 'mpiexec -n <number of threads> ./halvard_mpi'

:$ make clean:
- - - -removes halvard and halvard_mpi


by default compiler flags -Wall, -g, -o and -O2 are included. 
