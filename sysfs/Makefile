CC=gcc
CFLAGS=-Wall
EXECUTABLE=trafficlights

.DEFAULT_GOAL := trafficlights

trafficlights: trafficlights.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) trafficlights.c 

clean: 
	@rm -f $(EXECUTABLE)
