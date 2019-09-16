#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"

ADXL345 accel;

int16_t ax, ay, az;

void setup() {
    Wire.begin();
    Serial.begin(9600);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accel.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
}

void loop() {
    // read raw accel measurements from device
    accel.getAcceleration(&ax, &ay, &az);

    // display tab-separated accel x/y/z values
    Serial.print("accel:\t");
    Serial.print("aX: ");
    Serial.print(ax); Serial.print("\t");
    Serial.print("aY: ");
    Serial.print(ay); Serial.print("\t");
    Serial.print("aZ: ");
    Serial.println(az);
    delay(500);
}
