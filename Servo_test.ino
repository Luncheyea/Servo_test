#include <HCPCA9685.h> // Include the HCPCA9685 library created by Andrew Davies

#define I2CAdd 0x40 // Default address of the PCA9685 Module
HCPCA9685 HCPCA9685(I2CAdd); // Define Library to use I2C communication

void setup() {
  HCPCA9685.Init(SERVO_MODE); // Set to Servo Mode
  HCPCA9685.Sleep(false); // Wake up PCA9685 module

  Serial.begin(115200);
}

int16_t degree = 10, pin = 0;
void loop() {
  if (Serial.available()) {
    Serial.flush();

    String receive = "";
    while (Serial.available()) {
      receive += (char)Serial.read();
      delay(2);
    }

    int8_t index = receive.indexOf("p"), i = 0;
    if (index >= 0) {
      pin = receive[index + 1] - '0';

      Serial.print("pin=");
      Serial.println(pin);
    } else {
      degree = 0;
      while (receive[i] >= '0' && receive[i] <= '9')
        degree = degree * 10 + (receive[i++] - '0');

      if (degree > 360)
        degree = 360;
      else if (degree < 10)
        degree = 10;

      Serial.print("pin");
      Serial.print(pin);
      Serial.print(" = ");
      Serial.println(degree);

      HCPCA9685.Servo(pin, degree); // Move Servo 0
    }
  }

  delay(500);
}





