import numpy as np
import sys

#Takes a two collumn array from a file and returns the arrray
#cut down to the size given


if(len(sys.argv) != 3):
    print("usage: {} <data file to be cut down> <new size>".format(sys.argv[0]))
    raise IndexError()


def readfile(filename):
    infile = open(filename, 'r')
    infile.readline()
    infile.readline()
    sizeline = infile.readline().split()
    nodes = int(sizeline[2])
    edges = int(sizeline[4])
    from_to = np.zeros((edges, 2)) #makes array with two collumns
    infile.readline()
    for i, line in enumerate(infile):
        elem = np.array(line.split())
        elem=elem.astype(int)
        from_to[i] = elem
    infile.close()
    return from_to

def writefile(filename, arr, size):
    outfile=open(filename, 'w')
    outfile.write("# Directed graph \n")
    outfile.write("# just an example \n")
    nodes = int(np.max(arr) +1)
    outfile.write("# Nodes: {:d} Edges: {:d} \n".format(nodes, size ))
    outfile.write("# FromNodeId     ToNodeId \n")
    for i, elem in enumerate(arr):
        outfile.write("{:d}  {:d} \n" .format(int(elem[0]), int(elem[1])))
    outfile.close()
    return 0


from_to  = readfile(str(sys.argv[1]))
newsize = int(sys.argv[2])

writefile('data_'+str(newsize)+'.txt', from_to[:newsize], newsize)
