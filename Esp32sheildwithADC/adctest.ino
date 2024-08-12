#include <SPI.h>

const int csPin = 5;
const float referenceVoltage = 4.096;

void setup() {
  Serial.begin(115200);
  
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);

  SPI.begin(18, 19, 23, csPin); // SCK, MISO, MOSI, SS
}

uint16_t readADC(uint8_t channel) {
  // MCP3208 requires three bytes to be sent: start bit + single-ended mode + channel selection + 2 dummy bits
  uint8_t commandByte = 0x06 | (channel >> 2); // Start bit + single-ended mode + MSB of channel
  uint8_t secondByte = (channel & 0x03) << 6;  // Remaining 2 bits of channel

  digitalWrite(csPin, LOW); 

  SPI.transfer(commandByte);  // Send command byte
  uint8_t highByte = SPI.transfer(secondByte); // Send second byte and receive high byte of result
  uint8_t lowByte = SPI.transfer(0x00);       // Send dummy byte and receive low byte of result

  digitalWrite(csPin, HIGH); 

  uint16_t result = ((highByte & 0x0F) << 8) | lowByte; // Combine high and low byte into 12-bit result
  return result;
}

void loop() {
  for (int channel = 0; channel < 7; channel++) {
    uint16_t result = readADC(channel);
    float voltage = (result / 4095.0) * referenceVoltage; 
    Serial.print("Channel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.print(result); // Print the 12-bit result in decimal
    Serial.print(" (");
    Serial.print(voltage, 4); // Print voltage with 4 decimal places
    Serial.println(" V)");
    delay(1000);
  }
}

