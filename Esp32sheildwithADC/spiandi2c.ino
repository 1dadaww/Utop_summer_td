#include <Arduino.h>
#include <ESP32TimerInterrupt.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>

// The Stepper pins
#define STEPPER1_DIR_PIN 16   //Arduino D9
#define STEPPER1_STEP_PIN 17  //Arduino D8
#define STEPPER2_DIR_PIN 4    //Arduino D11
#define STEPPER2_STEP_PIN 14  //Arduino D10
#define STEPPER_EN 15         //Arduino D12

const int csPin = 5; 
const float referenceVoltage = 4.096; 

// Diagnostic pin for oscilloscope
#define TOGGLE_PIN  32        //Arduino A4

const int PRINT_INTERVAL = 500;
const int LOOP_INTERVAL = 10;
const int  STEPPER_INTERVAL_US = 20;

const float kx = 20.0;

// Global objects
ESP32Timer ITimer(3);
Adafruit_MPU6050 mpu;         // Default pins for I2C are SCL: IO26, SDA: IO25

// Interrupt Service Routine for motor update
// Note: ESP32 doesn't support floating point calculations in an ISR
uint16_t readADC(uint8_t channel) {
  // MCP3208 requires three bytes to be sent: start bit + single-ended mode + channel selection + 2 dummy bits
  uint8_t commandByte = 0x06 | (channel >> 2); // Start bit + single-ended mode + MSB of channel
  uint8_t secondByte = (channel & 0x03) << 6;  // Remaining 2 bits of channel

  digitalWrite(csPin, LOW); // Select the MCP3208

  SPI.transfer(commandByte);  // Send command byte
  uint8_t highByte = SPI.transfer(secondByte); // Send second byte and receive high byte of result
  uint8_t lowByte = SPI.transfer(0x00);       // Send dummy byte and receive low byte of result

  digitalWrite(csPin, HIGH); // Deselect the MCP3208

  uint16_t result = ((highByte & 0x0F) << 8) | lowByte; // Combine high and low byte into 12-bit result
  return result;
}

void setup()
{
  Serial.begin(115200);
  pinMode(TOGGLE_PIN, OUTPUT);
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);

  SPI.begin(18, 19, 23, csPin); // SCK, MISO, MOSI, SS

  // Initialize I2C communication with custom SDA and SCL pins
  Wire.begin(25, 26);

  // Try to initialize Accelerometer/Gyroscope
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

  // Enable the stepper motor drivers
  pinMode(STEPPER_EN, OUTPUT);
  digitalWrite(STEPPER_EN, false);
}

void loop()
{
  // Static variables are initialized once and then the value is remembered between subsequent calls to this function
  static unsigned long printTimer = 0;  // time of the next print
  static unsigned long loopTimer = 0;   // time of the next control update
  static float tiltx = 0.0;             // current tilt angle

  // Print updates every PRINT_INTERVAL ms
  if (millis() > printTimer) {
    printTimer += PRINT_INTERVAL;
    Serial.print(tiltx * 1000);
    Serial.print(' ');
    Serial.println();
  }

  for (int channel = 0; channel < 1; channel++) {
    uint16_t result = readADC(channel);
    float voltage = (result / 4095.0) * referenceVoltage;
    Serial.print("Channel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.print(result);
    Serial.print(" (");
    Serial.print(voltage, 4); // Print voltage with 4 decimal places
    Serial.println(" V)");
    delay(1000);
  }
}
