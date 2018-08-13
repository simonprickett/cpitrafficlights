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

void writeToFile(const char *absoluteFileName, const char *contents); 
void gpioSetup(const char *pin);
void gpioCleanup(const char *pin);
void gpioWrite(const char *pin, const char *val);
void allLightsOff();
void interruptHandler(int);

void writeToFile(const char *absoluteFileName, const char *contents) {
	int fd = open(absoluteFileName, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", absoluteFileName);
		exit(1);
	}

	int contentsLength = strlen(contents);

	if (write(fd, contents, contentsLength) != contentsLength) {
		fprintf(stderr, "Failed to write entire value %s to %s!\n", contents, absoluteFileName);
		exit(1);
	}

	close(fd);
}

void gpioSetup(const char *pin) {
	// Export pin and set as output.
	int fd = open("/sys/class/gpio/export", O_WRONLY);
	char buf[33];

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open /sys/class/gpio/export for writing!\n");
		exit(1);
	}

	write(fd, pin, strlen(pin));

	close(fd);

	// Short sleep to let the operating system create a symlink!
	sleep(1);

	sprintf(buf, "/sys/class/gpio/gpio%s/direction", pin);

	fd = open(buf, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", buf);
		exit(1);
	}

	write(fd, "out", 3);
	close(fd);
}

void gpioCleanup(const char *pin) {
	// Unexport pin.
	int fd = open("/sys/class/gpio/unexport", O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open /sys/class/gpio/unexport for writing!\n");
		exit(1);
	}

	write(fd, pin, strlen(pin));
	close(fd);
}

void gpioWrite(const char *pin, const char *val) {
	char buf[29];
	int fd;

	sprintf(buf, "/sys/class/gpio/gpio%s/value", pin);

	fd = open(buf, O_WRONLY);

	if (-1 == fd) {
		fprintf(stderr, "Couldn't open %s for writing!\n", buf);
		exit(1);
	}

	write(fd, val, 1);

	close(fd);
}

void allLightsOff() {
	gpioWrite(RED, GPIO_LOW);
	gpioWrite(YELLOW, GPIO_LOW);
	gpioWrite(GREEN, GPIO_LOW);
}

void interruptHandler(int signal) {
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
