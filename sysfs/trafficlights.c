#include <signal.h>
#include <unistd.h>
#include "gpiosysfs.h"

#define GPIO_LOW "0"
#define GPIO_HIGH "1"

#define RED "9"
#define YELLOW "10"
#define GREEN "11"

static void allLightsOff();
static void interruptHandler(const int);

static void allLightsOff() {
	gpioWrite(RED, GPIO_LOW);
	gpioWrite(YELLOW, GPIO_LOW);
	gpioWrite(GREEN, GPIO_LOW);
}

void interruptHandler(const int signal) {
	allLightsOff();
	gpioCleanup(RED);
	gpioCleanup(YELLOW);
	gpioCleanup(GREEN);
	exit(0);
}

int main(void) {
	signal(SIGINT, interruptHandler);

	gpioSetup(RED);
	gpioSetup(YELLOW);
	gpioSetup(GREEN);

	allLightsOff();

	while(1) {
		// Red
		gpioWrite(RED, GPIO_HIGH);
		sleep(3);

		// Red and Yellow
		gpioWrite(YELLOW, GPIO_HIGH);
		sleep(1);

		// Green
		gpioWrite(RED, GPIO_LOW);
		gpioWrite(YELLOW, GPIO_LOW);
		gpioWrite(GREEN, GPIO_HIGH);
		sleep(5);

		// Yellow
		gpioWrite(GREEN, GPIO_LOW);
		gpioWrite(YELLOW, GPIO_HIGH);
		sleep(2);

		// Yellow off
		gpioWrite(YELLOW, GPIO_LOW);
	}
}
