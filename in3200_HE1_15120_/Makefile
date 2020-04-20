CFLAGSS = -Wall -g -O2
CFLAGSP = -Wall -g -O2 -fopenmp
LDFLAGS =  -lm

FILES = main.c read_graph_from_file1.c read_graph_from_file1.h read_graph_from_file2.c read_graph_from_file2.h count_mutual_links1.c count_mutual_links1.h count_mutual_links2.c count_mutual_links2.h top_n_webpages.c top_n_webpages.h test.c test.h



all: multi single


multi: $(FILES)
	gcc $(CFLAGSP) -o multi $(FILES) $(LDFLAGS)

single: $(FILES)
	gcc $(CFLAGSS) -o single $(FILES) $(LDFLAGS)

clean:
	rm -f multi
	rm -f single




