#include "Wire.h"
#include "I2Cdev.h"
#include "ADXL345.h"

ADXL345 accel;

int16_t ax, ay, az;
float X_out, Y_out, Z_out, roll, pitch, rollF, pitchF;

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
    X_out = (float)ax/256;
    Y_out = (float)ay/256;
    Z_out = (float)az/256;
    
    roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
    pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;
    
    // display tab-separated accel x/y/z values
    rollF = 0.94 * rollF + 0.06 * roll;
    pitchF = 0.94 * pitchF + 0.06 * pitch;
  
    Serial.print(rollF);
    Serial.print("/");
    Serial.println(pitchF);
}
