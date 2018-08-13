#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <wiringPi.h>

#define RED 13
#define YELLOW 12
#define GREEN 14

static void allLightsOff();
static void interruptHandler(int);

static void allLightsOff() {
	digitalWrite(RED, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, LOW);
}

static void interruptHandler(int signal) {
	allLightsOff();
	exit(0);
}

int main(void) {
	signal(SIGINT, interruptHandler);

	if (-1 == wiringPiSetup()) {
		printf("Failed to setup Wiring Pi!\n");
		return 1;
	}

	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);

	allLightsOff();

	while(1) {
		// Red
		digitalWrite(RED, HIGH);
		delay(3000);

		// Red and Yellow
		digitalWrite(YELLOW, HIGH);
		delay(1000);

		// Green
		digitalWrite(RED, LOW);
		digitalWrite(YELLOW, LOW);
		digitalWrite(GREEN, HIGH);
		delay(5000);

		// Yellow
		digitalWrite(GREEN, LOW);
		digitalWrite(YELLOW, HIGH);
		delay(2000);

		// Yellow off
		digitalWrite(YELLOW, LOW);
	}

	// Never reached, keeps the compiler happy.
	return 0;
}
