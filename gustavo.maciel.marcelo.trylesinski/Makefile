NVCC	  = nvcc
CXX       = g++
CPPFLAGS  = -std=c++11 -Wall -pedantic -O3 -flto
CUDAFLAGS = -arch sm_30 -Xptxas --opt-level=3
LDFLAGS   = -L/usr/local/cuda/lib64 -lcuda -lcudart
objects   = main.o dclock.o cpu_montecarlo.o
tobjects  = test.o dclock.o cpu_montecarlo.o

main : $(objects)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test : $(tobjects)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o : dclock.h cpu_montecarlo.h
test.o : dclock.h cpu_montecarlo.h
dclock.o : dclock.h
cpu_montecarlo.o: cpu_montecarlo.h
#reduce.o : reduce.cu reduce.cuh mtrutils.h
#	$(NVCC) $(CUDAFLAGS) -c $<

.PHONY : all
all : main test

.PHONY : clean
clean :
	-rm -f main test $(objects) $(tobjects)
