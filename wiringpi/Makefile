CC=gcc
CFLAGS=-Wall
LIBS=-lwiringPi
EXECUTABLE=trafficlights

.DEFAULT_GOAL := trafficlights

trafficlights: trafficlights.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) trafficlights.c $(LIBS) 

clean: 
	@rm -f $(EXECUTABLE)
