CC=g++


CCFLAGS=-c -Wall


release: aisdiGraphs


debug: CCFLAGS += -g
debug: aisdiGraphs


aisdiGraphs: main.o functions.o
	$(CC) main.o functions.o -o aisdiGraphs


main.o: main.cpp functions.h
	$(CC) $(CCFLAGS) main.cpp


functions.o: functions.cpp functions.h
	$(CC) $(CCFLAGS) functions.cpp


clean:
	rm -f *.o
