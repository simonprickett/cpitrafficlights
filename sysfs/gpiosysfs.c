/* gpiosysfs.c */

#include "gpiosysfs.h"

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

void gpioSetup(const char *pin) {
	// TODO only export if not already exported...
	writeToFile("/sys/class/gpio/export", pin);

	char buf[33];
	struct stat statBuf;
	int pinExported = -1;

	sprintf(buf, "/sys/class/gpio/gpio%s/direction", pin);

	// May have to briefly wait for OS to make symlink! 
	while (pinExported != 0) {	
		sleep(1);
		pinExported = stat(buf, &statBuf);
	}

	writeToFile(buf, "out");
}

void gpioCleanup(const char *pin) {
	writeToFile("/sys/class/gpio/unexport", pin);
}

void gpioWrite(const char *pin, const char *val) {
	char buf[29];
	sprintf(buf, "/sys/class/gpio/gpio%s/value", pin);
	writeToFile(buf, val);
}
