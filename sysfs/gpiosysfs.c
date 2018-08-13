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
	writeToFile("/sys/class/gpio/export", pin);

	// Short sleep to let the operating system create a symlink!
	sleep(1);

	char buf[33];
	sprintf(buf, "/sys/class/gpio/gpio%s/direction", pin);

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
