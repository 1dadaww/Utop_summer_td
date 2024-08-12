# ESP32 Shield with MCP3208 ADC Chip

This new ESP32 shield integrates an MCP3208 ADC chip, designed with the default SPI pins of the ESP32. We've optimized the design by removing unstable pins, such as those for UART, ensuring better reliability in various applications.

### GPIO Pin Layout
- **Top Left Corners:** Input-only pins.
- **Bottom Left Corners:** Pins that support the internal ADC of the ESP32.
- **Top Right Corners:** Default I2C communication pins (SCL and SDA).

The default pin configuration for the ESP32 can be seen below:

![ESP32 Pinout](ESP32pinout.png)

### Design Files
The complete design files for the shield are available in [ESP32withmcp3208V3.zip](ESP32withmcp3208V3.zip).

### Testing the ADC
You can test the MCP3208 ADC using the provided script: [adctest.ino](adctest.ino).
