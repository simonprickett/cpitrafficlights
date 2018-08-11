#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_LOW 0
#define GPIO_HIGH 1

#define RED 13
#define YELLOW 12
#define GREEN 14

static int gpioSetup(int pin);
static int gpioCleanup(int pin);
static int gpioWrite(int pin, int val);

static void allLightsOff();
static void interruptHandler(int);

static int gpioSetup(int pin) {
	// Export pin and set as output.
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	char buf[3];

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open /sys/class/gpio/export for writing!\n");
		return(-1);
	}

	sprintf(buf, "%d", pin);
	write(fd, buf, strlen(buf));

	close(fd);
	return(0);
}

static int gpioCleanup(int pin) {
	// TODO
	return 0;
}

static int gpioWrite(int pin, int val) {
	// TODO
	return 0;
}


static void allLightsOff() {
	gpioWrite(RED, GPIO_LOW);
	gpioWrite(YELLOW, GPIO_LOW);
	gpioWrite(GREEN, GPIO_LOW);
}

static void interruptHandler(int signal) {
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
		sleep(3000);

		// Red and Yellow
		gpioWrite(YELLOW, GPIO_HIGH);
		sleep(1000);

		// Green
		gpioWrite(RED, GPIO_LOW);
		gpioWrite(YELLOW, GPIO_LOW);
		gpioWrite(GREEN, GPIO_HIGH);
		sleep(5000);

		// Yellow
		gpioWrite(GREEN, GPIO_LOW);
		gpioWrite(YELLOW, GPIO_HIGH);
		sleep(2000);

		// Yellow off
		gpioWrite(YELLOW, GPIO_LOW);
	}
}
