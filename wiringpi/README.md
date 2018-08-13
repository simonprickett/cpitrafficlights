# Experiments with Low Voltage Labs Traffic Lights on Raspberry Pi in C

## Wiring Pi Method

TODO Overview...


### Attach Traffic Lights

Attach the traffic lights so that they are connected to GPIO 9, 10, 11.

### Install Wiring Pi

```
$ cd <projectsFolder>
$ git clone git://git.drogon.net/wiringPi
$ cd wiringPi
$ ./build
```

### Compile and Run Code

Clone this repo, then:

```
$ git clone https://github.com/simonprickett/cpitrafficlights.git
$ cd cpitrafficlights/wiringpi
$ make
$ ./trafficlights
```
