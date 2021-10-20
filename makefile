.SUFFIXES: .cxx .cpp .hxx
DIR = `basename $(CURDIR)

FIBHEAP = FibHeap

CFIBHEAP = $(FIBHEAP).cxx

XFIBHEAP = $(FIBHEAP).x

HEADER1 = FibHeap.hxx


CFLAGS = -std=c++11

CXX = g++

.PHONY: all tar clean runFIBHEAP

all: $(XFIBHEAP) 

$(XFIBHEAP): $(CFIBHEAP) $(HEADER1)
	$(CXX) $(CFLAGS) -o $(XFIBHEAP)	$<


runFIBHEAP: all
	./$(XFIBHEAP)

clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out

tar: clean
	(cd ../;tar zcvf $(DIR).tar.gz $(DIR))
