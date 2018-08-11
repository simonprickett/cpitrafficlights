#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_LOW 0
#define GPIO_HIGH 1

#define RED 9 
#define YELLOW 10
#define GREEN 11

static void gpioSetup(int pin);
static void gpioCleanup(int pin);
static void gpioWrite(int pin, int val);

static void allLightsOff();
static void interruptHandler(int);

static void gpioSetup(int pin) {
	// Export pin and set as output.
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	char buf[33];

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open /sys/class/gpio/export for writing!\n");
		exit(1);
	}

	sprintf(buf, "%d", pin);
	write(fd, buf, strlen(buf));

	close(fd);

	sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);

	fd = open(buf, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", buf);
		exit(1);
	}

	write(fd, "out", 3);
	close(fd);
}

static void gpioCleanup(int pin) {
	// TODO
}

static void gpioWrite(int pin, int val) {
	char buf[29];
	int fd;

	sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);

	fd = open(buf, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", buf);
		exit(1);
	}

	sprintf(buf, "%d", val);

	write(fd, buf, 1);

	close(fd);
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
