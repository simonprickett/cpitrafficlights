#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_LOW "0"
#define GPIO_HIGH "1"

#define RED "9"
#define YELLOW "10"
#define GREEN "11"

static void writeToFile(const char *absoluteFileName, const char *contents); 
static void gpioSetup(const char *pin);
static void gpioCleanup(const char *pin);
static void gpioWrite(const char *pin, const char *val);
static void allLightsOff();
static void interruptHandler(const int);

static void writeToFile(const char *absoluteFileName, const char *contents) {
	int fd = open(absoluteFileName, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", absoluteFileName);
		exit(1);
	}

	int contentsLength = strlen(contents);

	if (write(fd, contents, contentsLength) != contentsLength) {
		fprintf(stderr, "Failed to write entire value %s to %s!\n", contents, absoluteFileName);
		close(fd);
		exit(1);
	}

	close(fd);
}

static void gpioSetup(const char *pin) {
	writeToFile("/sys/class/gpio/export", pin);

	// Short sleep to let the operating system create a symlink!
	sleep(1);

	char buf[33];
	sprintf(buf, "/sys/class/gpio/gpio%s/direction", pin);

	writeToFile(buf, "out");
}

static void gpioCleanup(const char *pin) {
	writeToFile("/sys/class/gpio/unexport", pin);
}

static void gpioWrite(const char *pin, const char *val) {
	char buf[29];
	sprintf(buf, "/sys/class/gpio/gpio%s/value", pin);
	writeToFile(buf, val);
}

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
