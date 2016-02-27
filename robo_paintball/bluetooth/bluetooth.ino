/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include <AFMotor.h>

// Define o motor1 ligado a conexao 1
AF_DCMotor motor1(1); 
// Define o motor2 ligado a conexao 4
AF_DCMotor motor2(4);

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
//00:19:86:00:0F:F9
PS3BT PS3(&Btd, 0x00, 0x19, 0x86, 0x00, 0x0F, 0xF9); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  // Define a velocidade maxima para os motores 1 e 2
  motor1.setSpeed(255); 
  motor2.setSpeed(255); 

}
void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117){
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      // Aciona o motor 1 no sentido horario
      motor1.run(FORWARD); 
      // Aciona o motor 2 no sentido anti-horario
      motor2.run(BACKWARD); 
    } 
    else {

      motor1.run(RELEASE); 
      motor2.run(RELEASE);
    }

    if(PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
    }

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
//      if (PS3.getButtonClick(TRIANGLE)) {
//        Serial.print(F("\r\nTraingle"));
//        PS3.setRumbleOn(RumbleLow);
//      }
//      if (PS3.getButtonClick(CIRCLE)) {
//        Serial.print(F("\r\nCircle"));
//        PS3.setRumbleOn(RumbleHigh);
//      }
//      if (PS3.getButtonClick(CROSS)){
//        Serial.print(F("\r\nCross"));
//      }
//      if (PS3.getButtonClick(SQUARE)){
//        Serial.print(F("\r\nSquare"));
//      }
//      if (PS3.getButtonClick(UP)) {
//        Serial.print(F("\r\nUp"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED4);
//        }
//      }
//      if (PS3.getButtonClick(RIGHT)) {
//        Serial.print(F("\r\nRight"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED1);
//        }
//      }
//      if (PS3.getButtonClick(DOWN)) {
//        Serial.print(F("\r\nDown"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED2);
//        }
//      }
//      if (PS3.getButtonClick(LEFT)) {
//        Serial.print(F("\r\nLeft"));
//        if (PS3.PS3Connected) {
//          PS3.setLedOff();
//          PS3.setLedOn(LED3);
//        }
//      }

//      if (PS3.getButtonClick(L1))
//        Serial.print(F("\r\nL1"));
//      if (PS3.getButtonClick(L3))
//        Serial.print(F("\r\nL3"));
//      if (PS3.getButtonClick(R1))
//        Serial.print(F("\r\nR1"));
//      if (PS3.getButtonClick(R3))
//        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
}



