/* gpiosysfs.h */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void gpioSetup(const char *pin);
void gpioCleanup(const char *pin);
void gpioWrite(const char *pin, const char *val);
