# Compiler binary:
CPP= g++

# Recommended compiler flags for speed:
#	OpenMP enabled
#	full binary code optimization
#	full error and warning reports
#	no range checking within BRKGA:
CFLAGS= -O3 -fpermissive -fopenmp -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

# Compiler flags for debugging; uncomment if needed:
#	range checking enabled in the BRKGA API
#	OpenMP disabled
#	no binary code optimization
#CFLAGS= -DRANGECHECK -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

OBJECTS= tissueInstance.o tissueSolver.o tissueDecoder.o tissueVerifier.o Population.o brkga-main.o

# Targets:
all: brkga-main

brkga-main: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o brkga-main

brkga-main.o:
	$(CPP) $(CFLAGS) -c brkga-main.cpp

tissueInstance.o:
	$(CPP) $(CFLAGS) -c tissueInstance.cpp

tissueSolver.o:
	$(CPP) $(CFLAGS) -c tissueSolver.cpp

tissueDecoder.o:
	$(CPP) $(CFLAGS) -c tissueDecoder.cpp

tissueVerifier.o:
	$(CPP) $(CFLAGS) -c tissueVerifier.cpp

Population.o:
	$(CPP) $(CFLAGS) -c brkgaAPI/Population.cpp

# Remove:
clean:
	rm -f brkga-main $(OBJECTS)
