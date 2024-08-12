The new ESP32 sheild is made that combines with a mcp3208 ADC chip. The pin cnnections are using the default SPI pins of ESP32. In the new shield, the unstable pins such as pins for UART has been removed. For the rest GPIO pins The GPIO pins at top left corners are input only pins, the bottom left corners are the pins that support internal ADC of ESP32. For the right top corners, the SCL and SDA pins are the default pins for I2C communication. The default pins can be seen from the image.[ESP32pinout]

The ADC can be test using a simple script [adctest.ino].
