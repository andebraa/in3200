# in3200
Code from projects in the subject 'high performance computing' (in3200) at the university of oslo


Makefile generates two .exe files, one with openMP and one without. The main code uses the file name hard coded into the script, however the test file requires a filename given in the command line. An error and usage will be explained if not given.

If you wish to run larger data sets than the 50000 one you will need to comment out the 2D table method and Count mutual links 1. This means everything from line 30 to line 60 in main, and line 30 to 80 in test!  


---------------------------------------------------------------------
to compile:
make -> multi.exe & single.exe
multi has -fopenMP included

to run:
./multi <filename> 

where filname is for example data_50000.txt. This data set is included in the zip. This data set is simply web_NotreDame slized to the first 50 000 webpages. 
