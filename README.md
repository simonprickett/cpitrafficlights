# Experiments with Low Voltage Labs Traffic Lights on Raspberry Pi in C

Let's look at a couple of ways of controlling the Raspberry Pi's GPIO pins using the C programming language, and the [Low Voltage Labs traffic light LEDs](http://lowvoltagelabs.com/products/pi-traffic/).

# Wiring Pi Method

[Wiring Pi](http://wiringpi.com/) is a well established library for handling GPIO interactions.  

[Here's my example code and documentation](wiringpi/).

# sysfs Method

Using this method requires no external libraries, we just need to write code to manipulate files on the Pi's filesystem.

[Here's my example code and documentation](sysfs/).

# Resources

* The [code samples page](https://elinux.org/RPi_GPIO_Code_Samples) at elinux.org has a wealth of information about GPIO programming for the Raspberry Pi.
* resin.io have also published a [good summary of options](https://docs.resin.io/learn/develop/hardware/gpio/#raspberry-pi) for working with GPIO.
