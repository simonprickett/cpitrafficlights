CC=gcc
CFLAGS=-Wall
EXECUTABLE=trafficlights

.DEFAULT_GOAL := trafficlights

gpiosysfs.o: gpiosysfs.h gpiosysfs.c
	$(CC) $(CLFAGS) -c gpiosysfs.c

trafficlights: trafficlights.c gpiosysfs.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) trafficlights.c gpiosysfs.o

clean: 
	@rm -f gpiosysfs.o
	@rm -f $(EXECUTABLE)
